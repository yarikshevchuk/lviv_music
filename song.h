#pragma once
#include <set>
#include <string>

class Song {
    int songId;
    std::string name;
    std::string author;
    std::set<std::string> genres;
    int rating;
    static int Count;

   public:
    Song(std::string name, std::string author, std::set<std::string> genres);
    ~Song() = default;

    void updateRating(int val);
    bool hasGenre(std::string name);
    std::set<std::string> getGenres();
    int getId();
    std::string getName();
    std::string getAuthor();
    int getRating();
};
