#include "authProfile.h"

#include <iostream>
#include <map>

#include "playlist.h"
#include "server.h"
#include "song.h"
using namespace std;

AuthProfile::AuthProfile(string username, string password, int age) : Profile(true), username(username), password(password), age(age), primaryGenre("none") {}

string AuthProfile::updatePrimaryGenre() {
    map<string, int> genres;
    string newGenre;
    int mostCommon = 0;

    if (likedSongs.size() == 0) {
        return "none";
    }
    for (Song* song : likedSongs) {
        for (string genre : song->getGenres()) {
            if (genres.find(genre) == genres.end()) {
                genres.insert({genre, 1});
            } else {
                genres[genre] += 1;
            }
        }
    }
    for (auto ptr = genres.begin(); ptr != genres.end(); ptr++) {
        if (ptr->second > mostCommon) {
            mostCommon = ptr->second;
            newGenre = ptr->first;
        }
    }
    primaryGenre = newGenre;
    return primaryGenre;
}

void AuthProfile::setRecs(vector<Song*> allSongs) {
    if (likedSongs.size() == 0) return;
    if (primaryGenre == "none") {
        updatePrimaryGenre();
    }

    for (Song* song : allSongs) {
        if (song->hasGenre(primaryGenre)) {
            recs.insert(song);
        }
    }
}

void AuthProfile::likeSong(Server& server, const string& songName) {
    Song* likedSong = server.findSong(songName);
    if (likedSong == nullptr) {
        return;
    }

    for (Song* sng : likedSongs) {
        if (sng->getName() == likedSong->getName()) {
            return;
        }
    }
    cout << "@" << username << " liked a song " << likedSong->getName() << "\n";

    likedSongs.push_back(likedSong);
    likedSong->updateRating(1);
    updatePrimaryGenre();
    setRecs(server.getAllSongs());
}
void AuthProfile::likeSong(Server& server, int songId) {
    Song* likedSong = server.findSong(songId);
    if (likedSong == nullptr) {
        return;
    }

    for (Song* sng : likedSongs) {
        if (sng->getName() == likedSong->getName()) {
            return;
        }
    }
    cout << "@" << username << " liked a song " << likedSong->getName() << "\n";

    likedSongs.push_back(likedSong);
    likedSong->updateRating(1);
    updatePrimaryGenre();
    setRecs(server.getAllSongs());
}

void AuthProfile::addPlaylist(Playlist* playlist) { playlists.push_back(playlist); };
void AuthProfile::removePlaylist(Playlist* playlist) {
    for (int i = 0; i < playlists.size(); i++) {
        if (playlist->getId() == playlists[i]->getId()) {
            delete playlists[i];
            playlists.erase(playlists.begin() + i);
        }
    }
};