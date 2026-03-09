#pragma once

#include "Product.h"

#include <string>

struct GroceryProduct : Product {
  float sellingPrice;
  float weight;
  int expiryDate;
  int threshold;
  int availableStock;
  float discount;
  std::string storeId;
};
