#include "IntegratedLowerDisplay.h"
#include "ui_IntegratedLowerDisplay.h"


IntegratedLowerDisplay::IntegratedLowerDisplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IntegratedLowerDisplay),
    Display_End(false)
{
    ui->setupUi(this);


    dataupdate=new QTimer();
    connect(dataupdate,&QTimer::timeout,this,&IntegratedLowerDisplay::on_timeout);
    dataupdate->start(1000);

  //  connect(this, SIGNAL(sig_updateData()), this, SLOT(slot_updateData()));
   // emit sig_updateData();




}

IntegratedLowerDisplay::~IntegratedLowerDisplay()
{
    delete ui;
}

void IntegratedLowerDisplay::on_timeout()
{
    i++;
    updateData();

}

void IntegratedLowerDisplay::updateData()
{
    if(i>=2&&(!Display_End))
    {
        ui->lineEdit->setText(QString::fromLocal8Bit("1a1a"));
        ui->lineEdit_2->setText(QString::fromLocal8Bit("501a"));
        ui->lineEdit_4->setText("80FF");
        float course_angle=-145.99+qrand()%100;
         ui->lineEdit_6->setText(QString::number(course_angle,'f',2));

         ui->lineEdit_12->setText("30.59");
         ui->lineEdit_13->setText("117.03");

    }
    if(i>=25&&(!Display_End))
    {
        ui->lineEdit_3->setText(QString::number(i-25));
    }

    if(i>=3&&(!Display_End))
    {
        ui->lineEdit_5->setText(QString::number(13+20*(i-3)));
    }

    if(i>=14&&(!Display_End))
    {
        float pitch_angle=-0.20+qrand()%10*0.01;
        ui->lineEdit_7->setText(QString::number(pitch_angle,'f',2));
        float roll_angle=qrand()%10*0.01;
        ui->lineEdit_8->setText(QString::number(roll_angle,'f',2));
    }

    if(i>=22&&i<130&&(!Display_End))
    {
        float north=(i-22)*0.12;
        ui->lineEdit_9->setText(QString::number(north,'f',2));
        float vertical=(i-22)*0.13;
        ui->lineEdit_10->setText(QString::number(vertical,'f',2));
        float earth=-(i-22)*0.17;
        ui->lineEdit_11->setText(QString::number(earth,'f',2));
    }

    if(i>=130&&(!Display_End))
    {
        ui->lineEdit_9->setText("0.00");
        ui->lineEdit_10->setText("0.00");
        ui->lineEdit_11->setText("0.00");

        float realcourse_angle=-145.99+qrand()%100;
        ui->lineEdit_15->setText(QString::number(realcourse_angle,'f',2));
        float direction=(i-130)*12;
        ui->lineEdit_16->setText(QString::number(direction,'f',2));
        float lateral=(i-130)*18;
        ui->lineEdit_17->setText(QString::number(lateral,'f',2));
        if(i%2==0)
        {
            ui->lineEdit_18->setText("0.00");
        }else {
            ui->lineEdit_18->setText("0.01");
        }

        ui->lineEdit_19->setText("0.00");
        float ins_direction=-0.01+(i-130)%10*0.01;
        ui->lineEdit_20->setText(QString::number(ins_direction,'g',2));
        float ins_vertical=(i-130)%100*0.2;
        ui->lineEdit_21->setText(QString::number(ins_vertical,'g',2));


        float ins_lateral=(i-130)%100*0.3;
        ui->lineEdit_22->setText(QString::number(ins_lateral,'g',2));

        ui->lineEdit_23->setText("-0.02");
    }
    if(i==2&&(!Display_End))
    {
        ui->lineEdit_14->setText("24.80");
    }
    if((i>170)&&(i%4==0)&&(!Display_End))
    {
        int j=0;
        j++;
        double height=24.80-j*0.40;
        ui->lineEdit_14->setText(QString::number(height,'g',2));
    }

}

void IntegratedLowerDisplay::slot_displaylowend()
{
    Display_End=true;
    dataupdate->stop();
}
