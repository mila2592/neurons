#include "core.h"
#include <QDebug>

Core &Core::instance()
{
    static Core core_object;
    return core_object;
}

Core::Core(QObject *obj) : QObject(obj)
{
    ;
}

void Core::init_core()
{
    // Create main window for application. Note, it will be autoremoved
    NeuronMainWidget *widget = new NeuronMainWidget();
    connect(widget,SIGNAL(about_to_close()), this, SLOT(prepare_to_close()));
    widget->show();

    // Create neuron net
    neuron_net = new NeuronNet();
}

void Core::prepare_to_close()
{
    qDebug() << "Core:: preparing to close...";
    delete neuron_net;
}
