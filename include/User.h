#pragma once
#include <memory>
#include <set>
#include <string>
#include <vector>

#include "interface/IHasPlaylists.h"
#include "interface/IHasRecs.h"
#include "interface/IIdentity.h"
#include "interface/ILikesSongs.h"
#include "interface/IPublishesSongs.h"

class ISongRepository;
class Playlist;

class User {
   private:
    bool isAuthenticated{false};

    std::unique_ptr<ILikesSongs> likes_;
    std::unique_ptr<IHasPlaylists> playlists_;
    std::unique_ptr<IHasRecs> recs_;
    std::unique_ptr<IPublishesSongs> publisher_;
    std::unique_ptr<IIdentity> identity_;

   public:
    explicit User();

    bool getAuthStatus();

    void grantListenerAccess(std::unique_ptr<ILikesSongs> likes, std::unique_ptr<IHasPlaylists> playlists, std::unique_ptr<IHasRecs> recs, std::unique_ptr<IIdentity> identity);
    void grantArtistAccess(std::unique_ptr<IPublishesSongs> publisher);

    ILikesSongs* likes();
    IHasPlaylists* playlists();
    IHasRecs* recs();
    IPublishesSongs* publisher();
    IIdentity* identity();

    void listen(std::shared_ptr<ISongRepository> songs, int songId);
    void listenPlaylist(std::shared_ptr<ISongRepository> songs, const std::shared_ptr<Playlist>& playlist);

    void logoutToGuest();
};
