#include "tw/delivery/service/ProductService.h"

namespace tw::delivery::service {
    ProductService::ProductService(std::vector<std::shared_ptr<core::Product>> productsRef) : products{std::move(productsRef)} {}

    [[nodiscard]] std::shared_ptr<core::Product> ProductService::getProduct(std::string_view productId, std::string_view outletId) const {
        for (const auto& product : products) {
            if (product->productId == productId) {
                if (auto grocery = std::dynamic_pointer_cast<core::GroceryProduct>(product)) {
                    if (grocery->storeId == outletId) {
                        return product;
                    }
                }
            }
        }
        return nullptr; // No match found
    }
}
