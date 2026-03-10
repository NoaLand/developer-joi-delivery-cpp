#pragma once

#include "core/Cart.h"
#include "core/GroceryProduct.h"
#include "core/GroceryStore.h"
#include "core/User.h"

#include <random>
#include <string>
#include <unordered_map>
#include <vector>

namespace tw::delivery::data {
    class SeedData {
    public:
        static int getRandomNumberUsingNextInt(int min, int max) {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            std::uniform_int_distribution<> dist(min, max - 1);
            return dist(gen);
        }

        static core::Cart createCartForUser(std::string userId,
                                            std::string_view firstName,
                                            std::string_view lastName,
                                            std::string cartId) {
            return {std::move(cartId), std::move(userId), store101};
        }

        static std::shared_ptr<core::GroceryProduct> createGroceryProduct(std::string productName, std::string productId, const std::shared_ptr<core::GroceryStore>& store) {
            auto grocery = std::make_shared<core::GroceryProduct>();
            grocery->productId = std::move(productId);
            grocery->productName = std::move(productName);
            grocery->mrp = 10.5f;
            grocery->weight = 500.0f;
            grocery->storeId = store->outletId;
            grocery->threshold = 10;
            grocery->availableStock = 30;

            return grocery;
        }

        inline static auto store101 = std::make_shared<core::GroceryStore>("Fresh Picks", "Fresh Picks Store", "store101");
        inline static auto store102 = std::make_shared<core::GroceryStore>("Natural Choice", "Natural Choice Store", "store102");

        inline static std::unordered_map<std::string, core::Cart> cartForUsers {
            {"user101", createCartForUser("user101", "John", "Doe", "cart101")},
            {"user102", createCartForUser("user102", "Rachel", "Zane", "cart102")}
        };

        inline static std::vector<std::shared_ptr<core::Product>> products = {
            createGroceryProduct("Wheat Bread", "product101", store101),
            createGroceryProduct("Spinach", "product102", store101),
            createGroceryProduct("Crackers", "product103", store101)
        };

        inline static core::User user101 {
            "user101", "John", "Doe", "John.Doe@gmail.com",
            std::to_string(getRandomNumberUsingNextInt(100000000, 900000000))
        };
        inline static core::User user102 {
            "user102", "Rachel", "Zane", "Rachel.Zane@gmail.com",
            std::to_string(getRandomNumberUsingNextInt(100000000, 900000000))
        };
        inline static std::vector<core::User> users {user101, user102};
    };
}