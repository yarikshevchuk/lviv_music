g++ -std=c++17 ^
  src/main.cpp ^
  src/server.cpp ^
  src/feed.cpp ^
  src/song.cpp ^
  src/playlist.cpp ^
  src/User.cpp ^
  src/ListenerIdentity.cpp ^
  src/ListenerLikesSongs.cpp ^
  src/ListenerHasPlaylists.cpp ^
  src/ListenerHasRecs.cpp ^
  src/ArtistPublisher.cpp ^
  -Iinclude -o my_app
my_app.exe