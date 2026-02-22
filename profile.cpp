#include "profile.h"

#include <iostream>

#include "server.h"
#include "song.h"
using namespace std;

Profile::Profile(bool authStatus) : isAuthenticated(authStatus) {
    userId = Count++;
};

vector<Song*> Profile::getRecs() {
    return vector<Song*>(recs.begin(), recs.end());
};

std::vector<Song*> Profile::getLikedSongs() { return likedSongs; };
int Profile::getId() { return userId; };
int Profile::getAuthStatus() { return isAuthenticated; };
int Profile::Count = 0;