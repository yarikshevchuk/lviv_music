#include "../include/ListenerLikesSongs.h"

#include <algorithm>
#include <memory>

#include "../include/Song.h"

using namespace std;

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

    likedSongs_.push_back(likedSong);
    likedSong->updateRating(1);
}

void ListenerLikesSongs::unlikeSong(std::shared_ptr<ISongRepository> songs, int songId) {
    auto unlikedSong = songs->findSong(songId);
    if (!unlikedSong) {
        return;
    }

    auto it = std::remove_if(likedSongs_.begin(), likedSongs_.end(), [songId](const std::shared_ptr<Song>& s) { return s && s->getId() == songId; });

    if (it != likedSongs_.end()) {
        likedSongs_.erase(it, likedSongs_.end());
        unlikedSong->updateRating(-1);
    }
}
vector<shared_ptr<Song>> ListenerLikesSongs::getLikedSongs() { return likedSongs_; };