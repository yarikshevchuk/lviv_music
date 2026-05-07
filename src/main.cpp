
#include "../include/App.h"
#include "../include/GenreRecommendationStrategy.h"
#include "../include/LocalSongRepository.h"
#include "../include/SQLAuthService.h"
#include "../include/boost/di.hpp"
#include "../include/dto/SqliteDatabase.h"
#include "../include/dto/SqliteUserStore.h"
#include "../include/interface/IAuthService.h"
#include "../include/interface/IRecommendationManager.h"
#include "../include/RecommendationManager.h"
#include "../include/interface/IRecommendationStrategy.h"
#include "../include/interface/ISongRepository.h"
#include "../include/interface/IUserStore.h"

int main() {
    auto db = std::make_shared<dto::SqliteDatabase>();
    db->open("lviv_music.db");

    auto userStore = std::make_shared<SqliteUserStore>(db);

    namespace di = boost::di;

    auto injector = di::make_injector(di::bind<ISongRepository>().to([] { return LocalSongRepository::getInstance(); }), 
        di::bind<IRecommendationStrategy>().to<GenreRecommendationStrategy>().in(di::singleton), 
        di::bind<IRecommendationManager>().to<RecommendationManager>().in(di::singleton),
        di::bind<IUserStore>().to(*userStore),
        di::bind<IAuthService>().to<SQLAuthService>().in(di::singleton));
    auto app = injector.create<App>();

    return app.run();
}