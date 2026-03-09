#include "service/CartService.h"
#include "service/ProductService.h"
#include "service/UserService.h"

#include "core/Cart.h"
#include "core/Product.h"
#include "dto/AddProductRequest.h"
#include "dto/CartProductInfo.h"
#include <gtest/gtest.h>

#include <vector>

// using namespace detail;

class MockCartServiceTest : public ::testing::Test {
protected:
    void SetUp() override {
        GroceryStore store1{"Fresh Mart", "Fresh Mart Store", "store1"};
        GroceryProduct product1 = SeedData::createGroceryProduct("Apple", "product1",  store1);
        product1.sellingPrice = 100.0;

        products.push_back(product1);

        User user1;
        user1.setUserId("user1");
        user1.setFirstName("John");
        user1.setLastName("Doe");
        users.push_back(user1);

        User user2;
        user2.setUserId("user2");
        user2.setFirstName("Rachel");
        user2.setLastName("Zane");
        users.push_back(user2);
        
        // Initialize UserService and ProductService
        userService = std::make_unique<UserService>(users);
        productService = std::make_unique<ProductService>(products);
        cartService = std::make_unique<CartService>(cartForUsers, *userService, *productService);
    }
    void TearDown() override {
        // Cleanup if necessary
        products.clear();
    }
    std::unique_ptr<UserService> userService;   
    std::unique_ptr<ProductService> productService;
    std::unique_ptr<CartService> cartService;

    std::vector<GroceryProduct> products;// = {product};
    std::vector<User> users;

    std::unordered_map<std::string, Cart> cartForUsers = {
    {"user1",
     SeedData::createCartForUser("user1", "John", "Doe", "cart101")},
    {"user2",
     SeedData::createCartForUser("user2", "Rachel", "Zane", "cart102")}};
};

TEST_F(MockCartServiceTest, AddProductToCartForUser_ValidInput) {

    AddProductRequest request;
    request.setUserId(users[0].getUserId());
    request.setOutletId("store1");
    request.setProductId(products[0].productId);

    CartProductInfo cartProductInfo = cartService->addProductToCartForUser(request);

    EXPECT_EQ(cartProductInfo.getProduct().productId, "product1");
    EXPECT_EQ(cartProductInfo.getSellingPrice(), 100.0); // Assuming selling price is 100.0
    EXPECT_EQ(cartProductInfo.getCart().products.size(), 1);
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