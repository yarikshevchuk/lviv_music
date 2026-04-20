#include "../include/ListenerLikesSongs.h"

#include <iostream>
#include <map>

#include "../include/server.h"
#include "../include/song.h"

using namespace std;

void ListenerLikesSongs::likeSong(Server& server, const string& songName) {
    Song* likedSong = server.findSong(songName);
    if (likedSong == nullptr) {
        return;
    }

    for (Song* sng : likedSongs_) {
        if (sng->getName() == likedSong->getName()) {
            return;
        }
    }
    // cout << "@" << username << " liked a song " << likedSong->getName() << "\n"; // this logic needs to be moved to feed

    likedSongs_.push_back(likedSong);
    likedSong->updateRating(1);
    // updatePrimaryGenre();
    // setRecs(server.getAllSongs());
}

void ListenerLikesSongs::likeSong(Server& server, int songId) {
    Song* likedSong = server.findSong(songId);
    if (likedSong == nullptr) {
        return;
    }

    for (Song* sng : likedSongs_) {
        if (sng->getName() == likedSong->getName()) {
            return;
        }
    }
    // cout << "@" << username << " liked a song " << likedSong->getName() << "\n"; // this logic needs to be moved to feed

    likedSongs_.push_back(likedSong);
    likedSong->updateRating(1);
    // updatePrimaryGenre();
    // setRecs(server.getAllSongs());
}
vector<Song*> ListenerLikesSongs::getLikedSongs() { return likedSongs_; };