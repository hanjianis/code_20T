#include "Integraedconfirmdlg.h"
#include "ui_Integraedconfirmdlg.h"
#include "Packet.h"
#include <QDesktopWidget>

IntegraedconfirmDlg::IntegraedconfirmDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IntegraedconfirmDlg)
{
    ui->setupUi(this);   
    setWindowFlags(Qt::FramelessWindowHint);
    resize(DLG_WIDTH2, DLG_HEIGHT2);
    QDesktopWidget* desktop = QApplication::desktop(); // =qApp->desktop();也可以
    //move((desktop->width() - this->width()) / 2, (desktop->height() - this->height()) / 2);
    move((WIDTH - this->width()) / 2, (desktop->height() - this->height()) / 2);
    //hide();

}

IntegraedconfirmDlg::~IntegraedconfirmDlg()
{
    delete ui;
}

void IntegraedconfirmDlg::on_pushButton_clicked()
{
    emit sig_closeIntegratedtestdialog();
    this->close();

}

void IntegraedconfirmDlg::slot_value(QString longitude,QString heading,QString latitude,QString height)
{
    ui->textEdit->setText(longitude);
    ui->textEdit_2->setText(height);
    ui->textEdit_3->setText(heading);
    ui->textEdit_4->setText(latitude);
    ui->textEdit->setEnabled(false);
    ui->textEdit_2->setEnabled(false);
    ui->textEdit_3->setEnabled(false);
    ui->textEdit_4->setEnabled(false);

}

void IntegraedconfirmDlg::on_pushButton_2_clicked()
{
    this->close();
}

