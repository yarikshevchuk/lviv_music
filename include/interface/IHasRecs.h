#pragma once
#include <memory>
#include <vector>

class Song;

class IHasRecs {
   public:
    virtual ~IHasRecs() = default;

    virtual void setRecs(std::vector<std::shared_ptr<Song>> trending) = 0;
    virtual std::vector<std::shared_ptr<Song>> getRecs() = 0;
};