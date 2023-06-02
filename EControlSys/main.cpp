#include "EControlSys.h"
#include <QtWidgets/QApplication>
#include <QFile>
int main(int argc, char *argv[])
{
	

    QApplication a(argc, argv);
	//加载qss文件
	QFile qssFile(":/qss/lightblue.css");
	qssFile.open(QFile::ReadOnly); //以只读方式打开
	if (qssFile.isOpen())
	{
		QString qss = QLatin1String(qssFile.readAll());
		QString paletteColor = qss.mid(20, 7);
		qApp->setPalette(QPalette(QColor(paletteColor)));
		qApp->setStyleSheet(qss);
		qssFile.close();
	}
	a.setWindowIcon(QIcon(":/EControlSys/res/main.ico"));

	QFont f(QString::fromLocal8Bit("微软雅黑"), 13);
	a.setFont(f);
    EControlSys w;
    w.show();
    return a.exec();
}
