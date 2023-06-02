#pragma once

#include <QWidget>
#include "ui_WeightManageWidget.h"

class WeightManageWidget : public QWidget
{
	Q_OBJECT

public:
	WeightManageWidget(QWidget *parent = Q_NULLPTR);
	~WeightManageWidget();

private:
	Ui::WeightManageWidget ui;
public slots:
	void on_lineEdit_editingFinished();
	void on_lineEdit_2_editingFinished();
};
