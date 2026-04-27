#pragma once

#include "interface/IPublishesSongs.h"


class ArtistPublisher : public IPublishesSongs {
   public:
    void publishSong(std::shared_ptr<ISongRepository> songs, std::shared_ptr<Song> song) override;
};

