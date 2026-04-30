#include "../include/Feed.h"

#include <iomanip>
#include <iostream>
#include <memory>
#include <string>

#include "../include/User.h"
#include "../include/interface/IHasPlaylists.h"
#include "../include/interface/IHasRecs.h"
#include "../include/interface/IIdentity.h"
#include "../include/interface/ILikesSongs.h"
#include "../include/Playlist.h"
#include "../include/Song.h"
using namespace std;

void Feed ::printSongs(vector<shared_ptr<Song>>& songs) {
    for (const auto& sng : songs) {
        if (!sng) continue;
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

void Feed::displayTitle(std::shared_ptr<User> user) {
    if (user != nullptr && user->getAuthStatus() && user->identity() != nullptr) {
        cout << "||@" << user->identity()->getUsername() << " feed:||\n";
        return;
    }

    cout << "||Anonymous user feed:||\n";
};

void Feed::displayTrends(std::shared_ptr<ISongRepository> songs) {
    vector<shared_ptr<Song>> trends = songs->getTrendingSongs();

    cout << "||Trending songs:||\n";
    printSongs(trends);

    cout << "\n";
};
void Feed::displayRecs(std::shared_ptr<User> user) {
    if (user == nullptr || !user->getAuthStatus() || user->recs() == nullptr) {
        return;
    }

    vector<shared_ptr<Song>> recs = user->recs()->getRecs();

    cout << "||Your recomendations:||\n";
    printSongs(recs);

    cout << "\n";
};
void Feed::displayLiked(std::shared_ptr<User> user) {
    if (user == nullptr || !user->getAuthStatus() || user->likes() == nullptr) {
        return;
    }

    vector<shared_ptr<Song>> liked = user->likes()->getLikedSongs();

    cout << "||Liked Songs:||\n";
    printSongs(liked);

    cout << "\n";
};
void Feed::displayPlaylists(std::shared_ptr<User> user) {
    if (user == nullptr || !user->getAuthStatus() || user->playlists() == nullptr) {
        return;
    }

    vector<shared_ptr<Playlist>> playlists = user->playlists()->getPlaylists();

    cout << "||Playlists:||\n";

    if (playlists.size() == 0) {
        cout << "You do not have any playlists yet\n\n";
        return;
    }

    for (int i = 0; i < playlists.size(); i++) {
        vector<shared_ptr<Song>> songs = playlists[i]->getSongs();

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