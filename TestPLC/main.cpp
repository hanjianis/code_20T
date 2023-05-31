#include "TestPLC.h"
#include <QtWidgets/QApplication>
#include "motioncontroll.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	MotionControll mon;
	mon.show();
    //TestPLC w;
    //w.show();
    return a.exec();
}
