#pragma once
#include <memory>
#include "interface/IHasPlaylists.h"

class Playlist;

class ListenerHasPlaylists : public IHasPlaylists {
   private:
    std::vector<std::shared_ptr<Playlist>> playlists_;

   public:
    void addPlaylist(std::shared_ptr<Playlist> playlist) override;
    void removePlaylist(int playlistId) override;
    std::vector<std::shared_ptr<Playlist>> getPlaylists() override;
};