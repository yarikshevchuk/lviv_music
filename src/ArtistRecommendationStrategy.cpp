#include "../include/ArtistRecommendationStrategy.h"

#include <map>

#include "../include/Song.h"
#include "../include/User.h"

using namespace std;

std::vector<std::shared_ptr<Song>> ArtistRecommendationStrategy::generateRecommendations(std::shared_ptr<ISongRepository> songs, std::shared_ptr<User> user) const {
    std::vector<std::shared_ptr<Song>> recs;

    if (user == nullptr || !user->getAuthStatus() || user->likes() == nullptr || user->likes()->getLikedSongs().empty()) {
        return recs;
    }

    map<string, int> artists;
    string mainArtist = "none";
    std::vector<std::shared_ptr<Song>> likedSongs = user->likes()->getLikedSongs();

    for (const auto& song : likedSongs) {
        string author = song->getAuthor();
        if (artists.find(author) == artists.end()) {
            artists.insert({author, 1});
        } else {
            artists[author] += 1;
        }
    }

    int mostCommon = 0;
    for (auto ptr = artists.begin(); ptr != artists.end(); ptr++) {
        if (ptr->second > mostCommon) {
            mostCommon = ptr->second;
            mainArtist = ptr->first;
        }
    }

    if (mainArtist == "none") {
        return recs;
    }

    for (auto const& song : songs->getSongs()) {
        if (song->getAuthor() == mainArtist) {
            recs.push_back(song);
        }
    }

    return recs;
}