/********************************************************************************
** Form generated from reading UI file 'MultiControlSys.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MULTICONTROLSYS_H
#define UI_MULTICONTROLSYS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MultiControlSysClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QPushButton *btnparam;
    QPushButton *btntest;
    QPushButton *btnself_check;
    QPushButton *btnauto_test;
    QPushButton *btn_history;
    QPushButton *btn_manage;
    QPushButton *btn_qiangding;
    QPushButton *btn_help;
    QPushButton *quit;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *verticalLayout_2;
    QLabel *lable_date;
    QLabel *lable_time;
    QFrame *line;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_8;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_9;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_10;
    QLineEdit *lineEdit;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QMainWindow *MultiControlSysClass)
    {
        if (MultiControlSysClass->objectName().isEmpty())
            MultiControlSysClass->setObjectName(QString::fromUtf8("MultiControlSysClass"));
        MultiControlSysClass->resize(727, 570);
        MultiControlSysClass->setMinimumSize(QSize(0, 0));
        MultiControlSysClass->setMaximumSize(QSize(1280, 1024));
        centralWidget = new QWidget(MultiControlSysClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setMinimumSize(QSize(0, 0));
        centralWidget->setMaximumSize(QSize(1280, 1024));
        centralWidget->setStyleSheet(QString::fromUtf8(""));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(683, 135));
        label_3->setMaximumSize(QSize(683, 135));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(40);
        font.setBold(false);
        font.setItalic(false);
        label_3->setFont(font);
        label_3->setStyleSheet(QString::fromUtf8("image: url(:/MultiControlSys/res/title.png);\n"
"font: 40pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);


        gridLayout->addWidget(widget, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(50, -1, 50, -1);
        btnparam = new QPushButton(centralWidget);
        btnparam->setObjectName(QString::fromUtf8("btnparam"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setKerning(false);
        btnparam->setFont(font1);
        btnparam->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(btnparam);

        btntest = new QPushButton(centralWidget);
        btntest->setObjectName(QString::fromUtf8("btntest"));
        btntest->setFont(font1);
        btntest->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(btntest);

        btnself_check = new QPushButton(centralWidget);
        btnself_check->setObjectName(QString::fromUtf8("btnself_check"));
        btnself_check->setFont(font1);
        btnself_check->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(btnself_check);

        btnauto_test = new QPushButton(centralWidget);
        btnauto_test->setObjectName(QString::fromUtf8("btnauto_test"));
        btnauto_test->setFont(font1);
        btnauto_test->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(btnauto_test);

        btn_history = new QPushButton(centralWidget);
        btn_history->setObjectName(QString::fromUtf8("btn_history"));
        btn_history->setFont(font1);
        btn_history->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(btn_history);

        btn_manage = new QPushButton(centralWidget);
        btn_manage->setObjectName(QString::fromUtf8("btn_manage"));
        btn_manage->setFont(font1);
        btn_manage->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(btn_manage);

        btn_qiangding = new QPushButton(centralWidget);
        btn_qiangding->setObjectName(QString::fromUtf8("btn_qiangding"));
        btn_qiangding->setFont(font1);
        btn_qiangding->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(btn_qiangding);

        btn_help = new QPushButton(centralWidget);
        btn_help->setObjectName(QString::fromUtf8("btn_help"));
        btn_help->setFont(font1);
        btn_help->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(btn_help);

        quit = new QPushButton(centralWidget);
        quit->setObjectName(QString::fromUtf8("quit"));
        quit->setFont(font1);
        quit->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(quit);


        horizontalLayout->addLayout(verticalLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(0, 0));
        label_2->setMaximumSize(QSize(500, 500));
        label_2->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(label_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(50, -1, 50, -1);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, 50, -1, -1);
        lable_date = new QLabel(centralWidget);
        lable_date->setObjectName(QString::fromUtf8("lable_date"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font2.setPointSize(16);
        font2.setBold(false);
        font2.setItalic(false);
        lable_date->setFont(font2);
        lable_date->setStyleSheet(QString::fromUtf8("font: 16pt \"\346\245\267\344\275\223\";"));
        lable_date->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(lable_date);

        lable_time = new QLabel(centralWidget);
        lable_time->setObjectName(QString::fromUtf8("lable_time"));
        lable_time->setStyleSheet(QString::fromUtf8("font: 16pt \"\346\245\267\344\275\223\";"));
        lable_time->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(lable_time);


        verticalLayout_7->addLayout(verticalLayout_2);

        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_7->addWidget(line);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setStyleSheet(QString::fromUtf8(""));
        label_5->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label_5);

        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setStyleSheet(QString::fromUtf8("font: 16pt \"\346\245\267\344\275\223\";"));
        label_6->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label_6);

        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setStyleSheet(QString::fromUtf8("font: 16pt \"\346\245\267\344\275\223\";"));
        label_7->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label_7);


        verticalLayout_7->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(label_8);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        QFont font3;
        font3.setPointSize(12);
        font3.setBold(true);
        font3.setUnderline(true);
        label_9->setFont(font3);
        label_9->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_9);


        verticalLayout_6->addLayout(verticalLayout_3);


        verticalLayout_7->addLayout(verticalLayout_6);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(-1, -1, -1, 0);
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(label_10);

        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setEnabled(false);
        lineEdit->setStyleSheet(QString::fromUtf8("QLineEdit:disabled {\n"
"\n"
"    background-color: #C4C4C4;\n"
"    border: 1px solid;\n"
"    margin: 0px;\n"
"}"));
        lineEdit->setAlignment(Qt::AlignCenter);
        lineEdit->setDragEnabled(true);
        lineEdit->setCursorMoveStyle(Qt::LogicalMoveStyle);
        lineEdit->setClearButtonEnabled(false);

        verticalLayout_4->addWidget(lineEdit);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_2);


        verticalLayout_7->addLayout(verticalLayout_4);


        horizontalLayout->addLayout(verticalLayout_7);

        horizontalLayout->setStretch(2, 1);

        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        MultiControlSysClass->setCentralWidget(centralWidget);

        retranslateUi(MultiControlSysClass);

        QMetaObject::connectSlotsByName(MultiControlSysClass);
    } // setupUi

    void retranslateUi(QMainWindow *MultiControlSysClass)
    {
        MultiControlSysClass->setWindowTitle(QCoreApplication::translate("MultiControlSysClass", "MultiControlSys", nullptr));
        label_3->setText(QCoreApplication::translate("MultiControlSysClass", "<html><head/><body><p><span style=\" font-size:18pt; font-weight:600;\">EZ-20T\351\200\232\347\224\250\350\260\203\350\257\225\350\256\276\345\244\207</span></p></body></html>", nullptr));
        btnparam->setText(QCoreApplication::translate("MultiControlSysClass", "\345\217\202 \346\225\260 \350\256\276 \347\275\256", nullptr));
        btntest->setText(QCoreApplication::translate("MultiControlSysClass", "\346\211\213 \345\212\250 \346\265\213 \350\257\225", nullptr));
        btnself_check->setText(QCoreApplication::translate("MultiControlSysClass", "\347\263\273 \347\273\237 \350\207\252 \346\243\200", nullptr));
        btnauto_test->setText(QCoreApplication::translate("MultiControlSysClass", "\350\207\252 \345\212\250 \346\265\213 \350\257\225", nullptr));
        btn_history->setText(QCoreApplication::translate("MultiControlSysClass", "\346\225\260 \346\215\256 \345\244\204 \347\220\206", nullptr));
        btn_manage->setText(QCoreApplication::translate("MultiControlSysClass", "\347\273\264 \346\212\244 \347\256\241 \347\220\206", nullptr));
        btn_qiangding->setText(QCoreApplication::translate("MultiControlSysClass", "\350\256\241 \351\207\217 \346\212\242 \345\256\232", nullptr));
        btn_help->setText(QCoreApplication::translate("MultiControlSysClass", "\345\234\250 \347\272\277 \345\270\256 \345\212\251", nullptr));
        quit->setText(QCoreApplication::translate("MultiControlSysClass", "\351\200\200 \345\207\272", nullptr));
        label_2->setText(QString());
        lable_date->setText(QCoreApplication::translate("MultiControlSysClass", "2020\345\271\26410\346\234\21015\346\227\245", nullptr));
        lable_time->setText(QCoreApplication::translate("MultiControlSysClass", "08\357\274\23236\357\274\23248", nullptr));
        label_5->setText(QCoreApplication::translate("MultiControlSysClass", "\350\242\253\346\265\213\345\257\271\350\261\241\345\236\213\345\217\267", nullptr));
        label_6->setText(QCoreApplication::translate("MultiControlSysClass", "YJ-12", nullptr));
        label_7->setText(QCoreApplication::translate("MultiControlSysClass", "XX-XX", nullptr));
        label_8->setText(QCoreApplication::translate("MultiControlSysClass", "\350\242\253\346\265\213\345\257\271\350\261\241\347\274\226\345\217\267", nullptr));
        label_9->setText(QCoreApplication::translate("MultiControlSysClass", "000000", nullptr));
        label_10->setText(QCoreApplication::translate("MultiControlSysClass", "\347\263\273\347\273\237\345\267\245\344\275\234\346\227\266\351\227\264", nullptr));
        lineEdit->setText(QCoreApplication::translate("MultiControlSysClass", "322:35:39", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MultiControlSysClass: public Ui_MultiControlSysClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MULTICONTROLSYS_H
