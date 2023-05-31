#pragma once

#include <QObject>
#include "Packet.h"
//����excel�Ĳ���
//��ⱨ��Ĳ��� ���ݲ�ͬ�Ĳ��� ѡ��ͬ��ģ�� ���Թ����в���ÿ������
//ģ��λ��ini�� CreateExcelʱ������ѡ��ͬģ��
class ExcelOperate : public QObject
{
	Q_OBJECT

public:
	ExcelOperate(QObject *parent);
	~ExcelOperate();
	void CreateExcel(int type,int unit);//����ģ�� �����µ� 
	void InsertSheet(int row,AutoTestData atd);//����һ�����ݵ����
	void SaveAs(int usetm=0);//����
	void SetCellStr(Sheet* sheet, int row, int col, QString str);//���õ�Ԫ������
	AutoTestFileInfo _FileInfo;//�ļ���Ϣ
private:
	int _xlsxindex;//excel���к�
	Sheet* sheet;
	Format* format;
	Sheet* _sheetModule;//�������ģ��
	Book* book;
	
	//QString _testTm;//����ʱ�� ʱ����-ʱ����

	void ClearSheet(Sheet* sheet1);//��ձ��
	void InsertDB(QString filename);//�����ļ������Ϣ�����ݿ�
};
