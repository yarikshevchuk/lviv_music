#include "../include/LocalSongRepository.h"
#include "../include/Song.h"
#include <vector>
#include <memory>

using namespace std;

void LocalSongRepository::addSong(std::shared_ptr<Song> sng) {
    if (!sng) return;
    for (auto ptr = songs_.begin(); ptr != songs_.end(); ptr++) {
        if (((*ptr)->getName() == sng->getName()) && ((*ptr)->getAuthor() == sng->getAuthor())) {
            return;
        }
    }
    songs_.push_back(sng);
}

void LocalSongRepository::addTrendingSong(shared_ptr<Song> sng) {
    if (!sng) return;
    for (auto ptr = trends_.begin(); ptr != trends_.end(); ptr++) {
        if (((*ptr)->getName() == sng->getName()) && ((*ptr)->getAuthor() == sng->getAuthor())) {
            return;
        }
    }
    trends_.push_back(sng);
    addSong(sng);
}


std::vector<std::shared_ptr<Song>> LocalSongRepository::getTrendingSongs() {return trends_;};
std::vector<std::shared_ptr<Song>> LocalSongRepository::getSongs() {return songs_;};



shared_ptr<Song> LocalSongRepository::findSong(const string& songName) {
    for (const auto& s : songs_) {
        if (s->getName() == songName) return s;
    }
    return {};
}

shared_ptr<Song> LocalSongRepository::findSong(int songId) {
    for (const auto& s : songs_) {
        if (s->getId() == songId) return s;
    }
    return {};
}
