#pragma once

#include "interface/IRecommendationStrategy.h"

class ArtistRecommendationStrategy : public IRecommendationStrategy {
   public:
    std::vector<std::shared_ptr<Song>> generateRecommendations(std::shared_ptr<ISongRepository> songs, std::shared_ptr<User> user) const override;
};