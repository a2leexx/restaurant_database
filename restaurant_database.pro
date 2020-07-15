#-------------------------------------------------
#
# Project created by QtCreator 2016-12-21T23:21:09
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = restaurant_database
TEMPLATE = app

CONFIG += C++11


SOURCES += main.cpp\
        mainwindow.cpp \
    inputaddressdialog.cpp \
    inputpositiondialog.cpp \
    inputemployeedialog.cpp \
    inputemployeelastname.cpp \
    positionsqlmodel.cpp \
    connectiondialog.cpp

HEADERS  += mainwindow.h \
    inputaddressdialog.h \
    inputpositiondialog.h \
    inputemployeedialog.h \
    inputemployeelastname.h \
    positionsqlmodel.h \
    connectiondialog.h

FORMS    += mainwindow.ui

DISTFILES += \
    .gitignore \
    README.md \
    images/add_position.png \
    images/login.png \
    images/positions.png \
    images/statistics.png
