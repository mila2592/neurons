#ifndef CORE_H
#define CORE_H

#include "neuronmainwidget.h"
#include "neuronnet.h"
#include <QObject>

class Core : public QObject
{
Q_OBJECT
public:
    static Core &instance();
    void init_core();
private:
    explicit Core(QObject *obj = 0);
    Core(const Core&){}
    ~Core(){;}
    // Members
    NeuronNet *neuron_net;
private slots:
    void prepare_to_close();
};

#endif // CORE_H