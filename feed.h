#pragma once

#include <vector>

class Song;
class Server;
class Profile;

class Feed {
    void printSongs(std::vector<Song*>& songs);

   public:
    void displayUserFeed(Server& server, Profile* user);
};