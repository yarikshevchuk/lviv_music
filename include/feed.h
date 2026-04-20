#pragma once

#include <memory>
#include <vector>

class Song;
class Server;
class User;

class Feed {
   private:
    void printSongs(std::vector<std::shared_ptr<Song>>& songs);

   public:
    void displayTitle(Server& server, User* user);
    void displayTrends(Server& server, User* user);
    void displayRecs(Server& server, User* user);
    void displayLiked(Server& server, User* user);
    void displayPlaylists(Server& server, User* user);
};