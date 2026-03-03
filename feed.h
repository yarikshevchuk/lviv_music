#pragma once

#include <vector>

class Song;
class Server;
class Profile;

class Feed {
   private:
    void printSongs(std::vector<Song*>& songs);

   public:
    void displayTitle(Server& server, Profile* user);
    void displayTrends(Server& server, Profile* user);
    void displayRecs(Server& server, Profile* user);
    void displayLiked(Server& server, Profile* user);
    void displayPlaylists(Server& server, Profile* user);
};