#include "EditTaskDlg.h"
#include "SelectUserDlg.h"
#include <QSqlQuery>
EditTaskDlg::EditTaskDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	QMap<QString,SubjectInfo>::iterator it = GlobalManager::getInstance()->m_mapSubjects.begin();
	while (it != GlobalManager::getInstance()->m_mapSubjects.end())
	{
		ui.comboBox->addItem(it->subject_name);
		it++;
	}
}

EditTaskDlg::~EditTaskDlg()
{
}

void EditTaskDlg::on_ok_clicked()
{
	//更新数据库
	QString task_id = ui.lineEdit->text();
	QString task_name = ui.lineEdit_2->text();
	int mode = ui.radioButton->isChecked() ? 1 : 2;
	QString user_login_name = ui.lineEdit_4->text();
	QStringList userlst = user_login_name.split(";");
	if (userlst.size() > 2)
	{
		GlobalManager::getInstance()->ShowMessageBox(QString::fromLocal8Bit("只可以有一名学员！！"));
		return;
	}
	user_login_name = userlst[0];

	QString subject = ui.comboBox->currentText();
	QString sql = QString("update tasks_list set name='%1',mode=%2,user_login_name='%3',subject='%4' where task_id='%5';")
		.arg(task_name).arg(mode).arg(user_login_name).arg(subject).arg(task_id);
	QSqlQuery query;
	if (query.exec(sql))
	{
		GlobalManager::getInstance()->ShowMessageBox(QString::fromLocal8Bit("修改成功！！！"));
		m_curTask.task_name = task_name;
		m_curTask.mode = mode;
		m_curTask.subject = subject;
		m_curTask.user_login_name = user_login_name;
	}
	else
	{
		GlobalManager::getInstance()->ShowMessageBox(QString::fromLocal8Bit("修改失败！！！"));
	}
	
	QDialog::accept();
	close();
}

void EditTaskDlg::on_cancel_clicked()
{
	QDialog::reject();
	close();
}

void EditTaskDlg::on_select_btn_clicked()
{
	SelectUserDlg ldg(this);
	ldg.exec();
}

void EditTaskDlg::AddUserListSlot(QString str)
{
	ui.lineEdit_4->setText(str);
}

void EditTaskDlg::SetCurTask(TaskInfo& curTask)
{
	m_curTask = curTask;
	ui.lineEdit->setText(curTask.task_id);
	ui.lineEdit_2->setText(curTask.task_name);
	ui.lineEdit_4->setText(curTask.user_login_name);
	if (curTask.mode == 1)
	{
		ui.radioButton->setChecked(true);
	}
	else if (curTask.mode == 2)
	{
		ui.radioButton_2->setChecked(true);
	}
	ui.comboBox->setCurrentText(curTask.subject);
}
