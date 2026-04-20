#pragma once
#include "interface/IHasPlaylists.h"

class Playlist;

class ListenerHasPlaylists : public IHasPlaylists {
   private:
    std::vector<Playlist*> playlists_;

   public:
    void addPlaylist(Playlist* playlist) override;
    void removePlaylist(Playlist* playlist) override;
    std::vector<Playlist*> getPlaylists() override;
};