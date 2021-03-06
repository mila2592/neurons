QT       += core gui

TARGET = neur2
TEMPLATE = app

#QMAKE_CXXFLAGS += -std=c++11

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
           functions.cpp \
           neuronmainwidget.cpp \
           core.cpp \
           neuronnet.cpp \
    connections.cpp \
    neuron.cpp \
    netmap.cpp

HEADERS  += neuron.h \
    mainwindow.h \
    neuronmainwidget.h \
    core.h \
    neuronnet.h \
    connections.h \
    plasticity.h \
    netmap.h

QWT_ROOT = c:/qwt-6.1.3

INCLUDEPATH += $${QWT_ROOT}/src

win32{
    LIBS += $${QWT_ROOT}/lib/libqwtd.a
}
unix{
    LIBS += $${QWT_ROOT}/lib/libqwt.so.5.2.1
}

FORMS += \
    neuronmainwidget.ui








