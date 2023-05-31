/********************************************************************************
** Form generated from reading UI file 'AutoTestWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTOTESTWIDGET_H
#define UI_AUTOTESTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AutoTestWidget
{
public:
    QHBoxLayout *horizontalLayout;

    void setupUi(QWidget *AutoTestWidget)
    {
        if (AutoTestWidget->objectName().isEmpty())
            AutoTestWidget->setObjectName(QString::fromUtf8("AutoTestWidget"));
        AutoTestWidget->resize(628, 513);
        AutoTestWidget->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	font-family:Microsoft Yahei;\n"
"    font-size:10pt;\n"
"background-image: url();\n"
"	color: rgb(90, 90, 90);\n"
"}\n"
""));
        horizontalLayout = new QHBoxLayout(AutoTestWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));

        retranslateUi(AutoTestWidget);

        QMetaObject::connectSlotsByName(AutoTestWidget);
    } // setupUi

    void retranslateUi(QWidget *AutoTestWidget)
    {
        AutoTestWidget->setWindowTitle(QCoreApplication::translate("AutoTestWidget", "AutoTestWidget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AutoTestWidget: public Ui_AutoTestWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTOTESTWIDGET_H
