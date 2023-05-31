#include "t"
#include "ui_IntegratedLowerDisplay.h"

IntegratedLowerDisplay::IntegratedLowerDisplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IntegratedLowerDisplay)
{
    ui->setupUi(this);
}

IntegratedLowerDisplay::~IntegratedLowerDisplay()
{
    delete ui;
}
