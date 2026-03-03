#pragma once
#include <string>
#include <vector>

#include "profile.h"
class Song;
class Server;

class AuthProfile : public Profile {
   private:
    std::string username;
    std::string password;
    std::string primaryGenre;
    int age;

    std::string updatePrimaryGenre();
    void setRecs(std::vector<Song*> allSongs) override;

   public:
    AuthProfile(std::string username, std::string password, int age);
    void likeSong(Server& server, const std::string& songName) override;
    void likeSong(Server& server, int songId) override;
    void addPlaylist(Playlist* playlist) override;
    void removePlaylist(Playlist* playlist) override;

    std::string getUsername() override { return username; }
};