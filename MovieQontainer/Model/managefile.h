#ifndef MANAGEFILE_H
#define MANAGEFILE_H

#include "Model/movieitem.h"
#include "Model/animation.h"
#include "Model/tvseries.h"
#include "Model/film.h"
#include "Model/qontainer.h"
#include "Model/myexception.h"
#include <string>
#include <vector>
#include <QXmlStreamReader>
#include <QFile>
#include <QSaveFile>

using std::string;
using std::vector;

class managefile {
private:
    string path;
public:
    managefile(string = "0");
    void load(Qontainer<movieitem*>&);
    void save(Qontainer<movieitem*>&);
};

#endif // MANAGEFILE_H
