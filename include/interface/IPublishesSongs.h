#pragma once
#include <memory>
#include <string>

class Server;
class Song;

class IPublishesSongs {
   public:
    virtual ~IPublishesSongs() = default;

    virtual void publishSong(Server& server, std::shared_ptr<Song> song) = 0;
};
