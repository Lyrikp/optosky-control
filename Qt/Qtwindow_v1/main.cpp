#include "mainwindow.h"

#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QDialog>
#include <QWidget>
#include <QMainWindow>
#include <QSlider>
#include <QSpinBox>
#include <QLineEdit>    // 行编辑
#include <QHBoxLayout>  // 水平布局器
#include <QDoubleValidator> // 验证器
#pragma execution_character_set("utf-8")

int main(int argc, char *argv[])
{
    // 主窗口
    QApplication a(argc, argv);
    MainWindow Mainwindow;
    Mainwindow.resize(1800, 1200);
    Mainwindow.show();
    return a.exec();
}
