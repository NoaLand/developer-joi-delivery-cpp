#include "../../rest/controller/CartController.h"
#include "../../rest/domain/Cart.h"
#include "../../rest/domain/Outlet.h"
#include "../../rest/domain/Product.h"
#include "../../rest/dto/AddProductRequest.h"
#include "../../rest/dto/CartProductInfo.h"
#include <gtest/gtest.h>

#include <vector>

using namespace detail;

// Existing tests
TEST(CartControllerTest, ToJsonEmptyCart) {
  std::vector<Product> products;
  Outlet outlet("Fresh Picks", "Fresh Picks Store", "outletABC");
  Cart cart;
  cart.setCartId("cart123");
  cart.setOutlet(outlet);
  cart.setProducts(products);

  auto json = to_json(cart);
  EXPECT_EQ(json["cartId"], "cart123");
  EXPECT_EQ(json["outlet"]["outletId"], "outletABC");
  EXPECT_TRUE(json["products"].empty());
}

TEST(CartControllerTest, ToJsonWithProducts) {
  std::vector<Product> products;
  Product p1("p1", "Soap", 40.5);
  Product p2("p2", "Shampoo", 120.0);
  products.push_back(p1);
  products.push_back(p2);

  Outlet outlet("Fresh Picks", "Fresh Picks Store", "outlet001");

  Cart cart;

  cart.setCartId("cart001");
  cart.setOutlet(outlet);
  cart.setProducts(products);

  auto json = to_json(cart);
  EXPECT_EQ(json["cartId"], "cart001");
  EXPECT_EQ(json["products"].size(), 2);
  EXPECT_EQ(json["products"][0]["productName"], "Soap");
  EXPECT_EQ(json["products"][1]["mrp"], 120.0);
}

// New comprehensive tests

// Test individual to_json functions
TEST(CartControllerTest, ToJsonProduct) {
  Product product("prod123", "Test Product", 99.99);
  auto json = to_json(product);

  EXPECT_EQ(json["productId"], "prod123");
  EXPECT_EQ(json["productName"], "Test Product");
  EXPECT_NEAR(json["mrp"], 99.99, 0.01);
}

TEST(CartControllerTest, ToJsonProductWithZeroPrice) {
  Product product("prod456", "Free Product", 0.0);
  auto json = to_json(product);

  EXPECT_EQ(json["productId"], "prod456");
  EXPECT_EQ(json["productName"], "Free Product");
  EXPECT_EQ(json["mrp"], 0.0);
}

TEST(CartControllerTest, ToJsonProductWithNegativePrice) {
  Product product("prod789", "Invalid Product", -10.0);
  auto json = to_json(product);

  EXPECT_EQ(json["productId"], "prod789");
  EXPECT_EQ(json["productName"], "Invalid Product");
  EXPECT_EQ(json["mrp"], -10.0);
}

TEST(CartControllerTest, ToJsonOutlet) {
  Outlet outlet("Test Store", "Test Description", "outlet123");
  auto json = to_json(outlet);

  EXPECT_EQ(json["outletId"], "outlet123");
  EXPECT_EQ(json["outletName"], "Test Store");
}

TEST(CartControllerTest, ToJsonOutletWithEmptyStrings) {
  Outlet outlet("", "", "");
  auto json = to_json(outlet);

  EXPECT_EQ(json["outletId"], "");
  EXPECT_EQ(json["outletName"], "");
}

// Test Cart with different states
TEST(CartControllerTest, ToJsonCartWithUserId) {
  std::vector<Product> products;
  Product p1("p1", "Product 1", 25.0);
  products.push_back(p1);

  Outlet outlet("Store", "Description", "outlet1");
  Cart cart;
  cart.setCartId("cart1");
  cart.setUserId("user123");
  cart.setOutlet(outlet);
  cart.setProducts(products);

  auto json = to_json(cart);
  EXPECT_EQ(json["cartId"], "cart1");
  EXPECT_EQ(json["outlet"]["outletId"], "outlet1");
  EXPECT_EQ(json["products"].size(), 1);
}

TEST(CartControllerTest, ToJsonCartWithManyProducts) {
  std::vector<Product> products;
  for (int i = 0; i < 10; i++) {
    Product p("p" + std::to_string(i), "Product " + std::to_string(i),
              i * 10.0);
    products.push_back(p);
  }

  Outlet outlet("Large Store", "Large Description", "outlet_large");
  Cart cart;
  cart.setCartId("large_cart");
  cart.setOutlet(outlet);
  cart.setProducts(products);

  auto json = to_json(cart);
  EXPECT_EQ(json["cartId"], "large_cart");
  EXPECT_EQ(json["products"].size(), 10);
  EXPECT_EQ(json["products"][0]["productName"], "Product 0");
  EXPECT_EQ(json["products"][9]["productName"], "Product 9");
}

TEST(CartControllerTest, ToJsonCartWithSpecialCharacters) {
  std::vector<Product> products;
  Product p1("p1", "Product & More", 50.0);
  products.push_back(p1);

  Outlet outlet("Store & More", "Description & More", "outlet&more");
  Cart cart;
  cart.setCartId("cart&more");
  cart.setOutlet(outlet);
  cart.setProducts(products);

  auto json = to_json(cart);
  EXPECT_EQ(json["cartId"], "cart&more");
  EXPECT_EQ(json["outlet"]["outletName"], "Store & More");
  EXPECT_EQ(json["products"][0]["productName"], "Product & More");
}

// Test CartProductInfo to_json
TEST(CartControllerTest, ToJsonCartProductInfo) {
  std::vector<Product> products;
  Product p1("p1", "Test Product", 75.0);
  products.push_back(p1);

  Outlet outlet("Test Store", "Test Description", "outlet_test");
  Cart cart;
  cart.setCartId("cart_test");
  cart.setOutlet(outlet);
  cart.setProducts(products);

  Product product("prod_test", "Product Info", 100.0);

  CartProductInfo info;
  info.setCart(cart);
  info.setProduct(product);
  info.setSellingPrice(85.0);

  auto json = to_json(info);
  EXPECT_EQ(json["cart"]["cartId"], "cart_test");
  EXPECT_EQ(json["proudct"]["productId"],
            "prod_test"); // Note: typo in original code
  EXPECT_EQ(json["sellingPrice"], 85.0);
}

TEST(CartControllerTest, ToJsonCartProductInfoWithZeroSellingPrice) {
  std::vector<Product> products;
  Outlet outlet("Store", "Description", "outlet1");
  Cart cart;
  cart.setCartId("cart1");
  cart.setOutlet(outlet);
  cart.setProducts(products);

  Product product("prod1", "Product 1", 50.0);

  CartProductInfo info;
  info.setCart(cart);
  info.setProduct(product);
  info.setSellingPrice(0.0);

  auto json = to_json(info);
  EXPECT_EQ(json["sellingPrice"], 0.0);
}

// Test edge cases and boundary conditions
TEST(CartControllerTest, ToJsonCartWithEmptyCartId) {
  std::vector<Product> products;
  Outlet outlet("Store", "Description", "outlet1");
  Cart cart;
  cart.setCartId("");
  cart.setOutlet(outlet);
  cart.setProducts(products);

  auto json = to_json(cart);
  EXPECT_EQ(json["cartId"], "");
}

TEST(CartControllerTest, ToJsonCartWithVeryLongStrings) {
  std::string longString(1000, 'a');
  std::vector<Product> products;
  Product p1("p1", longString, 100.0);
  products.push_back(p1);

  Outlet outlet(longString, longString, longString);
  Cart cart;
  cart.setCartId(longString);
  cart.setOutlet(outlet);
  cart.setProducts(products);

  auto json = to_json(cart);
  EXPECT_EQ(json["cartId"], longString);
  EXPECT_EQ(json["outlet"]["outletName"], longString);
  EXPECT_EQ(json["products"][0]["productName"], longString);
}

// Test Product comparison operator
TEST(CartControllerTest, ProductComparisonOperator) {
  Product p1("p1", "Product 1", 10.0);
  Product p2("p2", "Product 2", 20.0);
  Product p3("p3", "Product 3", 10.0);

  EXPECT_TRUE(p1 < p2);
  EXPECT_FALSE(p2 < p1);
  EXPECT_FALSE(p1 < p3); // Same price, should not be less
}

// Test Cart addProduct method
TEST(CartControllerTest, CartAddProduct) {
  Cart cart;
  Product p1("p1", "Product 1", 25.0);
  Product p2("p2", "Product 2", 50.0);

  cart.addProduct(p1);
  cart.addProduct(p2);

  auto products = cart.getProducts();
  EXPECT_EQ(products.size(), 2);
  EXPECT_EQ(products[0].getProductId(), "p1");
  EXPECT_EQ(products[1].getProductId(), "p2");
}

// Test DTO classes
TEST(CartControllerTest, AddProductRequestGettersAndSetters) {
  AddProductRequest request;

  request.setUserId("user123");
  request.setOutletId("outlet456");
  request.setProductId("product789");

  EXPECT_EQ(request.getUserId(), "user123");
  EXPECT_EQ(request.getOutletId(), "outlet456");
  EXPECT_EQ(request.getProductId(), "product789");
}

TEST(CartControllerTest, CartProductInfoGettersAndSetters) {
  std::vector<Product> products;
  Outlet outlet("Store", "Description", "outlet1");
  Cart cart;
  cart.setCartId("cart1");
  cart.setOutlet(outlet);
  cart.setProducts(products);

  Product product("prod1", "Product 1", 100.0);

  CartProductInfo info;
  info.setCart(cart);
  info.setProduct(product);
  info.setSellingPrice(90.0);

  EXPECT_EQ(info.getCart().getCartId(), "cart1");
  EXPECT_EQ(info.getProduct().getProductId(), "prod1");
  EXPECT_EQ(info.getSellingPrice(), 90.0);
}

// Test JSON structure validation
TEST(CartControllerTest, JsonStructureValidation) {
  std::vector<Product> products;
  Product p1("p1", "Product 1", 25.0);
  products.push_back(p1);

  Outlet outlet("Store", "Description", "outlet1");
  Cart cart;
  cart.setCartId("cart1");
  cart.setOutlet(outlet);
  cart.setProducts(products);

  auto json = to_json(cart);

  // Verify all required fields exist
  EXPECT_TRUE(json.contains("cartId"));
  EXPECT_TRUE(json.contains("outlet"));
  EXPECT_TRUE(json.contains("products"));

  // Verify outlet structure
  EXPECT_TRUE(json["outlet"].contains("outletId"));
  EXPECT_TRUE(json["outlet"].contains("outletName"));

  // Verify products array structure
  EXPECT_TRUE(json["products"].is_array());
  if (!json["products"].empty()) {
    EXPECT_TRUE(json["products"][0].contains("productId"));
    EXPECT_TRUE(json["products"][0].contains("productName"));
    EXPECT_TRUE(json["products"][0].contains("mrp"));
  }
}

// Test with different numeric values
TEST(CartControllerTest, ToJsonProductWithHighPrice) {
  Product product("prod_high", "Expensive Product", 999999.9);
  auto json = to_json(product);

  constexpr double epsilon = 0.05; // relaxed tolerance

  EXPECT_EQ(json["productId"], "prod_high");
  EXPECT_EQ(json["productName"], "Expensive Product");
  EXPECT_NEAR(json["mrp"].get<double>(), 999999.90, epsilon);
}

TEST(CartControllerTest, ToJsonProductWithPrecisePrice) {
  Product product("prod_precise", "Precise Product", 3.14159);
  auto json = to_json(product);

  EXPECT_EQ(json["productId"], "prod_precise");
  EXPECT_EQ(json["productName"], "Precise Product");
  EXPECT_NEAR(json["mrp"], 3.14159, 0.00001);
}
