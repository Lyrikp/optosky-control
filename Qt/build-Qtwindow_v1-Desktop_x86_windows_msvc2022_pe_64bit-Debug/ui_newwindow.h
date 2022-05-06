/********************************************************************************
** Form generated from reading UI file 'newwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWWINDOW_H
#define UI_NEWWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_newWindow
{
public:
    QGridLayout *gridLayout;
    QPushButton *buttonOutputData;
    QPushButton *pushButton_2;
    QCheckBox *boxWaveShapeCorrect;
    QSpinBox *spinSmoothLevel;
    QPushButton *pushButton;
    QCheckBox *boxNoLinearCorrect;
    QCheckBox *boxDeductDark;
    QPushButton *buttonCorrect;
    QPushButton *buttonCancel;

    void setupUi(QWidget *newWindow)
    {
        if (newWindow->objectName().isEmpty())
            newWindow->setObjectName(QString::fromUtf8("newWindow"));
        newWindow->resize(440, 300);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setBold(true);
        newWindow->setFont(font);
        newWindow->setAcceptDrops(false);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../svgsource/tools-fill.svg"), QSize(), QIcon::Normal, QIcon::Off);
        newWindow->setWindowIcon(icon);
        gridLayout = new QGridLayout(newWindow);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        buttonOutputData = new QPushButton(newWindow);
        buttonOutputData->setObjectName(QString::fromUtf8("buttonOutputData"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("../../svgsource/logout-circle-r-line.svg"), QSize(), QIcon::Normal, QIcon::Off);
        buttonOutputData->setIcon(icon1);

        gridLayout->addWidget(buttonOutputData, 4, 3, 1, 1);

        pushButton_2 = new QPushButton(newWindow);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setLayoutDirection(Qt::LeftToRight);
        pushButton_2->setFlat(true);

        gridLayout->addWidget(pushButton_2, 3, 0, 1, 1);

        boxWaveShapeCorrect = new QCheckBox(newWindow);
        boxWaveShapeCorrect->setObjectName(QString::fromUtf8("boxWaveShapeCorrect"));

        gridLayout->addWidget(boxWaveShapeCorrect, 4, 2, 1, 1);

        spinSmoothLevel = new QSpinBox(newWindow);
        spinSmoothLevel->setObjectName(QString::fromUtf8("spinSmoothLevel"));
        spinSmoothLevel->setMaximum(4);

        gridLayout->addWidget(spinSmoothLevel, 3, 1, 1, 3);

        pushButton = new QPushButton(newWindow);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("../../svgsource/line-chart-line.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon2);
        pushButton->setFlat(true);

        gridLayout->addWidget(pushButton, 1, 0, 1, 1);

        boxNoLinearCorrect = new QCheckBox(newWindow);
        boxNoLinearCorrect->setObjectName(QString::fromUtf8("boxNoLinearCorrect"));

        gridLayout->addWidget(boxNoLinearCorrect, 4, 1, 1, 1);

        boxDeductDark = new QCheckBox(newWindow);
        boxDeductDark->setObjectName(QString::fromUtf8("boxDeductDark"));
        boxDeductDark->setChecked(true);
        boxDeductDark->setTristate(false);

        gridLayout->addWidget(boxDeductDark, 4, 0, 1, 1);

        buttonCorrect = new QPushButton(newWindow);
        buttonCorrect->setObjectName(QString::fromUtf8("buttonCorrect"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("../../svgsource/check-line.svg"), QSize(), QIcon::Normal, QIcon::Off);
        buttonCorrect->setIcon(icon3);

        gridLayout->addWidget(buttonCorrect, 5, 0, 1, 2);

        buttonCancel = new QPushButton(newWindow);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8("../../svgsource/close-line.svg"), QSize(), QIcon::Normal, QIcon::Off);
        buttonCancel->setIcon(icon4);

        gridLayout->addWidget(buttonCancel, 5, 2, 1, 2);


        retranslateUi(newWindow);

        QMetaObject::connectSlotsByName(newWindow);
    } // setupUi

    void retranslateUi(QWidget *newWindow)
    {
        newWindow->setWindowTitle(QCoreApplication::translate("newWindow", "\346\225\260\346\215\256\345\244\204\347\220\206\350\256\276\347\275\256", nullptr));
        buttonOutputData->setText(QCoreApplication::translate("newWindow", "\345\257\274\345\207\272\345\216\237\345\247\213\346\225\260\346\215\256", nullptr));
        pushButton_2->setText(QCoreApplication::translate("newWindow", "\346\273\244\346\263\242\347\255\211\347\272\247", nullptr));
        boxWaveShapeCorrect->setText(QCoreApplication::translate("newWindow", "\346\263\242\345\275\242\347\237\253\346\255\243", nullptr));
        pushButton->setText(QCoreApplication::translate("newWindow", "\346\225\260\346\215\256\345\244\204\347\220\206", nullptr));
        boxNoLinearCorrect->setText(QCoreApplication::translate("newWindow", "\351\235\236\347\272\277\346\200\247\347\237\253\346\255\243", nullptr));
        boxDeductDark->setText(QCoreApplication::translate("newWindow", "\346\232\227\345\272\225\347\237\253\346\255\243", nullptr));
        buttonCorrect->setText(QString());
        buttonCancel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class newWindow: public Ui_newWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWWINDOW_H
