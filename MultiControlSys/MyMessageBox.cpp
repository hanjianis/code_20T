#include "MyMessageBox.h"

MyMessageBox::MyMessageBox(QString title,QString content,QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowTitle(title);
	ui.label->setText(content);
}

MyMessageBox::~MyMessageBox()
{
}

void MyMessageBox::on_btnyes_clicked()
{
	QDialog::accept();
	close();
}

void MyMessageBox::on_btnno_clicked()
{
	QDialog::reject();
	close();
}
