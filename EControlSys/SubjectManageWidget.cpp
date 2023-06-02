#include "SubjectManageWidget.h"
#include <QSqlQuery>
#include <QDebug>
#include "EditSubject.h"
SubjectManageWidget::SubjectManageWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.tableWidget->setAlternatingRowColors(true);
	ui.tableWidget->verticalHeader()->setVisible(false);
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	InitTable();
}

SubjectManageWidget::~SubjectManageWidget()
{
}
void SubjectManageWidget::InitTable()
{

	QBrush bruship = QBrush(QColor(90, 90, 255));
	QBrush brushop(QColor(83, 158, 216));
	QString sql = QString("select * from subject;");
	QSqlQuery query(sql);
	int row = 0;
	while (query.next())
	{
		int column = 0;
		ui.tableWidget->setRowCount(row+1);

		QTableWidgetItem* item = new QTableWidgetItem(QString("%1").arg(row + 1));
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		item->setData(Qt::UserRole, query.value("subject_name").toString());
		ui.tableWidget->setItem(row, column++, item);

		item = new QTableWidgetItem(QString("%1").arg(query.value("id").toInt()));
		item->setForeground(bruship);
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget->setItem(row, column++, item);

		item = new QTableWidgetItem(query.value("subject_name").toString());
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget->setItem(row, column++, item);

		item = new QTableWidgetItem(query.value("remark").toString());
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget->setItem(row, column++, item);


		item = new QTableWidgetItem(QString::fromLocal8Bit("编辑"));
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		item->setForeground(brushop);
		ui.tableWidget->setItem(row, column++, item);

		ui.tableWidget->horizontalHeader()->setSectionResizeMode(row, QHeaderView::ResizeToContents);
		row++;
	
	}

}

void SubjectManageWidget::on_tableWidget_itemClicked(QTableWidgetItem* item)
{
	qDebug() << item->column();
	if (item->column() == 4)
	{
		//详情
		QString devid = ui.tableWidget->item(item->row(), 0)->data(Qt::UserRole).toString();
		EditSubject dlg(devid);
		if (dlg.exec() == QDialog::Accepted)
		{
			//更新界面
			InitTable();
		}
	}
}
