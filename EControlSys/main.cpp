#include "EControlSys.h"
#include <QtWidgets/QApplication>
#include <QFile>
int main(int argc, char *argv[])
{
	

    QApplication a(argc, argv);
	//����qss�ļ�
	QFile qssFile(":/qss/lightblue.css");
	qssFile.open(QFile::ReadOnly); //��ֻ����ʽ��
	if (qssFile.isOpen())
	{
		QString qss = QLatin1String(qssFile.readAll());
		QString paletteColor = qss.mid(20, 7);
		qApp->setPalette(QPalette(QColor(paletteColor)));
		qApp->setStyleSheet(qss);
		qssFile.close();
	}
	a.setWindowIcon(QIcon(":/EControlSys/res/main.ico"));

	QFont f(QString::fromLocal8Bit("΢���ź�"), 13);
	a.setFont(f);
    EControlSys w;
    w.show();
    return a.exec();
}
