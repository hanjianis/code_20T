/********************************************************************************
** Form generated from reading UI file 'MyToolTipDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYTOOLTIPDLG_H
#define UI_MYTOOLTIPDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyToolTipDlg
{
public:
    QLabel *label;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *MyToolTipDlg)
    {
        if (MyToolTipDlg->objectName().isEmpty())
            MyToolTipDlg->setObjectName(QString::fromUtf8("MyToolTipDlg"));
        MyToolTipDlg->resize(299, 131);
        MyToolTipDlg->setStyleSheet(QString::fromUtf8("QDialog{\n"
"	background-image: url();\n"
"}\n"
"\n"
"QPushButton{\n"
"  font-family:Microsoft Yahei;\n"
"    font-size:12pt;\n"
"	\n"
"	border:1px solid;\n"
"	border-image: url();\n"
"}QLabel{\n"
"	font-family:Microsoft Yahei;\n"
"    font-size:12pt;\n"
"background-image: url();\n"
"}"));
        label = new QLabel(MyToolTipDlg);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(9, 9, 281, 71));
        label->setStyleSheet(QString::fromUtf8(""));
        label->setAlignment(Qt::AlignCenter);
        widget = new QWidget(MyToolTipDlg);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 100, 281, 25));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        retranslateUi(MyToolTipDlg);

        QMetaObject::connectSlotsByName(MyToolTipDlg);
    } // setupUi

    void retranslateUi(QDialog *MyToolTipDlg)
    {
        MyToolTipDlg->setWindowTitle(QCoreApplication::translate("MyToolTipDlg", "MyToolTipDlg", nullptr));
        label->setText(QCoreApplication::translate("MyToolTipDlg", "content", nullptr));
        pushButton->setText(QCoreApplication::translate("MyToolTipDlg", "O K", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyToolTipDlg: public Ui_MyToolTipDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYTOOLTIPDLG_H
