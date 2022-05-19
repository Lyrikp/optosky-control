#include "peakset.h"
#include "ui_peakset.h"

int peakset::peak_distance = 10;

peakset::peakset(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::peakset)
{
    ui->setupUi(this);
}

peakset::~peakset()
{
    delete ui;
}

void peakset::on_buttonAcceptp_clicked()
{
    peakset::peak_distance = ui->peakDistance->value();
    close();
}


void peakset::on_buttonCancelp_clicked()
{
    close();
}

