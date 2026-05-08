#include "../../include/dto/SqliteDatabase.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

#include <sqlite3.h>

namespace dto {
namespace {

void throwOnError(int rc, sqlite3* db, const char* context) {
    if (rc == SQLITE_OK || rc == SQLITE_DONE || rc == SQLITE_ROW) {
        return;
    }
    const char* msg = db ? sqlite3_errmsg(db) : "unknown";
    std::string what = std::string(context) + ": " + msg;
    throw std::runtime_error(what);
}

}  

void SqliteDbCloser::operator()(sqlite3* db) const noexcept {
    if (db != nullptr) {
        sqlite3_close(db);
    }
}

void SqliteDatabase::open(const std::string& file_path, const std::string& schema_file_path) {
    close();

    sqlite3* raw = nullptr;
    int rc = sqlite3_open_v2(file_path.c_str(), &raw, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, nullptr);
    throwOnError(rc, raw, "sqlite3_open_v2");
    db_.reset(raw);

    if (!schema_file_path.empty()) {
        readSchema(schema_file_path);
    }
}

void SqliteDatabase::close() {
    db_.reset();
}

void SqliteDatabase::readSchema(const std::string& path) {
    std::ifstream in(path, std::ios::in | std::ios::binary);
    if (!in) {
        throw std::runtime_error("failed to read file: " + path);
    }
    std::ostringstream buffer;
    buffer << in.rdbuf();

    const std::string sql = buffer.str();
    if (sql.empty()) {
        return;
    }

    char* err = nullptr;
    const int rc = sqlite3_exec(db_.get(), sql.c_str(), nullptr, nullptr, &err);
    if (rc != SQLITE_OK) {
        std::string msg = err ? err : "unknown sqlite error";
        if (err) {
            sqlite3_free(err);
        }
        throw std::runtime_error(msg);
    }
}

}  
