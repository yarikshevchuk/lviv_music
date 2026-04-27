#include "../include/LocalAuthService.h"

#include <cctype>

bool LocalAuthService::isValidCredential(const std::string& s) {
    if (s.empty()) {
        return false;
    }
    for (unsigned char ch : s) {
        if (std::isspace(ch)) {
            return false;
        }
    }
    return true;
}

LocalAuthService::LocalAuthService() {
    creds_.emplace("user1", "user1");
    creds_.emplace("admin", "admin");
}

bool LocalAuthService::registerUser(const std::string& username, const std::string& password) {
    if (!isValidCredential(username) || !isValidCredential(password)) {
        return false;
    }
    if (creds_.find(username) != creds_.end()) {
        return false;
    }
    creds_.emplace(username, password);
    return true;
}

bool LocalAuthService::login(const std::string& username, const std::string& password) {
    const auto it = creds_.find(username);
    if (it == creds_.end() || it->second != password) {
        isAuthenticated_ = false;
        current_.clear();
        return false;
    }
    isAuthenticated_ = true;
    current_ = username;
    return true;
}

void LocalAuthService::logout() {
    isAuthenticated_ = false;
    current_.clear();
}

bool LocalAuthService::isAuthenticated() const { return isAuthenticated_; }

const std::string& LocalAuthService::getUsername() const {
    if (!isAuthenticated_) {
        return empty_;
    }
    return current_;
}
