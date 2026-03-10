#pragma once

#include "Product.h"
#include "Outlet.h"

#include <string>
#include <vector>
#include <memory>

struct Cart {
	std::string cartId;
	std::string userId;
	std::shared_ptr<Outlet> outlet;
	std::vector<std::shared_ptr<Product>> products;
};