#pragma once

#include "ProductService.h"
#include "UserService.h"
#include "../domain/Cart.h"
#include "../domain/GroceryProduct.h"
#include "../domain/User.h"
#include "../dto/AddProductRequest.h"
#include "../dto/CartProductInfo.h"
#include "../seedData/SeedData.h"

#include <memory>
#include <string>
#include <unordered_map>
#include <optional>
#include <iostream>

class CartService {
public:
  CartService(const CartService& cs) {
    this->userService = cs.userService;
    this->productService = cs.productService;
  }
  CartService(UserService &uService, ProductService &pService)
      : userService(uService), productService(pService) {}
  CartService(std::unordered_map<std::string, Cart> &carts,
              UserService &uService, ProductService &pService)
      : userCarts(carts), userService(uService), productService(pService) {}

  CartProductInfo
  addProductToCartForUser(const AddProductRequest &addProductRequest) {
    CartProductInfo cartProductInfo;
    auto user = userService.fetchUserById(addProductRequest.getUserId());
    if(!user.has_value()) {
      std::cerr << "User not found: " << addProductRequest.getUserId() << std::endl;
      return cartProductInfo;
    }
    Cart &cart = fetchCartForUser(user.value());

    auto product = productService.getProduct(
        addProductRequest.getProductId(), addProductRequest.getOutletId());
    if(!product.has_value()) {
      std::cerr << "Product not found: " << addProductRequest.getOutletId() << std::endl;
      return cartProductInfo;
    }

    GroceryProduct gproduct = product.value();
    //cart.getProducts().push_back(product.value());
    cart.addProduct(gproduct);

    cartProductInfo.setCart(cart);
    cartProductInfo.setProduct(gproduct);
    cartProductInfo.setSellingPrice(gproduct.getSellingPrice());

    return cartProductInfo;
  }

  Cart getCartForUser(const std::string &userId) {
    auto user = userService.fetchUserById(userId);
    return fetchCartForUser(user.value());
  }

private:
  std::unordered_map<std::string, Cart> userCarts{SeedData::cartForUsers};
  UserService userService;
  ProductService productService;

  Cart &fetchCartForUser(const User &user) {
    return userCarts.at(user.getUserId()); // throws if not found
  }
};
