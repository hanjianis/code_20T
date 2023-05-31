#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TestExcelAx.h"

class TestExcelAx : public QMainWindow
{
    Q_OBJECT

public:
    TestExcelAx(QWidget *parent = Q_NULLPTR);

private:
    Ui::TestExcelAxClass ui;
};
