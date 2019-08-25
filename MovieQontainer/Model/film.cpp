#include "film.h"
using namespace std;

film::film(string tit, int dur, string gnr, int usc, string pl, int tp, string dir, string sg, string cnt) :
    movieitem(tit, dur, gnr, usc, pl, tp), director(dir), saga(sg), country(cnt) {}

film::film(string tit, string gnr, int usc) : movieitem(tit, gnr, usc) {}

film::film(int usc) : movieitem(usc) {}

film& film::operator=(const film& f) {
    if(this != &f)
        *this = f;
    return *this;
}

bool film::operator==(const film& f) const {
    return (movieitem::operator==(f) && director == f.director && saga == f.saga && country == f.country);
}

string film::Type() const {
    return "Film";
}

//metodi get
string film::getDirector() const {
    return director;
}

string film::getSaga() const {
    return saga;
}

string film::getCountry() const {
    return country;
}

//metodi set
void film::setDirector(const string &value) {
    director = value;
}

void film::setSaga(const string &value) {
    saga = value;
}

void film::setCountry(const string &value) {
    country = value;
}
