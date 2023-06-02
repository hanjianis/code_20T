#include "EditSubject.h"
#include "GlobalManager.h"
#include <QSqlQuery>
EditSubject::EditSubject(QString subjectid, QWidget *parent)
	: QDialog(parent)
{

	ui.setupUi(this);
	m_subjectid = subjectid;
	QMap<QString, SubjectInfo>::iterator it = GlobalManager::getInstance()->m_mapSubjects.find(subjectid);
	if (it != GlobalManager::getInstance()->m_mapSubjects.end())
	{
		ui.lineEdit->setText(it->subject_name);
		ui.lineEdit_2->setText(it->remark);
	}
}

EditSubject::~EditSubject()
{
}

void EditSubject::on_ok_clicked()
{
	QMap<QString, SubjectInfo>::iterator it = GlobalManager::getInstance()->m_mapSubjects.find(m_subjectid);
	if (it != GlobalManager::getInstance()->m_mapSubjects.end())
	{
		it->remark = ui.lineEdit_2->text();
		//�������ݿ�
		QString sql = QString("update subject set remark='%1' where id=%2;")
			.arg(it->remark).arg(it->id);
		QSqlQuery query;
		if (query.exec(sql))
		{
			GlobalManager::getInstance()->ShowMessageBox(QString::fromLocal8Bit("�޸ĳɹ�������"));

		}
		else
		{
			GlobalManager::getInstance()->ShowMessageBox(QString::fromLocal8Bit("�޸�ʧ�ܣ�����"));
		}
	}
	else
	{
		GlobalManager::getInstance()->ShowMessageBox(QString::fromLocal8Bit("��Ŀ�����ڣ�����"));
		return;
	}
	QDialog::accept();
	close();
}

void EditSubject::on_cancel_clicked()
{
	QDialog::reject();
	close();
}
