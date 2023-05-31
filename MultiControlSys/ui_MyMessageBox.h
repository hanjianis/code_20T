/********************************************************************************
** Form generated from reading UI file 'MyMessageBox.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYMESSAGEBOX_H
#define UI_MYMESSAGEBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_MyMessageBox
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnyes;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnno;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QDialog *MyMessageBox)
    {
        if (MyMessageBox->objectName().isEmpty())
            MyMessageBox->setObjectName(QString::fromUtf8("MyMessageBox"));
        MyMessageBox->resize(505, 129);
        MyMessageBox->setStyleSheet(QString::fromUtf8("QDialog{\n"
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
        verticalLayout = new QVBoxLayout(MyMessageBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(MyMessageBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnyes = new QPushButton(MyMessageBox);
        btnyes->setObjectName(QString::fromUtf8("btnyes"));
        btnyes->setMaximumSize(QSize(16777215, 23));

        horizontalLayout->addWidget(btnyes);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        btnno = new QPushButton(MyMessageBox);
        btnno->setObjectName(QString::fromUtf8("btnno"));
        btnno->setMaximumSize(QSize(16777215, 23));

        horizontalLayout->addWidget(btnno);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout);

        verticalLayout->setStretch(0, 1);

        retranslateUi(MyMessageBox);

        QMetaObject::connectSlotsByName(MyMessageBox);
    } // setupUi

    void retranslateUi(QDialog *MyMessageBox)
    {
        MyMessageBox->setWindowTitle(QCoreApplication::translate("MyMessageBox", "MyMessageBox", nullptr));
        label->setText(QCoreApplication::translate("MyMessageBox", "content", nullptr));
        btnyes->setText(QCoreApplication::translate("MyMessageBox", "Yes", nullptr));
        btnno->setText(QCoreApplication::translate("MyMessageBox", "No", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyMessageBox: public Ui_MyMessageBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYMESSAGEBOX_H
