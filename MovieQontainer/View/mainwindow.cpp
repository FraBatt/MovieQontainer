#include "View/mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    setFixedSize(800, 800);
    setFocusPolicy(Qt::StrongFocus);
    if(qontainer.getSize() == 0) {
        QString filename = openFile();
        while(filename.isEmpty()) {
            QMessageBox msg;
            msg.setText("File non corretto!");
            QPushButton* Yes = msg.addButton(tr("Riprova"), QMessageBox::YesRole);
            msg.setDefaultButton(Yes);
            msg.exec();
            filename = openFile();
        }

        file = new managefile(filename.toStdString());
        file->load(qontainer);
    }

    this->setWindowTitle("MovieQontainer - Francesco Battistella");
    this->setFont(QFont("Arial"));

    contGrid = new QGridLayout();

    contGrid->setColumnMinimumWidth(0,300);
    contGrid->setColumnMinimumWidth(1,300);

    contGrid->setRowMinimumHeight(0, 100);
    contGrid->setRowMinimumHeight(1, 200);
    contGrid->setRowMinimumHeight(2, 300);
    contGrid->setRowMinimumHeight(3, 200);

    titleLabel= new QLabel();
    titleLabel->setScaledContents(true);
    QPixmap logo(":/img/logo.png");
    titleLabel->setPixmap(logo);
    titleLabel->setFixedSize(300, 200);
    contGrid->addWidget(titleLabel, 0, 0, Qt::AlignCenter);

    //---------------------SEARCH-----------------

    searchGrid = new QGridLayout();

    searchTitle = new QLabel();
    searchTitle->setText("Ricerca");
    searchTitle->setFont(QFont("Arial", 18));

    searchGrid->addWidget(searchTitle, 0, 1, Qt::AlignCenter);

    titleSearch = new QLabel();
    titleSearch->setText("Titolo:");
    titleSearch->setFixedHeight(25);
    titleLine = new QLineEdit();
    titleLine->setPlaceholderText("Inserisci il titolo");
    titleLine->setFixedSize(250, 25);

    genreSearch = new QLabel();
    genreSearch->setText("Genere:");
    genreSearch->setFixedHeight(25);
    genreLine = new QLineEdit();
    genreLine->setPlaceholderText("Inserisci il genere");
    genreLine->setFixedSize(250, 25);

    yearSearch = new QLabel();
    yearSearch->setText("Anno:");
    yearSearch->setFixedHeight(25);
    yearLine = new QLineEdit();
    yearLine->setPlaceholderText("Inserisci l'anno di uscita");
    yearLine->setFixedSize(250, 25);

    searchGrid->addWidget(titleSearch, 1, 0, Qt::AlignCenter);
    searchGrid->addWidget(titleLine, 1, 1, Qt::AlignCenter);
    searchGrid->addWidget(genreSearch, 2, 0, Qt::AlignCenter);
    searchGrid->addWidget(genreLine, 2, 1, Qt::AlignCenter);
    searchGrid->addWidget(yearSearch, 3, 0, Qt::AlignCenter);
    searchGrid->addWidget(yearLine, 3, 1, Qt::AlignCenter);

    searchButton = new QPushButton();
    searchButton->setText("Cerca");
    searchButton->setFixedSize(100,25);

    searchGrid->addWidget(searchButton, 4, 1, Qt::AlignCenter);

    connect(searchButton, SIGNAL(clicked()), this, SLOT(onClickSearch()));

    contGrid->addLayout(searchGrid, 1, 0, Qt::AlignCenter);

    //--------------------ADD-------------------

    addGrid = new QGridLayout();

    addTitle = new QLabel();
    addTitle->setText("Aggiungi");
    addTitle->setFont(QFont("Arial", 18));

    addGrid->addWidget(addTitle, 0, 1, Qt::AlignRight);

    addFilm = new QPushButton();
    addFilm->setText("Film");
    addFilm->setFixedSize(80, 80);
    addFilm->setStyleSheet("Background-color : #fff;");

    addSerie = new QPushButton();
    addSerie->setText("Serie Tv");
    addSerie->setFixedSize(80, 80);
    addSerie->setStyleSheet("Background-color : #fff;");

    addAnime = new QPushButton();
    addAnime->setText("Anime");
    addAnime->setFixedSize(80, 80);
    addAnime->setStyleSheet("Background-color : #fff;");

    addGrid->addWidget(addFilm, 1, 0, Qt::AlignRight);
    addGrid->addWidget(addSerie, 1, 1, Qt::AlignRight);
    addGrid->addWidget(addAnime, 1, 2, Qt::AlignRight);

    contGrid->addLayout(addGrid, 2, 0, Qt::AlignCenter);

    connect(addFilm, SIGNAL(clicked()), this, SLOT(onClickAddFilm()));
    connect(addSerie, SIGNAL(clicked()), this, SLOT(onClickAddSerie()));
    connect(addAnime, SIGNAL(clicked()), this, SLOT(onClickAddAnime()));


    //-------------------LIBRARY-----------------

    libraryLabel= new QLabel();
    libraryLabel->setText("La tua libreria:");
    libraryLabel->setFont(QFont("Arial", 24));
    contGrid->addWidget(libraryLabel, 0, 1, Qt::AlignCenter);

    QLabel* label2 = new QLabel();
    label2->setText("Serie Tv");
    contGrid->addWidget(label2, 2, 1, Qt::AlignCenter);

    QLabel* label3 = new QLabel();
    label3->setText("Anime");
    contGrid->addWidget(label3, 3, 1, Qt::AlignCenter);

    visualFilm();
    visualSeries();
    visualAnime();

    contGrid->setSpacing(25);
    setLayout(contGrid);
}

QString MainWindow::openFile() {
    return QFileDialog::getOpenFileName(this, "Carica file dati", QDir::homePath(), "Xml, (*.xml)");
}

void MainWindow::closeEvent(QCloseEvent* event) {
    file->save(qontainer);
    event->accept();
}

//------------------------------VISUAL--------------------------------

void MainWindow::visualFilm() {
    QWidget* filmWidget = new QWidget();
    QVBoxLayout* filmBox= new QVBoxLayout();
    QGridLayout* filmGrid = new QGridLayout();

    visualScroll = new QScrollArea;
    visualScroll->setWidgetResizable(true);
    visualScroll->setFrameShape(QFrame::NoFrame);
    visualScroll->setWidget(filmWidget);
    filmBox->addWidget(visualScroll);

    int i = 0;
    for(auto it = qontainer.begin(); it != qontainer.end(); ++it) {
        if(dynamic_cast<film*>(*it)) {
            QPushButton* visualFilmButton = new QPushButton();
            visualFilmButton->setText(QString::fromStdString((*it)->getTitle()));
            visualFilmButton->setFixedSize(250, 25);
            visualFilmButton->setObjectName(QString::number(i));

            filmGrid->addWidget(visualFilmButton);

            connect(visualFilmButton, SIGNAL(clicked()), this, SLOT(onClickVisualFilm()));

            ++i;
        }
    }
    filmWidget->setLayout(filmGrid);
    contGrid->addLayout(filmBox, 1, 1, Qt::AlignCenter);
}

void MainWindow::visualSeries() {
    QWidget* seriesWidget = new QWidget();
    QGridLayout* seriesGrid = new QGridLayout();
    QVBoxLayout* seriesBox= new QVBoxLayout();

    visualScroll = new QScrollArea;
    visualScroll->setWidgetResizable(true);
    visualScroll->setFrameShape(QFrame::NoFrame);
    visualScroll->setWidget(seriesWidget);
    seriesBox->addWidget(visualScroll);

    int i=0;
    for(auto it = qontainer.begin(); it != qontainer.end(); ++it) {
        if(dynamic_cast<tvseries*>(*it)) {
            QPushButton* visualSerieButton = new QPushButton();
            visualSerieButton->setText(QString::fromStdString((*it)->getTitle()));
            visualSerieButton->setFixedSize(250, 25);
            visualSerieButton->setObjectName(QString::number(i));

            seriesGrid->addWidget(visualSerieButton, i, 0);

            connect(visualSerieButton, SIGNAL(clicked()), this, SLOT(onClickVisualSerie()));

            ++i;
        }
    }
    seriesWidget->setLayout(seriesGrid);
    contGrid->addLayout(seriesBox, 2, 1 ,Qt::AlignCenter);
}

void MainWindow::visualAnime() {

    QWidget* animeWidget = new QWidget();
    QGridLayout* animeGrid = new QGridLayout();
    QVBoxLayout* animeBox= new QVBoxLayout();

    visualScroll = new QScrollArea;
    visualScroll->setWidgetResizable(true);
    visualScroll->setFrameShape(QFrame::NoFrame);
    visualScroll->setWidget(animeWidget);
    animeBox->addWidget(visualScroll);


    int i=0;
    for(auto it = qontainer.begin(); it != qontainer.end(); ++it) {
        if(dynamic_cast<animation*>(*it)) {
            QPushButton* visualAnimeButton = new QPushButton();
            visualAnimeButton->setText(QString::fromStdString((*it)->getTitle()));
            visualAnimeButton->setFixedSize(250, 25);
            visualAnimeButton->setObjectName(QString::number(i));

            animeGrid->addWidget(visualAnimeButton, i, 0);

            connect(visualAnimeButton, SIGNAL(clicked()), this, SLOT(onClickVisualAnime()));

            ++i;
        }
    }
    animeWidget->setLayout(animeGrid);
    contGrid->addLayout(animeBox, 3, 1 ,Qt::AlignCenter);
}

void MainWindow::onClickVisualFilm() {
    QPushButton* visualFilmButton = dynamic_cast<QPushButton*>(sender());
    if(visualFilmButton) {
        int index = visualFilmButton->objectName().toInt(), i = 0;
        film* f = nullptr, *visualize = nullptr;
        for(auto it = qontainer.begin(); it != qontainer.end(); ++it) {
            f = dynamic_cast<film*>(*it);
            if(f) {
                if(i == index) {
                    visualize = dynamic_cast<film*>(*it);
                    startVisualFilm(visualize);
                    return;
                }
                else
                    ++i;
            }
        }
    }
}

void MainWindow::onClickVisualSerie() {
    QPushButton* visualSerieButton = dynamic_cast<QPushButton*>(sender());
    if(visualSerieButton) {
        int index = visualSerieButton->objectName().toInt(), i = 0;
        tvseries* tv = nullptr, *visualize = nullptr;
        for(auto it = qontainer.begin(); it != qontainer.end(); ++it) {
            tv = dynamic_cast<tvseries*>(*it);
            if(tv) {
                if(i == index) {
                    visualize = dynamic_cast<tvseries*>(*it);
                    startVisualSerie(visualize);
                    return;
                }
                else
                    ++i;
            }
        }
    }
}

void MainWindow::onClickVisualAnime() {
    QPushButton* visualAnimeButton = dynamic_cast<QPushButton*>(sender());
    if(visualAnimeButton) {
        int index = visualAnimeButton->objectName().toInt(), i = 0;
        animation* a = nullptr, *visualize = nullptr;
        for(auto it = qontainer.begin(); it != qontainer.end(); ++it) {
            a = dynamic_cast<animation*>(*it);
            if(a) {
                if(i == index) {
                    visualize = dynamic_cast<animation*>(*it);
                    startVisualAnime(visualize);
                    return;
                }
                else
                    ++i;
            }
        }
    }
}

void MainWindow::startVisualFilm(film* f) {
    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle("Visualizza Film");

    form = new QFormLayout(dialog);

    dialog->setFont(QFont("Arial", 18));

    QLabel* title = new QLabel();
    title->setText(QString::fromStdString(f->getTitle()));
    title->setFont(QFont("Arial", 34));
    title->setAlignment(Qt::AlignCenter);
    QLabel* vuota = new QLabel();
    vuota->setFixedHeight(15);
    QLabel* duration = new QLabel();
    int dur = f->getDuration();
    if(dur > 60) {
        int ore = dur/60;
        int min = dur%60;
        duration->setText((QString::number(ore)) + " ore e " + (QString::number(min)) + " minuti");
    }
    else if(dur == 60)
        duration->setText("Un'ora");
    else
        duration->setText((QString::number(dur)) + " minuti");
    QLabel* genre = new QLabel();
    genre->setText(QString::fromStdString(f->getGenre()));
    QLabel* year = new QLabel();
    year->setText(QString::number(f->getYear()));
    QLabel* plot = new QLabel();
    plot->setText(QString::fromStdString((f->getPlot())));
    plot->setFixedWidth(360);
    plot->setScaledContents(true);
    plot->setWordWrap(true);
    QLabel* director = new QLabel();
    director->setText(QString::fromStdString(f->getDirector()));
    QLabel* saga = new QLabel();
    saga->setText(QString::fromStdString(f->getSaga()));
    QLabel* country = new QLabel();
    country->setText(QString::fromStdString(f->getCountry()));

    form->addRow(title);
    if(f->getDuration() != 0) form->addRow(duration);
    form->addRow(genre);
    if(f->getYear() != 0) form->addRow(year);
    form->addRow(plot);
    form->addRow(director);
    form->addRow(saga);
    form->addRow(country);

    form->addRow(vuota);

    QDialogButtonBox* B = new QDialogButtonBox(Qt::Horizontal);
    B->addButton(tr("Modifica/Elimina"), QDialogButtonBox::AcceptRole);

    form->addRow(B);

    connect(B, SIGNAL(accepted()), dialog, SLOT(accept()));
    connect(B, SIGNAL(rejected()), dialog, SLOT(reject()));

    if(dialog->exec() == QDialog::Accepted) {
        QMessageBox msg;
        msg.setText("Vuoi modificare o eliminare il film?");
        QPushButton* goBack = new QPushButton();
        goBack->setText("Indietro");
        QPushButton* modifyButton = new QPushButton();
        modifyButton->setText("Modifica");
        QPushButton* deleteButton = new QPushButton();
        deleteButton->setText("Elimina");
        msg.addButton(goBack, QMessageBox::RejectRole);
        msg.addButton(modifyButton, QMessageBox::YesRole);
        msg.addButton(deleteButton, QMessageBox::YesRole);
        msg.setDefaultButton(goBack);

        msg.exec();

        if(msg.clickedButton() == modifyButton)
            modifyPage(f);
        else if(msg.clickedButton() == deleteButton) {
            QMessageBox deleteMsg;
            deleteMsg.setText("Confermare l'operazione?");
            QPushButton* yesButton = deleteMsg.addButton(tr("Si"), QMessageBox::YesRole);
            QPushButton* noButton = deleteMsg.addButton(tr("No"), QMessageBox::NoRole);
            deleteMsg.setDefaultButton(noButton);
            deleteMsg.exec();
            if(deleteMsg.clickedButton() == yesButton) {
                deleteElement(f);
                visualFilm();
                deleteMsg.setText("Film eliminato con successo!");
            }
        }
    }
}

void MainWindow::startVisualSerie(tvseries* tv) {
    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle("Visualizza Serie Tv");

    form = new QFormLayout(dialog);

    dialog->setFont(QFont("Arial", 18));

    QLabel* title = new QLabel();
    title->setText(QString::fromStdString(tv->getTitle()));
    title->setFont(QFont("Arial", 34));
    title->setAlignment(Qt::AlignCenter);
    QLabel* vuota = new QLabel();
    vuota->setFixedHeight(15);
    QLabel* duration = new QLabel();
    int dur = tv->getDuration();
    if(dur > 60) {
        int ore = dur/60;
        int min = dur%60;
        duration->setText((QString::number(ore)) + " ore e " + (QString::number(min)) + " minuti");
    }
    else if(dur == 60)
        duration->setText("Un'ora");
    else
        duration->setText((QString::number(dur)) + " minuti");
    QLabel* genre = new QLabel();
    genre->setText(QString::fromStdString(tv->getGenre()));
    QLabel* year = new QLabel();
    year->setText(QString::number(tv->getYear()));
    QLabel* plot = new QLabel();
    plot->setText(QString::fromStdString((tv->getPlot())));
    plot->setFixedWidth(360);
    plot->setScaledContents(true);
    plot->setWordWrap(true);
    QLabel* ideator = new QLabel();
    ideator->setText(QString::fromStdString(tv->getIdeator()));
    QLabel* season = new QLabel();
    season->setText(QString::number(tv->getSeason()) + "ª stagione");
    QLabel* episodes = new QLabel();
    episodes->setText(QString::number(tv->getEpisodes()) + " episodi");

    form->addRow(title);
    if(tv->getDuration() != 0) form->addRow(duration);
    form->addRow(genre);
    if(tv->getYear() != 0) form->addRow(year);
    form->addRow(plot);
    form->addRow(ideator);
    if(tv->getSeason() != 0) form->addRow(season);
    if(tv->getEpisodes() != 0) form->addRow(episodes);

    form->addRow(vuota);

    QDialogButtonBox* B = new QDialogButtonBox(Qt::Horizontal);
    B->addButton(tr("Modifica/Elimina"), QDialogButtonBox::AcceptRole);

    form->addRow(B);

    connect(B, SIGNAL(accepted()), dialog, SLOT(accept()));
    connect(B, SIGNAL(rejected()), dialog, SLOT(reject()));

    if(dialog->exec() == QDialog::Accepted) {
        QMessageBox msg;
        msg.setText("Vuoi modificare o eliminare la serie?");
        QPushButton* goBack = new QPushButton();
        goBack->setText("Indietro");
        QPushButton* modifyButton = new QPushButton();
        modifyButton->setText("Modifica");
        QPushButton* deleteButton = new QPushButton();
        deleteButton->setText("Elimina");
        msg.addButton(goBack, QMessageBox::RejectRole);
        msg.addButton(modifyButton, QMessageBox::YesRole);
        msg.addButton(deleteButton, QMessageBox::YesRole);
        msg.setDefaultButton(goBack);

        msg.exec();

        if(msg.clickedButton() == modifyButton)
            modifyPage(tv);
        else if(msg.clickedButton() == deleteButton) {
            QMessageBox deleteMsg;
            deleteMsg.setText("Confermare l'operazione?");
            QPushButton* yesButton = deleteMsg.addButton(tr("Si"), QMessageBox::YesRole);
            QPushButton* noButton = deleteMsg.addButton(tr("No"), QMessageBox::NoRole);
            deleteMsg.setDefaultButton(noButton);
            deleteMsg.exec();
            if(deleteMsg.clickedButton() == yesButton) {
                deleteElement(tv);
                visualSeries();
                deleteMsg.setText("Serie Tv eliminata con successo!");
            }
        }
    }    
}

void MainWindow::startVisualAnime(animation* a) {
    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle("Visualizza Anime");

    form = new QFormLayout(dialog);

    dialog->setFont(QFont("Arial", 18));

    QLabel* title = new QLabel();
    title->setText(QString::fromStdString(a->getTitle()));
    title->setFont(QFont("Arial", 34));
    title->setAlignment(Qt::AlignCenter);
    QLabel* vuota = new QLabel();
    vuota->setFixedHeight(15);
    QLabel* duration = new QLabel();
    int dur = a->getDuration();
    if(dur > 60) {
        int ore = dur/60;
        int min = dur%60;
        duration->setText((QString::number(ore)) + " ore e " + (QString::number(min)) + " minuti");
    }
    else if(dur == 60)
        duration->setText("Un'ora");
    else
        duration->setText((QString::number(dur)) + " minuti");    QLabel* genre = new QLabel();
    genre->setText(QString::fromStdString(a->getGenre()));
    QLabel* year = new QLabel();
    year->setText(QString::number(a->getYear()));
    QLabel* plot = new QLabel();
    plot->setText(QString::fromStdString((a->getPlot())));
    plot->setFixedWidth(360);
    plot->setScaledContents(true);
    plot->setWordWrap(true);
    QLabel* country = new QLabel();
    country->setText(QString::fromStdString(a->getCountry()));
    QLabel* season = new QLabel();
    season->setText(QString::number(a->getSeason()) + "ª stagione");
    QLabel* episodes = new QLabel();
    episodes->setText(QString::number(a->getEpisodes()) + " episodi");

    form->addRow(title);
    if(a->getDuration() != 0) form->addRow(duration);
    form->addRow(genre);
    if(a->getYear() != 0) form->addRow(year);
    form->addRow(plot);
    form->addRow(country);
    if(a->getSeason() != 0) form->addRow(season);
    if(a->getEpisodes() != 0) form->addRow(episodes);

    form->addRow(vuota);

    QDialogButtonBox* B = new QDialogButtonBox(Qt::Horizontal);
    B->addButton(tr("Modifica/Elimina"), QDialogButtonBox::AcceptRole);

    form->addRow(B);

    connect(B, SIGNAL(accepted()), dialog, SLOT(accept()));
    connect(B, SIGNAL(rejected()), dialog, SLOT(reject()));

    if(dialog->exec() == QDialog::Accepted) {
        QMessageBox msg;
        msg.setText("Vuoi modificare o eliminare l'anime?");
        QPushButton* goBack = new QPushButton();
        goBack->setText("Indietro");
        QPushButton* modifyButton = new QPushButton();
        modifyButton->setText("Modifica");
        QPushButton* deleteButton = new QPushButton();
        deleteButton->setText("Elimina");
        msg.addButton(goBack, QMessageBox::RejectRole);
        msg.addButton(modifyButton, QMessageBox::YesRole);
        msg.addButton(deleteButton, QMessageBox::YesRole);
        msg.setDefaultButton(goBack);

        msg.exec();

        if(msg.clickedButton() == modifyButton)
            modifyPage(a);
        else if(msg.clickedButton() == deleteButton) {
            QMessageBox deleteMsg;
            deleteMsg.setText("Confermare l'operazione?");
            QPushButton* yesButton = deleteMsg.addButton(tr("Si"), QMessageBox::YesRole);
            QPushButton* noButton = deleteMsg.addButton(tr("No"), QMessageBox::NoRole);
            deleteMsg.setDefaultButton(noButton);
            deleteMsg.exec();
            if(deleteMsg.clickedButton() == yesButton) {
                deleteElement(a);
                visualAnime();
                deleteMsg.setText("Anime eliminato con successo!");
            }
        }
    }
}

//----------------------------------ADD----------------------------------

void MainWindow::addLabel(QString name, QString place, QFormLayout* form) {
    QLabel* label = new QLabel(this);
    label->setText(name);
    label->setFixedHeight(25);
    QLineEdit* box = new QLineEdit(this);
    box->setFixedSize(350, 25);
    box->setPlaceholderText(place);

    addVector.push_back(box);

    form->addRow(label);
    form->addRow(box);
}

void MainWindow::onClickAddFilm() {
    QDialog* dialog = new QDialog(this);
    dialog->setFixedSize(400, 450);
    dialog->setWindowTitle("Aggiungi un film");

    addVector.clear();

    form = new QFormLayout(dialog);

    addLabel("Titolo:", "Inserisci il titolo", form);
    addLabel("Durata", "Inserisci la durata in minuti", form);
    addLabel("Genere:", "Inserisci il genere", form);
    addLabel("Anno", "Inserisci l'anno di uscita", form);
    addLabel("Trama:", "Inserisci la trama in breve", form);
    addLabel("Regista:", "Inserisci il regista", form);
    addLabel("Saga:", "Inserisci la saga", form);
    addLabel("Paese:", "Inserisci il paese di produzione", form);

    QLabel* vuota = new QLabel();
    vuota->setFixedHeight(15);

    form->addRow(vuota);

    QDialogButtonBox* B=new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, dialog);
    form->addRow(B);

    QObject::connect(B, SIGNAL(accepted()), dialog, SLOT(accept()));
    QObject::connect(B, SIGNAL(rejected()), dialog, SLOT(reject()));

    if(dialog->exec() == QDialog::Accepted) {
        string title, genre, plot, director, saga, country;
        int duration, year;

        title = addVector[0]->text().toStdString();
        duration = addVector[1]->text().toInt();
        genre = addVector[2]->text().toStdString();
        year = addVector[3]->text().toInt();
        plot = addVector[4]->text().toStdString();
        director = addVector[5]->text().toStdString();
        saga = addVector[6]->text().toStdString();
        country = addVector[7]->text().toStdString();

        movieitem* f = new film(title, duration, genre, year, plot, 1, director, saga, country);
        qontainer.push_back(f);

        visualFilm();

        QMessageBox m;
        m.setText("Film aggiunto con successo!");
        m.exec();
    }
}

void MainWindow::onClickAddSerie() {
    QDialog* dialog = new QDialog(this);
    dialog->setFixedSize(400, 450);
    dialog->setWindowTitle("Aggiungi una serie tv");
    form = new QFormLayout(dialog);

    addVector.clear();

    addLabel("Titolo:", "Inserisci il titolo", form);
    addLabel("Durata", "Inserisci la durata in minuti", form);
    addLabel("Genere:", "Inserisci il genere", form);
    addLabel("Anno", "Inserisci l'anno di uscita", form);
    addLabel("Trama:", "Inserisci la trama in breve", form);
    addLabel("Ideatore:", "Inserisci l'ideatore", form);
    addLabel("Stagione:", "Inserisci la stagione", form);
    addLabel("Episodi:", "Inserisci gli episodi", form);

    QLabel* vuota = new QLabel();
    vuota->setFixedHeight(15);

    form->addRow(vuota);

    QDialogButtonBox* B=new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, dialog);
    form->addRow(B);

    QObject::connect(B, SIGNAL(accepted()), dialog, SLOT(accept()));
    QObject::connect(B, SIGNAL(rejected()), dialog, SLOT(reject()));

    if(dialog->exec() == QDialog::Accepted) {
        string title, genre, plot, ideator;
        int duration, year, season, episodes;

        title = addVector[0]->text().toStdString();
        duration = addVector[1]->text().toInt();
        genre = addVector[2]->text().toStdString();
        year = addVector[3]->text().toInt();
        plot = addVector[4]->text().toStdString();
        ideator = addVector[5]->text().toStdString();
        season = addVector[6]->text().toInt();
        episodes = addVector[7]->text().toInt();

        movieitem* tv = new tvseries(title, duration, genre, year, plot, 2, ideator, season, episodes);
        qontainer.push_back(tv);

        visualSeries();

        QMessageBox m;
        m.setText("Serie Tv aggiunta con successo!");
        m.exec();
    }
}

void MainWindow::onClickAddAnime() {
    QDialog* dialog = new QDialog(this);
    dialog->setFixedSize(400, 450);
    dialog->setWindowTitle("Aggiungi un anime");
    form = new QFormLayout(dialog);

    addVector.clear();

    addLabel("Titolo:", "Inserisci il titolo", form);
    addLabel("Durata", "Inserisci la durata in minuti", form);
    addLabel("Genere:", "Inserisci il genere", form);
    addLabel("Anno", "Inserisci l'anno di uscita", form);
    addLabel("Trama:", "Inserisci la trama in breve", form);
    addLabel("Paese:", "Inserisci il paese di produzione", form);
    addLabel("Stagione:", "Inserisci la stagione", form);
    addLabel("Episodi", "Inserisci gli episodi", form);

    QLabel* vuota = new QLabel();
    vuota->setFixedHeight(15);

    form->addRow(vuota);

    QDialogButtonBox* B=new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, dialog);
    form->addRow(B);

    QObject::connect(B, SIGNAL(accepted()), dialog, SLOT(accept()));
    QObject::connect(B, SIGNAL(rejected()), dialog, SLOT(reject()));

    if(dialog->exec() == QDialog::Accepted) {
        string title, genre, plot, country;
        int duration, year, season, episodes;

        title = addVector[0]->text().toStdString();
        duration = addVector[1]->text().toInt();
        genre = addVector[2]->text().toStdString();
        year = addVector[3]->text().toInt();
        plot = addVector[4]->text().toStdString();
        country = addVector[5]->text().toStdString();
        season = addVector[6]->text().toInt();
        episodes = addVector[7]->text().toInt();

        movieitem* a = new animation(title, duration, genre, year, plot, 3, country, season, episodes);
        qontainer.push_back(a);

        visualAnime();

        QMessageBox m;
        m.setText("Anime aggiunto con successo!");
        m.exec();
    }
}

//-------------------------------SEARCH--------------------------------

void MainWindow::onClickSearch() {
    resultVector.clear();
    string tit = titleLine->text().toStdString();
    string gnr = genreLine->text().toStdString();
    int year = yearLine->text().toInt();
    if(!titleLine->text().isEmpty() && genreLine->text().isEmpty() && year == 0) {
        for(auto it = qontainer.cbegin(); it != qontainer.cend(); ++it) {
            if(tit == (*it)->getTitle())
                resultVector.push_back(*it);
        }
        if(resultVector.empty()) {
            QMessageBox m;
            m.setText("OPS! La ricerca non è andata a buon fine!");
            m.exec();
        }
        else
            viewResultSearch(resultVector);
    }
    else if(titleLine->text().isEmpty() && !genreLine->text().isEmpty() && year == 0) {
        for(auto it = qontainer.cbegin(); it != qontainer.cend(); ++it) {
            if(gnr == (*it)->getGenre())
                resultVector.push_back(*it);
        }
        if(resultVector.empty()) {
            QMessageBox m;
            m.setText("OPS! La ricerca non è andata a buon fine!");
            m.exec();
        }
        else
            viewResultSearch(resultVector);
    }
    else if(titleLine->text().isEmpty() && genreLine->text().isEmpty() && year != 0) {
        for(auto it = qontainer.cbegin(); it != qontainer.cend(); ++it) {
            if(year == (*it)->getYear())
                resultVector.push_back(*it);
        }
        if(resultVector.empty()) {
            QMessageBox m;
            m.setText("OPS! La ricerca non è andata a buon fine!");
            m.exec();
        }
        else
            viewResultSearch(resultVector);
    }
    else if(!titleLine->text().isEmpty() && !genreLine->text().isEmpty() && year == 0) {
        for(auto it = qontainer.cbegin(); it != qontainer.cend(); ++it) {
            if(tit == (*it)->getTitle() && gnr == (*it)->getGenre())
                resultVector.push_back(*it);
        }
        if(resultVector.empty()) {
            QMessageBox m;
            m.setText("OPS! La ricerca non è andata a buon fine!");
            m.exec();
        }
        else
            viewResultSearch(resultVector);
    }
    else if(!titleLine->text().isEmpty() && genreLine->text().isEmpty() && year != 0) {
        for(auto it = qontainer.cbegin(); it != qontainer.cend(); ++it) {
            if(tit == (*it)->getTitle() && year == (*it)->getYear())
                resultVector.push_back(*it);
        }
        if(resultVector.empty()) {
            QMessageBox m;
            m.setText("OPS! La ricerca non è andata a buon fine!");
            m.exec();
        }
        else
            viewResultSearch(resultVector);
    }
    else if(titleLine->text().isEmpty() && !genreLine->text().isEmpty() && year != 0) {
        for(auto it = qontainer.cbegin(); it != qontainer.cend(); ++it) {
            if(gnr == (*it)->getGenre() && year == (*it)->getYear())
                resultVector.push_back(*it);
        }
        if(resultVector.empty()) {
            QMessageBox m;
            m.setText("OPS! La ricerca non è andata a buon fine!");
            m.exec();
        }
        else
            viewResultSearch(resultVector);
    }
    else if(!titleLine->text().isEmpty() && !genreLine->text().isEmpty() && year != 0) {
        for(auto it = qontainer.cbegin(); it != qontainer.cend(); ++it) {
            if(tit == (*it)->getTitle() && gnr == (*it)->getGenre() && year == (*it)->getYear())
                resultVector.push_back(*it);
        }
        if(resultVector.empty()) {
            QMessageBox m;
            m.setText("OPS! La ricerca non è andata a buon fine!");
            m.exec();
        }
        else
            viewResultSearch(resultVector);
    }
}

void MainWindow::viewResultSearch(vector<movieitem*> resultVector) {
    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle("Risultati della ricerca");

    form = new QFormLayout(dialog);
    int i = 0;
    for(auto it = resultVector.begin(); it != resultVector.end(); ++it, i++) {
        QPushButton* button = new QPushButton();
        button->setFixedSize(250, 25);
        button->setText(QString::fromStdString((*it)->getTitle()));
        button->setObjectName(QString::number(i));
        form->addRow(button);

        connect(button, SIGNAL(clicked()), this, SLOT(onClickVisualize()));
    }

    QLabel* vuota = new QLabel();
    vuota->setFixedHeight(15);

    form->addRow(vuota);

    QDialogButtonBox* B=new QDialogButtonBox(dialog);
    B->addButton(tr("Elimina tutti"), QDialogButtonBox::AcceptRole);
    B->addButton(tr("Indietro"), QDialogButtonBox::RejectRole);

    form->addRow(B);
    QObject::connect(B, SIGNAL(accepted()), dialog, SLOT(accept()));
    QObject::connect(B, SIGNAL(rejected()), dialog, SLOT(reject()));

    dialog->exec();

    if(QDialog::Accepted) {
        QMessageBox deleteMsg;
        deleteMsg.setText("Confermare l'operazione?");
        QPushButton* yesButton = deleteMsg.addButton(tr("Si"), QMessageBox::YesRole);
        QPushButton* noButton = deleteMsg.addButton(tr("No"), QMessageBox::NoRole);
        deleteMsg.setDefaultButton(noButton);
        deleteMsg.exec();
        if(deleteMsg.clickedButton() == yesButton) {
            for(auto it = resultVector.begin(); it != resultVector.end(); ++it)
                qontainer.erase(*it);
            visualFilm();
            visualSeries();
            visualAnime();
        }

    }
}

void MainWindow::onClickVisualize() {
    QPushButton* button = dynamic_cast<QPushButton*>(sender());
    if (button) {
        int indice = button->objectName().toInt(), i=0;
        movieitem* m = nullptr;
        for(auto it=resultVector.begin(); it!=resultVector.end() && i<=indice; ++it){
            if(i==indice) {
                m=*it;
                film* f = dynamic_cast<film*>(m);
                if(f) {
                    startVisualFilm(f);
                    return;
                }
                tvseries* tv = dynamic_cast<tvseries*>(m);
                if(tv) {
                    startVisualSerie(tv);
                    return;
                }
                animation* a = dynamic_cast<animation*>(m);
                if(a) {
                    startVisualAnime(a);
                    return;
                }
            }
            else
                ++i;
        }
    }
}


//-----------------------------MODIFY--------------------------------

void MainWindow::modifyPage(movieitem* m) {
    QDialog* dialog = new QDialog(this);
    dialog->setFixedSize(400, 450);
    dialog->setWindowTitle("Aggiungi un film");

    addVector.clear();

    form = new QFormLayout(dialog);

    addLabel("Titolo:", "Inserisci il titolo", form);
    addLabel("Durata", "Inserisci la durata in minuti", form);
    addLabel("Genere:", "Inserisci il genere", form);
    addLabel("Anno", "Inserisci l'anno di uscita", form);
    addLabel("Trama:", "Inserisci la trama in breve", form);

    film* f = dynamic_cast<film*>(m);
    if(f) {
        addLabel("Regista:", "Inserisci il regista", form);
        addLabel("Saga:", "Inserisci la saga", form);
        addLabel("Paese:", "Inserisci il paese di produzione", form);
    }
    tvseries* tv = dynamic_cast<tvseries*>(m);
    if(tv) {
        addLabel("Ideatore:", "Inserisci l'ideatore", form);
        addLabel("Stagione:", "Inserisci la stagione", form);
        addLabel("Episodi:", "Inserisci gli episodi", form);
    }
    animation* a = dynamic_cast<animation*>(m);
    if(a) {
        addLabel("Paese:", "Inserisci il paese di produzione", form);
        addLabel("Stagione:", "Inserisci la stagione", form);
        addLabel("Episodi:", "Inserisci gli episodi", form);
    }

    QLabel* vuota = new QLabel();
    vuota->setFixedHeight(15);

    form->addRow(vuota);

    QDialogButtonBox* B=new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, dialog);
    form->addRow(B);

    QObject::connect(B, SIGNAL(accepted()), dialog, SLOT(accept()));
    QObject::connect(B, SIGNAL(rejected()), dialog, SLOT(reject()));

    if(dialog->exec() == QDialog::Accepted) {
        string title, genre, plot;
        int duration, year;

        if(f) {
            string director, saga, country;
            if(!addVector[0]->text().isEmpty()) {
                title = addVector[0]->text().toStdString();
                f->setTitle(title);
            }
            if(!addVector[1]->text().isEmpty()) {
                duration = addVector[1]->text().toInt();
                f->setDuration(duration);
            }
            if(!addVector[2]->text().isEmpty()) {
                genre = addVector[2]->text().toStdString();
                f->setGenre(genre);
            }
            if(!addVector[3]->text().isEmpty()) {
                year = addVector[3]->text().toInt();
                f->setYear(year);
            }
            if(!addVector[4]->text().isEmpty()) {
                plot = addVector[4]->text().toStdString();
                f->setPlot(plot);
            }
            if(!addVector[5]->text().isEmpty()) {
                director = addVector[5]->text().toStdString();
                f->setDirector(director);
            }
            if(!addVector[6]->text().isEmpty()) {
                saga = addVector[6]->text().toStdString();
                f->setSaga(saga);
            }
            if(!addVector[7]->text().isEmpty()) {
                country = addVector[7]->text().toStdString();
                f->setCountry(country);
            }
            QMessageBox m;
            m.setText("Film modificato con successo!");
            m.exec();
            visualFilm();
        }
        if(tv) {
            string ideator;
            int season, episodes;
            if(!addVector[0]->text().isEmpty()) {
                title = addVector[0]->text().toStdString();
                tv->setTitle(title);
            }
            if(!addVector[1]->text().isEmpty()) {
                duration = addVector[1]->text().toInt();
                tv->setDuration(duration);
            }
            if(!addVector[2]->text().isEmpty()) {
                genre = addVector[2]->text().toStdString();
                tv->setGenre(genre);
            }
            if(!addVector[3]->text().isEmpty()) {
                year = addVector[3]->text().toInt();
                tv->setYear(year);
            }
            if(!addVector[4]->text().isEmpty()) {
                plot = addVector[4]->text().toStdString();
                tv->setPlot(plot);
            }
            if(!addVector[5]->text().isEmpty()) {
                ideator = addVector[5]->text().toStdString();
                tv->setIdeator(ideator);
            }
            if(!addVector[6]->text().isEmpty()) {
                season = addVector[6]->text().toInt();
                tv->setSeason(season);
            }
            if(!addVector[7]->text().isEmpty()) {
                episodes = addVector[7]->text().toInt();
                tv->setEpisodes(episodes);
            }
            QMessageBox m;
            m.setText("Serie tv modificata con successo!");
            m.exec();
            visualSeries();
        }
        if(a) {
            string country;
            int season, episodes;
            if(!addVector[0]->text().isEmpty()) {
                title = addVector[0]->text().toStdString();
                a->setTitle(title);
            }
            if(!addVector[1]->text().isEmpty()) {
                duration = addVector[1]->text().toInt();
                a->setDuration(duration);
            }
            if(!addVector[2]->text().isEmpty()) {
                genre = addVector[2]->text().toStdString();
                a->setGenre(genre);
            }
            if(!addVector[3]->text().isEmpty()) {
                year = addVector[3]->text().toInt();
                a->setYear(year);
            }
            if(!addVector[4]->text().isEmpty()) {
                plot = addVector[4]->text().toStdString();
                a->setPlot(plot);
            }
            if(!addVector[5]->text().isEmpty()) {
                country = addVector[5]->text().toStdString();
                a->setCountry(country);
            }
            if(!addVector[6]->text().isEmpty()) {
                season = addVector[6]->text().toInt();
                a->setSeason(season);
            }
            if(!addVector[7]->text().isEmpty()) {
                episodes = addVector[7]->text().toInt();
                a->setEpisodes(episodes);
            }
            QMessageBox m;
            m.setText("Anime modificato con successo!");
            m.exec();
            visualAnime();

        }
    }
}

//---------------------------DELETE----------------------------

void MainWindow::deleteElement(movieitem* m) {
    qontainer.erase(m);
    visualFilm();
    visualSeries();
    visualAnime();
}
