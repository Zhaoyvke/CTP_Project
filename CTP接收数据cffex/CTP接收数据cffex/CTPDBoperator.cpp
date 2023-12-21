#include "CTPDBoperator.h"
//#include "StringOpera.h"
//extern map<string, string> m_instrument2dbname;


CTPDBoperator::CTPDBoperator(string dbname,string tablepre)
{ 
	this->pre = tablepre;
	this->klinedbname = dbname;
	InitCon();//创建连接
    Producttablename();//生成数据库表名
	Cretetable();//创建表
}

void CTPDBoperator::tickkinsertDB(TickKline & tickk)
{
	string tablename = getTablenameBytype(tickk.type);
	char sql[2048];

	sprintf_s(sql, "insert into %stick values('%s','%s',%d,'%s','%s',%lf,%lf,%lf,%d,%lf,%lf,%lf,%d,%d,%lf,%lf,'%s','%s',%lf,%d,%lf,%d,%lf,default,'%s')"
		, tablename.c_str(), tickk.instumentId, tickk.type, tickk.sequence, tickk.tradeDay, tickk.updateTime, tickk.totalvolume, tickk.openInterest, tickk.closeprice, tickk.volume, tickk.openprice, tickk.highprice, tickk.lowprice, tickk.klineType, tickk.addposition, tickk.kaicangvolume, tickk.pingcangvolume, tickk.Dealtype, tickk.direction, tickk.buyprice, tickk.buyqty, tickk.sellprice, tickk.sellqty, tickk.weibi, tickk.local);

	unique_lock<mutex> lock(tickk_mutex);
	if (mysql_query(&tickcon, sql))
	{
		cout << "插入tickk数据出错!" <<mysql_error(&tickcon)<< endl;
		OutputDebugStringA("插入tickk数据出错!");
		system("pause");
		exit(0);
	}
}

void CTPDBoperator::klineinsertDB(TickKline & kline)
{
	string tablename = getTablenameBytype(kline.type);
	char sql[2048];
	sprintf_s(sql, "insert into %s values('%s','%s',%d,'%s','%s',%lf,%lf,%lf,%d,%lf,%lf,%lf,%d)"
		, tablename.c_str(), kline.instumentId, kline.type, kline.sequence, kline.tradeDay, kline.updateTime, kline.totalvolume, kline.openInterest, kline.closeprice, kline.volume, kline.openprice, kline.highprice, kline.lowprice, kline.klineType);
	unique_lock<mutex> lock(kline_mutex);
	if (mysql_query(&klinecon, sql))
	{
		cout << "插入kline数据出错!" << mysql_error(&klinecon) << endl;
		OutputDebugStringA("插入kline数据出错!");
		system("pause");
		exit(0);
	}
	
}

void CTPDBoperator::updateKlineDB(TickKline & kline)
{
	char sql[2048];
	string tablename = getTablenameBytype(kline.type);

	sprintf_s(sql, "update %s set totalvolume=%lf, openInterest=%lf,volume=%d,closeprice=%lf,highprice=%lf,lowprice=%lf,klineType=%d where updateTime='%s'", tablename.c_str(), kline.totalvolume, kline.openInterest, kline.volume, kline.closeprice, kline.highprice, kline.lowprice, kline.klineType, kline.updateTime);
	unique_lock<mutex> lock(kline_mutex);
	if (mysql_query(&klinecon, sql))
	{
		cout << "更新kline数据出错!!" << mysql_error(&klinecon) << endl;
		OutputDebugStringA("更新kline数据出错!");
		system("pause");
		exit(0);
	}
}

string CTPDBoperator::getTablenameBytype(string type)
{
	if (type == "M") {
		return tablenames[ONEMIN];
	}
	else if (type == "3M")
	{
		return  tablenames[THREEMIN];
	}
	else if (type == "5M") 
	{
		return tablenames[FIVEMIN];
	}
	else if (type == "15M")
	{
		return tablenames[FIFTEENMIN];
	}
	else if (type == "30M") 
	{
		return tablenames[THIRTMIN];
	}
	else if (type == "60M")
	{
		return tablenames[SIXTYMIN];
	}
	else if (type == "D") 
	{
		return tablenames[DAY];
	}

}

void CTPDBoperator::GetLastTickKline(vector<TickKline> &lasttickklines)
{
	string sql;
	char str[1000];
	for (int i = 0; i < tablenames.size() - 1; i++) {
		sprintf_s(str, " (select  totalvolume,openinterest,openprice,highprice,lowprice,closeprice,tradeDay,updateTime from %s order by updateTime desc limit 1) union all ", tablenames[i].c_str());
		sql += str;
	}
	sprintf_s(str, " (select totalvolume,openinterest,openprice,highprice,lowprice,closeprice ,tradeDay,updateTime from %s order by updateTime desc limit 1) ", tablenames[tablenames.size() - 1].c_str());
	sql += str;

	if (mysql_query(&klinecon, sql.c_str()))
	{
		OutputDebugStringA("获取上一个周期K线失败!");
		system("pause");
		exit(0);
	}
	MYSQL_RES *res = mysql_store_result(&klinecon);
	MYSQL_ROW row;
	if (res == NULL)
		return;
	int k = 0;
	while (row = mysql_fetch_row(res))
	{
		lasttickklines[k].totalvolume = atof(row[0]); //atof ：将给定的字符串值转换为双精度值。它接受一个包含浮点数的字符串并返回它的双精度值。
		lasttickklines[k].openInterest = atof(row[1]);
		lasttickklines[k].openprice = atof(row[2]);
		lasttickklines[k].highprice = atof(row[3]);
		lasttickklines[k].lowprice = atof(row[4]);
		lasttickklines[k].closeprice = atof(row[5]);
		strcpy(lasttickklines[k].tradeDay, row[6]);
		strcpy(lasttickklines[k].updateTime, row[7]);
		k++;
	}

}

void CTPDBoperator::GetKlinesBeforeId(Period pt, int id, int n, vector<IndexKLine>& ks, vector<double>& ks_close)
{
	char sql[1024];
	string tablename = tablenames[pt] + "tick";
	sprintf_s(sql, "select * from %s where id<%d order by id desc limit %d  ", tablename.c_str(), id, n);
	if (mysql_query(&tickcon, sql)) {
		cout << "mysql error:" << mysql_error(&tickcon) << endl;
		return;
	}
	MYSQL_RES *res = mysql_store_result(&tickcon);
	MYSQL_ROW row;
	while (row = mysql_fetch_row(res))
	{
		IndexKLine k;
		memset(&k, 0, sizeof(IndexKLine));
		strcpy_s(k.datatime, row[4]);
		strcpy_s(k.ID, row[0]);
		strcpy_s(k.tradeday, row[3]);
		k.hold = atoi(row[6]);
		k.close = atof(row[7]);
		k.vol = atoi(row[8]);
		k.open = atof(row[7]);
		k.max = atof(row[7]);
		k.min = atof(row[7]);
		k.KLineType = atoi(row[12]);
		ks.push_back(k);
		ks_close.push_back(k.close);
	}
	mysql_free_result(res);

}

void CTPDBoperator::GetKlinesBeforeUpdateTime(Period pt, string updateTime, int n, vector<IndexKLine>& ks, vector<double>& ks_close)
{
	char sql[1024];
	string tablename = tablenames[pt];
	sprintf_s(sql, "select * from %s where updateTime<'%s' order by updateTime desc limit %d  ", tablename.c_str(), updateTime.c_str(), n);
	if (mysql_query(&klinecon, sql)) {
		cout << "mysql error:" << mysql_error(&klinecon) << endl;
		return;
	}
	MYSQL_RES *res = mysql_store_result(&klinecon);
	MYSQL_ROW row;
	while (row = mysql_fetch_row(res))
	{
		IndexKLine k;
		memset(&k, 0, sizeof(IndexKLine));
		strcpy_s(k.datatime, row[4]);
		strcpy_s(k.ID, row[0]);
		strcpy_s(k.tradeday, row[3]);
		k.hold = atoi(row[6]);
		k.close = atof(row[7]);
		k.vol = atoi(row[8]);
		k.open = atof(row[9]);
		k.max = atof(row[10]);
		k.min = atof(row[11]);
		k.KLineType = atoi(row[12]);
		ks.push_back(k);
		ks_close.push_back(k.close);
	}
	mysql_free_result(res);
}

int CTPDBoperator::GetLastTick(subtick &sub_tick)
{
	int id = 0;
	string tablename = tablenames[TICK]+"tick";
	char sql[1024];
	sprintf_s(sql,"select instrumentID,tradeDay,closeprice,id,local from %s order by id desc limit 1", tablename.c_str());
	if(mysql_query(&tickcon,sql))
	{
		cout << "mysql error:" << mysql_error(&tickcon) << endl;
		return id;
	}
	MYSQL_RES *res = mysql_store_result(&tickcon);
	MYSQL_ROW row;
	while (row = mysql_fetch_row(res))
	{
		sub_tick.instrumentID = row[0];
		sub_tick.tradeDay = row[1];
		sub_tick.tickprice = atof(row[2]);
		id = atoi(row[3]);
		sub_tick.local = row[4];
	}
	return id;
}

void CTPDBoperator::GetKlineById(Period pt, int id, IndexKLine & k)
{
	memset(&k, 0, sizeof(IndexKLine));
	char sql[1024];
	string tablename = tablenames[pt]+"tick";
	sprintf_s(sql, "select * from %s where id=%d  ", tablename.c_str(), id);
	if (mysql_query(&tickcon, sql)) {
		cout << "mysql error:" << mysql_error(&tickcon) << endl;
		return;
	}
	MYSQL_RES *res = mysql_store_result(&tickcon);
	MYSQL_ROW row;
	while (row = mysql_fetch_row(res))
	{
		if (row[0] == NULL)
			break;
		strcpy_s(k.datatime, row[4]);
		strcpy_s(k.ID, row[0]);
		strcpy_s(k.tradeday, row[3]);
		k.hold = atoi(row[6]);
		k.close = atof(row[7]);
		k.vol = atoi(row[8]);
		k.open = atof(row[9]);
		k.max = atof(row[10]);
		k.min = atof(row[11]);
		k.KLineType = atoi(row[12]);
		strcpy_s(k.local, row[24]);
	}
	mysql_free_result(res);
}

void CTPDBoperator::GetCurrenttickkById(Period pt, int id, TickKline & currenttick)
{
	memset(&currenttick, 0, sizeof(TickKline));
	char sql[1024];
	string tablename = tablenames[pt] + "tick";
	sprintf_s(sql, "select * from %s where id=%d  ", tablename.c_str(), id);
	if (mysql_query(&tickcon, sql)) {
		cout << "mysql error:" << mysql_error(&tickcon) << endl;
		return;
	}
	MYSQL_RES *res = mysql_store_result(&tickcon);
	MYSQL_ROW row;
	while (row = mysql_fetch_row(res))
	{
		strcpy(currenttick.instumentId, row[0]);
		strcpy(currenttick.type, row[1]);
		currenttick.sequence = atoi(row[2]);
		strcpy(currenttick.tradeDay, row[3]);
		strcpy(currenttick.updateTime, row[4]);
		currenttick.totalvolume = atof(row[5]);
		currenttick.openInterest = atof(row[6]);
		currenttick.closeprice = atof(row[7]);
		currenttick.volume = atoi(row[8]);
		currenttick.openprice = atof(row[9]);
		currenttick.highprice = atof(row[10]);
		currenttick.lowprice = atof(row[11]);
		currenttick.klineType = atoi(row[12]);
		
		currenttick.addposition = atoi(row[13]);
		currenttick.kaicangvolume = atof(row[14]);
		currenttick.pingcangvolume = atof(row[15]);
		strcpy(currenttick.Dealtype, row[16]);
		strcpy(currenttick.direction, row[17]);
		currenttick.buyprice=atof(row[18]);
		currenttick.buyqty=atoi(row[19]);
		currenttick.sellprice = atof(row[20]);
		currenttick.sellqty = atoi(row[21]);
		currenttick.weibi = atof(row[22]);
		currenttick.id = atol(row[23]);
		strcpy(currenttick.local, row[24]);
	}
	mysql_free_result(res);
}

void CTPDBoperator::GetDayData(Period pt, int id, Kline &daykline)
{
	memset(&daykline, 0, sizeof(Kline));
	char sql[1024];
	string tablename = tablenames[pt] + "tick_tice";
	sprintf_s(sql, "select openprice,highprice,lowprice,closeprice from %s where id=%d  ", tablename.c_str(), id);
	if (mysql_query(&tickcon, sql)) {
		cout << "mysql error:" << mysql_error(&tickcon) << endl;
		return;
	}
	MYSQL_RES *res = mysql_store_result(&tickcon);
	MYSQL_ROW row;
	while (row = mysql_fetch_row(res))
	{
		daykline.openprice = atof(row[0]);
		daykline.highprice = atof(row[1]);
		daykline.lowprice = atof(row[2]);
		daykline.closeprice = atof(row[3]);
	}
	mysql_free_result(res);
}

void CTPDBoperator::Producttablename()
{
	tablenames.push_back(pre + "_onemkline");
	tablenames.push_back(pre + "_onemkline");
	tablenames.push_back(pre + "_3mkline");
	tablenames.push_back(pre + "_5mkline");
	tablenames.push_back(pre + "_15mkline");
	tablenames.push_back(pre + "_30mkline");
	tablenames.push_back(pre + "_60mkline");
	tablenames.push_back(pre + "_daykline");

	
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
	
	sprintf_s(sql, "create table  if not exists %stick (instrumentID varchar(20),type varchar(5),sequence int(4),tradeDay varchar(15),updateTime varchar(20),totalvolume double,openinterest double,closeprice double,volume int(9),openprice double,highprice double,lowprice double,klineType int(2), addposition int(5),openvolume double,evenvolume double,Dealtype varchar(20),direction varchar(2),buyprice double,buyqty int(10),sellprice double, sellqty int(10),weibi double, Id int(11) primary key auto_increment,local varchar(30))", tablenames[i].c_str());

		if (mysql_query(&tickcon, sql))
		{
			OutputDebugStringA("创建tickkline表有问题");
			return false;
		}
		sprintf_s(sql, "create table  if not exists %s (instrumentID varchar(20),type varchar(5),sequence int(4),tradeDay varchar(15),updateTime varchar(20) primary key,totalvolume double,openinterest double,closeprice double,volume int(9),openprice double,highprice double,lowprice double,klineType int(2))", tablenames[i].c_str());
		if (mysql_query(&klinecon, sql))
		{
			OutputDebugStringA("创建kline表有问题");
			return false;

		}

	}
	return true;
}
void CTPDBoperator::InitCon()
{

	mysql_init(&klinecon);  //初始化K线数据库的连接
	//kline 的连接
	if (mysql_real_connect(&klinecon, LOCALHOST, USER, SQLPASSWORD, klinedbname.c_str(), 3306, NULL, 0) == NULL) //如果返回为空说明数据库连接出错
	{
		cout << "数据库连接出错!" <<mysql_error(&klinecon)<< endl;
		system("pause");
		exit(0);
	}


	string tickkdbname="temp"+ klinedbname;
	//string tickkdbname= klinedbname;
	mysql_init(&tickcon);
	//klinetick的连接
	if (mysql_real_connect(&tickcon, LOCALHOST, USER, SQLPASSWORD, tickkdbname.c_str(), 3306, NULL, 0)==NULL)
	{
		cout << "数据库连接出错!" << mysql_error(&tickcon) << endl;
		system("pause");
		exit(0);
	}

}

void CTPDBoperator::CloseCon()
{
	mysql_close(&klinecon);
	mysql_close(&tickcon);

}

CTPDBoperator::~CTPDBoperator()
{
	mysql_close(&klinecon);
	mysql_close(&tickcon);
}
