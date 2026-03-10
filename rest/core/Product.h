#pragma once

#include <string>

struct  Product {
    std::string productId;
    std::string productName;
    float mrp;

    virtual ~Product() = default;

    bool operator<(const Product& other) const {
        return this->mrp < other.mrp;
    }
};
