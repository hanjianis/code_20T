#include "AutoTestWidget.h"
#include "XLManager.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
AutoTestWidget::AutoTestWidget(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    //UpdateInsLables(1, 40);
    InitWidget();//����ռ�
    //UpdateInsLables(121, 141);
}

AutoTestWidget::~AutoTestWidget()
{
}

void AutoTestWidget::InitWidget()
{
    //XLManager* pXL = XLManager::GetInstance();

    //4���� 10��    
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
        if (childItem->layout())//�����layout
        {
            ClearLayout((QBoxLayout*)childItem);
        }
        if (childItem->widget())
        {
            childItem->widget()->setParent(nullptr);
        }
    }
}
//�Զ��������±ߵı��
void AutoTestWidget::UpdateInsLables(int begin, int end)
{
    ClearLayout(ui.horizontalLayout);

    XLManager* pXL = XLManager::GetInstance();

    //4���� 10��
    for (int j = 0; j < 4; j++)
    {
        QVBoxLayout* hb = new QVBoxLayout();
        ui.horizontalLayout->addLayout(hb);
        QVBoxLayout* hb2 = new QVBoxLayout();
        ui.horizontalLayout->addLayout(hb2);
        for (int i = 0; i < 10; i++)
        {
            if ((j * 10 + i + begin) > pXL->m_mapAutoTestList.count())
            {//������һ��
                //���㻹���
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
