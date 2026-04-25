#include "../include/ListenerLikesSongs.h"

#include <memory>

#include "../include/song.h"

using namespace std;

void ListenerLikesSongs::likeSong(std::shared_ptr<ISongRepository> songs, const string& songName) {
    auto likedSong = songs->findSong(songName);
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
}

void ListenerLikesSongs::likeSong(std::shared_ptr<ISongRepository> songs, int songId) {
    auto likedSong = songs->findSong(songId);
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