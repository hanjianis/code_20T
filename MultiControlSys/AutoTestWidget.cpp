#include "AutoTestWidget.h"
#include "XLManager.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
AutoTestWidget::AutoTestWidget(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    //UpdateInsLables(1, 40);
    InitWidget();//撑起空间
    //UpdateInsLables(121, 141);
}

AutoTestWidget::~AutoTestWidget()
{
}

void AutoTestWidget::InitWidget()
{
    //XLManager* pXL = XLManager::GetInstance();

    //4大列 10行    
    for (int j = 0; j < 1; j++)
    {
        QVBoxLayout* hb = new QVBoxLayout();
        ui.horizontalLayout->addLayout(hb);
        QVBoxLayout* hb2 = new QVBoxLayout();
        ui.horizontalLayout->addLayout(hb2);
        for (int i = 0; i < 10; i++)
        {

            QLabel* lb = new QLabel("");
            hb->addWidget(lb);


        }
    }    
}

void AutoTestWidget::ClearLayout(QBoxLayout* Layout)
{
    QLayoutItem* childItem;
    while ((childItem = Layout->takeAt(0)) != nullptr)
    {
        if (childItem->layout())//如果是layout
        {
            ClearLayout((QBoxLayout*)childItem);
        }
        if (childItem->widget())
        {
            childItem->widget()->setParent(nullptr);
        }
    }
}
//自动测试最下边的表格
void AutoTestWidget::UpdateInsLables(int begin, int end)
{
    ClearLayout(ui.horizontalLayout);

    XLManager* pXL = XLManager::GetInstance();

    //4大列 10行
    for (int j = 0; j < 4; j++)
    {
        QVBoxLayout* hb = new QVBoxLayout();
        ui.horizontalLayout->addLayout(hb);
        QVBoxLayout* hb2 = new QVBoxLayout();
        ui.horizontalLayout->addLayout(hb2);
        for (int i = 0; i < 10; i++)
        {
            if ((j * 10 + i + begin) > pXL->m_mapAutoTestList.count())
            {//撑起这一列
                //计算还差几个
                for (int t = 0; t < 10 - i; t++)
                {
                    QLabel* lb3 = new QLabel("");
                    hb->addWidget(lb3);
                    QLabel* lb4 = new QLabel("");
                    hb2->addWidget(lb4);
                }
                return;
            }
            QLabel* lb = new QLabel(pXL->m_mapAutoTestList[j * 10 + i + begin].note);
            hb->addWidget(lb);

            QLabel* lb2 = new QLabel(pXL->m_mapAutoTestList[j * 10 + i + begin].autoVal);
            hb2->addWidget(lb2);
            pXL->m_mapAutoTestList[j * 10 + i + begin].val = lb2;
        }
    }
}
