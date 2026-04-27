#pragma once
#include "interface/IAuthService.h"
#include <string>
#include <unordered_map>

class LocalAuthService : public IAuthService {
   private:
    std::unordered_map<std::string, std::string> creds_;
    bool isAuthenticated_{false};
    std::string current_;
    std::string empty_;

    static bool isValidCredential(const std::string& s);

   public:
    LocalAuthService();
    bool registerUser(const std::string& username, const std::string& password) override;
    bool login(const std::string& username, const std::string& password) override;
    void logout() override;

    bool isAuthenticated() const override;
    const std::string& getUsername() const override;
};
