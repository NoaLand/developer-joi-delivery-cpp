#pragma once
#include <string>

class AddProductRequest {
private:
    std::string userId;
    std::string outletId;
    std::string productId;

public:
    // Getters
    const std::string& getUserId() const { return userId; }
    const std::string& getOutletId() const { return outletId; }
    const std::string& getProductId() const { return productId; }

    // Setters
    void setUserId(const std::string& id) { userId = id; }
    void setOutletId(const std::string& id) { outletId = id; }
    void setProductId(const std::string& id) { productId = id; }
};

