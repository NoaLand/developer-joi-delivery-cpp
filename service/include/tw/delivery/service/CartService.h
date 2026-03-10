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
        std::unordered_map<std::string, core::Cart> userCarts{data::SeedData::cartForUsers};
        UserService userService;
        ProductService productService;

    public:
        CartService(UserService uService, ProductService pService);
        CartService(std::unordered_map<std::string, core::Cart>& carts, UserService& uService, ProductService& pService);

        core::Cart addProductToCartForUser(const dto::AddProductRequest& addProductRequest);
        core::Cart getCartForUser(std::string_view userId);

    private:
        core::Cart& fetchCartForUser(const core::User& user);
    };
}
