#include "../include/ServerSongRepository.h"
#include "../include/Song.h"
#include <vector>
#include <memory>

using namespace std;

void ServerSongRepository::addSong(std::shared_ptr<Song> sng) {
    if (!sng) return;
    for (const auto& s : songs_) {
        if (s->getName() == sng->getName()) {
            return;
        }
    }
    songs_.push_back(sng);
}

void ServerSongRepository::addTrendingSong(shared_ptr<Song> sng) {
    if (!sng) return;
    for (auto ptr = trends_.begin(); ptr != trends_.end(); ptr++) {
        if ((*ptr)->getName() == sng->getName()) {
            return;
        }
    }
    trends_.push_back(sng);
    addSong(sng);
}


std::vector<std::shared_ptr<Song>> ServerSongRepository::getTrendingSongs() {return trends_;};
std::vector<std::shared_ptr<Song>> ServerSongRepository::getSongs() {return songs_;};



shared_ptr<Song> ServerSongRepository::findSong(const string& songName) {
    for (const auto& s : songs_) {
        if (s->getName() == songName) return s;
    }
    return {};
}

shared_ptr<Song> ServerSongRepository::findSong(int songId) {
    for (const auto& s : songs_) {
        if (s->getId() == songId) return s;
    }
    return {};
}
