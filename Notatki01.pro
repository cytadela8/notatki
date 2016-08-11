#-------------------------------------------------
#
# Project created by QtCreator 2016-07-18T12:14:47
#
#-------------------------------------------------

QT += core gui
QT += testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Notatki01
TEMPLATE = app


SOURCES += main.cpp\
        mainview.cpp \
    sidemenu.cpp \
    touchbutton.cpp

HEADERS  += mainview.h \
    sidemenu.h \
    touchbutton.h

CONFIG += mobility \
    c++14

MOBILITY =

QMAKE_CXXFLAGS += -std=c++14
