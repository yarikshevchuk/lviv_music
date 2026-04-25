#include "../include/User.h"

#include <utility>

using namespace std;

User::User() {};
void User::grantListenerAccess(std::unique_ptr<ILikesSongs> likes, std::unique_ptr<IHasPlaylists> playlists, std::unique_ptr<IHasRecs> recs, std::unique_ptr<IIdentity> identity) {
    likes_ = std::move(likes);
    playlists_ = std::move(playlists);
    recs_ = std::move(recs);
    identity_ = std::move(identity);

    isAuthenticated = true;
}

void User::logoutToGuest() {
    likes_.reset();
    playlists_.reset();
    recs_.reset();
    publisher_.reset();
    identity_.reset();
    isAuthenticated = false;
}

void User::grantArtistAccess(std::unique_ptr<IPublishesSongs> pubilsher) { publisher_ = std::move(pubilsher); }

ILikesSongs* User::likes() { return likes_.get(); }
IHasPlaylists* User::playlists() { return playlists_.get(); }
IHasRecs* User::recs() { return recs_.get(); }
IPublishesSongs* User::publisher() { return publisher_.get(); }
IIdentity* User::identity() { return identity_.get(); }

bool User::getAuthStatus() { return isAuthenticated; };