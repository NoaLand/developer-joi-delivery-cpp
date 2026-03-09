#pragma once
#include "core/User.h"
#include "data/SeedData.h"
#include <optional>
#include <string>
#include <vector>

class UserService {
public:
  UserService(std::vector<User> &usersRef) : users(usersRef) {}
  UserService() {}

  // Return optional to handle "not found" instead of null
  std::optional<User> fetchUserById(const std::string &userId) {
    for (const auto &user : users) {
      if (user.userId == userId) {
        return user;
      }
    }
    return std::nullopt; // No match found
  }

private:
  std::vector<User> users{SeedData::users};
};
