#pragma once

#include <string>

struct AddProductRequest {
    std::string userId;
    std::string outletId;
    std::string productId;
};

