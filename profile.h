#pragma once
#include <set>
#include <string>
#include <vector>

class Song;
class Server;
class Profile {
    int userId;
    static int Count;

   protected:
    bool isAuthenticated;
    std::set<Song*> recs;
    std::vector<Song*> likedSongs;

   public:
    Profile(bool authStatus);
    virtual ~Profile() {};

    virtual void setRecs(std::vector<Song*> trending) = 0;
    virtual void likeSong(Server& server, const std::string& songName) = 0;
    virtual void likeSong(Server& server, int songId) = 0;
    virtual std::string getUsername() = 0;

    std::vector<Song*> getRecs();
    std::vector<Song*> getLikedSongs();
    int getId();
    int getAuthStatus();
};
