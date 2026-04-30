#pragma once
#include <memory>
#include <string>
#include <vector>

#include "../dto/StoredTypes.h"

class ISongStore {
   public:
    virtual ~ISongStore() = default;

    virtual int insertSong(const DTO::SongRow& song) = 0;
    virtual bool updateSong(const DTO::SongRow& song) = 0;
    virtual bool deleteSong(int id) = 0;

    virtual std::shared_ptr<DTO::SongRow> getSongById(int id) const = 0;
    virtual std::vector<DTO::SongRow> listSongs() const = 0;
};
