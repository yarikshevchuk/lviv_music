#include <gtest/gtest.h>

#include <chrono>
#include <string>

#include "LocalAuthService.h"


TEST(LocalAuthService, RegisterInMemory) {
    const std::string u = "kasjdfklj19idjfhasdfkl";
    const std::string p = "secret1";

    LocalAuthService a;
    EXPECT_TRUE(a.registerUser(u, p));
    EXPECT_FALSE(a.registerUser(u, p));
    EXPECT_TRUE(a.login(u, p));
    EXPECT_TRUE(a.isAuthenticated());
    EXPECT_EQ(a.getUsername(), u);
}

TEST(LocalAuthService, RejectsInvalidCredentials) {
    LocalAuthService a;
    EXPECT_FALSE(a.registerUser("", "x"));
    EXPECT_FALSE(a.registerUser("x", ""));
    EXPECT_FALSE(a.registerUser("bad name", "pass"));
}
