#include <string>

#include "authProfile.h"
#include "feed.h"
#include "noAuthProfile.h"
#include "profile.h"
#include "server.h"
#include "song.h"

int main() {
    Server server;
    Feed feed;
    server.addSong(new Song("You're my heart, you're my soul",
                            "Modern Talking ", {"Eurodisco"}));
    server.addSong(
        new Song("Cheri Cheri Lady", "Modern Talking", {"Eurodisco"}));
    server.addSong(new Song("Self Control", "Laura Branigan", {"Eurodisco"}));
    server.addSong(new Song("The Diary of Jane", "Breaking Benjamin ",
                            {"Rock", "Nu-Metal"}));
    server.addSong(new Song("In the end", "Linkin Park", {"Rock", "Nu-Metal"}));
    server.addSong(
        new Song("Somewhere I Belong", "Linkin Park", {"Rock", "Nu-Metal"}));
    server.addTrendingSong(
        new Song("Can You Feel My Heart", "BMTH", {"Rock", "Nu-Metal"}));
    server.addTrendingSong(
        new Song("Before I Forget", "Slipknot", {"Nu-Metal"}));

    Profile* user1 = new NoAuthProfile();
    Profile* user2 = new AuthProfile("super_hacker3000", "fhfkhdk", 19);

    server.addUser(user1);
    server.addUser(user2);

    feed.displayUserFeed(server, user1);
    feed.displayUserFeed(server, user2);

    user1->likeSong(server, "Cheri Cheri Lady");
    user2->likeSong(server, "Cheri Cheri Lady");
    user2->likeSong(server, "In the end");
    // user2->likeSong(server, "Somewhere I Belong");
    user2->likeSong(server, 5);  // "Somewhere I Belong" id
    feed.displayUserFeed(server, user1);
    feed.displayUserFeed(server, user2);
    std::cin.get();
    return 0;
}
