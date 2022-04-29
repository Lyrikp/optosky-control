#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QValueAxis>
#include "newwindow.h"

#include "DriverType.h"
#include "Driver_app.h"

#include <windows.h>
#include <iostream>
#include<fstream>

#define TEXT_COLOR_RED(STRING) "<font color=red>" STRING "</font>" "<font color=black> </font>"
#define TEXT_COLOR_GREEN(STRING) "<font color=green>" STRING "</font>" "<font color=black> </font>"
#define TEXT_COLOR_YELLOW(STRING) "<font color=yellow>" STRING "</font>" "<font color=black> </font>"

int MainWindow::time_global;
int MainWindow::average_global;
int MainWindow::dataflag = 0;
Spectrumsp MainWindow::data;
float* MainWindow::wave;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 两个数字验证器，限制输入数字
    ui->setTime->setValidator(new QDoubleValidator(this));
    ui->setAverage->setValidator(new QDoubleValidator(this));

    connect(ui->setTime, SIGNAL(textChanged(QString)),
            this, SLOT(enableButton()));
    connect(ui->setAverage, SIGNAL(textChanged(QString)),
            this, SLOT(enableButton()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 设定时间和次数后光谱可用
void MainWindow::enableButton(void)
{
    bool bX0k, bY0k;
    ui->setTime->text().toDouble(&bX0k);
    ui->setAverage->text().toDouble(&bY0k);
    ui->buttonSpectrum->setEnabled(bX0k && bY0k);
    ui->buttonDarkSp->setEnabled(bX0k && bY0k);
}

// 开始连接
void MainWindow::on_buttonLink_clicked()
{
    bool flag_0;
    flag_0 = openSpectraMeter();
    QString log = "Link successful.";
    if (flag_0==true)
    {
        ui->logShow->clearHistory();
        ui->logShow->append(log);
        ErrorFlag flag_1 = initialize();
        Sleep(500);
        log = "Initilaizing...";
        ui->logShow->append(log);
        if (flag_1 == INIT_SUCCESS)
            {
                ui->logShow->append(TEXT_COLOR_GREEN("Done."));
                ui->logShow->append("Please continue setting.");
                ui->logShow->append(" ");
            }
            else
            {
                log = "Init Failed";
                ui->logShow->append(TEXT_COLOR_RED("FATAL ") + log);
            }
    }
    else
    {
        log = "No device linked.";
        ui->logShow->append(TEXT_COLOR_RED("FATAL ") + log);
    }

}

// 断开连接
void MainWindow::on_buttonOut_clicked()
{
    closeSpectraMeter();
    ui->logShow->clear();
    Sleep(500);
    ui->logShow->append("Have a nice day.");
    Sleep(3000);
    ui->logShow->clear();
}


// 连接的信息
void MainWindow::on_buttonVice_clicked()
{
    spectrum_device_info ATP5020P;
    findSpectraMeters(ATP5020P);
    QString num = QString::number(ATP5020P.length, 10);
    ui->logShow->append(num + " device ready.");
    ui->logShow->append(" ");
}



// 设备信息
void MainWindow::on_buttonInfo_clicked()
{
    QString min_integraltime = QString::number(getIntegrationTimeMinimum(), 10);
    QString max_integraltime = QString::number(getIntegrationTimeMaximum(), 10);
    QString integraltime = QString::number(getActualIntegrationTime(), 10);
    ui->logShow->append("--------device information---------");
    ui->logShow->append(TEXT_COLOR_RED("The Range of integraltime:") +
                min_integraltime + "~" + max_integraltime
                );
    ui->logShow->append("Now integraltime: " + integraltime + "ms");
}


// 设置积分时间
void MainWindow::on_setTime_editingFinished()
{
    int settime = ui->setTime->text().toInt();
    setIntegrationTime(settime);
    QString time = QString::number(settime, 10);
    ui->logShow->append("--------set Interationtime--------");
    ui->logShow->append("Set time: " + time + "ms");
    MainWindow::time_global = settime;
}


// 设置平均采样次数
void MainWindow::on_setAverage_editingFinished()
{
    int average = ui->setAverage->text().toInt();
    QString average1 = QString::number(average, 10);
    ui->logShow->append("--------set Averagetime--------");
    ui->logShow->append("Set average number: " + average1);
    MainWindow::average_global = average;
}

void MainWindow::on_buttonSpectrum_clicked()
{
    // 图表初始化
    QChart *chart = new QChart();
    chart->setTitle("光谱测量");
    ui->chartView->setChart(chart);
    ui->chartView->setRenderHint(QPainter::Antialiasing);

    QLineSeries *series0 = new QLineSeries;
    curSeries = series0;

    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(2);
    pen.setColor(Qt::blue);
    series0->setPen(pen);

    chart->addSeries(series0);

    QValueAxis *axisX = new QValueAxis;
    QValueAxis *axisY = new QValueAxis;
    curAxis = axisX;

    axisX->setRange(300,900);
    axisX->setTickCount(10);
    axisX->setTitleText("波长/nm");

    axisY->setRange(0,60000);
    axisY->setTickCount(10);
    axisY->setTitleText("强度(Counts)");

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series0->attachAxis(axisX);
    series0->attachAxis(axisY);

    chart->legend()->hide();

    series0->clear();

    // 获取数据
    setIntegrationTime(MainWindow::time_global);
    setAverage(MainWindow::average_global);
    int flag = getSpectrum(MainWindow::time_global);
    int count = 0;
    while (flag != 1 )   // 等待数据获取完成
    {
        count++;
        Sleep(500);
        if (count>=10)  // 等待大于5s后跳出报错
        {
            break;
        }
    }
    Sleep(1000);

    // 输出日志
    QString log;
    if (flag == 1)
        {
            flag = getSpectrumDataReadyFlag();
            if (flag == SPECTRUMDATA_READY)
            {
                log = "Get Spectrum.";
                ui->logShow->append("---------------------");

                ui->logShow->append(TEXT_COLOR_GREEN("Done ") + log);
                ui->logShow->append("Processing...");
                ui->logShow->append("---------------------");
            }
            else
            {
                log = "Data isn't ready.";
                ui->logShow->append("---------------------");
                ui->logShow->append(TEXT_COLOR_RED("Failed ") + log);
                ui->logShow->append("---------------------");
            }
        }
    else
    {
        log = "Haven't got Spectrum";
        ui->logShow->append(TEXT_COLOR_RED("Failed ") + log);
        ui->logShow->append("Please check light source.");
    }

    // 获得横纵坐标数据
    MainWindow::wave = getWavelength();
    MainWindow::data = ReadSpectrum();
    int* intensity = data.array;
    QList<QPointF> newPoints;
    for(int i = 0; i<2000 ; i++)
    {
        QPointF point;
        qreal x = *(wave + i);
        qreal y = *(intensity + i);
        point.setX(x);
        point.setY(y);
        newPoints.append(point);
    }
    series0->replace(newPoints);    // 绘图

    MainWindow::dataflag = 1;

}

// 暗背景模式
void MainWindow::on_buttonDarkSp_clicked()
{
    // 图表初始化
    QChart *chart = new QChart();
    chart->setTitle("光谱测量（暗背景开启）");
    ui->chartView->setChart(chart);
    ui->chartView->setRenderHint(QPainter::Antialiasing);

    QLineSeries *series0 = new QLineSeries;
    curSeries = series0;

    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(2);
    pen.setColor(Qt::blue);
    series0->setPen(pen);

    chart->addSeries(series0);

    QValueAxis *axisX = new QValueAxis;
    QValueAxis *axisY = new QValueAxis;
    curAxis = axisX;

    axisX->setRange(300,900);
    axisX->setTickCount(10);
    axisX->setTitleText("波长/nm");

    axisY->setRange(0,60000);
    axisY->setTickCount(10);
    axisY->setTitleText("强度(Counts)");

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series0->attachAxis(axisX);
    series0->attachAxis(axisY);

    chart->legend()->hide();

    series0->clear();



    // 获取数据
    setIntegrationTime(MainWindow::time_global);
    setAverage(MainWindow::average_global);
    int flag = getDarkSpectrum(MainWindow::time_global);
    int count = 0;
    while (flag != 1)   // 等待数据获取完成
    {
        count++;
        Sleep(500);
        if (count>=10)  // 等待大于5s后跳出报错
        {
            break;
        }
    }
    // 输出日志
    QString log;
    if (flag == 1)
        {
            flag = getSpectrumDataReadyFlag();
            if (flag == SPECTRUMDATA_READY)
            {
                log = "Get Spectrum.";
                ui->logShow->append("---------------------");

                ui->logShow->append(TEXT_COLOR_GREEN("Done ") + log);
                ui->logShow->append("Processing in dark mode...");
                ui->logShow->append("---------------------");
            }
            else
            {
                log = "Data isn't ready.";
                ui->logShow->append("---------------------");
                ui->logShow->append(TEXT_COLOR_RED("Failed ") + log);
                ui->logShow->append("---------------------");
            }
        }
    else
    {
        log = "Haven't got Spectrum";
        ui->logShow->append(TEXT_COLOR_RED("Failed ") + log);
        ui->logShow->append("Please check light source.");
    }

    MainWindow::wave = getWavelength();
    MainWindow::data = ReadSpectrum();
    int* intensity = data.array;
    QList<QPointF> newPoints;
    for(int i = 0; i<2000 ; i++)
    {
        QPointF point;
        qreal x = *(wave + i);
        qreal y = *(intensity + i);
        point.setX(x);
        point.setY(y);
        newPoints.append(point);
    }
    series0->replace(newPoints);

}

// 光谱图表部分
// 放大
void MainWindow::on_buttonZoomIn_clicked()
{
    ui->chartView->chart()->zoom(1.2);
}

// 缩小
void MainWindow::on_buttonZoomOut_clicked()
{
    ui->chartView->chart()->zoom(0.8);
}

// 复位
void MainWindow::on_butttonReset_clicked()
{
    ui->chartView->chart()->zoomReset();
}




// 绘图区域复位
void MainWindow::on_buttonClean_clicked()
{
    QChart *chart = new QChart();
    chart->setTitle("等待测量");
    ui->chartView->setChart(chart);
    ui->chartView->setRenderHint(QPainter::Antialiasing);

    QLineSeries *series0 = new QLineSeries;
    curSeries = series0;

    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(2);
    pen.setColor(Qt::blue);
    series0->setPen(pen);

    chart->addSeries(series0);

    QValueAxis *axisX = new QValueAxis;
    QValueAxis *axisY = new QValueAxis;
    curAxis = axisX;

    axisX->setRange(300,900);
    axisX->setTickCount(10);
    axisX->setTitleText("波长/nm");

    axisY->setRange(0,60000);
    axisY->setTickCount(10);
    axisY->setTitleText("强度(Counts)");

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series0->attachAxis(axisX);
    series0->attachAxis(axisY);

    chart->legend()->hide();

    series0->clear();
}

// 清空日志
void MainWindow::on_buttonCleanlog_clicked()
{
    ui->logShow->clear();
}

// 菜单 开始连接
void MainWindow::on_actionLink_device_triggered()
{
    bool flag_0;
    flag_0 = openSpectraMeter();
    QString log = "Link successful.";
    if (flag_0==true)
    {
        ui->logShow->clearHistory();
        ui->logShow->append(log);
        ErrorFlag flag_1 = initialize();
        Sleep(500);
        log = "Initilaizing...";
        ui->logShow->append(log);
        if (flag_1 == INIT_SUCCESS)
            {
                ui->logShow->append(TEXT_COLOR_GREEN("Done."));
                ui->logShow->append("Please continue setting.");
                ui->logShow->append(" ");
            }
            else
            {
                log = "Init Failed";
                ui->logShow->append(TEXT_COLOR_RED("FATAL ") + log);
            }
    }
    else
    {
        log = "No device linked.";
        ui->logShow->append(TEXT_COLOR_RED("FATAL ") + log);
    }
}

// 菜单 断开连接
void MainWindow::on_actionStop_Link_triggered()
{
    closeSpectraMeter();
    ui->logShow->clear();
    Sleep(500);
    ui->logShow->append("Have a nice day.");
    Sleep(3000);
    ui->logShow->clear();
}

// 菜单 关闭所有窗口
void MainWindow::on_actionQuit_triggered()
{
    close();
}



// 菜单 原始数据 输出txt
void MainWindow::on_actionOrigin_Data_triggered()
{
    QChart *chart = new QChart();
    chart->setTitle("光谱测量");
    ui->chartView->setChart(chart);
    ui->chartView->setRenderHint(QPainter::Antialiasing);

    QLineSeries *series0 = new QLineSeries;
    curSeries = series0;

    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(2);
    pen.setColor(Qt::blue);
    series0->setPen(pen);

    chart->addSeries(series0);

    QValueAxis *axisX = new QValueAxis;
    QValueAxis *axisY = new QValueAxis;
    curAxis = axisX;

    axisX->setRange(300,900);
    axisX->setTickCount(10);
    axisX->setTitleText("波长/nm");

    axisY->setRange(0,60000);
    axisY->setTickCount(10);
    axisY->setTitleText("强度(Counts)");

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series0->attachAxis(axisX);
    series0->attachAxis(axisY);

    chart->legend()->hide();

    series0->clear();

    // 获取数据
    setIntegrationTime(MainWindow::time_global);
    setAverage(MainWindow::average_global);
    int flag = getSpectrum(MainWindow::time_global);
    int count = 0;
    while (flag != 1)   // 等待数据获取完成
    {
        count++;
        Sleep(500);
        if (count>=10)  // 等待大于5s后跳出报错
        {
            break;
        }
    }

    if (flag == 1)
    {
        flag = getSpectrumDataReadyFlag();
        if (flag == SPECTRUMDATA_READY)
        {
            ui->logShow->append(TEXT_COLOR_YELLOW("Processing Original Data."));
            // 获得横纵坐标数据
            std::ofstream origindata;
            MainWindow::wave = getWavelength();
            MainWindow::data = ReadSpectrum();
            int* intensity = data.array;
            QList<QPointF> newPoints;
            origindata.open("data_origin.txt");
            for(int i = 0; i<2000 ; i++)
            {
                QPointF point;
                qreal x = *(wave + i);
                qreal y = *(intensity + i);
                origindata << "[" << x << ", " << y << "]" << std::endl;
                point.setX(x);
                point.setY(y);
                newPoints.append(point);
            }
            origindata.close();
            series0->replace(newPoints);
            MainWindow::dataflag = 1;   // 原始数据设为存在
        }
        else
        {
            ui->logShow->append(TEXT_COLOR_RED("NO DATA."));
        }
    }

}

void MainWindow::on_actionData_Process_triggered()
{
    if (MainWindow::dataflag != 1)
    {
        QString log = "System never accept original data, please make sure clicked 'Original Data(light) first.'";
        ui->logShow->append(TEXT_COLOR_RED("FATAL") + log);
    }
    else
    {
        newWindow *configWindow = new newWindow;
        configWindow->show();
        MainWindow::on_buttonSpectrum_clicked();
    }

}


// 画图函数
void MainWindow::on_buttonDrawGraph_clicked()
{
    if (newWindow::changeflag == 1)
    {
        ui->logShow->append("---------------------");
        QString log = "Data processed success.";
        ui->logShow->append(TEXT_COLOR_GREEN("Done ") + log);
    }
    else
    {
        ui->logShow->append("---------------------");
        QString log = "Nothing changed.";
        ui->logShow->append(TEXT_COLOR_GREEN("Warning ") + log);
    }

    QChart *chart = new QChart();
    chart->setTitle("处理光谱");
    ui->chartView->setChart(chart);
    ui->chartView->setRenderHint(QPainter::Antialiasing);

    QLineSeries *series0 = new QLineSeries;
    curSeries = series0;

    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(2);
    pen.setColor(Qt::blue);
    series0->setPen(pen);

    chart->addSeries(series0);

    QValueAxis *axisX = new QValueAxis;
    QValueAxis *axisY = new QValueAxis;
    curAxis = axisX;

    axisX->setRange(300,900);
    axisX->setTickCount(10);
    axisX->setTitleText("波长/nm");

    axisY->setRange(0,60000);
    axisY->setTickCount(10);
    axisY->setTitleText("强度(Counts)");

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series0->attachAxis(axisX);
    series0->attachAxis(axisY);

    chart->legend()->hide();

    series0->clear();

    wave = getWavelength();
    float* intensity = dataProcess(MainWindow::data.array, newWindow::smoothLevel, newWindow::deductflag, newWindow::nolinear, newWindow::waveshape);
    QList<QPointF> newPoints;
    for(int i = 0; i<2000 ; i++)
    {
        QPointF point;
        qreal x = *(wave + i);
        qreal y = *(intensity + i);
        point.setX(x);
        point.setY(y);
        newPoints.append(point);
    }
    series0->replace(newPoints);    // 绘图
    MainWindow::dataflag = 0;
}

// 导出数据
void MainWindow::on_buttonDataOut_clicked()
{
    std::ofstream origindata;
    MainWindow::wave = getWavelength();
    MainWindow::data = ReadSpectrum();

    QList<QPointF> newPoints;
    origindata.open("data_origin.txt");
    for(int i = 0; i<2000 ; i++)
    {
        QPointF point;
        qreal x = *(MainWindow::wave + i);
        qreal y = *(data.array + i);
        origindata << "[" << x << ", " << y << "]" << std::endl;
        point.setX(x);
        point.setY(y);
        newPoints.append(point);
    }
    origindata.close();
}

// 系统校准
void MainWindow::on_buttonSystemCheck_clicked()
{
    ui->logShow->append(TEXT_COLOR_YELLOW("Please prepare standard light..."));
    Sleep(5000);
    ui->logShow->append(" ");
    ui->logShow->append(TEXT_COLOR_GREEN("Start."));

    ErrorFlag flag_1 = initialize();
    int count = 0;

    while(flag_1 != INIT_SUCCESS)
    {
        Sleep(100);
        count++;
        if (count>10)
        {
            QString log = "initiated failed.";
            ui->logShow->append(TEXT_COLOR_RED("Failed ") + log);
            break;
        }
    }

    QChart *chart = new QChart();
    chart->setTitle("校准光谱");
    ui->chartView->setChart(chart);
    ui->chartView->setRenderHint(QPainter::Antialiasing);

    QLineSeries *series0 = new QLineSeries;
    curSeries = series0;

    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(2);
    pen.setColor(Qt::blue);
    series0->setPen(pen);

    chart->addSeries(series0);

    QValueAxis *axisX = new QValueAxis;
    QValueAxis *axisY = new QValueAxis;
    curAxis = axisX;

    axisX->setRange(300,900);
    axisX->setTickCount(10);
    axisX->setTitleText("波长/nm");

    axisY->setRange(0,60000);
    axisY->setTickCount(10);
    axisY->setTitleText("强度(Counts)");

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series0->attachAxis(axisX);
    series0->attachAxis(axisY);

    chart->legend()->hide();

    series0->clear();

    // 获取数据
    setIntegrationTime(10);
    setAverage(5);
    int flag = getSpectrum(10);
    count = 0;
    while (flag != 1 )   // 等待数据获取完成
    {
        count++;
        Sleep(500);
        if (count>=10)  // 等待大于5s后跳出报错
        {
            break;
        }
    }
    Sleep(1000);

    // 获得横纵坐标数据
    float* checkwave = getWavelength();
    Spectrumsp checkdata = ReadSpectrum();
    int* intensity = checkdata.array;
    QList<QPointF> newPoints;
    for(int i = 0; i<2000 ; i++)
    {
        QPointF point;
        qreal x = *(checkwave + i);
        qreal y = *(intensity + i);
        point.setX(x);
        point.setY(y);
        newPoints.append(point);
    }
    series0->replace(newPoints);    // 绘图

    MainWindow::dataflag = 1;
    std::ofstream standardDatafile;
    standardDatafile.open("HL030410015.lmp");

    float* standardwave;
    Spectrumsp standarddata;
    double x = 0, y = 0;
    for (int i = 0; !standardDatafile.eof();i++)
    {
        standardDatafile >> *(standardwave +i ) >> *(standarddata.array + i);


    }

}

