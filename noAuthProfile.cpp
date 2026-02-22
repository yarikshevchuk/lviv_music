#include "noAuthProfile.h"

#include "server.h"
#include "song.h"
using namespace std;

NoAuthProfile::NoAuthProfile() : Profile(false) {};
void NoAuthProfile::setRecs(vector<Song*> trending) {
    cout << "You need to create an account to have recomendations.\n";
};
void NoAuthProfile::likeSong(Server& server, const std::string& songName) {
    cout << "You need to create an account to like songs.\n";
}
void NoAuthProfile::likeSong(Server& server, int songId) {
    cout << "You need to create an account to like songs.\n";
}
string NoAuthProfile::getUsername() { return "none"; };