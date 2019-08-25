#ifndef MOVIEITEM_H
#define MOVIEITEM_H

#include <string>
#include <vector>

using std::string;

class movieitem
{
private:
    string title;
    int duration;
    string genre;
    int year;
    string plot;
    int type;
public:
    movieitem(string = "null", int = 0, string = "null", int = 0, string = "null", int = 0);
    movieitem(string, string="null", int=0);
    movieitem(int);
    virtual ~movieitem() = default;

    virtual bool operator==(const movieitem&) const;

    virtual string Type() const =0;

    //metodi get
    string getTitle() const;
    int getDuration() const;
    string getGenre() const;
    int getYear() const;
    string getPlot() const;
    int getType() const;

    //metodi set
    void setTitle(const string &value);
    void setDuration(const int &value);
    void setGenre(const string &value);
    void setYear(const int &value);
    void setPlot(const string &value);
    void setType(const int &value);
};

#endif // MOVIEITEM_H
