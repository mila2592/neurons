#ifndef NEURONNET_H
#define NEURONNET_H

#include <QObject>
#include <vector>
#include <memory>
#include <QApplication>
#include "neuron.h"

#include <iostream>
#include <fstream>

class NeuronNet : public QObject
{
    Q_OBJECT
public:
    explicit NeuronNet(QObject *parent = 0);
    void add_layer(int exciting_number, int inhibiting_number);
    void connect_layers(int lay1, int lay2,int type_of_connections=0);

    void show_conns_for_lay(int lay1, int lay2);
    void integrate_of_activity(std::ofstream& volt_file, std::ofstream& res_file);
    void integrate_of_activity1(std::ofstream& volt_file, std::ofstream& res_file);
    void tmp();
    int neuron_x_coord(int lay,int neur);
    int neuron_y_coord(int lay,int neur);

    int size()
    {
        return(this->neuron_layers.size());
    }

    int size_of_lay(int lay_num)
    {
        return(this->neuron_layers[lay_num].size());
    }

    void neuron_info(int lay_num,int neur_num)
    {
        this->neuron_layers[lay_num][neur_num].showPar();
    }

    int num_ex_in_lay(int lay_num)
    {
        return  ( this->num_neurons_in_layers[lay_num][0]);

    }
    int num_inh_in_lay(int lay_num)
    {
        return  ( this->num_neurons_in_layers[lay_num][1]);
    }


    float izhik_Vm_Euler(int lay, int neuron);
    float izhik_Um_Euler(int lay, int neuron);


private:
    std::vector<std::vector<Neuron> > neuron_layers; // All the network
    std::vector<std::vector<Connections> >  network_connections;

    std::vector<std::vector<int> > num_neurons_in_layers; // запоминает, сколько в каком слое возб. и торм. нейронов
    std::vector<std::vector<int> > num_connections_in_layers;//число связей в слоях

signals:

    void spikeSignal(int x, int y, int id);
    //        void newNeuronsSignal(int n,int x, int y, int id);
    void newNeuronSignal(int x, int y, int id);

public slots:
};

#endif // NEURONNET_H
