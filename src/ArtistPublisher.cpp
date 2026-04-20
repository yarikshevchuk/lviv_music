#include "../include/ArtistPublisher.h"

#include "../include/server.h"
#include "../include/song.h"

void ArtistPublisher::publishSong(Server& server, Song* song) {
    if (song == nullptr) {
        return;
    }
    server.addSong(song);
}

