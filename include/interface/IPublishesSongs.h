#pragma once
#include <memory>
#include <string>

class Server;
class Song;
class ISongRepository;

class IPublishesSongs {
   public:
    virtual ~IPublishesSongs() = default;

    virtual void publishSong(std::shared_ptr<ISongRepository> songs, std::shared_ptr<Song> song) = 0;
};
