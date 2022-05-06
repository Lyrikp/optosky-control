#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qcustomplot.h"
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QDoubleValidator>
#include <QtCharts>
#include <QChartView>
QT_CHARTS_USE_NAMESPACE
#include <QValueAxis>
#include <DriverType.h>
#include <Driver_app.h>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    static int time_global;
    static int average_global;

    static int dataflag;

    static Spectrumsp data;
    static float* wave;

public slots:
    void enableButton(void);        // 使能槽函数

    void onMouseWheel(void);        // 鼠标滚轮事件

    void on_buttonLink_clicked();

    void on_buttonOut_clicked();

    void on_buttonVice_clicked();

    void on_buttonInfo_clicked();

    void on_setTime_editingFinished();

    void on_setAverage_editingFinished();

    void on_buttonSpectrum_clicked();

    // void mouseMove1(QMouseEvent *e);

private slots:

    void on_butttonReset_clicked();

    void on_buttonDarkSp_clicked();

    void on_buttonClean_clicked();

    void on_buttonCleanlog_clicked();

    void on_actionLink_device_triggered();

    void on_actionStop_Link_triggered();

    void on_actionQuit_triggered();

    void on_actionOrigin_Data_triggered();

    void on_actionData_Process_triggered();

    void on_buttonDrawGraph_clicked();

    void on_buttonDataOut_clicked();

    void on_buttonSystemCheck_clicked();

    void on_buttonDataProcess_clicked();


    bool on_buttonSaveGraphic_clicked();

private:
    // 通过 ui-> 访问界面相关代码
    Ui::MainWindow *ui;

    void createChart();

    QLineSeries *curSeries;
    QValueAxis *curAxis;

   /* 游标相关
    QCPItemTracer *tracer;
    QCPItemText *tracerLabel;
    */



/*    QLineEdit* setTime;
    QLineEdit* setAverage;
    QPushButton* buttonSpetrum;
    QPushButton* buttonLink;
    QPushButton* buttonStop;
    QPushButton* buttonInfo;
    QPushButton* buttonVice;
*/
};
#endif // MAINWINDOW_H
