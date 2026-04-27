#include "../include/app.h"

#include <iostream>
#include <memory>
#include <set>
#include <string>


#include "../include/ListenerHasPlaylists.h"
#include "../include/ListenerHasRecs.h"
#include "../include/ListenerHasTrends.h"
#include "../include/ListenerIdentity.h"
#include "../include/ListenerLikesSongs.h"
#include "../include/Song.h"
#include "../include/User.h"
#include "../include/Feed.h"
#include "../include/interface/IAuthService.h"
#include "../include/interface/IRecommendationService.h"
#include "../include/interface/ISongRepository.h"
#include "../include/playlist.h"

App::App(Feed& feed, std::shared_ptr<IAuthService> auth, std::shared_ptr<ISongRepository> songs, std::shared_ptr<IRecommendationService> recs) : feed_(feed), auth_(std::move(auth)), songs_(std::move(songs)), recs_(std::move(recs)) {}

int App::run() {
    if (auth_) {
        std::cout << "auth ok? " << (auth_->login("user1", "user1") ? "true" : "false") << "\n";
        std::cout << "auth ok? " << (auth_->login("user1", "wrong") ? "true" : "false") << "\n";
    }

    auto s1 = std::make_shared<Song>("You're my heart, you're my soul", "Modern Talking ", std::set<std::string>{"Eurodisco"});
    auto s2 = std::make_shared<Song>("Cheri Cheri Lady", "Modern Talking", std::set<std::string>{"Eurodisco"});
    auto s3 = std::make_shared<Song>("Self Control", "Laura Branigan", std::set<std::string>{"Eurodisco"});
    auto s4 = std::make_shared<Song>("The Diary of Jane", "Breaking Benjamin ", std::set<std::string>{"Rock", "Nu-Metal"});
    auto s5 = std::make_shared<Song>("In the end", "Linkin Park", std::set<std::string>{"Rock", "Nu-Metal"});
    auto s6 = std::make_shared<Song>("Somewhere I Belong", "Linkin Park", std::set<std::string>{"Rock", "Nu-Metal"});

    auto t1 = std::make_shared<Song>("Can You Feel My Heart", "BMTH", std::set<std::string>{"Rock", "Nu-Metal"});
    auto t2 = std::make_shared<Song>("Before I Forget", "Slipknot", std::set<std::string>{"Nu-Metal"});

    songs_->addSong(s1);
    songs_->addSong(s2);
    songs_->addSong(s3);
    songs_->addSong(s4);
    songs_->addSong(s5);
    songs_->addSong(s6);

    songs_->addTrendingSong(t1);
    songs_->addTrendingSong(t2);

    std::shared_ptr<User> user1 = std::make_shared<User>();
    std::shared_ptr<User> user2 = std::make_shared<User>();

    user2->grantListenerAccess(std::make_unique<ListenerLikesSongs>(), std::make_unique<ListenerHasPlaylists>(), std::make_unique<ListenerHasRecs>(), std::make_unique<ListenerIdentity>("user1", "user1@gmail.com", 1, 18));

    if (auto* user_likes = user1->likes()) {
        user_likes->likeSong(songs_, "Cheri Cheri Lady");
    }
    if (auto* user_likes = user2->likes()) {
        user_likes->likeSong(songs_, "Cheri Cheri Lady");
    }

    if (auto* user_likes = user2->likes()) {
        user_likes->likeSong(songs_, "In the end");
    }
    if (auto* user_likes = user2->likes()) {
        user_likes->likeSong(songs_, 5);  // "Somewhere I Belong" id
    }

    auto p1 = std::make_shared<Playlist>("My first playlist", "My collection of good songs.");
    auto p2 = std::make_shared<Playlist>("My second playlist", "Songs for a hard workout.");

    if (auto* user_playlists = user2->playlists()) {
        user_playlists->addPlaylist(p1);
        user_playlists->addPlaylist(p2);
    }

    p1->addSong(s1);
    p1->addSong(s2);
    p1->addSong(s3);

    p2->addSong(s4);
    p2->addSong(s6);

    feed_.displayTitle(user1);
    feed_.displayTrends(songs_);
    feed_.displayPlaylists(user1);

    std::vector<std::shared_ptr<Song>> recs2 = recs_->generateRecommendations(songs_, user2);

    if (auto* user_recs = user2->recs()) {
        user2->recs()->setRecs(recs2);
    }

    feed_.displayTitle(user2);
    feed_.displayRecs(user2);
    feed_.displayLiked(user2);
    feed_.displayPlaylists(user2);
    feed_.displayTrends(songs_);

    return 0;
}
