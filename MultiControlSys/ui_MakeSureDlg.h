/********************************************************************************
** Form generated from reading UI file 'MakeSureDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAKESUREDLG_H
#define UI_MAKESUREDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MakeSureDlg
{
public:
    QLabel *label_2;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_4;
    QLabel *label_3;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_5;
    QLabel *label_6;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer;
    QPushButton *ok;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *cancel;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *MakeSureDlg)
    {
        if (MakeSureDlg->objectName().isEmpty())
            MakeSureDlg->setObjectName(QString::fromUtf8("MakeSureDlg"));
        MakeSureDlg->resize(514, 425);
        MakeSureDlg->setMaximumSize(QSize(514, 425));
        MakeSureDlg->setStyleSheet(QString::fromUtf8("QDialog{\n"
"	background-image: url(:/MultiControlSys/res/dbk.png);\n"
"}"));
        label_2 = new QLabel(MakeSureDlg);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(60, 90, 391, 33));
        QFont font;
        font.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font.setPointSize(25);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(true);
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8("font: 25pt \"\346\245\267\344\275\223\";"));
        layoutWidget = new QWidget(MakeSureDlg);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(61, 150, 298, 35));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font1.setPointSize(20);
        label_4->setFont(font1);

        horizontalLayout->addWidget(label_4);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font1);

        horizontalLayout->addWidget(label_3);

        layoutWidget1 = new QWidget(MakeSureDlg);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(61, 200, 281, 35));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(layoutWidget1);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font1);

        horizontalLayout_2->addWidget(label_5);

        label_6 = new QLabel(layoutWidget1);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font1);

        horizontalLayout_2->addWidget(label_6);

        layoutWidget2 = new QWidget(MakeSureDlg);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(70, 260, 351, 81));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        ok = new QPushButton(layoutWidget2);
        ok->setObjectName(QString::fromUtf8("ok"));
        QFont font2;
        font2.setBold(true);
        ok->setFont(font2);

        horizontalLayout_5->addWidget(ok);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);

        cancel = new QPushButton(layoutWidget2);
        cancel->setObjectName(QString::fromUtf8("cancel"));
        cancel->setFont(font2);

        horizontalLayout_5->addWidget(cancel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);


        retranslateUi(MakeSureDlg);

        QMetaObject::connectSlotsByName(MakeSureDlg);
    } // setupUi

    void retranslateUi(QDialog *MakeSureDlg)
    {
        MakeSureDlg->setWindowTitle(QCoreApplication::translate("MakeSureDlg", "MakeSureDlg", nullptr));
        label_2->setText(QCoreApplication::translate("MakeSureDlg", "\350\257\267\347\241\256\350\256\244\345\276\205\346\265\213\345\257\274\345\274\271\344\277\241\346\201\257\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("MakeSureDlg", "\345\257\274\345\274\271\345\236\213\345\217\267\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("MakeSureDlg", "K/AKD20", nullptr));
        label_5->setText(QCoreApplication::translate("MakeSureDlg", "\345\257\274\345\274\271\345\274\271\345\217\267\357\274\232", nullptr));
        label_6->setText(QCoreApplication::translate("MakeSureDlg", "000000", nullptr));
        ok->setText(QCoreApplication::translate("MakeSureDlg", "\347\241\256\345\256\232", nullptr));
        cancel->setText(QCoreApplication::translate("MakeSureDlg", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MakeSureDlg: public Ui_MakeSureDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAKESUREDLG_H
