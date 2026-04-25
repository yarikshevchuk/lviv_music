#include "../include/ListenerHasTrends.h"
#include <memory>
#include <vector>
using namespace std;

    
void ListenerHasTrends::setTrends(vector<shared_ptr<Song>> trends) {
    trends_ = std::move(trends);
}
vector<shared_ptr<Song>> ListenerHasTrends::getTrends() { return trends_; };