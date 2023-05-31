#ifndef EXCELOPERATOR_H
#define EXCELOPERATOR_H

#include <QObject>
#include <ActiveQt/QAxObject>
#include <QDebug>
#include <QDir>

class ExcelOperator : public QObject
{
	Q_OBJECT
public:
	explicit ExcelOperator(QObject *parent = nullptr);
	~ExcelOperator();
	//���ļ�
	bool open(QString path);
	//�ر��ļ�
	bool close();
	//����ļ�
	bool SaveAs(QString path);
	//��ȡ����������
	int getSheetsCount();
	//�������ƴ���������
	QAxObject* addSheet(QString name);
	//��������ɾ��������
	bool delSheet(QString name);
	//���ݱ��ɾ��������
	bool delSheet(int index);
	//�������ƻ�ȡ������
	QAxObject* getSheet(QString name);
	//���ݱ�Ż�ȡ������
	QAxObject* getSheet(int index);
	//��ȡ�ж���
	QAxObject* getRows(QAxObject* pSheet);
	//��ȡ����
	int getRowsCount(QAxObject* pSheet);
	//��ȡ�ж���
	QAxObject* getColumns(QAxObject* pSheet);
	//��ȡ����
	int getColumnsCount(QAxObject* pSheet);
	//��������ֵ��ȡ��Ԫ��ֵ, ��: 3�У�5��
	QString getCell(QAxObject* pSheet, int row, int column);
	//�������б�Ż�ȡ��Ԫ��ֵ, ��: "F6"
	QString getCell(QAxObject* pSheet, QString number);
	//��������ֵ���õ�Ԫ��ֵ
	bool setCell(QAxObject* pSheet, int row, int column, QString value);
	//�������б�����õ�Ԫ��ֵ
	bool setCell(QAxObject* pSheet, QString number, QString value);


signals:

public slots:
private:
	QAxObject*      m_pExcel;
	QAxObject*      m_pWorksheets;
	QAxObject*      m_pWorkbook;
	QString         m_strPath;
};

#endif // EXCELOPERATOR_H

