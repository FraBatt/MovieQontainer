#ifndef ANIMATION_H
#define ANIMATION_H

#include "Model/movieitem.h"

class animation : public movieitem {
private:
    string country;
    int season;
    int episodes;
public:
    animation(string = "null", int = 0, string = "null", int = 0, string = "null", int = 3, string = "null", int = 1, int = 1);
    animation(string = "null", string = "null", int = 0);
    ~animation() = default;
    animation& operator=(const animation&);
    bool operator==(const animation&) const;

    virtual string Type() const override;

    //metodi get
    string getCountry() const;
    int getSeason() const;
    int getEpisodes() const;

    //metodi set
    void setCountry(const string &value);
    void setSeason(const int &value);
    void setEpisodes(const int &value);
};

#endif // ANIMATION_H
