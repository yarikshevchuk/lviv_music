g++ -std=c++17 ^
  src/app.cpp ^
  src/main.cpp ^
  src/feed.cpp ^
  src/song.cpp ^
  src/playlist.cpp ^
  src/User.cpp ^
  src/ListenerIdentity.cpp ^
  src/ListenerLikesSongs.cpp ^
  src/ListenerHasPlaylists.cpp ^
  src/ListenerHasRecs.cpp ^
  src/ArtistPublisher.cpp ^
  src/LocalAuthService.cpp ^
  src/ServerSongRepository.cpp ^
  src/GenreRecommendationService.cpp ^
  -Iinclude -o my_app
my_app.exe