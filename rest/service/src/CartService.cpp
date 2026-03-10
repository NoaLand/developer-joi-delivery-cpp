#include "tw/delivery/service/CartService.h"

#include <iostream>

namespace tw::delivery::service {
    CartService::CartService(UserService uService, ProductService pService) : userService{std::move(uService)}, productService{std::move(pService)} {}

    CartService::CartService(std::unordered_map<std::string, Cart>& carts, UserService& uService, ProductService& pService)
        : userCarts{std::move(carts)}, userService{std::move(uService)}, productService{std::move(pService)} {}

    Cart CartService::addProductToCartForUser(const AddProductRequest& addProductRequest) {
        auto user = userService.fetchUserById(addProductRequest.userId);
        if (!user.has_value()) {
            std::cerr << "User not found: " << addProductRequest.userId << std::endl;
            return {};
        }

        auto product = productService.getProduct(addProductRequest.productId, addProductRequest.outletId);
        if (!product) {
            std::cerr << "Product not found: " << addProductRequest.productId << std::endl;
            return {};
        }

        Cart& cart = fetchCartForUser(user.value());
        cart.products.emplace_back(std::move(product));

        return cart;
    }

    Cart CartService::getCartForUser(std::string_view userId) {
        return fetchCartForUser(userService.fetchUserById(userId).value());
    }

    Cart& CartService::fetchCartForUser(const User& user) {
        return userCarts.at(user.userId); // throws if not found
    }
}