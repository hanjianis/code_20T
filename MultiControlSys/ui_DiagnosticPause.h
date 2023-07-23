/********************************************************************************
** Form generated from reading UI file 'DiagnosticPause.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIAGNOSTICPAUSE_H
#define UI_DIAGNOSTICPAUSE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DiagnosticPause
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;

    void setupUi(QDialog *DiagnosticPause)
    {
        if (DiagnosticPause->objectName().isEmpty())
            DiagnosticPause->setObjectName(QString::fromUtf8("DiagnosticPause"));
        DiagnosticPause->resize(514, 327);
        pushButton = new QPushButton(DiagnosticPause);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(120, 240, 111, 51));
        pushButton_2 = new QPushButton(DiagnosticPause);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(300, 240, 101, 51));
        label = new QLabel(DiagnosticPause);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(170, 110, 201, 71));
        QFont font;
        font.setPointSize(24);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(true);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("font:24pt"));

        retranslateUi(DiagnosticPause);

        QMetaObject::connectSlotsByName(DiagnosticPause);
    } // setupUi

    void retranslateUi(QDialog *DiagnosticPause)
    {
        DiagnosticPause->setWindowTitle(QCoreApplication::translate("DiagnosticPause", "Dialog", nullptr));
        pushButton->setText(QCoreApplication::translate("DiagnosticPause", "\347\241\256\345\256\232", nullptr));
        pushButton_2->setText(QCoreApplication::translate("DiagnosticPause", "\345\217\226\346\266\210", nullptr));
        label->setText(QCoreApplication::translate("DiagnosticPause", " \346\232\202\345\201\234\346\265\213\350\257\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DiagnosticPause: public Ui_DiagnosticPause {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIAGNOSTICPAUSE_H
