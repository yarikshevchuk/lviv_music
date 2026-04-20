#pragma once
#include <vector>

class Song;

class IHasTrends {
   public:
    virtual ~IHasTrends() = default;

    virtual void setTrends(std::vector<Song*> trending) = 0;
    virtual std::vector<Song*> getTrends() = 0;
};