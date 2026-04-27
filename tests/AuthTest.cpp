#include <gtest/gtest.h>

#include "LocalAuthService.h"

TEST(LocalAuthService, LoginSuccess) {
    LocalAuthService auth;
    EXPECT_TRUE(auth.login("user1", "user1"));
    EXPECT_TRUE(auth.isAuthenticated());
    EXPECT_EQ(auth.getUsername(), "user1");
}

TEST(LocalAuthService, LoginFailure) {
    LocalAuthService auth;
    EXPECT_FALSE(auth.login("user1", "wrongPass"));
    EXPECT_FALSE(auth.isAuthenticated());
}