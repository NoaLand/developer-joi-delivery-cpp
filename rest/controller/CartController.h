#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "../domain/Outlet.h"

#include <boost/beast/http.hpp>
#include <nlohmann/json.hpp>

#include "../dto/AddProductRequest.h"
#include "../dto/CartProductInfo.h"

#include "../service/CartService.h"
namespace http = boost::beast::http;

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
  std::vector<Product> products = cart.getProducts();
  std::transform(products.begin(), products.end(),
                 std::back_inserter(product_json_array),
                 [](const Product &p) { return detail::to_json(p); });

  return nlohmann::json{{"cartId", cart.getCartId()},
                        {"outlet", detail::to_json(cart.getOutlet())},
                        {"products", product_json_array}};
}
auto to_json(const CartProductInfo &info) {
  auto cart_json = to_json(info.getCart());
  auto product_json = to_json(info.getProduct());
  return nlohmann::json{{"cart", cart_json},
                        {"proudct", product_json},
                        {"sellingPrice", info.getSellingPrice()}};
}
} // namespace detail

class CartController {
public:
  CartController(const CartService &cart_service)
      : cart_service_(cart_service) {}

  http::response<http::string_body>
  AddProductToCart(const http::request<http::string_body> &req,
                   const std::vector<std::string> &queries) {
    auto body = nlohmann::json::parse(req.body());

    AddProductRequest add_product_request;

    add_product_request.setUserId(body["userId"]);
    add_product_request.setOutletId(body["outletId"]);
    add_product_request.setProductId(body["productId"]);

    CartProductInfo cart_product_info =
        cart_service_.addProductToCartForUser(add_product_request);

    http::response<http::string_body> res{http::status::ok, req.version()};
    res.set(http::field::content_type, "application/json");
    res.keep_alive(req.keep_alive());

    auto response_body = detail::to_json(cart_product_info);
    nlohmann::json j;
    // res.body() = response_body.dump();
    j["product"] = response_body;
    res.body() = j.dump();
    res.prepare_payload();
    return res;
  }

  http::response<http::string_body>
  ViewCart(const http::request<http::string_body> &req,
           const std::vector<std::string> &queries) {
    auto userId = queries[0];
    auto cart = cart_service_.getCartForUser(userId);
    std::cout << "-- view query - user id " << userId << "\n";

    http::response<http::string_body> res{http::status::ok, req.version()};
    res.set(http::field::content_type, "application/json");
    res.keep_alive(req.keep_alive());

    auto response_body = detail::to_json(cart);
    nlohmann::json j;
    j["view"] = response_body;
    res.body() = j.dump();
    res.prepare_payload();
    return res;
  }

private:
  CartService cart_service_;
};
