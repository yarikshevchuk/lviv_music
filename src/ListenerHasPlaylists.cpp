#include "../include/ListenerHasPlaylists.h"

#include <vector>
#include <memory>

#include "../include/Playlist.h"
using namespace std;

void ListenerHasPlaylists::addPlaylist(shared_ptr<Playlist> playlist) {
    if (!playlist) return;
    playlists_.push_back(std::move(playlist));
}
void ListenerHasPlaylists::removePlaylist(int playlistId) {
    for (int i = 0; i < playlists_.size(); i++) {
        if (playlistId == playlists_[i]->getId()) {
            playlists_.erase(playlists_.begin() + i);
            return;
        }
    }
};
vector<shared_ptr<Playlist>> ListenerHasPlaylists::getPlaylists() { return playlists_; };
