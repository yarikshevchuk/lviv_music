#include "profile.h"

#include <iostream>

#include "playlist.h"
#include "server.h"
#include "song.h"
using namespace std;

Profile::Profile(bool authStatus) : isAuthenticated(authStatus), userId(Count++) {};

vector<Song*> Profile::getRecs() { return vector<Song*>(recs.begin(), recs.end()); };

vector<Song*> Profile::getLikedSongs() { return likedSongs; };
vector<Playlist*> Profile::getPlaylists() { return playlists; };

int Profile::getId() { return userId; };
int Profile::getAuthStatus() { return isAuthenticated; };
int Profile::Count = 0;