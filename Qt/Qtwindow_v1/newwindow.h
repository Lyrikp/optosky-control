#ifndef NEWWINDOW_H
#define NEWWINDOW_H

#include <QWidget>

namespace Ui {
class newWindow;
}

class newWindow : public QWidget
{
    Q_OBJECT

public:
    explicit newWindow(QWidget *parent = nullptr);
    ~newWindow();

    static bool deductflag;
    static int smoothLevel;
    static bool nolinear;
    static bool waveshape;
    static int* processedData;

    static int changeflag;

private slots:

    void on_boxDeductDark_clicked();

    void on_boxNoLinearCorrect_clicked();

    void on_boxWaveShapeCorrect_clicked();

    void on_buttonCorrect_clicked();

    void on_buttonCancel_clicked();

    void on_buttonOutputData_clicked();

private:
    Ui::newWindow *ui;
};

#endif // NEWWINDOW_H
