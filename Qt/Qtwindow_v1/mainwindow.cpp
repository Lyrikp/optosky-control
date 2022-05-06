#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QValueAxis>
#include <QChartView>
#include <QTextCodec>
#include "newwindow.h"
#include "newwindow2.h"
#include "qcustomplot.h"
#include <QMouseEvent>

#include "DriverType.h"
#include "Driver_app.h"

#include <windows.h>
#include <iostream>
#include<fstream>
#pragma execution_character_set("utf-8")

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

    connect(ui->chartPlot, &QCustomPlot::mouseWheel, this, &MainWindow::onMouseWheel);
    ui->labelTitle->setText(u8"休息中......");
    ui->chartPlot->setBackground(QPixmap("./catnap.png"));                  //设置背景为透明色
    ui->chartPlot->setBackgroundScaledMode(Qt::KeepAspectRatio);

    // 游标
    // connect(ui->chartPlot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mouseMove1(QMouseEvent*)));

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

// 随意放大缩小函数
void MainWindow::onMouseWheel()
{
    if (ui->chartPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
        ui->chartPlot->axisRect()->setRangeZoom(ui->chartPlot->xAxis->orientation());
    else if (ui->chartPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
        ui->chartPlot->axisRect()->setRangeZoom(ui->chartPlot->yAxis->orientation());
    else
        ui->chartPlot->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}

/* 游标 过于浪费资源，容易闪退
void MainWindow::mouseMove1(QMouseEvent *e)
{
    //获得鼠标位置处对应的横坐标数据x
    double x = ui->chartPlot->xAxis->pixelToCoord(e->pos().x());
    double y = ui->chartPlot->yAxis->pixelToCoord(e->pos().y());
    double xValue, yValue;

    xValue = x;
    yValue = y;

    tracer->position->setCoords(xValue, yValue);//设置游标位置
    tracerLabel->setText(QString(u8"波长 = %1 \n光强 = %2").arg(xValue).arg(yValue));//设置游标说明内容
    ui->chartPlot->replot();//绘制器一定要重绘，否则看不到游标位置更新情况
}
*/

// 开始连接
void MainWindow::on_buttonLink_clicked()
{
    bool flag_0;
    flag_0 = openSpectraMeter();
    QString log = "Link successful.";
    ui->labelTitle->setText(u8"设备已上线");

    QCustomPlot *customPlot = ui->chartPlot;
    ui->chartPlot->clearGraphs();   // 清除上一次数据
    ui->chartPlot->clearItems();
    ui->chartPlot->clearPlottables();
    ui->chartPlot->clearFocus();
    ui->chartPlot->clearMask();
    customPlot->addGraph();
    ui->chartPlot->setBackground(QPixmap("./light.jpg"));
    ui->chartPlot->setBackgroundScaledMode(Qt::IgnoreAspectRatio);
    ui->chartPlot->replot();

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
                ui->logShow->append(u8"继续设定，未设定将按上次设定数据处理");
                ui->logShow->append(u8"设定前请先检查设备信息");
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
    closeSpectraMeter();// 关闭设备

    QCustomPlot *customPlot = ui->chartPlot; // 初始化绘图区
    ui->chartPlot->clearGraphs();
    ui->chartPlot->clearItems();
    ui->chartPlot->clearPlottables();
    ui->chartPlot->clearFocus();
    ui->chartPlot->clearMask();
    customPlot->addGraph();
    ui->chartPlot->setBackground(QPixmap("./catnap.png"));
    ui->chartPlot->setBackgroundScaledMode(Qt::KeepAspectRatio);
    ui->chartPlot->replot();

    ui->logShow->clear(); // 清空日志
    Sleep(500);
    ui->logShow->append("Have a nice day.");

}


// 连接的信息
void MainWindow::on_buttonVice_clicked()
{
    spectrum_device_info ATP5020P;
    findSpectraMeters(ATP5020P);
    QString num = QString::number(ATP5020P.length, 10);
    ui->logShow->append(num + u8" 个设备已上线");
    ui->logShow->append(" ");
}



// 设备信息
void MainWindow::on_buttonInfo_clicked()
{
    QString min_integraltime = QString::number(getIntegrationTimeMinimum(), 10);
    QString max_integraltime = QString::number(getIntegrationTimeMaximum(), 10);
    QString integraltime = QString::number(getActualIntegrationTime(), 10);
    ui->logShow->append(u8"------设备信息-------");
    ui->logShow->append(TEXT_COLOR_RED(u8"积分时间范围: ") +
                min_integraltime + "~" + max_integraltime
                );
    ui->logShow->append("当前设定积分时间: " + integraltime + "ms");
}


// 设置积分时间
void MainWindow::on_setTime_editingFinished()
{
    int settime = ui->setTime->text().toInt();
    setIntegrationTime(settime);
    QString time = QString::number(settime, 10);
    ui->logShow->append("----设定积分时间----");
    ui->logShow->append("积分时间: " + time + "ms");
    MainWindow::time_global = settime;
}


// 设置平均采样次数
void MainWindow::on_setAverage_editingFinished()
{
    int average = ui->setAverage->text().toInt();
    QString average1 = QString::number(average, 10);
    ui->logShow->append("----设定平均采样次数----");
    ui->logShow->append("设定平均采样次数: " + average1);
    MainWindow::average_global = average;
}

// 一般绘图
void MainWindow::on_buttonSpectrum_clicked()
{
    // 图表初始化
    QCustomPlot *customPlot = ui->chartPlot;
    ui->chartPlot->clearGraphs();   // 清除上一次数据
    ui->chartPlot->clearItems();
    ui->chartPlot->clearPlottables();
    ui->chartPlot->clearFocus();
    ui->chartPlot->clearMask();
    customPlot->addGraph();
    QPen pen;
    pen.setWidth(4);//曲线的粗细
    pen.setColor(Qt::lightGray);
    customPlot->graph(0)->setPen(pen); // 曲线的颜色
    customPlot->graph(0)->setBrush(QBrush(QColor(116, 120, 122, 20))); // 曲线与X轴包围区的颜色
    ui->chartPlot->setBackground(QPixmap("./light.jpg"));
    ui->chartPlot->setBackgroundScaledMode(Qt::IgnoreAspectRatio);

    // 标题初始化
    ui->labelTitle->setText("波长-强度光谱图像绘制");
    /* 旧初始化 会产生重复标题渲染问题
    customPlot->plotLayout()->insertRow(0);
    QCPTextElement *H_title = new QCPTextElement(customPlot, "光谱测量", QFont("HarmonyOS Sans SC", 12, QFont::Bold));
    customPlot->plotLayout()->addElement(0, 0, H_title);
    */
    // 为坐标轴添加标签
    ui->chartPlot->xAxis->setLabel(u8"波长/nm");
    ui->chartPlot->yAxis->setLabel(u8"强度(Counts)");
    // 设置坐标轴的范围及颜色
    ui->chartPlot->xAxis->setRange(300, 900);
    ui->chartPlot->yAxis->setRange(0, 6000);
    ui->chartPlot->xAxis->setLabelColor(Qt::black);
    ui->chartPlot->yAxis->setLabelColor(Qt::black);
    ui->chartPlot->xAxis->setBasePen(QPen(Qt::black));
    ui->chartPlot->yAxis->setBasePen(QPen(Qt::black));
    ui->chartPlot->xAxis->setTickPen(QPen(Qt::black));
    ui->chartPlot->yAxis->setTickPen(QPen(Qt::black));
    ui->chartPlot->xAxis->setTickLabelColor(Qt::black);
    ui->chartPlot->yAxis->setTickLabelColor(Qt::black);

    ui->chartPlot->graph(0)->rescaleAxes();

    ui->chartPlot->legend->setVisible(true); // 显示图例
    customPlot->legend->setBrush(QColor(255, 255, 255, 150)); // 图例透明
    ui->chartPlot->legend->setFont(QFont("HarmonyOS Sans SC"));
    customPlot->legend->setBorderPen(Qt::NoPen);// 隐藏边框
    customPlot->graph(0)->setName("原始数据");//设置名称

    ui->chartPlot->graph(0)->rescaleAxes(); // 自适应宽度

    ui->chartPlot->setInteraction(QCP::iRangeDrag,true);// 拖拽曲线
    ui->chartPlot->setInteraction(QCP::iRangeZoom,true);// 鼠标滚轮缩放
    ui->chartPlot->setCursor(QCursor(Qt::PointingHandCursor));
    ui->chartPlot->setInteraction( QCP::iSelectAxes,true);
    onMouseWheel();

    /* 游标
    // 生成游标
    tracer = new QCPItemTracer(customPlot); //生成游标

    tracer->setPen(QPen(Qt::red));//圆圈轮廓颜色
    tracer->setBrush(QBrush(Qt::red));//圆圈圈内颜色
    tracer->setStyle(QCPItemTracer::tsCircle);//圆圈
    tracer->setSize(5);//设置大小
    //游标说明
    tracerLabel = new QCPItemText(customPlot); //生成游标说明
    tracerLabel->setLayer("overlay");//设置图层为overlay，因为需要频繁刷新
    tracerLabel->setPen(QPen(Qt::black));//设置游标说明颜色
    tracerLabel->setPositionAlignment(Qt::AlignLeft | Qt::AlignTop);//左上
    tracerLabel->position->setParentAnchor(tracer->position);//自动跟随
    */


    // 设备获取光谱数据
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
    Sleep(2000);    // wait 2 seconds

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

    // 获取横纵坐标数据
    MainWindow::wave = getWavelength();
    MainWindow::data = ReadSpectrum();
    QVector<double> x(2001), y(2001); //初始化向量x和y
        for (int i=0; i<2001; ++i)
        {
          x[i] = *(MainWindow::wave + i);
          y[i] = *(MainWindow::data.array + i);
        }
    ui->chartPlot->graph(0)->setData(x, y);
    ui->chartPlot->graph(0)->setName("设定光谱数据");// 设置图例名称

    // 绘图
    ui->chartPlot->replot();
    MainWindow::dataflag = 1; // 有数据，设定标志位为1

/*  旧绘图插件
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
    // setData();为数据曲线关联数据
    // series0->replace(newPoints);    // 原绘图
    */


}


// 暗背景模式
void MainWindow::on_buttonDarkSp_clicked()
{
    // 图表初始化
    QCustomPlot *customPlot = ui->chartPlot;
    ui->chartPlot->clearGraphs();   // 清除上一次数据
    ui->chartPlot->clearItems();
    ui->chartPlot->clearPlottables();
    ui->chartPlot->clearFocus();
    ui->chartPlot->clearMask();
    customPlot->addGraph();
    QPen pen;
    pen.setWidth(4);//曲线的粗细
    pen.setColor(Qt::white);
    customPlot->graph(0)->setPen(pen); // 曲线的颜色
    customPlot->graph(0)->setBrush(QBrush(QColor(216, 227, 231, 20))); // 曲线与X轴包围区的颜色
    ui->chartPlot->setBackground(QPixmap("./dark.png"));
    ui->chartPlot->setBackgroundScaledMode(Qt::IgnoreAspectRatio);

    // 标题初始化
    ui->labelTitle->setText("波长-强度光谱图像(暗环境模式)");
    /* 旧初始化 会产生重复标题渲染问题
    customPlot->plotLayout()->insertRow(0);
    QCPTextElement *H_title = new QCPTextElement(customPlot, "光谱测量", QFont("HarmonyOS Sans SC", 12, QFont::Bold));
    customPlot->plotLayout()->addElement(0, 0, H_title);
    */
    // 为坐标轴添加标签
    ui->chartPlot->xAxis->setLabel("波长/nm");
    ui->chartPlot->yAxis->setLabel("强度Counts");
    // 设置坐标轴样式 风格为 dark
    ui->chartPlot->xAxis->setRange(300, 900);
    ui->chartPlot->yAxis->setRange(0, 6000);
    ui->chartPlot->xAxis->setLabelColor(Qt::white);
    ui->chartPlot->yAxis->setLabelColor(Qt::white);
    ui->chartPlot->xAxis->setBasePen(QPen(Qt::white));
    ui->chartPlot->yAxis->setBasePen(QPen(Qt::white));
    ui->chartPlot->xAxis->setTickPen(QPen(Qt::white));
    ui->chartPlot->yAxis->setTickPen(QPen(Qt::white));
    ui->chartPlot->xAxis->setTickLabelColor(Qt::white);
    ui->chartPlot->yAxis->setTickLabelColor(Qt::white);
    //设置图例
    ui->chartPlot->legend->setVisible(true); // 显示图例
    customPlot->legend->setBrush(QColor(255, 255, 255, 150)); // 图例透明
    ui->chartPlot->legend->setFont(QFont("HarmonyOS Sans SC"));
    customPlot->legend->setBorderPen(Qt::NoPen);// 隐藏边框
    customPlot->graph(0)->setName("原始数据");//设置名称

    ui->chartPlot->graph(0)->rescaleAxes();

    for (int k = 1; k < ui->chartPlot->graphCount(); k++)
    {
        ui->chartPlot->graph(k)->rescaleAxes(true);
    }

    ui->chartPlot->setInteraction(QCP::iRangeDrag,true);// 拖拽曲线
    ui->chartPlot->setInteraction(QCP::iRangeZoom,true);// 鼠标滚轮缩放
    ui->chartPlot->setCursor(QCursor(Qt::PointingHandCursor));
    ui->chartPlot->setInteraction( QCP::iSelectAxes,true);
    onMouseWheel();

    // 设备获取光谱数据
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
    Sleep(2000);    // wait 2 seconds

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
                ui->logShow->append(u8"暗环境模式绘图中");
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
        ui->logShow->append(u8"请确保光源打开");
    }

    // 获取横纵坐标数据
    MainWindow::wave = getWavelength();
    MainWindow::data = ReadSpectrum();
    QVector<double> x(2001), y(2001); //初始化向量x和y
        for (int i=0; i<2001; ++i)
        {
          x[i] = *(MainWindow::wave + i);
          y[i] = *(MainWindow::data.array + i);
        }
    ui->chartPlot->graph(0)->setData(x, y);
    ui->chartPlot->graph(0)->setName("暗环境模式光谱");// 设置图例名称

    // 绘图
    ui->chartPlot->replot();
    MainWindow::dataflag = 1; // 有数据，设定标志位为1
    /* 旧插件绘图
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
    */

}

// 光谱图表复位
void MainWindow::on_butttonReset_clicked()
{
    // 设置坐标轴的范围，以看到所有数据
    ui->chartPlot->xAxis->setRange(300, 900);
    ui->chartPlot->legend->setVisible(true); // 显示图例

    ui->chartPlot->graph(0)->rescaleAxes();

    ui->chartPlot->setInteraction(QCP::iRangeDrag,true);// 拖拽曲线
    ui->chartPlot->setInteraction(QCP::iRangeZoom,true);// 鼠标滚轮缩放
    ui->chartPlot->setCursor(QCursor(Qt::PointingHandCursor));
    ui->chartPlot->setInteraction( QCP::iSelectAxes,true);
    onMouseWheel();
    ui->chartPlot->xAxis->setLabel(u8"波长/nm");
    ui->chartPlot->yAxis->setLabel(u8"强度Counts");
}




// 绘图区域清空
void MainWindow::on_buttonClean_clicked()
{
    // 图表初始化
    QCustomPlot *customPlot = ui->chartPlot;
    ui->chartPlot->clearGraphs();   // 清除上一次数据
    ui->chartPlot->clearItems();
    ui->chartPlot->clearPlottables();
    ui->chartPlot->clearFocus();
    ui->chartPlot->clearMask();
    customPlot->addGraph();
    customPlot->graph(0)->setPen(QPen(Qt::blue)); // 曲线的颜色
    customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // 曲线与X轴包围区的颜色

    // 标题初始化
    ui->labelTitle->setText("绘图区已复位");
    /*
    customPlot->plotLayout()->insertRow(0);
    QCPTextElement *H_title = new QCPTextElement(customPlot, "光谱测量", QFont("HarmonyOS Sans SC", 12, QFont::Bold));
    customPlot->plotLayout()->addElement(0, 0, H_title);
    */
    // 为坐标轴添加标签
    ui->chartPlot->yAxis->setLabel("波长/nm");
    ui->chartPlot->yAxis->setLabel("强度(Counts)");
    ui->chartPlot->xAxis->setLabelColor(Qt::black);
    ui->chartPlot->yAxis->setLabelColor(Qt::black);
    ui->chartPlot->xAxis->setBasePen(QPen(Qt::black));
    ui->chartPlot->yAxis->setBasePen(QPen(Qt::black));
    ui->chartPlot->xAxis->setTickPen(QPen(Qt::black));
    ui->chartPlot->yAxis->setTickPen(QPen(Qt::black));
    ui->chartPlot->xAxis->setTickLabelColor(Qt::black);
    ui->chartPlot->yAxis->setTickLabelColor(Qt::black);

    // 设置坐标轴的范围，以看到所有数据
    ui->chartPlot->xAxis->setRange(300, 900);
    ui->chartPlot->yAxis->setRange(0, 6000);
    ui->chartPlot->legend->setVisible(true); // 显示图例
    customPlot->legend->setBrush(QColor(255, 255, 255, 150)); // 图例透明
    ui->chartPlot->legend->setFont(QFont("HarmonyOS Sans SC"));
    customPlot->legend->setBorderPen(Qt::NoPen);// 隐藏边框
    ui->chartPlot->setBackground(QPixmap("./light.jpg"));
    ui->chartPlot->setBackgroundScaledMode(Qt::IgnoreAspectRatio);


    ui->chartPlot->graph(0)->rescaleAxes();

    ui->chartPlot->setInteraction(QCP::iRangeDrag,true);// 拖拽曲线
    ui->chartPlot->setInteraction(QCP::iRangeZoom,true);// 鼠标滚轮缩放

    // 输出日志
    QString log;
    log = "Graphic area clear done.";
    ui->logShow->append("---------------------");
    ui->logShow->append(TEXT_COLOR_GREEN("Clear ") + log);

    // 绘图
    ui->chartPlot->replot();
    /* 旧清空插件
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
    */
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
    // 图表初始化
    QCustomPlot *customPlot = ui->chartPlot;
    ui->chartPlot->clearGraphs();   // 清除上一次数据
    ui->chartPlot->clearItems();
    ui->chartPlot->clearPlottables();
    ui->chartPlot->clearFocus();
    ui->chartPlot->clearMask();
    customPlot->addGraph();
    customPlot->graph(0)->setPen(QPen(Qt::white)); // 曲线的颜色
    customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // 曲线与X轴包围区的颜色

    // 标题初始化
    ui->labelTitle->setText(u8"原始数据导出预渲染");

    /* 旧标题 会引起重复渲染问题
    customPlot->plotLayout()->insertRow(0);
    QCPTextElement *H_title = new QCPTextElement(customPlot, "光谱测量", QFont("HarmonyOS Sans SC", 12, QFont::Bold));
    customPlot->plotLayout()->addElement(0, 0, H_title);
    */
    // 为坐标轴添加标签
    ui->chartPlot->yAxis->setLabel(u8"波长/nm");
    ui->chartPlot->yAxis->setLabel(u8"强度(Counts)");
    // 设置坐标轴的范围，以看到所有数据
    ui->chartPlot->xAxis->setRange(300, 900);
    ui->chartPlot->yAxis->setRange(0, 6000);
    ui->chartPlot->xAxis->setLabelColor(Qt::white);
    ui->chartPlot->yAxis->setLabelColor(Qt::white);
    ui->chartPlot->xAxis->setTickPen(QPen(Qt::white));
    ui->chartPlot->yAxis->setTickPen(QPen(Qt::white));
    ui->chartPlot->xAxis->setTickLabelColor(Qt::white);
    ui->chartPlot->yAxis->setTickLabelColor(Qt::white);

    ui->chartPlot->legend->setVisible(true); // 显示图例
    customPlot->legend->setBrush(QColor(255, 255, 255, 150)); // 图例透明
    ui->chartPlot->legend->setFont(QFont("HarmonyOS Sans SC"));
    customPlot->legend->setBorderPen(Qt::NoPen);// 隐藏边框
    customPlot->graph(0)->setName(u8"原始数据");//设置名称
    // 背景颜色
    ui->chartPlot->setBackground(QPixmap("./dark.png"));
    ui->chartPlot->setBackgroundScaledMode(Qt::IgnoreAspectRatio);

    ui->chartPlot->graph(0)->rescaleAxes();

    ui->chartPlot->setInteraction(QCP::iRangeDrag,true);// 拖拽曲线
    ui->chartPlot->setInteraction(QCP::iRangeZoom,true);// 鼠标滚轮缩放

    // 设备获取光谱数据
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
    Sleep(2000);    // wait 2 seconds

    // 输出日志
    QString log;
    if (flag == 1)
        {
            flag = getSpectrumDataReadyFlag();
            if (flag == SPECTRUMDATA_READY)
            {
                log = "Get Origin Data.";
                ui->logShow->append("---------------------");

                ui->logShow->append(TEXT_COLOR_GREEN("Done ") + log);
                ui->logShow->append("Processing...");

                log = "Accept Data";
                ui->logShow->append(TEXT_COLOR_GREEN("Done ") + log);
                ui->logShow->append(u8"导出文件命名为'Origin_Data.txt'");
            }
            else
            {
                log = "Set isn't ready.";
                ui->logShow->append("---------------------");
                ui->logShow->append(TEXT_COLOR_RED("Failed ") + log);
            }
        }
    else
    {
        log = "Haven't got Spectrum";
        ui->logShow->append(TEXT_COLOR_RED("Failed ") + log);
        ui->logShow->append("请检查数据是否存在");
    }

    // 获取横纵坐标数据
    MainWindow::wave = getWavelength();
    MainWindow::data = ReadSpectrum();
    QVector<double> x(2001), y(2001); //初始化向量x和y
        for (int i=0; i<2001; ++i)
        {
          x[i] = *(MainWindow::wave + i);
          y[i] = *(MainWindow::data.array + i);
        }
    ui->chartPlot->graph(0)->setData(x, y);
    ui->chartPlot->graph(0)->setName(u8"原始光谱数据");// 设置图例名称

    // 绘图
    ui->chartPlot->replot();
    MainWindow::dataflag = 1; // 有数据，设定标志位为1

    if (MainWindow::dataflag == 1)
    {
            // 获得横纵坐标数据
            std::ofstream origindata;
            int* intensity = data.array;
            QList<QPointF> newPoints;
            origindata.open("Origin_Data.txt");
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
    }
        else
        {
            ui->logShow->append(TEXT_COLOR_RED(u8"无数据接收"));
        }
    /* 旧数据导出，基于QchartView
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
    */

}

// 头栏数据处理
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
// 数据处理，和头栏数据处理功能相同
void MainWindow::on_buttonDataProcess_clicked()
{
    if (MainWindow::dataflag != 1)
    {
        QString log = u8"系统未收集到原始数据";
        ui->logShow->append(TEXT_COLOR_RED("FATAL ") + log);
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
        QString log = "数据处理成功，请重新绘图";
        ui->logShow->append(TEXT_COLOR_GREEN("Done ") + log);
    }
    else
    {
        ui->logShow->append("---------------------");
        QString log = "Nothing changed.";
        ui->logShow->append(TEXT_COLOR_YELLOW("Warning ") + log);
    }

    // 图表初始化
    QCustomPlot *customPlot = ui->chartPlot;
    ui->chartPlot->clearGraphs();   // 清除上一次数据
    ui->chartPlot->clearItems();
    ui->chartPlot->clearPlottables();
    ui->chartPlot->clearFocus();
    ui->chartPlot->clearMask();
    customPlot->addGraph();

    QPen pen;
    pen.setWidth(4);//曲线的粗细
    pen.setColor(Qt::blue);
    customPlot->graph(0)->setPen(pen); // 曲线的颜色
    customPlot->graph(0)->setBrush(QBrush(QColor(23, 129, 181, 40))); // 曲线与X轴包围区的颜色
    ui->chartPlot->setBackground(QPixmap("./light.jpg"));
    ui->chartPlot->setBackgroundScaledMode(Qt::IgnoreAspectRatio);

    // 标题初始化
    ui->labelTitle->setText(u8"处理后光谱图像");
    /* 旧初始化 会产生重复标题渲染问题
    customPlot->plotLayout()->insertRow(0);
    QCPTextElement *H_title = new QCPTextElement(customPlot, "光谱测量", QFont("HarmonyOS Sans SC", 12, QFont::Bold));
    customPlot->plotLayout()->addElement(0, 0, H_title);
    */
    // 为坐标轴设定，风格为 light
    ui->chartPlot->xAxis->setLabel(u8"波长/nm");
    ui->chartPlot->yAxis->setLabel(u8"强度(Counts)");
    ui->chartPlot->xAxis->setLabelColor(Qt::black);
    ui->chartPlot->yAxis->setLabelColor(Qt::black);
    ui->chartPlot->xAxis->setBasePen(QPen(Qt::black));
    ui->chartPlot->yAxis->setBasePen(QPen(Qt::black));
    ui->chartPlot->xAxis->setTickPen(QPen(Qt::black));
    ui->chartPlot->yAxis->setTickPen(QPen(Qt::black));
    ui->chartPlot->xAxis->setTickLabelColor(Qt::black);
    ui->chartPlot->yAxis->setTickLabelColor(Qt::black);
    // 设置坐标轴的范围，以看到所有数据
    ui->chartPlot->xAxis->setRange(300, 900);
    ui->chartPlot->yAxis->setRange(0, 6000);
    ui->chartPlot->legend->setVisible(true); // 显示图例
    customPlot->legend->setBrush(QColor(255, 255, 255, 150)); // 图例透明
    ui->chartPlot->legend->setFont(QFont("HarmonyOS Sans SC"));
    customPlot->legend->setBorderPen(Qt::NoPen);// 隐藏边框
    customPlot->graph(0)->setName(u8"原始数据");//设置名称

    ui->chartPlot->graph(0)->rescaleAxes();

    ui->chartPlot->setInteraction(QCP::iRangeDrag,true);// 拖拽曲线
    ui->chartPlot->setInteraction(QCP::iRangeZoom,true);// 鼠标滚轮缩放
    ui->chartPlot->setCursor(QCursor(Qt::PointingHandCursor));
    ui->chartPlot->setInteraction( QCP::iSelectAxes,true);
    onMouseWheel();

    // 设备获取光谱数据
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

    // 获取横纵坐标数据
    MainWindow::wave = getWavelength();
    float* intensity = dataProcess(MainWindow::data.array, newWindow::smoothLevel, newWindow::deductflag, newWindow::nolinear, newWindow::waveshape);
    QVector<double> x(2001), y(2001); //初始化向量x和y

    if (newwindow2::Caready == 1)
    {
        for (int i=0; i<2001; ++i)
        {
            x[i] = *(MainWindow::wave + i);
            y[i] = *(intensity + i);
            y[i] = (y[i] - newwindow2::D) * newwindow2::Ca[i] / MainWindow::time_global;
        }
        ui->chartPlot->graph(0)->setData(x, y);
        ui->chartPlot->graph(0)->setName(u8"标定/处理后光谱数据");// 设置图例名称
    }
    else if (newWindow::changeflag == 1)
    {
        for (int i=0; i<2001; ++i)
        {
            x[i] = *(MainWindow::wave + i);
            y[i] = *(intensity + i);
        }
        ui->chartPlot->graph(0)->setData(x, y);
        ui->chartPlot->graph(0)->setName(u8"处理后光谱数据");// 设置图例名称
    }
    else
    {
        for (int i=0; i<2001; ++i)
        {
            x[i] = *(MainWindow::wave + i);
            y[i] = *(intensity + i);
        }
        ui->chartPlot->graph(0)->setData(x, y);
        ui->chartPlot->graph(0)->setName(u8"光谱数据");// 设置图例名称
    }

    // 绘图
    ui->chartPlot->replot();
    MainWindow::dataflag = 0; // 数据已使用，置零

    /* 基于旧 QChartView 的重绘图
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
    */
}

// 导出数据
void MainWindow::on_buttonDataOut_clicked()
{
    std::ofstream origindata;
    MainWindow::wave = getWavelength();
    MainWindow::data = ReadSpectrum();
    ui->logShow->append(u8"导出现在保存的数据，请确保数据为最新");
    ui->logShow->append(u8" ");
    ui->logShow->append(u8"本次导出的文件名称为 'Data.txt' 请注意查收");

    QList<QPointF> newPoints;
    origindata.open("Data.txt");
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
    bool flag_0;
    closeSpectraMeter();
    flag_0 = openSpectraMeter(); // 再次尝试连接设备

    if (flag_0 == true)
    {
        ui->logShow->clear();
        ui->logShow->append(TEXT_COLOR_GREEN(u8"初始化校准处理"));
        initialize();
        Sleep(500);
        newwindow2 *configWindow = new newwindow2;
        configWindow->show();
    }
    else    // 无设备连接，先清空日志，再进行提示
    {
        ui->logShow->clear();
        ui->logShow->append(u8"设备初始化出现问题");
    }

}
/* 旧系统校准录入
    bool flag_0;
    flag_0 = openSpectraMeter();
    if (flag_0 == true )    // 有设备连接
    {
        // 日志提示
        ui->logShow->append(TEXT_COLOR_YELLOW("Please prepare standard light..."));
        Sleep(5000);
        ui->logShow->append(" ");
        ui->logShow->append(TEXT_COLOR_GREEN("Start."));

        // 设备再次初始化，保证不因为其他操作影响设备
        ui->logShow->append("Initing device...");
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

        // 获取标准灯数据 D0
        ui->logShow->append("Test standard spectrum.");
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

*/


// 保存图片
bool MainWindow::on_buttonSaveGraphic_clicked()
{
    QString filename = QFileDialog::getSaveFileName();

        if( filename == "" ){
            QMessageBox::information(this,"fail","保存失败");
             return false;
         }
         if( filename.endsWith(".png") ){
             QMessageBox::information(this,"success","成功保存为png文件");
             return ui->chartPlot->savePng( filename, ui->chartPlot->width(), ui->chartPlot->height() );

         }
         if( filename.endsWith(".jpg")||filename.endsWith(".jpeg") ){
             QMessageBox::information(this,"success","成功保存为jpg文件");
             return ui->chartPlot->saveJpg( filename, ui->chartPlot->width(), ui->chartPlot->height() );

         }
         if( filename.endsWith(".bmp") ){
             QMessageBox::information(this,"success","成功保存为bmp文件");
             return ui->chartPlot->saveBmp( filename, ui->chartPlot->width(), ui->chartPlot->height() );

         }
         if( filename.endsWith(".pdf") ){
             QMessageBox::information(this,"success","成功保存为pdf文件");
             return ui->chartPlot->savePdf( filename, ui->chartPlot->width(), ui->chartPlot->height() );

         }
        else{
         //否则追加后缀名为.png保存文件
             QMessageBox::information(this,"success","保存成功,默认保存为png文件");
         return ui->chartPlot->savePng(filename.append(".png"), ui->chartPlot->width(), ui->chartPlot->height() );

        }
}

