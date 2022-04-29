#ifndef DIALOGPEN_H
#define DIALOGPEN_H

#include <QDialog>
#include <QPen>

namespace Ui {
class DialogPen;
}

class DialogPen : public QDialog
{
    Q_OBJECT
private:
    QPen m_pen;
public:
    explicit DialogPen(QWidget *parent = nullptr);
    ~DialogPen();

    QPen getPen();
    static QPen getPen(QPen iniPen, bool &ok);
    void setPen(const QPen &pen);

private slots:

    void on_colorOption_clicked();

private:
    Ui::DialogPen *ui;
};

#endif // DIALOGPEN_H
