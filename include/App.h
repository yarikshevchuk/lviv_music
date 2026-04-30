#pragma once
#include <memory>

#include "boost/di.hpp"
#include "interface/IRecommendationService.h"
#include "interface/ISongRepository.h"
#include "interface/IAuthService.h"

class Server;
class User;

class App {
   private:
    std::shared_ptr<IAuthService> auth_;
    std::shared_ptr<ISongRepository> songs_;
    std::shared_ptr<IRecommendationService> recs_;
    std::shared_ptr<User> currentUser_;

   public:
    App(std::shared_ptr<IAuthService> auth, std::shared_ptr<ISongRepository> songs, std::shared_ptr<IRecommendationService> recs);
    int run();
};
