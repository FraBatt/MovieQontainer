#ifndef FILM_H
#define FILM_H

#include "Model/movieitem.h"

class film : public movieitem {
private:
    string director;
    string saga;
    string country;
public:
    film(string = "null", int = 0, string = "null", int = 0, string = "null", int = 1, string = "null", string = "null", string = "null");
    film(string, string = "null", int = 0);
    film(int = 0);
    ~film() = default;
    film& operator=(const film&);
    bool operator==(const film&) const;

    virtual string Type() const override;

    //metodi get
    string getDirector() const;
    string getSaga() const;
    string getCountry() const;

    //metodi set
    void setDirector(const string &value);
    void setSaga(const string &value);
    void setCountry(const string &value);
};

#endif // FILM_H
