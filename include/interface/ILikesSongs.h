#pragma once
#include <string>
#include <vector>

class Server;
class Song;

class ILikesSongs {
   public:
    virtual ~ILikesSongs() = default;

    virtual void likeSong(Server& server, const std::string& songName) = 0;
    virtual void likeSong(Server& server, int songId) = 0;
    virtual std::vector<Song*> getLikedSongs() = 0;
};