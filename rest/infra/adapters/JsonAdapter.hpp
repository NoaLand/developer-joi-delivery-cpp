#pragma once

#include <nlohmann/json.hpp>
#include <memory>

#include "core/Product.h"
#include "core/GroceryProduct.h"
#include "core/Outlet.h"
#include "core/GroceryStore.h"
#include "core/Cart.h"

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Product, productId, productName, mrp)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(GroceryProduct,
    productId, productName, mrp,
    sellingPrice, weight, expiryDate, threshold, availableStock, discount, storeId)

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Outlet, name, description, outletId)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(GroceryStore,
    name, description, outletId,
    inventory)

namespace nlohmann {
    template <typename T>
    struct adl_serializer<std::shared_ptr<T>> {
        static void to_json(json& j, const std::shared_ptr<T>& ptr) {
            if (ptr) {
                j = *ptr;
            } else {
                j = nullptr;
            }
        }

        static void from_json(const json& j, std::shared_ptr<T>& ptr) {
            if (j.is_null()) {
                ptr = nullptr;
            } else {
                ptr = std::make_shared<T>(j.get<T>());
            }
        }
    };

    template <>
    struct adl_serializer<std::shared_ptr<Product>> {
        static void to_json(json& j, const std::shared_ptr<Product>& ptr) {
            if (!ptr) {
                j = nullptr;
                return;
            }

            if (auto gp = std::dynamic_pointer_cast<GroceryProduct>(ptr)) {
                j = *gp;
            } else {
                j = *ptr;
            }
        }

        static void from_json(const json& j, std::shared_ptr<Product>& ptr) {
            if (j.is_null()) {
                ptr = nullptr;
                return;
            }

            if (j.contains("sellingPrice")) {
                ptr = std::make_shared<GroceryProduct>(j.get<GroceryProduct>());
            } else {
                ptr = std::make_shared<Product>(j.get<Product>());
            }
        }
    };

    template <>
    struct adl_serializer<std::shared_ptr<Outlet>> {
        static void to_json(json& j, const std::shared_ptr<Outlet>& ptr) {
            if (!ptr) {
                j = nullptr;
                return;
            }

            if (auto gs = std::dynamic_pointer_cast<GroceryStore>(ptr)) {
                j = *gs;
            } else {
                j = *ptr;
            }
        }

        static void from_json(const json& j, std::shared_ptr<Outlet>& ptr) {
            if (j.is_null()) {
                ptr = nullptr;
                return;
            }

            if (j.contains("inventory")) {
                ptr = std::make_shared<GroceryStore>(j.get<GroceryStore>());
            } else {
                ptr = std::make_shared<Outlet>(j.get<Outlet>());
            }
        }
    };
}

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Cart, cartId, userId, outlet, products)

namespace tw::delivery::infra::adapter::json {
    template <typename T>
    std::string serialize(const T& obj, int index = 4) {
        nlohmann::json j = obj;
        return j.dump(index);
    }
}
