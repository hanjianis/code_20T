#include "KaoShiManage.h"
#include <QSqlQuery>
#include "GlobalManager.h"
#include "LogMgr.h"
#include <QMenu>
#include <QDebug>
#include "TaskDetailDlg.h"
#include "EditTaskDlg.h"
KaoShiManage::KaoShiManage(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.tableWidget->setAlternatingRowColors(true);
	ui.tableWidget->verticalHeader()->setVisible(false);
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	InitTable();
	CreateMenus();
}

KaoShiManage::~KaoShiManage()
{
}
void KaoShiManage::CreateMenus()
{

	ui.tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);

	QMenu * chartMenu = new QMenu(this);

	chartMenu->addAction(ui.acStart);
	chartMenu->addAction(ui.acPause);
	chartMenu->addAction(ui.acStop);
	chartMenu->addAction(ui.acDetail);
	chartMenu->addAction(ui.acDelTask);
	chartMenu->addAction(ui.acEditTask);
//	chartMenu->addAction(ui.acReplay);
	chartMenu->addAction(ui.acTeacherScore);
	connect(ui.tableWidget, &QWidget::customContextMenuRequested, [=](const QPoint &pos)
	{
		qDebug() << pos;
		chartMenu->exec(QCursor::pos());
	});
}
void KaoShiManage::InitTable()
{
	QBrush bruship = QBrush(QColor(90, 90, 255));
	QBrush brushop(QColor(83, 158, 216));
	QBrush brushstate_finished(QColor(102, 204, 102));
	QString str;
	QString sql = QString("select * from tasks_list where mode=2;");
	QSqlQuery query(sql);
	int row = 0;
	ui.tableWidget->setRowCount(row);
	while (query.next())
	{
		int column = 0;
		ui.tableWidget->setRowCount(row + 1);

		QTableWidgetItem* item = new QTableWidgetItem(QString("%1").arg(row + 1));
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget->setItem(row, column++, item);
		
		item = new QTableWidgetItem(query.value("task_id").toString());
		item->setForeground(bruship);
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget->setItem(row, column++, item);

		item = new QTableWidgetItem(query.value("name").toString());
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget->setItem(row, column++, item);

		item = new QTableWidgetItem(query.value("subject").toString());
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget->setItem(row, column++, item);


		item = new QTableWidgetItem(query.value("user_login_name").toString());
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget->setItem(row, column++, item);


		item = new QTableWidgetItem(query.value("startTm1").toString());
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget->setItem(row, column++, item);

		item = new QTableWidgetItem(query.value("startTm2").toString());
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget->setItem(row, column++, item);

		item = new QTableWidgetItem(query.value("endTm").toString());
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

		str = LogMgr::GetInstance()->FormatFloatNum(query.value("compu_score").toFloat());
		item = new QTableWidgetItem(str);
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget->setItem(row, column++, item);

		str = LogMgr::GetInstance()->FormatFloatNum(query.value("teacher_score").toFloat());
		item = new QTableWidgetItem(str);
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget->setItem(row, column++, item);

		str = LogMgr::GetInstance()->FormatFloatNum(query.value("score").toFloat());
		item = new QTableWidgetItem(str);
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget->setItem(row, column++, item);

		item = new QTableWidgetItem(QString::fromLocal8Bit("详情"));
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		item->setForeground(brushop);
		ui.tableWidget->setItem(row, column++, item);


		row++;

	}

	ui.tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
}

void KaoShiManage::refresh()
{
	InitTable();
}

void KaoShiManage::on_acDetail_triggered()
{
	int row = ui.tableWidget->currentItem()->row();
	QString str = ui.tableWidget->item(row, 1)->text();
	TaskDetailDlg dlg(str, this);

	dlg.exec();
}

void KaoShiManage::on_acStart_triggered()
{
	//拿到当前任务信息 保存起来 使得后面的操作匹配起来
	int row = ui.tableWidget->currentItem()->row();
	CurrentTask curTask;
	curTask.subject = ui.tableWidget->item(row, 3)->text();
	curTask.task_id = ui.tableWidget->item(row, 1)->text();
	curTask.task_name = ui.tableWidget->item(row, 2)->text();
	curTask.user_login_name = ui.tableWidget->item(row, 6)->text();
	bool bFlag = GlobalManager::getInstance()->AddCurTask(curTask);
	if (bFlag)
	{
		QString str = LogMgr::GetInstance()->GetCurrentTimeString();
		//修改数据 开始时间 状态
		QString sql = QString("update tasks_list set startTm2='%1',state=1 where task_id='%2';").arg(str).arg(curTask.task_id);
		QSqlQuery query(sql);
		//修改当前table
		ui.tableWidget->item(row, 8)->setText(str);
		str = GlobalManager::getInstance()->ConvertStateToString(1);
		ui.tableWidget->item(row, 10)->setText(str);
	}
}

void KaoShiManage::on_acStop_triggered()
{
	int row = ui.tableWidget->currentItem()->row();
	CurrentTask curTask;
	curTask.subject = ui.tableWidget->item(row, 3)->text();
	curTask.task_id = ui.tableWidget->item(row, 1)->text();
	curTask.task_name = ui.tableWidget->item(row, 2)->text();
	curTask.user_login_name = ui.tableWidget->item(row, 6)->text();
	GlobalManager::getInstance()->RemoveCurTask(curTask.subject);

	QString str = LogMgr::GetInstance()->GetCurrentTimeString();
	//修改数据 开始时间 状态
	QString sql = QString("update tasks_list set endTm='%1',state=2 where task_id='%2';").arg(str).arg(curTask.task_id);
	QSqlQuery query(sql);
	//修改当前table
	ui.tableWidget->item(row, 9)->setText(str);
	str = GlobalManager::getInstance()->ConvertStateToString(2);
	ui.tableWidget->item(row, 10)->setText(str);
}

void KaoShiManage::on_acPause_triggered()
{

}

void KaoShiManage::on_acDelTask_triggered()
{
	int row = ui.tableWidget->currentItem()->row();
	QString task_id = ui.tableWidget->item(row, 1)->text();

	QString sql = QString("update tasks_list set del=1 where task_id='%1';").arg(task_id);
	QSqlQuery query;
	if (query.exec(sql))
	{
		GlobalManager::getInstance()->ShowMessageBox(QString::fromLocal8Bit("删除成功！"));
		ui.tableWidget->removeRow(row);
	}

}

void KaoShiManage::on_acEditTask_triggered()
{
	int row = ui.tableWidget->currentItem()->row();
	TaskInfo curTask;
	curTask.subject = ui.tableWidget->item(row, 3)->text();
	curTask.task_id = ui.tableWidget->item(row, 1)->text();
	curTask.task_name = ui.tableWidget->item(row, 2)->text();
	curTask.user_login_name = ui.tableWidget->item(row, 6)->text();
	curTask.mode = ui.tableWidget->item(row, 4)->text() == QString::fromLocal8Bit("训练模式") ? 1 : 2;
	EditTaskDlg dlg;
	dlg.SetCurTask(curTask);
	if (dlg.exec() == QDialog::Accepted)
	{
		curTask = dlg.m_curTask;
		//更新这一列
		qDebug() << curTask.task_name;
		ui.tableWidget->item(row, 3)->setText(curTask.subject);
		ui.tableWidget->item(row, 2)->setText(curTask.task_name);
		ui.tableWidget->item(row, 6)->setText(curTask.user_login_name);
		ui.tableWidget->item(row, 4)->setText(GlobalManager::getInstance()->ConvertModeToString(curTask.mode));
	}
}

void KaoShiManage::on_acReplay_triggered()
{
	GlobalManager::getInstance()->ShowMessageBox(QString::fromLocal8Bit("暂未开放！！！"));
}

void KaoShiManage::on_acTeacherScore_triggered()
{
	GlobalManager::getInstance()->ShowMessageBox(QString::fromLocal8Bit("暂未开放！！！"));
}

void KaoShiManage::on_tableWidget_itemClicked(QTableWidgetItem* item)
{
	if(item->column() == 12)//详情
		on_acDetail_triggered();
}

void KaoShiManage::on_query_clicked()
{
	//查询
	QString strSubject = ui.lineEdit->text();
	QString strClass = ui.lineEdit_2->text();
	//
	//QString sql = QString("select * from tasks_list where mode=2 and ;");
	//QSqlQuery query(sql);
}
