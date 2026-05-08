cmake_minimum_required(VERSION 3.16)
project(lviv_music LANGUAGES C CXX)

if(POLICY CMP0135)
  # FetchContent URL download: use extraction time for out-of-date checks (not archive timestamps)
  cmake_policy(SET CMP0135 NEW)
endif()
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/d72f9c8aea6817cdf1ca0ac10887f328de7f3da2.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
  sqlite3_source
  URL https://sqlite.org/2026/sqlite-amalgamation-3530000.zip
)
FetchContent_MakeAvailable(sqlite3_source)
add_library(sqlite3 STATIC "${sqlite3_source_SOURCE_DIR}/sqlite3.c")
target_include_directories(sqlite3 PUBLIC "${sqlite3_source_SOURCE_DIR}")

add_executable(lviv_music
    src/Main.cpp
    src/App.cpp
    src/Song.cpp
    src/Playlist.cpp
    src/User.cpp
    src/ListenerIdentity.cpp
    src/ListenerLikesSongs.cpp
    src/ListenerHasPlaylists.cpp
    src/ListenerHasRecs.cpp
    src/ArtistPublisher.cpp
    src/LocalAuthService.cpp
    src/SQLAuthService.cpp
    src/LoggerLikesSongs.cpp
    src/LocalSongRepository.cpp
    src/GenreRecommendationStrategy.cpp
    src/ArtistRecommendationStrategy.cpp
    src/RecommendationManager.cpp
    src/dto/SqliteDatabase.cpp
    src/dto/SqliteUserStore.cpp
)

enable_testing()
add_executable(lviv_music_tests
  tests/AuthTest.cpp
  tests/AuthRegisterTest.cpp
  tests/SQLAuthServiceTest.cpp
  tests/LocalSongRepositoryTest.cpp
  src/LocalAuthService.cpp
  src/SQLAuthService.cpp
  src/LocalSongRepository.cpp
  src/dto/SqliteDatabase.cpp
  src/dto/SqliteUserStore.cpp
  src/Song.cpp
)
target_include_directories(lviv_music_tests PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_compile_definitions(
  lviv_music_tests PRIVATE
  "LVIV_MUSIC_TEST_SCHEMA_SQL_PATH=\"${CMAKE_CURRENT_SOURCE_DIR}/db/schema.sql\""
)
target_link_libraries(
  lviv_music_tests PRIVATE
  GTest::gtest_main
  sqlite3
)

target_link_libraries(lviv_music
  sqlite3
)
include(GoogleTest)
gtest_discover_tests(lviv_music_tests)


target_include_directories(lviv_music PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

if(MSVC)
    target_compile_options(lviv_music PRIVATE /W4 /permissive-)
else()
    target_compile_options(lviv_music PRIVATE -Wall -Wextra -Wpedantic)
endif()
