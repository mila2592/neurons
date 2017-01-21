#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QWidget>
#include <QtGui>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <QGlobal.h>
#include <QDebug>
#include <qwt_plot_picker.h>
#include <qwt_plot_zoomer.h>



class neur : public QWidget
{
    Q_OBJECT

public:
    neur(QWidget *parent = 0);
    ~neur();
    //private:




    struct neuron
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


        //        int id;
        //        string info;


    };



    neuron *lay;
    float **y;

    int *pos_x,*pos_y;

    int *pre_conns;    // индексы пресинаптических нейронов
    int *post_conns;   // индексы постсинаптических нейронов
    float *weights; 	// веса связей

    // float **Vms; // мембранные потенциалы
    //    float  **Ums; // вспомогательные переменные модели Ижикевича
    //    float *Iex; 		// внешний постоянный ток приложенный к нейрону
    float *Isyn,*n_con,*out_con; 		// синаптический ток на каждый нейрон



    double *xp,*yp,*up;
    double *xp_bef,*yp_bef,*up_bef;

    float *nAMPA,*nGABA,*Erev;
    float *t_poisson,*weights_poisson;

    struct Lay
    {

        neuron *l;
    };

    void init_neurons();
    //    void init_connections();
    void init_connections0();
    void init_connections1();
    void init_connections2();
    void init_conns_gauss();
    void resize_mass_conns(int new_size);

    float izhik_Vm(int neuron, int time);
    float izhik_Um(int neuron, int time);
    void nmain();
    void createLay(int Nex,int Ninh);
    float izhik_Vm_bef(neur *mass, int neuron);
    float izhik_Um_bef(neur *mass,int neuron);

    void setIexEq0(float Imax,float Imin);
    void setIexAll(float Imax,float Imin);
    void setIex(int n, float Imax,float Imin,std::string id);
    void integrate ();
    void spike(int i);
    void not_spike(int i);
    void show_conns();
    void test();
    //////////////////////////////////////////////////////////////////////////////////

    QWidget *wgt,*wgt1,*wgt2,*wgt3,*wgt4,*wgt5,*wgt6,*wgt7;//странички
    QTabWidget *tw;
    ////////////////////////////////
    //для стр1
    ////////////////////////////////
    QTimer *timer;
    QImage *img,*img1;

    QPushButton *conns_btn,*start_btn,*stop_btn,*newLay_btn;
    QLabel *label1,*label2,*time_lbl;

    QwtPlot *plot1,*plot2;
    QwtPlotCurve *curve1;
    QScrollArea *sa;
    QGraphicsView *gv;
    QPainter *p1;

    QLCDNumber *time_lcd;

    void paintEvent(QPaintEvent* );
private slots:
    void drawFiringNeur();
    void drawConns();
    void startIntegrate();
    void stopIntegrate();
    void newLay();
};

#endif // MAINWINDOW_H

