#pragma once
#include <memory>
#include <vector>

class Playlist;

class IHasPlaylists {
   public:
    virtual ~IHasPlaylists() = default;

    virtual void addPlaylist(std::shared_ptr<Playlist> playlist) = 0;
    virtual void removePlaylist(int playlistId) = 0;
    virtual std::vector<std::shared_ptr<Playlist>> getPlaylists() = 0;
};