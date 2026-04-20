#pragma once

#include "interface/IHasRecs.h"

class ListenerHasRecs : public IHasRecs {
   private:
    std::vector<Song*> recs_;

   public:
    void setRecs(std::vector<Song*> trending) override;
    std::vector<Song*> getRecs() override;
};