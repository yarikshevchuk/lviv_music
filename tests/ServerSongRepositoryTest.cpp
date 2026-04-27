#include <gtest/gtest.h>

#include <memory>
#include <set>
#include <vector>
#include <string>

#include "ServerSongRepository.h"
#include "Song.h"

using namespace std;

TEST(ServerSongRepository, AddAndFindSong) {
    ServerSongRepository repo;
    shared_ptr<Song> sng1 = make_shared<Song>("Song1", "Author1", set<string>{"HipHop"});

    repo.addSong(sng1);

    shared_ptr<Song> found = repo.findSong("Song1");
    EXPECT_EQ(found, sng1);
}

TEST(ServerSongRepository, AddTwoSongsAndCheck) {
    ServerSongRepository repo;
    shared_ptr<Song> sng1 = make_shared<Song>("Song", "Author1", set<string>{"HipHop"});
    shared_ptr<Song> sng2 = make_shared<Song>("Song", "Author2", set<string>{"Metal"});

    repo.addSong(sng1);
    repo.addSong(sng2);

    vector<shared_ptr<Song>> songs = repo.getSongs();

    EXPECT_FALSE(songs.size() == 0);
    EXPECT_TRUE(songs[1]->getGenres().count("Metal"));
    EXPECT_EQ(songs[0]->getName(), sng1->getName());
}

TEST(ServerSongRepository, AddTrendingSong) {
    ServerSongRepository repo;
    shared_ptr<Song> sng1 = make_shared<Song>("Song", "Author1", set<string>{"HipHop"});

    repo.addTrendingSong(sng1);

    EXPECT_EQ(repo.getTrendingSongs().size(), 1);
    EXPECT_EQ(repo.getSongs().size(), 1);
}