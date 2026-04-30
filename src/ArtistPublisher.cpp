#include "../include/ArtistPublisher.h"
#include "../include/interface/ISongRepository.h"

#include <memory>
#include "../include/Song.h"

void ArtistPublisher::publishSong(std::shared_ptr<ISongRepository> songs, std::shared_ptr<Song> song) {
    if (!song || artistName_.empty()) {
        return;
    } 
    songs->addSong(song);
}

ArtistPublisher::ArtistPublisher(const std::string artistName) : artistName_(artistName){}

void ArtistPublisher::setArtistName(const std::string name) {artistName_ = name;};
const std::string ArtistPublisher::getArtistName() {return artistName_;};
