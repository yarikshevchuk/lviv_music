#include "../include/ListenerHasPlaylists.h"

#include <vector>

#include "../include/playlist.h"
using namespace std;

void ListenerHasPlaylists::addPlaylist(Playlist* playlist) { playlists_.push_back(playlist); };
void ListenerHasPlaylists::removePlaylist(Playlist* playlist) {
    for (int i = 0; i < playlists_.size(); i++) {
        if (playlist->getId() == playlists_[i]->getId()) {
            delete playlists_[i];
            playlists_.erase(playlists_.begin() + i);
        }
    }
};
vector<Playlist*> ListenerHasPlaylists::getPlaylists() { return playlists_; };