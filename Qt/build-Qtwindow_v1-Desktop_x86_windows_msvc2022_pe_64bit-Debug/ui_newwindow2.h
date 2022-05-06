/********************************************************************************
** Form generated from reading UI file 'newwindow2.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWWINDOW2_H
#define UI_NEWWINDOW2_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_newwindow2
{
public:
    QGridLayout *gridLayout;
    QPushButton *AcceptData;
    QLineEdit *Wave1;
    QLineEdit *Wave10;
    QLabel *label_2;
    QLabel *label_13;
    QLineEdit *Wave6;
    QLineEdit *Spectrum8;
    QLabel *label_5;
    QLineEdit *Wave8;
    QLabel *label_10;
    QLineEdit *Wave7;
    QLineEdit *Wave9;
    QLabel *label_7;
    QPushButton *CancelData;
    QLineEdit *Spectrum1;
    QLineEdit *Wave2;
    QLineEdit *Spectrum7;
    QLineEdit *Spectrum10;
    QLineEdit *Spectrum6;
    QLabel *label_12;
    QLabel *label_4;
    QLabel *label_6;
    QLabel *label;
    QLabel *label_9;
    QLineEdit *Spectrum2;
    QLineEdit *Spectrum4;
    QLineEdit *Wave3;
    QLineEdit *Spectrum9;
    QPushButton *pushButton;
    QLabel *label_11;
    QPushButton *buttonInputStandard;
    QLineEdit *Spectrum3;
    QLineEdit *Wave4;
    QLineEdit *Spectrum5;
    QLabel *label_8;
    QLineEdit *Wave5;
    QLabel *label_3;
    QPushButton *buttonCaOutput;

    void setupUi(QWidget *newwindow2)
    {
        if (newwindow2->objectName().isEmpty())
            newwindow2->setObjectName(QString::fromUtf8("newwindow2"));
        newwindow2->resize(475, 536);
        QFont font;
        font.setFamily(QString::fromUtf8("HarmonyOS Sans SC"));
        font.setBold(true);
        newwindow2->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../svgsource/building-3-line.svg"), QSize(), QIcon::Normal, QIcon::Off);
        newwindow2->setWindowIcon(icon);
        gridLayout = new QGridLayout(newwindow2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        AcceptData = new QPushButton(newwindow2);
        AcceptData->setObjectName(QString::fromUtf8("AcceptData"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("../../svgsource/check-line.svg"), QSize(), QIcon::Normal, QIcon::Off);
        AcceptData->setIcon(icon1);

        gridLayout->addWidget(AcceptData, 10, 4, 1, 1);

        Wave1 = new QLineEdit(newwindow2);
        Wave1->setObjectName(QString::fromUtf8("Wave1"));

        gridLayout->addWidget(Wave1, 2, 1, 1, 1);

        Wave10 = new QLineEdit(newwindow2);
        Wave10->setObjectName(QString::fromUtf8("Wave10"));

        gridLayout->addWidget(Wave10, 11, 1, 1, 1);

        label_2 = new QLabel(newwindow2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 1, 1, 1);

        label_13 = new QLabel(newwindow2);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout->addWidget(label_13, 11, 0, 1, 1);

        Wave6 = new QLineEdit(newwindow2);
        Wave6->setObjectName(QString::fromUtf8("Wave6"));

        gridLayout->addWidget(Wave6, 7, 1, 1, 1);

        Spectrum8 = new QLineEdit(newwindow2);
        Spectrum8->setObjectName(QString::fromUtf8("Spectrum8"));

        gridLayout->addWidget(Spectrum8, 9, 2, 1, 1);

        label_5 = new QLabel(newwindow2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 3, 0, 1, 1);

        Wave8 = new QLineEdit(newwindow2);
        Wave8->setObjectName(QString::fromUtf8("Wave8"));

        gridLayout->addWidget(Wave8, 9, 1, 1, 1);

        label_10 = new QLabel(newwindow2);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout->addWidget(label_10, 8, 0, 1, 1);

        Wave7 = new QLineEdit(newwindow2);
        Wave7->setObjectName(QString::fromUtf8("Wave7"));

        gridLayout->addWidget(Wave7, 8, 1, 1, 1);

        Wave9 = new QLineEdit(newwindow2);
        Wave9->setObjectName(QString::fromUtf8("Wave9"));

        gridLayout->addWidget(Wave9, 10, 1, 1, 1);

        label_7 = new QLabel(newwindow2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 5, 0, 1, 1);

        CancelData = new QPushButton(newwindow2);
        CancelData->setObjectName(QString::fromUtf8("CancelData"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("../../svgsource/close-line.svg"), QSize(), QIcon::Normal, QIcon::Off);
        CancelData->setIcon(icon2);

        gridLayout->addWidget(CancelData, 11, 4, 1, 1);

        Spectrum1 = new QLineEdit(newwindow2);
        Spectrum1->setObjectName(QString::fromUtf8("Spectrum1"));

        gridLayout->addWidget(Spectrum1, 2, 2, 1, 1);

        Wave2 = new QLineEdit(newwindow2);
        Wave2->setObjectName(QString::fromUtf8("Wave2"));

        gridLayout->addWidget(Wave2, 3, 1, 1, 1);

        Spectrum7 = new QLineEdit(newwindow2);
        Spectrum7->setObjectName(QString::fromUtf8("Spectrum7"));

        gridLayout->addWidget(Spectrum7, 8, 2, 1, 1);

        Spectrum10 = new QLineEdit(newwindow2);
        Spectrum10->setObjectName(QString::fromUtf8("Spectrum10"));

        gridLayout->addWidget(Spectrum10, 11, 2, 1, 1);

        Spectrum6 = new QLineEdit(newwindow2);
        Spectrum6->setObjectName(QString::fromUtf8("Spectrum6"));

        gridLayout->addWidget(Spectrum6, 7, 2, 1, 1);

        label_12 = new QLabel(newwindow2);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout->addWidget(label_12, 10, 0, 1, 1);

        label_4 = new QLabel(newwindow2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        label_6 = new QLabel(newwindow2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 4, 0, 1, 1);

        label = new QLabel(newwindow2);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        label_9 = new QLabel(newwindow2);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout->addWidget(label_9, 7, 0, 1, 1);

        Spectrum2 = new QLineEdit(newwindow2);
        Spectrum2->setObjectName(QString::fromUtf8("Spectrum2"));

        gridLayout->addWidget(Spectrum2, 3, 2, 1, 1);

        Spectrum4 = new QLineEdit(newwindow2);
        Spectrum4->setObjectName(QString::fromUtf8("Spectrum4"));

        gridLayout->addWidget(Spectrum4, 5, 2, 1, 1);

        Wave3 = new QLineEdit(newwindow2);
        Wave3->setObjectName(QString::fromUtf8("Wave3"));

        gridLayout->addWidget(Wave3, 4, 1, 1, 1);

        Spectrum9 = new QLineEdit(newwindow2);
        Spectrum9->setObjectName(QString::fromUtf8("Spectrum9"));

        gridLayout->addWidget(Spectrum9, 10, 2, 1, 1);

        pushButton = new QPushButton(newwindow2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setLayoutDirection(Qt::LeftToRight);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("../../svgsource/chat-poll-line.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon3);
        pushButton->setFlat(true);

        gridLayout->addWidget(pushButton, 0, 0, 1, 1);

        label_11 = new QLabel(newwindow2);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout->addWidget(label_11, 9, 0, 1, 1);

        buttonInputStandard = new QPushButton(newwindow2);
        buttonInputStandard->setObjectName(QString::fromUtf8("buttonInputStandard"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8("../../svgsource/chat-forward-line.svg"), QSize(), QIcon::Normal, QIcon::Off);
        buttonInputStandard->setIcon(icon4);

        gridLayout->addWidget(buttonInputStandard, 0, 4, 1, 1);

        Spectrum3 = new QLineEdit(newwindow2);
        Spectrum3->setObjectName(QString::fromUtf8("Spectrum3"));

        gridLayout->addWidget(Spectrum3, 4, 2, 1, 1);

        Wave4 = new QLineEdit(newwindow2);
        Wave4->setObjectName(QString::fromUtf8("Wave4"));

        gridLayout->addWidget(Wave4, 5, 1, 1, 1);

        Spectrum5 = new QLineEdit(newwindow2);
        Spectrum5->setObjectName(QString::fromUtf8("Spectrum5"));

        gridLayout->addWidget(Spectrum5, 6, 2, 1, 1);

        label_8 = new QLabel(newwindow2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 6, 0, 1, 1);

        Wave5 = new QLineEdit(newwindow2);
        Wave5->setObjectName(QString::fromUtf8("Wave5"));

        gridLayout->addWidget(Wave5, 6, 1, 1, 1);

        label_3 = new QLabel(newwindow2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 1, 2, 1, 1);

        buttonCaOutput = new QPushButton(newwindow2);
        buttonCaOutput->setObjectName(QString::fromUtf8("buttonCaOutput"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8("../../svgsource/file-transfer-line.svg"), QSize(), QIcon::Normal, QIcon::Off);
        buttonCaOutput->setIcon(icon5);

        gridLayout->addWidget(buttonCaOutput, 1, 4, 1, 1);


        retranslateUi(newwindow2);

        QMetaObject::connectSlotsByName(newwindow2);
    } // setupUi

    void retranslateUi(QWidget *newwindow2)
    {
        newwindow2->setWindowTitle(QCoreApplication::translate("newwindow2", "\346\263\242\351\225\277\347\237\253\346\255\243", nullptr));
        AcceptData->setText(QCoreApplication::translate("newwindow2", "\347\241\256\345\256\232", nullptr));
        label_2->setText(QCoreApplication::translate("newwindow2", "\346\263\242\351\225\277", nullptr));
        label_13->setText(QCoreApplication::translate("newwindow2", "10", nullptr));
        label_5->setText(QCoreApplication::translate("newwindow2", "2", nullptr));
        label_10->setText(QCoreApplication::translate("newwindow2", "7", nullptr));
        label_7->setText(QCoreApplication::translate("newwindow2", "4", nullptr));
        CancelData->setText(QCoreApplication::translate("newwindow2", "\345\217\226\346\266\210", nullptr));
        label_12->setText(QCoreApplication::translate("newwindow2", "9", nullptr));
        label_4->setText(QCoreApplication::translate("newwindow2", "1", nullptr));
        label_6->setText(QCoreApplication::translate("newwindow2", "3", nullptr));
        label->setText(QCoreApplication::translate("newwindow2", "\345\272\217\345\217\267", nullptr));
        label_9->setText(QCoreApplication::translate("newwindow2", "6", nullptr));
        pushButton->setText(QCoreApplication::translate("newwindow2", "\350\276\223\345\205\245\345\217\202\346\225\260", nullptr));
        label_11->setText(QCoreApplication::translate("newwindow2", "8", nullptr));
        buttonInputStandard->setText(QCoreApplication::translate("newwindow2", "\345\257\274\345\205\245\345\217\202\346\225\260", nullptr));
        label_8->setText(QCoreApplication::translate("newwindow2", "5", nullptr));
        label_3->setText(QCoreApplication::translate("newwindow2", "\345\205\211\345\274\272", nullptr));
        buttonCaOutput->setText(QCoreApplication::translate("newwindow2", "\347\224\237\346\210\220Ca", nullptr));
    } // retranslateUi

};

namespace Ui {
    class newwindow2: public Ui_newwindow2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWWINDOW2_H
