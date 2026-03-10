#pragma once

#include <string>

namespace tw::delivery::core {
    struct  User {
        std::string userId;
        std::string firstName;
        std::string lastName;
        std::string email;
        std::string phoneNumber;
    };
}
