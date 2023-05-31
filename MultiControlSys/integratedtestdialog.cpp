#include "integratedtestdialog.h"
#include "ui_integratedtestdialog.h"
#include "Packet.h"
#include <QDesktopWidget>
#include "AtmoTask.h"
#include "XLManager.h"
#include "PowerTask.h"
#include "AutoTestDlg.h"
#include "FeiKongTask.h"
#include "CPUTask.h"
#include "DPUTask.h"
#include "Task5.h"
#include "Task10.h"
#include "Task13.h"

IntegratedTestDialog::IntegratedTestDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IntegratedTestDialog)
{
    ui->setupUi(this);
    m_parent = parent;
    setWindowFlags(Qt::FramelessWindowHint);
    resize(DLG_WIDTH, DLG_HEIGHT);
    QDesktopWidget* desktop = QApplication::desktop(); // =qApp->desktop();也可以
    //move((desktop->width() - this->width()) / 2, (desktop->height() - this->height()) / 2);
    move((WIDTH - this->width()) / 2, (desktop->height() - this->height()) / 2);
    //hide();

    m_intercongirm=new IntegraedconfirmDlg();
    connect(this,SIGNAL(sig_value(QString,QString,QString,QString)),m_intercongirm,SLOT(slot_value(QString,QString,QString,QString)));
    connect(m_intercongirm,SIGNAL(sig_closeIntegratedtestdialog()),this,SLOT(slot_closeIntegratedtestdialog()));

}

IntegratedTestDialog::~IntegratedTestDialog()
{
    delete ui;
}




void IntegratedTestDialog::on_pushButton_clicked()
{
    /*
    ui->textEdit->setEnabled(false);
    ui->textEdit_2->setEnabled(false);
    ui->textEdit_3->setEnabled(false);
    ui->textEdit_4->setEnabled(false);
    ui->textEdit_5->setEnabled(false);
    ui->textEdit_6->setEnabled(false);
    ui->textEdit_7->setEnabled(false);
    ui->textEdit_8->setEnabled(false);
    ui->textEdit_9->setEnabled(false);
    ui->textEdit_10->setEnabled(false);
    ui->textEdit_11->setEnabled(false);
    ui->textEdit_12->setEnabled(false);
    */
    QString longitude= ui->textEdit->toPlainText();
    QString heading =ui->textEdit_2->toPlainText();
    QString latitude=ui->textEdit_3->toPlainText();
    QString height=ui->textEdit_4->toPlainText();
    emit sig_value(longitude,heading,latitude,height);

    m_intercongirm->exec();
}


void IntegratedTestDialog::on_pushButton_2_clicked()
{

}

void IntegratedTestDialog::slot_closeIntegratedtestdialog()
{
    this->close();
}
