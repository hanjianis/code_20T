#pragma once

#include <QObject>
#include "Packet.h"
//关于excel的操作
//检测报告的产生 根据不同的测试 选择不同的模板 测试过程中插入每条测试
//模板位于ini下 CreateExcel时有区分选择不同模板
class ExcelOperate : public QObject
{
	Q_OBJECT

public:
	ExcelOperate(QObject *parent);
	~ExcelOperate();
	void CreateExcel(int type,int unit);//按照模板 生成新的 
	void InsertSheet(int row,AutoTestData atd);//插入一行数据到表格
	void SaveAs(int usetm=0);//保存
	void SetCellStr(Sheet* sheet, int row, int col, QString str);//设置单元格内容
	AutoTestFileInfo _FileInfo;//文件信息
private:
	int _xlsxindex;//excel的行号
	Sheet* sheet;
	Format* format;
	Sheet* _sheetModule;//工作表的模板
	Book* book;
	
	//QString _testTm;//测试时间 时分秒-时分秒

	void ClearSheet(Sheet* sheet1);//清空表格
	void InsertDB(QString filename);//插入文件相关信息到数据库
};
