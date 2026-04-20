#pragma once
#include <string>

class Server;
class Song;

class IPublishesSongs {
   public:
    virtual ~IPublishesSongs() = default;

    virtual void publishSong(Server& server, Song* song) = 0;
};
