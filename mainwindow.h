#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tmath.h"
#include "qcustomplot.h"
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow(){delete ui;};

signals:
    void settingChanged();

private slots:
    void on_recalculate_clicked();
    void calculation();
    void on_recalculate_2_clicked();

private:
    Ui::MainWindow *ui;
    float samplingRate;
    float speed;
    int channels;
    float pitch;
    int samples;
    float offsexX;
    float offsetY;
    float length;
    float height;
    float resolution;
    std::vector<ArrayXXf> tfm_data;
    std::vector<ArrayXXf>  lookUpTable;
    ArrayXXf tfm_result;
    QCustomPlot *m_plot;
};
#endif // MAINWINDOW_H
