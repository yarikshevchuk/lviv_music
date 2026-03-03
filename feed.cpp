#include "feed.h"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>

#include "playlist.h"
#include "profile.h"
#include "server.h"
#include "song.h"
using namespace std;

void Feed ::printSongs(vector<Song*>& songs) {
    for (Song* sng : songs) {
        string wrapp = "||";
        int width = max(sng->getName().size(), sng->getAuthor().size() + 8) + 1;
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

void Feed::displayTitle(Server& server, Profile* user) {
    if (user->getAuthStatus() == 1) {
        cout << "||@" << user->getUsername() << " feed:||\n";
    } else {
        cout << "||Anonymous user feed:||\n";
    }
};

void Feed::displayTrends(Server& server, Profile* user) {
    vector<Song*> trends = server.getTrendingSongs();

    cout << "||Trending songs:||\n";
    printSongs(trends);

    cout << "\n";
};
void Feed::displayRecs(Server& server, Profile* user) {
    vector<Song*> recs = user->getRecs();

    if (user->getAuthStatus() == 1) {
        cout << "||Your recomendations:||\n";
        printSongs(recs);
    }

    cout << "\n";
};
void Feed::displayLiked(Server& server, Profile* user) {
    vector<Song*> liked = user->getLikedSongs();

    if (user->getAuthStatus() == 1) {
        cout << "||Liked Songs:||\n";
        printSongs(liked);
    }

    cout << "\n";
};
void Feed::displayPlaylists(Server& server, Profile* user) {
    vector<Playlist*> playlists = user->getPlaylists();

    if (user->getAuthStatus() == 0) {
        return;
    }

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