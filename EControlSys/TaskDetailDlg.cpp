#include "TaskDetailDlg.h"
#include <QSqlQuery>
#include "GlobalManager.h"
#include "LogMgr.h"
#include <QTableWidgetItem>
#include <QMouseEvent>
TaskDetailDlg::TaskDetailDlg(QString task_id, QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	//ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.tableWidget->setAlternatingRowColors(true);
	ui.tableWidget->verticalHeader()->setVisible(false);
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	_task_id = task_id;
	int column = 0;
	ui.tableWidget->setColumnWidth(column++, 80);
	ui.tableWidget->setColumnWidth(column++, 150);
	ui.tableWidget->setColumnWidth(column++, 700);//动作名称
	ui.tableWidget->setColumnWidth(column++, 120);
	ui.tableWidget->setColumnWidth(column++, 200);

	InitTable();

	ui.label_29->installEventFilter(this);//安装事件过滤器
	ui.label_25->installEventFilter(this);//安装事件过滤器
	ui.groupBox->setVisible(false);//默认不显示

}

TaskDetailDlg::~TaskDetailDlg()
{
}

void TaskDetailDlg::InitTable()
{
	QBrush bruship = QBrush(QColor(90, 90, 255));
	QBrush brushop(QColor(83, 158, 216));
	QBrush brushstate_finished(QColor(102, 204, 102));
	QString str,subject;
	QString sql = QString("select * from tasks_list where task_id='%1';").arg(_task_id);
	QSqlQuery query;
	query.exec(sql);
	while (query.next())
	{
		subject = query.value("subject").toString();
		str = GlobalManager::getInstance()->ConvertModeToString(query.value("mode").toInt());
		ui.label_2->setText(str);

		ui.label_3->setText(query.value("name").toString());

		ui.label_6->setText(query.value("task_id").toString());

		ui.label_10->setText(subject);

		ui.label_8->setText(query.value("user_login_name").toString());

		ui.label_12->setText(query.value("class").toString());

		str = GlobalManager::getInstance()->ConvertTypeToString(query.value("type").toInt());
		ui.label_14->setText(str);

		str = GlobalManager::getInstance()->ConvertTypeToString(query.value("type").toInt());
		ui.label_16->setText(str);

		str = GlobalManager::getInstance()->ConvertStateToString(query.value("state").toInt());
		ui.label_18->setText(str);

		ui.label_20->setText(query.value("startTm1").toString());

		ui.label_22->setText(query.value("startTm2").toString());
		ui.label_24->setText(query.value("endTm").toString());
	}

	sql = QString("select * from task_log where task_id='%1';").arg(_task_id);
	query.exec(sql);
	int row = 0;
	ui.tableWidget->setRowCount(row);
	while (query.next())
	{
		int column = 0;
		ui.tableWidget->setRowCount(row + 1);

		QTableWidgetItem* item = new QTableWidgetItem(QString("%1").arg(row + 1));
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget->setItem(row, column++, item);

		item = new QTableWidgetItem(subject);
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget->setItem(row, column++, item);

		item = new QTableWidgetItem(query.value("acname").toString());
		item->setForeground(bruship);
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget->setItem(row, column++, item);

		int state = query.value("state").toInt();
		str = GlobalManager::getInstance()->ConvertStateToString(state);
		item = new QTableWidgetItem(str);
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		if (state == 1)
		{
			item->setForeground(brushstate_finished);
		}
		if (state == 0)
		{
			item->setForeground(bruship);
		}
		ui.tableWidget->setItem(row, column++, item);

		item = new QTableWidgetItem(query.value("tm").toString());
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget->setItem(row, column++, item);

		row++;

	}
}

void TaskDetailDlg::on_toolButton_clicked()
{
	bool bVisible = ui.groupBox->isVisible();
	ui.groupBox->setVisible(!bVisible);
	if (bVisible)
	{
	//	ui.toolButton->setIcon(QIcon(":/EControlSys/res/u137.png"));
		ui.label_29->setStyleSheet("image: url(:/EControlSys/res/u136.png);");
	}
	else
	{
		//ui.toolButton->setIcon(QIcon(":/EControlSys/res/u136.png"));
		ui.label_29->setStyleSheet("image: url(:/EControlSys/res/u137.png);");
	}
}

bool TaskDetailDlg::eventFilter(QObject *obj, QEvent *event)
{
	if (obj == ui.label_29 || ui.label_25)
	{
		if (event->type() == QEvent::MouseButtonPress)//mouse button pressed
		{
			QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
			if (mouseEvent->button() == Qt::LeftButton)
			{
				on_toolButton_clicked();
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	return QDialog::eventFilter(obj, event);
}
