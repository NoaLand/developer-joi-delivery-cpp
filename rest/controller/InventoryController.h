#pragma once

#include <string>

#include <boost/beast/http.hpp>
#include <nlohmann/json.hpp>

namespace http = boost::beast::http;

class InventoryController {
public:
  InventoryController() {}

  http::response<http::string_body>
  fetchStoreInventoryHealth(const http::request<http::string_body> &req,
                            const std::vector<std::string> &queries) {
    http::response<http::string_body> res{http::status::ok, req.version()};
    res.set(http::field::content_type, "application/json");
    res.keep_alive(req.keep_alive());
    res.prepare_payload();
    return res;
  }
};
