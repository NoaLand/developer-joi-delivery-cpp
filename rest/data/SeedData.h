#pragma once
#include "core/Cart.h"
#include "core/GroceryProduct.h"
#include "core/GroceryStore.h"
#include "core/User.h"
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

class SeedData {
public:
    static int getRandomNumberUsingNextInt(int min, int max) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(min, max - 1);
        return dist(gen);
    }

    static std::shared_ptr<GroceryProduct> createGroceryProduct(const std::string& productName, const std::string& productId, const std::shared_ptr<GroceryStore>& store) {
        auto grocery = std::make_shared<GroceryProduct>();
        grocery->productId = productId;
        grocery->productName = productName;
        grocery->mrp = 10.5f;
        grocery->weight = 500.0f;
        grocery->storeId = store->outletId;
        grocery->threshold = 10;
        grocery->availableStock = 30;

        return grocery;
    }

    inline static auto store101 = std::make_shared<GroceryStore>("Fresh Picks", "Fresh Picks Store", "store101");
    inline static auto store102 = std::make_shared<GroceryStore>("Natural Choice", "Natural Choice Store", "store102");

    inline static std::unordered_map<std::string, Cart> cartForUsers {
        {"user101", {"cart101", "user101", store101}},
        {"user102", {"cart102", "user102", store101}}
    };;

    inline static User user101 {
        "user101", "John", "Doe", "John.Doe@gmail.com",
        std::to_string(getRandomNumberUsingNextInt(100000000, 900000000))
    };
    inline static User user102 {
        "user102", "Rachel", "Zane", "Rachel.Zane@gmail.com",
        std::to_string(getRandomNumberUsingNextInt(100000000, 900000000))
    };
    static std::vector<std::shared_ptr<Product>> products;
    inline static std::vector<User> users {user101, user102};

};

std::vector<std::shared_ptr<Product>> SeedData::products = {
    SeedData::createGroceryProduct("Wheat Bread", "product101",
                                   SeedData::store101),
    SeedData::createGroceryProduct("Spinach", "product102", SeedData::store101),
    SeedData::createGroceryProduct("Crackers", "product103",
                                   SeedData::store101)
};