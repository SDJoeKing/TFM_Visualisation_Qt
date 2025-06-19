#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "tmath.h"
#include <QDebug>
#include <QFile>
#include <QVector3D>
#include <iostream>

using namespace MATH;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(this, &MainWindow::settingChanged, this, &MainWindow::calculation);

    m_plot = new QCustomPlot(this);
    QCPColorMap *_map = new QCPColorMap(m_plot->xAxis, m_plot->yAxis);
    ui->tfmArea->addWidget(m_plot);

    m_plot->xAxis->setLabel("TFM X Axis");
    m_plot->yAxis->setLabel("TFM Y Axis");

    QCPColorScale *scale = new QCPColorScale(m_plot);
    _map->setColorScale(scale);

}



void MainWindow::on_recalculate_clicked()
{
    samplingRate = ui->rate->value() * 1e6;
    speed = ui->speed->value();
    channels = ui->channel->value();
    pitch = ui->pitch->value();
    samples = ui->samples->value();
    offsexX = ui->offsetX->value();
    offsetY = ui->offsetY->value();
    length = ui->width->value();
    height = ui->height->value();
    resolution = ui->resolution->value();

    if(!tfm_data.empty())
        tfm_data.clear();
    if(!lookUpTable.empty())
        lookUpTable.clear();

    int numOfRow = height / resolution;
    int numOfCol = length / resolution;

    // empty data array and tfm result array for new configurations
    for(int tx = 0 ; tx < channels; tx++)
    {
        tfm_data.emplace_back(ArrayXXf::Zero(channels, samples));
        lookUpTable.emplace_back(ArrayXXf::Zero(numOfRow, numOfCol));
    }

    bool out = populateMAT(tfm_data, ui->lineEdit->text());
    
    if(!out)
        throw std::runtime_error("Cannot load data"); // this can be replaced by a QMessagebox::warning for better App execution
    
    auto map = static_cast<QCPColorMap *>(m_plot->plottable());
    map->data()->setSize( int(length / resolution), int(height / resolution));
    map->data()->setRange(QCPRange(offsexX, offsexX+length), QCPRange(offsetY, offsetY + height));
    map->setGradient(QCPColorGradient::gpJet);

    map->rescaleDataRange();
    map->rescaleAxes();
    m_plot->replot(QCustomPlot::rpImmediateRefresh);

    emit settingChanged();
}

void MainWindow::calculation()
{

    int numOfRow = height / resolution;
    int numOfCol = length / resolution;

    // generate TFM look up table holding calculated distance from pixels (focus points) to the Tx channels
    generateLookTable(lookUpTable, speed, pitch, offsexX, offsetY, resolution);
    tfm_result = ArrayXXf(numOfRow, numOfCol);

    // calculate TFM results according to lookUpTable
    TFM(tfm_data, tfm_result, lookUpTable, samplingRate);

    QCPColorMap *_map = static_cast<QCPColorMap *>(m_plot->plottable());
    auto key = _map->data()->keySize();
    auto value = _map->data()->valueSize();

    _map->data()->fill(0);

    for(int row = 0; row< value; row++)
    {
        for(int col = 0; col < key; col++)
            _map->data()->setCell(col, row, qAbs(tfm_result(row, col)));
    }
    _map->setGradient(QCPColorGradient::gpJet);
    _map->rescaleDataRange();
    _map->rescaleAxes();
    m_plot->replot(QCustomPlot::rpQueuedRefresh);
}

// This is file selection button
void MainWindow::on_recalculate_2_clicked()
{
    QString name = QFileDialog::getOpenFileName(this, "Select FMC data", QApplication::applicationFilePath(), "*.dat");
    ui->lineEdit->setText(name);
}

