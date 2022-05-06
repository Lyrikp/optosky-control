#include "newwindow.h"
#include "ui_newwindow.h"
#include "mainwindow.h"

#include "DriverType.h"
#include "Driver_app.h"

#include <windows.h>
#include <iostream>
#include <fstream>

#pragma execution_character_set("utf-8")

bool newWindow::deductflag;
bool newWindow::nolinear;
int newWindow::smoothLevel;
bool newWindow::waveshape;
int* newWindow::processedData;

int newWindow::changeflag = 0;


newWindow::newWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::newWindow)
{
    ui->setupUi(this);
}

newWindow::~newWindow()
{
    delete ui;
}


void newWindow::on_boxDeductDark_clicked()
{
    if (ui->boxDeductDark->isChecked())
    {
        newWindow::deductflag = 1;
    }
    else
    {
        newWindow::deductflag = 0;
    }
}


void newWindow::on_boxNoLinearCorrect_clicked()
{
    if (ui->boxNoLinearCorrect->isChecked())
    {
        newWindow::nolinear = 1;
    }
    else
    {
        newWindow::nolinear = 0;
    }

}


void newWindow::on_boxWaveShapeCorrect_clicked()
{
    if (ui->boxWaveShapeCorrect->isChecked())
    {
        newWindow::waveshape = 1;
    }
    else
    {
        newWindow::waveshape = 0;
    }
}

// 接受数据处理
void newWindow::on_buttonCorrect_clicked()
{
    newWindow::smoothLevel = ui->spinSmoothLevel->value();  // 获取滤波平滑参数
    newWindow::changeflag = 1;
    close();

}


void newWindow::on_buttonCancel_clicked()
{
    close();
}

// 导出处理后数据，不保存参数
void newWindow::on_buttonOutputData_clicked()
{
    std::ofstream origindata;
    MainWindow::wave = getWavelength();
    MainWindow::data = ReadSpectrum();
    float* intensity;
    intensity = dataProcess(MainWindow::data.array, newWindow::smoothLevel, newWindow::deductflag, newWindow::nolinear, newWindow::waveshape);

    QList<QPointF> newPoints;
    origindata.open("Data_Output.txt");
    for(int i = 0; i<2000 ; i++)
    {
        QPointF point;
        qreal x = *(MainWindow::wave + i);
        qreal y = *(intensity + i);
        origindata << "[" << x << ", " << y << "]" << std::endl;
        point.setX(x);
        point.setY(y);
        newPoints.append(point);
    }
    origindata.close();

}

