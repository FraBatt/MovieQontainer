#include "movieitem.h"

movieitem::movieitem(string tit, int dur, string gnr, int usc, string pl, int tp) : title(tit), duration(dur),
    genre(gnr), year(usc), plot(pl), type(tp) {}

movieitem::movieitem(string tit, string gnr, int usc) : title(tit), genre(gnr), year(usc) {}


movieitem::movieitem(int usc) : year(usc) {}

bool movieitem::operator==(const movieitem& m) const {
    return (title == m.title && duration == m.duration && genre == m.genre && year == m.year && plot == m.plot && type == m.type);
}

//metodi get
string movieitem::getTitle() const {
    return title;
}

int movieitem::getDuration() const {
    return duration;
}

string movieitem::getGenre() const {
    return genre;
}

int movieitem::getYear() const {
    return year;
}

string movieitem::getPlot() const {
    return plot;
}

int movieitem::getType() const {
    return type;
}

//metodi set
void movieitem::setTitle(const string &value) {
    title = value;
}

void movieitem::setDuration(const int &value) {
    duration = value;
}

void movieitem::setGenre(const string &value) {
    genre = value;
}

void movieitem::setYear(const int &value) {
    year = value;
}

void movieitem::setPlot(const string &value) {
    plot = value;
}

void movieitem::setType(const int &value) {
    type = value;
}
