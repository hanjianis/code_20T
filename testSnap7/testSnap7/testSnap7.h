#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_testSnap7.h"
#include "snap7.h"
class testSnap7 : public QMainWindow
{
	Q_OBJECT

public:
	testSnap7(QWidget *parent = Q_NULLPTR);

private:
	Ui::testSnap7Class ui;
	TS7Client *ptrPLC;
};
