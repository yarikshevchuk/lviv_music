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
    int listenCount;
    static int Count;

    class Lyrics {
       private:
        std::string lyrics;
        std::string source;

       public:
        std::string getLyrics() const;
        std::string getSource() const;
        void setLyrics(std::string lyrics);
        void setSource(std::string source);
    };
    Lyrics L;

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

    void addLyrics(std::string lyrics, std::string source);

    int getRating() const;

    void addListen();
    int getListenCount() const;
};
