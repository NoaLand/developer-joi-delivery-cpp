#pragma once

#include <string>
using namespace std;

class Product {
public:
  Product() : productId(""), productName(""), mrp(0.0) {}
  Product(string pid, string pname, float price)
      : productId(pid), productName(pname), mrp(price) {}

  // Getters
  const string &getProductId() const { return productId; }
  const string &getProductName() const { return productName; }
  const float &getMrp() const { return mrp; }

  // Setters
  void setProductId(const string &id) { productId = id; }
  void setProductName(const string &name) { productName = name; }
  void setMrp(const float &price) { mrp = price; }

  bool operator<(const Product &other) const {
    return this->getMrp() < other.getMrp();
  }

private:
  string productId;
  string productName;
  float mrp;
};
