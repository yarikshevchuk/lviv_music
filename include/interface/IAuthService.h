#pragma once
#include <string>

class IAuthService{
    public: 
    virtual ~IAuthService() = default;

    virtual bool login(const std::string& username, const std::string& password) = 0;
    virtual void logout() = 0;

    virtual bool isAuthenticated() const = 0;
    virtual const std::string& getUsername() const = 0;
};