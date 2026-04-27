#pragma once
#include <memory>
#include <string>
#include <vector>

#include "../dto/StoredTypes.h"

class IUserStore {
   public:
    virtual ~IUserStore() = default;

    virtual int insertUser(const DTO::UserRow& user) = 0;
    virtual bool updateUser(const DTO::UserRow& user) = 0;
    virtual bool deleteUser(int id) = 0;

    virtual std::shared_ptr<DTO::UserRow> getUserById(int id) const = 0;
    virtual std::shared_ptr<DTO::UserRow> getUserByUsername(const std::string& username) const = 0;
    virtual std::vector<DTO::UserRow> listUsers() const = 0;
};
