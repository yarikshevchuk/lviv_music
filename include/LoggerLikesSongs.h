#pragma once 
#include "./interface/ILikesSongs.h"
#include <iostream>
#include <memory>
#include <string>

class LoggerLikesSongs : public ILikesSongs{
    private:
    std::unique_ptr<ILikesSongs> likesSongs_;

    public:
    LoggerLikesSongs(std::unique_ptr<ILikesSongs> likesSongs) : likesSongs_(std::move(likesSongs)){};
    virtual void likeSong(std::shared_ptr<ISongRepository>, int songId) override;
    virtual void unlikeSong(std::shared_ptr<ISongRepository>, int songId) override;
    virtual std::vector<std::shared_ptr<Song>> getLikedSongs() override;

};