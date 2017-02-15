#include "netmap.h"

NetMap::NetMap(QWidget *parent) :
    QWidget(parent)
{
    //    QTimer tm;
    int sc=500;
    img = new QImage(QSize(sc, sc), QImage::Format_ARGB32_Premultiplied);


    QPalette pal;
    pal.setBrush(this->backgroundRole(), QBrush(QPixmap::fromImage(*img)));
    this->setPalette(pal);
    this->resize(sc, sc);
    this->setAutoFillBackground(true);

    this->show();

    NeuronNet net1;
    QObject::connect(&net1,SIGNAL(newNeuronSignal(int,int,int)),this, SLOT(drawNewNeuron(int, int,int)));

    net1.add_layer(100,25);

    //    net1.add_layer(100,25);


    std::cout<<net1.size_of_lay(0)<<std::endl;

    net1.connect_layers(0, 0);

    QObject::connect(&net1,SIGNAL(spikeSignal(int,int,int)),this, SLOT(drawSpike(int, int,int)));


    net1.tmp();

}

void NetMap::drawNewNeuron(int x, int y,int id)
{
    QPainter painter(img);
    QPen pen(Qt::green,20);
    if(id==-1)
        pen.setColor(Qt::blue);
    //    QPen pen(QColor (0, 32, 0));
    pen.setCapStyle(Qt::RoundCap);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPoint(x, y);

    QPalette pal;
    pal.setBrush(this->backgroundRole(), QBrush(QPixmap::fromImage(*img)));
    this->setPalette(pal);
}



void NetMap::drawSpike(int x, int y,int id)
{
    QPainter painter(img);
    QPen pen(Qt::red,19);
    //    QPen pen(QColor (0, 32, 0));
    pen.setCapStyle(Qt::RoundCap);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.drawPoint(x, y);

    QPalette pal;
    pal.setBrush(this->backgroundRole(), QBrush(QPixmap::fromImage(*img)));
    this->setPalette(pal);
    this->repaint();


    if(id==1)
        pen.setColor(Qt::green);
    else if(id==-1)
        pen.setColor(Qt::blue);

    pen.setWidth(20);

    painter.setPen(pen);
    //    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPoint(x, y);

    pal.setBrush(this->backgroundRole(), QBrush(QPixmap::fromImage(*img)));
    this->setPalette(pal);
    this->repaint();
}
