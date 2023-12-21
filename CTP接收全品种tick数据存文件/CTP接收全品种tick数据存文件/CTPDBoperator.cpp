#include "CTPDBoperator.h"
//#include "StringOpera.h"
//extern map<string, string> m_instrument2dbname;


CTPDBoperator::CTPDBoperator(string dbname,string tablepre)
{ 
	this->pre = tablepre;
	this->tickdbname = dbname;
	InitCon();//创建连接
    Producttablename();//生成数据库表名
	Cretetable();//创建表
}

void CTPDBoperator::Producttablename()
{

	tablenames.push_back(pre + "_tick");
}

bool CTPDBoperator::Cretetable()
{
	if (tablenames.size() == 0)
	{
		OutputDebugStringA("创建数据库表时,表名容器为空");
	}
	char sql[1024];
	for (int i = 0; i < tablenames.size(); i++)
	{
		sprintf_s(sql, "create table  if not exists %s (Local varchar(35),TradingDay varchar(11),InstrumentID varchar(9),ExchangeID varchar(9),ExchangeInstID varchar(9),"
			"LastPrice double, PreSettlementPrice double, PreClosePrice double, PreOpenInterest double,OpenPrice double, HighestPrice double,LowestPrice double,Volume int, Turnover double,OpenInterest double,ClosePrice double,"
			"SettlementPrice double, UpperLimitPrice double, LowerLimitPrice double, PreDelta double, CurrDelta double,BidPrice1 double, BidVolume1 int,AskPrice1 double,AskVolume1 int,BidPrice2 double,BidVolume2 int,"
			"AskPrice2 double,AskVolume2 int,BidPrice3 double,BidVolume3 double,AskPrice3 double, AskVolume3 int,BidPrice4 double,BidVolume4 double,AskPrice4 double, AskVolume4 int,BidPrice5 double,BidVolume5 double,AskPrice5 double, AskVolume5 int,AveragePrice double,index local_index(Local),index TradingDay_index(TradingDay))", tablenames[i].c_str());
		if (mysql_query(&tickcon, sql))
		{
			//OutputDebugStringA("创建tick表有问题");
			string weizhi =to_string(__LINE__)+__FILE__;
			string error = mysql_error(&tickcon);
			WriteLog::writeloginfo(weizhi+error);
			return false;
		}
	}
	return true;

}
void CTPDBoperator::InitCon()
{

	
	mysql_init(&tickcon);
	if (mysql_real_connect(&tickcon, LOCALHOST, USER, SQLPASSWORD, tickdbname.c_str(), 3306, NULL, 0)==NULL)
	{
		cout << "数据库连接出错!" << mysql_error(&tickcon) << endl;
		system("pause");
		exit(0);
	}

}
void CTPDBoperator::InsertToTickTable(CTPtick ctptick, string tablename)
{
	char sql[10240];
	sprintf_s(sql, "insert into %s values('%s','%s','%s','%s','%s',%lf,%lf,%lf,%lf,%lf,%lf,%lf,%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%d,%lf,%d,%lf,%d,%lf,%d,%lf,%d,%lf,%d,%lf,%d,%lf,%d,%lf,%d,%lf,%d,%lf)",
		tablename.c_str(), ctptick.local, ctptick.TradingDay, ctptick.InstrumentID, ctptick.ExchangeID, ctptick.ExchangeInstID, ctptick.LastPrice, ctptick.PreSettlementPrice, ctptick.PreClosePrice, ctptick.PreOpenInterest, ctptick.OpenPrice, ctptick.HighestPrice, ctptick.LowestPrice, ctptick.Volume,ctptick.Turnover,ctptick.OpenInterest,
		ctptick.ClosePrice, ctptick.SettlementPrice, ctptick.UpperLimitPrice, ctptick.LowerLimitPrice, ctptick.PreDelta, ctptick.CurrDelta, ctptick.BidPrice1, ctptick.BidVolume1, ctptick.AskPrice1, ctptick.AskVolume1,
		ctptick.BidPrice2, ctptick.BidVolume2, ctptick.AskPrice2, ctptick.AskVolume2, ctptick.BidPrice3, ctptick.BidVolume3, ctptick.AskPrice3, ctptick.AskVolume3, ctptick.BidPrice4, ctptick.BidVolume4, ctptick.AskPrice4, ctptick.AskVolume4,
		ctptick.BidPrice5, ctptick.BidVolume5, ctptick.AskPrice5, ctptick.AskVolume5, ctptick.AveragePrice);
		if (mysql_query(&tickcon, sql))
		{
			string weizhi = to_string(__LINE__) + __FILE__;
			string error = mysql_error(&tickcon);
			WriteLog::writeloginfo(weizhi + error+","+ ctptick.InstrumentID+","+ ctptick.local+"数据库表名"+tablename);
			return ;
		}
		return;
}

CTPDBoperator::~CTPDBoperator()
{
	mysql_close(&tickcon);
}
