#include "tw/delivery/service/CartService.h"
#include "tw/delivery/service/ProductService.h"
#include "tw/delivery/service/UserService.h"

#include "core/Cart.h"
#include "core/Product.h"
#include "dto/AddProductRequest.h"
#include <gtest/gtest.h>

#include <vector>

class MockCartServiceTest : public ::testing::Test {
protected:
    void SetUp() override {
        const auto store1 = std::make_shared<GroceryStore>("Fresh Mart", "Fresh Mart Store", "store1");
        const auto product1 = SeedData::createGroceryProduct("Apple", "product1",  store1);
        product1->sellingPrice = 100.0;

        products.push_back(product1);

        User user1{"user1", "John", "Doe"};
        users.push_back(user1);

        User user2{"user2", "Rachel", "Zane"};
        users.push_back(user2);
        
        // Initialize UserService and ProductService
        userService = std::make_unique<tw::delivery::service::UserService>(users);
        productService = std::make_unique<tw::delivery::service::ProductService>(products);
        cartService = std::make_unique<tw::delivery::service::CartService>(cartForUsers, *userService, *productService);
    }

    void TearDown() override {}

    std::unique_ptr<tw::delivery::service::UserService> userService;
    std::unique_ptr<tw::delivery::service::ProductService> productService;
    std::unique_ptr<tw::delivery::service::CartService> cartService;

    std::vector<std::shared_ptr<Product>> products;
    std::vector<User> users;

    std::unordered_map<std::string, Cart> cartForUsers = {
        {"user1", {"cart101", "user1", SeedData::store101}},
        {"user2", {"cart102", "user2", SeedData::store101}}
    };
};

TEST_F(MockCartServiceTest, AddProductToCartForUser_ValidInput) {

    AddProductRequest request{users.at(0).userId, "store1", products.at(0)->productId};

    Cart cart = cartService->addProductToCartForUser(request);

    std::shared_ptr<Product> product = cart.products.at(0);
    EXPECT_EQ(product->productId, "product1");
    EXPECT_EQ(std::dynamic_pointer_cast<GroceryProduct>(product)->sellingPrice, 100.0); // Assuming selling price is 100.0
    EXPECT_EQ(cart.products.size(), 1);
}

TEST_F(MockCartServiceTest, GetCartForUser_ValidUser) {
    Cart cart = cartService->getCartForUser("user1");

    EXPECT_EQ(cart.cartId, "cart101");
    EXPECT_EQ(cart.userId, "user1");
    EXPECT_EQ(cart.products.size(), 0); // Initially, the cart should be empty
}

TEST_F(MockCartServiceTest, GetCartForUser_InvalidUser) {
    EXPECT_THROW({
        cartService->getCartForUser("invalid_user");
    }, std::bad_optional_access); // Expecting out_of_range exception for invalid user
}