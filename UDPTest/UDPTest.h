#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_UDPTest.h"
#include <QUdpSocket>
#include <QTimer>
#include "ShareLib.h"
class UDPTest : public QMainWindow
{
    Q_OBJECT

public:
    UDPTest(QWidget *parent = Q_NULLPTR);

private:
    Ui::UDPTestClass ui;
	QUdpSocket* m_udp;
	QTimer* m_timer;
public slots:
	void udpRead();
	void on_timeout();
};
