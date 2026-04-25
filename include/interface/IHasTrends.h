#pragma once
#include <memory>
#include <vector>

class Song;

class IHasTrends {
   public:
    virtual ~IHasTrends() = default;

    virtual void setTrends(std::vector<std::shared_ptr<Song>> trending) = 0;
    virtual std::vector<std::shared_ptr<Song>> getTrends() = 0;
};