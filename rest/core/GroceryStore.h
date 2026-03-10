#pragma once

#include "GroceryProduct.h"
#include "Outlet.h"

#include <set>

struct GroceryStore : Outlet {
    std::set<GroceryProduct> inventory;

    using Outlet::Outlet;
};
