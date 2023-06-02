#include "PlanThinkDlg.h"
#include "SelectUserDlg.h"
#include <QSqlQuery>
#include "LogMgr.h"
#include "GlobalManager.h"
PlanThinkDlg::PlanThinkDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	initSubjects();
	QString plan_id = QString("PLAN_%1").arg(GlobalManager::getInstance()->_plan_id, 3, 10, QLatin1Char('0'));
	ui.lineEdit_2->setText(plan_id);
	ui.dateTimeEdit->setDateTime(QDateTime::currentDateTime());
}

PlanThinkDlg::~PlanThinkDlg()
{
}

void PlanThinkDlg::AddThinkPlan()
{
	QString plan_id = ui.lineEdit_2->text();// QString("PLAN_%1").arg(GlobalManager::getInstance()->_plan_id, 3, 10, QLatin1Char('0'));
	int mode = ui.radioButton->isChecked() == true ? 1 : 2;//1ѵ��ģʽ 2����ģʽ

	QSqlQuery query;
	query.prepare("exec [dbo].[AddThinkPlan] ?, ?, ?, ?, ?, ?, ?, ?,? output");
	query.bindValue(0, plan_id);
	query.bindValue(1, ui.lineEdit->text());//����
	query.bindValue(2, mode);
	query.bindValue(3, ui.comboBox->currentText());//��Ŀ
	query.bindValue(4, ui.lineEdit_4->text());//ѧԱ
	query.bindValue(5, ui.dateTimeEdit->text());//ʱ��
	query.bindValue(6, ui.lineEdit_3->text());
	query.bindValue(7, QString::fromLocal8Bit(""));
	query.bindValue(8, 0, QSql::Out);
	bool bFlag = query.exec();
	if (bFlag)
	{
		int planid = query.boundValue(8).toInt();
		if (planid < 0)
			bFlag = false;
		else
		{
			GlobalManager::getInstance()->_plan_id = planid + 1;
		}
	}

}

void PlanThinkDlg::AddTask()
{
	QString plan_id = ui.lineEdit_2->text();// QString("PLAN_%1").arg(GlobalManager::getInstance()->_plan_id, 3, 10, QLatin1Char('0'));
	int mode = ui.radioButton->isChecked() == true ? 1 : 2;//1ѵ��ģʽ 2����ģʽ
	QString str = ui.lineEdit_4->text();
	QStringList userLst = str.split(";");
	if (userLst.size() == 0)
	{
	
	}
	int paramindex = 0;
	for (int i = 0; i < userLst.count(); i++)
	{
		
		if (userLst[i].isEmpty())
			return;

		TaskInfo tsinfo;
		tsinfo.id = GlobalManager::getInstance()->_task_id ;
		tsinfo.plan_id = plan_id;
		tsinfo.task_name = ui.lineEdit->text();
		tsinfo.subject = ui.comboBox->currentText();
		tsinfo.user_login_name = userLst[i];
		tsinfo.startTm1 = ui.dateTimeEdit->text();
		tsinfo.note = QString::fromLocal8Bit("");
		tsinfo.type = 1;
		tsinfo.mode = mode;
		GlobalManager::getInstance()->AddTaskToDB(tsinfo);
	}
	
}

void PlanThinkDlg::on_select_btn_clicked()
{
	SelectUserDlg ldg(this);
	ldg.exec();
}

void PlanThinkDlg::on_ok_clicked()
{
	if (ui.lineEdit->text().isEmpty())//���ɿ�
	{
		GlobalManager::getInstance()->ShowMessageBox(QString::fromLocal8Bit("�������Ʋ���Ϊ�գ���"));
		return;
	}
	QString str = ui.lineEdit_4->text();
	QStringList userLst = str.split(";");
	if (userLst.size() == 0)
	{
		GlobalManager::getInstance()->ShowMessageBox(QString::fromLocal8Bit("��ѡ��ѧԱ����"));
		return;
	}
	//���һ���붨
	AddThinkPlan();
	//�������
	AddTask();
	QDialog::accept();
	close();
}

void PlanThinkDlg::on_cancel_clicked()
{
	QDialog::reject();
	close();
}

void PlanThinkDlg::initSubjects()
{
	QString sql = QString("select * from subject;");
	QSqlQuery query(sql);
	QStringList strlst;
	while (query.next())
	{
		strlst << query.value("subject_name").toString();
	}
	ui.comboBox->addItems(strlst);
}

void PlanThinkDlg::AddUserListSlot(QString str)
{
	ui.lineEdit_4->setText(str);
}
