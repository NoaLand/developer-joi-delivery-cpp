#pragma once

#include "ProductService.h"
#include "UserService.h"
#include "core/Cart.h"
#include "core/User.h"
#include "data/SeedData.h"
#include "dto/AddProductRequest.h"

#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>

class CartService {
    std::unordered_map<std::string, Cart> userCarts{SeedData::cartForUsers};
    UserService userService;
    ProductService productService;

public:
    CartService(UserService uService, ProductService pService)
        : userService{std::move(uService)}, productService{std::move(pService)} {}

    CartService(std::unordered_map<std::string, Cart>& carts, UserService& uService, ProductService& pService)
        : userCarts{std::move(carts)}, userService{std::move(uService)}, productService{std::move(pService)} {}

    Cart addProductToCartForUser(const AddProductRequest& addProductRequest) {
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

    Cart getCartForUser(std::string_view userId) {
        return fetchCartForUser(userService.fetchUserById(userId).value());
    }

private:
    Cart& fetchCartForUser(const User& user) {
        return userCarts.at(user.userId); // throws if not found
    }
};
