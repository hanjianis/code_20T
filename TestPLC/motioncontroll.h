#ifndef MOTIONCONTROLL_H
#define MOTIONCONTROLL_H

#include <QWidget>
#include <QTimer>
#include "snap7.h"

namespace Ui {
class MotionControll;
}

class MotionControll : public QWidget
{
    Q_OBJECT

public:
    explicit MotionControll(QWidget *parent = 0);
    ~MotionControll();

private slots:
    void on_btn_Connect_clicked();

    void on_btn_RotateStart_clicked();

    void on_btn_RotateStop_clicked();

    void on_CheckBox_DistanceSet_stateChanged(int arg1);

    void on_btn_GoEnd_clicked();

    void on_btn_Stop_clicked();

    void on_btn_GoBeginMannul_pressed();

    void on_btn_GoBeginMannul_released();

    void on_btn_GoEndMannul_pressed();

    void on_btn_GoEndMannul_released();

    void on_lineEdit_Distance_editingFinished();

    void on_btn_Zero_clicked();

    void readHorisonVal();

    void on_btn_Disconnect_clicked();

private:
    Ui::MotionControll *ui;

    TS7Client *ptrPLC;
    bool m_bStatus;

    QTimer m_timer;
};

#endif // MOTIONCONTROLL_H
