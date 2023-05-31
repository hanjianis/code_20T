#include "motioncontroll.h"
#include "ui_motioncontroll.h"
#include <QMessageBox>
#include <QDebug>

#include "snap7.h"

MotionControll::MotionControll(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MotionControll)
{
    ui->setupUi(this);
    ptrPLC = new TS7Client();

    ui->lineEdit_Distance->setDisabled(true);
    ui->btn_Stop->setStyleSheet("background:rgb(200,100,70)");
    m_bStatus = false;

    connect(&m_timer, SIGNAL(timeout()), this, SLOT(readHorisonVal()));
}

MotionControll::~MotionControll()
{
    delete ui;
    m_timer.stop();
}

void MotionControll::on_btn_Connect_clicked()
{
    if(!ptrPLC->Connected())
    {
        int res = ptrPLC->ConnectTo("192.168.2.12", 0, 1);
        if(!res)
        {
            ui->btn_Connect->setDisabled(true);
            m_timer.start(500);
        }
    }
}

void MotionControll::on_btn_RotateStart_clicked()
{
    if(ptrPLC->Connected())
    {
        byte buff = 1;
        ptrPLC->WriteArea(0x83, 1, 16, 1, 1, &buff);
        ui->btn_RotateStart->setDisabled(true);
        ui->btn_RotateStop->setDisabled(false);
    }
}

void MotionControll::on_btn_RotateStop_clicked()
{
    if(ptrPLC->Connected())
    {
        byte buff = 0;
        ptrPLC->WriteArea(0x83, 1, 16, 1, 1, &buff);
        ui->btn_RotateStart->setDisabled(true);
        ui->btn_RotateStop->setDisabled(false);
    }
}


void MotionControll::on_CheckBox_DistanceSet_stateChanged(int arg1)
{
    if(ui->CheckBox_DistanceSet->isChecked())
    {
        ui->lineEdit_Distance->setDisabled(false);
    }
    else
    {
        ui->lineEdit_Distance->setDisabled(true);
    }
}


void MotionControll::on_btn_GoEnd_clicked()
{
    //M201.5
    if(ptrPLC->Connected())
    {
        byte buff = 1;
        ptrPLC->WriteArea(0x83, 1, 1613, 1, 1, &buff);
        buff = 0;
        ptrPLC->WriteArea(0x83, 1, 1613, 1, 1, &buff);
    }
}

void MotionControll::on_btn_Stop_clicked()
{
    //M201.4
    if(ptrPLC->Connected())
    {
        if(!m_bStatus)
        {
            byte buff = 1;
            ptrPLC->WriteArea(0x83, 1, 1612, 1, 1, &buff);
            ui->btn_Stop->setStyleSheet("background:rgb(0,200,0)");
            ui->btn_Stop->setText("Continue");
            m_bStatus = true;
        }
        else
        {
            byte buff = 0;
            ptrPLC->WriteArea(0x83, 1, 1612, 1, 1, &buff);
            ui->btn_Stop->setStyleSheet("background:rgb(200,100,70)");
            ui->btn_Stop->setText("Pause");
            m_bStatus = false;
        }
    }
}

void MotionControll::on_btn_GoBeginMannul_pressed()
{
    //M200.2
    if(ptrPLC->Connected())
    {
        byte buff = 1;
        ptrPLC->WriteArea(0x83, 1, 1603, 1, 1, &buff);
    }
}

void MotionControll::on_btn_GoBeginMannul_released()
{
    //M200.2
    if(ptrPLC->Connected())
    {
        byte buff = 0;
        ptrPLC->WriteArea(0x83, 1, 1603, 1, 1, &buff);
    }
}

void MotionControll::on_btn_GoEndMannul_pressed()
{
    //M200.3
    if(ptrPLC->Connected())
    {
        byte buff = 1;
        ptrPLC->WriteArea(0x83, 1, 1602, 1, 1, &buff);
    }
}

void MotionControll::on_btn_GoEndMannul_released()
{
    //M200.3
    if(ptrPLC->Connected())
    {
        byte buff = 0;
        ptrPLC->WriteArea(0x83, 1, 1602, 1, 1, &buff);
    }
}

void MotionControll::on_lineEdit_Distance_editingFinished()
{
    //M100
    if(ptrPLC->Connected())
    {
        const int Len = 4;
        float Dis = ui->lineEdit_Distance->text().toFloat();
        if(Dis > 570)
            return;

        QByteArray array;
        array.resize(Len);
        memcpy(array.data(), &Dis, Len);
        byte buff[Len];
        for(int i = 0; i<array.size(); i++)
        {
            buff[i] = array[i];
        }

        for(int i=0; i<Len; i++)
        {
        ptrPLC->WriteArea(0x83, 1, 100+Len-1-i, 1, 0x02, &buff[i]);
//        ptrPLC->WriteArea(0x83, 1, 102, 1, 0x02, &buff[1]);
//        ptrPLC->WriteArea(0x83, 1, 101, 1, 0x02, &buff[2]);
//        ptrPLC->WriteArea(0x83, 1, 100, 1, 0x02, &buff[3]);
        }


//        qDebug()<<Dis<<buff[0]<<buff[1]<<buff[2]<<buff[3];
    }
}

void MotionControll::on_btn_Zero_clicked()
{
    //M202.1
    if(ptrPLC->Connected())
    {
        byte buff = 1;
        ptrPLC->WriteArea(0x83, 1, 1617, 1, 1, &buff);
        buff = 0;
        ptrPLC->WriteArea(0x83, 1, 1617, 1, 1, &buff);
    }
}

void MotionControll::readHorisonVal()
{
    if(this->isVisible())
    {
        const int Len = 4;
        float Dis;

        QByteArray array;
        array.resize(Len);

		byte buff[Len] = { 0 };

		ptrPLC->DBRead(3, 66, Len, buff);

      //  ptrPLC->ReadArea(0x83, 1, 10, 1, 0x08, buff);
        for(int i = 0; i<array.size(); i++)
        {
            array[i] = buff[Len-1-i];
        }
		float aa;

		memcpy(&aa, array, 4);
       // memcpy(&Dis, array.data(), Len);*/
        ui->label_HorisonPos->setText(QString("%1").arg(aa));
    }
}

void MotionControll::on_btn_Disconnect_clicked()
{
    if(ptrPLC->Connected())
    {
        ptrPLC->Disconnect();
        ui->btn_Connect->setDisabled(false);
        m_timer.stop();
    }
}
