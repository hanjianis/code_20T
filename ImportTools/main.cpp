#include "ImportTools.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ImportTools w;
    w.show();
    return a.exec();
}
