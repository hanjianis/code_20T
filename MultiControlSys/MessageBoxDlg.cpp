#include "MessageBoxDlg.h"
#include "Packet.h"
#include <QDesktopWidget>
MessageBoxDlg::MessageBoxDlg(QString str,QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	ui.label_3->setText(str);
	setWindowFlags(Qt::FramelessWindowHint);
	resize(DLG_WIDTH, DLG_HEIGHT);
	QDesktopWidget* desktop = QApplication::desktop(); // =qApp->desktop();р╡©ирт
	//move((desktop->width() - this->width()) / 2, (desktop->height() - this->height()) / 2);
	move((WIDTH - this->width()) / 2, (desktop->height() - this->height()) / 2);
}

MessageBoxDlg::~MessageBoxDlg()
{
}


void MessageBoxDlg::on_pushButton_clicked()
{
	QDialog::accept();
	close();
}
