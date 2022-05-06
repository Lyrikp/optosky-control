/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLink_device;
    QAction *actionStop_Link;
    QAction *actionOrigin_Data;
    QAction *actionQuit;
    QAction *actionData_Process;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QPushButton *buttonDataProcess;
    QLineEdit *setAverage;
    QPushButton *buttonLink;
    QPushButton *buttonDataOut;
    QPushButton *buttonDarkSp;
    QLineEdit *setTime;
    QPushButton *buttonVice;
    QPushButton *pushButton_5;
    QPushButton *buttonOut;
    QPushButton *buttonSystemCheck;
    QPushButton *buttonSpectrum;
    QPushButton *butttonReset;
    QCustomPlot *chartPlot;
    QTextBrowser *logShow;
    QPushButton *buttonCleanlog;
    QPushButton *buttonInfo;
    QPushButton *buttonClean;
    QPushButton *pushButton_6;
    QPushButton *buttonSaveGraphic;
    QPushButton *buttonDrawGraph;
    QLabel *labelTitle;
    QStatusBar *statusbar;
    QMenuBar *menuBar;
    QMenu *menuOPTOSKY_ATP5020P;
    QMenu *menudata_process;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(815, 461);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("HarmonyOS Sans SC"));
        font.setPointSize(9);
        font.setBold(true);
        MainWindow->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../svgsource/bar-chart-grouped-line.svg"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setAutoFillBackground(false);
        actionLink_device = new QAction(MainWindow);
        actionLink_device->setObjectName(QString::fromUtf8("actionLink_device"));
        actionStop_Link = new QAction(MainWindow);
        actionStop_Link->setObjectName(QString::fromUtf8("actionStop_Link"));
        actionOrigin_Data = new QAction(MainWindow);
        actionOrigin_Data->setObjectName(QString::fromUtf8("actionOrigin_Data"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionData_Process = new QAction(MainWindow);
        actionData_Process->setObjectName(QString::fromUtf8("actionData_Process"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        buttonDataProcess = new QPushButton(centralwidget);
        buttonDataProcess->setObjectName(QString::fromUtf8("buttonDataProcess"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("../../svgsource/tools-fill.svg"), QSize(), QIcon::Normal, QIcon::Off);
        buttonDataProcess->setIcon(icon1);

        gridLayout->addWidget(buttonDataProcess, 0, 8, 1, 1);

        setAverage = new QLineEdit(centralwidget);
        setAverage->setObjectName(QString::fromUtf8("setAverage"));

        gridLayout->addWidget(setAverage, 6, 0, 1, 2);

        buttonLink = new QPushButton(centralwidget);
        buttonLink->setObjectName(QString::fromUtf8("buttonLink"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(9);
        font1.setBold(true);
        buttonLink->setFont(font1);
        buttonLink->setStyleSheet(QString::fromUtf8("background-color: rgb(23, 195, 123);\n"
""));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("../../svgsource/play-line.svg"), QSize(), QIcon::Normal, QIcon::Off);
        buttonLink->setIcon(icon2);
        buttonLink->setFlat(true);

        gridLayout->addWidget(buttonLink, 0, 0, 1, 1);

        buttonDataOut = new QPushButton(centralwidget);
        buttonDataOut->setObjectName(QString::fromUtf8("buttonDataOut"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("../../svgsource/file-3-line.svg"), QSize(), QIcon::Normal, QIcon::Off);
        buttonDataOut->setIcon(icon3);
        buttonDataOut->setFlat(true);

        gridLayout->addWidget(buttonDataOut, 2, 1, 1, 1);

        buttonDarkSp = new QPushButton(centralwidget);
        buttonDarkSp->setObjectName(QString::fromUtf8("buttonDarkSp"));
        buttonDarkSp->setEnabled(false);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8("../../svgsource/contrast-2-fill.svg"), QSize(), QIcon::Normal, QIcon::Off);
        buttonDarkSp->setIcon(icon4);
        buttonDarkSp->setFlat(false);

        gridLayout->addWidget(buttonDarkSp, 0, 3, 1, 1);

        setTime = new QLineEdit(centralwidget);
        setTime->setObjectName(QString::fromUtf8("setTime"));

        gridLayout->addWidget(setTime, 4, 0, 1, 2);

        buttonVice = new QPushButton(centralwidget);
        buttonVice->setObjectName(QString::fromUtf8("buttonVice"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8("../../svgsource/link.svg"), QSize(), QIcon::Normal, QIcon::Off);
        buttonVice->setIcon(icon5);
        buttonVice->setFlat(true);

        gridLayout->addWidget(buttonVice, 1, 0, 1, 1);

        pushButton_5 = new QPushButton(centralwidget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8("../../svgsource/timer-line.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_5->setIcon(icon6);
        pushButton_5->setCheckable(false);
        pushButton_5->setAutoDefault(true);
        pushButton_5->setFlat(true);

        gridLayout->addWidget(pushButton_5, 3, 0, 1, 1);

        buttonOut = new QPushButton(centralwidget);
        buttonOut->setObjectName(QString::fromUtf8("buttonOut"));
        buttonOut->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 99, 102);"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8("../../svgsource/stop-line.svg"), QSize(), QIcon::Normal, QIcon::Off);
        buttonOut->setIcon(icon7);
        buttonOut->setFlat(true);

        gridLayout->addWidget(buttonOut, 0, 1, 1, 1);

        buttonSystemCheck = new QPushButton(centralwidget);
        buttonSystemCheck->setObjectName(QString::fromUtf8("buttonSystemCheck"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8("../../svgsource/settings-6-line.svg"), QSize(), QIcon::Normal, QIcon::Off);
        buttonSystemCheck->setIcon(icon8);
        buttonSystemCheck->setFlat(true);

        gridLayout->addWidget(buttonSystemCheck, 2, 0, 1, 1);

        buttonSpectrum = new QPushButton(centralwidget);
        buttonSpectrum->setObjectName(QString::fromUtf8("buttonSpectrum"));
        buttonSpectrum->setEnabled(false);
        QIcon icon9;
        icon9.addFile(QString::fromUtf8("../../svgsource/login-circle-fill.svg"), QSize(), QIcon::Normal, QIcon::Off);
        buttonSpectrum->setIcon(icon9);
        buttonSpectrum->setAutoDefault(false);
        buttonSpectrum->setFlat(false);

        gridLayout->addWidget(buttonSpectrum, 0, 2, 1, 1);

        butttonReset = new QPushButton(centralwidget);
        butttonReset->setObjectName(QString::fromUtf8("butttonReset"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8("../../svgsource/find-replace-line.svg"), QSize(), QIcon::Normal, QIcon::Off);
        butttonReset->setIcon(icon10);

        gridLayout->addWidget(butttonReset, 0, 9, 1, 1);

        chartPlot = new QCustomPlot(centralwidget);
        chartPlot->setObjectName(QString::fromUtf8("chartPlot"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("HarmonyOS Sans SC"));
        font2.setPointSize(9);
        font2.setBold(false);
        chartPlot->setFont(font2);
        chartPlot->setAutoFillBackground(true);

        gridLayout->addWidget(chartPlot, 2, 2, 7, 10);

        logShow = new QTextBrowser(centralwidget);
        logShow->setObjectName(QString::fromUtf8("logShow"));
        logShow->setEnabled(true);
        logShow->setReadOnly(true);

        gridLayout->addWidget(logShow, 8, 0, 1, 2);

        buttonCleanlog = new QPushButton(centralwidget);
        buttonCleanlog->setObjectName(QString::fromUtf8("buttonCleanlog"));
        buttonCleanlog->setAutoFillBackground(false);
        QIcon icon11;
        icon11.addFile(QString::fromUtf8("../../svgsource/folder-info-line.svg"), QSize(), QIcon::Normal, QIcon::Off);
        buttonCleanlog->setIcon(icon11);
        buttonCleanlog->setCheckable(false);
        buttonCleanlog->setAutoDefault(true);
        buttonCleanlog->setFlat(true);

        gridLayout->addWidget(buttonCleanlog, 7, 0, 1, 1);

        buttonInfo = new QPushButton(centralwidget);
        buttonInfo->setObjectName(QString::fromUtf8("buttonInfo"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8("../../svgsource/information-line.svg"), QSize(), QIcon::Normal, QIcon::Off);
        buttonInfo->setIcon(icon12);
        buttonInfo->setFlat(true);

        gridLayout->addWidget(buttonInfo, 1, 1, 1, 1);

        buttonClean = new QPushButton(centralwidget);
        buttonClean->setObjectName(QString::fromUtf8("buttonClean"));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8("../../svgsource/rhythm-line.svg"), QSize(), QIcon::Normal, QIcon::Off);
        buttonClean->setIcon(icon13);
        buttonClean->setCheckable(false);
        buttonClean->setAutoDefault(true);
        buttonClean->setFlat(true);

        gridLayout->addWidget(buttonClean, 0, 11, 1, 1);

        pushButton_6 = new QPushButton(centralwidget);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8("../../svgsource/focus-2-fill.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_6->setIcon(icon14);
        pushButton_6->setCheckable(false);
        pushButton_6->setAutoDefault(true);
        pushButton_6->setFlat(true);

        gridLayout->addWidget(pushButton_6, 5, 0, 1, 1);

        buttonSaveGraphic = new QPushButton(centralwidget);
        buttonSaveGraphic->setObjectName(QString::fromUtf8("buttonSaveGraphic"));
        QIcon icon15;
        icon15.addFile(QString::fromUtf8("../../svgsource/image-add-fill.svg"), QSize(), QIcon::Normal, QIcon::Off);
        buttonSaveGraphic->setIcon(icon15);

        gridLayout->addWidget(buttonSaveGraphic, 0, 10, 1, 1);

        buttonDrawGraph = new QPushButton(centralwidget);
        buttonDrawGraph->setObjectName(QString::fromUtf8("buttonDrawGraph"));
        QIcon icon16;
        icon16.addFile(QString::fromUtf8("../../svgsource/line-chart-line.svg"), QSize(), QIcon::Normal, QIcon::Off);
        buttonDrawGraph->setIcon(icon16);
        buttonDrawGraph->setAutoDefault(false);
        buttonDrawGraph->setFlat(false);

        gridLayout->addWidget(buttonDrawGraph, 0, 4, 1, 1);

        labelTitle = new QLabel(centralwidget);
        labelTitle->setObjectName(QString::fromUtf8("labelTitle"));
        labelTitle->setMinimumSize(QSize(84, 25));
        QFont font3;
        font3.setFamily(QString::fromUtf8("HarmonyOS Sans SC"));
        font3.setPointSize(16);
        font3.setBold(true);
        labelTitle->setFont(font3);
        labelTitle->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labelTitle, 1, 2, 1, 10);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 815, 20));
        menuOPTOSKY_ATP5020P = new QMenu(menuBar);
        menuOPTOSKY_ATP5020P->setObjectName(QString::fromUtf8("menuOPTOSKY_ATP5020P"));
        menudata_process = new QMenu(menuBar);
        menudata_process->setObjectName(QString::fromUtf8("menudata_process"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuOPTOSKY_ATP5020P->menuAction());
        menuBar->addAction(menudata_process->menuAction());
        menuOPTOSKY_ATP5020P->addAction(actionLink_device);
        menuOPTOSKY_ATP5020P->addAction(actionStop_Link);
        menuOPTOSKY_ATP5020P->addSeparator();
        menuOPTOSKY_ATP5020P->addAction(actionQuit);
        menudata_process->addAction(actionOrigin_Data);
        menudata_process->addSeparator();
        menudata_process->addSeparator();
        menudata_process->addAction(actionData_Process);

        retranslateUi(MainWindow);

        buttonDarkSp->setDefault(false);
        pushButton_5->setDefault(true);
        buttonSpectrum->setDefault(false);
        buttonCleanlog->setDefault(true);
        buttonClean->setDefault(true);
        pushButton_6->setDefault(true);
        buttonDrawGraph->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\345\205\211\350\260\261\344\273\252\346\216\247\345\210\266_V0.0.5", nullptr));
        actionLink_device->setText(QCoreApplication::translate("MainWindow", "Link device", nullptr));
        actionStop_Link->setText(QCoreApplication::translate("MainWindow", "Stop Link", nullptr));
        actionOrigin_Data->setText(QCoreApplication::translate("MainWindow", "Origin Data(Light)", nullptr));
        actionQuit->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
        actionData_Process->setText(QCoreApplication::translate("MainWindow", "Data Process", nullptr));
        buttonDataProcess->setText(QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\345\244\204\347\220\206", nullptr));
        buttonLink->setText(QCoreApplication::translate("MainWindow", "\350\277\236\346\216\245\350\256\276\345\244\207", nullptr));
        buttonDataOut->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\207\272\346\225\260\346\215\256", nullptr));
        buttonDarkSp->setText(QCoreApplication::translate("MainWindow", "\346\232\227\350\203\214\346\231\257\346\250\241\345\274\217", nullptr));
        buttonVice->setText(QCoreApplication::translate("MainWindow", "\350\277\236\346\216\245\344\277\241\346\201\257", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "\351\207\207\346\240\267\346\227\266\351\227\264", nullptr));
        buttonOut->setText(QCoreApplication::translate("MainWindow", "\346\226\255\345\274\200\350\277\236\346\216\245", nullptr));
        buttonSystemCheck->setText(QCoreApplication::translate("MainWindow", "\347\263\273\347\273\237\346\240\241\345\207\206", nullptr));
        buttonSpectrum->setText(QCoreApplication::translate("MainWindow", "\346\265\213\351\207\217", nullptr));
        butttonReset->setText(QCoreApplication::translate("MainWindow", "\345\244\215\344\275\215", nullptr));
        buttonCleanlog->setText(QCoreApplication::translate("MainWindow", "\346\223\215\344\275\234\346\227\245\345\277\227", nullptr));
        buttonInfo->setText(QCoreApplication::translate("MainWindow", "\350\256\276\345\244\207\344\277\241\346\201\257", nullptr));
        buttonClean->setText(QCoreApplication::translate("MainWindow", "\345\205\211\350\260\261\346\265\213\351\207\217", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "\351\207\207\351\233\206\346\254\241\346\225\260", nullptr));
        buttonSaveGraphic->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230\345\233\276\345\203\217", nullptr));
        buttonDrawGraph->setText(QCoreApplication::translate("MainWindow", "\351\207\215\347\273\230\345\233\276", nullptr));
        labelTitle->setText(QCoreApplication::translate("MainWindow", "\345\205\211\350\260\261\346\225\260\346\215\256", nullptr));
        menuOPTOSKY_ATP5020P->setTitle(QCoreApplication::translate("MainWindow", "OPTOSKY ATP5020P", nullptr));
        menudata_process->setTitle(QCoreApplication::translate("MainWindow", "Data Process", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
