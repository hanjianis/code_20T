#ifndef T
#define T

#include <QWidget>

namespace Ui {
class IntegratedLowerDisplay;
}

class IntegratedLowerDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit IntegratedLowerDisplay(QWidget *parent = nullptr);
    ~IntegratedLowerDisplay();

private:
    Ui::IntegratedLowerDisplay *ui;
};

#endif // T
