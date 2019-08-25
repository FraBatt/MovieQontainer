#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Model/movieitem.h"
#include "Model/animation.h"
#include "Model/tvseries.h"
#include "Model/film.h"
#include "Model/managefile.h"
#include "Model/qontainer.h"
#include <QWidget>
#include <QCloseEvent>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QButtonGroup>
#include <QVBoxLayout>
#include <QFont>
#include <QAction>
#include <QGridLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QScrollArea>
#include <QScrollBar>
#include <QPixmap>
#include <QImage>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QDialog>
#include <vector>

using std::vector;

class MainWindow : public QWidget {
    Q_OBJECT
private:
    Qontainer<movieitem*> qontainer;
    managefile* file;
    vector<movieitem*> resultVector;
    QGridLayout* contGrid, *viewGrid, *addGrid, *searchGrid;
    QVBoxLayout* addLayout;
    QLabel* titleLabel, *libraryLabel, *searchTitle, *addTitle, *titleSearch, *genreSearch, *yearSearch;
    QLineEdit* titleLine, *genreLine, *yearLine;
    QPushButton *searchButton, *addFilm, *addSerie, *addAnime;
    QScrollArea* visualScroll;
    vector<QLineEdit*> addVector, modifyVector;
    QFormLayout* form;
protected:
    void closeEvent(QCloseEvent*) override;
public:
    MainWindow(QWidget* = nullptr);
    ~MainWindow() = default;
public slots:
    QString openFile();
    //-----ADD-------
    void addLabel(QString, QString, QFormLayout*);
    void onClickAddFilm();
    void onClickAddSerie();
    void onClickAddAnime();
    //-------SEARCH--------
    void onClickSearch();
    void viewResultSearch(vector<movieitem*>);
    void onClickVisualize();
    //----VISUAL------
    void visualFilm();
    void visualAnime();
    void visualSeries();
    void onClickVisualFilm();
    void onClickVisualSerie();
    void onClickVisualAnime();
    void startVisualFilm(film*);
    void startVisualSerie(tvseries*);
    void startVisualAnime(animation*);
    //--------MODIFY-------
    void modifyPage(movieitem*);
    //---------DELETE---------
    void deleteElement(movieitem*);
};

#endif // MAINWINDOW_H
