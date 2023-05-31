#include "ExcelOperate.h"
#include "LogMgr.h"
#include "GlobalManager.h"
#include <QSqlQuery>
#include <QDebug>
//中文的内容读出来后要进行编码的转换，这个为转换函数：wchar_t to char
char *w2c(char *pcstr, const wchar_t *pwstr, size_t len)
{
	int nlength = wcslen(pwstr);
	//获取转换后的长度
	int nbytes = WideCharToMultiByte(0, 0, pwstr, nlength, NULL, 0, NULL, NULL);
	if (nbytes > len)   nbytes = len;
	// 通过以上得到的结果，转换unicode 字符为ascii 字符
	WideCharToMultiByte(0, 0, pwstr, nlength, pcstr, nbytes, NULL, NULL);
	return pcstr;
}
//中文的内容读出来后要进行编码的转换，这个为转换函数：wchar_t to char
wchar_t *c2w(const char *pcstr, wchar_t *pwstr, int len)
{
	//int iSize;
	//	wchar_t* pwszUnicode;
		//返回接受字符串所需缓冲区的大小，已经包含字符结尾符'\0'
	//iSize = MultiByteToWideChar(CP_ACP, 0, pcstr, -1, NULL, 0); //iSize =wcslen(pwsUnicode)+1=6
	//pwstr = (wchar_t *)malloc(iSize * sizeof(wchar_t)); //不需要 pwszUnicode = (wchar_t *)malloc((iSize+1)*sizeof(wchar_t))
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
		swprintf(ws, 100, L"./ini/syscheck.xlsx");//系统自检
	if (type == ATT_AUTO)
	{
		if (unit == INS_TEST)
		{
			swprintf(ws, 100, L"./ini/inscheck.xlsx");//自动测试-》惯导测试
		}
		if (unit == SIGNLE_TEST)
		{
			swprintf(ws, 100, L"./ini/singlecheck.xlsx");//自动测试-》单项测试
		}
		if (unit == MULT_TEST)
		{
			swprintf(ws, 100, L"./ini/multcheck.xlsx"); //自动测试 - 》综合测试
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

	book = xlCreateXMLBook();//创建一个二进制格式的XLS（Execl97-03）的实例,在使用前必须先调用这个函数创建操作excel的对象
   //book->setKey(......);//如果购买了该库，则设置相应的key，若没有购买，则不用这行
	if (book)//是否创建实例成功
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
				//设置时间
				SetCellStr(sheet, 1, 4, _FileInfo.filetm);
				//设置时间
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
	//设置表格
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
			SetCellStr(sheet,_xlsxindex,col++,QString::fromLocal8Bit("√"));

		}
		else if(atd.content == 0)
		{
			SetCellStr(sheet, _xlsxindex, col++, QString::fromLocal8Bit("×"));
		}
		else
		{
			SetCellStr(sheet, _xlsxindex, col++, QString::fromLocal8Bit("//"));
		}
		_xlsxindex++;
		if (_xlsxindex >= 41)
		{
			int sheetcnt = book->sheetCount();
			//添加一个表格
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
			//系统自检20201218105355 K/AKD20 000000号导弹年月日时分秒至年月日时分秒进行系统自检连续测试
			//类型时间 弹类型 弹号 开始时间-结束时间进行测试单元测试方式
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
			//设置一共多少页
			
			int sheetcnt = book->sheetCount();
			str = QString::fromLocal8Bit("共%1页").arg(sheetcnt-1);//不包含首页
			sheet = book->getSheet(0);
			SetCellStr(sheet, 6, 0, str);
			str = _FileInfo.startTm;
			str.append("-");
			str.append(_FileInfo.endTm);
			SetCellStr(sheet, 15, 2, str);//测试时间
			//测试用时
			str = QString::fromLocal8Bit("%1秒").arg(usetm);
			SetCellStr(sheet, 16, 2, str);//测试时间

			for (int i = 1; i < sheetcnt; i++)
			{
				sheet = book->getSheet(i);
				str = QString::fromLocal8Bit("共%1页第%2页").arg(sheetcnt - 1).arg(i);//不包含首页
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

