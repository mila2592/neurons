#include "mainwindow.h"
#include "neuron.h"
#include "neuronnet.h"
#include <conio.h>
#include <iostream>
#include <math.h>

#include <fstream>
#include <cstdlib>
#include "functions.cpp"
#include <QProcess>

//QImage *img;
using namespace std;

double step = 0.01;
double T = 0;

neur::neur(QWidget *parent): QWidget(parent)

{

    //    //Py_Initialize();


    //    //    static const QString PROGRAM_NAME = "C:/Python27/python.exe"; // Для примера - Блокнот
    //    //    QProcess::startDetached( PROGRAM_NAME );

    //    QProcess process(this);
    //    //    QString scriptFile =  QCoreApplication::applicationDirPath() + "../../scriptPath/script.py";
    //    //      QString scriptFile =  "C:/QTp/neurShotTerm/neur1/rastr.py";
    //    QString scriptFile =  "rastr.py";
    //    QStringList pythonCommandArguments = QStringList() <<"/С"<< "python"<<" rastr.py";

    //    ////    printf("PyCommand: %s\n", qStringToStdString(pythonCommandArguments.join(' ')).c_str());
    //    process.start ("cmd.exe",QStringList("cmd /c python rastr.py \n"));
    //    //   process.start ("cmd /c python rastr.py \n");
    //    process.waitForFinished(5000);

    //    //   if(process.exitStatus()==true)
    //    cout<<"terminated"<<endl;
    //    process.terminate();

    //    //  process.waitForStarted();
    //    //process.waitForFinished(500);


    //        static const QString PROGRAM_NAME = "C:/Windows/System32/cmd.exe";
    ////       process.startDetached  ( PROGRAM_NAME);
    ////       process.putChar(*"python rastr.py");
    //               process.startDetached  ( PROGRAM_NAME,QStringList("C:\QTp\neurShotTerm\neur1"));

    //        process.startDetached(PROGRAM_NAME,pythonCommandArguments);
    //  process.waitForReadyRead();
    //        process.waitForFinished();
    //        QProcess::startDetached( PROGRAM_NAME,QStringList("python rastr.py"));

    QTime t;
    t.start();


    //        QTime midnight(0,0,0);
    //        qsrand(midnight.secsTo(QTime::currentTime()));

    Ncon  = int(Nneur*Nneur*pee);
    //    cout<<"Ncon "<< Ncon<<endl;
    Ncon +=int(Nneur*Nneur*pei);
    //    cout<<"Ncon "<< Ncon<<endl;
    Ncon+=int(Nneur*Nneur*pii);
    //    cout<<"Ncon "<< Ncon<<endl;
    Ncon+=int(Nneur*Nneur*pie);


    cout<<"Ncon "<< Ncon<<endl;
    //Ncon=20;


    //    y = new float*[Ncon];
    //    for(int i=0;i<Ncon;i++)
    //        y[i]= new float[2];

    pre_conns = new int[Ncon];
    post_conns = new int[Ncon];
    weights = new float[Ncon];


    xp = new double[Ncon];
    yp = new double[Ncon];
    up = new double[Ncon];
    xp_bef=new double[Ncon];
    yp_bef=new double[Ncon];
    up_bef=new double[Ncon];

    Erev=new float[Ncon];

    for(int i=0;i<Ncon;i++)
    {
        xp[i]=0.0;
        yp[i]=1.;
        up[i]=0.5;

        xp_bef[i]=0.0;
        yp_bef[i]=1.;
        up_bef[i]=0.5;

        weights[i]=0;
    }

    //    Vms = new float*[Nneur]; // мембранные потенциалы
    //    for(int i=0;i<Nneur;i++)
    //        Vms[i]= new float[Tsim];

    //    Ums = new float*[Nneur]; // мембранные потенциалы
    //    for(int i=0;i<Nneur;i++)
    //        Ums[i]= new float[Tsim];


    //    Iex=new float [Nneur]; 		// внешний постоянный ток приложенный к нейрону
    Isyn= new float[Nneur]; 		// синаптический ток на каждый нейрон

    nAMPA= new float[Nneur];
    nGABA= new float[Nneur];


    t_poisson= new float[Nneur];
    weights_poisson= new float[Nneur];

    n_con= new float[Nneur];
    out_con= new float[Nneur];
    for(int i=0;i<Nneur;i++)
    {
        n_con[i] =0;
        out_con[i]=0;
        t_poisson[i]= 0;
        weights_poisson[i] = 100; //((rand() % ((int)(maxWie - minWie)*10))/10.0f + minWie);
    }

    //    QTime midnight(0,0,0);
    //    qsrand(midnight.secsTo(QTime::currentTime()));





    /////////////////////////////////////////////////
    //реализация самого окна со страничками
    /////////////////////////////////////////////////

    QTextCodec::setCodecForTr(QTextCodec::codecForName ("Windows-1251"));//для русского текста
    QGridLayout *layout = new QGridLayout;
    tw=new QTabWidget(this);

    wgt1=new QWidget(this);//виджеты для страничек
    wgt2=new QWidget(this);wgt3=new QWidget;//виджеты для страничек
    wgt4=new QWidget; wgt5=new QWidget;//виджеты для страничек
    wgt6=new QWidget; wgt7=new QWidget;//виджеты для страничек

    tw->insertTab(1,wgt1,"page1");//странички
    tw->insertTab(2,wgt2,"page2");

    layout->addWidget(tw, 0, 0);
    setLayout(layout);

    ////////////////////////////////////////////
    //для стр 1
    /////////////////////////////////////////////
    time_lcd = new QLCDNumber;
    time_lcd->setSegmentStyle(QLCDNumber::Flat);
    time_lcd->setMinimumSize(100, 25);

    timer = new QTimer;
    //    connect(timer, SIGNAL(timeout()), this, SLOT(drawFiringNeur()));
    //     timer->start(20);

    conns_btn=new QPushButton(tr("показать связи"));
    start_btn=new QPushButton(tr("старт"));
    stop_btn=new QPushButton(tr("стоп"));
    newLay_btn=new QPushButton(tr("создать слой"));

    label1=new QLabel("label1");
    label2=new QLabel("label2");
    time_lbl=new QLabel(tr("мс"));
    max_time_lbl=new QLabel(tr("время \nинтегрирования, мс"));


    max_time= new QSpinBox;
    max_time->setRange(0,9999999999);
    max_time->setValue(Tmax*h);

    plot1=new QwtPlot;
    plot2=new QwtPlot;
    plot1->setFixedSize(1000,1000);
    curve1=new QwtPlotCurve;
    curve1->setStyle(QwtPlotCurve::Dots);
    curve1->setPen(QPen(Qt::blue));
    plot1->setAxisTitle(QwtPlot::xBottom,"time");
    plot1->setAxisTitle(QwtPlot::yLeft,"x1");
    curve1->attach(plot1);


    /*QGraphicsView **/gv=new  QGraphicsView;
    QGraphicsScene *gs=new QGraphicsScene /*(QRectF(0,0,30,30))*/;

    /* QScrollArea **/sa=new QScrollArea(wgt1);
    //    sa->setSizeIncrement(10,10);
    //sa->setWidget(plot1);

    img = new QImage(QSize(sc, sc), QImage::Format_ARGB32_Premultiplied);

    //    img->setColor(100,Qt::white);

    wgt = new QWidget(sa);
    QPalette pal;
    pal.setBrush(wgt->backgroundRole(), QBrush(QPixmap::fromImage(*img)));
    wgt->setPalette(pal);
    wgt->resize(sc, sc);
    wgt->setAutoFillBackground(true);
    sa->setWidget(wgt);

    wgt->show();


    QGridLayout *layout1 = new QGridLayout;

    layout1->addWidget(label1, 1, 1);
    layout1->addWidget(label2, 1, 2);
    layout1->addWidget(time_lcd, 1, 3);
    layout1->addWidget(time_lbl, 1, 4);
    layout1->addWidget(conns_btn, 2, 1);
    layout1->addWidget(start_btn, 2, 2);
    layout1->addWidget(stop_btn, 3, 2);
    layout1->addWidget(max_time, 4, 2);
    layout1->addWidget(max_time_lbl, 4, 3);
    layout1->addWidget(newLay_btn, 2, 3);
    layout1->addWidget(sa, 3, 1);


    wgt1->setLayout(layout1);
    connect(conns_btn, SIGNAL(clicked()), this, SLOT(drawConns()));
    //    connect(start_btn, SIGNAL(clicked()), timer, SLOT(start()));
    connect(start_btn, SIGNAL(clicked()), this, SLOT(startIntegrate()));
    connect(stop_btn, SIGNAL(clicked()), this, SLOT(stopIntegrate()));
    connect(newLay_btn, SIGNAL(clicked()), this, SLOT(newLay()));
    connect(max_time, SIGNAL(valueChanged(int)), this, SLOT(setMaxTime()));



    //    Neuron n1('e');
    //    Neuron n2('i');
    //    Neuron n3;
    //    Neuron n4('d');
    //    n1.showPar();
    //    n2.showPar();
    //    n3.showPar();
    //    n4.showPar();

    NeuronNet net1;
    net1.add_layer(200,25);

    net1.add_layer(200,25);

    //    net1.add_layer(15,7);

    //    net1.add_layer(10,1);
    //    net1.add_layer(12,5);
    //    net1.add_layer(14,7);
    //  int a=  net1.size(0);

    cout<<net1.size_of_lay(0)<<endl;
//    net1.connect_layers(0, 1);
        net1.connect_layers(0, 0);
    net1.tmp();
    //    for(int i=0;i<4;i++)
    //        net1.neuron_info(0,i);
    //    cout<<"net1.size= "<<net1.size()<<endl;
    //    cout<< "net1.neuron_layers[0]= "<<net1.neuron_layers[0].size()<<endl;
    //    cout<< "net1.num_neurons_in_layers[0][1]= "<<net1.num_ex_in_lay(0)<<endl;
    //    cout<< "net1.num_neurons_in_layers[0][1]= "<<net1.num_inh_in_lay(1)<<endl;


    //    net1.connect_layers(0, 0);
    //    net1.show_conns_for_lay(0,0);


    //    net1.connect_layers(2, 3);
    //    net1.connect_layers(0, 1);
    //    net1.connect_layers(2, 3);

    //    net1.show_conns_for_lay(2,3);



    std::vector <std::vector <int> > post_neur;

    for(int i=0;i<10;i++)
    {
        std::vector <int> vecc;
        post_neur.push_back(vecc);
    }
    post_neur[0].push_back(1);
    post_neur[0].push_back(2);
    post_neur[0].push_back(3);


    post_neur[9].push_back(1);
    post_neur[9].push_back(2);
    post_neur[9].push_back(3);



    for(int i=0;i<post_neur[0].size();i++)
        cout<<"dd= "<<post_neur[0][i]<<endl;


    //    vector <int> vecInt(3,100); ///Создаем вектор из 3 элементов и заполняем его значением 100
    //    vector <int>::iterator it;
    //    it = vecInt.begin(); ///Итератор указывает на vec[0]

    //    ///Вектор расширяется теперь до 4 элементов
    //    vecInt.insert (it,200); ///И первым элементом записывается 200

    //    ///Вектор расширяется теперь до 5 элементов
    //    it = vecInt.begin() + 3;///Вектор указывает на 4 элемент (0-элемент+3-элемента)
    //    vecInt.insert(it,300);///И четвертым элементом записывается 300
    //    vecInt.insert(it+1,900);///Вектор расширяется теперь до 6 элементов и 5 элементом записывается 900


    //    vector<std::vector<Neuron> > neur_vec;
    //    neur_vec.push_back(std::vector<Neuron>(4));
    //    neur_vec.push_back(std::vector<Neuron>(4));

    //    cout<<"neur_vec.size= "<<neur_vec.size()<<endl;
    //    cout<<"neur_vec[0].size= "<<neur_vec[0].size()<<endl;
    //    neur_vec[0].size();
    //    neur_vec[0][0].showPar();
    //cout<<net1.neuron_layers.size()<<endl;

    //    char ak = '0xffx0';
    //    cout<<"ak= "<<ak<<endl;
    ////   createLay(100,30);
    //    createLay(Nex,Ninh);
    nmain();
    //    init_connections1();
    //    timer->start(1);




    //       init_conns_gauss();
    //    show_conns();

    //    coord = new double[n];
    //    ydata = new double[MAX_POINTS1];
    //    tdata = new double[MAX_POINTS1];
    //    y1data = new double[MAX_POINTS1];
    //    r1data = new double[MAX_POINTS1];
    //    r2data = new double[MAX_POINTS1];




    //    QProcess process1(this);

    //    process1.start ("cmd /c python rastr.py \n");
    //    process1.waitForFinished(-1);

    //     cout<<"код выполнялся "<<t.elapsed()<<endl;

    ///////////////////////////////////////////

    //        cout<<"nmain running...."<<endl;
    //        nmain();
    //            show_conns();
    //        cout<<"код выполнялся "<<t.elapsed()<<endl;



    //    for(int i=0;i<Ncon;i++)
    //        delete []y[i];
    //    delete []y;


    //    delete []pre_conns;
    //    delete []post_conns;

    //    delete []weights;

    //    delete []xp;
    //    delete []yp;
    //    delete []up;

    //    delete []xp_bef;
    //    delete []yp_bef;
    //    delete []up_bef;

    //    delete []nAMPA;
    //    delete []nGABA;
    //    delete []Erev;

    //    delete []n_con;

    //    if(lay)
    //        delete []lay;

    //    //    delete []Iex;
    //    delete []Isyn;

}


void neur::paintEvent(QPaintEvent* pe)
{

    int ss=Nneur;
    //        QPainter painter(img);
    //        QPen pen(Qt::green,20);
    //        //    QPen pen(QColor (0, 32, 0));
    //        pen.setCapStyle(Qt::RoundCap);
    //        painter.setPen(pen);
    //        for(int i=0;i<ss;i++)
    //        {
    //            painter.drawPoint(lay[i].x, lay[i].y);
    //            //        cout<<"x= "<<lay[i].x<<" y= "<<lay[i].y<<endl;
    //        }
    //        pen.setWidth(2);
    //        pen.setColor(Qt::blue);
    //        painter.setPen(pen);
    //        for(int i=0;i<num_con;i++)
    //        {
    //            painter.drawLine(QPoint(lay[pre_conns[i]].x, lay[pre_conns[i]].y),QPoint(lay[post_conns[i]].x, lay[post_conns[i]].y));
    //            //        cout<<"x= "<<lay[i].x<<" y= "<<lay[i].y<<endl;
    //        }
    //        QPalette pal;
    //        pal.setBrush(wgt->backgroundRole(), QBrush(QPixmap::fromImage(*img)));
    //        wgt->setPalette(pal);

}


void neur::show_conns()
{
    int ss=Nneur;
    QPainter painter(img);

    QPen pen(Qt::green,20);
    //    QPen pen(QColor (0, 32, 0));
    pen.setCapStyle(Qt::RoundCap);
    painter.setPen(pen);
    for(int i=0;i<ss;i++)
    {
        if(i+1>Nex)
        {
            pen.setColor(Qt::blue);
            //    QPen pen(QColor (0, 32, 0));
            painter.setPen(pen);
        }

        painter.drawPoint(lay[i].x, lay[i].y);
        //        cout<<"x= "<<lay[i].x<<" y= "<<lay[i].y<<endl;
    }

    pen.setWidth(1);
    pen.setColor(Qt::lightGray);
    painter.setBrush(Qt::lightGray);
    painter.setPen(pen);

    //  /*
    for(int i=0;i<num_con;i++)
    {
        //        painter.drawLine(QPoint(lay[pre_conns[i]].x, lay[pre_conns[i]].y),QPoint(lay[post_conns[i]].x, lay[post_conns[i]].y));
        //        //        cout<<"x= "<<lay[i].x<<" y= "<<lay[i].y<<endl;


        QPolygon arrow;
        int arrowWidth=5,arrowHeight=7;
        arrow << QPoint(0, -arrowWidth/2)
              << QPoint(arrowHeight, 0)
              << QPoint(0, arrowWidth/2);
        //                QPointF beginPoint(80,60),endPoint(10,14);

        if(pre_conns[i]!=post_conns[i])
        {
            QPoint beginPoint(lay[pre_conns[i]].x, lay[pre_conns[i]].y),endPoint(lay[post_conns[i]].x, lay[post_conns[i]].y);
            //        cout<<"pre_conns= "<<pre_conns[i]<<" post_conns= "<<post_conns[i]<<endl;

            QPoint p0(beginPoint);
            QPoint p1(endPoint);
            double dx = p1.x() - p0.x();
            double dy = p1.y() - p0.y();
            double angle = atan2(dy, dx);
            QPoint p2(p1.x() - arrowHeight * cos(angle),
                      p1.y() - arrowHeight * sin(angle));
            double lineLen = sqrt(dx*dx + dy*dy);

            if(lineLen >= arrowHeight){
                painter.drawLine(p0, p2);
            }
            painter.save();
            painter.translate(p2);
            painter.rotate(180/3.14159 * angle);
            painter.drawConvexPolygon(arrow);
            painter.restore();
        }
        else
            painter.drawPoint(lay[i].x, lay[i].y);

    }
    //    */



    //    QPolygon arrow;
    //    int arrowWidth=10,arrowHeight=16;
    //            arrow << QPoint(0, -arrowWidth/2)
    //                  << QPoint(arrowHeight, 0)
    //                  << QPoint(0, arrowWidth/2);
    //            QPointF beginPoint(80,60),endPoint(10,14);

    //            QPointF p0(beginPoint);
    //            QPointF p1(endPoint);
    //            double dx = p1.x() - p0.x();
    //            double dy = p1.y() - p0.y();
    //            double angle = atan2(dy, dx);
    //            QPointF p2(p1.x() - arrowHeight * cos(angle),
    //                       p1.y() - arrowHeight * sin(angle));
    //            double lineLen = sqrt(dx*dx + dy*dy);

    //            if(lineLen >= arrowHeight){
    //                painter.drawLine(p0, p2);
    //            }
    //            painter.save();
    //            painter.translate(p2);
    //            painter.rotate(180/3.14159 * angle);
    //            painter.drawConvexPolygon(arrow);
    //            painter.restore();
    //////////////////////////////////
    QPalette pal;
    pal.setBrush(wgt->backgroundRole(), QBrush(QPixmap::fromImage(*img)));
    wgt->setPalette(pal);
}


void neur::test()
{

    QPolygon arrow;
    int arrowWidth=10,arrowHeight=6;
    arrow << QPoint(0, -arrowWidth/2)
          << QPoint(arrowHeight, 0)
          << QPoint(0, arrowWidth/2);
    QPointF beginPoint(0,0),endPoint(10,60);

    QPainter painter(img);
    QPointF p0(beginPoint);
    QPointF p1(endPoint);
    double dx = p1.x() - p0.x();
    double dy = p1.y() - p0.y();
    double angle = atan2(dy, dx);
    QPointF p2(p1.x() - arrowHeight * cos(angle),
               p1.y() - arrowHeight * sin(angle));
    double lineLen = sqrt(dx*dx + dy*dy);

    if(lineLen >= arrowHeight){
        painter.drawLine(p0, p2);
    }
    painter.save();
    painter.translate(p2);
    painter.rotate(180/3.14159 * angle);
    painter.drawConvexPolygon(arrow);
    painter.restore();
}


neur::~neur()
{
    cout<<endl<<" destr"<<endl;


}
//void btn::closeEvent(QCloseEvent *q)//событие при закрытии приложения
//{
//    stp7=1;
//    cout<<endl<<" close"<<endl;
//    menu4->close();
//    init_point->close();
//    if(indicator==1)
//        stop_move();
//    delete []coord;
//    delete []ydata;
//    delete []tdata;
//    delete []y1data;
//    delete []r1data;
//    delete []r2data;


//    //    for(int i=0;i<100;i++)
//    //       delete  []pointS[i];
//    //     delete []pointS;


//    //    for(int i=0;i<n;i++)
//    //      delete []dx[i];

//    //    delete []dx;

//    //    Sdx= new double*[100];
//    //    for(int i=0;i<100;i++)
//    //         delete []Sdx[i];
//    //     delete []Sdx;
//    delete []Sx;
//    delete []Sf;
//}
