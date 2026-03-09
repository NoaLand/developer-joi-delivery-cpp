#pragma once

#include "GroceryProduct.h"
#include "Outlet.h"

#include <set>
#include <string>
using namespace std;

class GroceryStore : public Outlet {
public:
  GroceryStore(string name, string desc, string oid) : Outlet(name, desc, oid) {
    this->inventory.clear();
  }

  // Getters
  const set<GroceryProduct> getInventory() const { return inventory; }

private:
  set<GroceryProduct> inventory;
};
