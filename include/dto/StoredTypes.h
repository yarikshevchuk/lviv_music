#pragma once
#include <set>
#include <string>

namespace DTO {

struct UserRow {
    int id{0};
    std::string username;
    std::string password_hash;
    std::string email;
    int age{0};
    bool is_artist{false};
};

}  // namespace DTO
