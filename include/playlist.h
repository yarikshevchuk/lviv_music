#pragma once
#include <memory>
#include <string>
#include <vector>

#include "Song.h"

class Playlist {
   private:
    std::string name;
    std::string description;
    std::vector<std::shared_ptr<Song>> songs;
    int playlistId;
    static int Count;

    class {
       public:
        int totalDuration;
        int playCount;
        std::string lastUpdated;
    } stats;

    void updateTime();
    void updateDuration(const std::shared_ptr<Song>& sng, int sign);

   public:
    Playlist(std::string nm, std::string descr);
    ~Playlist() = default;

    void addSong(std::shared_ptr<Song> sng);
    void deleteSong(const std::shared_ptr<Song>& sng);

    void setName(std::string playlistName);
    void setDescription(std::string descr);

    std::vector<std::shared_ptr<Song>> getSongs() const;
    std::string getName() const;
    std::string getDescription() const;
    int getTotalDuration() const;
    int getId() const;
    int getPlayCount() const;
    std::string getLastUpdated() const;
};