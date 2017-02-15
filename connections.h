#ifndef CONNECTIONS_H
#define CONNECTIONS_H
#include <vector>
//#include "neuron.h"
struct Connections
{
    //    std::vector<int> inside_connections;
    std::vector<std::vector<int> >lay_to_lay_connections; // связи одного нейрона (нейроны на пресинапсе)
    std::vector<std::vector<float> >weights;

    std::vector<std::vector<float> >x_plast;//
    std::vector<std::vector<float> >y_plast;
    std::vector<std::vector<float> >u_plast;

    std::vector<std::vector<float> >x_plast_bef;//
    std::vector<std::vector<float> >y_plast_bef;
    std::vector<std::vector<float> >u_plast_bef;

    //    std::vector<int> conn_layers;//номер слоев
    void setInitialConditions();

};

#endif // CONNECTIONS_H
