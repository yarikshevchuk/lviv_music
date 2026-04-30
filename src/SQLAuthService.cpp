#include "../include/SQLAuthService.h"

#include <cctype>

#include "../include/dto/StoredTypes.h"
#include "../include/interface/IUserStore.h"

SQLAuthService::SQLAuthService(IUserStore& userStore) : userStore_(userStore) {}

bool SQLAuthService::isValidCredential(const std::string& s) {
    if (s.empty()) {
        return false;
    }
    for (unsigned char ch : s) {
        if (std::isspace(ch) != 0) {
            return false;
        }
    }
    return true;
}

bool SQLAuthService::registerUser(const std::string& username, const std::string& password) {
    if (!isValidCredential(username) || !isValidCredential(password)) {
        return false;
    }

    if (userStore_.getUserByUsername(username) != nullptr) {
        return false;
    }

    DTO::UserRow row;
    row.username = username;
    row.password_hash = password;
    row.email = "";
    row.age = 0;
    row.is_artist = false;

    const int newId = userStore_.insertUser(row);
    return newId > 0;
}

bool SQLAuthService::login(const std::string& username, const std::string& password) {
    auto user = userStore_.getUserByUsername(username);
    if (user == nullptr || user->password_hash != password) {
        isAuthenticated_ = false;
        current_.clear();
        return false;
    }
    isAuthenticated_ = true;
    current_ = username;
    return true;
}

void SQLAuthService::logout() {
    isAuthenticated_ = false;
    current_.clear();
}

bool SQLAuthService::isAuthenticated() const { return isAuthenticated_; }

const std::string& SQLAuthService::getUsername() const {
    if (!isAuthenticated_) {
        return empty_;
    }
    return current_;
}

