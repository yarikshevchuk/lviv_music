#pragma once
#include <memory>
#include <vector>

class Song;
class User;
class ISongRepository;

class IRecommendationStrategy{
public:
    virtual std::vector<std::shared_ptr<Song>> generateRecommendations(std::shared_ptr<ISongRepository> songs, std::shared_ptr<User> user) const = 0;
};