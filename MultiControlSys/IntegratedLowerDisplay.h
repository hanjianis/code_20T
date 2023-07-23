#pragma once

#include <QWidget>
#include <QTimer>
#include<QCoreApplication>


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

public slots:
    void on_timeout();//定时器回调
   // void slot_updateData();

signals:
 //  void sig_updateData();

private:
    Ui::IntegratedLowerDisplay *ui;
};
