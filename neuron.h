#ifndef _NEURON_H_
#define _NEURON_H_

struct Neuron
{
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
};

#endif // _NEURON_H_