#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "SQLAuthService.h"
#include "dto/SqliteDatabase.h"
#include "dto/SqliteUserStore.h"

static std::shared_ptr<dto::SqliteDatabase> makeInMemoryDb() {
    auto db = std::make_shared<dto::SqliteDatabase>();
    db->open(":memory:", "../db/schema.sql");
    return db;
}

TEST(SQLAuthService, RegisterAndLogin) {
    auto db = makeInMemoryDb();
    SqliteUserStore userStore(db);
    SQLAuthService auth(userStore);

    const std::string u = "user_sql";
    const std::string p = "pass_sql";

    EXPECT_TRUE(auth.registerUser(u, p));
    EXPECT_FALSE(auth.registerUser(u, p));

    EXPECT_TRUE(auth.login(u, p));
    EXPECT_TRUE(auth.isAuthenticated());
    EXPECT_EQ(auth.getUsername(), u);
}

TEST(SQLAuthService, LoginFailure) {
    auto db = makeInMemoryDb();
    SqliteUserStore userStore(db);
    SQLAuthService auth(userStore);

    EXPECT_FALSE(auth.login("missing", "x"));
    EXPECT_FALSE(auth.isAuthenticated());
}

TEST(SQLAuthService, RejectsInvalidCredentials) {
    auto db = makeInMemoryDb();
    SqliteUserStore userStore(db);
    SQLAuthService auth(userStore);

    EXPECT_FALSE(auth.registerUser("", "x"));
    EXPECT_FALSE(auth.registerUser("x", ""));
    EXPECT_FALSE(auth.registerUser("bad name", "pass"));
}

