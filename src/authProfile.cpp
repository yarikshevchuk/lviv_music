#include "../include/authProfile.h"

#include <iostream>
#include <map>

#include "../include/playlist.h"
#include "../include/server.h"
#include "../include/song.h"
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



void AuthProfile::addPlaylist(Playlist* playlist) { playlists.push_back(playlist); };
void AuthProfile::removePlaylist(Playlist* playlist) {
    for (int i = 0; i < playlists.size(); i++) {
        if (playlist->getId() == playlists[i]->getId()) {
            delete playlists[i];
            playlists.erase(playlists.begin() + i);
        }
    }
};
vector<Playlist*> AuthProfile::getPlaylists() { return playlists; };

void AuthProfile::setTrends(vector<Song*> trending) { trends = trending; };
std::vector<Song*> AuthProfile::getTrends() { return trends; };

string AuthProfile::getUsername() { return username; };
int AuthProfile::getAge() { return age; };