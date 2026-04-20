#pragma once
#include <string>
#include <vector>

#include "interface/IHasPlaylists.h"
#include "interface/IHasRecs.h"
#include "interface/IHasTrends.h"
#include "interface/IIdentity.h"
#include "interface/ILikesSongs.h"

class Song;
class Server;
class Playlist;

class AuthProfile : public ILikesSongs, public IHasPlaylists, public IIdentity, public IHasRecs, public IHasTrends {
   private:
    std::vector<Song*> likedSongs;
    std::vector<Playlist*> playlists;
    std::set<Song*> recs;
    std::vector<Song*> trends;

    std::string username;
    std::string password;
    std::string primaryGenre;
    int age;

    std::string updatePrimaryGenre();

   public:
    AuthProfile(std::string username, std::string password, int age);

    virtual void setTrends(std::vector<Song*> trending) override;
    virtual std::vector<Song*> getTrends() override;

    std::string getUsername() override;
    int getAge() override;
};