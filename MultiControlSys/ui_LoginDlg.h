/********************************************************************************
** Form generated from reading UI file 'LoginDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDLG_H
#define UI_LOGINDLG_H

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

class Ui_LoginDlg
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *btnok;
    QPushButton *btncancel;
    QLabel *tips;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLineEdit *lineEdit_3;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QComboBox *comboBox;
    QLabel *label_3;

    void setupUi(QDialog *LoginDlg)
    {
        if (LoginDlg->objectName().isEmpty())
            LoginDlg->setObjectName(QString::fromUtf8("LoginDlg"));
        LoginDlg->resize(514, 425);
        LoginDlg->setStyleSheet(QString::fromUtf8("QDialog{\n"
"	background-image: url(:/MultiControlSys/res/dbk.png);\n"
"}"));
        layoutWidget = new QWidget(LoginDlg);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(100, 77, 301, 40));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(layoutWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        layoutWidget1 = new QWidget(LoginDlg);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(50, 240, 440, 61));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_5->setSpacing(80);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(50, 0, 50, 0);
        btnok = new QPushButton(layoutWidget1);
        btnok->setObjectName(QString::fromUtf8("btnok"));
        btnok->setEnabled(true);
        QFont font;
        font.setBold(true);
        btnok->setFont(font);

        horizontalLayout_5->addWidget(btnok);

        btncancel = new QPushButton(layoutWidget1);
        btncancel->setObjectName(QString::fromUtf8("btncancel"));
        btncancel->setFont(font);

        horizontalLayout_5->addWidget(btncancel);

        tips = new QLabel(LoginDlg);
        tips->setObjectName(QString::fromUtf8("tips"));
        tips->setGeometry(QRect(70, 310, 391, 41));
        tips->setFont(font);
        layoutWidget2 = new QWidget(LoginDlg);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(100, 200, 301, 40));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        lineEdit_3 = new QLineEdit(layoutWidget2);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

        horizontalLayout_4->addWidget(lineEdit_3);

        layoutWidget3 = new QWidget(LoginDlg);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(100, 120, 301, 40));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget3);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        lineEdit_2 = new QLineEdit(layoutWidget3);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        horizontalLayout_2->addWidget(lineEdit_2);

        comboBox = new QComboBox(LoginDlg);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(290, 161, 105, 39));
        label_3 = new QLabel(LoginDlg);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(101, 161, 171, 31));
        label_3->setStyleSheet(QString::fromUtf8(""));

        retranslateUi(LoginDlg);

        QMetaObject::connectSlotsByName(LoginDlg);
    } // setupUi

    void retranslateUi(QDialog *LoginDlg)
    {
        LoginDlg->setWindowTitle(QCoreApplication::translate("LoginDlg", "LoginDlg", nullptr));
        label->setText(QCoreApplication::translate("LoginDlg", "\347\224\250\346\210\267\345\247\223\345\220\215", nullptr));
        lineEdit->setText(QCoreApplication::translate("LoginDlg", "         user", nullptr));
        btnok->setText(QCoreApplication::translate("LoginDlg", "\347\241\256\345\256\232", nullptr));
        btncancel->setText(QCoreApplication::translate("LoginDlg", "\345\217\226\346\266\210", nullptr));
        tips->setText(QString());
        label_4->setText(QCoreApplication::translate("LoginDlg", "\345\257\274\345\274\271\345\217\267  ", nullptr));
        lineEdit_3->setText(QCoreApplication::translate("LoginDlg", "1701013", nullptr));
        label_2->setText(QCoreApplication::translate("LoginDlg", "\347\224\250\346\210\267\345\217\243\344\273\244", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("LoginDlg", "\346\210\230\346\226\227\345\274\271", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("LoginDlg", "\346\203\260\346\200\247\345\274\271", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("LoginDlg", "\351\201\245\346\265\213\345\274\271", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("LoginDlg", "\350\256\255\347\273\203\345\274\271", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("LoginDlg", "\345\257\274\345\274\271", nullptr));

        label_3->setText(QCoreApplication::translate("LoginDlg", "\345\257\274\345\274\271\345\236\213\345\217\267/\347\212\266\346\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDlg: public Ui_LoginDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDLG_H
