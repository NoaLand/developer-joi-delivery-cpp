#pragma once

#include <string>

struct Outlet {
    std::string name;
    std::string description;
    std::string outletId;

    Outlet() = default;
    Outlet(std::string name, std::string description, std::string outletId)
        : name{std::move(name)}, description{std::move(description)}, outletId{std::move(outletId)} {}

    virtual ~Outlet() = default;
};
