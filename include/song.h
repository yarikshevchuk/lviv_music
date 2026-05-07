#pragma once
#include <set>
#include <string>

#include "../include/interface/IAudio.h"

class Song : public IAudio {
   private:
    class {
       public:
        std::string name;
        std::string author;
        int duration;
    } staticInfo;
    std::set<std::string> genres;

    int songId;
    int rating;
    int listenCount{0};
    static int Count;

   public:
    Song(std::string name, std::string author, std::set<std::string> genres, int duration = 180);
    ~Song() = default;

    void updateRating(int val);
    bool hasGenre(std::string name);

    std::set<std::string> getGenres() const;
    int getId() const override;
    std::string getName() const override;
    std::string getAuthor() const override;
    int getDuration() const;

    int getRating() const;

    void addListen();
    int getListenCount() const;
};
