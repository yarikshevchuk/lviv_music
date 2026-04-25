#pragma once
#include <memory>

#include "boost/di.hpp"
#include "interface/IRecommendationService.h"
#include "interface/ISongRepository.h"
#include "interface/IAuthService.h"

class Feed;
class Server;

class App {
   private:
    Feed& feed_;
    std::shared_ptr<IAuthService> auth_;
    std::shared_ptr<ISongRepository> songs_;
    std::shared_ptr<IRecommendationService> recs_;

   public:
    App(Feed& feed, std::shared_ptr<IAuthService> auth, std::shared_ptr<ISongRepository> songs, std::shared_ptr<IRecommendationService> recs);
    int run();
};
