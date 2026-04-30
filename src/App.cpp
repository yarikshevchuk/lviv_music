#include "../include/app.h"

#include <iostream>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "../include/Song.h"
#include "../include/interface/IAuthService.h"

App::App(std::shared_ptr<IAuthService> auth, std::shared_ptr<ISongRepository> songs, std::shared_ptr<IRecommendationService> recs) : auth_(std::move(auth)), songs_(std::move(songs)), recs_(std::move(recs)) {}

int App::run() {
    if (songs_ == nullptr) {
        std::cout << "Song repository is not configured.\n";
        return 1;
    }

    // Songs are created manually for now, but stored inside the injected repository.
    songs_->addSong(std::make_shared<Song>("You're my heart, you're my soul", "Modern Talking", std::set<std::string>{"Eurodisco"}));
    songs_->addSong(std::make_shared<Song>("Cheri Cheri Lady", "Modern Talking", std::set<std::string>{"Eurodisco"}));
    songs_->addSong(std::make_shared<Song>("Self Control", "Laura Branigan", std::set<std::string>{"Eurodisco"}));
    songs_->addSong(std::make_shared<Song>("The Diary of Jane", "Breaking Benjamin", std::set<std::string>{"Rock", "Nu-Metal"}));
    songs_->addTrendingSong(std::make_shared<Song>("Can You Feel My Heart", "BMTH", std::set<std::string>{"Rock", "Nu-Metal"}));
    songs_->addTrendingSong(std::make_shared<Song>("Before I Forget", "Slipknot", std::set<std::string>{"Nu-Metal"}));

    // Likes are kept in-memory (simplest possible UI for now).
    std::set<int> likedSongIds;

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
        std::vector<std::shared_ptr<Song>> out;
        for (const auto& s : songs_->getSongs()) {
            if (likedSongIds.count(s->getId()) != 0) {
                out.push_back(s);
            }
        }
        return out;
    };

    auto showSong = [&](const std::vector<std::shared_ptr<Song>>& list, size_t startIndex) {
        if (list.empty()) {
            return;
        }

        size_t idx = startIndex;
        while (true) {
            const auto& s = list[idx];
            const bool isLiked = likedSongIds.count(s->getId()) != 0;

            std::cout << "\n=== Song ===\n";
            std::cout << "Name:   " << s->getName() << "\n";
            std::cout << "Author: " << s->getAuthor() << "\n";
            std::cout << "Rating: " << s->getRating() << "\n";
            std::cout << "Liked:  " << (isLiked ? "yes" : "no") << "\n";
            std::cout << "\n";
            std::cout << "[1] Like/Unlike\n";
            std::cout << "[2] Play next song\n";
            std::cout << "[0] Back to main menu\n";
            std::cout << "Choose: ";

            const int action = readInt(0, 2);
            if (action == 0) {
                return;
            }
            if (action == 1) {
                if (isLiked) {
                    likedSongIds.erase(s->getId());
                } else {
                    likedSongIds.insert(s->getId());
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

    // === AUTH menu ===
    if (auth_ == nullptr) {
        std::cout << "Auth service is not configured.\n";
        return 1;
    }

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
        std::cout << "[1] Trends\n";
        std::cout << "[2] All songs\n";
        std::cout << "[3] Liked songs\n";
        std::cout << "[0] Logout & Exit\n";
        std::cout << "Choose: ";

        const int choice = readInt(0, 3);
        if (choice == 0) {
            auth_->logout();
            return 0;
        }
        if (choice == 1) {
            showSongList("Trends", songs_->getTrendingSongs());
        } else if (choice == 2) {
            showSongList("All songs", songs_->getSongs());
        } else if (choice == 3) {
            showSongList("Liked songs", getLikedSongs());
        }
    }
}
