#pragma once

#include "interface/IAuthService.h"

#include <string>

class IUserStore;

class SQLAuthService final : public IAuthService {
   private:
    static bool isValidCredential(const std::string& s);

    IUserStore& userStore_;
    bool isAuthenticated_{false};
    std::string current_;
    std::string empty_;

   public:
    explicit SQLAuthService(IUserStore& userStore);

    bool registerUser(const std::string& username, const std::string& password) override;
    bool login(const std::string& username, const std::string& password) override;
    void logout() override;

    bool isAuthenticated() const override;
    const std::string& getUsername() const override;
};

