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
    virtual void setArtistName(const std::string name) = 0;
    virtual const std::string getArtistName() = 0;
};
