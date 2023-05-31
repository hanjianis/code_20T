/********************************************************************************
** Form generated from reading UI file 'InputTemperatureDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTTEMPERATUREDLG_H
#define UI_INPUTTEMPERATUREDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InputTemperatureDlg
{
public:
    QLabel *label;
    QPushButton *pushButton;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QLabel *label_2;

    void setupUi(QDialog *InputTemperatureDlg)
    {
        if (InputTemperatureDlg->objectName().isEmpty())
            InputTemperatureDlg->setObjectName(QString::fromUtf8("InputTemperatureDlg"));
        InputTemperatureDlg->resize(514, 425);
        InputTemperatureDlg->setStyleSheet(QString::fromUtf8("QDialog{\n"
"	background-image: url(:/MultiControlSys/res/dbk.png);\n"
"}\n"
"QLabel{\n"
"	font-family:Microsoft Yahei;\n"
"    font-size:20pt;\n"
"background-image: url();\n"
"}\n"
"QPushButton{\n"
"    font-family:Microsoft Yahei;\n"
"    font-size:20pt;\n"
"	width:218px;\n"
"	height:80px;\n"
"	border-radius:8px;\n"
"	border-image: url(:/MultiControlSys/res/btn.png);\n"
"}"));
        label = new QLabel(InputTemperatureDlg);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(100, 110, 271, 41));
        pushButton = new QPushButton(InputTemperatureDlg);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(170, 290, 151, 51));
        widget = new QWidget(InputTemperatureDlg);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(150, 180, 211, 62));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setMinimumSize(QSize(0, 60));
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft YaHei"));
        font.setPointSize(40);
        lineEdit->setFont(font);

        horizontalLayout->addWidget(lineEdit);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(40, 40));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Microsoft Yahei"));
        font1.setPointSize(20);
        label_2->setFont(font1);
        label_2->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
"color: rgb(85, 255, 127);"));

        horizontalLayout->addWidget(label_2);


        retranslateUi(InputTemperatureDlg);

        QMetaObject::connectSlotsByName(InputTemperatureDlg);
    } // setupUi

    void retranslateUi(QDialog *InputTemperatureDlg)
    {
        InputTemperatureDlg->setWindowTitle(QCoreApplication::translate("InputTemperatureDlg", "InputTemperatureDlg", nullptr));
        label->setText(QCoreApplication::translate("InputTemperatureDlg", "\350\257\267\350\276\223\345\205\245\345\275\223\345\211\215\346\270\251\345\272\246\357\274\232", nullptr));
        pushButton->setText(QCoreApplication::translate("InputTemperatureDlg", "\347\241\256\345\256\232", nullptr));
        lineEdit->setText(QCoreApplication::translate("InputTemperatureDlg", "20.00", nullptr));
        label_2->setText(QCoreApplication::translate("InputTemperatureDlg", "\342\204\203", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InputTemperatureDlg: public Ui_InputTemperatureDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTTEMPERATUREDLG_H
