/********************************************************************************
** Form generated from reading UI file 'MessageBoxDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESSAGEBOXDLG_H
#define UI_MESSAGEBOXDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_MessageBoxDlg
{
public:
    QLabel *label_3;
    QPushButton *pushButton;

    void setupUi(QDialog *MessageBoxDlg)
    {
        if (MessageBoxDlg->objectName().isEmpty())
            MessageBoxDlg->setObjectName(QString::fromUtf8("MessageBoxDlg"));
        MessageBoxDlg->resize(514, 425);
        MessageBoxDlg->setStyleSheet(QString::fromUtf8(""));
        label_3 = new QLabel(MessageBoxDlg);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 90, 491, 121));
        label_3->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	font-family:Microsoft Yahei;\n"
"    font-size:20pt;\n"
"	background-image: url();\n"
"}"));
        label_3->setAlignment(Qt::AlignCenter);
        pushButton = new QPushButton(MessageBoxDlg);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(160, 220, 218, 68));

        retranslateUi(MessageBoxDlg);

        QMetaObject::connectSlotsByName(MessageBoxDlg);
    } // setupUi

    void retranslateUi(QDialog *MessageBoxDlg)
    {
        MessageBoxDlg->setWindowTitle(QCoreApplication::translate("MessageBoxDlg", "MessageBoxDlg", nullptr));
        label_3->setText(QCoreApplication::translate("MessageBoxDlg", "<html><head/><body><p><span style=\" font-size:20pt; font-weight:600;\">\346\216\245\351\200\232\347\273\274\345\220\210\347\224\265\346\272\220</span></p></body></html>", nullptr));
        pushButton->setText(QCoreApplication::translate("MessageBoxDlg", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MessageBoxDlg: public Ui_MessageBoxDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESSAGEBOXDLG_H
