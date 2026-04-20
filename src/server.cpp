#include "../include/server.h"

#include <memory>

#include "../include/song.h"

using namespace std;

vector<shared_ptr<Song>> Server::getTrendingSongs() { return trendingSongs; }
vector<shared_ptr<Song>> Server::getAllSongs() { return allSongs; }
void Server::setTrendingSongs(vector<shared_ptr<Song>> sngs) { trendingSongs = std::move(sngs); }

void Server::addTrendingSong(shared_ptr<Song> sng) {
    if (!sng) return;
    for (auto ptr = trendingSongs.begin(); ptr != trendingSongs.end(); ptr++) {
        if ((*ptr)->getName() == sng->getName()) {
            return;
        }
    }
    trendingSongs.push_back(sng);
    addSong(sng);
}

void Server::addSong(shared_ptr<Song> sng) {
    if (!sng) return;
    for (const auto& s : allSongs) {
        if (s->getName() == sng->getName()) {
            return;
        }
    }
    allSongs.push_back(sng);
}

shared_ptr<Song> Server::findSong(const string& songName) {
    for (const auto& s : allSongs) {
        if (s->getName() == songName) return s;
    }
    return {};
}

shared_ptr<Song> Server::findSong(int songId) {
    for (const auto& s : allSongs) {
        if (s->getId() == songId) return s;
    }
    return {};
}