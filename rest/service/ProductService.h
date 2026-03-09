#pragma once
#include "core/GroceryProduct.h"
#include "data/SeedData.h"
#include <optional>
#include <string>
#include <vector>

class ProductService {
public:
  ProductService(std::vector<GroceryProduct> &productsRef)
      : products(productsRef) {}
  ProductService() {}

  // Return optional to handle "not found" instead of null
  std::optional<GroceryProduct> getProduct(const std::string &productId,
                                           const std::string &outletId) {
    for (const auto &groceryProduct : products) {
      if (groceryProduct.productId == productId &&
          groceryProduct.storeId == outletId) {
        return groceryProduct;
      }
    }
    return std::nullopt; // No match found
  }

private:
  std::vector<GroceryProduct> products{SeedData::groceryProducts};
};
