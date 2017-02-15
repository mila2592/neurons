#include "neuronnet.h"
#include <cmath>
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
    std::vector<int> vec;

    vec.push_back(exciting_number);
    vec.push_back(inhibiting_number);
    vec.push_back(exciting_number+inhibiting_number);
    num_neurons_in_layers.push_back(vec);

    for(int i=exciting_number;i<exciting_number+inhibiting_number;i++)
        neuron_layers[neuron_layers.size()-1][i].setId_WithPar('i');

    //
    for(int i=0;i<exciting_number;i++)
    {
        neuron_layers[neuron_layers.size()-1][i].setRandCoord();
        emit newNeuronSignal(neuron_layers[neuron_layers.size()-1][i].x,neuron_layers[neuron_layers.size()-1][i].y,1);
    }
    for(int i=exciting_number;i<exciting_number+inhibiting_number;i++)
    {
        neuron_layers[neuron_layers.size()-1][i].setRandCoord();
        emit newNeuronSignal(neuron_layers[neuron_layers.size()-1][i].x,neuron_layers[neuron_layers.size()-1][i].y,-1);

    }


    ////////////////////////////////////////////////////////////////
    //а это для связей
    ////////////////////////////////////////////////////////////////
    std::vector<Connections> con;
    for(int i=0;i<exciting_number+inhibiting_number;i++)
    {
        Connections c;
        for(int i=0;i<neuron_layers.size();i++)
        {
            std::vector<int> n;
            std::vector<float> ff;
            c.lay_to_lay_connections.push_back(n);
            c.weights.push_back(ff);


            c.x_plast.push_back(ff);
            c.y_plast.push_back(ff);
            c.u_plast.push_back(ff);

            c.x_plast_bef.push_back(ff);
            c.y_plast_bef.push_back(ff);
            c.u_plast_bef.push_back(ff);
        }
        con.push_back(c);
    }

    network_connections.push_back(con);

    for(int i=0;i<neuron_layers.size()-1;i++)
        for(int j=0;j<neuron_layers[i].size();j++)
        {
            std::vector<int> n;
            std::vector<float> f;
            network_connections[i][j].lay_to_lay_connections.push_back(n);
            network_connections[i][j].weights.push_back(f);

            network_connections[i][j].x_plast.push_back(f);
            network_connections[i][j].y_plast.push_back(f);
            network_connections[i][j].u_plast.push_back(f);


            network_connections[i][j].x_plast_bef.push_back(f);
            network_connections[i][j].y_plast_bef.push_back(f);
            network_connections[i][j].u_plast_bef.push_back(f);
        }

    for(int i=neuron_layers.size()-1;i<neuron_layers.size();i++)
    {

        std::vector <int> vec;
        for(int i=0;i<neuron_layers.size();i++)
            vec.push_back(0);
        num_connections_in_layers.push_back(vec);
    }

    for(int i=0;i<neuron_layers.size()-1;i++)
    {
        num_connections_in_layers[i].push_back(0);
    }

    //        neuron_layers[0][0].con.lay_to_lay_connections[0][0]=1;

    for(int i=0;i<neuron_layers.size();i++)
        std::cout<<"num conns= "<<num_connections_in_layers[0][i]<<std::endl;


    std::cout<<"network_connections.size()= "<< network_connections.size()<<std::endl;
    for(int i=0;i<network_connections.size();i++)
        std::cout<<"network_connections[i].size()= "<< network_connections[i].size()<<std::endl;
    std::cout<<std::endl;
}

int NeuronNet::neuron_x_coord(int lay,int neur)
{
    return neuron_layers[lay][neur].x;
}
int NeuronNet::neuron_y_coord(int lay,int neur)
{
    return neuron_layers[lay][neur].y;
}

void NeuronNet::connect_layers(int lay1, int lay2, int type_of_connections)
{
    //*int type_of_connections - еще не реализовано
    float pee=0.03;
    float pei=0.02;
    float pii=0.0;
    float pie=0.031371;
    double minWee = 100.0f; // веса, размерность пкА
    double maxWee = 101.0f;
    double minWei = 80.0f; // веса, размерность пкА
    double maxWei = 100.0f;
    double minWii = 20.0f; // веса, размерность пкА
    double maxWii = 40.0f;
    double minWie = 50.0f; // веса, размерность пкА
    double maxWie = 70.0f;
    int Nex1= num_neurons_in_layers[lay1][0];
    int Ninh1=num_neurons_in_layers[lay1][1];
    int Nex2= num_neurons_in_layers[lay2][0];
    int Ninh2=num_neurons_in_layers[lay2][1];
    int Nneur1=num_neurons_in_layers[lay1][2];
    int Nneur2=num_neurons_in_layers[lay2][2];
    int Nex = Nex1+Nex2;
    int Ninh = Ninh1+Ninh2;
    std::cout<<"Nex= "<<Nex1<<std::endl;
    std::cout<<"Ninh= "<<Ninh1<<std::endl;

    int   num_con=int (Nex1*Nex2*pee);
    int con_idx=0;
    for (con_idx = 0; con_idx < num_con; con_idx++)
    {
        //neuron_connections.
        int pre =  rand() % Nex1;
        int post = rand() % Nex2;
        float w=(rand() % ((int)(maxWee - minWee)*10))/10.0f + minWee;

        network_connections[lay1][pre].lay_to_lay_connections[lay2].push_back(post);
        //        network_connections[lay1][pre].weights[lay2].push_back((rand() % ((int)(maxWee - minWee)*10))/10.0f + minWee);
        network_connections[lay1][pre].weights[lay2].push_back(w);

        network_connections[lay1][pre].x_plast[lay2].push_back(0.);
        network_connections[lay1][pre].y_plast[lay2].push_back(1.);
        network_connections[lay1][pre].u_plast[lay2].push_back(0.5);

        network_connections[lay1][pre].x_plast_bef[lay2].push_back(0.);
        network_connections[lay1][pre].y_plast_bef[lay2].push_back(1.);
        network_connections[lay1][pre].u_plast_bef[lay2].push_back(0.5);

//        std::cout<<"pre=  "<< pre<<std::endl;
//        std::cout<<"post=  "<< post<<std::endl;
//        std::cout<<"w=  "<< w<<std::endl;
//        std::cout<<std::endl;
    }
    //////////////////////////////
    num_con  += int(Nex1*Ninh2*pei);
    //    cout<<"Nneur*Nneur*pei "<< int(Nneur*Nneur*pei)<<endl;
    for (; con_idx < num_con; con_idx++)
    {
        // случайно выбираем постсипантические и пресинаптические нейроны
        int pre = rand() % Nex1;
        int post = (rand() % Ninh2)+Nex2;
        float w=(rand() % ((int)(maxWei - minWei)*10))/10.0f + minWei;
        network_connections[lay1][pre].lay_to_lay_connections[lay2].push_back(post);
        //  network_connections[lay1][pre].weights[lay2].push_back((rand() % ((int)(maxWei - minWei)*10))/10.0f + minWei);
        network_connections[lay1][pre].weights[lay2].push_back(w);

        network_connections[lay1][pre].x_plast[lay2].push_back(0.);
        network_connections[lay1][pre].y_plast[lay2].push_back(1.);
        network_connections[lay1][pre].u_plast[lay2].push_back(0.5);

        network_connections[lay1][pre].x_plast_bef[lay2].push_back(0.);
        network_connections[lay1][pre].y_plast_bef[lay2].push_back(1.);
        network_connections[lay1][pre].u_plast_bef[lay2].push_back(0.5);

//        std::cout<<"pre=  "<< pre<<std::endl;
//        std::cout<<"post=  "<< post<<std::endl;
//        std::cout<<std::endl;
    }
    num_con  += int(Ninh1*Ninh2*pii);
    for (; con_idx < num_con; con_idx++)
    {
        // случайно выбираем постсипантические и пресинаптические нейроны
        int pre = rand() % Ninh1+Nex1;
        int post = rand() % Ninh2+Nex2;
        float w=-((rand() % ((int)(maxWei - minWii)*10))/10.0f + minWii);
        network_connections[lay1][pre].lay_to_lay_connections[lay2].push_back(post);
        // network_connections[lay1][pre].weights[lay2].push_back((rand() % ((int)(maxWii - minWii)*10))/10.0f + minWii);
        network_connections[lay1][pre].weights[lay2].push_back(w);


        network_connections[lay1][pre].x_plast[lay2].push_back(0.);
        network_connections[lay1][pre].y_plast[lay2].push_back(1.);
        network_connections[lay1][pre].u_plast[lay2].push_back(0.5);

        network_connections[lay1][pre].x_plast_bef[lay2].push_back(0.);
        network_connections[lay1][pre].y_plast_bef[lay2].push_back(1.);
        network_connections[lay1][pre].u_plast_bef[lay2].push_back(0.5);

//        std::cout<<"pre=  "<< pre<<std::endl;
//        std::cout<<"post=  "<< post<<std::endl;
//        std::cout<<std::endl;
    }
    num_con  += int(Ninh1*Nex2*pie);
    for (; con_idx < num_con; con_idx++)
    {
        // случайно выбираем постсипантические и пресинаптические нейроны
        int pre = rand() % Ninh1+Nex1;
        int post = rand() % Nex2;
        float w=-((rand() % ((int)(maxWei - minWie)*10))/10.0f + minWie);
        network_connections[lay1][pre].lay_to_lay_connections[lay2].push_back(post);
        //        network_connections[lay1][pre].weights[lay2].push_back((rand() % ((int)(maxWie - minWie)*10))/10.0f + minWie);
        network_connections[lay1][pre].weights[lay2].push_back(w);

        network_connections[lay1][pre].x_plast[lay2].push_back(0.);
        network_connections[lay1][pre].y_plast[lay2].push_back(1.);
        network_connections[lay1][pre].u_plast[lay2].push_back(0.5);

        network_connections[lay1][pre].x_plast_bef[lay2].push_back(0.);
        network_connections[lay1][pre].y_plast_bef[lay2].push_back(1.);
        network_connections[lay1][pre].u_plast_bef[lay2].push_back(0.5);

//        std::cout<<"pre=  "<< pre<<std::endl;
//        std::cout<<"post=  "<< post<<std::endl;
//        std::cout<<std::endl;
    }
    num_connections_in_layers[lay1][lay2]=num_con;
    std::cout<<"lay "<<lay1<<" to "<<lay2<<" - "<<num_con<<" connections"<<std::endl;

}
void NeuronNet:: show_conns_for_lay(int lay1, int lay2)
{

    std::cout<<"layer "<<lay1<<" has "<<num_connections_in_layers[lay1][lay2]<<" connections"<<" ";
    std::cout<<"with layer "<<lay2<<": "<<std::endl;
    for(int i=0;i<neuron_layers[lay1].size();i++)
    {
        std::cout<<"pre - "<<i<<std::endl;
        std::cout<<"post - "<<std::endl;
        if(network_connections[lay1][i].lay_to_lay_connections[lay2].size()==0)
            std::cout<<"no connections"<<std::endl<<std::endl;
        else
        {
            for(int j=0;j<network_connections[lay1][i].lay_to_lay_connections[lay2].size();j++)
            {
                std::cout<<network_connections[lay1][i].lay_to_lay_connections[lay2][j]<<" w= ";
                std::cout<<network_connections[lay1][i].weights[lay2][j]<<" "<<std::endl;
            }
            std::cout<<std::endl;
        }
    }
}
double a_ = 0.02f;
double b_ = 0.5f;
double c_ = -40.0f; // значение мембранного потенциала до которого он сбрасывается после спайка
double d_ = 100.0f;
double k_ = 0.5f;
double Vr_ = -60.0f;
double Vt_ = -45.0f;
double Vpeak_ = 35.0f;  // максимальное значение мембранного потенциала, при котором происходит сброс до значения с
double V0_ = -60.0f; // начальное значение для мембранного потенциала
double U0_ = 0.0f;   // начальное значение для вспомогательной переменной
double Cm_ = 50.0f;
float step_=0.5f;

float h_=0.5,trec_e_=800,tpsc_e_=5.,tfac_e_=0.00001,Ue_=0.5;
float trec_i_=800,tpsc_i_=5.,tfac_i_=0.00001,Ui_=0.05;
int t_=0;
//float trec_e=800.,trec_i=100.,tfac_e=0.00001,tfac_i=0.00001,t1=3.,tpsc=5.;
//float tpsc_e=5.,tpsc_i=5.,Ue=0.5,Ui=0.05;

float NeuronNet::izhik_Vm_Euler(int lay, int neuron)
{
    return (k_*(neuron_layers[lay][neuron].Vm_before  - Vr_)*(neuron_layers[lay][neuron].Vm_before  - Vt_) - neuron_layers[lay][neuron].Um_before +  neuron_layers[lay][neuron].Iex + neuron_layers[lay][neuron].Isyn)/Cm_;
}
float NeuronNet::izhik_Um_Euler(int lay,int neuron)
{
    return neuron_layers[lay][neuron].a*(neuron_layers[lay][neuron].b*(neuron_layers[lay][neuron].Vm_before - Vr_) - neuron_layers[lay][neuron].Um_before);
}


void NeuronNet::integrate_of_activity(std::ofstream& volt_file, std::ofstream& res_file)
{//это - 1 шаг интегрирования!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // проходим по всем нейронам
    for(int lay=0;lay<neuron_layers.size();lay++)
        for (int neur = 0; neur < neuron_layers[lay].size(); neur++)
        {
            //            std::cout<<"lay= "<<lay<<", neur= "<<neur<<" "<<std::endl;
            //            neuron_layers[lay][neur].showPar();
            //        neuron_layers
            neuron_layers[lay][neur].Vm = neuron_layers[lay][neur].Vm_before + step_*izhik_Vm_Euler(lay,neur);
            neuron_layers[lay][neur].Um = neuron_layers[lay][neur].Um_before + step_*izhik_Um_Euler(lay,neur);

            //            std::cout<<"lay= "<<lay<<", neur= "<<neur<<" "<<std::endl;
            //            neuron_layers[lay][neur].showPar();

            neuron_layers[lay][neur].Isyn = 0.0f;
            if ( neuron_layers[lay][neur].Vm_before >Vpeak_)
            {

                neuron_layers[lay][neur].Vm =  neuron_layers[lay][neur].c;
                //                Vms[neur][t] = c;
                neuron_layers[lay][neur].Um =  neuron_layers[lay][neur].Um_before +  neuron_layers[lay][neur].d;

                emit spikeSignal( neuron_layers[lay][neur].x,  neuron_layers[lay][neur].y, neuron_layers[lay][neur].get_id1());

                if(lay==0)
                    res_file <<t_*h_<< "; " <<neur + 1 << "; " << std::endl;
                //                {
                //                    res_file <<t*h<< "; " <<neur + 1 << "; " << endl;// запись в файл
                //                    spikes++;
                //                }
                {
                    // ДОПИСАТЬ!!!!!!!!!!!!!!!!!!!!
                    //ф-я перерисовки нейрона со спайком!!!!!!!!!!!!!!!!!1
                }
            }
            neuron_layers[lay][neur].Vm_before =  neuron_layers[lay][neur].Vm;
            neuron_layers[lay][neur].Um_before =  neuron_layers[lay][neur].Um;
        }
    //теперь по связям......


    for (int lay_pre = 0; lay_pre<network_connections.size(); lay_pre++)
    {
        for(int pre=0;pre<network_connections[lay_pre].size();pre++)
        {
            int spike=0;
            if (neuron_layers[lay_pre][pre].Vm_before > Vpeak_)
                spike=1;

            if( neuron_layers[lay_pre][pre].get_id()=='e')
            {
                if(spike==0)
                    for(int lay_post=0;lay_post<network_connections[lay_pre][pre].lay_to_lay_connections.size();lay_post++)
                    {
                        for(int post=0;post<network_connections[lay_pre][pre].lay_to_lay_connections[lay_post].size();post++)
                        {
                            network_connections[lay_pre][pre].x_plast[lay_post][post] =
                                    1. - (1.-network_connections[lay_pre][pre].x_plast[lay_post][post])*exp(-h_/trec_e_);

                            network_connections[lay_pre][pre].y_plast[lay_post][post] =
                                    1. - (1.-network_connections[lay_pre][pre].y_plast[lay_post][post])*exp(-h_/tpsc_e_);

                            network_connections[lay_pre][pre].u_plast[lay_post][post] =
                                    1. - (1.-network_connections[lay_pre][pre].u_plast[lay_post][post])*exp(-h_/tfac_e_);

                            neuron_layers[lay_post][network_connections[lay_pre][pre].lay_to_lay_connections[lay_post][post]].Isyn+=network_connections[lay_pre][pre].y_plast[lay_post][post];
                        }


                    }

                ///////////////////////////////////////////////////////////////
                /////////////////////////////////////////////////////////////////
                else if(spike==1)
                    for(int lay_post=0;lay_post<network_connections[lay_pre][pre].lay_to_lay_connections.size();lay_post++)
                    {
                        for(int post=0;post<network_connections[lay_pre][pre].lay_to_lay_connections[lay_post].size();post++)
                        {
                            network_connections[lay_pre][pre].x_plast[lay_post][post] =
                                    1. - (1.-network_connections[lay_pre][pre].x_plast[lay_post][post])*exp(-h_/trec_e_);

                            network_connections[lay_pre][pre].y_plast[lay_post][post] =
                                    1. - (1.-network_connections[lay_pre][pre].y_plast[lay_post][post])*exp(-h_/tpsc_e_);

                            network_connections[lay_pre][pre].u_plast[lay_post][post] =
                                    1. - (1.-network_connections[lay_pre][pre].u_plast[lay_post][post])*exp(-h_/tfac_e_);


                            ///////////////////////////
                            //добавляется при спайке на пресинаптическом нейроне
                            ///////////////////////////

                            network_connections[lay_pre][pre].u_plast[lay_post][post] =
                                    network_connections[lay_pre][pre].u_plast[lay_post][post] +
                                    Ui_*(1-network_connections[lay_pre][pre].u_plast[lay_post][post]) ;


                            network_connections[lay_pre][pre].y_plast[lay_post][post] =
                                    network_connections[lay_pre][pre].y_plast[lay_post][post]+
                                    network_connections[lay_pre][pre].weights[lay_post][post]*
                                    network_connections[lay_pre][pre].u_plast[lay_post][post]*network_connections[lay_pre][pre].x_plast[lay_post][post];



                            network_connections[lay_pre][pre].x_plast[lay_post][post] =
                                    network_connections[lay_pre][pre].x_plast[lay_post][post]-
                                    network_connections[lay_pre][pre].u_plast[lay_post][post]*network_connections[lay_pre][pre].x_plast[lay_post][post];

                            neuron_layers[lay_post][network_connections[lay_pre][pre].lay_to_lay_connections[lay_post][post]].Isyn+=network_connections[lay_pre][pre].y_plast[lay_post][post];

                        }


                    }


            }

            else if( neuron_layers[lay_pre][pre].get_id()=='i')
            {
                if(spike==0)
                {
                    for(int lay_post=0;lay_post<network_connections[lay_pre][pre].lay_to_lay_connections.size();lay_post++)
                    {
                        for(int post=0;post<network_connections[lay_pre][pre].lay_to_lay_connections[lay_post].size();post++)
                        {
                            network_connections[lay_pre][pre].x_plast[lay_post][post] =
                                    1. - (1.-network_connections[lay_pre][pre].x_plast[lay_post][post])*exp(-h_/trec_i_);

                            network_connections[lay_pre][pre].y_plast[lay_post][post] =
                                    1. - (1.-network_connections[lay_pre][pre].y_plast[lay_post][post])*exp(-h_/tpsc_i_);

                            network_connections[lay_pre][pre].u_plast[lay_post][post] =
                                    1. - (1.-network_connections[lay_pre][pre].u_plast[lay_post][post])*exp(-h_/tfac_i_);

                            neuron_layers[lay_post][network_connections[lay_pre][pre].lay_to_lay_connections[lay_post][post]].Isyn+=network_connections[lay_pre][pre].y_plast[lay_post][post];

                        }
                    }
                }


                else if(spike==1)
                {
                    for(int lay_post=0;lay_post<network_connections[lay_pre][pre].lay_to_lay_connections.size();lay_post++)
                    {
                        for(int post=0;post<network_connections[lay_pre][pre].lay_to_lay_connections[lay_post].size();post++)
                        {
                            network_connections[lay_pre][pre].x_plast[lay_post][post] =
                                    1. - (1.-network_connections[lay_pre][pre].x_plast[lay_post][post])*exp(-h_/trec_i_);

                            network_connections[lay_pre][pre].y_plast[lay_post][post] =
                                    1. - (1.-network_connections[lay_pre][pre].y_plast[lay_post][post])*exp(-h_/tpsc_i_);

                            network_connections[lay_pre][pre].u_plast[lay_post][post] =
                                    1. - (1.-network_connections[lay_pre][pre].u_plast[lay_post][post])*exp(-h_/tfac_i_);


                            ///////////////////////////////////////////////////////////////////////
                            ///////////////////////////
                            //добавляется при спайке на пресинаптическом нейроне
                            ///////////////////////////

                            network_connections[lay_pre][pre].u_plast[lay_post][post] =
                                    network_connections[lay_pre][pre].u_plast[lay_post][post] +
                                    Ui_*(1-network_connections[lay_pre][pre].u_plast[lay_post][post]) ;


                            network_connections[lay_pre][pre].y_plast[lay_post][post] =
                                    network_connections[lay_pre][pre].y_plast[lay_post][post]+
                                    network_connections[lay_pre][pre].weights[lay_post][post]*
                                    network_connections[lay_pre][pre].u_plast[lay_post][post]*network_connections[lay_pre][pre].x_plast[lay_post][post];



                            network_connections[lay_pre][pre].x_plast[lay_post][post] =
                                    network_connections[lay_pre][pre].x_plast[lay_post][post]-
                                    network_connections[lay_pre][pre].u_plast[lay_post][post]*network_connections[lay_pre][pre].x_plast[lay_post][post];

                            neuron_layers[lay_post][network_connections[lay_pre][pre].lay_to_lay_connections[lay_post][post]].Isyn+=network_connections[lay_pre][pre].y_plast[lay_post][post];

                        }
                    }
                }
            }
        }


    }

    volt_file <<t_*h_<< " " <<   neuron_layers[0][1].Isyn<< std::endl;
    t_++;//1 шаг интегрирования
}

////////////////////////////////////////////////
/////////////////////////////////////////////////


double psc_excxpire_time1 = 4.0f;
float expire_coeff1 = exp(-h_/psc_excxpire_time1);

//это интегрирование без пластичности
void NeuronNet::integrate_of_activity1(std::ofstream& volt_file, std::ofstream& res_file)
{//это - 1 шаг интегрирования!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // проходим по всем нейронам
    for(int lay=0;lay<neuron_layers.size();lay++)
        for (int neur = 0; neur < neuron_layers[lay].size(); neur++)
        {
            //            std::cout<<"lay= "<<lay<<", neur= "<<neur<<" "<<std::endl;
            //            neuron_layers[lay][neur].showPar();
            //        neuron_layers
            neuron_layers[lay][neur].Vm = neuron_layers[lay][neur].Vm_before + step_*izhik_Vm_Euler(lay,neur);
            neuron_layers[lay][neur].Um = neuron_layers[lay][neur].Um_before + step_*izhik_Um_Euler(lay,neur);

            //            std::cout<<"lay= "<<lay<<", neur= "<<neur<<" "<<std::endl;
            //            neuron_layers[lay][neur].showPar();

            neuron_layers[lay][neur].Isyn = 0.0f;
            if ( neuron_layers[lay][neur].Vm_before >Vpeak_)
            {

                neuron_layers[lay][neur].Vm =  neuron_layers[lay][neur].c;
                neuron_layers[lay][neur].Um =  neuron_layers[lay][neur].Um_before +  neuron_layers[lay][neur].d;

                if(lay==0)
                    res_file <<t_*h_<< "; " <<neur + 1 << "; " << std::endl;

                {
                    // ДОПИСАТЬ!!!!!!!!!!!!!!!!!!!!
                    //ф-я перерисовки нейрона со спайком!!!!!!!!!!!!!!!!!1
                }
            }
            //            neuron_layers[lay][neur].Vm_before =  neuron_layers[lay][neur].Vm;
            //            neuron_layers[lay][neur].Um_before =  neuron_layers[lay][neur].Um;
        }
    //теперь по связям......


    for (int lay_pre = 0; lay_pre<network_connections.size(); lay_pre++)
    {
        for(int pre=0;pre<network_connections[lay_pre].size();pre++)
        {
            int spike=0;
            if (neuron_layers[lay_pre][pre].Vm_before > Vpeak_)
                spike=1;

            if(spike==0)
                for(int lay_post=0;lay_post<network_connections[lay_pre][pre].lay_to_lay_connections.size();lay_post++)
                {
                    for(int post=0;post<network_connections[lay_pre][pre].lay_to_lay_connections[lay_post].size();post++)
                    {

                        network_connections[lay_pre][pre].y_plast[lay_post][post] =
                                network_connections[lay_pre][pre].y_plast[lay_post][post]*expire_coeff1;

                        neuron_layers[lay_post][network_connections[lay_pre][pre].lay_to_lay_connections[lay_post][post]].Isyn+=network_connections[lay_pre][pre].y_plast[lay_post][post]*network_connections[lay_pre][pre].weights[lay_post][post];
                    }


                }

            ///////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////
            else if(spike==1)
                for(int lay_post=0;lay_post<network_connections[lay_pre][pre].lay_to_lay_connections.size();lay_post++)
                {
                    for(int post=0;post<network_connections[lay_pre][pre].lay_to_lay_connections[lay_post].size();post++)
                    {
                        network_connections[lay_pre][pre].y_plast[lay_post][post] =
                                network_connections[lay_pre][pre].y_plast[lay_post][post]*expire_coeff1+1;

                        neuron_layers[lay_post][network_connections[lay_pre][pre].lay_to_lay_connections[lay_post][post]].Isyn+=network_connections[lay_pre][pre].y_plast[lay_post][post]*network_connections[lay_pre][pre].weights[lay_post][post];
                    }


                }

        }


    }

    for(int lay=0;lay<neuron_layers.size();lay++)
        for (int neur = 0; neur < neuron_layers[lay].size(); neur++)
        {

            neuron_layers[lay][neur].Vm_before =  neuron_layers[lay][neur].Vm;
            neuron_layers[lay][neur].Um_before =  neuron_layers[lay][neur].Um;
        }

    volt_file <<t_*h_<< " " <<   neuron_layers[0][1].Isyn<< std::endl;
    t_++;//1 шаг интегрирования
}

void NeuronNet::tmp()
{

    char str[6] = "";

    std::ofstream  res_file ;
    std::ofstream  volt_file ;

    int Tsim=2000;

    res_file.open("rastr0.csv");
    volt_file.open("voltages0.txt");


    for(int lay=0;lay<neuron_layers.size();lay++)
        for(int neur=0;neur<neuron_layers[lay].size();neur++)
            neuron_layers[lay][neur].Iex=50;


    for (int t = 1; t < Tsim; t++)
    {
        integrate_of_activity(volt_file,res_file);
        QApplication::processEvents();
    }
    res_file.close();
    volt_file.close();
    std::cout<<"end of integration"<<std::endl;
}


