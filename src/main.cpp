#include <memory>
#include <string>

#include "../include/ListenerHasPlaylists.h"
#include "../include/ListenerHasRecs.h"
#include "../include/ListenerHasTrends.h"
#include "../include/ListenerIdentity.h"
#include "../include/ListenerLikesSongs.h"
#include "../include/User.h"
#include "../include/feed.h"
#include "../include/playlist.h"
#include "../include/server.h"
#include "../include/song.h"

int main() {
    Feed feed;
    Server server;

    Song* s1 = new Song("You're my heart, you're my soul", "Modern Talking ", {"Eurodisco"});
    Song* s2 = new Song("Cheri Cheri Lady", "Modern Talking", {"Eurodisco"});
    Song* s3 = new Song("Self Control", "Laura Branigan", {"Eurodisco"});
    Song* s4 = new Song("The Diary of Jane", "Breaking Benjamin ", {"Rock", "Nu-Metal"});
    Song* s5 = new Song("In the end", "Linkin Park", {"Rock", "Nu-Metal"});
    Song* s6 = new Song("Somewhere I Belong", "Linkin Park", {"Rock", "Nu-Metal"});

    Song* t1 = new Song("Can You Feel My Heart", "BMTH", {"Rock", "Nu-Metal"});
    Song* t2 = new Song("Before I Forget", "Slipknot", {"Nu-Metal"});

    server.addSong(s1);
    server.addSong(s2);
    server.addSong(s3);
    server.addSong(s4);
    server.addSong(s5);
    server.addSong(s6);

    server.addTrendingSong(t1);
    server.addTrendingSong(t2);

    User user1;
    User user2;

    user2.grantListenerAccess(std::make_unique<ListenerLikesSongs>(), std::make_unique<ListenerHasPlaylists>(), std::make_unique<ListenerHasRecs>(), std::make_unique<ListenerIdentity>("user1", "user1@gmail.com", 1, 18));

    if (auto* user_likes = user1.likes()) {
        user_likes->likeSong(server, "Cheri Cheri Lady");
    }
    if (auto* user_likes = user2.likes()) {
        user_likes->likeSong(server, "Cheri Cheri Lady");
    }

    if (auto* user_likes = user2.likes()) {
        user_likes->likeSong(server, "In the end");
    }
    if (auto* user_likes = user2.likes()) {
        user_likes->likeSong(server, 5);  // "Somewhere I Belong" id
    }

    Playlist* p1 = new Playlist("My first playlist", "My collection of good songs.");
    Playlist* p2 = new Playlist("My second playlist", "Songs for a hard workout.");

    if (auto* user_playlists = user2.playlists()) {
        user_playlists->addPlaylist(p1);
        user_playlists->addPlaylist(p2);
    }

    p1->addSong(s1);
    p1->addSong(s2);
    p1->addSong(s3);

    p2->addSong(s4);
    p2->addSong(s6);

    feed.displayTitle(server, &user1);
    feed.displayTrends(server, &user1);
    feed.displayPlaylists(server, &user1);

    feed.displayTitle(server, &user2);
    feed.displayRecs(server, &user2);
    feed.displayLiked(server, &user2);
    feed.displayPlaylists(server, &user2);
    feed.displayTrends(server, &user2);

    return 0;
}
