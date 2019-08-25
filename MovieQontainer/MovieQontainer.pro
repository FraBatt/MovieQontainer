#-------------------------------------------------
#
# Project created by QtCreator 2019-08-18T17:18:09
#
#-------------------------------------------------

QT       += core
QT += core
QT += widgets
QT += gui
QMAKE_CXXFLAGS += -std=c++11
CONFIG += sdk_no_version_check

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MovieQontainer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
    View/mainwindow.cpp \
    Model/movieitem.cpp \
    Model/film.cpp \
    Model/tvseries.cpp \
    Model/animation.cpp \
    Model/managefile.cpp \
    Model/myexception.cpp \

HEADERS += \
    View/mainwindow.h \
    Model/movieitem.h \
    Model/qontainer.h \
    Model/film.h \
    Model/tvseries.h \
    Model/animation.h \
    Model/managefile.h \
    Model/myexception.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    images/moviecontainer-logo.png \
    View/logo.png \
    View/logo1.jpeg
