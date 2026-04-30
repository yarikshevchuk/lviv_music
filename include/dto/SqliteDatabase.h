#pragma once

#include <memory>
#include <string>

struct sqlite3;

namespace dto {

struct SqliteDbCloser {
    void operator()(sqlite3* db) const noexcept;
};

class SqliteDatabase {
   private:
    void close();
    void readSchema(const std::string& schema_file_path);

    std::unique_ptr<sqlite3, SqliteDbCloser> db_{nullptr};
    
   public:
    SqliteDatabase() = default;
    ~SqliteDatabase() = default;

    void open(const std::string& file_path, const std::string& schema_file_path = "db/schema.sql");

    sqlite3* handle() const { return db_.get(); }
};

}  
