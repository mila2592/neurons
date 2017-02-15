#include <QtGui/QApplication>
#include <QTextCodec>
//#include "core.h"
#include "netmap.h"
//#include "neuronmainwidget.h"
#include "mainwindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForTr(QTextCodec::codecForName ("Windows-1251"));

        NetMap wnd;
        wnd.show();

//    Core::instance().init_core();

//////////////////////////////////
//    NeuronMainWidget main_widget;
//    main_widget.show();

////////////////////////
//    neur wnd;
//    wnd.show();
///////////////////////
    return a.exec();
}
