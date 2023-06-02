#include "ControlWidget.h"
#include <QSqlQuery>
#include <QDebug>
#include "GlobalManager.h"
#include <QMenu>
#include "TaskDetailDlg.h"
#include "Packet.h"
#include "MsgManager.h"
#include "LogMgr.h"
#include <QDateTime>
#include "EditTaskDlg.h"
QString  _SelectStyle = QString("background-color: rgb(170, 255, 255);");
//QString _SelectStyle = QString("background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #DEF0FE,stop:1 #C0DEF6);");
ControlWidget::ControlWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	InitUI();
	//
	connect(ui.treeWidget, SIGNAL(itemClicked(QTreeWidgetItem *, int );), this, SLOT(on_treeWidget_itemClicked(QTreeWidgetItem *, int)));
	//connect(ui.tableWidget, SIGNAL(itemClicked(QTableWidgetItem *)), this, SLOT(on_tableWidget_itemClicked(QTableWidgetItem*)));
	connect(GlobalManager::getInstance(), SIGNAL(UpdateTaskList(TaskInfo&)), this, SLOT(UpdateTaskListSlot(TaskInfo&)));
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); 
	ui.tableWidget->setAlternatingRowColors(true);
	ui.tableWidget->verticalHeader()->setVisible(false);
	ui.tableWidget->horizontalHeader()->setSortIndicatorShown(true);
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_bUpOrDown = false;
	connect(ui.tableWidget->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(sortTableByCol(int)));

	//ui.tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.tableWidget_2->setAlternatingRowColors(true);
	ui.tableWidget_2->verticalHeader()->setVisible(false);
	ui.tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
	int column = 0;
	ui.tableWidget_2->setColumnWidth(column++, 80);
	ui.tableWidget_2->setColumnWidth(column++, 150);
	ui.tableWidget_2->setColumnWidth(column++, 150);
	ui.tableWidget_2->setColumnWidth(column++, 150);
	ui.tableWidget_2->setColumnWidth(column++, 700);//动作名称
	ui.tableWidget_2->setColumnWidth(column++, 150);
	ui.tableWidget_2->setColumnWidth(column++, 200);
	InitTable();

	on_pushButton_3_clicked();
	on_list_toolbutton_clicked();
	
	//创建菜单
	CreateMenus();
}

ControlWidget::~ControlWidget()
{
}

void ControlWidget::InitTable()
{
	QString sql = QString("select * from tasks_list where del=0;");
	
	InitTable(sql);
	
}

void ControlWidget::InitTable(QString sql)
{
	QBrush bruship = QBrush(QColor(90, 90, 255));
	QBrush brushop(QColor(83, 158, 216));
	QBrush brushstate_finished(QColor(102, 204, 102));
	QString str;

	QSqlQuery query(sql);
	int row = 0;
	ui.tableWidget->setRowCount(row);
	while (query.next())
	{

		TaskInfo tsinfo;
		tsinfo.id = query.value("id").toInt();
		tsinfo.task_id = query.value("task_id").toString();
		tsinfo.plan_id = query.value("plan_id").toString();
		tsinfo.task_name = query.value("name").toString();
		tsinfo.subject = query.value("subject").toString();
		tsinfo.mode = query.value("mode").toInt();
		tsinfo.type = query.value("type").toInt();
		tsinfo.user_login_name = query.value("user_login_name").toString();
		tsinfo.startTm1 = query.value("startTm1").toString();
		tsinfo.startTm2 = query.value("startTm2").toString();
		tsinfo.endTm = query.value("endTm").toString();

		tsinfo.state = query.value("state").toInt();

		AddTableWidget(tsinfo);
	
	}
}

void ControlWidget::InitTable2(QString sql)
{
	
	/*id	task_id	acname	subject	tm	state	taskname	user_login_name
		1	TASK_014	启动	导弹测试	2020 - 12 - 21	2	777	7987*/
	QBrush bruship = QBrush(QColor(90, 90, 255));
	QBrush brushop(QColor(83, 158, 216));
	QBrush brushstate_finished(QColor(102, 204, 102));
	QString str;

	QSqlQuery query(sql);
	int row = 0;
	ui.tableWidget_2->setRowCount(row);
	
	while (query.next())
	{
		int column = 0;
		ui.tableWidget_2->insertRow(0);
	
		row = ui.tableWidget_2->rowCount();
		ui.tableWidget_2->setRowCount(row);
	
		QTableWidgetItem* item = new QTableWidgetItem(QString("%1").arg(row + 1));
		row = 0;
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget_2->setItem(row, column++, item);

		item = new QTableWidgetItem(query.value("task_id").toString());
		item->setForeground(bruship);
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget_2->setItem(row, column++, item);

		item = new QTableWidgetItem(query.value("taskname").toString());
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget_2->setItem(row, column++, item);

		item = new QTableWidgetItem(query.value("subject").toString());
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget_2->setItem(row, column++, item);

		item = new QTableWidgetItem(query.value("acname").toString());
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget_2->setItem(row, column++, item);

		item = new QTableWidgetItem(query.value("user_login_name").toString());
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget_2->setItem(row, column++, item);

		item = new QTableWidgetItem(query.value("tm").toString());
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget_2->setItem(row, column++, item);

		row++;


	}
}

void ControlWidget::CreateMenus()
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

	connect(ui.tableWidget, &QWidget::customContextMenuRequested, [=](const QPoint &pos)
	{
		qDebug() << pos;
		chartMenu->exec(QCursor::pos());
	});
}

void ControlWidget::AddTableWidget(TaskInfo tsinfo)
{
	QBrush bruship = QBrush(QColor(90, 90, 255));
	QBrush brushop(QColor(83, 158, 216));
	QBrush brushstate_finished(QColor(102, 204, 102));
	QString str;

	ui.tableWidget->insertRow(0);

	int row = ui.tableWidget->rowCount();

	QTableWidgetItem* item = new QTableWidgetItem(QString("%1").arg(row ));
	int column = 0;
	row = 0;
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	item->setData(Qt::UserRole, tsinfo.id);
	ui.tableWidget->setItem(row, column++, item);

	item = new QTableWidgetItem(tsinfo.task_id);
	item->setForeground(bruship);
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.tableWidget->setItem(row, column++, item);

	item = new QTableWidgetItem(tsinfo.task_name);
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.tableWidget->setItem(row, column++, item);

	item = new QTableWidgetItem(tsinfo.subject);
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.tableWidget->setItem(row, column++, item);

	str = GlobalManager::getInstance()->ConvertModeToString(tsinfo.mode);
	item = new QTableWidgetItem(str);
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.tableWidget->setItem(row, column++, item);

	str = GlobalManager::getInstance()->ConvertTypeToString(tsinfo.type);
	item = new QTableWidgetItem(str);
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.tableWidget->setItem(row, column++, item);


	item = new QTableWidgetItem(tsinfo.user_login_name);
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.tableWidget->setItem(row, column++, item);


	item = new QTableWidgetItem(tsinfo.startTm1);
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.tableWidget->setItem(row, column++, item);

	item = new QTableWidgetItem(tsinfo.startTm2);
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.tableWidget->setItem(row, column++, item);

	item = new QTableWidgetItem(tsinfo.endTm);
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.tableWidget->setItem(row, column++, item);

	int state = tsinfo.state;
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

	//QLabel* label = new QLabel(QString::fromLocal8Bit("详情"));
	//label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	//label->setStyleSheet("color: rgb(83, 158, 216);");
	//connect(label, SIGNAL(), this, SLOT());
	item = new QTableWidgetItem(QString::fromLocal8Bit("详情"));
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	item->setForeground(brushop);
	ui.tableWidget->setItem(row, column++, item);
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(row,QHeaderView::ResizeToContents);
}

void ControlWidget::InitUI()
{
	ui.dateEdit->setDate(QDateTime::currentDateTime().date());
	ui.comboBox->addItem(QString::fromLocal8Bit("全部"));
	QMap<QString, SubjectInfo>::iterator it = GlobalManager::getInstance()->m_mapSubjects.begin();//key 科目名称
	while (it != GlobalManager::getInstance()->m_mapSubjects.end())
	{
		ui.comboBox->addItem(it->subject_name);
		it++;
	}
}

void ControlWidget::sortTableByCol(int col)
{
	if (m_bUpOrDown)		//sortUpDown为自定义的一个bool变量，表示升序还是降序
	{
		ui.tableWidget->sortItems(col, Qt::AscendingOrder);
		m_bUpOrDown = false;
	}
	else
	{
		ui.tableWidget->sortItems(col, Qt::DescendingOrder);
		m_bUpOrDown = true;
	}
}

void ControlWidget::UpdateTaskListSlot(TaskInfo& tsinfo)
{
	qDebug() << "==================";
	AddTableWidget(tsinfo);
}

void ControlWidget::on_replay_toolbutton_clicked()
{

	ui.list_toolbutton->setStyleSheet("");
	ui.replay_toolbutton->setStyleSheet(_SelectStyle);
	ui.list_widget->setVisible(false);
	ui.replay_widget->setVisible(true);
	
}

void ControlWidget::on_list_toolbutton_clicked()
{
	ui.list_toolbutton->setStyleSheet(_SelectStyle);
	ui.replay_toolbutton->setStyleSheet("");
	ui.list_widget->setVisible(true);
	ui.replay_widget->setVisible(false);
}

void ControlWidget::on_pushButton_clicked()
{
	QString taskname = ui.lineEdit->text();//
	QString username = ui.lineEdit_2->text();

	QString sql = QString("select * from tasks_list ");
	QString sqlwhere;
	if (!taskname.isEmpty() && !username.isEmpty())
	{
		sqlwhere = QString(" where name LIKE '%%1%' and user_login_name LIKE '%%2%' and del=0").arg(taskname).arg(username);
	}
	if (!username.isEmpty() && taskname.isEmpty())
	{
		sqlwhere = QString(" where user_login_name LIKE '%%1%' and del=0").arg(username);
	}
	if (!taskname.isEmpty() && username.isEmpty())
	{
		sqlwhere = QString(" where name LIKE '%%1%' and del=0").arg(taskname);
	}
	sql.append(sqlwhere);
	
	qDebug() << sql;
	InitTable(sql);
}

void ControlWidget::on_pushButton_2_clicked()
{
	ui.lineEdit->setText("");
	ui.lineEdit_2->setText("");
	on_pushButton_clicked();
}

void ControlWidget::on_pushButton_3_clicked()
{
	//获取日期
	QString str = ui.dateEdit->text();
	QString sql;
	if(ui.comboBox->currentIndex() == 0)//第一个 全部
		sql = QString("select task_log.id as id,task_log.task_id as task_id, task_log.acname as acname,tasks_list.subject as subject,task_log.tm as tm,\
		task_log.state as state,tasks_list.name as taskname,tasks_list.user_login_name as user_login_name\
		from task_log, tasks_list where tasks_list.task_id = task_log.task_id and task_log.tm >='%1'").arg(str);
	else
		sql = QString("select task_log.id as id,task_log.task_id as task_id, task_log.acname as acname,tasks_list.subject as subject,task_log.tm as tm,\
		task_log.state as state,tasks_list.name as taskname,tasks_list.user_login_name as user_login_name\
		from task_log, tasks_list where tasks_list.task_id = task_log.task_id and task_log.tm >='%1' and subject='%2'").arg(str).arg(ui.comboBox->currentText());
	
	qDebug() << sql;
	InitTable2(sql);
}

void ControlWidget::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
	qDebug() << item->text(0);
	if (item->parent() == nullptr)//全部
	{
		InitTable();
		return;
	}
	//
	 QString sql = QString("select * from tasks_list where subject = '%1'  and del=0;").arg(item->text(0));
	 InitTable(sql);
}

void ControlWidget::on_tableWidget_itemClicked(QTableWidgetItem* item)
{
	qDebug() << item->column();
	if (item->column() == 11)
	{
		//详情
		on_acDetail_triggered();
	}
}

void ControlWidget::on_acDetail_triggered()
{
	int row = ui.tableWidget->currentItem()->row();
	QString str = ui.tableWidget->item(row, 1)->text();
	TaskDetailDlg dlg(str,this);
	dlg.exec();
}

void ControlWidget::on_acStart_triggered()
{
	//拿到当前任务信息 保存起来 使得后面的操作匹配起来
	int row = ui.tableWidget->currentItem()->row();
	CurrentTask curTask;
	curTask.subject = ui.tableWidget->item(row, 3)->text();
	curTask.task_id = ui.tableWidget->item(row, 1)->text();
	curTask.task_name = ui.tableWidget->item(row,2)->text();
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

void ControlWidget::on_acStop_triggered()
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

void ControlWidget::on_acPause_triggered()
{
	int row = ui.tableWidget->currentItem()->row();
	CurrentTask curTask;
	curTask.subject = ui.tableWidget->item(row, 3)->text();
	curTask.task_id = ui.tableWidget->item(row, 1)->text();
	curTask.task_name = ui.tableWidget->item(row, 2)->text();
	curTask.user_login_name = ui.tableWidget->item(row, 6)->text();
	GlobalManager::getInstance()->RemoveCurTask(curTask.subject);

	QString str = LogMgr::GetInstance()->GetCurrentTimeString();
	//修改数据 开始时间 状态 3是暂停
	QString sql = QString("update tasks_list set endTm='%1',state=3 where task_id='%2';").arg(str).arg(curTask.task_id);
	QSqlQuery query(sql);
	//修改当前table
	ui.tableWidget->item(row, 9)->setText(str);
	str = GlobalManager::getInstance()->ConvertStateToString(3);
	ui.tableWidget->item(row, 10)->setText(str);
}

void ControlWidget::on_acDelTask_triggered()
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
	//
}

void ControlWidget::on_acEditTask_triggered()
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

void ControlWidget::on_acReplay_triggered()
{
	GlobalManager::getInstance()->ShowMessageBox(QString::fromLocal8Bit("暂未开放！！！"));
}

void ControlWidget::refresh()
{
	InitTable();
}

void ControlWidget::AddTaskLog(int msgid)
{

	//查找属于的任务
	PCurrentTask pCurTask = GlobalManager::getInstance()->GetCurTask(msgid);
	if (pCurTask == nullptr)
	{
		pCurTask = GlobalManager::getInstance()->GenerateOneTask(GlobalManager::getInstance()->GetSubject(msgid));
	}
	if(pCurTask != nullptr)
	{
		PMsgNetData pNet = MsgManager::GetInstance()->getMsgNet(msgid);
		if (pNet != nullptr)
		{
			QString str = LogMgr::GetInstance()->GetCurrentTimeString();
			//需要添加到数据库
			QString sql = QString("INSERT INTO [dbo].[task_log] (task_id, acname, state, tm,acid,acsoft) VALUES ( '%1', '%2', 2, '%3',%4,'%6'); ")
				.arg(pCurTask->task_id)
				.arg(pNet->note)
				.arg(str)
				.arg(pNet->id)
				.arg(pNet->soft);
			QSqlQuery query(sql);

			ui.tableWidget_2->insertRow(0);

			int row = ui.tableWidget_2->rowCount();

			int column = 0;
			int index = 0;
			QTableWidgetItem* item = new QTableWidgetItem(QString("%1").arg(row));
			item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			ui.tableWidget_2->setItem(index, column++, item);

			item = new QTableWidgetItem(pCurTask->task_id);
			item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			ui.tableWidget_2->setItem(index, column++, item);

			item = new QTableWidgetItem(pCurTask->task_name);
			item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			ui.tableWidget_2->setItem(index, column++, item);

			item = new QTableWidgetItem(pCurTask->subject);
			item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			ui.tableWidget_2->setItem(index, column++, item);

			item = new QTableWidgetItem(QString("%1").arg(pNet->note));
			item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			ui.tableWidget_2->setItem(index, column++, item);

			item = new QTableWidgetItem(pCurTask->user_login_name);
			item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			ui.tableWidget_2->setItem(index, column++, item);

			item = new QTableWidgetItem(str);
			item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			ui.tableWidget_2->setItem(index, column++, item);

			ui.tableWidget_2->scrollToItem(item, QAbstractItemView::PositionAtCenter);
		}
	}
	if (msgid == eMsg_T_OnCloseApp)//综合测控软件 关闭
	{
		StopTask(pCurTask->task_id);
		//任务终止完成
		GlobalManager::getInstance()->RemoveCurTask(pCurTask->subject);
	}
}

void ControlWidget::StopTask(QString task_id)
{
	QString str = LogMgr::GetInstance()->GetCurrentTimeString();
	//修改数据 开始时间 状态
	QString sql = QString("update tasks_list set endTm='%1',state=2 where task_id='%2';").arg(str).arg(task_id);
	QSqlQuery query(sql);
	//update table 
	int row = -1;
	//查找所在的行
	for (int i = 0; i < ui.tableWidget->rowCount(); i++)
	{
		if (ui.tableWidget->item(i, 1)->text() == task_id)
		{
			row = i;
			break;
		}
	}
	if (row == -1)
		return;
	//
	ui.tableWidget->item(row, 9)->setText(str);
	str = GlobalManager::getInstance()->ConvertStateToString(2);
	ui.tableWidget->item(row, 10)->setText(str);
}
