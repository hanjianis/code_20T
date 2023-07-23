#ifndef DIAGNOSTICPAUSE_H
#define DIAGNOSTICPAUSE_H

#include <QDialog>

namespace Ui {
class DiagnosticPause;
}

class DiagnosticPause : public QDialog
{
    Q_OBJECT

public:
    explicit DiagnosticPause(QWidget *parent = nullptr);
    ~DiagnosticPause();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

signals:
    void sig_diagnosticpause();

private:
    Ui::DiagnosticPause *ui;
};

#endif // DIAGNOSTICPAUSE_H
