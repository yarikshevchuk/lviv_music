#pragma once
#include <memory>
#include <vector>

#include "./IRecommendationStrategy.h"

class IRecommendationManager {
   public:
    virtual ~IRecommendationManager() = default;
    virtual void setStrategy(std::shared_ptr<IRecommendationStrategy> strategy) = 0;
    virtual std::vector<std::shared_ptr<Song>> getRecommendations(std::shared_ptr<ISongRepository> songs, std::shared_ptr<User> user) const = 0;
};