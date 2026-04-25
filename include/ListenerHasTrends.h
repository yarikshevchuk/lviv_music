#pragma once

#include "interface/IHasTrends.h"

class Song;

class ListenerHasTrends: public IHasTrends {
   private:
    std::vector<std::shared_ptr<Song>> trends_;

   public:
    void setTrends(std::vector<std::shared_ptr<Song>> trending) override;
    std::vector<std::shared_ptr<Song>> getTrends() override;
}; 