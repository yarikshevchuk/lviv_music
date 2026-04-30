#include "../../include/dto/SqliteSongStore.h"

#include <cctype>
#include <stdexcept>
#include <utility>

#include <sqlite3.h>

#include "interface/ISongStore.h"

namespace {

void bindString(sqlite3_stmt* st, int idx, const std::string& s) {
    if (sqlite3_bind_text(st, idx, s.c_str(), static_cast<int>(s.size()), SQLITE_TRANSIENT) != SQLITE_OK) {
        throw std::runtime_error("sqlite3_bind_text");
    }
}

std::string joinGenres(const std::set<std::string>& genres) {
    std::string out;
    bool first = true;
    for (const auto& g : genres) {
        if (!first) {
            out += ',';
        }
        first = false;
        out += g;
    }
    return out;
}

std::string trim(const std::string& s) {
    size_t b = 0;
    while (b < s.size() && std::isspace(static_cast<unsigned char>(s[b])) != 0) {
        ++b;
    }
    size_t e = s.size();
    while (e > b && std::isspace(static_cast<unsigned char>(s[e - 1])) != 0) {
        --e;
    }
    return s.substr(b, e - b);
}

std::set<std::string> parseGenres(const std::string& text) {
    std::set<std::string> out;
    size_t i = 0;
    while (i < text.size()) {
        size_t j = text.find(',', i);
        if (j == std::string::npos) {
            j = text.size();
        }
        std::string token = trim(text.substr(i, j - i));
        if (!token.empty()) {
            out.insert(std::move(token));
        }
        i = (j == text.size()) ? j : (j + 1);
    }
    return out;
}

bool execNoRows(sqlite3* db, const char* sql) {
    char* err = nullptr;
    const int rc = sqlite3_exec(db, sql, nullptr, nullptr, &err);
    if (rc != SQLITE_OK) {
        std::string what = "sqlite3_exec: ";
        if (err) {
            what += err;
            sqlite3_free(err);
        } else {
            what += "unknown";
        }
        throw std::runtime_error(what);
    }
    return true;
}

}  // namespace

SqliteSongStore::SqliteSongStore(std::shared_ptr<dto::SqliteDatabase> db) : db_(std::move(db)) {}

int SqliteSongStore::insertSong(const DTO::SongRow& song) {
    sqlite3* db = db_->handle();
    const char* sql =
        "INSERT INTO songs (name, author, duration_sec, rating, listen_count, genres_text) "
        "VALUES (?, ?, ?, ?, ?, ?);";
    sqlite3_stmt* st = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &st, nullptr) != SQLITE_OK) {
        throw std::runtime_error("sqlite3_prepare_v2 (insert song)");
    }
    bindString(st, 1, song.name);
    bindString(st, 2, song.author);
    sqlite3_bind_int(st, 3, song.duration_sec);
    sqlite3_bind_int(st, 4, song.rating);
    sqlite3_bind_int(st, 5, song.listen_count);
    bindString(st, 6, joinGenres(song.genres));
    if (sqlite3_step(st) != SQLITE_DONE) {
        sqlite3_finalize(st);
        return -1;
    }
    sqlite3_finalize(st);
    return static_cast<int>(sqlite3_last_insert_rowid(db));
}

bool SqliteSongStore::updateSong(const DTO::SongRow& song) {
    sqlite3* db = db_->handle();
    const char* sql =
        "UPDATE songs SET name = ?, author = ?, duration_sec = ?, rating = ?, listen_count = ?, genres_text = ? "
        "WHERE id = ?;";
    sqlite3_stmt* st = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &st, nullptr) != SQLITE_OK) {
        throw std::runtime_error("sqlite3_prepare_v2 (update song)");
    }
    bindString(st, 1, song.name);
    bindString(st, 2, song.author);
    sqlite3_bind_int(st, 3, song.duration_sec);
    sqlite3_bind_int(st, 4, song.rating);
    sqlite3_bind_int(st, 5, song.listen_count);
    bindString(st, 6, joinGenres(song.genres));
    sqlite3_bind_int(st, 7, song.id);
    if (sqlite3_step(st) != SQLITE_DONE) {
        sqlite3_finalize(st);
        return false;
    }
    sqlite3_finalize(st);
    return sqlite3_changes(db) > 0;
}

bool SqliteSongStore::deleteSong(int id) {
    sqlite3* db = db_->handle();
    const char* sql = "DELETE FROM songs WHERE id = ?;";
    sqlite3_stmt* st = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &st, nullptr) != SQLITE_OK) {
        throw std::runtime_error("sqlite3_prepare_v2 (delete song)");
    }
    sqlite3_bind_int(st, 1, id);
    const int step_rc = sqlite3_step(st);
    sqlite3_finalize(st);
    if (step_rc != SQLITE_DONE) {
        return false;
    }
    return sqlite3_changes(db) > 0;
}

static DTO::SongRow rowFromStmtWithoutGenres(sqlite3_stmt* st) {
    DTO::SongRow s;
    s.id = sqlite3_column_int(st, 0);
    const unsigned char* nm = sqlite3_column_text(st, 1);
    const unsigned char* au = sqlite3_column_text(st, 2);
    const unsigned char* genres = sqlite3_column_text(st, 6);
    s.name = nm ? reinterpret_cast<const char*>(nm) : std::string{};
    s.author = au ? reinterpret_cast<const char*>(au) : std::string{};
    s.duration_sec = sqlite3_column_int(st, 3);
    s.rating = sqlite3_column_int(st, 4);
    s.listen_count = sqlite3_column_int(st, 5);
    s.genres = genres ? parseGenres(reinterpret_cast<const char*>(genres)) : std::set<std::string>{};
    return s;
}

std::shared_ptr<DTO::SongRow> SqliteSongStore::getSongById(int id) const {
    sqlite3* db = db_->handle();
    const char* sql = "SELECT id, name, author, duration_sec, rating, listen_count, genres_text "
                       "FROM songs WHERE id = ? LIMIT 1;";
    sqlite3_stmt* st = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &st, nullptr) != SQLITE_OK) {
        throw std::runtime_error("sqlite3_prepare_v2 (get song by id)");
    }
    sqlite3_bind_int(st, 1, id);
    const int step_rc = sqlite3_step(st);
    if (step_rc == SQLITE_ROW) {
        DTO::SongRow s = rowFromStmtWithoutGenres(st);
        sqlite3_finalize(st);
        return std::make_shared<DTO::SongRow>(s);
    }
    sqlite3_finalize(st);
    return nullptr;
}

std::vector<DTO::SongRow> SqliteSongStore::listSongs() const {
    sqlite3* db = db_->handle();
    const char* sql = "SELECT id, name, author, duration_sec, rating, listen_count, genres_text "
                       "FROM songs ORDER BY id ASC;";
    sqlite3_stmt* st = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &st, nullptr) != SQLITE_OK) {
        throw std::runtime_error("sqlite3_prepare_v2 (list songs)");
    }
    std::vector<DTO::SongRow> out;
    int rc;
    while ((rc = sqlite3_step(st)) == SQLITE_ROW) {
        DTO::SongRow s = rowFromStmtWithoutGenres(st);
        out.push_back(std::move(s));
    }
    sqlite3_finalize(st);
    if (rc != SQLITE_DONE) {
        throw std::runtime_error("sqlite3_step (list songs)");
    }
    return out;
}
