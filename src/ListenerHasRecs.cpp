#include "../include/ListenerHasRecs.h"

#include <memory>
#include <vector>
using namespace std;

void ListenerHasRecs::setRecs(vector<shared_ptr<Song>> recs) {
    recs_ = std::move(recs);
}
vector<shared_ptr<Song>> ListenerHasRecs::getRecs() { return recs_; };