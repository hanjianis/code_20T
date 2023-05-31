/********************************************************************************
** Form generated from reading UI file 'TestItemsDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTITEMSDLG_H
#define UI_TESTITEMSDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TestItemsDlg
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *dxt;
    QCheckBox *ywxhq;
    QCheckBox *xsjxxt;
    QCheckBox *zmxt;
    QCheckBox *dqxt;
    QCheckBox *yxxt;
    QCheckBox *all;
    QPushButton *btnok;
    QLabel *label_3;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QCheckBox *fkcszd;
    QCheckBox *zdjbk;
    QCheckBox *zdjck;
    QCheckBox *qyddbxt;
    QCheckBox *dpujzt;
    QCheckBox *ldgdb;
    QCheckBox *dlxt;

    void setupUi(QDialog *TestItemsDlg)
    {
        if (TestItemsDlg->objectName().isEmpty())
            TestItemsDlg->setObjectName(QString::fromUtf8("TestItemsDlg"));
        TestItemsDlg->resize(514, 420);
        TestItemsDlg->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"    font-family:Microsoft Yahei;\n"
"    font-size:15pt;\n"
"	width:218px;\n"
"	height:68px;\n"
"	border-radius:8px;\n"
"	border-image: url(:/MultiControlSys/res/btn.png);\n"
"}"));
        layoutWidget = new QWidget(TestItemsDlg);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(260, 110, 121, 251));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        dxt = new QCheckBox(layoutWidget);
        dxt->setObjectName(QString::fromUtf8("dxt"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setBold(true);
        font.setWeight(75);
        dxt->setFont(font);

        verticalLayout_2->addWidget(dxt);

        ywxhq = new QCheckBox(layoutWidget);
        ywxhq->setObjectName(QString::fromUtf8("ywxhq"));
        ywxhq->setFont(font);

        verticalLayout_2->addWidget(ywxhq);

        xsjxxt = new QCheckBox(layoutWidget);
        xsjxxt->setObjectName(QString::fromUtf8("xsjxxt"));
        xsjxxt->setFont(font);

        verticalLayout_2->addWidget(xsjxxt);

        zmxt = new QCheckBox(layoutWidget);
        zmxt->setObjectName(QString::fromUtf8("zmxt"));
        zmxt->setFont(font);

        verticalLayout_2->addWidget(zmxt);

        dqxt = new QCheckBox(layoutWidget);
        dqxt->setObjectName(QString::fromUtf8("dqxt"));
        dqxt->setFont(font);

        verticalLayout_2->addWidget(dqxt);

        yxxt = new QCheckBox(layoutWidget);
        yxxt->setObjectName(QString::fromUtf8("yxxt"));
        yxxt->setFont(font);

        verticalLayout_2->addWidget(yxxt);

        all = new QCheckBox(layoutWidget);
        all->setObjectName(QString::fromUtf8("all"));
        all->setFont(font);
        all->setChecked(false);
        all->setTristate(true);

        verticalLayout_2->addWidget(all);

        btnok = new QPushButton(TestItemsDlg);
        btnok->setObjectName(QString::fromUtf8("btnok"));
        btnok->setGeometry(QRect(389, 330, 101, 31));
        label_3 = new QLabel(TestItemsDlg);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 60, 421, 27));
        label_3->setAlignment(Qt::AlignCenter);
        layoutWidget1 = new QWidget(TestItemsDlg);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(90, 110, 121, 251));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        fkcszd = new QCheckBox(layoutWidget1);
        fkcszd->setObjectName(QString::fromUtf8("fkcszd"));
        fkcszd->setFont(font);

        verticalLayout->addWidget(fkcszd);

        zdjbk = new QCheckBox(layoutWidget1);
        zdjbk->setObjectName(QString::fromUtf8("zdjbk"));
        zdjbk->setFont(font);

        verticalLayout->addWidget(zdjbk);

        zdjck = new QCheckBox(layoutWidget1);
        zdjck->setObjectName(QString::fromUtf8("zdjck"));
        zdjck->setFont(font);

        verticalLayout->addWidget(zdjck);

        qyddbxt = new QCheckBox(layoutWidget1);
        qyddbxt->setObjectName(QString::fromUtf8("qyddbxt"));
        qyddbxt->setFont(font);

        verticalLayout->addWidget(qyddbxt);

        dpujzt = new QCheckBox(layoutWidget1);
        dpujzt->setObjectName(QString::fromUtf8("dpujzt"));
        dpujzt->setFont(font);

        verticalLayout->addWidget(dpujzt);

        ldgdb = new QCheckBox(layoutWidget1);
        ldgdb->setObjectName(QString::fromUtf8("ldgdb"));
        ldgdb->setFont(font);

        verticalLayout->addWidget(ldgdb);

        dlxt = new QCheckBox(layoutWidget1);
        dlxt->setObjectName(QString::fromUtf8("dlxt"));
        dlxt->setFont(font);

        verticalLayout->addWidget(dlxt);


        retranslateUi(TestItemsDlg);

        QMetaObject::connectSlotsByName(TestItemsDlg);
    } // setupUi

    void retranslateUi(QDialog *TestItemsDlg)
    {
        TestItemsDlg->setWindowTitle(QCoreApplication::translate("TestItemsDlg", "TestItemsDlg", nullptr));
        dxt->setText(QCoreApplication::translate("TestItemsDlg", "\350\210\265\347\263\273\347\273\237", nullptr));
        ywxhq->setText(QCoreApplication::translate("TestItemsDlg", "\346\262\271\344\275\215\344\277\241\345\217\267\345\231\250", nullptr));
        xsjxxt->setText(QCoreApplication::translate("TestItemsDlg", "\344\270\213\350\247\206\346\231\257\350\261\241\347\263\273\347\273\237", nullptr));
        zmxt->setText(QCoreApplication::translate("TestItemsDlg", "\347\205\247\346\230\216\347\263\273\347\273\237", nullptr));
        dqxt->setText(QCoreApplication::translate("TestItemsDlg", "\347\224\265\346\260\224\347\263\273\347\273\237", nullptr));
        yxxt->setText(QCoreApplication::translate("TestItemsDlg", "\345\274\225\344\277\241\347\263\273\347\273\237", nullptr));
        all->setText(QCoreApplication::translate("TestItemsDlg", "\345\205\250\351\200\211", nullptr));
        btnok->setText(QCoreApplication::translate("TestItemsDlg", "\347\241\256\345\256\232", nullptr));
        label_3->setText(QCoreApplication::translate("TestItemsDlg", "<html><head/><body><p><span style=\" font-size:18pt; font-weight:600;\">K/AKD20\345\257\274\345\274\271\345\215\225\351\241\271\346\265\213\350\257\225\351\241\271\347\233\256</span></p></body></html>", nullptr));
        fkcszd->setText(QCoreApplication::translate("TestItemsDlg", "\351\243\236\346\216\247\345\217\202\346\225\260\350\243\205\350\256\242", nullptr));
        zdjbk->setText(QCoreApplication::translate("TestItemsDlg", "\345\210\266\345\257\274\346\234\272\345\271\266\345\217\243", nullptr));
        zdjck->setText(QCoreApplication::translate("TestItemsDlg", "\345\210\266\345\257\274\346\234\272\344\270\262\345\217\243", nullptr));
        qyddbxt->setText(QCoreApplication::translate("TestItemsDlg", "\346\260\224\345\216\213\345\257\274\350\257\273\350\241\250\347\263\273\347\273\237", nullptr));
        dpujzt->setText(QCoreApplication::translate("TestItemsDlg", "DPU\345\237\272\345\207\206\345\233\276", nullptr));
        ldgdb->setText(QCoreApplication::translate("TestItemsDlg", "\351\233\267\350\276\276\351\253\230\345\272\246\350\241\250", nullptr));
        dlxt->setText(QCoreApplication::translate("TestItemsDlg", "\345\212\250\345\212\233\347\263\273\347\273\237", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TestItemsDlg: public Ui_TestItemsDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTITEMSDLG_H
