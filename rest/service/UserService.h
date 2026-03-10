#pragma once

#include <optional>
#include <string>
#include <vector>

#include "core/User.h"
#include "data/SeedData.h"

class UserService {
    std::vector<User> users{SeedData::users};

public:
    UserService() = default;
    explicit UserService(std::vector<User> users) : users{std::move(users)} {}

    // Return optional to handle "not found" instead of null
    [[nodiscard]] std::optional<User> fetchUserById(const std::string& userId) const {
        for (const auto& user : users) {
            if (user.userId == userId) {
                return user;
            }
        }
        return std::nullopt; // No match found
    }
};
