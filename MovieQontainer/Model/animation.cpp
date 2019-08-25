#include "animation.h"
using namespace std;

animation::animation(string tit, int dur, string gnr, int usc, string pl, int tp, string cnt, int ssn, int ep) :
    movieitem(tit, dur, gnr, usc, pl, tp), country(cnt), season(ssn), episodes(ep) {}

animation::animation(string tit, string gnr, int usc) : movieitem(tit, gnr, usc) {}

animation& animation::operator=(const animation& a) {
    if(this != &a)
        *this = a;
    return *this;
}

bool animation::operator==(const animation &a) const {
    return (movieitem::operator==(a) && country == a.country && season == a.season && episodes == a.episodes);
}

string animation::Type() const {
    return "Anime";
}

//metodi get
string animation::getCountry() const {
    return country;
}

int animation::getSeason() const {
    return season;
}

int animation::getEpisodes() const {
    return episodes;
}

//metodi set
void animation::setCountry(const string &value) {
    country = value;
}

void animation::setSeason(const int &value) {
    season = value;
}

void animation::setEpisodes(const int &value) {
    episodes = value;
}
