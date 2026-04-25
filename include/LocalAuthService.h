#pragma once 
#include "interface/IAuthService.h"
#include <string>
#include <unordered_map>

class LocalAuthService: public IAuthService{
private:
    std::unordered_map<std::string, std::string> creds_;
    bool isAuthenticated_{false};
    std::string current_;
    std::string empty_;

public:
    LocalAuthService();
    bool login(const std::string& username, const std::string& password) override;
    void logout() override;

    bool isAuthenticated() const override ;
    virtual const std::string& getUsername() const override;

};