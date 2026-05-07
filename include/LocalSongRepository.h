#pragma once
#include "boost/di.hpp"
#include "interface/ISongRepository.h"

class Song;

class LocalSongRepository : public ISongRepository {
   private:
    std::vector<std::shared_ptr<Song>> songs_;
    std::vector<std::shared_ptr<Song>> trends_;

    LocalSongRepository() {}

   public:
    ~LocalSongRepository() = default;
    LocalSongRepository(const LocalSongRepository&) = delete;
    LocalSongRepository& operator=(const LocalSongRepository&) = delete;

    static LocalSongRepository* getInstance();

    void clear();

    void addSong(std::shared_ptr<Song> sng) override;
    void addTrendingSong(std::shared_ptr<Song> sng) override;

    std::vector<std::shared_ptr<Song>> getTrendingSongs() override;
    std::vector<std::shared_ptr<Song>> getSongs() override;

    std::shared_ptr<Song> findSong(const std::string& songName) override;
    std::shared_ptr<Song> findSong(int songId) override;
};