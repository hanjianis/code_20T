#include "SelectUserDlg.h"
#include <QSqlQuery>
#include "GlobalManager.h"
SelectUserDlg::SelectUserDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.tableWidget->setAlternatingRowColors(true);
	ui.tableWidget->verticalHeader()->setVisible(false);
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	QString sql = QString("SELECT u.id,u.login_name, u.real_name, c.id class_id,  c.name class_name  FROM  user_info u LEFT JOIN  student_class  c ON c.id = u.class_id WHERE u.user_type = 0 ;");
	InitTable(sql);
	InitCombox();
	connect(this, SIGNAL(AddUserList(QString)), parent, SLOT(AddUserListSlot(QString)));

}

SelectUserDlg::~SelectUserDlg()
{
}
void SelectUserDlg::InitTable(QString sql)
{

	QBrush bruship = QBrush(QColor(90, 90, 255));
	QBrush brushop(QColor(83, 158, 216));
//	QString sql = QString("SELECT u.id,u.login_name, u.real_name, c.id class_id,  c.name class_name  FROM  user_info u LEFT JOIN  student_class  c ON c.id = u.class_id WHERE u.user_type = 0 ;");
	QSqlQuery query(sql);
	int row = 0;
	while (query.next())
	{
		int column = 0;
		ui.tableWidget->setRowCount(row + 1);

		QTableWidgetItem* item = new QTableWidgetItem(query.value("login_name").toString());
		item->setCheckState(Qt::Unchecked);
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget->setItem(row, column++, item);

		item = new QTableWidgetItem(query.value("real_name").toString());
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget->setItem(row, column++, item);

		item = new QTableWidgetItem(query.value("class_name").toString());
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget->setItem(row, column++, item);

		row++;

	}

}

void SelectUserDlg::on_all_clicked()
{
	for (int i = 0; i < ui.tableWidget->rowCount(); i++)
	{
		ui.tableWidget->item(i, 0)->setCheckState(Qt::Checked);
	}
}

void SelectUserDlg::on_ok_clicked()
{
	QString str;
	//获取一串学号 
	for (int i = 0; i < ui.tableWidget->rowCount(); i++)
	{
		QTableWidgetItem* item = ui.tableWidget->item(i, 0);
		if(item->checkState()==Qt::Checked)
		{
			str.append(item->text());
			str.append(";");
		}
	}
	emit AddUserList(str);
	QDialog::accept();
	close();
}

void SelectUserDlg::on_cancel_clicked()
{
	QDialog::reject();
	close();
}

void SelectUserDlg::on_comboBox_currentTextChanged(const QString & str)
{
	QMap<QString, StudentClass>::iterator it = GlobalManager::getInstance()->m_mapStudentClass.find(str);
	if (it != GlobalManager::getInstance()->m_mapStudentClass.end())
	{
		ui.tableWidget->setRowCount(0);
		QString sql = QString("SELECT u.id,u.login_name, u.real_name, c.id class_id,  c.name class_name  FROM  user_info u LEFT JOIN  student_class  c ON c.id = u.class_id WHERE u.user_type = 0 and u.class_id=%1;").arg(it->id);
		InitTable(sql);
	
	}
}

void SelectUserDlg::InitCombox()
{
	ui.comboBox->addItem(QString::fromLocal8Bit("全部"));
	QMap<QString, StudentClass>::iterator it = GlobalManager::getInstance()->m_mapStudentClass.begin();
	while (it != GlobalManager::getInstance()->m_mapStudentClass.end())
	{
		ui.comboBox->addItem(it->name);
		it++;
	}
}
