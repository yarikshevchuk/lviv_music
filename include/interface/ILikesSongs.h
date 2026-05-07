#pragma once
#include "ISongRepository.h"
#include <memory>
#include <string>
#include <vector>

class Server;
class Song;

class ILikesSongs {
   public:
    virtual ~ILikesSongs() = default;

    virtual void likeSong(std::shared_ptr<ISongRepository>, int songId) = 0;
    virtual void unlikeSong(std::shared_ptr<ISongRepository>, int songId) = 0;

    virtual std::vector<std::shared_ptr<Song>> getLikedSongs() = 0;
};