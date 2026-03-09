#pragma once

#include <algorithm>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

#include "core/Outlet.h"
#include "dto/CartProductInfo.h"

namespace detail {
auto to_json(Product product) {
  return nlohmann::json{{"productId", product.getProductId()},
                        {"productName", product.getProductName()},
                        {"mrp", product.getMrp()}};
}

auto to_json(const Outlet &store) {
  return nlohmann::json{{"outletId", store.getOutletId()},
                        {"outletName", store.getName()}};
}

auto to_json(const Cart &cart) {
  auto product_json_array = nlohmann::json::array();
  std::vector<std::shared_ptr<Product>> products = cart.products;
  std::transform(products.begin(), products.end(),
                 std::back_inserter(product_json_array),
                 [](const auto& p) { return detail::to_json(*p); });

  return nlohmann::json{{"cartId", cart.cartId},
                        {"outlet", detail::to_json(*cart.outlet)},
                        {"products", product_json_array}};
}
auto to_json(const CartProductInfo &info) {
  auto cart_json = to_json(info.getCart());
  auto product_json = to_json(info.getProduct());
  return nlohmann::json{{"cart", cart_json},
                        {"product", product_json},
                        {"sellingPrice", info.getSellingPrice()}};
}
} // namespace detail
