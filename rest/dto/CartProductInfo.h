#pragma once

#include "../domain/Cart.h"
#include "../domain/Product.h"

class CartProductInfo {
public:
    // CartProductInfo(const Cart& c, const Product& p, float price)
    //     : cart(c), product(p), sellingPrice(price) {}
	// Getters
	const Cart& getCart() const { return cart; }
	const Product& getProduct() const { return product; }
	const float& getSellingPrice() const { return sellingPrice; }

	// Setters
	void setCart(const Cart& cart) { this->cart = cart; }
	void setProduct(const Product& product) { this->product = product; }
	void setSellingPrice(const float& sp) { this->sellingPrice = sp; }

private:
    Cart cart;
    Product product;
    float sellingPrice;
};
