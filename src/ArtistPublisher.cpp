#include "../include/ArtistPublisher.h"
#include "../include/interface/ISongRepository.h"

#include <memory>
#include "../include/Song.h"

void ArtistPublisher::publishSong(std::shared_ptr<ISongRepository> songs, std::shared_ptr<Song> song) {
    if (!song) {
        return;
    }
    songs->addSong(song);
}

