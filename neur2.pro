#-------------------------------------------------
#
# Project created by QtCreator 2014-01-27T14:22:34
#
#-------------------------------------------------

QT       += core gui

TARGET = neur2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    functions.cpp

HEADERS  += mainwindow.h
INCLUDEPATH +=c:/qwt-6.1.3/src

LIBS +=c:/qwt-6.1.3/lib/libqwtd.a
LIBS +=c:/qwt-6.1.3/lib/libqwt.a

INCLUDEPATH +=c:/Python27/include


EIGEN_PATH  = C:/eigen-eigen-f562a193118d
INCLUDEPATH += $${EIGEN_PATH}











