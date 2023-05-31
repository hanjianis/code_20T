#include "ImportTools.h"
#include <QFileDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include "QSwitchButton.h"
ImportTools::ImportTools(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	ConnectSQLServer();
	SwitchButton* btn = new SwitchButton(this);
	btn->setParent(this);
}

void ImportTools::Supplement(MsgNetData& dd)
{
	dd.softid = dd.id / 100;
	if (dd.id / 100 == 2)
	{
		dd.soft = QString::fromLocal8Bit("火工品测试仪");
	}
	if (dd.id / 100 == 1)
	{
		dd.soft = QString::fromLocal8Bit("综合测控软件");
	}
	if (dd.id / 100 == 3)
	{
		dd.soft = QString::fromLocal8Bit("引信测试软件");
	}
	if (dd.id / 100 == 4)
	{
		dd.soft = QString::fromLocal8Bit("惯导测试ksdmon");
	}
	if (dd.id / 100 == 5)
	{
		dd.soft = QString::fromLocal8Bit("惯导测试eksybd软件");
	}
	if (dd.id / 100 == 6)
	{
		dd.soft = QString::fromLocal8Bit("惯导测试eksyx2软件");
	}
	if (dd.id / 100 == 7)
	{
		dd.soft = QString::fromLocal8Bit("惯导测试eksyep软件");
	}
	if (dd.id / 100 == 8)
	{
		dd.soft = QString::fromLocal8Bit("惯导测试EKCHL数据处理");
	}
	if (dd.id / 100 == 9)
	{
		dd.soft = QString::fromLocal8Bit("惯导测试eksy2软件");
	}
	if (dd.id / 100 == 10)
	{
		dd.soft = QString::fromLocal8Bit("惯导测试ekzdj2软件");
	}
}

void ImportTools::on_pushButton_clicked()
{
	QString file_name = QFileDialog::getOpenFileName(this,
		tr("Open File"),
		"",
		"",
		0);
	if (!file_name.isNull())
	{
		//fileName是文件名
		InitMsg(file_name);
	}
	else {
		//点的是取消
		//...
	}
}
void ImportTools::ConnectSQLServer()
{
	//连接sqlserver数据库

	QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
	db.setDatabaseName(QString("DRIVER={SQL SERVER};"
		"SERVER=%1;" //服务器名称
		"DATABASE=%2;"//数据库名
		"UID=%3;"           //登录名
		"PWD=%4;"        //密码
	)
		.arg("127.0.0.1")
		.arg("20T")
		.arg("20T_ctl")
		.arg("20T_ctl")
	);
	if (!db.open())
	{
		qDebug() << "connect sql server failed!";

	}
	else
	{
		qDebug() << "connect sql server successfully!";
	}
	//test
	QSqlQuery query;
	query.exec("select * from test_table");
	while (query.next())	//循环输出
	{
		qDebug() << "===========";
		qDebug() << query.value(0).toInt() << query.value(1).toString();
	}
}
void ImportTools::InitMsg(QString strFile)
{
	//获取路径
	QString str;
	QByteArray line;
	QStringList lst;
	QFile file(strFile);
	if (file.open(QIODevice::ReadOnly))
	{
		while (!file.atEnd())
		{
			line = file.readLine();
			if (!line.isEmpty())
			{
				str = line;
				lst = str.split("//");
				if (lst.size() >= 2)
				{
					//0
					QStringList idlst = lst.at(0).split("=");
					if (idlst.size() >= 2)
					{
						MsgNetData dd;
						QString str1 = idlst[1];
						//去掉最后一个分号
						str1 = str1.mid(0, str1.length() - 1);
						dd.id = str1.toInt();
						Supplement(dd);
						dd.note = lst[1].trimmed();
						//插入数据库
						QString sql = QString("INSERT INTO [dbo].[client_acs] ([ac_id], [ac_name], [ac_soft], [ac_esoft], [ac_note], [ac_softid]) VALUES (%1, '%2', '%3', '%4', '%5',%6);")
							.arg(dd.id)
							.arg(dd.note)
							.arg(dd.soft)
							.arg(dd.soft)
							.arg(dd.note)
							.arg(dd.softid);
						QSqlQuery query;
						query.exec(sql);
					}
				}
			}
		}
	}
}