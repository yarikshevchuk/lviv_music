#include "../include/GenreRecommendationService.h"
#include "../include/Song.h"
#include "../include/User.h"
#include <map>

using namespace std;

std::vector<std::shared_ptr<Song>> GenreRecommendationService::generateRecommendations(std::shared_ptr<ISongRepository> songs, std::shared_ptr<User> user) const {
    std::vector<std::shared_ptr<Song>> recs;
    
    if(user == nullptr || !user->getAuthStatus() || user->likes() == nullptr || user->likes()->getLikedSongs().empty()) {
        return recs;
    }

    map<string, int> genres;
    string primaryGenre = "none";
    std::vector<std::shared_ptr<Song>> likedSongs = user->likes()->getLikedSongs();


    for (const auto &song : likedSongs) {
        for (string genre : song->getGenres()) {
            if (genres.find(genre) == genres.end()) {
                genres.insert({genre, 1});
            } else {
                genres[genre] += 1;
            }
        }
    }

    int mostCommon = 0;
    for (auto ptr = genres.begin(); ptr != genres.end(); ptr++) {
        if (ptr->second > mostCommon) {
            mostCommon = ptr->second;
            primaryGenre = ptr->first;
        }
    }

    if(primaryGenre == "none") {
        return recs;
    }

    for (auto const &song : songs->getSongs()) {
        if (song->hasGenre(primaryGenre)) {
            recs.push_back(song);
        }
    } 

    return recs;
}