#pragma once
#include <string>
#include <vector>

class Profile;
class Song;

class Server {
    std::vector<Song*> trendingSongs;
    std::vector<Song*> allSongs;
    std::vector<Profile*> users;

   public:
    ~Server();

    std::vector<Song*> getTrendingSongs();
    std::vector<Song*> getAllSongs();

    void addUser(Profile* prfl);
    void setTrendingSongs(std::vector<Song*> sngs);
    void addTrendingSong(Song* sng);
    void addSong(Song* sng);

    Song* findSong(std::string songName);
    Song* findSong(int songId);
};