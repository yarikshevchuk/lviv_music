#pragma once

#include "interface/IPublishesSongs.h"


class ArtistPublisher : public IPublishesSongs {
private:
    std::string artistName_;
   public:
    ArtistPublisher(const std::string name);

    void publishSong(std::shared_ptr<ISongRepository> songs, std::shared_ptr<Song> song) override;
    void setArtistName(const std::string name) override;
    const std::string getArtistName() override;
};

