#include "TestExcelAx.h"
#include <QAxObject>
#include "ExcelOperator.h"
TestExcelAx::TestExcelAx(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	ExcelOperator* excel = new ExcelOperator(this);
	excel->open("D:/syscheck.xlsx");
	excel->SaveAs("D:/22.xlsx");
	//QAxObject excel("Excel.Application");
	//excel.setProperty("Visible", false);
	//excel.setProperty("DisplayAlerts", false);
	//QAxObject* workbooks = excel.querySubObject("WorkBooks"); // 获取工作簿集合
	////2.1新建
	//workbooks->dynamicCall("Add"); // 新建一个工作簿
	//QAxObject* workbook = excel.querySubObject("ActiveWorkBook"); // 获取当前工作簿
	//workbook = workbooks->querySubObject("Open(const QString&)", ("D:/syscheck.xlsx"));

	//QAxObject* worksheet = workbook->querySubObject("WorkSheets(int)", 1); // 获取工作表集合的工作表1， 即sheet1
	//QAxObject* usedrange = worksheet->querySubObject("UsedRange"); // sheet范围
	//int intRowStart = usedrange->property("Row").toInt(); // 起始行数   为1
	//int intColStart = usedrange->property("Column").toInt();  // 起始列数 为1

	//workbook->dynamicCall("SaveAs(const QString&)", "D:/11.xlsx");
	//workbook->dynamicCall("Close(Boolean)", false);
	//excel.dynamicCall("Quit");
}
