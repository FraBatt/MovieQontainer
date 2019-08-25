#include "View/mainwindow.h"
#include <QApplication>
#include <QWidget>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
