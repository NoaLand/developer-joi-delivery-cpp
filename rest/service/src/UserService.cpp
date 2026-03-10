#include "tw/delivery/service/UserService.h"

namespace tw::delivery::service {
    UserService::UserService(std::vector<User> users) : users{std::move(users)} {}

    [[nodiscard]] std::optional<User> UserService::fetchUserById(std::string_view userId) const {
        for (const auto& user : users) {
            if (user.userId == userId) {
                return user;
            }
        }
        return std::nullopt; // No match found
    }
}
