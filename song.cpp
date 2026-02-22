#include "song.h"
using namespace std;

Song::Song(string name, string author, set<string> genres)
    : name(name), author(author), genres(genres) {
    songId = Count++;
    rating = 7;
}

void Song::updateRating(int val) {
    if (val > 0) {
        rating = min(rating + 1, 10);
    } else if (val < 0) {
        rating = max(rating - 1, 0);
    }
}

bool Song::hasGenre(string name) { return genres.find(name) != genres.end(); }
set<string> Song::getGenres() { return genres; }
int Song::getId() { return songId; }
string Song::getName() { return name; }
string Song::getAuthor() { return author; }
int Song::getRating() { return rating; }

int Song::Count = 0;
