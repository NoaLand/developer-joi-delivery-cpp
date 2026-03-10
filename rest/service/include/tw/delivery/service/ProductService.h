#pragma once

#include <string>
#include <vector>

#include "core/Product.h"
#include "data/SeedData.h"

namespace tw::delivery::service {
    class ProductService {
        std::vector<std::shared_ptr<core::Product>> products{data::SeedData::products};

    public:
        ProductService() = default;
        explicit ProductService(std::vector<std::shared_ptr<core::Product>> productsRef);

        [[nodiscard]] std::shared_ptr<core::Product> getProduct(std::string_view productId, std::string_view outletId) const;
    };
}

