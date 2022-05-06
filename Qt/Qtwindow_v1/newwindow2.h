#ifndef NEWWINDOW2_H
#define NEWWINDOW2_H

#include <QWidget>

namespace Ui {
class newwindow2;
}

class newwindow2 : public QWidget
{
    Q_OBJECT

public:
    explicit newwindow2(QWidget *parent = nullptr);
    ~newwindow2();

    static bool fileflag;
    static int D;
    static double Ca[2001];
    static bool Caready;

private slots:
    void on_AcceptData_clicked();

    void on_buttonCaOutput_clicked();

    void on_CancelData_clicked();

private:
    Ui::newwindow2 *ui;
};

#endif // NEWWINDOW2_H
