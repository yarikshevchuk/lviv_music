#pragma once
#include <memory>
#include <string>
#include <vector>

class Song;

class Server {
   private:
    std::vector<std::shared_ptr<Song>> trendingSongs;
    std::vector<std::shared_ptr<Song>> allSongs;

   public:
    ~Server() = default;

    std::vector<std::shared_ptr<Song>> getTrendingSongs();
    std::vector<std::shared_ptr<Song>> getAllSongs();

    void setTrendingSongs(std::vector<std::shared_ptr<Song>> sngs);
    void addTrendingSong(std::shared_ptr<Song> sng);
    void addSong(std::shared_ptr<Song> sng);

    std::shared_ptr<Song> findSong(const std::string& songName);
    std::shared_ptr<Song> findSong(int songId);
};