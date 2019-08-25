#include "Model/managefile.h"

managefile::managefile(string s) : path(s) {}

void managefile::load(Qontainer<movieitem*>& qontainer) {
    QFile file(QString::fromStdString(path));
    if(!file.open(QIODevice::ReadOnly)) {
        throw myexception("Errore di apertura file!");
    }

    QXmlStreamReader reader(&file);
    if(reader.readNextStartElement()) {
        if(reader.name() == "movie") {
            while(reader.readNextStartElement()) {
                const QXmlStreamAttributes att = reader.attributes();

                string title = att.hasAttribute("title")? att.value("title").toString().toStdString(): "";
                int duration = att.hasAttribute("duration")? att.value("duration").toInt(): 1;
                string genre = att.hasAttribute("genre")? att.value("genre").toString().toStdString(): "";
                int year = att.hasAttribute("year")? att.value("year").toInt(): 1;
                string plot = att.hasAttribute("plot")? att.value("plot").toString().toStdString(): "";

                movieitem* toPush = nullptr;
                if(reader.name() == "Film") {
                    string director = att.hasAttribute("director")? att.value("director").toString().toStdString(): "";
                    string saga = att.hasAttribute("saga")? att.value("saga").toString().toStdString(): "";
                    string country = att.hasAttribute("country")? att.value("country").toString().toStdString(): "";

                    toPush = new film(title, duration, genre, year, plot, 1, director, saga, country);
                    qontainer.push_back(toPush);
                }
                else if(reader.name() == "Serie") {
                    string director = att.hasAttribute("ideator")? att.value("ideator").toString().toStdString(): "";
                    int season = att.hasAttribute("season")? att.value("season").toInt(): 1;
                    int episodes = att.hasAttribute("episodes")? att.value("episodes").toInt(): 1;

                    toPush = new tvseries(title, duration, genre, year, plot, 2, director, season, episodes);
                    qontainer.push_back(toPush);
                }
                else if(reader.name() == "Anime") {
                    string country = att.hasAttribute("country")? att.value("country").toString().toStdString(): "";
                    int season = att.hasAttribute("season")? att.value("season").toInt(): 1;
                    int episodes = att.hasAttribute("episodes")? att.value("episodes").toInt(): 1;

                    toPush = new animation(title, duration, genre, year, plot, 3, country, season, episodes);
                    qontainer.push_back(toPush);
                }

                if(!reader.isEndDocument())
                    reader.skipCurrentElement();
            }
        }
    }
    file.close();
}

void managefile::save(Qontainer<movieitem*>& qontainer) {
    QSaveFile file(QString::fromStdString(path));
    if(!file.open(QFile::WriteOnly)) {
        throw myexception("File non corretto");
    }

    QXmlStreamWriter writer(&file);

    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeComment("NON MODIFICARE QUESTO FILE!!");

    writer.writeStartElement("movie");

    for(auto it = qontainer.cbegin(); it != qontainer.cend(); ++it) {
        const movieitem* toSave = *it;
        const QString type = QString::fromStdString(toSave->Type());
        writer.writeEmptyElement(type);

        writer.writeAttribute("title", QString::fromStdString(toSave->getTitle()));
        writer.writeAttribute("duration", QString::number(toSave->getDuration()));
        writer.writeAttribute("genre", QString::fromStdString(toSave->getGenre()));
        writer.writeAttribute("year", QString::number(toSave->getYear()));
        writer.writeAttribute("plot", QString::fromStdString(toSave->getPlot()));

        if(type == "Film") {
            const film* f = static_cast<const film*>(toSave);
            writer.writeAttribute("director", QString::fromStdString(f->getDirector()));
            writer.writeAttribute("saga", QString::fromStdString(f->getSaga()));
            writer.writeAttribute("country", QString::fromStdString(f->getCountry()));
        }
        else if(type == "Serie") {
            const tvseries* tv = static_cast<const tvseries*>(toSave);
            writer.writeAttribute("ideator", QString::fromStdString(tv->getIdeator()));
            writer.writeAttribute("season", QString::number(tv->getSeason()));
            writer.writeAttribute("episodes", QString::number(tv->getEpisodes()));
        }
        else if(type == "Anime") {
            const animation* a = static_cast<const animation*>(toSave);
            writer.writeAttribute("country", QString::fromStdString(a->getCountry()));
            writer.writeAttribute("season", QString::number(a->getSeason()));
            writer.writeAttribute("episodes", QString::number(a->getEpisodes()));
        }
    }

    writer.writeEndElement();
    writer.writeEndDocument();
    file.commit();
}
