#ifndef NEURONMAINWIDGET_H
#define NEURONMAINWIDGET_H

#include <QWidget>

namespace Ui {
class NeuronMainWidget;
}

class NeuronMainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NeuronMainWidget(QWidget *parent = 0);
    ~NeuronMainWidget();

private slots:
    void on_start_btn_clicked();
    void on_add_layer_btn_clicked();
    void on_stop_btn_clicked();
    void on_integrating_time_sb_editingFinished();

private:
    Ui::NeuronMainWidget *ui;
signals:
    void start_btn_triggered();
    void stop_btn_triggered();
    void add_layer_btn_triggered();
    void integrating_time_changed(double);
    void about_to_close();
protected:
    void closeEvent(QCloseEvent *);
};

#endif // NEURONMAINWIDGET_H
