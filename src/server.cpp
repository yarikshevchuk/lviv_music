#include "../include/server.h"

#include "../include/song.h"

using namespace std;

Server::~Server() {
    for (int i = 0; i < allSongs.size(); i++) {
        delete allSongs[i];
    }
};

vector<Song*> Server::getTrendingSongs() { return trendingSongs; }
vector<Song*> Server::getAllSongs() { return allSongs; }
void Server::setTrendingSongs(vector<Song*> sngs) { trendingSongs = sngs; }

void Server::addTrendingSong(Song* sng) {
    for (auto ptr = trendingSongs.begin(); ptr != trendingSongs.end(); ptr++) {
        if ((*ptr)->getName() == sng->getName()) {
            return;
        }
    }
    trendingSongs.push_back(sng);
    addSong(sng);
}

void Server::addSong(Song* sng) {
    for (Song* s : allSongs) {
        if (s->getName() == sng->getName()) {
            return;
        }
    }
    allSongs.push_back(sng);
}

Song* Server::findSong(string songName) {
    for (Song* s : allSongs) {
        if (s->getName() == songName) {
            return s;
        }
    }
    return nullptr;
}

Song* Server::findSong(int songId) {
    for (Song* s : allSongs) {
        if (s->getId() == songId) {
            return s;
        }
    }
    return nullptr;
}