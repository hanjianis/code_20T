/********************************************************************************
** Form generated from reading UI file 'HistoryDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HISTORYDLG_H
#define UI_HISTORYDLG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HistoryDlg
{
public:
    QVBoxLayout *verticalLayout_9;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_13;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout_10;
    QLabel *lable_date;
    QLabel *lable_time;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_7;
    QDateEdit *dateEdit;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QComboBox *comboBox_2;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_8;
    QComboBox *comboBox_7;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QComboBox *comboBox_4;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_9;
    QComboBox *comboBox_8;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_10;
    QComboBox *comboBox_9;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QComboBox *comboBox_3;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QComboBox *comboBox_5;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_11;
    QSpacerItem *horizontalSpacer_5;
    QToolButton *query;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_14;
    QCheckBox *checkBox;
    QLabel *label_12;
    QSpacerItem *horizontalSpacer;
    QListWidget *listWidget;
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *verticalLayout_6;
    QPushButton *btn_open;
    QPushButton *btn_close;
    QPushButton *btn_pailie;
    QPushButton *btn_compare;
    QPushButton *btn_export;
    QPushButton *btn_printf;
    QPushButton *btn_del;
    QPushButton *btn_other;
    QToolButton *quit;

    void setupUi(QDialog *HistoryDlg)
    {
        if (HistoryDlg->objectName().isEmpty())
            HistoryDlg->setObjectName(QString::fromUtf8("HistoryDlg"));
        HistoryDlg->resize(899, 818);
        HistoryDlg->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_9 = new QVBoxLayout(HistoryDlg);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        widget = new QWidget(HistoryDlg);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout_13 = new QHBoxLayout(widget);
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_2);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(683, 135));
        label_3->setMaximumSize(QSize(683, 135));
        label_3->setLayoutDirection(Qt::LeftToRight);
        label_3->setStyleSheet(QString::fromUtf8("border-image: url(:/MultiControlSys/res/title.png);\n"
"font: 35pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        label_3->setAlignment(Qt::AlignCenter);

        horizontalLayout_13->addWidget(label_3);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_3);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        verticalLayout_10->setContentsMargins(-1, 20, -1, -1);
        lable_date = new QLabel(widget);
        lable_date->setObjectName(QString::fromUtf8("lable_date"));
        QFont font;
        font.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font.setPointSize(16);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        lable_date->setFont(font);
        lable_date->setStyleSheet(QString::fromUtf8("font: 16pt \"\346\245\267\344\275\223\";"));
        lable_date->setAlignment(Qt::AlignCenter);

        verticalLayout_10->addWidget(lable_date);

        lable_time = new QLabel(widget);
        lable_time->setObjectName(QString::fromUtf8("lable_time"));
        lable_time->setFont(font);
        lable_time->setStyleSheet(QString::fromUtf8("font: 16pt \"\346\245\267\344\275\223\";"));
        lable_time->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        verticalLayout_10->addWidget(lable_time);


        horizontalLayout_13->addLayout(verticalLayout_10);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_4);


        verticalLayout_9->addWidget(widget);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(-1, -1, 30, -1);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(HistoryDlg);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label);

        comboBox = new QComboBox(HistoryDlg);
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout->addWidget(comboBox);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_7 = new QLabel(HistoryDlg);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_9->addWidget(label_7);

        dateEdit = new QDateEdit(HistoryDlg);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));
        dateEdit->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_9->addWidget(dateEdit);


        verticalLayout->addLayout(horizontalLayout_9);


        horizontalLayout_8->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(HistoryDlg);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label_2);

        comboBox_2 = new QComboBox(HistoryDlg);
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setDuplicatesEnabled(false);
        comboBox_2->setFrame(true);

        horizontalLayout_3->addWidget(comboBox_2);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_8 = new QLabel(HistoryDlg);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_10->addWidget(label_8);

        comboBox_7 = new QComboBox(HistoryDlg);
        comboBox_7->addItem(QString());
        comboBox_7->setObjectName(QString::fromUtf8("comboBox_7"));

        horizontalLayout_10->addWidget(comboBox_7);


        verticalLayout_2->addLayout(horizontalLayout_10);


        horizontalLayout_8->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(HistoryDlg);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label_4);

        comboBox_4 = new QComboBox(HistoryDlg);
        comboBox_4->addItem(QString());
        comboBox_4->setObjectName(QString::fromUtf8("comboBox_4"));

        horizontalLayout_4->addWidget(comboBox_4);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_9 = new QLabel(HistoryDlg);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_11->addWidget(label_9);

        comboBox_8 = new QComboBox(HistoryDlg);
        comboBox_8->addItem(QString());
        comboBox_8->setObjectName(QString::fromUtf8("comboBox_8"));

        horizontalLayout_11->addWidget(comboBox_8);


        verticalLayout_3->addLayout(horizontalLayout_11);


        horizontalLayout_8->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_10 = new QLabel(HistoryDlg);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_12->addWidget(label_10);

        comboBox_9 = new QComboBox(HistoryDlg);
        comboBox_9->addItem(QString());
        comboBox_9->setObjectName(QString::fromUtf8("comboBox_9"));

        horizontalLayout_12->addWidget(comboBox_9);


        verticalLayout_4->addLayout(horizontalLayout_12);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_6 = new QLabel(HistoryDlg);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_6->addWidget(label_6);

        comboBox_3 = new QComboBox(HistoryDlg);
        comboBox_3->addItem(QString());
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));

        horizontalLayout_6->addWidget(comboBox_3);


        verticalLayout_4->addLayout(horizontalLayout_6);


        horizontalLayout_8->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_5 = new QLabel(HistoryDlg);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(label_5);

        comboBox_5 = new QComboBox(HistoryDlg);
        comboBox_5->addItem(QString());
        comboBox_5->setObjectName(QString::fromUtf8("comboBox_5"));

        horizontalLayout_5->addWidget(comboBox_5);


        verticalLayout_5->addLayout(horizontalLayout_5);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_11 = new QLabel(HistoryDlg);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_7->addWidget(label_11);


        verticalLayout_5->addLayout(horizontalLayout_7);


        horizontalLayout_8->addLayout(verticalLayout_5);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_5);

        query = new QToolButton(HistoryDlg);
        query->setObjectName(QString::fromUtf8("query"));
        query->setStyleSheet(QString::fromUtf8(""));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/MultiControlSys/res/query.png"), QSize(), QIcon::Normal, QIcon::Off);
        query->setIcon(icon);
        query->setIconSize(QSize(64, 66));
        query->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        horizontalLayout_8->addWidget(query);


        verticalLayout_9->addLayout(horizontalLayout_8);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        horizontalLayout_14->setContentsMargins(80, -1, -1, -1);
        checkBox = new QCheckBox(HistoryDlg);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        horizontalLayout_14->addWidget(checkBox);

        label_12 = new QLabel(HistoryDlg);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_14->addWidget(label_12);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer);


        verticalLayout_8->addLayout(horizontalLayout_14);

        listWidget = new QListWidget(HistoryDlg);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        verticalLayout_8->addWidget(listWidget);


        horizontalLayout_2->addLayout(verticalLayout_8);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(30, -1, 30, -1);
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        btn_open = new QPushButton(HistoryDlg);
        btn_open->setObjectName(QString::fromUtf8("btn_open"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btn_open->sizePolicy().hasHeightForWidth());
        btn_open->setSizePolicy(sizePolicy);

        verticalLayout_6->addWidget(btn_open);

        btn_close = new QPushButton(HistoryDlg);
        btn_close->setObjectName(QString::fromUtf8("btn_close"));

        verticalLayout_6->addWidget(btn_close);

        btn_pailie = new QPushButton(HistoryDlg);
        btn_pailie->setObjectName(QString::fromUtf8("btn_pailie"));

        verticalLayout_6->addWidget(btn_pailie);

        btn_compare = new QPushButton(HistoryDlg);
        btn_compare->setObjectName(QString::fromUtf8("btn_compare"));

        verticalLayout_6->addWidget(btn_compare);

        btn_export = new QPushButton(HistoryDlg);
        btn_export->setObjectName(QString::fromUtf8("btn_export"));

        verticalLayout_6->addWidget(btn_export);

        btn_printf = new QPushButton(HistoryDlg);
        btn_printf->setObjectName(QString::fromUtf8("btn_printf"));

        verticalLayout_6->addWidget(btn_printf);

        btn_del = new QPushButton(HistoryDlg);
        btn_del->setObjectName(QString::fromUtf8("btn_del"));

        verticalLayout_6->addWidget(btn_del);

        btn_other = new QPushButton(HistoryDlg);
        btn_other->setObjectName(QString::fromUtf8("btn_other"));

        verticalLayout_6->addWidget(btn_other);


        verticalLayout_7->addLayout(verticalLayout_6);

        quit = new QToolButton(HistoryDlg);
        quit->setObjectName(QString::fromUtf8("quit"));
        quit->setStyleSheet(QString::fromUtf8(""));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/MultiControlSys/res/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        quit->setIcon(icon1);
        quit->setIconSize(QSize(64, 66));
        quit->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        verticalLayout_7->addWidget(quit);


        horizontalLayout_2->addLayout(verticalLayout_7);


        verticalLayout_9->addLayout(horizontalLayout_2);


        retranslateUi(HistoryDlg);

        QMetaObject::connectSlotsByName(HistoryDlg);
    } // setupUi

    void retranslateUi(QDialog *HistoryDlg)
    {
        HistoryDlg->setWindowTitle(QCoreApplication::translate("HistoryDlg", "HistoryDlg", nullptr));
        label_3->setText(QCoreApplication::translate("HistoryDlg", "<html><head/><body><p><span style=\" font-size:48pt; vertical-align:super;\">\345\216\206\345\217\262\346\225\260\346\215\256\345\244\204\347\220\206</span></p></body></html>", nullptr));
        lable_date->setText(QCoreApplication::translate("HistoryDlg", "2020\345\271\26410\346\234\21015\346\227\245", nullptr));
        lable_time->setText(QCoreApplication::translate("HistoryDlg", "08\357\274\23236\357\274\23248", nullptr));
        label->setText(QCoreApplication::translate("HistoryDlg", "\347\212\266\346\200\201", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("HistoryDlg", "\345\205\250\351\203\250", nullptr));

        label_7->setText(QCoreApplication::translate("HistoryDlg", "\346\227\245\346\234\237", nullptr));
        label_2->setText(QCoreApplication::translate("HistoryDlg", "\345\274\271\345\217\267", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("HistoryDlg", "\345\205\250\351\203\250", nullptr));

        label_8->setText(QCoreApplication::translate("HistoryDlg", "   \350\207\263", nullptr));
        comboBox_7->setItemText(0, QCoreApplication::translate("HistoryDlg", "\345\205\250\351\203\250", nullptr));

        label_4->setText(QCoreApplication::translate("HistoryDlg", "\345\215\225\345\205\203", nullptr));
        comboBox_4->setItemText(0, QCoreApplication::translate("HistoryDlg", "\345\205\250\351\203\250", nullptr));

        label_9->setText(QCoreApplication::translate("HistoryDlg", "\347\211\210\346\234\254", nullptr));
        comboBox_8->setItemText(0, QCoreApplication::translate("HistoryDlg", "\345\205\250\351\203\250", nullptr));

        label_10->setText(QCoreApplication::translate("HistoryDlg", "\350\256\276\345\244\207\345\217\267", nullptr));
        comboBox_9->setItemText(0, QCoreApplication::translate("HistoryDlg", "\345\205\250\351\203\250", nullptr));

        label_6->setText(QCoreApplication::translate("HistoryDlg", "\347\231\273\351\231\206\344\272\272", nullptr));
        comboBox_3->setItemText(0, QCoreApplication::translate("HistoryDlg", "\345\205\250\351\203\250", nullptr));

        label_5->setText(QCoreApplication::translate("HistoryDlg", "\345\210\206\347\261\273\347\255\233\351\200\211", nullptr));
        comboBox_5->setItemText(0, QCoreApplication::translate("HistoryDlg", "\345\205\250\351\203\250", nullptr));

        label_11->setText(QString());
        query->setText(QCoreApplication::translate("HistoryDlg", "  \346\237\245\350\257\242", nullptr));
        checkBox->setText(QCoreApplication::translate("HistoryDlg", "\345\205\250\351\200\211", nullptr));
        label_12->setText(QCoreApplication::translate("HistoryDlg", "\345\205\261\346\211\276\345\210\260", nullptr));
        btn_open->setText(QCoreApplication::translate("HistoryDlg", "\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
        btn_close->setText(QCoreApplication::translate("HistoryDlg", "\345\205\263\351\227\255\346\226\207\344\273\266", nullptr));
        btn_pailie->setText(QCoreApplication::translate("HistoryDlg", "\346\216\222\345\210\227\347\252\227\345\217\243", nullptr));
        btn_compare->setText(QCoreApplication::translate("HistoryDlg", "\351\241\271\347\233\256\345\257\271\346\257\224", nullptr));
        btn_export->setText(QCoreApplication::translate("HistoryDlg", "\345\257\274\345\207\272\346\226\207\344\273\266", nullptr));
        btn_printf->setText(QCoreApplication::translate("HistoryDlg", "\346\211\223\345\215\260\350\276\223\345\207\272", nullptr));
        btn_del->setText(QCoreApplication::translate("HistoryDlg", "\345\210\240\351\231\244\346\226\207\344\273\266", nullptr));
        btn_other->setText(QCoreApplication::translate("HistoryDlg", "\345\205\266\344\273\226\345\244\204\347\220\206", nullptr));
        quit->setText(QCoreApplication::translate("HistoryDlg", "  \351\200\200\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HistoryDlg: public Ui_HistoryDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HISTORYDLG_H
