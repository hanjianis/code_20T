#include "ExcelOperate.h"
#include "LogMgr.h"
#include "GlobalManager.h"
#include <QSqlQuery>
#include <QDebug>
//���ĵ����ݶ�������Ҫ���б����ת�������Ϊת��������wchar_t to char
char *w2c(char *pcstr, const wchar_t *pwstr, size_t len)
{
	int nlength = wcslen(pwstr);
	//��ȡת����ĳ���
	int nbytes = WideCharToMultiByte(0, 0, pwstr, nlength, NULL, 0, NULL, NULL);
	if (nbytes > len)   nbytes = len;
	// ͨ�����ϵõ��Ľ����ת��unicode �ַ�Ϊascii �ַ�
	WideCharToMultiByte(0, 0, pwstr, nlength, pcstr, nbytes, NULL, NULL);
	return pcstr;
}
//���ĵ����ݶ�������Ҫ���б����ת�������Ϊת��������wchar_t to char
wchar_t *c2w(const char *pcstr, wchar_t *pwstr, int len)
{
	//int iSize;
	//	wchar_t* pwszUnicode;
		//���ؽ����ַ������軺�����Ĵ�С���Ѿ������ַ���β��'\0'
	//iSize = MultiByteToWideChar(CP_ACP, 0, pcstr, -1, NULL, 0); //iSize =wcslen(pwsUnicode)+1=6
	//pwstr = (wchar_t *)malloc(iSize * sizeof(wchar_t)); //����Ҫ pwszUnicode = (wchar_t *)malloc((iSize+1)*sizeof(wchar_t))
	MultiByteToWideChar(CP_ACP, 0, pcstr, -1, pwstr, len);
	return pwstr;
}
ExcelOperate::ExcelOperate(QObject *parent)
	: QObject(parent)
{
	_xlsxindex = 5;
	book = nullptr;
	_sheetModule = nullptr;
	sheet = nullptr;
}

ExcelOperate::~ExcelOperate()
{
}
void ExcelOperate::CreateExcel(int type, int unit)
{
	wchar_t ws[100];
	if(type == ATT_SYS)
		swprintf(ws, 100, L"./ini/syscheck.xlsx");//ϵͳ�Լ�
	if (type == ATT_AUTO)
	{
		if (unit == INS_TEST)
		{
			swprintf(ws, 100, L"./ini/inscheck.xlsx");//�Զ�����-���ߵ�����
		}
		if (unit == SIGNLE_TEST)
		{
			swprintf(ws, 100, L"./ini/singlecheck.xlsx");//�Զ�����-���������
		}
		if (unit == MULT_TEST)
		{
			swprintf(ws, 100, L"./ini/multcheck.xlsx"); //�Զ����� - ���ۺϲ���
		}
	}
	if (ws[0] == '\0')
	{
		qDebug() << "xlsx error.............";
		return;
	}

	_FileInfo.startDt = LogMgr::GetInstance()->GetCurrentDate();
	_FileInfo.filetm = LogMgr::GetInstance()->GetCurrentTimeString();
	_FileInfo.startTm = LogMgr::GetInstance()->GetCurrentTm();
	_FileInfo.missileName = GlobalManager::getInstance()->_missileName;
	_FileInfo.missileType = GlobalManager::getInstance()->_missileType;

	book = xlCreateXMLBook();//����һ�������Ƹ�ʽ��XLS��Execl97-03����ʵ��,��ʹ��ǰ�����ȵ������������������excel�Ķ���
   //book->setKey(......);//��������˸ÿ⣬��������Ӧ��key����û�й�����������
	if (book)//�Ƿ񴴽�ʵ���ɹ�
	{
		if (book->load(ws))
		{
			int cnt = book->sheetCount();
			//book->setActiveSheet(0);
			//sheet = book->getSheet(1);
			_sheetModule = book->getSheet(1);
			sheet = book->getSheet(0);
			if (sheet)
			{
				//����ʱ��
				SetCellStr(sheet, 1, 4, _FileInfo.filetm);
				//����ʱ��
				SetCellStr(sheet, 14, 2, _FileInfo.startDt);
				
			}
			wchar_t ws[100];
			swprintf(ws, 100, L"sheet%d", cnt + 1);
			sheet = book->insertSheet(cnt, ws, _sheetModule);
			_xlsxindex = 5;
			format = nullptr;
			format =sheet->cellFormat(_xlsxindex+1, 1);
			ClearSheet(sheet);
			SetCellStr(sheet, 1, 4, _FileInfo.filetm);
		}
	}
}

void ExcelOperate::InsertSheet(int row, AutoTestData atd)
{
	//���ñ��
	if (sheet)
	{
		
		int col = 0;
		char str[256] = { 0 };

		wchar_t * t = nullptr;
		int iSize;
		sprintf(str, "%d", row);
		iSize = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0); //iSize =wcslen(pwsUnicode)+1=6
		t = (wchar_t *)malloc(iSize * sizeof(wchar_t)); //
		c2w(str, t, iSize);
		sheet->writeStr(_xlsxindex, col++, t);
		if (t != nullptr)
			free(t);

		SetCellStr(sheet, _xlsxindex, col++, atd.name);
		SetCellStr(sheet, _xlsxindex, col++, atd.standardname);
		SetCellStr(sheet, _xlsxindex, col++, atd.val);
		SetCellStr(sheet, _xlsxindex, col++, atd.unit);
		if (atd.content == 1)
		{
			SetCellStr(sheet,_xlsxindex,col++,QString::fromLocal8Bit("��"));

		}
		else if(atd.content == 0)
		{
			SetCellStr(sheet, _xlsxindex, col++, QString::fromLocal8Bit("��"));
		}
		else
		{
			SetCellStr(sheet, _xlsxindex, col++, QString::fromLocal8Bit("//"));
		}
		_xlsxindex++;
		if (_xlsxindex >= 41)
		{
			int sheetcnt = book->sheetCount();
			//���һ�����
			if (book)
			{
				wchar_t ws[100];
				swprintf(ws, 100, L"sheet%d", sheetcnt + 1);
				sheet = book->insertSheet(sheetcnt, ws, _sheetModule);
				
				SetCellStr(sheet, 1, 4, _FileInfo.filetm);
				_xlsxindex = 5;
				ClearSheet(sheet);
				
			}
		}
	}
}

void ExcelOperate::SaveAs(int usetm)
{
		if (book)
		{
			QString str,filename;
			_FileInfo.endTm = LogMgr::GetInstance()->GetCurrentTm();
			//ϵͳ�Լ�20201218105355 K/AKD20 000000�ŵ���������ʱ������������ʱ�������ϵͳ�Լ���������
			//����ʱ�� ������ ���� ��ʼʱ��-����ʱ����в��Ե�Ԫ���Է�ʽ
			str.append(_FileInfo.unitName);
			str.append(_FileInfo.filetm);
			//str.append(_FileInfo.missileType);
			str.append(_FileInfo.missileName);
			str.append(_FileInfo.startDt);
			str.append(_FileInfo.startTm);
			str.append("-");
			str.append(_FileInfo.startDt);
			str.append(_FileInfo.endTm);
			str.append(_FileInfo.unitName);
			str.append(_FileInfo.modeName);
			filename = str;
			wchar_t ws[200];
			swprintf(ws, 200, L"./history/%s.xlsx",str.data());

			book->delSheet(1);
			//����һ������ҳ
			
			int sheetcnt = book->sheetCount();
			str = QString::fromLocal8Bit("��%1ҳ").arg(sheetcnt-1);//��������ҳ
			sheet = book->getSheet(0);
			SetCellStr(sheet, 6, 0, str);
			str = _FileInfo.startTm;
			str.append("-");
			str.append(_FileInfo.endTm);
			SetCellStr(sheet, 15, 2, str);//����ʱ��
			//������ʱ
			str = QString::fromLocal8Bit("%1��").arg(usetm);
			SetCellStr(sheet, 16, 2, str);//����ʱ��

			for (int i = 1; i < sheetcnt; i++)
			{
				sheet = book->getSheet(i);
				str = QString::fromLocal8Bit("��%1ҳ��%2ҳ").arg(sheetcnt - 1).arg(i);//��������ҳ
				SetCellStr(sheet, 43, 4, str);
			}
			if (book->save(ws))
			{
				InsertDB(filename);
			}
			book->release();
			book = nullptr;
			sheet = nullptr;
			_sheetModule = nullptr;
		}
		return;
}

void ExcelOperate::SetCellStr(Sheet* sheet1,int row, int col, QString str)
{
	if (!sheet1)
		return;
	int iSize = MultiByteToWideChar(CP_ACP, 0, str.toUtf8().data(), -1, NULL, 0); //iSize =wcslen(pwsUnicode)+1=6
	wchar_t* t = (wchar_t *)malloc(iSize * sizeof(wchar_t)); //
	c2w(str.toLocal8Bit().data(), t, iSize);
	sheet1->writeStr(row, col, t);
	if (t)
		free(t);
}


void ExcelOperate::ClearSheet(Sheet* sheet1)
{
	return;
	double height = sheet1->rowHeight(_xlsxindex);
	format->setBorder(BORDERSTYLE_NONE);
	for (int i = _xlsxindex; i < 43; i++)
	{
		sheet1->setRow(i, height, format);
		/*for (int j = 0; j < 6; j++)
		{
			sheet1->setCellFormat(i, j, format);
		}*/
	}
}

void ExcelOperate::InsertDB(QString filename)
{
	QString sql = QString("INSERT INTO history_file(state,missileType, missileName,unitName,\
	user, type, startDt,endDt,version, device, fileName, filePath,del) \
	VALUES(1, '%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9', '%10', '%11',0);")
		.arg(_FileInfo.missileType)
		.arg(_FileInfo.missileName)
		.arg(_FileInfo.unitName)
		.arg(GlobalManager::getInstance()->_user)//user
		.arg("1")//type
		.arg(_FileInfo.startDt)
		.arg(_FileInfo.startDt)//endDt
		.arg("")//version
		.arg("")//device;
		.arg(filename)//fileName;
		.arg("");//filePaht
	qDebug() << sql;
	QSqlQuery query;
	query.exec(sql);
}

