#pragma once
#include <string>
#include <vector>

class Song;

class Server {
   private:
    std::vector<Song*> trendingSongs;
    std::vector<Song*> allSongs;

   public:
    ~Server();

    std::vector<Song*> getTrendingSongs();
    std::vector<Song*> getAllSongs();

    void setTrendingSongs(std::vector<Song*> sngs);
    void addTrendingSong(Song* sng);
    void addSong(Song* sng);

    Song* findSong(std::string songName);
    Song* findSong(int songId);
};