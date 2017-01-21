#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    neur *wnd=new neur;

    wnd->show();
//    QMenuBar mb;
//    QMenu* mu=new QMenu("&Menu");
//    mu->addSeparator();
//    mu->addAction("&exit",&a,SLOT(exx(bool)));
//    mb.addMenu(mu);
//    mb.show();


    return a.exec();
}
