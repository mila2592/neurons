#include "neuronmainwidget.h"
#include "ui_neuronmainwidget.h"
#include <QDebug>

NeuronMainWidget::NeuronMainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NeuronMainWidget)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("NeuroSpiker"));
}

NeuronMainWidget::~NeuronMainWidget()
{
    delete ui;
}

void NeuronMainWidget::closeEvent(QCloseEvent *)
{
    emit about_to_close();
}

void NeuronMainWidget::on_start_btn_clicked()
{
    qDebug() << "Start btn triggered";
    emit start_btn_triggered();
}

void NeuronMainWidget::on_add_layer_btn_clicked()
{
    qDebug() << "Add layer btn triggered";
    emit add_layer_btn_triggered();
}

void NeuronMainWidget::on_stop_btn_clicked()
{
    qDebug() << "Stop btn triggered";
    emit stop_btn_triggered();
}

void NeuronMainWidget::on_integrating_time_sb_editingFinished()
{
    qDebug() << "Integration time changed";
    emit integrating_time_changed(ui->integrating_time_sb->value());
}
