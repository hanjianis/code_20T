#include "InputTemperatureDlg.h"
#include "GlobalManager.h"
#include <QDesktopWidget>
#include "Packet.h"
InputTemperatureDlg::InputTemperatureDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);
	resize(DLG_WIDTH, DLG_HEIGHT);
	QDesktopWidget* desktop = QApplication::desktop(); // =qApp->desktop();р╡©ирт
	//move((desktop->width() - this->width()) / 2, (desktop->height() - this->height()) / 2);
	move((WIDTH - this->width()) / 2, (desktop->height() - this->height()) / 2);
}

InputTemperatureDlg::~InputTemperatureDlg()
{
}

void InputTemperatureDlg::on_pushButton_clicked()
{
	GlobalManager::getInstance()->_currentTemp = ui.lineEdit->text().toFloat();
	QDialog::accept();
	close();
}
