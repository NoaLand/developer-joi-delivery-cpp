#pragma once

#include "Product.h"

#include <string>

namespace tw::delivery::core {
    struct GroceryProduct : Product {
        float sellingPrice;
        float weight;
        int expiryDate;
        int threshold;
        int availableStock;
        float discount;
        std::string storeId;

        using Product::Product;
    };
}
