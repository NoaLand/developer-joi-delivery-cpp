#pragma once

#include <optional>
#include <string>
#include <vector>

#include "core/GroceryProduct.h"
#include "data/SeedData.h"

class ProductService {
    std::vector<GroceryProduct> products{SeedData::groceryProducts};

public:
    ProductService() = default;
    explicit ProductService(std::vector<GroceryProduct> productsRef) : products{std::move(productsRef)} {}

    // Return optional to handle "not found" instead of null
    [[nodiscard]] std::optional<GroceryProduct> getProduct(std::string_view productId, std::string_view outletId) const {
        for (const auto& groceryProduct : products) {
            if (groceryProduct.productId == productId
                && groceryProduct.storeId == outletId) {
                return groceryProduct;
            }
        }
        return std::nullopt; // No match found
    }
};
