#include <string>

#include "authProfile.h"
#include "feed.h"
#include "noAuthProfile.h"
#include "playlist.h"
#include "profile.h"
#include "server.h"
#include "song.h"

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

    Profile* user1 = new NoAuthProfile();
    Profile* user2 = new AuthProfile("super_hacker3000", "fhfkhdk", 19);

    server.addUser(user1);
    server.addUser(user2);

    user1->likeSong(server, "Cheri Cheri Lady");
    user2->likeSong(server, "Cheri Cheri Lady");
    user2->likeSong(server, "In the end");
    user2->likeSong(server, 5);  // "Somewhere I Belong" id

    Playlist* p1 = new Playlist("My first playlist", "My collection of good songs.");
    Playlist* p2 = new Playlist("My second playlist", "Songs for a hard workout.");

    user2->addPlaylist(p1);
    user2->addPlaylist(p2);

    p1->addSong(s1);
    p1->addSong(s2);
    p1->addSong(s3);

    p2->addSong(s4);
    p2->addSong(s6);

    feed.displayTitle(server, user1);
    feed.displayTrends(server, user1);
    feed.displayPlaylists(server, user1);

    feed.displayTitle(server, user2);
    feed.displayRecs(server, user2);
    feed.displayLiked(server, user2);
    feed.displayPlaylists(server, user2);
    feed.displayTrends(server, user2);

    return 0;
}
