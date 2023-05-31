#include "testSnap7.h"
#pragma  comment(lib,"snap7.lib")
testSnap7::testSnap7(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ptrPLC = new TS7Client();
}
