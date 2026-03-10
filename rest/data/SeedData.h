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
    // Static data members
    static std::unordered_map<std::string, Cart> cartForUsers;
    static std::shared_ptr<GroceryStore> store101;
    static std::shared_ptr<GroceryStore> store102;
    static User user101;
    static User user102;
    static std::vector<std::shared_ptr<Product>> products;
    static std::vector<User> users;

    // Factory methods
    static Cart createCartForUser(const std::string& userId,
                                  const std::string& firstName,
                                  const std::string& lastName,
                                  const std::string& cartId);

    static std::shared_ptr<GroceryStore> createStore(const std::string& outletName,
                                    const std::string& description,
                                    const std::string& storeId);

    static User createUser(const std::string& userId,
                           const std::string& firstName,
                           const std::string& lastName);

    static int getRandomNumberUsingNextInt(int min, int max);

    // private:
    static std::shared_ptr<GroceryProduct> createGroceryProduct(const std::string& productName,
                                                                const std::string& productId,
                                                                const std::shared_ptr<GroceryStore>& store);
};

// Initialize static members
std::shared_ptr<GroceryStore> SeedData::store101 =
    SeedData::createStore("Fresh Picks", "Fresh Picks Store", "store101");
std::shared_ptr<GroceryStore> SeedData::store102 =
    SeedData::createStore("Natural Choice", "Natural Choice Store", "store102");
User SeedData::user101 = SeedData::createUser("user101", "John", "Doe");
User SeedData::user102 = SeedData::createUser("user102", "Rachel", "Zane");

std::unordered_map<std::string, Cart> SeedData::cartForUsers = {
    {
        "user101",
        SeedData::createCartForUser("user101", "John", "Doe", "cart101")
    },
    {
        "user102",
        SeedData::createCartForUser("user102", "Rachel", "Zane", "cart102")
    }
};

std::vector<std::shared_ptr<Product>> SeedData::products = {
    SeedData::createGroceryProduct("Wheat Bread", "product101",
                                   SeedData::store101),
    SeedData::createGroceryProduct("Spinach", "product102", SeedData::store101),
    SeedData::createGroceryProduct("Crackers", "product103",
                                   SeedData::store101)
};

std::vector<User> SeedData::users = {SeedData::user101, SeedData::user102};

// Factory method implementations
inline Cart SeedData::createCartForUser(const std::string& userId,
                                        const std::string& firstName,
                                        const std::string& lastName,
                                        const std::string& cartId) {
    return {cartId, userId, store101};
}

inline std::shared_ptr<GroceryStore> SeedData::createStore(const std::string& outletName,
                                          const std::string& description,
                                          const std::string& storeId) {
    return std::make_shared<GroceryStore>(outletName, description, storeId);
}

inline User SeedData::createUser(const std::string& userId,
                                 const std::string& firstName,
                                 const std::string& lastName) {
    return {
        userId, firstName, lastName, firstName + "." + lastName + "@gmail.com",
        std::to_string(getRandomNumberUsingNextInt(100000000, 900000000))
    };
}

inline int SeedData::getRandomNumberUsingNextInt(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max - 1);
    return dist(gen);
}

inline std::shared_ptr<GroceryProduct> SeedData::createGroceryProduct(const std::string& productName,
                                                                      const std::string& productId,
                                                                      const std::shared_ptr<GroceryStore>& store) {
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
