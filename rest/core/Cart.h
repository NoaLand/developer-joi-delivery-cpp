#pragma once


class User;

#include "Product.h"
#include "User.h"
#include "Outlet.h"

#include <string>
#include <vector>
using namespace std;


class Cart {
public:
	//Getters
	Cart(){products.clear();};

	const std::string& getCartId() const { return cartId; }
	const Outlet& getOutlet() const { return outlet; }
	vector<Product> getProducts() const { return products; }
	const string& getUserId() const { return userId; }

	//Setters
	void setCartId(const std::string& id) { cartId = id; }
	void setOutlet(const Outlet& out) { outlet = out; }
	void setProducts(const vector<Product>& pLists) {
		products.clear();
		for(auto& prod: pLists) {
			products.emplace_back(prod);
			//addProduct(prod);
		}
	}
	void addProduct(const Product& prod) {
		products.emplace_back(prod);
	}
	void setUserId(const string& user) {
		this->userId = user;
	}
private:

    string cartId;
    Outlet outlet;

    vector<Product> products;
    // User user;
	string userId;
};
