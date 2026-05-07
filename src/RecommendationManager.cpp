#include "../include/RecommendationManager.h"

RecommendationManager::RecommendationManager(std::shared_ptr<IRecommendationStrategy> strategy) : currentStrategy_(std::move(strategy)) {}

void RecommendationManager::setStrategy(std::shared_ptr<IRecommendationStrategy> strategy) { currentStrategy_ = strategy; };

std::vector<std::shared_ptr<Song>> RecommendationManager::getRecommendations(std::shared_ptr<ISongRepository> songs, std::shared_ptr<User> user) const {
    if (!currentStrategy_) return {};
    return currentStrategy_->generateRecommendations(songs, user);
};