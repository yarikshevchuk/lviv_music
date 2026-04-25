#pragma once

#include "interface/ISongRepository.h"
#include <memory>
#include <vector>

class Song;
class Server;
class User;

class Feed {
   private:
    void printSongs(std::vector<std::shared_ptr<Song>>& songs);

   public:
    void displayTitle(std::shared_ptr<User> user);
    void displayTrends(std::shared_ptr<ISongRepository> songs);
    void displayRecs(std::shared_ptr<User> user);
    void displayLiked(std::shared_ptr<User> user);
    void displayPlaylists(std::shared_ptr<User> user);
};