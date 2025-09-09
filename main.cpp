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

void showCartProductInfo() {
    // Placeholder function to show existing product info in user's cart
    std::cout << "Displaying existing product info in user's cart...\n";
    // Actual implementation would retrieve and display cart product info

    // add one more CLI to ask for details like userId, outletId, productId
    std::string userId, outletId, productId;
    std::cout << "Enter User ID: ";
    std::cin >> userId;
    std::cout << "Enter Outlet ID: ";
    std::cin >> outletId;
    std::cout << "Enter Product ID: ";
    std::cin >> productId;
    std::cout << "User ID: " << userId << ", Outlet ID: " << outletId << ", Product ID: " << productId << "\n";
}


void viewCartInfo() {
    // Placeholder function to view cart of a specific user
    std::cout << "Viewing cart of a specific user...\n";
    // Actual implementation would retrieve and display the user's cart info

    // add one more CLI to ask for details like userId
    std::string userId;
    std::cout << "Enter User ID: ";
    std::cin >> userId;
    std::cout << "User ID: " << userId << "\n";
    
    auto cart = cart_service.getCartForUser(userId);
    std::cout << "-- view query - user id " << userId << "\n";

    // http::response<http::string_body> res{http::status::ok, req.version()};
    // res.set(http::field::content_type, "application/json");
    // res.keep_alive(req.keep_alive());

    auto response_body = detail::to_json(cart);
    nlohmann::json j;
    j["view"] = response_body;

    // add code here to pretty print the json object
    std::cout << j.dump(4) << std::endl; // pretty print with 4 spaces indentation

}

int main(int argc, char *argv[]) {
// add CLI code to accept below input from user : 
// 1. add quantity to existing product in user's cart
// 2. Calculate and Provide Inventory Health Report for Store Owners
// 3. Implement Grocery Product Search by Name
// 4. Create Order
// 5. Expanding Grocery Delivery App to Support Food Delivery
// 6.Advanced Discounts, Dynamic Pricing

// can you help me with the code for above CLI options
    std::cout << "Grocery Store Management CLI\n";
    std::cout <<" 0. Show the existing product info in user's cart\n";
    std::cout << "1. Add quantity to existing product in user's cart\n";
    std::cout << "2. Calculate and Provide Inventory Health Report for Store Owners\n";
    std::cout << "3. Implement Grocery Product Search by Name\n";
    std::cout << "4. Create Order\n";
    std::cout << "5. Expanding Grocery Delivery App to Support Food Delivery\n";
    std::cout << "6. Advanced Discounts, Dynamic Pricing\n";
    std::cout << "7. To View Cart of a specific user\n";
    std::cout << "8. Exit\n";
    std::cout << "Select an option (1-8): ";

    int option;
    std::cin >> option;

    switch(option) {

        case 1:
            std::cout << "Adding quantity to existing product in user's cart...\n";
            // Call function to add quantity to product in cart
            break;
        case 2:
            std::cout << "Calculating Inventory Health Report...\n";
            // Call function to calculate inventory health report
            break;
        case 3:
            std::cout << "Searching for grocery products by name...\n";
            // Call function to search products by name
            break;
        case 4:
            std::cout << "Creating order...\n";
            // Call function to create order
            break;
        case 5:
            std::cout << "Expanding app to support food delivery...\n";
            // Call function to expand app features
            break;
        case 6:
            std::cout << "Implementing advanced discounts and dynamic pricing...\n";
            // Call function for discounts and pricing
            break;
        case 7:
            std::cout << "Viewing cart of a specific user...\n";
            viewCartInfo();
            break;
    // std::cout << "7. To View Cart of a specific user\n";"
        default:
            std::cout << "Invalid option selected.\n";
            break;
    }


  return EXIT_SUCCESS;
}