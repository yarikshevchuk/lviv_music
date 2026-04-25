#include "../include/LocalAuthService.h"

LocalAuthService::LocalAuthService() {
    creds_.emplace("user1", "user1");
    creds_.emplace("admin", "admin");
}

bool LocalAuthService::login(const std::string& username, const std::string& password) {
    auto it = creds_.find(username);
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
    if (!isAuthenticated_) return empty_;
    return current_;
}