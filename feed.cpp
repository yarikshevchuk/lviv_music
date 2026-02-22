#include "feed.h"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>

#include "profile.h"
#include "server.h"
#include "song.h"
using namespace std;

void Feed ::printSongs(vector<Song*>& songs) {
    for (Song* sng : songs) {
        string wrapp = "|";
        int width = max(sng->getName().size(), sng->getAuthor().size() + 8) + 1;
        for (int i = 0; i < width; i++) {
            wrapp += "=";
        }
        wrapp += "|\n";

        cout << wrapp;
        cout << left << "|" << setw(width) << sng->getName() << "|\n";
        cout << left << "|" << setw(width / 2 - 1) << sng->getAuthor();
        cout << right << setw(width / 2) << "Rating:" << sng->getRating()
             << "|\n";
        cout << wrapp << "\n";
    }
}

void Feed::displayUserFeed(Server& server, Profile* user) {
    vector<Song*> trends = server.getTrendingSongs();
    vector<Song*> recs = user->getRecs();
    vector<Song*> liked = user->getLikedSongs();

    if (user->getAuthStatus() == 1) {
        cout << "|@" << user->getUsername() << " feed:|\n";
    } else {
        cout << "|Anonymous user feed:|\n";
    }

    if (user->getAuthStatus() == 1) {
        cout << "|Your recomendations:|\n";
        printSongs(recs);
        cout << "|Liked Songs:|\n";
        printSongs(liked);
    }

    cout << "|Trending songs:|\n";
    printSongs(trends);

    cout << "\n";
}