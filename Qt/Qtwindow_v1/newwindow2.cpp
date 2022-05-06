#include "newwindow2.h"
#include "ui_newwindow2.h"

#include "newwindow.h"
#include "ui_newwindow.h"
#include "mainwindow.h"

#include "DriverType.h"
#include "Driver_app.h"

#include <windows.h>
#include <iostream>
#include <fstream>

#pragma execution_character_set("utf-8")
#include <QTextCodec>
#include "newwindow.h"
#include "newwindow2.h"
#include "qcustomplot.h"
#include <QMouseEvent>

bool newwindow2::fileflag = 0;
int newwindow2::D = 1660;
double newwindow2::Ca[2001];
bool newwindow2::Caready = 0;

newwindow2::newwindow2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::newwindow2)
{
    // 限制输入为 double 形式
    ui->setupUi(this);
    ui->Spectrum10->setValidator(new QDoubleValidator(this));
    ui->Spectrum1->setValidator(new QDoubleValidator(this));
    ui->Spectrum2->setValidator(new QDoubleValidator(this));
    ui->Spectrum3->setValidator(new QDoubleValidator(this));
    ui->Spectrum4->setValidator(new QDoubleValidator(this));
    ui->Spectrum5->setValidator(new QDoubleValidator(this));
    ui->Spectrum6->setValidator(new QDoubleValidator(this));
    ui->Spectrum7->setValidator(new QDoubleValidator(this));
    ui->Spectrum8->setValidator(new QDoubleValidator(this));
    ui->Spectrum9->setValidator(new QDoubleValidator(this));

    ui->Wave10->setValidator(new QDoubleValidator(this));
    ui->Wave1->setValidator(new QDoubleValidator(this));
    ui->Wave2->setValidator(new QDoubleValidator(this));
    ui->Wave3->setValidator(new QDoubleValidator(this));
    ui->Wave4->setValidator(new QDoubleValidator(this));
    ui->Wave5->setValidator(new QDoubleValidator(this));
    ui->Wave6->setValidator(new QDoubleValidator(this));
    ui->Wave7->setValidator(new QDoubleValidator(this));
    ui->Wave8->setValidator(new QDoubleValidator(this));
    ui->Wave9->setValidator(new QDoubleValidator(this));

}

newwindow2::~newwindow2()
{
    delete ui;
}



// 点击确定按键之后进行线性拟合
void newwindow2::on_AcceptData_clicked()
{
    // 接受输入的数据
    if (fileflag==0) // 没有输入数据文件的时候
    {
        double R0x[11], R0y[11];
        R0x[0] = 0;
        R0x[1] = ui->Wave1->text().toDouble();
        R0x[2] = ui->Wave2->text().toDouble();
        R0x[3] = ui->Wave3->text().toDouble();
        R0x[4] = ui->Wave4->text().toDouble();
        R0x[5] = ui->Wave5->text().toDouble();
        R0x[6] = ui->Wave6->text().toDouble();
        R0x[7] = ui->Wave7->text().toDouble();
        R0x[8] = ui->Wave8->text().toDouble();
        R0x[9] = ui->Wave9->text().toDouble();
        R0x[10] = ui->Wave10->text().toDouble();

        R0y[0] = 0;
        R0y[1] = ui->Spectrum1->text().toDouble();
        R0y[2] = ui->Spectrum2->text().toDouble();
        R0y[3] = ui->Spectrum3->text().toDouble();
        R0y[4] = ui->Spectrum4->text().toDouble();
        R0y[5] = ui->Spectrum5->text().toDouble();
        R0y[6] = ui->Spectrum6->text().toDouble();
        R0y[7] = ui->Spectrum7->text().toDouble();
        R0y[8] = ui->Spectrum8->text().toDouble();
        R0y[9] = ui->Spectrum9->text().toDouble();
        R0y[10] = ui->Spectrum10->text().toDouble();

        double k[10], b[10];
        double nRx[2001], nRy[2001];
        for (int i=0; i<2001; ++i)
        {
          nRx[i] = *(MainWindow::wave + i);
        }
        int i2 = 0;
        for(int i = 0; i<9; i++)    // 拟合R曲线
        {
            k[i] = (R0y[i+1]-R0y[i])/(R0x[i+1]-R0x[i]);
            b[i] = R0y[i] - k[i]*R0x[i];

            while(nRx[i2]<R0y[i])
            {
                nRy[i2] = nRx[i2]*k[i] + b[i];
                i2++;
            }
        }

        // 接受B曲线
        double Bx[2001], By[2001];
        MainWindow::wave = getWavelength();
        MainWindow::data = ReadSpectrum();
        for (int i=0; i<2001; ++i)
        {
            Bx[i] = *(MainWindow::wave + i);
            By[i] = *(MainWindow::data.array + i);
        }

        // 计算C曲线
        for (int i = 0; i<2000; i++)
        {
            newwindow2::Ca[i] = (nRy[i] * MainWindow::time_global)/(By[i] - newwindow2::D);
        }
        newwindow2::Caready = 1; // 设置Ca完成
    /* 构造体形式 会导致内存溢出
    // 接受输入的数据
    if (fileflag==0) // 没有输入数据文件的时候
    {
        QVector<double> R0x(11), R0y(11);
        R0x[0] = 0;
        R0x[1] = ui->Wave1->text().toDouble();
        R0x[2] = ui->Wave2->text().toDouble();
        R0x[3] = ui->Wave3->text().toDouble();
        R0x[4] = ui->Wave4->text().toDouble();
        R0x[5] = ui->Wave5->text().toDouble();
        R0x[6] = ui->Wave6->text().toDouble();
        R0x[7] = ui->Wave7->text().toDouble();
        R0x[8] = ui->Wave8->text().toDouble();
        R0x[9] = ui->Wave9->text().toDouble();
        R0x[10] = ui->Wave10->text().toDouble();

        R0y[0] = 0;
        R0y[1] = ui->Spectrum1->text().toDouble();
        R0y[2] = ui->Spectrum2->text().toDouble();
        R0y[3] = ui->Spectrum3->text().toDouble();
        R0y[4] = ui->Spectrum4->text().toDouble();
        R0y[5] = ui->Spectrum5->text().toDouble();
        R0y[6] = ui->Spectrum6->text().toDouble();
        R0y[7] = ui->Spectrum7->text().toDouble();
        R0y[8] = ui->Spectrum8->text().toDouble();
        R0y[9] = ui->Spectrum9->text().toDouble();
        R0y[10] = ui->Spectrum10->text().toDouble();

        QVector<double> k(10), b(10);
        QVector<double> nRx(2001), nRy(2001);
        for (int i=0; i<2001; ++i)
        {
          nRx[i] = *(MainWindow::wave + i);
        }
        int i2 = 0;
        for(int i = 0; i<10; i++)    // 拟合R曲线
        {
            k[i] = (R0y[i+1]-R0y[i])/(R0x[i+1]-R0x[i]);
            b[i] = R0y[i] - k[i]*R0x[i];

            while(nRx[i2]<R0y[i])
            {
                nRy[i2] = nRx[i2]*k[i] + b[i];
                i2++;
            }
        }

        // 接受B曲线
        QVector<double> Bx(2001), By(2001);
        MainWindow::wave = getWavelength();
        MainWindow::data = ReadSpectrum();
        for (int i=0; i<2001; ++i)
        {
            Bx[i] = *(MainWindow::wave + i);
            By[i] = *(MainWindow::data.array + i);
        }

        // 计算C曲线
        for (int i = 0; i<2000; i++)
        {
            *(newwindow2::Ca + i) = (nRy[i] * MainWindow::time_global)/(By[i] - newwindow2::D);
        }
        newwindow2::Caready = 1; // 设置Ca完成
*/
    }
    close();
}

// 生成Ca
void newwindow2::on_buttonCaOutput_clicked()
{
    // 接受输入的数据
    if (fileflag==0) // 没有输入数据文件的时候
    {
        double R0x[11], R0y[11];
        R0x[0] = 0;
        R0x[1] = ui->Wave1->text().toDouble();
        R0x[2] = ui->Wave2->text().toDouble();
        R0x[3] = ui->Wave3->text().toDouble();
        R0x[4] = ui->Wave4->text().toDouble();
        R0x[5] = ui->Wave5->text().toDouble();
        R0x[6] = ui->Wave6->text().toDouble();
        R0x[7] = ui->Wave7->text().toDouble();
        R0x[8] = ui->Wave8->text().toDouble();
        R0x[9] = ui->Wave9->text().toDouble();
        R0x[10] = ui->Wave10->text().toDouble();

        R0y[0] = 0;
        R0y[1] = ui->Spectrum1->text().toDouble();
        R0y[2] = ui->Spectrum2->text().toDouble();
        R0y[3] = ui->Spectrum3->text().toDouble();
        R0y[4] = ui->Spectrum4->text().toDouble();
        R0y[5] = ui->Spectrum5->text().toDouble();
        R0y[6] = ui->Spectrum6->text().toDouble();
        R0y[7] = ui->Spectrum7->text().toDouble();
        R0y[8] = ui->Spectrum8->text().toDouble();
        R0y[9] = ui->Spectrum9->text().toDouble();
        R0y[10] = ui->Spectrum10->text().toDouble();

        double k[10], b[10];
        double nRx[2001], nRy[2001];
        for (int i=0; i<2001; ++i)
        {
          nRx[i] = *(MainWindow::wave + i);
        }
        int i2 = 0;
        for(int i = 0; i<9; i++)    // 拟合R曲线
        {
            k[i] = (R0y[i+1]-R0y[i])/(R0x[i+1]-R0x[i]);
            b[i] = R0y[i] - k[i]*R0x[i];

            while(nRx[i2]<R0y[i])
            {
                nRy[i2] = nRx[i2]*k[i] + b[i];
                i2++;
            }
        }

        // 接受B曲线
        double Bx[2001], By[2001];
        MainWindow::wave = getWavelength();
        MainWindow::data = ReadSpectrum();
        for (int i=0; i<2001; ++i)
        {
            Bx[i] = *(MainWindow::wave + i);
            By[i] = *(MainWindow::data.array + i);
        }

        // 计算C曲线
        for (int i = 0; i<2000; i++)
        {
            newwindow2::Ca[i] = (nRy[i] * MainWindow::time_global)/(By[i] - newwindow2::D);
        }
        newwindow2::Caready = 1; // 设置Ca完成

        std::ofstream Ca_Data;

        Ca_Data.open("Ca_Data.txt");
        for(int i = 0; i<2000 ; i++)
        {
            qreal x = *(MainWindow::wave + i);
            qreal y = Ca[i];
            Ca_Data << "[" << x << ", " << y << "]" << std::endl;
        }
        Ca_Data.close();
    }

}


void newwindow2::on_CancelData_clicked()
{
    close();
}

