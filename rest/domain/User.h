#pragma once

class Cart;
// #include "Cart.h"

#include <string>
using namespace std;

class User {
private:
    string userId;
    string userName;
    string firstName;
    string lastName;
    string email;
    string phoneNumber;
    // Cart cart;
    string cartId;
public:
    const string& getUserId() const { return userId;}
    const string& getUserName() const { return userName; }
    const string& getFirstName() const { return firstName; }
    const string& getLastName() const { return lastName; }
    const string& getEmail() const { return email; }
    const string& getPhoneNumber() const { return phoneNumber; }
    const string& getCartId() const { return cartId; }

    void setUserId(const string& id) { userId = id; }
    void setUserName(const string& name ) { userName = name;}
    void setFirstName(const string& fName) { firstName = fName; }
    void setLastName(const string& lName) { lastName = lName;}
    void setEmail(const string& e) { email = e; }
    void setPhoneNumber(const string& pNumber) { phoneNumber = pNumber; }
    void setCartId(const string& cId) { cartId = cId; } 
};
