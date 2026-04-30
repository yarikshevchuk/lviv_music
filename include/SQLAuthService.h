#pragma once

#include "interface/IAuthService.h"

#include <memory>
#include <string>

class IUserStore;

class SQLAuthService: public IAuthService {
    private:
    static bool isValidCredential(const std::string& s);

    std::shared_ptr<IUserStore> userStore_;
    bool isAuthenticated_{false};
    std::string current_;
    std::string empty_;

   public:
    SQLAuthService(std::shared_ptr<IUserStore> userStore);

    bool registerUser(const std::string& username, const std::string& password) override;
    bool login(const std::string& username, const std::string& password) override;
    void logout() override;

    bool isAuthenticated() const override;
    const std::string& getUsername() const override;
};

