#include "../include/ArtistPublisher.h"


#include <memory>
#include "../include/server.h"
#include "../include/song.h"

void ArtistPublisher::publishSong(Server& server, std::shared_ptr<Song> song) {
    if (!song) {
        return;
    }
    server.addSong(song);
}

