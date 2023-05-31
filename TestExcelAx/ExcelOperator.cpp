#include "exceloperator.h"
#include <objbase.h>

ExcelOperator::ExcelOperator(QObject *parent) : QObject(parent)
, m_pExcel(NULL)
, m_pWorksheets(NULL)
, m_pWorkbook(NULL)
{

}

ExcelOperator::~ExcelOperator()
{
	close();
}

bool ExcelOperator::open(QString path)
{
	m_strPath = path;
	QAxObject *pWorkbooks = NULL;
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	m_pExcel = new(std::nothrow) QAxObject();
	if (NULL == m_pExcel) {
		qCritical() << "����Excel����ʧ��...";
		return false;
	}
	try {
		m_pExcel->setControl("Excel.Application");

		m_pExcel->dynamicCall("SetVisible(bool)", false); //true ��ʾ�����ļ�ʱ�ɼ���false��ʾΪ���ɼ�
		m_pExcel->setProperty("DisplayAlerts", false);
		pWorkbooks = m_pExcel->querySubObject("WorkBooks");
		//pWorkbooks->dynamicCall("Add");
		//m_pWorkbook = m_pExcel->querySubObject("ActiveWorkBook");
		qDebug() << "excel path: " << m_strPath;
		//��
		m_pWorkbook = pWorkbooks->querySubObject("Open(const QString&)", m_strPath);
		// ��ȡ�򿪵�excel�ļ������еĹ���sheet
		m_pWorksheets = m_pWorkbook->querySubObject("WorkSheets");
		QStringList slst = m_pWorksheets->verbs();
	}
	catch (...) {
		qCritical() << "���ļ�ʧ��...";
		return false;
	}

	return true;
}

bool ExcelOperator::close()
{
	qDebug() << "excel close...";
	if (m_pExcel)
	{
		qDebug() << "closing...";
		m_pWorkbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(m_strPath));
		m_pWorkbook->dynamicCall("Close()");
		m_pExcel->dynamicCall("Quit()");
		delete m_pExcel;
		m_pExcel = NULL;
	}
	return true;
}

bool ExcelOperator::SaveAs(QString path)
{
	if (m_pExcel)
	{
		qDebug() << "closing...";
		m_pWorkbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(path));
		m_pWorkbook->dynamicCall("Close(Boolean)", false);
		m_pExcel->dynamicCall("Quit()");
		delete m_pExcel;
		m_pExcel = NULL;
	}
	return true;
}

int ExcelOperator::getSheetsCount()
{
	int count = 0;
	count = m_pWorksheets->property("Count").toInt();
	return count;
}


QAxObject* ExcelOperator::addSheet(QString name)
{
	QAxObject *pWorkSheet = NULL;
	try {
		int count = m_pWorksheets->property("Count").toInt();  //��ȡ��������Ŀ
		QAxObject *pLastSheet = m_pWorksheets->querySubObject("Item(int)", count);
		pWorkSheet = m_pWorksheets->querySubObject("Add(QVariant)", pLastSheet->asVariant());
		pLastSheet->dynamicCall("Move(QVariant)", pWorkSheet->asVariant());
		pWorkSheet->setProperty("Name", name);  //���ù���������
	}
	catch (...) {
		qCritical() << "����sheetʧ��...";
	}
	return pWorkSheet;
}

bool ExcelOperator::delSheet(QString name)
{
	try {
		QAxObject *pFirstSheet = m_pWorksheets->querySubObject("Item(QString)", name);
		pFirstSheet->dynamicCall("delete");
	}
	catch (...) {
		qCritical() << "ɾ��sheetʧ��...";
		return false;
	}
	return true;
}

bool ExcelOperator::delSheet(int index)
{
	try {
		QAxObject *pFirstSheet = m_pWorksheets->querySubObject("Item(int)", index);
		pFirstSheet->dynamicCall("delete");
	}
	catch (...) {
		qCritical() << "ɾ��sheetʧ��...";
		return false;
	}
	return true;
}

QAxObject* ExcelOperator::getSheet(QString name)
{
	QAxObject* pWorkSheet = NULL;
	try {
		pWorkSheet = m_pWorksheets->querySubObject("Item(QString)", name);
	}
	catch (...) {
		qCritical() << "��ȡsheetʧ��...";
	}
	return pWorkSheet;
}

QAxObject* ExcelOperator::getSheet(int index)
{
	QAxObject* pWorkSheet = NULL;
	try {
		pWorkSheet = m_pWorksheets->querySubObject("Item(int)", index);
	}
	catch (...) {
		qCritical() << "��ȡsheetʧ��...";
	}
	return pWorkSheet;
}

QAxObject* ExcelOperator::getRows(QAxObject* pSheet)
{
	QAxObject* pRows = NULL;
	try {
		pRows = pSheet->querySubObject("Rows");
	}
	catch (...) {
		qCritical() << "��ȡ��ʧ��...";
	}
	return pRows;
}

int ExcelOperator::getRowsCount(QAxObject* pSheet)
{
	int rows = 0;
	try {
		QAxObject* pRows = getRows(pSheet);
		rows = pRows->property("Count").toInt();
	}
	catch (...) {
		qCritical() << "��ȡ����ʧ��...";
	}
	return rows;
}

QAxObject* ExcelOperator::getColumns(QAxObject* pSheet)
{
	QAxObject* pColumns = NULL;
	try {
		pColumns = pSheet->querySubObject("Columns");
	}
	catch (...) {
		qCritical() << "��ȡ��ʧ��...";
	}
	return pColumns;
}

int ExcelOperator::getColumnsCount(QAxObject* pSheet)
{
	int columns = 0;
	try {
		QAxObject* pColumns = getColumns(pSheet);
		columns = pColumns->property("Count").toInt();
	}
	catch (...) {
		qCritical() << "��ȡ����ʧ��...";
	}
	return columns;
}

QString ExcelOperator::getCell(QAxObject* pSheet, int row, int column)
{
	QString strCell = "";
	try {
		QAxObject* pCell = pSheet->querySubObject("Cells(int, int)", row, column);
		strCell = pCell->property("Value").toString();
	}
	catch (...) {
		qCritical() << "��ȡ��Ԫ����Ϣʧ��...";
	}

	return strCell;
}

QString ExcelOperator::getCell(QAxObject* pSheet, QString number)
{
	QString strCell = "";
	try {
		QAxObject* pCell = pSheet->querySubObject("Range(QString)", number);
		strCell = pCell->property("Value").toString();
	}
	catch (...) {
		qCritical() << "��ȡ��Ԫ����Ϣʧ��...";
	}

	return strCell;
}

bool ExcelOperator::setCell(QAxObject* pSheet, int row, int column, QString value)
{
	try {
		QAxObject* pCell = pSheet->querySubObject("Cells(int, int)", row, column);
		pCell->setProperty("Value", value);
	}
	catch (...) {
		qCritical() << "д�뵥Ԫ����Ϣʧ��...";
		return false;
	}
	return true;
}

bool ExcelOperator::setCell(QAxObject* pSheet, QString number, QString value)
{
	try {
		QAxObject* pCell = pSheet->querySubObject("Range(QString)", number);
		pCell->setProperty("Value", value);
	}
	catch (...) {
		qCritical() << "д�뵥Ԫ����Ϣʧ��...";
		return false;
	}
	return true;
}

