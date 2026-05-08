#include "../../include/dto/SqliteUserStore.h"

#include <stdexcept>
#include <utility>

#include <sqlite3.h>

#include "interface/IUserStore.h"

namespace {

void bindString(sqlite3_stmt* st, int idx, const std::string& s) {
    if (sqlite3_bind_text(st, idx, s.c_str(), static_cast<int>(s.size()), SQLITE_TRANSIENT) != SQLITE_OK) {
        throw std::runtime_error("sqlite3_bind_text");
    }
}

}  

SqliteUserStore::SqliteUserStore(std::shared_ptr<dto::SqliteDatabase> db) : db_(std::move(db)) {}

int SqliteUserStore::insertUser(const DTO::UserRow& user) {
    sqlite3* db = db_->handle();
    const char* sql = "INSERT INTO users (username, password_hash, email, age, is_artist) "
                      "VALUES (?, ?, ?, ?, ?);";
    sqlite3_stmt* st = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &st, nullptr) != SQLITE_OK) {   
        throw std::runtime_error("sqlite3_prepare_v2 (insert user)");
    }
    bindString(st, 1, user.username);
    bindString(st, 2, user.password_hash);
    bindString(st, 3, user.email);
    sqlite3_bind_int(st, 4, user.age);
    sqlite3_bind_int(st, 5, user.is_artist ? 1 : 0);

    const int step_rc = sqlite3_step(st);
    sqlite3_finalize(st);
    if (step_rc != SQLITE_DONE) {
        return -1;
    }
    return static_cast<int>(sqlite3_last_insert_rowid(db));
}

bool SqliteUserStore::deleteUser(int id) {
    sqlite3* db = db_->handle();
    const char* sql = "DELETE FROM users WHERE id = ?;";
    sqlite3_stmt* st = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &st, nullptr) != SQLITE_OK) {
        throw std::runtime_error("sqlite3_prepare_v2 (delete user)");
    }
    sqlite3_bind_int(st, 1, id);
    const int step_rc = sqlite3_step(st);
    sqlite3_finalize(st);
    if (step_rc != SQLITE_DONE) {
        return false;
    }
    return sqlite3_changes(db) > 0;
}

static DTO::UserRow rowFromStmt(sqlite3_stmt* st) {
    DTO::UserRow u;
    u.id = sqlite3_column_int(st, 0);
    const unsigned char* name = sqlite3_column_text(st, 1);
    const unsigned char* ph = sqlite3_column_text(st, 2);
    const unsigned char* em = sqlite3_column_text(st, 3);
    u.username = name ? reinterpret_cast<const char*>(name) : std::string{};
    u.password_hash = ph ? reinterpret_cast<const char*>(ph) : std::string{};
    u.email = em ? reinterpret_cast<const char*>(em) : std::string{};
    u.age = sqlite3_column_int(st, 4);
    u.is_artist = sqlite3_column_int(st, 5) != 0;
    return u;
}

std::shared_ptr<DTO::UserRow> SqliteUserStore::getUserById(int id) const {
    sqlite3* db = db_->handle();
    const char* sql = "SELECT id, username, password_hash, email, age, is_artist "
                       "FROM users WHERE id = ? LIMIT 1;";
    sqlite3_stmt* st = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &st, nullptr) != SQLITE_OK) {
        throw std::runtime_error("sqlite3_prepare_v2 (get user by id)");
    }
    sqlite3_bind_int(st, 1, id);
    const int step_rc = sqlite3_step(st);
    if (step_rc == SQLITE_ROW) {
        DTO::UserRow u = rowFromStmt(st);
        sqlite3_finalize(st);
        return std::make_shared<DTO::UserRow>(u);
    }
    sqlite3_finalize(st);
    return nullptr;
}

std::shared_ptr<DTO::UserRow> SqliteUserStore::getUserByUsername(const std::string& username) const {
    sqlite3* db = db_->handle();
    const char* sql = "SELECT id, username, password_hash, email, age, is_artist "
                       "FROM users WHERE username = ? LIMIT 1;";
    sqlite3_stmt* st = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &st, nullptr) != SQLITE_OK) {
        throw std::runtime_error("sqlite3_prepare_v2 (get user by username)");
    }
    bindString(st, 1, username);
    const int step_rc = sqlite3_step(st);
    if (step_rc == SQLITE_ROW) {
        DTO::UserRow u = rowFromStmt(st);
        sqlite3_finalize(st);
        return std::make_shared<DTO::UserRow>(u);
    }
    sqlite3_finalize(st);
    return nullptr;
}

std::vector<DTO::UserRow> SqliteUserStore::listUsers() const {
    sqlite3* db = db_->handle();
    const char* sql = "SELECT id, username, password_hash, email, age, is_artist "
                       "FROM users ORDER BY id ASC;";
    sqlite3_stmt* st = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &st, nullptr) != SQLITE_OK) {
        throw std::runtime_error("sqlite3_prepare_v2 (list users)");
    }
    std::vector<DTO::UserRow> out;
    int rc;
    while ((rc = sqlite3_step(st)) == SQLITE_ROW) {
        out.push_back(rowFromStmt(st));
    }
    sqlite3_finalize(st);
    if (rc != SQLITE_DONE) {
        throw std::runtime_error("sqlite3_step (list users)");
    }
    return out;
}
