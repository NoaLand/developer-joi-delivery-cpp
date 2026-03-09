#pragma once

#include <string>

struct  Product {
    std::string productId;
    std::string productName;
    float mrp;

    bool operator<(const Product& other) const {
        return this->mrp < other.mrp;
    }
};
