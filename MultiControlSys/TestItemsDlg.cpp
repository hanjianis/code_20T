#include "TestItemsDlg.h"
#include "Packet.h"
#include <QDesktopWidget>
#include "AtmoTask.h"
#include "XLManager.h"
#include "PowerTask.h"
#include "AutoTestDlg.h"
#include "FeiKongTask.h"
#include "CPUTask.h"
#include "DPUTask.h"
#include "Task5.h"
#include "Task10.h"
#include "Task13.h"
TestItemsDlg::TestItemsDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	m_parent = parent;

	setWindowFlags(Qt::FramelessWindowHint);
	resize(DLG_WIDTH, DLG_HEIGHT);
	QDesktopWidget* desktop = QApplication::desktop(); // =qApp->desktop();也可以
	//move((desktop->width() - this->width()) / 2, (desktop->height() - this->height()) / 2);
	move((WIDTH - this->width()) / 2, (desktop->height() - this->height()) / 2);
    //hide();
}

TestItemsDlg::~TestItemsDlg()
{
}

void TestItemsDlg::AddTask(int param1)
{
	XLManager* pXL = XLManager::GetInstance();

	ITask* task2 = new ITask(param1, m_parent);
	pXL->m_lstTasks.push_back(task2);
}

void TestItemsDlg::on_btnok_clicked()
{
	//根据勾选 对AutoTestDlg的Task 进行添加任务
	XLManager* pXL = XLManager::GetInstance();
	AutoTestDlg* dlg = (AutoTestDlg*)m_parent;
	pXL->m_lstTasks.clear();
	ITask* task = new PowerTask(m_parent);
	pXL->m_lstTasks.push_back(task);
	if (ui.fkcszd->checkState() == Qt::Checked)
	{
		ITask* task3 = new FeiKongTask(m_parent);
		pXL->m_lstTasks.push_back(task3);
		
	}
	if (ui.zdjbk->checkState() == Qt::Checked)
	{
		ITask* task3 = new CPUTask(m_parent);
		pXL->m_lstTasks.push_back(task3);
	}
	if (ui.zdjck->checkState() == Qt::Checked)
	{
		ITask* task3 = new DPUTask(m_parent);
		pXL->m_lstTasks.push_back(task3);
	}
	if (ui.qyddbxt->checkState() == Qt::Checked)
	{
		ITask* task3 = new AtmoTask(m_parent);
		pXL->m_lstTasks.push_back(task3);
	}
	if (ui.dpujzt->checkState() == Qt::Checked)
	{
		ITask* task3 = new Task5(m_parent);
		pXL->m_lstTasks.push_back(task3);
	}
	if (ui.yxxt->checkState() == Qt::Checked)
	{
		AddTask(6);
	}
	if (ui.ldgdb->checkState() == Qt::Checked)
	{
		AddTask(7);
	}
	if (ui.dxt->checkState() == Qt::Checked)
	{
		AddTask(8);
	}
	if (ui.ywxhq->checkState() == Qt::Checked)
	{
		AddTask(9);
	}
	if (ui.xsjxxt->checkState() == Qt::Checked)
	{
		ITask* task3 = new Task10(m_parent);
		pXL->m_lstTasks.push_back(task3);
	}
	if (ui.zmxt->checkState() == Qt::Checked)
	{
		AddTask(11);
	}
	if (ui.dlxt->checkState() == Qt::Checked)
	{
		AddTask(12);
	}
	if (ui.dqxt->checkState() == Qt::Checked)
	{
		ITask* task3 = new Task13(m_parent);
		pXL->m_lstTasks.push_back(task3);
	}
	QDialog::accept();
	hide();
	
}

void TestItemsDlg::on_all_clicked()
{
	//ȫѡ
	if (ui.all->checkState() != Qt::CheckState::Unchecked)
	{
		//ui.all->setCheckState(Qt::CheckState::PartiallyChecked);
		ui.fkcszd->setCheckState(Qt::CheckState::Checked);
		ui.zdjbk->setCheckState(Qt::CheckState::Checked);
		ui.zdjck->setCheckState(Qt::CheckState::Checked);
		ui.qyddbxt->setCheckState(Qt::CheckState::Checked);
		ui.dpujzt->setCheckState(Qt::CheckState::Checked);
		ui.ldgdb->setCheckState(Qt::CheckState::Checked);
		ui.dlxt->setCheckState(Qt::CheckState::Checked);

		ui.dxt->setCheckState(Qt::CheckState::Checked);
		ui.ywxhq->setCheckState(Qt::CheckState::Checked);
		ui.xsjxxt->setCheckState(Qt::CheckState::Checked);
		ui.zmxt->setCheckState(Qt::CheckState::Checked);
		ui.dqxt->setCheckState(Qt::CheckState::Checked);
		ui.yxxt->setCheckState(Qt::CheckState::Checked);
	}
	else
	{
		//ui.all->setCheckState(Qt::CheckState::Unchecked);
		ui.fkcszd->setCheckState(Qt::CheckState::Unchecked);
		ui.zdjbk->setCheckState(Qt::CheckState::Unchecked);
		ui.zdjck->setCheckState(Qt::CheckState::Unchecked);
		ui.qyddbxt->setCheckState(Qt::CheckState::Unchecked);
		ui.dpujzt->setCheckState(Qt::CheckState::Unchecked);
		ui.ldgdb->setCheckState(Qt::CheckState::Unchecked);
		ui.dlxt->setCheckState(Qt::CheckState::Unchecked);

		ui.dxt->setCheckState(Qt::CheckState::Unchecked);
		ui.ywxhq->setCheckState(Qt::CheckState::Unchecked);
		ui.xsjxxt->setCheckState(Qt::CheckState::Unchecked);
		ui.zmxt->setCheckState(Qt::CheckState::Unchecked);
		ui.dqxt->setCheckState(Qt::CheckState::Unchecked);
		ui.yxxt->setCheckState(Qt::CheckState::Unchecked);
	}
}
