#pragma once

#include <memory>
#include <vector>

#include "../interface/ISongStore.h"
#include "SqliteDatabase.h"

class SqliteSongStore final : public ISongStore {
   public:
    explicit SqliteSongStore(std::shared_ptr<dto::SqliteDatabase> db);
    int insertSong(const DTO::SongRow& song) override;
    bool updateSong(const DTO::SongRow& song) override;
    bool deleteSong(int id) override;

    std::shared_ptr<DTO::SongRow> getSongById(int id) const override;
    std::vector<DTO::SongRow> listSongs() const override;

   private:
    std::shared_ptr<dto::SqliteDatabase> db_;
};
