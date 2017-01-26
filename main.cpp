#include <QtGui/QApplication>
#include <QTextCodec>
#include "core.h"
//#include "neuronmainwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForTr(QTextCodec::codecForName ("Windows-1251"));

    Core::instance().init_core();
    //NeuronMainWidget main_widget;
    //main_widget.show();
    //neur wnd;
    //wnd.show();

    return a.exec();
}
