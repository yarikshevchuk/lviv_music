#include "../include/LoggerLikesSongs.h"

#include <memory>

#include "../include/Song.h"

using namespace std;

void LoggerLikesSongs::likeSong(std::shared_ptr<ISongRepository> songs, int songId) {
    const shared_ptr<Song> sng = songs->findSong(songId);
    std::cout << "[LOG]:User liked song: " << sng->getName() << std::endl;
    likesSongs_->likeSong(songs, songId);
}

void LoggerLikesSongs::unlikeSong(std::shared_ptr<ISongRepository> songs, int songId) {
    const shared_ptr<Song> sng = songs->findSong(songId);
    std::cout << "[LOG]:User unliked song: " << sng->getName() << std::endl;
    likesSongs_->unlikeSong(songs, songId);
}
vector<shared_ptr<Song>> LoggerLikesSongs::getLikedSongs() { return likesSongs_->getLikedSongs(); };