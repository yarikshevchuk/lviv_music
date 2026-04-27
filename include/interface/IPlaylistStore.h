#pragma once
#include <memory>
#include <string>
#include <vector>

#include "../dto/StoredTypes.h"

class IPlaylistStore {
   public:
    virtual ~IPlaylistStore() = default;

    virtual int insertPlaylist(const DTO::PlaylistRow& playlist) = 0;
    virtual bool updatePlaylist(const DTO::PlaylistRow& playlist) = 0;
    virtual bool deletePlaylist(int id) = 0;

    virtual std::shared_ptr<DTO::PlaylistRow> getPlaylistById(int id) const = 0;
    virtual std::vector<DTO::PlaylistRow> listPlaylistsForUser(int user_id) const = 0;

    virtual bool addSongToPlaylist(int playlist_id, int song_id, int position) = 0;
    virtual bool removeSongFromPlaylist(int playlist_id, int song_id) = 0;
    virtual std::vector<int> listSongIdsInPlaylist(int playlist_id) const = 0;
};
