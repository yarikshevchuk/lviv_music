#pragma once

#include "interface/IHasRecs.h"

class ListenerHasRecs : public IHasRecs {
   private:
    std::vector<std::shared_ptr<Song>> recs_;

   public:
    void setRecs(std::vector<std::shared_ptr<Song>> trending) override;
    std::vector<std::shared_ptr<Song>> getRecs() override;
}; 