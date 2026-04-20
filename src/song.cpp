#include "../include/song.h"
using namespace std;

Song::Song(string name, string author, set<string> genres, int duration) : staticInfo{name, author, duration}, songId(Count++), genres(genres), rating(7) {}

void Song::updateRating(int val) {
    if (val > 0) {
        rating = min(rating + 1, 10);
    } else if (val < 0) {
        rating = max(rating - 1, 0);
    }
}

bool Song::hasGenre(string name) { return genres.find(name) != genres.end(); }

set<string> Song::getGenres() const { return genres; }
int Song::getId() const { return songId; }
string Song::getName() const { return staticInfo.name; }
string Song::getAuthor() const { return staticInfo.author; }
int Song::getRating() const { return rating; }
int Song::getDuration() const { return staticInfo.duration; }

// lyrics

void Song::addLyrics(string lrcs, string src) {
    L.setLyrics(lrcs);
    L.setSource(src);
}

string Song::Lyrics::getLyrics() const { return lyrics; };
string Song::Lyrics::getSource() const { return source; };

void Song::Lyrics::setLyrics(string lrcs) { lyrics = lrcs; };
void Song::Lyrics::setSource(string src) { source = src; };

int Song::Count = 0;
