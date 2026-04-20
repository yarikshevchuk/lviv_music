#pragma once
#include <string>

class IIdentity {
   public:
    virtual ~IIdentity() = default;

    virtual std::string getUsername() = 0;
    virtual std::string getEmail() = 0;
    virtual int getId() = 0;
    virtual int getAge() = 0;
};