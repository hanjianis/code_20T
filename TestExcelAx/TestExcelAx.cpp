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
	//QAxObject* workbooks = excel.querySubObject("WorkBooks"); // ��ȡ����������
	////2.1�½�
	//workbooks->dynamicCall("Add"); // �½�һ��������
	//QAxObject* workbook = excel.querySubObject("ActiveWorkBook"); // ��ȡ��ǰ������
	//workbook = workbooks->querySubObject("Open(const QString&)", ("D:/syscheck.xlsx"));

	//QAxObject* worksheet = workbook->querySubObject("WorkSheets(int)", 1); // ��ȡ�������ϵĹ�����1�� ��sheet1
	//QAxObject* usedrange = worksheet->querySubObject("UsedRange"); // sheet��Χ
	//int intRowStart = usedrange->property("Row").toInt(); // ��ʼ����   Ϊ1
	//int intColStart = usedrange->property("Column").toInt();  // ��ʼ���� Ϊ1

	//workbook->dynamicCall("SaveAs(const QString&)", "D:/11.xlsx");
	//workbook->dynamicCall("Close(Boolean)", false);
	//excel.dynamicCall("Quit");
}
