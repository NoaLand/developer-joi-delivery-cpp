#pragma once

#include <string>

namespace tw::delivery::dto {
    struct AddProductRequest {
        std::string userId;
        std::string outletId;
        std::string productId;
    };
}
