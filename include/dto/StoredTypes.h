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

struct SongRow {
    int id{0};
    std::string name;
    std::string author;
    int duration_sec{180};
    int rating{0};
    int listen_count{0};
    std::set<std::string> genres;
};

} 
