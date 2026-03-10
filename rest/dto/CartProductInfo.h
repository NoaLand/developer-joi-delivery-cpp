#pragma once

#include <memory>

#include "core/Cart.h"
#include "core/Product.h"

struct CartProductInfo {
    Cart cart;
    std::shared_ptr<Product> product;
    float sellingPrice;
};
