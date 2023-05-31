/********************************************************************************
** Form generated from reading UI file 'InsConfigDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INSCONFIGDLG_H
#define UI_INSCONFIGDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InsConfigDlg
{
public:
    QLabel *label_3;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_6;
    QLineEdit *lineEdit_3;
    QLabel *label_7;
    QLineEdit *lineEdit_4;
    QLabel *label_8;
    QPushButton *btnok;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLabel *label_4;
    QLineEdit *lineEdit_2;
    QLabel *label_5;
    QWidget *widget2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_9;
    QLineEdit *lineEdit_5;
    QLabel *label_10;

    void setupUi(QDialog *InsConfigDlg)
    {
        if (InsConfigDlg->objectName().isEmpty())
            InsConfigDlg->setObjectName(QString::fromUtf8("InsConfigDlg"));
        InsConfigDlg->resize(512, 425);
        InsConfigDlg->setStyleSheet(QString::fromUtf8(""));
        label_3 = new QLabel(InsConfigDlg);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(70, 50, 381, 71));
        label_3->setMinimumSize(QSize(0, 0));
        label_3->setMaximumSize(QSize(683, 135));
        label_3->setLayoutDirection(Qt::LeftToRight);
        label_3->setStyleSheet(QString::fromUtf8("\n"
"font:20pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        label_3->setAlignment(Qt::AlignCenter);
        layoutWidget = new QWidget(InsConfigDlg);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(100, 220, 241, 29));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_3->addWidget(label_6);

        lineEdit_3 = new QLineEdit(layoutWidget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

        horizontalLayout_3->addWidget(lineEdit_3);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_3->addWidget(label_7);

        lineEdit_4 = new QLineEdit(layoutWidget);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));

        horizontalLayout_3->addWidget(lineEdit_4);

        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_3->addWidget(label_8);

        btnok = new QPushButton(InsConfigDlg);
        btnok->setObjectName(QString::fromUtf8("btnok"));
        btnok->setGeometry(QRect(170, 310, 161, 51));
        widget = new QWidget(InsConfigDlg);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(100, 130, 332, 29));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        comboBox = new QComboBox(widget);
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout->addWidget(comboBox);

        widget1 = new QWidget(InsConfigDlg);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(100, 180, 241, 29));
        horizontalLayout_2 = new QHBoxLayout(widget1);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(widget1);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        lineEdit = new QLineEdit(widget1);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout_2->addWidget(lineEdit);

        label_4 = new QLabel(widget1);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);

        lineEdit_2 = new QLineEdit(widget1);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        horizontalLayout_2->addWidget(lineEdit_2);

        label_5 = new QLabel(widget1);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_2->addWidget(label_5);

        widget2 = new QWidget(InsConfigDlg);
        widget2->setObjectName(QString::fromUtf8("widget2"));
        widget2->setGeometry(QRect(100, 260, 241, 29));
        horizontalLayout_4 = new QHBoxLayout(widget2);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_9 = new QLabel(widget2);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_4->addWidget(label_9);

        lineEdit_5 = new QLineEdit(widget2);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));

        horizontalLayout_4->addWidget(lineEdit_5);

        label_10 = new QLabel(widget2);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_4->addWidget(label_10);


        retranslateUi(InsConfigDlg);

        QMetaObject::connectSlotsByName(InsConfigDlg);
    } // setupUi

    void retranslateUi(QDialog *InsConfigDlg)
    {
        InsConfigDlg->setWindowTitle(QCoreApplication::translate("InsConfigDlg", "InsConfigDlg", nullptr));
        label_3->setText(QCoreApplication::translate("InsConfigDlg", "<html><head/><body><p>\346\203\257\345\257\274\345\210\235\345\247\213\345\217\202\346\225\260\350\243\205\350\256\242\345\217\212\347\261\273\345\236\213\351\200\211\346\213\251</p></body></html>", nullptr));
        label_6->setText(QCoreApplication::translate("InsConfigDlg", "\347\273\217   \345\272\246\357\274\232", nullptr));
        label_7->setText(QCoreApplication::translate("InsConfigDlg", "\345\272\246", nullptr));
        label_8->setText(QCoreApplication::translate("InsConfigDlg", "\345\210\206", nullptr));
        btnok->setText(QCoreApplication::translate("InsConfigDlg", "\347\241\256\345\256\232", nullptr));
        label->setText(QCoreApplication::translate("InsConfigDlg", "\346\203\257\345\257\274\346\265\213\350\257\225\347\261\273\345\236\213", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("InsConfigDlg", "\346\203\257\345\257\274\351\200\232\351\241\271", nullptr));

        label_2->setText(QCoreApplication::translate("InsConfigDlg", "\347\272\254   \345\272\246\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("InsConfigDlg", "\345\272\246", nullptr));
        label_5->setText(QCoreApplication::translate("InsConfigDlg", "\345\210\206", nullptr));
        label_9->setText(QCoreApplication::translate("InsConfigDlg", "\346\265\267\346\213\224\351\253\230\357\274\232", nullptr));
        label_10->setText(QCoreApplication::translate("InsConfigDlg", "m", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InsConfigDlg: public Ui_InsConfigDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSCONFIGDLG_H
