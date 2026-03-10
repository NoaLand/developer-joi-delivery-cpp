#pragma once

#include "ProductService.h"
#include "UserService.h"
#include "core/Cart.h"
#include "core/User.h"
#include "data/SeedData.h"
#include "dto/AddProductRequest.h"

#include <string>
#include <unordered_map>

namespace tw::delivery::service {
    class CartService {
        std::unordered_map<std::string, Cart> userCarts{SeedData::cartForUsers};
        UserService userService;
        ProductService productService;

    public:
        CartService(UserService uService, ProductService pService);
        CartService(std::unordered_map<std::string, Cart>& carts, UserService& uService, ProductService& pService);

        Cart addProductToCartForUser(const AddProductRequest& addProductRequest);
        Cart getCartForUser(std::string_view userId);

    private:
        Cart& fetchCartForUser(const User& user);
    };
}
