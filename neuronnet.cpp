#include "neuronnet.h"
#include <QDebug>

NeuronNet::NeuronNet(QObject *parent) : QObject(parent)
{
    ;
}
void NeuronNet::add_layer(int exciting_number, int inhibiting_number)
{
    if(exciting_number < 0)
    {
        qDebug() << "NeuronNet:: exciting_number less than zero";
        return;
    }
    if(inhibiting_number < 0)
    {
        qDebug() << "NeuronNet:: inhibiting_number less than zero";
        return;
    }
    neuron_layers.push_back(std::vector<Neuron>(exciting_number + inhibiting_number));
}
