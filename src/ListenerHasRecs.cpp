#include "../include/ListenerHasRecs.h"

#include <vector>
using namespace std;

void ListenerHasRecs::setRecs(vector<Song*> recs) {
    // this logic needs to be transferred to a separate logic class that manages recomendations

    // if (likedSongs.size() == 0) return;
    // if (primaryGenre == "none") {
    //     updatePrimaryGenre();
    // }

    // for (Song* song : allSongs) {
    //     if (song->hasGenre(primaryGenre)) {
    //         recs.insert(song);
    //     }
    // }

    // end of the block responsible for recs logic
    recs_ = recs;
}
vector<Song*> ListenerHasRecs::getRecs() { return recs_; };