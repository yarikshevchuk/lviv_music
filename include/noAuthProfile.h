#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "interface/IHasTrends.h"
#include "profile.h"

class Server;
class Song;
class NoAuthProfile : public Profile, public IHasTrends {
   private:
    std::vector<Song*> trends;

   public:
    NoAuthProfile();
    virtual void setTrends(std::vector<Song*> trending) override;
    virtual std::vector<Song*> getTrends() override;
};