#pragma once
#include <vector>

class ILikesStore {
   public:
    virtual ~ILikesStore() = default;

    virtual bool addLike(int user_id, int song_id) = 0;
    virtual bool removeLike(int user_id, int song_id) = 0;
    virtual bool isLiked(int user_id, int song_id) const = 0;

    virtual std::vector<int> listLikedSongIdsForUser(int user_id) const = 0;
};
