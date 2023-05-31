#include "MyToolTipDlg.h"

MyToolTipDlg::MyToolTipDlg(QString strTitle,QString content,QWidget *parent)
	: QDialog(parent)
{

	ui.setupUi(this);
	setWindowTitle(strTitle);
	ui.label->setText(content);
}

MyToolTipDlg::~MyToolTipDlg()
{
}

void MyToolTipDlg::on_pushButton_clicked()
{
	//
	QDialog::accept();
	close();
}
