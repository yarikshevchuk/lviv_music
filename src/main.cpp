
#include "../include/boost/di.hpp"
#include "../include/App.h"
#include "../include/Feed.h"
#include "../include/interface/IAuthService.h"
#include "../include/interface/ISongRepository.h"
#include "../include/interface/IUserStore.h"
#include "../include/interface/IRecommendationService.h"
#include "../include/LocalSongRepository.h"
#include "../include/GenreRecommendationService.h"
#include "../include/dto/SqliteDatabase.h"
#include "../include/dto/SqliteUserStore.h"
#include "../include/SQLAuthService.h"


int main() {
    auto db = std::make_shared<dto::SqliteDatabase>();
    db->open("lviv_music.db");

    auto userStore = std::make_shared<SqliteUserStore>(db);

    namespace di = boost::di;

    auto injector = di::make_injector(
        di::bind<Feed>().in(di::singleton),
        di::bind<ISongRepository>().to<LocalSongRepository>().in(di::singleton),
        di::bind<IRecommendationService>().to<GenreRecommendationService>().in(di::singleton),

        di::bind<IUserStore>().to(*userStore),
        di::bind<IAuthService>().to<SQLAuthService>().in(di::singleton)
    );
    auto app = injector.create<App>();

    return app.run();
}