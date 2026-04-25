#pragma once

#include "interface/IRecommendationService.h"

class GenreRecommendationService : public IRecommendationService{
public:
    std::vector<std::shared_ptr<Song>> generateRecommendations(std::shared_ptr<ISongRepository> songs, std::shared_ptr<User> user) const override;
};