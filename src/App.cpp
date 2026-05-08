#include "../include/app.h"

#include <iostream>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "../include/ListenerHasPlaylists.h"
#include "../include/ListenerHasRecs.h"
#include "../include/ListenerIdentity.h"
#include "../include/LoggerLikesSongs.h"
#include "../include/ListenerLikesSongs.h"
#include "../include/Song.h"
#include "../include/User.h"
#include "../include/ArtistRecommendationStrategy.h"
#include "../include/GenreRecommendationStrategy.h"
#include "../include/interface/IAuthService.h"

App::App(std::shared_ptr<IAuthService> auth, std::shared_ptr<ISongRepository> songs, std::shared_ptr<IRecommendationManager> recs) : auth_(std::move(auth)), songs_(std::move(songs)), recs_(std::move(recs)) {}

int App::run() {
    songs_->addSong(std::make_shared<Song>("You're my heart, you're my soul", "Modern Talking", std::set<std::string>{"Eurodisco"}));
    songs_->addSong(std::make_shared<Song>("Cheri Cheri Lady", "Modern Talking", std::set<std::string>{"Eurodisco"}));
    songs_->addSong(std::make_shared<Song>("Self Control", "Laura Branigan", std::set<std::string>{"Eurodisco"}));
    songs_->addSong(std::make_shared<Song>("The Diary of Jane", "Breaking Benjamin", std::set<std::string>{"Rock", "Nu-Metal"}));
    songs_->addSong(std::make_shared<Song>("So Cold", "Breaking Benjamin", std::set<std::string>{"Nu-Metal"}));
    songs_->addSong(std::make_shared<Song>("I Will Not Bow", "Breaking Benjamin", std::set<std::string>{"Nu-Metal"}));
    songs_->addSong(std::make_shared<Song>("Can You Feel My Heart", "BMTH", std::set<std::string>{"Rock", "Nu-Metal"}));
    songs_->addSong(std::make_shared<Song>("Before I Forget", "Slipknot", std::set<std::string>{"Nu-Metal"}));

    auto readLine = []() -> std::string {
        std::string s;
        std::getline(std::cin, s);
        return s;
    };

    auto readInt = [&](int minVal, int maxVal) -> int {
        while (true) {
            std::string s = readLine();
            std::stringstream ss(s);
            int v = 0;
            if ((ss >> v) && !(ss >> s) && v >= minVal && v <= maxVal) {
                return v;
            }
            std::cout << "Enter a number [" << minVal << ".." << maxVal << "]: ";
        }
    };

    auto getLikedSongs = [&]() -> std::vector<std::shared_ptr<Song>> {
        if (currentUser_ == nullptr || currentUser_->likes() == nullptr) {
            return {};
        }
        return currentUser_->likes()->getLikedSongs();
    };

    auto showSong = [&](const std::vector<std::shared_ptr<Song>>& list, size_t startIndex) {
        if (list.empty()) {
            return;
        }

        size_t idx = startIndex;
        while (true) {
            const auto& s = list[idx];
            bool isLiked = false;
            for (const auto& liked : getLikedSongs()) {
                if (liked && liked->getId() == s->getId()) {
                    isLiked = true;
                    break;
                }
            }

            std::cout << "\n=== Song ===\n";
            std::cout << "Name:   " << s->getName() << "\n";
            std::cout << "Author: " << s->getAuthor() << "\n";
            std::cout << "Rating: " << s->getRating() << "\n";
            std::cout << "Liked:  " << (isLiked ? "yes" : "no") << "\n";
            std::cout << "\n";
            std::cout << "[1] " << (isLiked ? "Unlike" : "Like") << "\n";
            std::cout << "[2] Play next song\n";
            std::cout << "[0] Back to main menu\n";
            std::cout << "Choose: ";

            const int action = readInt(0, 2);
            if (action == 0) {
                return;
            }
            if (action == 1) {
                if (currentUser_ != nullptr && currentUser_->likes() != nullptr) {
                    if (isLiked) {
                        currentUser_->likes()->unlikeSong(songs_, s->getId());
                    } else {
                        currentUser_->likes()->likeSong(songs_, s->getId());
                    }
                }
                continue;
            }
            if (action == 2) {
                idx = (idx + 1) % list.size();
                continue;
            }
        }
    };

    auto showSongList = [&](const std::string& title, const std::vector<std::shared_ptr<Song>>& list) {
        std::cout << "\n=== " << title << " ===\n";
        if (list.empty()) {
            std::cout << "(empty)\n";
            return;
        }

        for (size_t i = 0; i < list.size(); ++i) {
            std::cout << (i + 1) << ") " << list[i]->getName() << " - " << list[i]->getAuthor() << "\n";
        }
        std::cout << "0) Back\n";
        std::cout << "Choose song number: ";
        const int choice = readInt(0, static_cast<int>(list.size()));
        if (choice == 0) {
            return;
        }
        showSong(list, static_cast<size_t>(choice - 1));
    };

    auto openSettings = [&]() {
        if (recs_ == nullptr) {
            std::cout << "Settings are not configured.\n";
            return;
        }

        while (true) {
            std::cout << "\n=== Settings ===\n";
            std::cout << "Recommendation strategy:\n";
            std::cout << "[1] Genre (default)\n";
            std::cout << "[2] Artist\n";
            std::cout << "[0] Back\n";
            std::cout << "Choose: ";

            const int choice = readInt(0, 2);
            if (choice == 0) {
                return;
            }
            if (choice == 1) {
                recs_->setStrategy(std::make_shared<GenreRecommendationStrategy>());
                std::cout << "Switched to Genre strategy.\n";
            } else if (choice == 2) {
                recs_->setStrategy(std::make_shared<ArtistRecommendationStrategy>());
                std::cout << "Switched to Artist strategy.\n";
            }
        }
    };

    // === AUTH menu ===

    while (!auth_->isAuthenticated()) {
        std::cout << "\n=== Auth ===\n";
        std::cout << "[1] Login\n";
        std::cout << "[2] Register\n";
        std::cout << "[0] Exit\n";
        std::cout << "Choose: ";
        const int choice = readInt(0, 2);
        if (choice == 0) {
            return 0;
        }

        std::cout << "Username: ";
        const std::string username = readLine();
        std::cout << "Password: ";
        const std::string password = readLine();

        if (choice == 1) {
            if (!auth_->login(username, password)) {
                std::cout << "Login failed.\n";
            } else {
                currentUser_ = std::make_shared<User>();
                currentUser_->grantListenerAccess(std::make_unique<LoggerLikesSongs>(std::make_unique<ListenerLikesSongs>()), std::make_unique<ListenerHasPlaylists>(), std::make_unique<ListenerHasRecs>(), std::make_unique<ListenerIdentity>(auth_->getUsername(), "", 0, 0));
            }
        } else if (choice == 2) {
            if (!auth_->registerUser(username, password)) {
                std::cout << "Register failed.\n";
            } else {
                std::cout << "Registered.\n";
            }
        }
    }

    // === HOME menu ===
    while (true) {
        std::cout << "\n=== Home (" << auth_->getUsername() << ") ===\n";
        std::cout << "[1] All songs\n";
        std::cout << "[2] Liked songs\n";
        std::cout << "[3] Recommendations\n";
        std::cout << "[4] Settings\n";
        std::cout << "[0] Logout & Exit\n";
        std::cout << "Choose: ";

        const int choice = readInt(0, 4);
        if (choice == 0) {
            auth_->logout();
            currentUser_.reset();
            return 0;
        }
        if (choice == 1) {
            showSongList("All songs", songs_->getSongs());
        } else if (choice == 2) {
            showSongList("Liked songs", getLikedSongs());
        } else if (choice == 3) {
            currentUser_->recs()->setRecs(recs_->getRecommendations(songs_, currentUser_));
            showSongList("Recommendations", currentUser_->recs()->getRecs());
        } else if (choice == 4) {
            openSettings();
        }
    }
}
