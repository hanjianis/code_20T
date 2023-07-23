#include "DiagnosticPause.h"
#include "ui_DiagnosticPause.h"
#include "Packet.h"
#include <QDesktopWidget>

DiagnosticPause::DiagnosticPause(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DiagnosticPause)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    resize(DLG_WIDTH, DLG_HEIGHT);
    QDesktopWidget* desktop = QApplication::desktop(); // =qApp->desktop();也可以
    //move((desktop->width() - this->width()) / 2, (desktop->height() - this->height()) / 2);
    move((WIDTH - this->width()) / 2, (desktop->height() - this->height()) / 2);
}

DiagnosticPause::~DiagnosticPause()
{
    delete ui;
}

void DiagnosticPause::on_pushButton_clicked()
{
    emit sig_diagnosticpause();
    this->close();
}


void DiagnosticPause::on_pushButton_2_clicked()
{
    this->close();
}

