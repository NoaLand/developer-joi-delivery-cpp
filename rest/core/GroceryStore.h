#pragma once

#include "GroceryProduct.h"
#include "Outlet.h"

#include <set>

namespace tw::delivery::core {
    struct GroceryStore : Outlet {
        std::set<GroceryProduct> inventory;

        using Outlet::Outlet;
    };
}
