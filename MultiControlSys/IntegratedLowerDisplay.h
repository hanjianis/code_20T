#pragma once

#include <QWidget>
#include <QTimer>
#include<QCoreApplication>

//下面出现的显示界面
namespace Ui {
class IntegratedLowerDisplay;
}

class IntegratedLowerDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit IntegratedLowerDisplay(QWidget *parent = nullptr);
    ~IntegratedLowerDisplay();
    QTimer* dataupdate;
    int i=0;
    void updateData();
    bool Display_End;


public slots:
    void on_timeout();//定时器回调
   // void slot_updateData();
    //显示数据停止变化
    void slot_displaylowend();


signals:
 //  void sig_updateData();

private:
    Ui::IntegratedLowerDisplay *ui;
};
