#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ImportTools.h"
typedef struct MsgNetData
{
	int id;
	int softid;
	QString soft;
	QString note;
}*PMsgNetData;
class ImportTools : public QMainWindow
{
    Q_OBJECT

public:
    ImportTools(QWidget *parent = Q_NULLPTR);

private:
    Ui::ImportToolsClass ui;
	void Supplement(MsgNetData& dd);
public slots:
	void on_pushButton_clicked();
	void ConnectSQLServer();
	void InitMsg(QString strFile);
};
