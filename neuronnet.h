#ifndef NEURONNET_H
#define NEURONNET_H

#include <QObject>
#include <vector>
#include <memory>
#include "neuron.h"

class NeuronNet : public QObject
{
    Q_OBJECT
public:
    explicit NeuronNet(QObject *parent = 0);
    void add_layer(int exciting_number, int inhibiting_number);
private:
    std::vector<std::vector<Neuron> > neuron_layers; // All the network
signals:

public slots:
};

#endif // NEURONNET_H