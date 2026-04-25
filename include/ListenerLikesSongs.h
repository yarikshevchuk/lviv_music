#pragma once
#include <memory>

#include "interface/ILikesSongs.h"

class ListenerLikesSongs: public ILikesSongs{
private:
    std::vector<std::shared_ptr<Song>> likedSongs_;
public:
    void likeSong(std::shared_ptr<ISongRepository>, const std::string& songName) override;
    void likeSong(std::shared_ptr<ISongRepository>, int songId) override;
    std::vector<std::shared_ptr<Song>> getLikedSongs() override;
};
