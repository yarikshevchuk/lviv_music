#pragma once
#include <memory>

#include "interface/ILikesSongs.h"

class ListenerLikesSongs: public ILikesSongs{
private:
    std::vector<std::shared_ptr<Song>> likedSongs_;
public:
    void likeSong(std::shared_ptr<ISongRepository>, int songId) override;
    void unlikeSong(std::shared_ptr<ISongRepository>, int songId) override;
    std::vector<std::shared_ptr<Song>> getLikedSongs() override;
};
