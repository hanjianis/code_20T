#include "MakeSureDlg.h"
#include <QDesktopWidget>
#include "GlobalManager.h"
#include "Packet.h"
MakeSureDlg::MakeSureDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	ui.label_6->setText(GlobalManager::getInstance()->_missileName);
	ui.label_3->setText(GlobalManager::getInstance()->_missileType);
	setWindowFlags(Qt::FramelessWindowHint);
	QDesktopWidget* desktop = QApplication::desktop(); // =qApp->desktop();р╡©ирт
	//move((desktop->width() - this->width()) / 2, (desktop->height() - this->height()) / 2);
	move((WIDTH - this->width()) / 2, (desktop->height() - this->height()) / 2);
}

MakeSureDlg::~MakeSureDlg()
{
}

void MakeSureDlg::on_ok_clicked()
{
	QDialog::accept();
	close();
}

void MakeSureDlg::on_cancel_clicked()
{
	QDialog::reject();
	close();
}
