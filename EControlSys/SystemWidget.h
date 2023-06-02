#pragma once

#include <QWidget>
#include "ui_SystemWidget.h"
#include <QList>
class SystemWidget : public QWidget
{
	Q_OBJECT

public:
	SystemWidget(QWidget *parent = Q_NULLPTR);
	~SystemWidget();

private:
	Ui::SystemWidget ui;
	QList<QWidget*> m_lstWidget;
	void SetWdVisible(int wdindex);
public slots:
	void on_listwidget_itemClicked(QListWidgetItem *item);
};
