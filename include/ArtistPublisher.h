#pragma once

#include "interface/IPublishesSongs.h"

class Song;

class ArtistPublisher : public IPublishesSongs {
   public:
    void publishSong(Server& server, Song* song) override;
};

