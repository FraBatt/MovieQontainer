#ifndef TVSERIES_H
#define TVSERIES_H

#include "Model/movieitem.h"

class tvseries : public movieitem {
private:
    string ideator;
    int season;
    int episodes;
public:
    tvseries(string = "null", int = 0, string = "null", int = 0, string = "null", int = 2, string = "null", int = 1, int = 1);
    tvseries(string = "null", string = "null", int = 0);
    ~tvseries() = default;
    tvseries& operator=(const tvseries&);
    bool operator==(const tvseries&) const;

    virtual string Type() const override;

    //metodi get
    string getIdeator() const;
    int getSeason() const;
    int getEpisodes() const;

    //metodi set
    void setIdeator(const string &value);
    void setSeason(const int &value);
    void setEpisodes(const int &value);
};

#endif // TVSERIES_H
