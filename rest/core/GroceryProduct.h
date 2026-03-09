#pragma once
#include "Product.h"
// #include "GroceryStore.h"

#include <string>
using namespace std;

class GroceryProduct : public Product {
private:
  float sellingPrice;
  float weight;
  int expiryDate;
  int threshold;
  int availableStock;
  float discount;
  // GroceryStore store;
  string storeId;

public:
  // Getters
  const float &getSellingPrice() const { return sellingPrice; }
  const float &getWeight() const { return weight; }
  const int &getExpiryDate() const { return expiryDate; }
  const int &getThreshold() const { return threshold; }
  const int &getAvailableStock() const { return availableStock; }
  const float &getDiscount() const { return discount; }
  const string &getStoreId() const { return storeId; }
  // const GroceryStory& getStore() const { return store; }

  // Setters
  void setSellingPrice(const float &price) { sellingPrice = price; }
  void setWeight(const float &wt) { weight = wt; }
  void setExpiryDate(const int &dt) { expiryDate = dt; }
  void setThreshold(const int &th) { threshold = th; }
  void setAvailableStock(const int &stockCount) { availableStock = stockCount; }
  void setDiscount(const float &disc) { discount = disc; }
  void setStoreId(const string &sid) { storeId = sid; }
};
