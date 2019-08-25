#include "tvseries.h"
using namespace std;

tvseries::tvseries(string tit, int dur, string gnr, int usc, string pl, int tp, string dir, int ssn, int ep) :
    movieitem(tit, dur, gnr, usc, pl, tp), ideator(dir), season(ssn), episodes(ep) {}

tvseries::tvseries(string tit, string gnr, int usc) : movieitem(tit, gnr, usc) {}

tvseries& tvseries::operator=(const tvseries& tv) {
    if(this != &tv)
        *this = tv;
    return *this;
}

bool tvseries::operator==(const tvseries& tv) const {
    return (movieitem::operator==(tv) && ideator == tv.ideator && season == tv.season && episodes == tv.episodes);
}

string tvseries::Type() const {
    return "Serie";
}

//metodi get
string tvseries::getIdeator() const {
    return ideator;
}

int tvseries::getSeason() const {
    return season;
}

int tvseries::getEpisodes() const {
    return episodes;
}

//metodi set
void tvseries::setIdeator(const string &value) {
    ideator = value;
}

void tvseries::setSeason(const int &value) {
    season = value;
}

void tvseries::setEpisodes(const int &value) {
    episodes = value;
}
