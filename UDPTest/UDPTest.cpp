#include "UDPTest.h"
#include <QDebug>
UDPTest::UDPTest(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	m_udp = new QUdpSocket();
	bool aa= m_udp->bind(QHostAddress("192.168.2.53"), 9090);
	//connect(m_udp, SIGNAL(readyRead()), this, SLOT(udpRead()));
	
	m_timer = new QTimer();
	connect(m_timer,SIGNAL(timeout()),this,SLOT(on_timeout()));
	m_timer->start(1000);
	int len = sizeof(int);
	qDebug() << "1111111";

}

void UDPTest::udpRead()
{
	QByteArray arr;
	while (m_udp->hasPendingDatagrams())
	{
		qDebug() << "==================";
		//arr.resize(m_udp->readBufferSize());
		//arr = m_udp->readAll();
		
	}
}

void UDPTest::on_timeout()
{
	//·¢ËÍÐÄÌø
	char dt[8+14*2] = { 0 };
	int cmd = 0x1100;
	memcpy(dt + 4, &cmd, 4);
	short d = 23;
	
	memcpy(dt + 10, &d, 2);
	int len = m_udp->writeDatagram(dt, 8 + 14 * 2,QHostAddress("192.168.2.53"),8089);
	qDebug() << len;
}
