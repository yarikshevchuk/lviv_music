
#include <math.h>

#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

class Song;
class Profile;
class NoAuthProfile;
class AuthProfile;
class Server;
class Feed;

class Song {
    int songId;
    string name;
    string author;
    set<string> genres;
    int rating;
    static int Count;

   public:
    Song(string name, string author, set<string> genres)
        : name(name), author(author), genres(genres) {
        songId = Count++;
        rating = 7;
    }
    ~Song() = default;

    void updateRating(int val) {
        if (val > 0) {
            rating = min(rating + 1, 10);
        } else if (val < 0) {
            rating = max(rating - 1, 0);
        }
    }
    bool hasGenre(string name) { return genres.find(name) != genres.end(); }
    set<string> getGenres() { return genres; }
    int getId() { return songId; }
    string getName() { return name; }
    string getAuthor() { return author; }
    int getRating() { return rating; }
};

class Server {
    vector<Song*> trendingSongs;
    vector<Song*> allSongs;
    vector<Profile*> users;

   public:
    ~Server() {
        for (int i = 0; i < trendingSongs.size(); i++) {
            delete trendingSongs[i];
        }
        for (int i = 0; i < allSongs.size(); i++) {
            delete allSongs[i];
        }
        for (int i = 0; i < users.size(); i++) {
            delete users[i];
        }
    };

    vector<Song*> getTrendingSongs() { return trendingSongs; }
    vector<Song*> getAllSongs() { return allSongs; }
    void addUser(Profile* prfl) { users.push_back(prfl); }
    void setTrendingSongs(vector<Song*> sngs) { trendingSongs = sngs; }
    void addTrendingSong(Song* sng) {
        bool foundSong = false;
        for (auto ptr = trendingSongs.begin(); ptr != trendingSongs.end();
             ptr++) {
            if ((*ptr)->getName() == sng->getName()) {
                foundSong = true;
                break;
            }
            if (foundSong) return;
        }
        trendingSongs.push_back(sng);
        addSong(sng);
    }
    void addSong(Song* sng) {
        bool foundSong = false;
        for (auto ptr = allSongs.begin(); ptr != allSongs.end(); ptr++) {
            if ((*ptr)->getName() == sng->getName()) {
                foundSong = true;
                break;
            }
            if (foundSong) return;
        }
        allSongs.push_back(sng);
    }
    Song* findSong(string songName) {
        for (auto ptr = allSongs.begin(); ptr != allSongs.end(); ptr++) {
            if ((*ptr)->getName() == songName) {
                return *ptr;
            }
        }
        return nullptr;
    }
    Song* findSong(int songId) {
        for (auto ptr = allSongs.begin(); ptr != allSongs.end(); ptr++) {
            if ((*ptr)->getId() == songId) {
                return *ptr;
            }
        }
        return nullptr;
    }
};

class Profile {
    int userId;
    static int Count;

   protected:
    bool isAuthenticated;
    set<Song*> recs;
    vector<Song*> likedSongs;

   public:
    Profile(bool authStatus) : isAuthenticated(authStatus) {
        userId = Count++;
    };
    virtual ~Profile() = default;

    virtual void setRecs(vector<Song*> trending) = 0;
    virtual void likeSong(Server server, string songName) = 0;
    virtual void likeSong(Server server, int songId) = 0;
    virtual string getUsername() = 0;

    vector<Song*> getRecs() const {
        return vector<Song*>(recs.begin(), recs.end());
    };
    vector<Song*> getLikedSongs() const { return likedSongs; };
    int getId() const { return userId; };
    int getAuthStatus() const { return isAuthenticated; };
};

class NoAuthProfile : public Profile {
   public:
    NoAuthProfile() : Profile(false) {};
    void setRecs(vector<Song*> trending) override {
        cout << "You need to create an account to have recomendations.\n";
    };
    void likeSong(Server server, string songName) override {
        cout << "You need to create an account to like songs.\n";
    }
    void likeSong(Server server, int songId) override {
        cout << "You need to create an account to like songs.\n";
    }
    string getUsername() override { return "none"; };
};

class AuthProfile : public Profile {
    string username;
    string password;
    string primaryGenre;
    int age;

    string updatePrimaryGenre() {
        map<string, int> genres;
        string newGenre;
        int mostCommon = 0;

        if (likedSongs.size() == 0) {
            return "none";
        }
        for (Song* song : likedSongs) {
            for (string genre : song->getGenres()) {
                if (genres.find(genre) == genres.end()) {
                    genres.insert({genre, 1});
                } else {
                    genres[genre] += 1;
                }
            }
        }
        for (auto ptr = genres.begin(); ptr != genres.end(); ptr++) {
            if (ptr->second > mostCommon) {
                mostCommon = ptr->second;
                newGenre = ptr->first;
            }
        }
        primaryGenre = newGenre;
        return primaryGenre;
    }
    void setRecs(vector<Song*> allSongs) override {
        if (likedSongs.size() == 0) return;
        if (primaryGenre == "none") {
            updatePrimaryGenre();
        }

        for (Song* song : allSongs) {
            if (song->hasGenre(primaryGenre)) {
                recs.insert(song);
            }
        }
    }

   public:
    AuthProfile(string username, string password, int age)
        : Profile(true),
          username(username),
          password(password),
          age(age),
          primaryGenre("none") {}
    void likeSong(Server server, string songName) override {
        Song* likedSong = server.findSong(songName);
        if (likedSong == nullptr) {
            return;
        }

        for (Song* sng : likedSongs) {
            if (sng->getName() == likedSong->getName()) {
                return;
            }
        }
        cout << "@" << username << " liked a song " << likedSong->getName()
             << "\n";

        likedSongs.push_back(likedSong);
        likedSong->updateRating(1);
        updatePrimaryGenre();
        setRecs(server.getAllSongs());
    }
    void likeSong(Server server, int songId) override {
        Song* likedSong = server.findSong(songId);
        if (likedSong == nullptr) {
            return;
        }

        for (Song* sng : likedSongs) {
            if (sng->getName() == likedSong->getName()) {
                return;
            }
        }
        cout << "@" << username << " liked a song " << likedSong->getName()
             << "\n";

        likedSongs.push_back(likedSong);
        likedSong->updateRating(1);
        updatePrimaryGenre();
        setRecs(server.getAllSongs());
    }

    string getUsername() override { return username; }
};

class Feed {
    void printSongs(vector<Song*>& songs) const {
        for (Song* sng : songs) {
            string wrapp = "|";
            int width =
                max(sng->getName().size(), sng->getAuthor().size() + 8) + 1;
            for (int i = 0; i < width; i++) {
                wrapp += "=";
            }
            wrapp += "|\n";

            cout << wrapp;
            cout << left << "|" << setw(width) << sng->getName() << "|\n";
            cout << left << "|" << setw(width / 2 - 1) << sng->getAuthor();
            cout << right << setw(width / 2) << "Rating:" << sng->getRating()
                 << "|\n";
            cout << wrapp << "\n";
        }
    }

   public:
    void displayUserFeed(Server server, Profile* user) {
        vector<Song*> trends = server.getTrendingSongs();
        vector<Song*> recs = user->getRecs();
        vector<Song*> liked = user->getLikedSongs();

        if (user->getAuthStatus() == 1) {
            cout << "|@" << user->getUsername() << " feed:|\n";
        } else {
            cout << "|Anonymous user feed:|\n";
        }

        if (user->getAuthStatus() == 1) {
            cout << "|Your recomendations:|\n";
            printSongs(recs);
            cout << "|Liked Songs:|\n";
            printSongs(liked);
        }

        cout << "|Trending songs:|\n";
        printSongs(trends);

        cout << "\n";
    }
};

int Song::Count = 0;
int Profile::Count = 0;

int main() {
    Server server;
    Feed feed;
    server.addSong(new Song("You're my heart, you're my soul", "Modern Talking",
                            {"Eurodisco"}));
    server.addSong(
        new Song("Cheri Cheri Lady", "Modern Talking", {"Eurodisco"}));
    server.addSong(new Song("Self Control", "Laura Branigan", {"Eurodisco"}));
    server.addSong(new Song("The Diary of Jane", "Breaking Benjamin",
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
    // user2->likeSong(server, "In the end");
    // user2->likeSong(server, "Somewhere I Belong");
    user2->likeSong(server, 5);  // "Somewhere I Belong" id

    feed.displayUserFeed(server, user1);
    feed.displayUserFeed(server, user2);

    return 0;
}
