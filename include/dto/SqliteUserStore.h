#pragma once

#include <memory>
#include <string>
#include <vector>

#include "../interface/IUserStore.h"
#include "SqliteDatabase.h"

class SqliteUserStore : public IUserStore {
   public:
    SqliteUserStore(std::shared_ptr<dto::SqliteDatabase> db);
    int insertUser(const DTO::UserRow& user) override;
    bool deleteUser(int id) override;

    std::shared_ptr<DTO::UserRow> getUserById(int id) const override;
    std::shared_ptr<DTO::UserRow> getUserByUsername(const std::string& username) const override;
    std::vector<DTO::UserRow> listUsers() const override;

   private:
    std::shared_ptr<dto::SqliteDatabase> db_;
};
