#include "neuron.h"

void Neuron::showPar() //показать все параметры
{
    if(id_=='e')
        std::cout << "excitatory neuron" << std::endl;
    else if(id_=='i')
        std::cout << "inhibitory neuron" << std::endl;
    std::cout << "a = " << a <<", ";
    std::cout << "b = " << b<<", ";
    std::cout << "c = " << c <<", ";
    std::cout << "d = " << d<<", ";

    std::cout << "Vm = " << Vm <<", ";
    std::cout << "Um = " << Um<<", ";
    std::cout << "Vm_before = " << Vm_before <<", ";
    std::cout << "Vm_before = " << Vm_before<<", ";

    std::cout << "Cm = " << Cm <<", ";
    std::cout << "Vr = " << Vr<<", ";
    std::cout << "Vt = " << Vt <<", ";
    std::cout << "Vpeak = " << Vpeak <<", ";
    std::cout << "V0 = " << V0<<", ";
    std::cout << "U0 = " << U0<<", ";

    std::cout << "x = " << x <<", ";
    std::cout << "y = " << y << std::endl << std::endl;

}


void Neuron::show_id() //показать возб. или торм. нейрон
{
    if(id_=='e')
        std::cout << " excitatory neuron";
    else if(id_=='i')
        std::cout << " inhibitory neuron";
}
char Neuron::get_id() //показать возб. или торм. нейрон
{
    //    return id_;
    if(id_=='e')
        return 'e';
    else if(id_=='i')
        return 'i';
}

int Neuron::get_id1() //показать возб. или торм. нейрон
{
    //    return id_;
    if(id_=='e')
        return 1;
    else if(id_=='i')
        return -1;
}
void Neuron::setId_WithPar(char id) //сделать нейрон возбуждающим или тормозным
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
    }; break;
    }
}


void Neuron::setRandCoord() //сделать нейрон возбуждающим или тормозным
{
    x=rand() %500;
    y=rand() %500;
}
