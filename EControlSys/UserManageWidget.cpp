#include "UserManageWidget.h"
#include <QSqlQuery>
#include <QDebug>
UserManageWidget::UserManageWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.tableWidget->setAlternatingRowColors(true);
	ui.tableWidget->verticalHeader()->setVisible(false);
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	QString sql = QString("select * from user_info where user_type=0;");
	
	InitTable(sql);
}

UserManageWidget::~UserManageWidget()
{
}
void UserManageWidget::InitTable(QString sql)
{
	ui.tableWidget->setRowCount(0);
	QBrush bruship = QBrush(QColor(90, 90, 255));
	QBrush brushop(QColor(83, 158, 216));
	//QString sql = QString("select * from user_info where user_type=0;");
	QSqlQuery query(sql);
	int row = 0;
	while (query.next())
	{
		int column = 0;
		ui.tableWidget->insertRow(0);

		QTableWidgetItem* item = new QTableWidgetItem(QString("%1").arg(ui.tableWidget->rowCount()));
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget->setItem(row, column++, item);


		item = new QTableWidgetItem(query.value("real_name").toString());
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget->setItem(row, column++, item);

		item = new QTableWidgetItem(query.value("login_name").toString());
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget->setItem(row, column++, item);

		item = new QTableWidgetItem(query.value("class").toString());
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget->setItem(row, column++, item);

		item = new QTableWidgetItem(query.value("tel").toString());
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget->setItem(row, column++, item);

		//item = new QTableWidgetItem(QString::fromLocal8Bit("±à¼­"));
		//item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		//item->setForeground(brushop);
		//ui.tableWidget->setItem(row, column++, item);

		ui.tableWidget->horizontalHeader()->setSectionResizeMode(row, QHeaderView::ResizeToContents);
	//	row++;

	}

}

void UserManageWidget::on_query_clicked()
{
	QString strNum = ui.lineEdit->text();
	QString strClass = ui.lineEdit_2->text();
	QString sql = QString("select * from user_info ");
	QString sqlwhere;
	if (!strNum.isEmpty() && !strClass.isEmpty())
	{
		sqlwhere = QString(" where login_name LIKE '%%1%' and class LIKE '%%2%' and user_type=0").arg(strNum).arg(strClass);
	}
	if (!strNum.isEmpty() && strClass.isEmpty())
	{
		sqlwhere = QString(" where login_name LIKE '%%1%' and user_type=0").arg(strNum);
	}
	if (!strClass.isEmpty() && strNum.isEmpty())
	{
		sqlwhere = QString(" where class LIKE '%%1%' and user_type=0").arg(strClass);
	}
	if (strClass.isEmpty() && strNum.isEmpty())
	{
		sqlwhere = QString(" where user_type=0").arg(strClass);
	}
	sql.append(sqlwhere);

	qDebug() << sql;
	InitTable(sql);
}

void UserManageWidget::on_reset_clicked()
{
	ui.lineEdit->setText("");
	ui.lineEdit_2->setText("");
	on_query_clicked();
}
