#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "profile.h"

class Server;
class Song;
class NoAuthProfile : public Profile {
   public:
    NoAuthProfile();
    void setRecs(std::vector<Song*> trending) override;
    void likeSong(Server& server, const std::string& songName);
    void likeSong(Server& server, int songId) override;
    std::string getUsername() override;
};