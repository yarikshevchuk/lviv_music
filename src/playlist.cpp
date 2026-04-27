#include "../include/Playlist.h"

#include <ctime>
using namespace std;

Playlist::Playlist(string nm, string descr) : name(nm), description(descr), playlistId(Count++), stats{0, 0, ""} {};

void Playlist::updateTime() {
    time_t tt;
    struct tm* ti;
    time(&tt);
    ti = localtime(&tt);

    stats.lastUpdated = asctime(ti);
}
void Playlist::updateDuration(const shared_ptr<Song>& sng, int sign) {
    if (!sng) return;
    stats.totalDuration += sign * (sng->getDuration());
}

void Playlist::addSong(shared_ptr<Song> sng) {
    if (!sng) return;
    songs.push_back(std::move(sng));
    updateTime();
    updateDuration(songs.back(), 1);
}
void Playlist::deleteSong(const shared_ptr<Song>& sng) {
    if (!sng) return;
    for (int i = 0; i < songs.size(); i++) {
        if (songs[i]->getId() == sng->getId()) {
            songs.erase(songs.begin() + i);
            return;
        }
        updateTime();
        updateDuration(sng, -1);
    }
};

void Playlist::setName(std::string playlistName) { name = playlistName; };
void Playlist::setDescription(std::string descr) { description = descr; };

vector<shared_ptr<Song>> Playlist::getSongs() const { return songs; }
std::string Playlist::getName() const { return name; };
std::string Playlist::getDescription() const { return description; };
int Playlist::getId() const { return playlistId; }

int Playlist::getTotalDuration() const { return stats.totalDuration; }
int Playlist::getPlayCount() const { return stats.playCount; }
string Playlist::getLastUpdated() const { return stats.lastUpdated; }

int Playlist::Count = 0;