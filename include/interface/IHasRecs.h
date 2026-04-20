#pragma once
#include <vector>

class Song;

class IHasRecs {
   public:
    virtual ~IHasRecs() = default;

    virtual void setRecs(std::vector<Song*> trending) = 0;
    virtual std::vector<Song*> getRecs() = 0;
};