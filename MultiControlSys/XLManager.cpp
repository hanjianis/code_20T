#include "XLManager.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QLabel>
#include "libxl/libxl.h"

#pragma comment(lib,"libxl/libxl.lib")
using namespace  libxl;
XLManager* XLManager::m_pInstance = nullptr;
XLManager::XLManager(QObject *parent)
	: QObject(parent)
{

	LoadItems();
	LoadXL();
	LoadDevice();
}

XLManager::~XLManager()
{
}

XLManager* XLManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new XLManager(nullptr);
	}
	return m_pInstance;
}

//加载数据库表格
void XLManager::LoadXL()
{
    QString strSql = QString("SELECT * FROM	Systemselftest;");
    QSqlQuery query;
    query.exec(strSql);    //

    while (query.next())
    {
        int id = query.value(0).toInt();
        AutoTestData data;
        data.id = id;
        data.num = query.value("num").toInt();
        data.datatype = query.value("datatype").toInt();
        data.type = query.value("type").toInt();
        data.name = query.value("name").toString();
        data.standardname = query.value("standardname").toString();
        data.standardval = query.value("standardval").toFloat();
        data.min = query.value("min").toFloat();
        data.max = query.value("max").toFloat();
        data.val = query.value("val").toString();
        data.unit = query.value("unit").toString();
        data.content = query.value("content").toInt();
        data.tip = query.value("tip").toString();
        data.tm = query.value("tm").toInt();
        data.standardtype=query.value("standardtype").toInt();

        m_lstSystemselftest[data.datatype].push_back(data);
    }

    strSql = QString("SELECT * FROM	Airtightnessinspection;");
    query.exec(strSql);    //

    while (query.next())
    {
        int id = query.value(0).toInt();
        AutoTestData data;
        data.id = id;
        data.num = query.value("num").toInt();
        data.datatype = query.value("datatype").toInt();
        data.type = query.value("type").toInt();
        data.name = query.value("name").toString();
        data.standardname = query.value("standardname").toString();
        data.standardval = query.value("standardval").toFloat();
        data.min = query.value("min").toFloat();
        data.max = query.value("max").toFloat();
        data.val = query.value("val").toString();
        data.unit = query.value("unit").toString();
        data.content = query.value("content").toInt();
        data.tip = query.value("tip").toString();
        data.tm = query.value("tm").toInt();

        m_lstAirtightnessinspection[data.datatype].push_back(data);
    }


    strSql = QString("SELECT * FROM	mnltdjc;");
	query.exec(strSql);    //

	while (query.next())
	{
		int id = query.value(0).toInt();
		AutoTestData data;
		data.id = id;
		data.num = query.value("num").toInt();
		data.datatype = query.value("datatype").toInt();
		data.type = query.value("type").toInt();
		data.name = query.value("name").toString();
		data.standardname = query.value("standardname").toString();
		data.standardval = query.value("standardval").toFloat();
        data.min = query.value("min").toFloat();
        data.max = query.value("max").toFloat();
		data.val = query.value("val").toString();
		data.unit = query.value("unit").toString();
		data.content = query.value("content").toInt();
		data.tip = query.value("tip").toString();

		m_lstMNLTDJC[data.datatype].push_back(data);
	}

	strSql = QString("SELECT * FROM	singletest;");
	query.exec(strSql);
	while (query.next())
	{
		int id = query.value(0).toInt();
		AutoTestData data;
		data.id = id;
		data.num = query.value("num").toInt();
		data.datatype = query.value("datatype").toInt();
		data.type = query.value("type").toInt();
		data.name = query.value("name").toString();
		data.standardname = query.value("standardname").toString();
		data.standardval = query.value("standardval").toFloat();
		data.min = query.value("min").toFloat();
		data.max = query.value("max").toFloat();
		data.val = query.value("val").toString();
		data.unit = query.value("unit").toString();
		data.content = query.value("content").toInt();
		data.tm = query.value("tm").toInt();
		data.tip = query.value("tip").toString();
		data.standardtype = query.value("standardType").toInt();
		m_mapSINGLE_TEST[data.datatype].push_back(data);
	}
	//惯导测试项
	strSql = QString("SELECT * FROM	ins;");
	query.exec(strSql);
	while (query.next())
	{
		int id = query.value(0).toInt();
		AutoTestData data;
		data.id = id;
		data.num = query.value("num").toInt();
		data.datatype = query.value("datatype").toInt();
		data.type = query.value("type").toInt();
		data.name = query.value("name").toString();
		data.standardname = query.value("standardname").toString();
		data.standardval = query.value("standardval").toFloat();
		data.min = query.value("min").toFloat();
		data.max = query.value("max").toFloat();
		data.val = query.value("val").toString();
		data.unit = query.value("unit").toString();
		data.content = query.value("content").toInt();
		data.tm = query.value("tm").toInt();
		data.tip = query.value("tip").toString();
		data.standardtype = query.value("standardType").toInt();

		m_mapINS[data.id] = data;
	}
	//综合测试项
	strSql = QString("SELECT * FROM	multtest;");
	query.exec(strSql);
	while (query.next())
	{
		int id = query.value(0).toInt();
		AutoTestData data;
		data.id = id;
		data.num = query.value("num").toInt();
		data.datatype = query.value("datatype").toInt();
		data.type = query.value("type").toInt();
		data.tm = query.value("tm").toInt();
		data.name = query.value("name").toString();
		data.standardname = query.value("standardname").toString();
		data.standardval = query.value("standardval").toFloat();
		data.min = query.value("min").toFloat();
		data.max = query.value("max").toFloat();
		data.val = query.value("val").toString();
		data.unit = query.value("unit").toString();
		data.content = query.value("content").toInt();
		data.tip = query.value("tip").toString();
		data.standardtype = query.value("standardType").toInt();
		m_mapMULT_TEST[data.datatype].push_back(data);
	}

    //综合测试
    strSql = QString("SELECT * FROM	Integratedtesting;");
    query.exec(strSql);    //

    while (query.next())
    {
        int id = query.value(0).toInt();
        AutoTestData data;
        data.id = id;
        data.num = query.value("num").toInt();
        data.datatype = query.value("datatype").toInt();
        data.type = query.value("type").toInt();
        data.name = query.value("name").toString();
        data.standardname = query.value("standardname").toString();
        data.standardval = query.value("standardval").toFloat();
        data.min = query.value("min").toFloat();
        data.max = query.value("max").toFloat();
        data.val = query.value("val").toString();
        data.unit = query.value("unit").toString();
        data.content = query.value("content").toInt();
        data.tip = query.value("tip").toString();
        data.tm = query.value("tm").toInt();
        data.standardtype=query.value("standardtype").toInt();

        m_lstIntegratedtesting[data.datatype].push_back(data);
    }

    //舵机回零
    strSql = QString("SELECT * FROM	Zeroreturnsteeringgear;");
    query.exec(strSql);    //

    while (query.next())
    {
        int id = query.value(0).toInt();
        AutoTestData data;
        data.id = id;
        data.num = query.value("num").toInt();
        data.datatype = query.value("datatype").toInt();
        data.type = query.value("type").toInt();
        data.name = query.value("name").toString();
        data.standardname = query.value("standardname").toString();
        data.standardval = query.value("standardval").toFloat();
        data.min = query.value("min").toFloat();
        data.max = query.value("max").toFloat();
        data.val = query.value("val").toString();
        data.unit = query.value("unit").toString();
        data.content = query.value("content").toInt();
        data.tip = query.value("tip").toString();
        data.tm = query.value("tm").toInt();

        m_lstZeroreturnsteeringgear[data.datatype].push_back(data);
    }
}


//加载测试项目
void XLManager::LoadItems()
{
	QString strSql = QString("SELECT * FROM	selfcheckitem;");
	QSqlQuery query;
	query.exec(strSql);    //

	while (query.next())
	{
		m_lstSelfCheckItems.push_back(query.value("name").toString());
	}

	strSql = QString("SELECT * FROM	autotestitems;");

	query.exec(strSql);    //

	while (query.next())
	{
		m_lstAutoTestItems.push_back(query.value("name").toString());
	}
	//自动测试时 下面的listwidget项
	strSql = QString("SELECT * FROM	items;");
	query.exec(strSql);    
	while (query.next())
	{
		AutoTestList atl;
		atl.id = query.value("id").toInt();
		atl.note = query.value("note").toString();
		atl.autoVal = query.value("val").toString();
		atl.type = query.value("type").toInt();
		atl.val = nullptr;
		m_mapAutoTestList[atl.id] = atl;
	}

}

void XLManager::LoadDevice()
{
	QString strSql = QString("SELECT * FROM	deviceList;");
	QSqlQuery query;

	query.exec(strSql);
	while (query.next())
	{
		DeviceInfo atl;
		atl.id = query.value("id").toInt();
		atl.note = query.value("note").toString();
		atl.ip = query.value("ip").toString();;
		atl.port = query.value("port").toInt();;
		atl.onlineflag = query.value("onlineflag").toInt();
		atl.heartcmd = query.value("heartcmd").toInt();
		m_mapDevice[atl.heartcmd] = atl;
	}
}
