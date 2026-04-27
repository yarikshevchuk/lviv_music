
#include "../include/boost/di.hpp"
#include "../include/App.h"
#include "../include/Feed.h"
#include "../include/LocalAuthService.h"
#include "../include/interface/IAuthService.h"
#include "../include/interface/ISongRepository.h"
#include "../include/interface/IRecommendationService.h"
#include "../include/ServerSongRepository.h"
#include "../include/GenreRecommendationService.h"

int main() {
    namespace di = boost::di;

    auto injector = di::make_injector(
        di::bind<Feed>().in(di::singleton),
        di::bind<IAuthService>().to<LocalAuthService>().in(di::singleton),
        di::bind<ISongRepository>().to<ServerSongRepository>().in(di::singleton),
        di::bind<IRecommendationService>().to<GenreRecommendationService>().in(di::singleton)
    );
    auto app = injector.create<App>();

    return app.run();
}