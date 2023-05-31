#pragma once

#include <QWidget>
#include "ui_AutoTestWidget.h"

class AutoTestWidget : public QWidget
{
    Q_OBJECT

public:
    AutoTestWidget(QWidget *parent = Q_NULLPTR);
    ~AutoTestWidget();

private:
    Ui::AutoTestWidget ui;
    void InitWidget();
    void ClearLayout(QBoxLayout* Layout);
public:
    void UpdateInsLables(int begin,int end);
};
