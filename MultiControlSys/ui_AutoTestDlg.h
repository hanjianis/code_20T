/********************************************************************************
** Form generated from reading UI file 'AutoTestDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTOTESTDLG_H
#define UI_AUTOTESTDLG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AutoTestDlg
{
public:
    QVBoxLayout *verticalLayout_13;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_10;
    QVBoxLayout *verticalLayout_12;
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidget;
    QWidget *listItems;
    QVBoxLayout *verticalLayout_16;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *label_2;
    QVBoxLayout *verticalLayout_9;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *lable_date;
    QLabel *lable_time;
    QFrame *line;
    QVBoxLayout *verticalLayout_4;
    QLabel *lable_date_2;
    QWidget *widget_7;
    QHBoxLayout *horizontalLayout_9;
    QLineEdit *lineEdit;
    QVBoxLayout *verticalLayout_5;
    QLabel *lable_date_3;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_8;
    QLineEdit *lineEdit_2;
    QVBoxLayout *verticalLayout_6;
    QLabel *lable_date_4;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_4;
    QComboBox *comboBox;
    QVBoxLayout *verticalLayout_7;
    QLabel *lable_date_5;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_5;
    QComboBox *comboBox_2;
    QVBoxLayout *verticalLayout_8;
    QLabel *lable_date_6;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_7;
    QComboBox *comboBox_3;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lable_date_7;
    QLineEdit *lineEdit_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lable_date_8;
    QLineEdit *lineEdit_4;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer_5;
    QVBoxLayout *verticalLayout_11;
    QToolButton *btnstart;
    QToolButton *toolButton_2;
    QToolButton *quit;

    void setupUi(QDialog *AutoTestDlg)
    {
        if (AutoTestDlg->objectName().isEmpty())
            AutoTestDlg->setObjectName(QString::fromUtf8("AutoTestDlg"));
        AutoTestDlg->resize(800, 818);
        AutoTestDlg->setMinimumSize(QSize(800, 600));
        AutoTestDlg->setMaximumSize(QSize(80000, 600000));
        AutoTestDlg->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_13 = new QVBoxLayout(AutoTestDlg);
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setContentsMargins(11, 11, 11, 11);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        widget = new QWidget(AutoTestDlg);
        widget->setObjectName(QString::fromUtf8("widget"));
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


        verticalLayout_13->addWidget(widget);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setSpacing(30);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        verticalLayout_12->setContentsMargins(20, -1, -1, 10);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tableWidget = new QTableWidget(AutoTestDlg);
        if (tableWidget->columnCount() < 6)
            tableWidget->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        if (tableWidget->rowCount() < 1)
            tableWidget->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setItem(0, 0, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setItem(0, 1, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setItem(0, 2, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setItem(0, 3, __qtablewidgetitem10);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setStyleSheet(QString::fromUtf8(""));
        tableWidget->setTextElideMode(Qt::ElideNone);

        verticalLayout->addWidget(tableWidget);


        verticalLayout_12->addLayout(verticalLayout);

        listItems = new QWidget(AutoTestDlg);
        listItems->setObjectName(QString::fromUtf8("listItems"));
        listItems->setMinimumSize(QSize(0, 20));
        verticalLayout_16 = new QVBoxLayout(listItems);
        verticalLayout_16->setSpacing(6);
        verticalLayout_16->setContentsMargins(11, 11, 11, 11);
        verticalLayout_16->setObjectName(QString::fromUtf8("verticalLayout_16"));

        verticalLayout_12->addWidget(listItems);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(AutoTestDlg);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(100, 16777215));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        label_2 = new QLabel(AutoTestDlg);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        horizontalLayout->addWidget(label_2);

        horizontalLayout->setStretch(0, 2);
        horizontalLayout->setStretch(1, 6);

        verticalLayout_12->addLayout(horizontalLayout);


        horizontalLayout_10->addLayout(verticalLayout_12);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(20, -1, 20, -1);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, 20, -1, -1);
        lable_date = new QLabel(AutoTestDlg);
        lable_date->setObjectName(QString::fromUtf8("lable_date"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font1.setPointSize(16);
        font1.setBold(false);
        font1.setItalic(false);
        lable_date->setFont(font1);
        lable_date->setStyleSheet(QString::fromUtf8("font: 16pt \"\346\245\267\344\275\223\";"));
        lable_date->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        verticalLayout_2->addWidget(lable_date);

        lable_time = new QLabel(AutoTestDlg);
        lable_time->setObjectName(QString::fromUtf8("lable_time"));
        lable_time->setFont(font1);
        lable_time->setStyleSheet(QString::fromUtf8("font: 16pt \"\346\245\267\344\275\223\";"));
        lable_time->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        verticalLayout_2->addWidget(lable_time);


        verticalLayout_3->addLayout(verticalLayout_2);

        line = new QFrame(AutoTestDlg);
        line->setObjectName(QString::fromUtf8("line"));
        line->setStyleSheet(QString::fromUtf8(""));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line);


        verticalLayout_9->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        lable_date_2 = new QLabel(AutoTestDlg);
        lable_date_2->setObjectName(QString::fromUtf8("lable_date_2"));
        QFont font2;
        font2.setBold(true);
        lable_date_2->setFont(font2);
        lable_date_2->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        verticalLayout_4->addWidget(lable_date_2);

        widget_7 = new QWidget(AutoTestDlg);
        widget_7->setObjectName(QString::fromUtf8("widget_7"));
        horizontalLayout_9 = new QHBoxLayout(widget_7);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        lineEdit = new QLineEdit(widget_7);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setEnabled(false);
        lineEdit->setMaximumSize(QSize(200, 16777215));
        lineEdit->setFont(font2);
        lineEdit->setAlignment(Qt::AlignCenter);

        horizontalLayout_9->addWidget(lineEdit);


        verticalLayout_4->addWidget(widget_7);


        verticalLayout_9->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        lable_date_3 = new QLabel(AutoTestDlg);
        lable_date_3->setObjectName(QString::fromUtf8("lable_date_3"));
        lable_date_3->setFont(font2);
        lable_date_3->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        verticalLayout_5->addWidget(lable_date_3);

        widget_6 = new QWidget(AutoTestDlg);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));
        horizontalLayout_8 = new QHBoxLayout(widget_6);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        lineEdit_2 = new QLineEdit(widget_6);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setEnabled(false);
        lineEdit_2->setMaximumSize(QSize(200, 16777215));
        lineEdit_2->setFont(font2);
        lineEdit_2->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
"color: rgb(85, 255, 127);"));
        lineEdit_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_8->addWidget(lineEdit_2);


        verticalLayout_5->addWidget(widget_6);


        verticalLayout_9->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(-1, 20, -1, -1);
        lable_date_4 = new QLabel(AutoTestDlg);
        lable_date_4->setObjectName(QString::fromUtf8("lable_date_4"));
        lable_date_4->setFont(font2);
        lable_date_4->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        verticalLayout_6->addWidget(lable_date_4);

        widget_3 = new QWidget(AutoTestDlg);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        horizontalLayout_4 = new QHBoxLayout(widget_3);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        comboBox = new QComboBox(widget_3);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setMaximumSize(QSize(180, 16777215));

        horizontalLayout_4->addWidget(comboBox);


        verticalLayout_6->addWidget(widget_3);


        verticalLayout_9->addLayout(verticalLayout_6);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(0);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        lable_date_5 = new QLabel(AutoTestDlg);
        lable_date_5->setObjectName(QString::fromUtf8("lable_date_5"));
        lable_date_5->setFont(font2);
        lable_date_5->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        verticalLayout_7->addWidget(lable_date_5);

        widget_4 = new QWidget(AutoTestDlg);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        horizontalLayout_5 = new QHBoxLayout(widget_4);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        comboBox_2 = new QComboBox(widget_4);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setMaximumSize(QSize(180, 16777215));

        horizontalLayout_5->addWidget(comboBox_2);


        verticalLayout_7->addWidget(widget_4);


        verticalLayout_9->addLayout(verticalLayout_7);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(0);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(-1, 0, -1, 0);
        lable_date_6 = new QLabel(AutoTestDlg);
        lable_date_6->setObjectName(QString::fromUtf8("lable_date_6"));
        lable_date_6->setFont(font2);
        lable_date_6->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        verticalLayout_8->addWidget(lable_date_6);

        widget_5 = new QWidget(AutoTestDlg);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        horizontalLayout_7 = new QHBoxLayout(widget_5);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        comboBox_3 = new QComboBox(widget_5);
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));
        comboBox_3->setMaximumSize(QSize(180, 16777215));

        horizontalLayout_7->addWidget(comboBox_3);


        verticalLayout_8->addWidget(widget_5);


        verticalLayout_9->addLayout(verticalLayout_8);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        verticalLayout_10->setContentsMargins(30, 0, 20, 20);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lable_date_7 = new QLabel(AutoTestDlg);
        lable_date_7->setObjectName(QString::fromUtf8("lable_date_7"));
        lable_date_7->setFont(font2);
        lable_date_7->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(lable_date_7);

        lineEdit_3 = new QLineEdit(AutoTestDlg);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setEnabled(false);
        lineEdit_3->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_2->addWidget(lineEdit_3);


        verticalLayout_10->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        lable_date_8 = new QLabel(AutoTestDlg);
        lable_date_8->setObjectName(QString::fromUtf8("lable_date_8"));
        lable_date_8->setFont(font2);
        lable_date_8->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(lable_date_8);

        lineEdit_4 = new QLineEdit(AutoTestDlg);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setEnabled(false);
        lineEdit_4->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_3->addWidget(lineEdit_4);


        verticalLayout_10->addLayout(horizontalLayout_3);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_10->addItem(verticalSpacer_4);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_10->addItem(verticalSpacer_2);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_10->addItem(verticalSpacer_3);


        verticalLayout_9->addLayout(verticalLayout_10);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(verticalSpacer_5);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        verticalLayout_11->setContentsMargins(20, -1, -1, -1);
        btnstart = new QToolButton(AutoTestDlg);
        btnstart->setObjectName(QString::fromUtf8("btnstart"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/MultiControlSys/res/start.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnstart->setIcon(icon);
        btnstart->setIconSize(QSize(64, 66));
        btnstart->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        verticalLayout_11->addWidget(btnstart);

        toolButton_2 = new QToolButton(AutoTestDlg);
        toolButton_2->setObjectName(QString::fromUtf8("toolButton_2"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/MultiControlSys/res/pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_2->setIcon(icon1);
        toolButton_2->setIconSize(QSize(64, 66));
        toolButton_2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        verticalLayout_11->addWidget(toolButton_2);

        quit = new QToolButton(AutoTestDlg);
        quit->setObjectName(QString::fromUtf8("quit"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/MultiControlSys/res/repaly.png"), QSize(), QIcon::Normal, QIcon::Off);
        quit->setIcon(icon2);
        quit->setIconSize(QSize(64, 66));
        quit->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        verticalLayout_11->addWidget(quit);


        verticalLayout_9->addLayout(verticalLayout_11);


        horizontalLayout_10->addLayout(verticalLayout_9);

        horizontalLayout_10->setStretch(0, 1);

        verticalLayout_13->addLayout(horizontalLayout_10);


        retranslateUi(AutoTestDlg);

        QMetaObject::connectSlotsByName(AutoTestDlg);
    } // setupUi

    void retranslateUi(QDialog *AutoTestDlg)
    {
        AutoTestDlg->setWindowTitle(QCoreApplication::translate("AutoTestDlg", "AutoTestDlg", nullptr));
        label_3->setText(QCoreApplication::translate("AutoTestDlg", "<html><head/><body><p><span style=\" font-size:18pt; font-weight:600;\">EZ-20T\350\207\252\345\212\250\345\214\226\346\265\213\350\257\225\347\263\273\347\273\237\346\265\213\350\257\225\351\235\242\346\235\277</span></p></body></html>", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("AutoTestDlg", "\345\272\217\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("AutoTestDlg", "\351\241\271\347\233\256\345\220\215\347\247\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("AutoTestDlg", "\346\212\200\346\234\257\346\235\241\344\273\266", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("AutoTestDlg", "\345\256\236\346\265\213\345\200\274", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("AutoTestDlg", "\345\215\225\344\275\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("AutoTestDlg", "\347\273\223\350\256\272", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("AutoTestDlg", "1", nullptr));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->item(0, 0);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("AutoTestDlg", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->item(0, 1);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("AutoTestDlg", "\344\276\233\347\224\265", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->item(0, 2);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("AutoTestDlg", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->item(0, 3);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("AutoTestDlg", "1", nullptr));
        tableWidget->setSortingEnabled(__sortingEnabled);

        label->setText(QCoreApplication::translate("AutoTestDlg", "\346\217\220\347\244\272\344\277\241\346\201\257", nullptr));
        label_2->setText(QString());
        lable_date->setText(QCoreApplication::translate("AutoTestDlg", "2020\345\271\26410\346\234\21015\346\227\245", nullptr));
        lable_time->setText(QCoreApplication::translate("AutoTestDlg", "08\357\274\23236\357\274\23248", nullptr));
        lable_date_2->setText(QCoreApplication::translate("AutoTestDlg", "\350\242\253\346\265\213\345\257\271\350\261\241\345\236\213\345\217\267/\347\212\266\346\200\201", nullptr));
        lineEdit->setText(QCoreApplication::translate("AutoTestDlg", "\347\263\273\347\273\237\350\207\252\346\243\200\347\212\266\346\200\201", nullptr));
        lable_date_3->setText(QCoreApplication::translate("AutoTestDlg", "\346\265\213\350\257\225\346\227\266\351\227\264", nullptr));
        lineEdit_2->setText(QCoreApplication::translate("AutoTestDlg", "00:00:00", nullptr));
        lable_date_4->setText(QCoreApplication::translate("AutoTestDlg", "\346\265\213\350\257\225\345\215\225\345\205\203", nullptr));
        lable_date_5->setText(QCoreApplication::translate("AutoTestDlg", "\346\265\213\350\257\225\346\226\271\345\274\217", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("AutoTestDlg", "\350\277\236\347\273\255\346\265\213\350\257\225", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("AutoTestDlg", "\345\215\225\351\241\271\346\265\213\350\257\225", nullptr));

        lable_date_6->setText(QCoreApplication::translate("AutoTestDlg", "\346\265\213\350\257\225\351\241\271\347\233\256", nullptr));
        comboBox_3->setItemText(0, QCoreApplication::translate("AutoTestDlg", "\346\211\200\346\234\211\351\241\271\347\233\256", nullptr));
        comboBox_3->setItemText(1, QCoreApplication::translate("AutoTestDlg", "\346\250\241\346\213\237\351\207\217\351\200\232\351\201\223\346\243\200\346\237\245", nullptr));
        comboBox_3->setItemText(2, QCoreApplication::translate("AutoTestDlg", "422\344\270\262\345\217\243\351\200\232\350\256\257\346\243\200\346\237\245", nullptr));
        comboBox_3->setItemText(3, QCoreApplication::translate("AutoTestDlg", "\347\250\213\346\216\247\350\256\276\345\244\207\347\256\241\347\220\206\345\231\250\346\243\200\346\237\245", nullptr));
        comboBox_3->setItemText(4, QCoreApplication::translate("AutoTestDlg", "\347\273\274\345\220\210\347\224\265\346\272\220\346\243\200\346\237\245", nullptr));
        comboBox_3->setItemText(5, QCoreApplication::translate("AutoTestDlg", "\344\270\255\351\242\221\347\224\265\346\272\220", nullptr));
        comboBox_3->setItemText(6, QCoreApplication::translate("AutoTestDlg", "\345\244\247\346\260\224\346\225\260\346\215\256\346\265\213\346\216\247\344\273\252\346\243\200\346\237\245", nullptr));
        comboBox_3->setItemText(7, QCoreApplication::translate("AutoTestDlg", "\351\233\267\350\276\276\351\253\230\345\272\246\350\241\250\344\277\241\345\217\267\346\272\220\346\243\200\346\237\245", nullptr));
        comboBox_3->setItemText(8, QCoreApplication::translate("AutoTestDlg", "\345\257\274\350\210\252\344\277\241\345\217\267\346\250\241\346\213\237\345\231\250\346\243\200\346\237\245", nullptr));
        comboBox_3->setItemText(9, QCoreApplication::translate("AutoTestDlg", "\346\231\257\350\261\241\346\250\241\346\213\237\345\231\250\346\243\200\346\237\245", nullptr));

        lable_date_7->setText(QCoreApplication::translate("AutoTestDlg", "\346\255\243\347\241\256\357\274\232", nullptr));
        lineEdit_3->setText(QCoreApplication::translate("AutoTestDlg", "0", nullptr));
        lable_date_8->setText(QCoreApplication::translate("AutoTestDlg", "\351\224\231\350\257\257\357\274\232", nullptr));
        lineEdit_4->setText(QCoreApplication::translate("AutoTestDlg", "0", nullptr));
        btnstart->setText(QCoreApplication::translate("AutoTestDlg", "\345\274\200\345\247\213", nullptr));
        toolButton_2->setText(QCoreApplication::translate("AutoTestDlg", "\346\232\202\345\201\234", nullptr));
        quit->setText(QCoreApplication::translate("AutoTestDlg", "\350\277\224\345\233\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AutoTestDlg: public Ui_AutoTestDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTOTESTDLG_H
