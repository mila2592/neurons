#ifndef _NEURON_H_
#define _NEURON_H_
#include <iostream>
#include <cstdlib>
#include "connections.h"


struct Neuron
{
    //private:

    double a;
    double b;
    double c; // значение мембранного потенциала до которого он сбрасывается после спайка
    double d;

    double Vm;
    double Um;

    double Um_before;
    double Vm_before;

    double Iex;
    double Isyn;
    double Cm;
    double Vr;
    double Vt;
    double V0;
    double k;
    double U0;
    double Vpeak;

    int x;
    int y;

private:
    char id_;


public:
    Neuron()    //это конструктор
    {
        a=0.02f;
        b=0.5f;
        c=-40.0f;
        d=100.0f;

        Vm=-60.0f;
        Um=0.0f;

        Um_before=0;
        Vm_before=-60.0f;

        Iex=0;
        Isyn=0;
        Cm=50.0f;;
        Vr=-60.0f;;
        Vt=-45.0f;;
        V0=-60.0f;
        k=0.5f;;
        U0=0.0f;
        Vpeak=35.0f;

        x=rand() %500;
        y=rand() %500;
        id_='e';

    }

    Neuron(char id)    //это конструктор
    {
        switch(id){
        case 'e':
        {
            a=0.02f;
            b=0.5f;
            c=-40.0f;
            d=100.0f;

            Vm=-60.0f;
            Um=0.0f;

            Um_before=0;
            Vm_before=-60.0f;

            Iex=0;
            Isyn=0;
            Cm=50.0f;;
            Vr=-60.0f;;
            Vt=-45.0f;;
            V0=-60.0f;
            k=0.5f;;
            U0=0.0f;
            Vpeak=35.0f;

            x=rand() %500;
            y=rand() %500;
            id_=id;
        }; break;
        case 'i':{
            a=0.08f;
            b=0.35f;
            c=-40.0f;
            d=10.0f;

            Vm=-60.0f;
            Um=0.0f;

            Um_before=0;
            Vm_before=-60.0f;

            Iex=0;
            Isyn=0;
            Cm=50.0f;;
            Vr=-60.0f;;
            Vt=-45.0f;;
            V0=-60.0f;
            k=0.5f;;
            U0=0.0f;
            Vpeak=35.0f;

            x=rand() %500;
            y=rand() %500;
            id_=id;
        }; break;
        default:         {
            a=0.02f;
            b=0.5f;
            c=-40.0f;
            d=100.0f;

            Vm=-60.0f;
            Um=0.0f;

            Um_before=0;
            Vm_before=-60.0f;;

            Iex=0;
            Isyn=0;
            Cm=50.0f;;
            Vr=-60.0f;;
            Vt=-45.0f;;
            V0=-60.0f;
            k=0.5f;;
            U0=0.0f;
            Vpeak=35.0f;

            x=rand() %500;
            y=rand() %500;
            id_='e';
        }; break;
        }

    }


    void showPar(); //показать все параметры
    void show_id(); //показать возб. или торм. нейрон
    void setId_WithPar(char id); //сделать нейрон возбуждающим или тормозным
    void setRandCoord();


    double get_a(),get_b(),get_c(),get_d(),
    get_Vm(),get_Um(),get_Um_before(),get_Vm_before(),
    get_Iex(),get_Isyn(),get_Cm(),get_Vr(),
    get_Vt(),get_V0(),get_k(),get_U0(),
    get_Vpeak();
    int get_x(),get_y();
    char get_id();
    int get_id1();

    void set_a(), set_b(), set_c(), set_d(),
    set_Vm(), set_Um(), set_Um_before(), set_Vm_before(),
    set_Iex(), set_Isyn(), set_Cm(), set_Vr(),
    set_Vt(), set_V0(), set_k(), set_U0(),
    set_Vpeak(), set_x(), set_y(), set_id();


};

#endif // _NEURON_H_
