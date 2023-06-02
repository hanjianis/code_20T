#include "TestDlg.h"

#include "VRSimulation.h"
TestDlg::TestDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);


//	ui.tabWidget->addTab(unit, QString::fromLocal8Bit("ÑµÁ·µ¥Ôª"));
	VRSimulation* vr = new VRSimulation();
//	ui.tabWidget->addTab(vr, QString::fromLocal8Bit("VR"));

	ui.horizontalLayout_2->addWidget(vr);



}

TestDlg::~TestDlg()
{
}
