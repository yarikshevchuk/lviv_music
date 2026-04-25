#pragma once
#include <memory>
#include <string>
#include <vector>

class Song;

class ISongRepository{
    public:
    virtual ~ISongRepository() = default;

    virtual void addSong(std::shared_ptr<Song> sng) = 0;
    virtual void addTrendingSong(std::shared_ptr<Song> sng) = 0;

    virtual std::vector<std::shared_ptr<Song>> getTrendingSongs() = 0;
    virtual std::vector<std::shared_ptr<Song>> getSongs() = 0;

    virtual std::shared_ptr<Song> findSong(const std::string& songName) = 0;
    virtual std::shared_ptr<Song> findSong(int songId) = 0;
};