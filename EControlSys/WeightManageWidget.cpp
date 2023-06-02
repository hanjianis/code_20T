#include "WeightManageWidget.h"
#include "GlobalManager.h"
#include <QDebug>
WeightManageWidget::WeightManageWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//³õÊ¼»¯
	QString str = QString("%1").arg(GlobalManager::getInstance()->_compuWeight);
	ui.lineEdit->setText(str);
	str = QString("%1").arg(GlobalManager::getInstance()->_teachWeight);
	ui.lineEdit_2->setText(str);
}

WeightManageWidget::~WeightManageWidget()
{
}

void WeightManageWidget::on_lineEdit_editingFinished()
{
	qDebug() << "=============================";
	GlobalManager::getInstance()->_compuWeight = ui.lineEdit->text().toFloat();
}

void WeightManageWidget::on_lineEdit_2_editingFinished()
{
	qDebug() << "=+++++++++++++++++++++++++";
	GlobalManager::getInstance()->_teachWeight = ui.lineEdit_2->text().toFloat();
}
