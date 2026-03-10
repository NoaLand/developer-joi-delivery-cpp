#pragma once

#include <string>
#include <utility>

struct Product {
    std::string productId;
    std::string productName;
    float mrp{};

    Product() = default;
    Product(std::string productId, std::string productName, const float mrp)
        : productId{std::move(productId)}, productName{std::move(productName)}, mrp{mrp} {}

    virtual ~Product() = default;

    bool operator<(const Product& other) const {
        return this->mrp < other.mrp;
    }
};
