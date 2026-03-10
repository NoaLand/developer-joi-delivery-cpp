#include <iostream>
#include <unordered_map>
#include <functional>

#include "tw/delivery/dto/AddProductRequest.h"

#include "tw/delivery/service/CartService.h"
#include "tw/delivery/service/ProductService.h"
#include "tw/delivery/service/UserService.h"

#include "tw/delivery/infra/adapters/JsonAdapter.h"

void addProductToCartForUser(tw::delivery::service::CartService& cart_service){
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
void viewCartInfo(tw::delivery::service::CartService& cart_service) {
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
    std::unordered_map<int, std::function<void(tw::delivery::service::CartService&)>> menu_routes {
        {1, addProductToCartForUser},
        {2, viewCartInfo},
        {3, [](auto& _) { std::cout << "Exiting the application...\n"; }}
    };


    std::cout << "Grocery Store Management CLI\n";
    std::cout << "1. Add product to Cart for a user\n";
    std::cout << "2. To View Cart of a specific user\n";
    std::cout << "3. Exit\n";
    std::cout << "Select an option (1-3): ";

    if (int option; std::cin >> option && menu_routes.count(option)) {
        tw::delivery::service::CartService cart_service{{}, {}};
        menu_routes[option](cart_service);
    } else {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid Input!\n";
    }

    return 0;
}