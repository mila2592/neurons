#ifndef NETMAP_H
#define NETMAP_H

#include <QWidget>
#include <QPainter>


#include "neuronnet.h"
class NetMap : public QWidget
{
    Q_OBJECT
public:
    explicit NetMap(QWidget *parent = 0);



private:
    QImage *img;
signals:



public slots:
    void drawSpike(int x, int y,int id);
    void drawNewNeuron(int x, int y,int id);

};

#endif // NETMAP_H
