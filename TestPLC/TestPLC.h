#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TestPLC.h"

class TestPLC : public QMainWindow
{
    Q_OBJECT

public:
    TestPLC(QWidget *parent = Q_NULLPTR);

private:
    Ui::TestPLCClass ui;
};
