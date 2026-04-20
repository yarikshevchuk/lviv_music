#include "../include/ListenerLikesSongs.h"

#include <iostream>
#include <map>
#include <memory>

#include "../include/server.h"
#include "../include/song.h"

using namespace std;

void ListenerLikesSongs::likeSong(Server& server, const string& songName) {
    auto likedSong = server.findSong(songName);
    if (!likedSong) {
        return;
    }

    for (const auto& sng : likedSongs_) {
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
    auto likedSong = server.findSong(songId);
    if (!likedSong) {
        return;
    }

    for (const auto& sng : likedSongs_) {
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
vector<shared_ptr<Song>> ListenerLikesSongs::getLikedSongs() { return likedSongs_; };