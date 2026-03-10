#include <iostream>

#include "dto/AddProductRequest.h"

#include "tw/delivery/service/CartService.h"
#include "tw/delivery/service/ProductService.h"
#include "tw/delivery/service/UserService.h"

#include "infra/adapters/JsonAdapter.hpp"

tw::delivery::service::UserService user_service{};
tw::delivery::service::ProductService product_service{};
tw::delivery::service::CartService cart_service{user_service, product_service};

void addProductToCartForUser(){
    std::cout << "Adding product to Cart for a user\n";
    std::string userId, outletId, productId;
    std::cout << "Enter User ID: ";
    std::cin >> userId;
    std::cout << "Enter Product ID: ";
    std::cin >> productId;
    std::cout << "Enter Outlet ID: ";
    std::cin >> outletId;

    const auto cart = cart_service.addProductToCartForUser({userId, outletId, productId});
    std::cout << tw::delivery::infra::adapter::json::serialize(cart) << std::endl;
}

// Placeholder function to view cart of a specific user
void viewCartInfo() {
    std::cout << "Viewing cart of a specific user...\n";
    std::string userId;
    std::cout << "Enter User ID: ";
    std::cin >> userId;
    std::cout << "User ID: " << userId << "\n";
    
    auto cart = cart_service.getCartForUser(userId);

    std::cout << "-- view query - user id " << userId << "\n";
    std::cout << tw::delivery::infra::adapter::json::serialize(cart) << std::endl;
}

int main() {
    std::cout << "Grocery Store Management CLI\n";
    std::cout << "1. Add product to Cart for a user\n";
    std::cout << "2. To View Cart of a specific user\n";
    std::cout << "3. Exit\n";
    std::cout << "Select an option (1-3): ";

    int option;
    std::cin >> option;
    switch(option) {
        case 1:
            addProductToCartForUser();
            break;
        case 2:
            viewCartInfo();
            break;
        case 3:
            std::cout << "Exiting the application...\n";
            break;
        default:
            std::cout << "Invalid option selected.\n";
            break;
    }

    return 0;
}