#pragma once
#include <QDialog>
#include "Integraedconfirmdlg.h"

namespace Ui {
class IntegratedTestDialog;
}

class IntegratedTestDialog : public QDialog
{
    Q_OBJECT

public:
    explicit IntegratedTestDialog(QWidget *parent = nullptr);
    ~IntegratedTestDialog();    

    IntegraedconfirmDlg* m_intercongirm;

private:
    Ui::IntegratedTestDialog *ui;
    QWidget* m_parent;

public slots:
    void slot_closeIntegratedtestdialog(); //关闭界面
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

signals:
    void sig_value(QString,QString,QString,QString);  //发送值


};


