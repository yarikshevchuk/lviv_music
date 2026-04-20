#include "../include/feed.h"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>

#include "../include/User.h"
#include "../include/interface/IHasPlaylists.h"
#include "../include/interface/IHasRecs.h"
#include "../include/interface/IIdentity.h"
#include "../include/interface/ILikesSongs.h"
#include "../include/playlist.h"
#include "../include/server.h"
#include "../include/song.h"
using namespace std;

void Feed ::printSongs(vector<Song*>& songs) {
    for (Song* sng : songs) {
        string wrapp = "||";
        int width = static_cast<int>(max(sng->getName().size(), sng->getAuthor().size() + 8U) + 1U);
        for (int i = 0; i < width; i++) {
            wrapp += "=";
        }
        wrapp += "||\n";

        cout << wrapp;
        cout << left << "||" << setw(width) << sng->getName() << "||\n";
        cout << left << "||" << setw(width - 8 - 1) << sng->getAuthor();
        cout << right << setw(8) << "Rating:" << sng->getRating() << "||\n";
        cout << wrapp << "\n";
    }
}

void Feed::displayTitle(Server&, User* user) {
    if (user != nullptr && user->getAuthStatus() && user->identity() != nullptr) {
        cout << "||@" << user->identity()->getUsername() << " feed:||\n";
        return;
    }

    cout << "||Anonymous user feed:||\n";
};

void Feed::displayTrends(Server& server, User*) {
    vector<Song*> trends = server.getTrendingSongs();

    cout << "||Trending songs:||\n";
    printSongs(trends);

    cout << "\n";
};
void Feed::displayRecs(Server&, User* user) {
    if (user == nullptr || !user->getAuthStatus() || user->recs() == nullptr) {
        cout << "\n";
        return;
    }

    vector<Song*> recs = user->recs()->getRecs();

    cout << "||Your recomendations:||\n";
    printSongs(recs);

    cout << "\n";
};
void Feed::displayLiked(Server&, User* user) {
    if (user == nullptr || !user->getAuthStatus() || user->likes() == nullptr) {
        cout << "\n";
        return;
    }

    vector<Song*> liked = user->likes()->getLikedSongs();

    cout << "||Liked Songs:||\n";
    printSongs(liked);

    cout << "\n";
};
void Feed::displayPlaylists(Server&, User* user) {
    if (user == nullptr || !user->getAuthStatus() || user->playlists() == nullptr) {
        return;
    }

    vector<Playlist*> playlists = user->playlists()->getPlaylists();

    cout << "||Playlists:||\n";

    if (playlists.size() == 0) {
        cout << "You do not have any playlists yet\n\n";
        return;
    }

    for (int i = 0; i < playlists.size(); i++) {
        vector<Song*> songs = playlists[i]->getSongs();

        cout << "" << playlists[i]->getName() << "\n";

        if (playlists[i]->getDescription() != "") {
            cout << "Description: " << playlists[i]->getDescription() << "\n";
        }

        if (songs.size() == 0) {
            cout << "This playlist is empty\n";
            continue;
        }

        printSongs(songs);
    }

    cout << "\n";
};