#-------------------------------------------------
#
# Project created by QtCreator 2014-01-27T14:22:34
#
#-------------------------------------------------

QT       += core gui

TARGET = neur2
TEMPLATE = app

# binary files destination
DESTDIR = build/

# Metaobject compiller files
MOC_DIR = moc/

# Object files
OBJECTS_DIR = obj/

# ui header files
UI_DIR = ui_generated/

INCLUDEPATH += ui_generated/

SOURCES += main.cpp\
           mainwindow.cpp \
           functions.cpp

HEADERS  += mainwindow.h

QWT_ROOT = c:/qwt-6.1.3

INCLUDEPATH += $${QWT_ROOT}/src

win32{
    LIBS += $${QWT_ROOT}/lib/libqwtd.a
}
unix{
    LIBS += $${QWT_ROOT}/lib/libqwt.so.5.2.1
}
