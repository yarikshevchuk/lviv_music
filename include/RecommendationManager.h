#include "../include/interface/IRecommendationManager.h"

class RecommendationManager : public IRecommendationManager {
   private:
    std::shared_ptr<IRecommendationStrategy> currentStrategy_;

   public:
    RecommendationManager() = default;
    explicit RecommendationManager(std::shared_ptr<IRecommendationStrategy> strategy);
    void setStrategy(std::shared_ptr<IRecommendationStrategy> strategy) override;
    std::vector<std::shared_ptr<Song>> getRecommendations(std::shared_ptr<ISongRepository> songs, std::shared_ptr<User> user) const override;
};