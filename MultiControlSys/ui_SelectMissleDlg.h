/********************************************************************************
** Form generated from reading UI file 'SelectMissleDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTMISSLEDLG_H
#define UI_SELECTMISSLEDLG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectMissleDlg
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_3;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBox;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_2;
    QToolButton *quit;
    QToolButton *toolButton_3;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_2;
    QWidget *widget_7;
    QHBoxLayout *horizontalLayout_7;

    void setupUi(QDialog *SelectMissleDlg)
    {
        if (SelectMissleDlg->objectName().isEmpty())
            SelectMissleDlg->setObjectName(QString::fromUtf8("SelectMissleDlg"));
        SelectMissleDlg->resize(884, 794);
        SelectMissleDlg->setMinimumSize(QSize(0, 0));
        SelectMissleDlg->setMaximumSize(QSize(1280, 1024));
        QFont font;
        font.setPointSize(9);
        SelectMissleDlg->setFont(font);
        SelectMissleDlg->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(SelectMissleDlg);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new QWidget(SelectMissleDlg);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMaximumSize(QSize(1280, 1024));
        horizontalLayout_6 = new QHBoxLayout(widget);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(683, 135));
        label_3->setMaximumSize(QSize(683, 135));
        label_3->setLayoutDirection(Qt::LeftToRight);
        label_3->setStyleSheet(QString::fromUtf8("border-image: url(:/MultiControlSys/res/title.png);\n"
"font: 40pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        label_3->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(label_3);


        verticalLayout->addWidget(widget);

        widget_3 = new QWidget(SelectMissleDlg);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        horizontalLayout_2 = new QHBoxLayout(widget_3);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(widget_3);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font1.setPointSize(25);
        font1.setBold(false);
        font1.setItalic(false);
        label->setFont(font1);
        label->setStyleSheet(QString::fromUtf8("font: 25pt \"\346\245\267\344\275\223\";"));
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label);


        verticalLayout->addWidget(widget_3);

        widget_2 = new QWidget(SelectMissleDlg);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        comboBox = new QComboBox(widget_2);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setMaximumSize(QSize(300, 30));
        QFont font2;
        font2.setPointSize(16);
        font2.setBold(true);
        comboBox->setFont(font2);
        comboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        horizontalLayout->addWidget(comboBox);


        verticalLayout->addWidget(widget_2);

        widget_4 = new QWidget(SelectMissleDlg);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        horizontalLayout_3 = new QHBoxLayout(widget_4);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pushButton = new QPushButton(widget_4);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMaximumSize(QSize(218, 68));
        QFont font3;
        font3.setPointSize(16);
        pushButton->setFont(font3);

        horizontalLayout_3->addWidget(pushButton);


        verticalLayout->addWidget(widget_4);

        widget_5 = new QWidget(SelectMissleDlg);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        horizontalLayout_4 = new QHBoxLayout(widget_5);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, -1, 100, -1);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        quit = new QToolButton(widget_5);
        quit->setObjectName(QString::fromUtf8("quit"));
        quit->setMaximumSize(QSize(250, 66));
        quit->setStyleSheet(QString::fromUtf8(""));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/MultiControlSys/res/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        quit->setIcon(icon);
        quit->setIconSize(QSize(64, 66));
        quit->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        verticalLayout_2->addWidget(quit);

        toolButton_3 = new QToolButton(widget_5);
        toolButton_3->setObjectName(QString::fromUtf8("toolButton_3"));
        toolButton_3->setMaximumSize(QSize(250, 66));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/MultiControlSys/res/end.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_3->setIcon(icon1);
        toolButton_3->setIconSize(QSize(64, 66));
        toolButton_3->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        verticalLayout_2->addWidget(toolButton_3);


        horizontalLayout_4->addLayout(verticalLayout_2);


        verticalLayout->addWidget(widget_5);

        widget_6 = new QWidget(SelectMissleDlg);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));
        QFont font4;
        font4.setPointSize(26);
        widget_6->setFont(font4);
        horizontalLayout_5 = new QHBoxLayout(widget_6);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_2 = new QLabel(widget_6);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font5;
        font5.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
        font5.setPointSize(30);
        font5.setBold(false);
        font5.setItalic(false);
        label_2->setFont(font5);
        label_2->setStyleSheet(QString::fromUtf8("QLabel{	\n"
"	color: rgb(0, 85, 255);	\n"
"font: 30pt \"Microsoft YaHei UI\";\n"
"}\n"
""));
        label_2->setTextFormat(Qt::RichText);
        label_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(label_2);


        verticalLayout->addWidget(widget_6);

        widget_7 = new QWidget(SelectMissleDlg);
        widget_7->setObjectName(QString::fromUtf8("widget_7"));
        horizontalLayout_7 = new QHBoxLayout(widget_7);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));

        verticalLayout->addWidget(widget_7);


        retranslateUi(SelectMissleDlg);

        QMetaObject::connectSlotsByName(SelectMissleDlg);
    } // setupUi

    void retranslateUi(QDialog *SelectMissleDlg)
    {
        SelectMissleDlg->setWindowTitle(QCoreApplication::translate("SelectMissleDlg", "SelectMissleDlg", nullptr));
        label_3->setText(QCoreApplication::translate("SelectMissleDlg", "<html><head/><body><p><span style=\" font-size:18pt; font-weight:600;\">EZ-20T\351\200\232\347\224\250\346\265\213\350\257\225\350\256\276\345\244\207</span></p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("SelectMissleDlg", "\351\200\211\346\213\251\345\257\274\345\274\271\345\236\213\345\217\267", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("SelectMissleDlg", "\350\257\267\351\200\211\346\213\251\346\265\213\350\257\225\350\275\257\344\273\266", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("SelectMissleDlg", "K/AKD63B", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("SelectMissleDlg", "K/AKD63BBD2", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("SelectMissleDlg", "K/AKD20", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("SelectMissleDlg", "YJ-12", nullptr));
        comboBox->setItemText(5, QCoreApplication::translate("SelectMissleDlg", "AKF21", nullptr));
        comboBox->setItemText(6, QCoreApplication::translate("SelectMissleDlg", "AKF063C", nullptr));
        comboBox->setItemText(7, QCoreApplication::translate("SelectMissleDlg", "AKF20A", nullptr));

        pushButton->setText(QCoreApplication::translate("SelectMissleDlg", "\347\241\256\345\256\232", nullptr));
        quit->setText(QCoreApplication::translate("SelectMissleDlg", "\351\200\200\345\207\272\350\275\257\344\273\266", nullptr));
        toolButton_3->setText(QCoreApplication::translate("SelectMissleDlg", "\345\205\263\346\234\272", nullptr));
        label_2->setText(QCoreApplication::translate("SelectMissleDlg", "\344\270\255\345\233\275\350\210\252\345\244\251\347\247\221\345\267\245\351\233\206\345\233\242\347\254\254\344\270\211\347\240\224\347\251\266\351\231\242\346\200\273\344\275\223\350\256\276\350\256\241\351\203\250\347\240\224\345\210\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectMissleDlg: public Ui_SelectMissleDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTMISSLEDLG_H
