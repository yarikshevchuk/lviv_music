#pragma once
#include <set>
#include <string>
#include <vector>

class Song;
class Server;
class Playlist;
class Profile {
   private:
    int userId;
    static int Count;

   protected:
    bool isAuthenticated;
    std::set<Song*> recs;
    std::vector<Song*> likedSongs;
    std::vector<Playlist*> playlists;

   public:
    Profile(bool authStatus);
    virtual ~Profile() {};

    virtual void addPlaylist(Playlist* playlist) = 0;
    virtual void removePlaylist(Playlist* playlist) = 0;

    virtual void likeSong(Server& server, const std::string& songName) = 0;
    virtual void likeSong(Server& server, int songId) = 0;

    virtual void setRecs(std::vector<Song*> trending) = 0;

    virtual std::string getUsername() = 0;
    std::vector<Song*> getRecs();
    std::vector<Song*> getLikedSongs();
    std::vector<Playlist*> getPlaylists();
    int getId();
    int getAuthStatus();
};
