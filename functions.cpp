#include "mainwindow.h"
//#include "mainwindow.cpp"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include "QTime"


using namespace std;
int sc=500;
int t,tc=0,tc1=400;
float con_probability = 0.1;
double h     = 0.5; 	  // временной шаг интегрирования
int   Tsim  = 1000/h; // время симуляции в дискретных отсчетах
int Tmax=Tsim;
//const int   Nex  = 200; 	  // Количество возбуждающих (excitatory) нейронов
//const int   Ninh  = 50;  	  // Количество тормозных (inhibitory) нейронов

const int   Nex  = 100; 	  // Количество возбуждающих (excitatory) нейронов
const int   Ninh  = 25;  	  // Количество тормозных (inhibitory) нейронов
const int   Nneur = Nex + Ninh;
//int   Ncon  = Nneur*Nneur*0.1f;
int   Ncon;// Количество сязей,
// 0.1 это вероятность связи между 2-мя случайными нейронами


int   num_con;
int stop_id=0;
double psc_excxpire_time = 4.0f; // характерное вермя спадания постсинаптического тока, мс

double minWee = 1300.0f; // веса, размерность пкА
double maxWee = 1301.0f;


double minWei = 80.0f; // веса, размерность пкА
double maxWei = 100.0f;

double minWii = 20.0f; // веса, размерность пкА
double maxWii = 40.0f;


double minWie = 50.0f; // веса, размерность пкА
double maxWie = 70.0f;
// Параметры нейрона
double Iex_max = 0.0f; // максимальный приложенный к нейрону ток 50 пкА
double Iex_min = 0.0f;

double a = 0.02f;
double b = 0.5f;
double c = -40.0f; // значение мембранного потенциала до которого он сбрасывается после спайка
double d = 100.0f;
double k = 0.5f;
double Vr = -60.0f;
double Vt = -45.0f;
double Vpeak = 35.0f;  // максимальное значение мембранного потенциала, при котором происходит сброс до значения с
double V0 = -60.0f; // начальное значение для мембранного потенциала
double U0 = 0.0f;   // начальное значение для вспомогательной переменной
double Cm = 50.0f;  // электрическая ёмкость нейрона, размерность пкФ

int spike_num = 0;

double kk=2;

double ae = 0.05f;
double be = 0.35f;
double ce = -60.0f; // значение мембранного потенциала до которого он сбрасывается после спайка
double de = 10.f;


double ai = 0.08f;
double bi = 0.35f;
double ci = -60.0f; // значение мембранного потенциала до которого он сбрасывается после спайка
double di = 10.0f;


////берсты!!!!!!!!
//float a		  = 0.031f;
//float b		  = 0.5f;
//float c		  = -28.0f; // значение мембранного потенциала до которого он сбрасываеться после спайка
//float d 	  = 90.0f;



//double ae = 0.031f;
//double be = 0.5f;
//double ce = -28.0f; // значение мембранного потенциала до которого он сбрасывается после спайка
//double de =  90.0f;


//double ai = 0.031f;
//double bi = 0.5f;
//double ci = -28.0f; // значение мембранного потенциала до которого он сбрасывается после спайка
//double di = 90.0f;

int spikes=0;

float p12ii = 0.;
float p21ii = 0.0;

float p1ee = 0.04009;
float p1ei = 0.04346;
float p12ie = 0.01346;

float p2ee = 0.04009;
float p2ei = 0.04346;
float p21ie = 0.05346;

//float p12ii = 0.01689;
//float p21ii = 0.01689;



int Nex1=Nex/2,Nex2=Nex/2,Ninh1=Ninh/2,Ninh2=Ninh/2;
int Nneur1=Nex1/2+Ninh1/2;
int Nneur2=Nex2/2+Ninh2/2;

//float pee=0.3;
//float pei=0.2;
//float pii=0.0;
//float pie=0.031371;

float pee=0.03;
float pei=0.02;
float pii=0.0;
float pie=0.031371;

float trec_e=800.,trec_i=100.,tfac_e=0.00001,tfac_i=0.00001,t1=3.,tpsc=5.;
float tpsc_e=5.,tpsc_i=5.,Ue=0.5,Ui=0.05;


float ErevAMPA=0.;
float ErevGABA=-75.;

int massNeur[1000];
ofstream  res_file ;
ofstream  volt_file ;

//void init_poisson(unsigned int* seeds, float* rates, float* weights, float psn_tau)
void init_poisson(float l,int t)
{



    //    int m=1/l;
    //    int sigma=1/l;
    int k=0;
    float X1,X=100.,tmp=0;
    //    X1=-(1/l)*log(rand());
    while(1)
    {

        X1=-(1./l)*log(double(rand()) / RAND_MAX);
        k++;
        tmp+=X1;
        cout<<tmp<<", ";
        if(tmp>X)
            break;

    }

    cout<<endl<<"k= "<<k<<endl;
}


void init_poisson2(float f,float &t)// f - частота, Hz
{
    float l=f*h/1000;
    int k=0;
    float X1,X=100.,tmp=0;
    //    X1=-(1/l)*log(rand());
    //    while(1)
    //    {
    tmp=t;
    X1=-(1./l)*log(double(rand()) / RAND_MAX);
    k++;
    tmp+=X1+1;
    t=tmp;
    //        cout<<tmp<<", ";
    //        if(tmp>X)
    //            break;

    //    }

    //    cout<<endl<<"k= "<<k<<endl;
}



void RandEvent(const float p,float &xi)
{
    xi=(double)(rand())/RAND_MAX;
    //    cout<<"xi= "<<xi<<endl;
    if(xi>p)
        xi=0;
    else
        xi=1;
    //    cout<<"xi= "<<xi<<endl;
}


void printTime(int ms)
{
    int h,min,sec,msec;
    h=ms/3600000;
    ms-=h*3600000;
    min=ms/60000;
    ms-=min*60000;
    sec=ms/1000;
    ms-=sec*1000;
    msec=ms;
    if(h!=0)
        cout<<h<<" ч "<<min<<" мин "<<sec<<" c "<<ms<<" мс"<<endl;
    else  if(min!=0)
        cout<<min<<" мин "<<sec<<" c "<<ms<<" мс"<<endl;
    else
        cout<<sec<<" c "<<ms<<" мс"<<endl;
}

void neur::createLay(int Nex,int Ninh)
{
    int Nneur=Nex+Ninh;
    lay = new neuron[Nex+Ninh];

    //    for(int i=0;i<Nneur;i++)
    //    {
    //        lay[i].a=a;
    //        lay[i].b=b;
    //        lay[i].c=c;
    //        lay[i].d=d;
    //        lay[i].Cm=Cm;
    //        lay[i].k=k;
    //        lay[i].Vr=Vr;
    //        lay[i].Vt=Vt;
    //        lay[i].Vpeak=Vpeak;
    //    }

    for(int i=0;i<Nex;i++)
    {
        lay[i].a=ae;
        lay[i].b=be;
        lay[i].c=ce;
        lay[i].d=de;
        lay[i].Cm=Cm;
        lay[i].k=k;
        lay[i].Vr=Vr;
        lay[i].Vt=Vt;
        lay[i].Vpeak=Vpeak;
        lay[i].x =  rand() %sc;
        lay[i].y =  rand() %sc;
        //        cout<<"x= "<<lay[i].x<<" y= "<<lay[i].y<<endl;
    }
    for(int i=Nex;i<Nneur;i++)
    {
        lay[i].a=ai;
        lay[i].b=bi;
        lay[i].c=ci;
        lay[i].d=di;
        lay[i].Cm=Cm;
        lay[i].k=k;
        lay[i].Vr=Vr;
        lay[i].Vt=Vt;
        lay[i].Vpeak=Vpeak;
        lay[i].x =  rand() %sc;
        lay[i].y =  rand() %sc;
        //         cout<<"x= "<<lay[i].x<<" y= "<<lay[i].y<<endl;
    }


    //    QTime midnight(0,0,0);
    //    qsrand(midnight.secsTo(QTime::currentTime()));

    //    cout<< qrand() % 10<<endl;


    //    cout<<ae/2. + double(rand()) / RAND_MAX * ae/2.<<endl;
    //        cout<<ae/2.<<endl;



    /*
    for(int i=0;i<Nex;i++)
    {
        lay[i].a=ae + double(rand()) / RAND_MAX * ae/kk;
        lay[i].b=be + pow(-1,rand()%10)*double(rand()) / RAND_MAX * be/kk;
        lay[i].c=ce+double(rand()%10)*0.1+double(rand()%10);
        //                         cout<<lay[i].c<<endl;
        //            lay[i].c=ce/2. + double(rand()) / RAND_MAX * ce/2.;
        lay[i].d=de/kk + double(rand()) / RAND_MAX * de/kk;
        lay[i].Cm=Cm;
        lay[i].k=k;
        lay[i].Vr=Vr;
        lay[i].Vt=Vt;
        lay[i].Vpeak=Vpeak;

        //                               cout<<lay[i].b<<endl;
    }
    for(int i=Nex;i<Nneur;i++)
    {
        lay[i].a=ai + double(rand()) / RAND_MAX * ai/kk;
        lay[i].b=bi/kk + double(rand()) / RAND_MAX * bi/kk;
        lay[i].c=ci+double(rand()%10)*0.1+double(rand()%10);
        //        lay[i].c=ci/kk + double(rand()) / RAND_MAX * ci/kk;
        lay[i].d=di/kk + double(rand()) / RAND_MAX * di/kk;
        lay[i].Cm=Cm;
        lay[i].k=k;
        lay[i].Vr=Vr;
        lay[i].Vt=Vt;
        lay[i].Vpeak=Vpeak;

        //        cout<<lay[i].b<<endl;
    }
     */
}

//void neuron::init_connections()
//{
//    for (int con_idx = 0; con_idx < Ncon; )
//    {
//        // случайно выбираем постсипантические и пресинаптические нейроны
//        int pre = rand() % Nneur;
//        int post = rand() % Nneur;
//        pre_conns[con_idx] = pre;
//        post_conns[con_idx] = post;
//        weights[con_idx] = (rand() % ((int)(maxWeight - minWeight)*10))/10.0f + minWeight;
//        if (pre >= Nex)
//        {
//            // если пресинаптический нейрон тормозный то вес связи идет со знаком минус
//            weights[con_idx] = -weights[con_idx];
//        }
//        y[con_idx][0] = 0.0f;
//        con_idx++;
//    }
//}

void neur::resize_mass_conns(int new_size)
{
    int pre[Ncon],post[Ncon];
    for(int i=0;i<Ncon;i++)
    {
        pre[i]=pre_conns[i];
        post[i]=post_conns[i];
    }

    delete []pre_conns;
    delete []post_conns;


    pre_conns=new int[new_size];
    post_conns=new int[new_size];

    for(int i=0;i<Ncon;i++)
    {
        pre_conns[i]=pre[i];
        post_conns[i]=post[i];
    }
    Ncon=new_size;
    cout<<"Ncon= "<<Ncon<<endl;
}

void neur::init_conns_gauss()
{
    float p=0,xi=0,s=0.018,mu=400,x=0;
    int k=0;
    //    vector <int> pre[Ncon],post[Ncon];
    int pre[Ncon],post[Ncon];
    for(int i=0;i<Nneur;i++)
        for(int j=0;j<Nneur;j++)
        {
            pre_conns[k]=i;
            x=sqrt(pow((lay[i].x-lay[j].x),2)+pow((lay[i].y-lay[j].y),2));
            //            cout<<"pre lay["<<i<<"].x= "<<lay[i].x<<endl;
            //            cout<<"post lay["<<j<<"].x= "<<lay[j].x<<endl;

            //            cout<<"pre lay["<<i<<"].y= "<<lay[i].y<<endl;
            //            cout<<"post lay["<<j<<"].y= "<<lay[j].y<<endl;

            //            p=1./(s*sqrt(2.*M_PI))*exp(pow(x-mu,2)/(-2.*s*s));
            //           p=1./(s*sqrt(2.*M_PI))*exp(pow(x-mu,2)/(2*s*s));
            //            p=(1-exp(-s*x));
            p=(exp(-s*x));
            //            cout<<"x= "<<x<<endl;
            //            cout<<"p= "<<p<<endl;
            RandEvent(p,xi);
            //            cout<<"xi= "<<xi<<endl;
            if(xi==1)
            {
                post_conns[k]=j;
                k++;
                if(k==Ncon)
                    resize_mass_conns(k+10);
            }
        }
    num_con=k;
    Ncon=k;
    cout<<"k= "<<k<<endl;
    cout<<"Ncon= "<<Ncon<<endl;
    //        for(int i=0;i<k;i++)
    //        {
    //            cout<<"pre= "<<pre_conns[i]<<" ";
    //            cout<<"post= "<<post_conns[i]<<endl;
    //        }

}


void neur::init_connections0()
{
    //    float pee=0.1009;
    //    cout<<endl<<endl;
    //    cout<<"pee "<< pee<<endl;
    //    cout<<"pei "<< pei<<endl;
    //    cout<<"pii "<< pii<<endl;
    //    cout<<"pie "<< pie<<endl;


    num_con  = int (Nneur*Nneur*pee);
    //    cout<<"Nneur*Nneur*pee "<< int (Nneur*Nneur*pee)<<endl;


    int con_idx=0;
    for (con_idx = 0; con_idx < num_con; con_idx++)
    {

        int pre =  rand() % Nex;
        int post = rand() % Nex;
        while(sqrt(pow(lay[post].x-lay[pre].x,2)+pow(lay[post].y-lay[pre].y,2))>100)
            post = rand() % Nex;

        n_con[post]++;
        out_con[pre]++;
        pre_conns[con_idx] = pre;
        post_conns[con_idx] = post;
        weights[con_idx] = (rand() % ((int)(maxWee - minWee)*10))/10.0f + minWee;
        //   weights[con_idx] = (rand() % ((int)(maxWeight - minWeight)*10))/10.0f + minWeight;

        //        y[con_idx][0] = 0.0f;
        Erev[con_idx]=ErevAMPA;
    }


    //////////////////////////////
    //    float pei=0.1346;
    num_con  += int(Nneur*Nneur*pei);
    //    cout<<"Nneur*Nneur*pei "<< int(Nneur*Nneur*pei)<<endl;

    for (; con_idx < num_con; con_idx++)
    {
        // случайно выбираем постсипантические и пресинаптические нейроны
        int pre = rand() % Nex;
        int post = (rand() % Ninh)+Nex;

        while(sqrt(pow(lay[post].x-lay[pre].x,2)+pow(lay[post].y-lay[pre].y,2))>100)
        {
            pre = rand() % Nex;
            post = (rand() % Ninh)+Nex;
        }

        n_con[post]++;
        out_con[pre]++;
        pre_conns[con_idx] = pre;
        post_conns[con_idx] = post;

        weights[con_idx] = (rand() % ((int)(maxWei - minWei)*10))/10.0f + minWei;
        //        weights[con_idx] = (rand() % ((int)(maxWeight - minWeight)*10))/10.0f + minWeight;

        //        y[con_idx][0] = 0.0f;
        //        Erev[con_idx]=ErevGABA;
        Erev[con_idx]=ErevAMPA;
    }


    //    float pii=0.1689;
    num_con  += int(Nneur*Nneur*pii);
    //    cout<<"Nneur*Nneur*pei "<< int(Nneur*Nneur*pii)<<endl;

    for (; con_idx < num_con; con_idx++)
    {
        // случайно выбираем постсипантические и пресинаптические нейроны
        int pre = rand() % Ninh+Nex;
        int post = rand() % Ninh+Nex;
        while(sqrt(pow(lay[post].x-lay[pre].x,2)+pow(lay[post].y-lay[pre].y,2))>100)
        {
            pre = rand() % Ninh+Nex;
            post = (rand() % Ninh)+Nex;
        }

        n_con[post]++;
        out_con[pre]++;
        pre_conns[con_idx] = pre;
        post_conns[con_idx] = post;

        weights[con_idx] = -((rand() % ((int)(maxWii - minWii)*10))/10.0f + minWii);

        //  weights[con_idx] = -((rand() % ((int)(maxWeight - minWeight)*10))/10.0f + minWeight);

        //        y[con_idx][0] = 0.0f;
        Erev[con_idx]=ErevGABA;

    }


    //    float pie=0.1371;
    num_con  += int(Nneur*Nneur*pie);

    //    cout<<"Nneur*Nneur*pie "<< int(Nneur*Nneur*pie)<<endl;
    //            cout<<"Nneur*Nneur*(pee+pei+pii+pie) "<< Nneur*Nneur*(pee+pei+pii+pie)<<endl;

    for (; con_idx < num_con; con_idx++)
    {
        // случайно выбираем постсипантические и пресинаптические нейроны
        int pre = rand() % Ninh+Nex;
        int post = rand() % Nex;
        while(sqrt(pow(lay[post].x-lay[pre].x,2)+pow(lay[post].y-lay[pre].y,2))>100)
        {
            pre = rand() % Ninh+Nex;
            post = rand() % Nex;
        }

        n_con[post]++;
        out_con[pre]++;
        pre_conns[con_idx] = pre;
        post_conns[con_idx] = post;

        weights[con_idx] = -((rand() % ((int)(maxWie - minWie)*10))/10.0f + minWie);
        //  weights[con_idx] = -((rand() % ((int)(maxWeight - minWeight)*10))/10.0f + minWeight);

        //        y[con_idx][0] = 0.0f;
        //        Erev[con_idx]=ErevAMPA;
        Erev[con_idx]=ErevGABA;
    }

    cout<<"Nneur= "<<Nneur<<endl;

    cout<<"num_con= "<<num_con<<endl;
    Ncon=num_con;
}

void neur::init_connections1()
{
    //    float pee=0.1009;
    //    cout<<endl<<endl;
    //    cout<<"pee "<< pee<<endl;
    //    cout<<"pei "<< pei<<endl;
    //    cout<<"pii "<< pii<<endl;
    //    cout<<"pie "<< pie<<endl;


    num_con  = int (Nneur*Nneur*pee);
    //    cout<<"Nneur*Nneur*pee "<< int (Nneur*Nneur*pee)<<endl;


    int con_idx=0;
    for (con_idx = 0; con_idx < num_con; con_idx++)
    {

        int pre =  rand() % Nex;
        int post = rand() % Nex;

        n_con[post]++;
        pre_conns[con_idx] = pre;
        post_conns[con_idx] = post;
        weights[con_idx] = (rand() % ((int)(maxWee - minWee)*10))/10.0f + minWee;
        //   weights[con_idx] = (rand() % ((int)(maxWeight - minWeight)*10))/10.0f + minWeight;

        //        y[con_idx][0] = 0.0f;
        Erev[con_idx]=ErevAMPA;
    }


    //////////////////////////////
    //    float pei=0.1346;
    num_con  += int(Nneur*Nneur*pei);
    //    cout<<"Nneur*Nneur*pei "<< int(Nneur*Nneur*pei)<<endl;

    for (; con_idx < num_con; con_idx++)
    {
        // случайно выбираем постсипантические и пресинаптические нейроны
        int pre = rand() % Nex;
        int post = (rand() % Ninh)+Nex;

        n_con[post]++;
        pre_conns[con_idx] = pre;
        post_conns[con_idx] = post;

        weights[con_idx] = (rand() % ((int)(maxWei - minWei)*10))/10.0f + minWei;
        //        weights[con_idx] = (rand() % ((int)(maxWeight - minWeight)*10))/10.0f + minWeight;

        //        y[con_idx][0] = 0.0f;
        //        Erev[con_idx]=ErevGABA;
        Erev[con_idx]=ErevAMPA;
    }


    //    float pii=0.1689;
    num_con  += int(Nneur*Nneur*pii);
    //    cout<<"Nneur*Nneur*pei "<< int(Nneur*Nneur*pii)<<endl;

    for (; con_idx < num_con; con_idx++)
    {
        // случайно выбираем постсипантические и пресинаптические нейроны
        int pre = rand() % Ninh+Nex;
        int post = rand() % Ninh+Nex;

        n_con[post]++;
        pre_conns[con_idx] = pre;
        post_conns[con_idx] = post;

        weights[con_idx] = -((rand() % ((int)(maxWii - minWii)*10))/10.0f + minWii);

        //  weights[con_idx] = -((rand() % ((int)(maxWeight - minWeight)*10))/10.0f + minWeight);

        //        y[con_idx][0] = 0.0f;
        Erev[con_idx]=ErevGABA;

    }


    //    float pie=0.1371;
    num_con  += int(Nneur*Nneur*pie);

    //    cout<<"Nneur*Nneur*pie "<< int(Nneur*Nneur*pie)<<endl;
    //            cout<<"Nneur*Nneur*(pee+pei+pii+pie) "<< Nneur*Nneur*(pee+pei+pii+pie)<<endl;

    for (; con_idx < num_con; con_idx++)
    {
        // случайно выбираем постсипантические и пресинаптические нейроны
        int pre = rand() % Ninh+Nex;
        int post = rand() % Nex;

        n_con[post]++;
        pre_conns[con_idx] = pre;
        post_conns[con_idx] = post;

        weights[con_idx] = -((rand() % ((int)(maxWie - minWie)*10))/10.0f + minWie);
        //  weights[con_idx] = -((rand() % ((int)(maxWeight - minWeight)*10))/10.0f + minWeight);

        //        y[con_idx][0] = 0.0f;
        //        Erev[con_idx]=ErevAMPA;
        Erev[con_idx]=ErevGABA;
    }

    cout<<"Nneur= "<<Nneur<<endl;

    cout<<"num_con= "<<num_con<<endl;
    Ncon=num_con;
}


void neur::init_connections2()
{
    //    float pee=0.1009;
    //    cout<<endl<<endl;
    //    cout<<"pee "<< pee<<endl;
    //    cout<<"pei "<< pei<<endl;
    //    cout<<"pii "<< pii<<endl;
    //    cout<<"pie "<< pie<<endl;


    //    num_con  = int (Nneur*Nneur*p1ee);
    num_con  = int (Nneur*Nneur*p1ee);
    //    cout<<"Nneur*Nneur*pee "<< int (Nneur*Nneur*pee)<<endl;
    int con_idx=0;
    for (con_idx = 0; con_idx < num_con; con_idx++)
    {
        // случайно выбираем постсипантические и пресинаптические нейроны
        int pre = rand() % Nex1;
        int post = rand() % Nex1;

        n_con[post]++;
        pre_conns[con_idx] = pre;
        post_conns[con_idx] = post;
        weights[con_idx] = (rand() % ((int)(maxWee - minWee)*10))/10.0f + minWee;


    }



    num_con  += int(Nneur*Nneur*p2ee);
    //    cout<<"Nneur*Nneur*pei "<< int(Nneur*Nneur*pei)<<endl;

    for (; con_idx < num_con; con_idx++)
    {
        // случайно выбираем постсипантические и пресинаптические нейроны
        int pre = (rand() % Nex2)+Nex1;
        int post = (rand() % Nex2)+Nex1;

        n_con[post]++;
        pre_conns[con_idx] = pre;
        post_conns[con_idx] = post;
        weights[con_idx] = (rand() % ((int)(maxWee - minWee)*10))/10.0f + minWee;


    }



    num_con  += int(Nneur*Nneur*p1ei);
    //    cout<<"Nneur*Nneur*pei "<< int(Nneur*Nneur*pei)<<endl;

    for (; con_idx < num_con; con_idx++)
    {
        // случайно выбираем постсипантические и пресинаптические нейроны
        int pre = rand() % Nex1;
        int post = (rand() % Ninh1)+Nex;

        n_con[post]++;
        pre_conns[con_idx] = pre;
        post_conns[con_idx] = post;
        weights[con_idx] = maxWei*2;
        //        weights[con_idx] = (rand() % ((int)(maxWee - minWee)*10))/10.0f + minWee;


    }

    num_con  += int(Nneur*Nneur*p2ei);
    //    cout<<"Nneur*Nneur*pei "<< int(Nneur*Nneur*pei)<<endl;

    for (; con_idx < num_con; con_idx++)
    {
        // случайно выбираем постсипантические и пресинаптические нейроны
        int pre = (rand() % Nex2) + Nex1;
        int post = (rand() % Ninh2)+Nex+Ninh1;

        n_con[post]++;
        pre_conns[con_idx] = pre;
        post_conns[con_idx] = post;
        weights[con_idx] = maxWei*2;
        //        weights[con_idx] = (rand() % ((int)(maxWee - minWee)*10))/10.0f + minWee;


    }

    num_con  += int(Nneur*Nneur*p12ie);
    //    cout<<"Nneur*Nneur*pei "<< int(Nneur*Nneur*pei)<<endl;

    for (; con_idx < num_con; con_idx++)
    {
        // случайно выбираем постсипантические и пресинаптические нейроны
        int pre = (rand() % Ninh1)+Nex ;
        int post = rand() % Nex2+Nex1;

        n_con[post]++;
        pre_conns[con_idx] = pre;
        post_conns[con_idx] = post;
        weights[con_idx] = -((rand() % ((int)(maxWee - minWee)*10))/10.0f + minWee);


    }


    num_con  += int(Nneur*Nneur*p21ie);
    //    cout<<"Nneur*Nneur*pei "<< int(Nneur*Nneur*pei)<<endl;

    for (; con_idx < num_con; con_idx++)
    {
        // случайно выбираем постсипантические и пресинаптические нейроны
        int pre = (rand() % Ninh2)+Nex +Ninh1;
        int post = rand() % Nex1;

        n_con[post]++;
        pre_conns[con_idx] = pre;
        post_conns[con_idx] = post;
        weights[con_idx] = -((rand() % ((int)(maxWee - minWee)*10))/10.0f + minWee);


    }

    num_con  += int(Nneur*Nneur*p12ii);
    //    cout<<"Nneur*Nneur*pei "<< int(Nneur*Nneur*pei)<<endl;

    for (; con_idx < num_con; con_idx++)
    {
        // случайно выбираем постсипантические и пресинаптические нейроны
        int pre = (rand() % Ninh1)+Nex ;
        int post = (rand() % Ninh2)+Nex+Ninh1;

        n_con[post]++;
        pre_conns[con_idx] = pre;
        post_conns[con_idx] = post;
        weights[con_idx] = -((rand() % ((int)(maxWee - minWee)*10))/10.0f + minWee);


    }


    num_con  += int(Nneur*Nneur*p21ii);
    //    cout<<"Nneur*Nneur*pei "<< int(Nneur*Nneur*pei)<<endl;

    for (; con_idx < num_con; con_idx++)
    {
        // случайно выбираем постсипантические и пресинаптические нейроны
        int pre = (rand() % Ninh2)+Nex+Ninh1 ;
        int post = (rand() % Ninh1)+Nex;

        n_con[post]++;
        pre_conns[con_idx] = pre;
        post_conns[con_idx] = post;
        weights[con_idx] = -((rand() % ((int)(maxWee - minWee)*10))/10.0f + minWee);

    }


}

void neur::init_neurons()
{
    for (int neur_idx = 0; neur_idx < Nneur; neur_idx++)
    {
        // случайно разбрасываем приложенные токи
        //        Iex[neur_idx] = (rand() % (int) (Iex_max*10))/10.0f;
        Isyn[neur_idx] = 0.0f;
        //        Vms[neur_idx][0] = V0;
        //        Ums[neur_idx][0] = U0;

    }


    for (int neur_idx = 0; neur_idx < Nneur; neur_idx++)
    {
        // случайно разбрасываем приложенные токи

        if(Iex_max>0)
            lay[neur_idx].Iex=(rand() % (int) (Iex_max*10))/10.0f;
        else
            lay[neur_idx].Iex=0.0f;

        //        cout<<lay[neur_idx].Iex<<endl;
        lay[neur_idx].Isyn = 0.0f;
        lay[neur_idx].Vm = V0;
        lay[neur_idx].Um = U0;
        lay[neur_idx].Vm_before = V0;
        lay[neur_idx].Um_before = U0;
    }
}




float neur::izhik_Vm(int neuron, int time)
{
    return (k*( lay[neuron].Vm_before  - Vr)*(lay[neuron].Vm_before  - Vt) - lay[neuron].Um_before +  lay[neuron].Iex /*Iex[neuron]*/ + Isyn[neuron])/Cm;
}

float neur::izhik_Um(int neuron, int time)
{
    return lay[neuron].a*(lay[neuron].b*(lay[neuron].Vm_before - Vr) - lay[neuron].Um_before);
}


void neur::setIexEq0(float Imax,float Imin=0)
{



    //    for (int neur_idx = 0; neur_idx < Nex; neur_idx++)
    //    {
    //        // устанавливаем приложенные токи = 0
    //        //         Iex[neur_idx] = .0f;
    //        Iex_max=Imax;
    //        lay[neur_idx].Iex=(rand() % (int) (Iex_max*10))/10.0f;;

    //    }

    //    Iex_max=Imax;
    //    Iex_min=Imin;
    if(Imax>0)
        for (int neur_idx = Nex; neur_idx < Nneur; neur_idx++)
        {

            lay[neur_idx].Iex=(rand() % ((int)(Imax - Imin)*10))/10.0f + Imin;


            //    cout<<lay[neur_idx].Iex<<endl;

        }

    else
        for (int neur_idx = Nex; neur_idx < Nneur; neur_idx++)
            lay[neur_idx].Iex=0.0f;
}

void neur::setIexAll(float Imax,float Imin=0)
{


    //    Iex_max=Imax;
    //    Iex_min=Imin;
    if(Imax>0)
        for (int neur_idx = 0; neur_idx < Nneur; neur_idx++)
        {
            lay[neur_idx].Iex=(rand() % ((int)(Imax - Imin)*10))/10.0f + Imin;

            //    cout<<lay[neur_idx].Iex<<endl;

        }

    else
        for (int neur_idx = 0; neur_idx < Nneur; neur_idx++)
            lay[neur_idx].Iex=0.0f;
}



void neur::setIex( int n,float Imax,float Imin=0, string id="ex")
{


    //    Iex_max=Imax;
    //    Iex_min=Imin;
    int ss=0;
    if (id=="inh")
        ss=Nex;
    if(Imax>0)
        for (int neur_idx = 0+ss; neur_idx < ss+n; neur_idx++)
        {
            lay[neur_idx].Iex=(rand() % ((int)(Imax - Imin)*10))/10.0f + Imin;

            //    cout<<lay[neur_idx].Iex<<endl;

        }

    else
        for (int neur_idx = 0+ss; neur_idx < ss+n; neur_idx++)
            lay[neur_idx].Iex=0.0f;
}
void neur::nmain()
{


    cout<<"main"<<endl;
    createLay(Nex,Ninh);


    init_neurons();



    //    QTime midnight(0,0,0);
    //    qsrand(midnight.secsTo(QTime::currentTime()));



    //    init_connections2();
    //    init_connections1();
    init_connections0();


    //     for (int t = 1; t < 10; t++)
    //         cout<<weights[t]<<endl;

    //   float expire_coeff = exp(-h/psc_excxpire_time);
    //    ofstream  res_file ;
    //    res_file.open("rastr.csv");


    for(int ss=0;ss<1;ss++)
    {
        //        QTime midnight(0,0,0);
        //        qsrand(midnight.secsTo(QTime::currentTime()));


        //        setIexAll(40.,20.);
        setIexAll(0.);
        //         setIexAll(45.,40.);
        //                setIexEq0(80.,60);

        //                        setIexAll(0.);
        //                setIex(Nex,32,30,"ex");
        //                                        setIex(Nex,32,30,"ex");

        //            lay[pre_conns[0]].Iex=50.;
        spike_num=0;
        spikes=0;

        char str[6] = "";
        char hg[100];

        strcpy(hg,"rastr" );
        strcat(hg,itoa(ss,str,10));
        strcat(hg,".csv");

        res_file.open(hg);

        strcpy(hg,"voltages" );
        strcat(hg,itoa(ss,str,10));
        strcat(hg,".txt");

        volt_file.open(hg);


        //        int N=Nex;
        //        for (int i=0; i < N; i++)
        //        {
        //            // случайно выбираем постсипантические и пресинаптические нейроны
        //            int p = rand() % (Ninh+Nex);
        //            massNeur[i] = p;
        //            //cout<<p<<endl;

        //        }
        //        for(int i=0;i<Nex1/4;i++)
        //            lay[i].Iex = 60;

        //        for(int i=Nex1;i<Nex2/4+Nex1;i++)
        //            lay[i].Iex = 60;


        for(int i=0;i<Nneur;i++)
        {
            init_poisson2(5.,t_poisson[i]);
            not_spike(i);
        }
        int ni=200/h;

    }

    wgt->repaint();
}








void neur::integrate ()
{

    //        for (int t = Tsim; t < Tsim*2; t++)
    //        {
    // проходим по всем нейронам
    for (int neur = 0; neur < Nneur; neur++)
    {

        //            Vms[neur][t] = Vms[neur][t-1] + h*izhik_Vm(neur, t-1);
        //            Ums[neur][t] = Ums[neur][t-1] + h*izhik_Um(neur, t-1);
        lay[neur].Vm = lay[neur].Vm_before + h*izhik_Vm(neur, t-1);
        lay[neur].Um = lay[neur].Um_before + h*izhik_Um(neur, t-1);


        Isyn[neur] = 0.0f;


        //                                if(t<Tsim/2&&t==int(t_poisson[neur]))
        //        if(t==int(t_poisson[neur]))
        //        {
        //            Isyn[neur] +=16.*weights_poisson[neur];
        //            init_poisson2(5.,t_poisson[neur]);
        //            //                                        if(neur==0)
        //            //                                        cout<<"t= "<<t_poisson[neur]<<" ";
        //        }


        //                volt_file <<t*h<< " " <<lay[neur].Vm_before << endl;

        //                cout<<Vms[neur][t]<<endl;
        //                cout<<Vms[neur][t-1]<<endl;


        if (lay[neur].Vm_before >Vpeak)
        {
            lay[neur].Vm = lay[neur].c;
            //                Vms[neur][t] = c;
            lay[neur].Um = lay[neur].Um_before + lay[neur].d;
            //                spike_times[spike_num] = t*h;
            //                spike_neurons[spike_num] = neur;
            //                if(neur==20)
            {
                res_file <<t*h<< "; " <<neur + 1 << "; " << endl;

                spikes++;
            }

            spike_num++;
            spike(neur);
            wgt->repaint();
            not_spike(neur);
            wgt->repaint();
        }
        //        else
        //            not_spike(neur);

        lay[neur].Vm_before = lay[neur].Vm;
        lay[neur].Um_before = lay[neur].Um;
    }

    //            volt_file <<t*h<< " " <<lay[1].Vm_before << endl;

    // проходим по всем связям
    for (int con = 0; con < Ncon; con++)
    {

        if(weights[con]>0)
        {
            xp[con] = 1. - (1.-xp[con])*exp(-h/trec_e);
            yp[con] = yp[con]*exp(-h/tpsc_e);
            up[con] = up[con]*exp(-h/tfac_e);
            //                cout<<xp[con]<<endl;
        }
        else
        {
            xp[con] = 1. - (1.-xp[con])*exp(-h/trec_i);
            yp[con] = yp[con]*exp(-h/tpsc_i);
            up[con] = up[con]*exp(-h/tfac_i);
        }

        //                up[con] = up[con]*exp(-h*tfac) ;


        xp_bef[con] = xp[con];
        yp_bef[con] = yp[con];
        up_bef[con] = up[con];

        if (lay[pre_conns[con]].Vm_before > Vpeak)
        {
            //                cout<<spike<<endl;
            if(pre_conns[con]<100)
                up[con] = up_bef[con]+Ue*(1-up_bef[con]) ;
            else
                up[con] = up_bef[con]+Ui*(1-up_bef[con]) ;
            xp[con] = xp_bef[con]-up[con]*xp_bef[con];
            //                cout<<xp[con]<<endl;
            yp[con] =  yp_bef[con]+weights[con]*up[con]*xp_bef[con];


        }




        //                Isyn[post_conns[con]] += y[con][1]*weights[con];
        //                Isyn[post_conns[con]] += xp[con]*up[con] *weights[con];
        //                Isyn[post_conns[con]] += yp[con]*( lay[post_conns[con]].Vm-Erev[con]);

        Isyn[post_conns[con]] += yp[con];
        //                 cout<<yp[con]*( lay[post_conns[con]].Vm-Erev[con])<<endl;
        //  Isyn[post_conns[con]] =0;

    }
    //            volt_file <<t*h<< " " <<yp[0]*( lay[post_conns[0]].Vm-Vr)<< endl;
    volt_file <<t*h<< " " << Isyn[90]<< endl;

    //    for (int neur = 0; neur < Nneur; neur++)
    //    {
    //        lay[neur].Vm_before = lay[neur].Vm;
    //        lay[neur].Um_before = lay[neur].Um;
    //    }

    if(t==tc)
    {
        tc=t+400;
        //                for(int i=0;i<Nex/2;i++)
        //                    lay[i].Iex = 0;

        //                for(int i=0;i<Nex1/2;i++)
        //                    lay[i].Iex = 0;

        //                    for(int i=0;i<Nex2/2+Nex1;i++)
        lay[20].Iex = 700;

    }

    if(t==tc-300)
    {
        lay[20].Iex = 0;


    }



    if(t==tc1)
    {
        tc1=t+700;
        //                for(int i=0;i<Nex/2;i++)
        //                    lay[i].Iex = 0;

        //                for(int i=0;i<Nex1/2;i++)
        //                    lay[i].Iex = 0;

        //                    for(int i=0;i<Nex2/2+Nex1;i++)

           lay[80].Iex = 700;

    }

    if(t==tc1-300)
    {
           lay[80].Iex = 0;
    }

    //            if(t==4000)
    //                setIexEq0(80.,50);


    //            if(t==8000)
    //                setIexEq0(30.,10);

    //            if(t>4000)
    //                setIexEq0(60.);
    //                                cout<<"Vms(t)"<<Vms[0][t]<<endl;
    //                                cout<<"Vms(t-1)"<<Vms[0][t-1]<<endl;
    //}

    t++;

}



void neur::drawFiringNeur()
{
    timer->stop();
    integrate();
    //    QApplication::processEvents();
    timer->start(1);

    time_lcd->display(int(t*h));
    if(t==Tsim)
    {            timer->stop();

        for(int i=0;i<Nneur;i++)
            not_spike(i);

        res_file.close();
        volt_file.close();


        QProcess process1(this);

        process1.start ("cmd /c python ../rastr.py \n");
        process1.waitForFinished(5000);

        for(int i=0;i<Nneur;i++)
            cout<<"out_con["<<i<<"]= "<<out_con[i]<<endl;
        //            cout<<"n_con["<<i<<"]= "<<n_con[i]<<endl;


        //            cout<<"код выполнялся "<<t.elapsed()<<endl;
    }
    //        QPalette pal;
    //        pal.setBrush(wgt->backgroundRole(), QBrush(QPixmap::fromImage(*img)));
    //        wgt->setPalette(pal);
}


void neur::spike(int i)
{
    QPainter painter(img);
    QPen pen(Qt::red,20);
    //    QPen pen(QColor (0, 32, 0));
    pen.setCapStyle(Qt::RoundCap);
    painter.setPen(pen);
    //    float g=acos(0.5)*(M_PI/180);
    //    cout<<"g= "<<g<<endl;
    painter.drawPoint(lay[i].x, lay[i].y);

    QPalette pal;
    pal.setBrush(wgt->backgroundRole(), QBrush(QPixmap::fromImage(*img)));
    wgt->setPalette(pal);
}

void neur::not_spike(int i)
{
    QPainter painter(img);
    QPen pen(Qt::green,20);
    if(i+1>Nex)
        pen.setColor(Qt::blue);
    //    QPen pen(QColor (0, 32, 0));
    pen.setCapStyle(Qt::RoundCap);
    painter.setPen(pen);

    painter.drawPoint(lay[i].x, lay[i].y);

    QPalette pal;
    pal.setBrush(wgt->backgroundRole(), QBrush(QPixmap::fromImage(*img)));
    wgt->setPalette(pal);
}


void neur::drawConns()
{
    show_conns();
}

void neur::startIntegrate()
{

    if(stop_id==1)
    {
        stop_id==0;
//        char hg[100];

//        ofstream res_file("rastr0.csv", ios_base::app); // открываем файл для добавления информации к концу файла
        res_file.open("rastr0.csv", ios_base::app); // открываем файл для добавления информации к концу файла
         volt_file.open("voltages.txt", ios_base::app); // открываем файл для добавления информации к концу файла

    }

    Tsim=Tmax;
    while(t<Tsim)
    {
        integrate();
        integrate();

        QApplication::processEvents();

        time_lcd->display(int(t*h));
    }
    //    if(t==Tsim)
    {

        for(int i=0;i<Nneur;i++)
            not_spike(i);

        res_file.close();
        volt_file.close();


        QProcess process1(this);

        process1.start ("cmd /c python ../rastr.py \n");
        process1.waitForFinished(5000);

        for(int i=0;i<Nneur;i++)
            cout<<"out_con["<<i<<"]= "<<out_con[i]<<endl;
        //            cout<<"n_con["<<i<<"]= "<<n_con[i]<<endl;


        //            cout<<"код выполнялся "<<t.elapsed()<<endl;

         stop_id=1;
    }
}
void neur::newLay()
{
    //    createLay(Nex,Ninh);

}
void neur::stopIntegrate()
{
    //    int tmp=t;
    Tsim=t;
    stop_id=1;
    //    t=tmp;
}
 void neur::setMaxTime()
 {
 Tmax  = max_time->value()/h;

 }
