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
#include <math.h>

#include <QTextCodec>
#include "newwindow.h"
#include "newwindow2.h"
#include "qcustomplot.h"
#include <QMouseEvent>
#include <QFileDialog>

#include <opencv2\opencv.hpp>
#include <iostream>
#include <vector>
using namespace cv;
using namespace std;
#pragma execution_character_set("utf-8")

bool newwindow2::fileflag = 0;
int newwindow2::D = 1660;

bool newwindow2::Caready = 0;

QCustomPlot *customPlot;
QVector<double> bx(2001), by(2001); //初始化b 标准灯
QVector<double> dx(2001), dy(2001); //初始化d 暗环境
QVector<double> Ca(2001);
QVector<double> R0x(30),R0y(30);
QVector<double> Rsx(2001), Rsy(2001);
int i0;

double newwindow2::ca[2001];    // 传递用的 Ca
double newwindow2::d[2001];     // 传递用的 D

#define hC (1.986445857*pow(10, -10))

Mat polyfit(vector<Point>& in_point, int n);

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

    ui->timeReset->setValidator(new QIntValidator(this));// 限制重设时间为整型

    // 图表初始化
    QCustomPlot *customPlot = ui->chartPlotall;
    // 为坐标轴添加标签
    ui->chartPlotall->xAxis->setLabel(u8"波长(nm)");
    ui->chartPlotall->yAxis->setLabel(u8"强度(Counts)或(J/Counts)");
    // 设置坐标轴的范围及颜色
    ui->chartPlotall->xAxis->setLabelColor(Qt::black);
    ui->chartPlotall->yAxis->setLabelColor(Qt::black);
    ui->chartPlotall->xAxis->setBasePen(QPen(Qt::black));
    ui->chartPlotall->yAxis->setBasePen(QPen(Qt::black));
    ui->chartPlotall->xAxis->setTickPen(QPen(Qt::black));
    ui->chartPlotall->yAxis->setTickPen(QPen(Qt::black));
    ui->chartPlotall->xAxis->setTickLabelColor(Qt::black);
    ui->chartPlotall->yAxis->setTickLabelColor(Qt::black);

    // 图例初始化
    ui->chartPlotall->legend->setVisible(true); // 显示图例
    customPlot->legend->setBrush(QColor(255, 255, 255, 150)); // 图例透明
    ui->chartPlotall->legend->setFont(QFont("HarmonyOS Sans SC"));
    customPlot->legend->setBorderPen(Qt::NoPen);// 隐藏边框
    // 预览初始化
    ui->chartPlotall->setInteraction(QCP::iRangeDrag,true);// 拖拽曲线
    ui->chartPlotall->setInteraction(QCP::iRangeZoom,true);// 鼠标滚轮缩放
    ui->chartPlotall->setCursor(QCursor(Qt::PointingHandCursor));// 鼠标更改为手型
    ui->chartPlotall->setInteraction( QCP::iSelectAxes,true);// 坐标轴可选
    ui->chartPlotall->xAxis->setRange(300, 900);
    ui->chartPlotall->yAxis->setRange(0, 6000);
    onMouseWheel();
    // 曲线初始化
    QPen pen;
    // Rs 曲线
    customPlot->addGraph();
    pen.setWidth(4);
    pen.setColor(Qt::yellow);
    ui->chartPlotall->graph(0)->setPen(pen);
    ui->chartPlotall->graph(0)->setName(u8"Rs线性拟合曲线");// 设置图例名称
    // B0 曲线
    customPlot->addGraph();
    pen.setWidth(4);
    pen.setColor(Qt::lightGray);
    customPlot->graph(1)->setPen(pen);
    ui->chartPlotall->graph(1)->setName(u8"B0标准灯光谱");// 设置图例名称
    // D0 曲线
    customPlot->addGraph();
    pen.setWidth(4);
    pen.setColor(Qt::darkGray);
    customPlot->graph(2)->setPen(pen);
    ui->chartPlotall->graph(2)->setName(u8"D0无光背景谱");// 设置图例名称
    // Ca 曲线
    customPlot->addGraph();
    pen.setWidth(4);
    pen.setColor(Qt::red);
    customPlot->graph(3)->setPen(pen);
    ui->chartPlotall->graph(3)->setName(u8"Ca校准曲线");// 设置图例名称

}

newwindow2::~newwindow2()
{
    delete ui;
}

// 随意放大缩小函数
void newwindow2::onMouseWheel()
{
    if (ui->chartPlotall->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
        ui->chartPlotall->axisRect()->setRangeZoom(ui->chartPlotall->xAxis->orientation());
    else if (ui->chartPlotall->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
        ui->chartPlotall->axisRect()->setRangeZoom(ui->chartPlotall->yAxis->orientation());
    else
        ui->chartPlotall->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}

// 确定 接受Ca 关闭窗口
void newwindow2::on_AcceptData_clicked()
{
    // 接受输入的数据
    if (newwindow2::Caready == 1)
    {
        for(int i = 0; i < 2000; i++)
        {
            newwindow2::ca[i] = Ca[i];
            newwindow2::d[i] = dy[i];
        }
        QMessageBox::information(this,"Success","校准参数已录入");
        close();
    }
    else
    {
        QMessageBox::information(this,"工作还没有做完，还不能休息","校准步骤未完成，退出请点击取消");
    }
}

// 生成Ca
void newwindow2::on_buttonCaOutput_clicked()
{
    // 接受输入的数据
    if (fileflag==0) // 没有输入数据文件的时候
    {
        // Rs 光功率
        //double R0x[11], R0y[11];
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

        // 光功率转换成为光子数
        for(int i = 1; i<10; i++)
        {
            R0y[i] = R0y[i] * R0x[i] * pow(10,10)/1.986445857;
        }

        // Rs 拟合
        double k[10], b[10];
        QVector<double> Rsx(2001), Rsy(2001);

        for (int i=0; i<2001; ++i) // Rs 的x轴为固定的波长
        {
          Rsx[i] = *(MainWindow::wave + i);
        }

        int p = 0;
        for(int i = 0; i<10; i++)    // 线型拟合 Rs 曲线
        {
            k[i] = (R0y[i+1]-R0y[i])/(R0x[i+1]-R0x[i]);
            b[i] = R0y[i] - k[i]*R0x[i];

            while(Rsx[p]<R0x[i])  // 当Rs 的x值在拟合范围区间内，求出y的值
            {
                Rsy[p] = Rsx[p]*k[i] + b[i];
                p++;
            }
        }
        // Rs 绘图
        ui->chartPlotall->graph(0)->setData(Rsx, Rsy);
        ui->chartPlotall->graph(0)->rescaleAxes(); // 自适应坐标轴范围

        // 计算C曲线
        for (int i = 0; i<2000; i++)
        {
            Ca[i] = Rsy[i]/(by[i] - dy[i]);
        }
        // Ca绘图
        ui->chartPlotall->graph(3)->setData(bx, Ca);
        ui->chartPlotall->graph(3)->rescaleAxes(); // 自适应坐标轴范围
        // 导出文件
        std::ofstream Ca_Data;
        Ca_Data.open("Ca_Data.txt");
        for (int i = 0; i<2000 ; i++)
        {
            qreal x = *(MainWindow::wave + i);
            qreal y = Ca[i];
            Ca_Data << "[" << x << ", " << y << "]" << std::endl;
        }
        Ca_Data.close();
        std::ofstream Ca_read;
        Ca_read.open("ca.txt");
        for (int i = 0; i<2000; i++)
        {
            qreal x = *(MainWindow::wave + i);
            qreal y = Ca[i];
            Ca_Data  << x << "    " << y << std::endl;
        }
        Ca_read.close();
        newwindow2::Caready = 1; // 设置Ca完成
    }
    else // 从文件读取数据
    {
        // 计算C曲线
        for (int i = 0; i<2000; i++)
        {
            Ca[i] = Rsy[i]*MainWindow::time_global / (by[i] - dy[i]);
        }
        // Ca绘图
        ui->chartPlotall->graph(3)->setData(Rsx, Ca);
        ui->chartPlotall->graph(3)->rescaleAxes(); // 自适应坐标轴范围

        // 导出文件
        std::ofstream Ca_Data;
        Ca_Data.open("Ca_Data.txt");
        for(int i = 0; i<2000 ; i++)
        {
            qreal x = *(MainWindow::wave + i);
            qreal y = Ca[i];
            Ca_Data << "[" << x << ", " << y << "]" << std::endl;
        }
        Ca_Data.close();

        std::ofstream Ca_read;
        Ca_read.open("ca.txt");
        for (int i = 0; i<2000; i++)
        {
            qreal x = *(MainWindow::wave + i);
            qreal y = Ca[i];
            Ca_read  << x << "    " << y << std::endl;
        }
        Ca_read.close();
        newwindow2::Caready = 1; // 设置Ca完成
    }

}

// 不接收数据关闭窗口
void newwindow2::on_CancelData_clicked()
{
    newwindow2::Caready = 0;    // 标定标志位置零
    newwindow2:: fileflag = 0;  // 文件数据标志位置零
    close();                    // 关闭窗口
}

// 测量暗背景 D0
void newwindow2::on_buttonDark_clicked()
{
    QMessageBox::information(this,"暗背景","请确定正在测量暗背景环境");

    setIntegrationTime(10);
    setAverage(1);
    int flag = getSpectrum(10);
    if(flag == 1)
    {
        Sleep(1000);
    }
    else
    {
        Sleep(2000);
    }
    Sleep(2000);
    MainWindow::wave = getWavelength();
    MainWindow::data = ReadSpectrum();
    for (int i=0; i<2001; ++i)
    {
        dx[i] = *(MainWindow::wave + i);
        dy[i] = *(MainWindow::data.array + i);
    }
    // D0 绘图
    ui->chartPlotall->graph(2)->setData(dx, dy); // 绘图
    ui->chartPlotall->replot();
    ui->chartPlotall->graph(2)->rescaleAxes(); // 自适应坐标轴范围
}

//测量标准灯 B0
void newwindow2::on_buttonLight_clicked()
{
    QMessageBox::information(this,"标准灯","请确定正在测量标准灯，且已预热完成");

    setIntegrationTime(10);
    setAverage(1);
    int flag = getSpectrum(10);
    if(flag == 1)
    {
        Sleep(1000);
    }
    else
    {
        Sleep(2000);
    }
    MainWindow::wave = getWavelength();
    MainWindow::data = ReadSpectrum();
    for (int i=0; i<2001; ++i)
    {
        bx[i] = *(MainWindow::wave + i);
        by[i] = *(MainWindow::data.array + i);
    }
    // B0 绘图
    ui->chartPlotall->graph(1)->setData(bx, by); // 绘图
    ui->chartPlotall->replot();
    ui->chartPlotall->graph(1)->rescaleAxes(); // 自适应坐标轴范围
}

// 导入数据
void newwindow2::on_buttonInputStandard_clicked()
{
    newwindow2::fileflag = 1;

    QString fileName = QFileDialog::getOpenFileName(this,tr("选择导入数据⽂件"),"",tr("TXT(*.txt)"));
    std::string str = fileName.toStdString();
    const char *filename = str.c_str();
    std::ifstream in(filename, std::ios::in);
    if (!in.is_open())
    {
        QMessageBox::information(this,"文件不存在","打开文件名称为'Rs.txt'");
        exit(0);
    }

    // 数据文件读取导入数组
    i0 = 0;
    while (!in.eof() && i0 < 100)
    {
        in >> R0x[i0] >> R0y[i0];
        i0++;
    }

    // 分段线性插值
    double k[100], b[100];
    for (int i = 0;i<i0-1; i++)
    {
        k[i] = (R0y[i+1] - R0y[i])/(R0x[i+1] - R0x[i]);
        b[i] = R0y[i] - k[i]*R0x[i];
    }
    int p = 0;
    MainWindow::wave = getWavelength();
    for (int i=0; i<2001; ++i) // Rs 的x轴为固定的波长
    {
      Rsx[i] = *(MainWindow::wave + i);
    }
    for(int i = 0; i<26; i++)
    {
        while(Rsx[p]<R0x[i+1])              // 当Rs 的x值在拟合范围区间内，求出y的值
        {
            Rsy[p] = Rsx[p]*k[i] + b[i];
            p++;
        }
    }
    // Rs 绘图
    ui->chartPlotall->graph(0)->setData(Rsx, Rsy);
    ui->chartPlotall->graph(0)->rescaleAxes(); // 自适应坐标轴范围
}


/* 多项式拟合曲线方法
Mat polyfit(vector<Point>& in_point, int n)
{
    int size = in_point.size();
    //所求未知数个数
    int x_num = n + 1;
    //构造矩阵U和Y
    Mat mat_u(size, x_num, CV_64F);
    Mat mat_y(size, 1, CV_64F);

    for (int i = 0; i < mat_u.rows; ++i)
        for (int j = 0; j < mat_u.cols; ++j)
        {
            mat_u.at<double>(i, j) = pow(in_point[i].x, j);
        }

    for (int i = 0; i < mat_y.rows; ++i)
    {
        mat_y.at<double>(i, 0) = in_point[i].y;
    }

    //矩阵运算，获得系数矩阵K
    Mat mat_k(x_num, 1, CV_64F);
    mat_k = (mat_u.t()*mat_u).inv()*mat_u.t()*mat_y;
    cout << mat_k << endl;
    return mat_k;
}
*/



// 重设积分时间
void newwindow2::on_buttonTimeReset_clicked()
{
    MainWindow::time_global = ui->timeReset->text().toInt();
    QMessageBox::information(this,"重设时间成功","该时间也会影响主界面的积分时间，如需改变，请在主界面重新设置");
}


void newwindow2::on_pushButton_2_clicked()
{

    QString fileName = QFileDialog::getOpenFileName(this,tr("导入数据文件"),"",tr("TXT(*.txt)"));
    std::string str = fileName.toStdString();
    const char *filename = str.c_str();
    std::ifstream in(filename, std::ios::in);
    if (!in.is_open())
    {
        QMessageBox::information(this,"文件不存在","没有导入文件~");
    }
    else
    {
        //将数据文件数据存入数组
        int i = 0;
        QVector<double> x(2000), y(2000);
        while (!in.eof() && i < 2000)
        {
            in >> x[i] >> y[i] ;
            i++;
        }
        ui->chartPlotall->graph(3)->setData(x, y);
    }
    ui->chartPlotall->replot();
    ui->chartPlotall->rescaleAxes();
}

