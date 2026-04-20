#pragma once
#include <vector>

class Playlist;

class IHasPlaylists {
   public:
    virtual ~IHasPlaylists() = default;

    virtual void addPlaylist(Playlist* playlist) = 0;
    virtual void removePlaylist(Playlist* playlist) = 0;
    virtual std::vector<Playlist*> getPlaylists() = 0;
};