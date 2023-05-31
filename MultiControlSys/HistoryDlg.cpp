#include "HistoryDlg.h"
#include "Packet.h"
#include <QDesktopWidget>
#include <QDebug>
#include <QSqlQuery>
#include <QListWidgetItem>
#include <QFile>
#include <QPrinter>
#include <QFileInfo>
#include "LogMgr.h"
#include "GlobalManager.h"
HistoryDlg::HistoryDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);// (Qt::CustomizeWindowHint);
	setFixedSize(WIDTH, HEIGHT);
	QDesktopWidget* desktop = QApplication::desktop(); // =qApp->desktop();也可以
	move(0, 0);
	//move((desktop->width() - this->width()) / 2, (desktop->height() - this->height()) / 2); 
	on_timeout();
	m_tmTimer = new QTimer();
	connect(m_tmTimer, SIGNAL(timeout()), this, SLOT(on_timeout()));
	m_tmTimer->start(1000);
}

HistoryDlg::~HistoryDlg()
{
}

void HistoryDlg::QueryAll()
{
	ui.listWidget->clear();
	QString sql = QString("select * from history_file where del = 0");
	QSqlQuery query(sql);
	int count = 0;
	while (query.next())
	{
		QListWidgetItem* item = new QListWidgetItem(query.value("fileName").toString());
		//item->setData(Qt::DisplayRole, "text");
		item->setData(Qt::CheckStateRole, Qt::Unchecked);
		ui.listWidget->addItem(item);
		count++;
	}
	QString str = QString::fromLocal8Bit("共找到%1个符合条件的数据结果文件").arg(count);
	ui.label_12->setText(str);
}

void HistoryDlg::on_timeout()
{
	LogMgr* pLog = LogMgr::GetInstance();
	ui.lable_date->setText(pLog->GetCurrentDate());
	ui.lable_time->setText(pLog->GetCurrentTimeHMS());
}

void HistoryDlg::on_query_clicked()
{
	QueryAll();
}

void HistoryDlg::on_quit_clicked()
{
	close();
}

void HistoryDlg::on_checkBox_clicked()
{
	qDebug() << ui.checkBox->checkState();
	//if (ui.checkBox->checkState() == Qt::Checked)
	{
		for (int i = 0; i < ui.listWidget->count(); i++)
		{
			ui.listWidget->item(i)->setCheckState(ui.checkBox->checkState());
		}
	}
}

void HistoryDlg::on_btn_del_clicked()
{
	QStringList lst;
	for (int i = 0; i < ui.listWidget->count(); i++)
	{
		QListWidgetItem* item = ui.listWidget->item(i);
		if (item->checkState() == Qt::Checked)
		{
			lst << item->text();
			QString strPath = QString::fromLocal8Bit("./history/%1").arg(item->text());
			QFile::remove(strPath);
		}
	}
}

void HistoryDlg::on_printf_clicked()
{
	// create a printer
	QPrinter printer;
	QString printerName = printer.printerName();
	// no default printer or no file return false
	QString filePath;
	for (int i = 0; i < ui.listWidget->count(); i++)
	{
		QListWidgetItem* item = ui.listWidget->item(i);
		if (item->checkState() == Qt::Checked)
		{
			filePath = QString::fromLocal8Bit("./history/%1").arg(item->text());
			break;
		}
	}
	if (printerName.size() == 0 || filePath.size() == 0)
		return ;
	QFileInfo fi(filePath);
	if (!fi.exists())
		return ;
	int ret = 0;
	ret = (int)ShellExecuteW(NULL,
		QString("print").toStdWString().c_str(),
		filePath.toStdWString().c_str(),
		NULL,
		NULL,
		SW_HIDE);
	// if return number bigger than 31 indicate succ
	if (ret > SE_ERR_NOASSOC)
		return ;
	return ;
}

void HistoryDlg::on_btn_close_clicked()
{
	GlobalManager::getInstance()->ShowButtonTip(this);
}

void HistoryDlg::on_btn_open_clicked()
{
	GlobalManager::getInstance()->ShowButtonTip(this);
}

void HistoryDlg::on_btn_compare_clicked()
{
	GlobalManager::getInstance()->ShowButtonTip(this);
}

void HistoryDlg::on_btn_other_clicked()
{
	GlobalManager::getInstance()->ShowButtonTip(this);

}

void HistoryDlg::on_btn_pailie_clicked()
{
	GlobalManager::getInstance()->ShowButtonTip(this);

}

void HistoryDlg::on_btn_export_clicked()
{
	GlobalManager::getInstance()->ShowButtonTip(this);
}

void HistoryDlg::on_btn_printf_clicked()
{
	GlobalManager::getInstance()->ShowButtonTip(this);
}
