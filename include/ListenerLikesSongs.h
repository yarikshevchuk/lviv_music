#pragma once

#include "interface/ILikesSongs.h"

class Song;

class ListenerLikesSongs: public ILikesSongs{
private:
    std::vector<Song*> likedSongs_;
public:
    void likeSong(Server& server, const std::string& songName) override;
    void likeSong(Server& server, int songId) override;
    std::vector<Song*> getLikedSongs() override;
};
