#include "dialogpen.h"
#include "ui_dialogpen.h"
#include <QColorDialog>

DialogPen::DialogPen(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

DialogPen::~DialogPen()
{
    delete ui;
}


