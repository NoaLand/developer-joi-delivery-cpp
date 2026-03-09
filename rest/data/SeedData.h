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
  static GroceryStore store101;
  static GroceryStore store102;
  static User user101;
  static User user102;
  static std::vector<GroceryProduct> groceryProducts;
  static std::vector<User> users;

  // Factory methods
  static Cart createCartForUser(const std::string &userId,
                                const std::string &firstName,
                                const std::string &lastName,
                                const std::string &cartId);

  static GroceryStore createStore(const std::string &outletName,
                                  const std::string &description,
                                  const std::string &storeId);

  static User createUser(const std::string &userId,
                         const std::string &firstName,
                         const std::string &lastName);

  static int getRandomNumberUsingNextInt(int min, int max);

// private:
  static GroceryProduct createGroceryProduct(const std::string &productName,
                                             const std::string &productId,
                                             const GroceryStore &store);
};

// Initialize static members
GroceryStore SeedData::store101 =
    SeedData::createStore("Fresh Picks", "Fresh Picks Store", "store101");
GroceryStore SeedData::store102 =
    SeedData::createStore("Natural Choice", "Natural Choice Store", "store102");
User SeedData::user101 = SeedData::createUser("user101", "John", "Doe");
User SeedData::user102 = SeedData::createUser("user102", "Rachel", "Zane");

std::unordered_map<std::string, Cart> SeedData::cartForUsers = {
    {"user101",
     SeedData::createCartForUser("user101", "John", "Doe", "cart101")},
    {"user102",
     SeedData::createCartForUser("user102", "Rachel", "Zane", "cart102")}};

std::vector<GroceryProduct> SeedData::groceryProducts = {
    SeedData::createGroceryProduct("Wheat Bread", "product101",
                                   SeedData::store101),
    SeedData::createGroceryProduct("Spinach", "product102", SeedData::store101),
    SeedData::createGroceryProduct("Crackers", "product103",
                                   SeedData::store101)};

std::vector<User> SeedData::users = {SeedData::user101, SeedData::user102};

// Factory method implementations
Cart SeedData::createCartForUser(const std::string &userId,
                                 const std::string &firstName,
                                 const std::string &lastName,
                                 const std::string &cartId) {
    // TODO: remove make_shared later
    return {cartId, userId, std::make_shared<GroceryStore>(store101)};
}

GroceryStore SeedData::createStore(const std::string &outletName,
                                   const std::string &description,
                                   const std::string &storeId) {
  return GroceryStore(outletName, description, storeId);
}

User SeedData::createUser(const std::string &userId,
                          const std::string &firstName,
                          const std::string &lastName) {
  User user;
  user.setUserId(userId);
  user.setFirstName(firstName);
  user.setLastName(lastName);
  user.setEmail(firstName + "." + lastName + "@gmail.com");
  user.setPhoneNumber(std::to_string(getRandomNumberUsingNextInt(100000000, 900000000)));

  return user;
  // return User(
  //     userId, firstName, lastName, firstName + "." + lastName + "@gmail.com",
  //     std::to_string(getRandomNumberUsingNextInt(100000000, 900000000)));
}

int SeedData::getRandomNumberUsingNextInt(int min, int max) {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(min, max - 1);
  return dist(gen);
}

GroceryProduct SeedData::createGroceryProduct(const std::string &productName,
                                              const std::string &productId,
                                              const GroceryStore &store) {
  GroceryProduct grocery;
  grocery.productId = productId;
  grocery.productName = productName;
  grocery.mrp = 10.5f;
  grocery.setWeight(500.0f);
  grocery.setStoreId(store.getOutletId());
  grocery.setThreshold(10);
  grocery.setAvailableStock(30);

  return grocery;

  // return GroceryProduct(productId, productName, 10.5f, 500.0f, store, 10, 30);
}
