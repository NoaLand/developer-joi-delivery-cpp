#pragma once

#include <optional>
#include <vector>

#include "tw/delivery/core/User.h"
#include "tw/delivery/data/SeedData.h"

namespace tw::delivery::service {
    class UserService {
        std::vector<core::User> users{data::SeedData::users};

    public:
        UserService() = default;
        explicit UserService(std::vector<core::User> users);

        // Return optional to handle "not found" instead of null
        [[nodiscard]] std::optional<core::User> fetchUserById(std::string_view userId) const;
    };
}
