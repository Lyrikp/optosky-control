#ifndef PEAKSET_H
#define PEAKSET_H

#include <QWidget>

namespace Ui {
class peakset;
}

class peakset : public QWidget
{
    Q_OBJECT

public:
    explicit peakset(QWidget *parent = nullptr);
    ~peakset();

    static int peak_distance;

private slots:
    void on_buttonAcceptp_clicked();

    void on_buttonCancelp_clicked();

private:
    Ui::peakset *ui;
};

#endif // PEAKSET_H
