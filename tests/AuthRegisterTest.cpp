#include <gtest/gtest.h>

#include <chrono>
#include <string>

#include "LocalAuthService.h"

namespace {
std::string uniqueUsername() {
    const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    return "user_" + std::to_string(ms);
}
}  

TEST(LocalAuthService, RegisterInMemory) {
    const std::string u = uniqueUsername();
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
