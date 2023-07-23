#ifndef INTEGRAEDCONFIRMDLG_H
#define INTEGRAEDCONFIRMDLG_H

#include <QDialog>
//综合测试弹出框的确认框
namespace Ui {
class IntegraedconfirmDlg;
}

class IntegraedconfirmDlg : public QDialog
{
    Q_OBJECT

public:
    explicit IntegraedconfirmDlg(QWidget *parent = nullptr);
    ~IntegraedconfirmDlg();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::IntegraedconfirmDlg *ui;

public slots:
    void slot_value(QString,QString,QString,QString);

signals:
    void sig_closeIntegratedtestdialog();
};

#endif // INTEGRAEDCONFIRMDLG_H

