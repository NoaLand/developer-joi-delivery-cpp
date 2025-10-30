#include <iostream>

#include "rest/dto/AddProductRequest.h"
#include "rest/dto/CartProductInfo.h"

#include "rest/service/CartService.h"
#include "rest/service/ProductService.h"
#include "rest/service/UserService.h"

#include "rest/util/JsonUtil.hpp"

UserService user_service{};
ProductService product_service{};
CartService cart_service{user_service, product_service};

void addProductToCartForUser(){
    std::cout << "Adding product to Cart for a user\n";
    std::string userId, outletId, productId;
    std::cout << "Enter User ID: ";
    std::cin >> userId;
    std::cout << "Enter Product ID: ";
    std::cin >> productId;
    std::cout << "Enter Outlet ID: ";
    std::cin >> outletId;

    AddProductRequest addProductRequest;
    addProductRequest.setUserId(userId);
    addProductRequest.setOutletId(outletId);
    addProductRequest.setProductId(productId);

    auto cartProductInfo = cart_service.addProductToCartForUser(addProductRequest);
    auto response_body = detail::to_json(cartProductInfo);
    nlohmann::json j;
    j["add"] = response_body;
    // add code here to pretty print the json object
    std::cout << j.dump(4) << std::endl; // pretty print with 4 spaces indentation

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

    auto response_body = detail::to_json(cart);
    nlohmann::json j;
    j["view"] = response_body;

    // add code here to pretty print the json object
    std::cout << j.dump(4) << std::endl; // pretty print with 4 spaces indentation

}

int main(int argc, char *argv[]) {
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
  return EXIT_SUCCESS;
}