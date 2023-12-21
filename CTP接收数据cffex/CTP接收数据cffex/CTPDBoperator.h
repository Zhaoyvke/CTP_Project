#pragma once
#include <string>
#include <vector>
#include <map>
#include "klineStruct.h"
#include "IndexStruct.h"
#include "dif2price.h"
#include "../include/mysql.h"
#include <iostream>
#include <mutex>
#define   LOCALHOST   "localhost"
#define   USER        "root"
#define   SQLPASSWORD "root"

using namespace std;
//接收CTP数据,相关数据库操作
class CTPDBoperator
{
public:
	CTPDBoperator(string dbname,string tablepre);
	~CTPDBoperator();

	void  tickkinsertDB(TickKline & tickk);  //将tickk 数据插入到数据库
	void  klineinsertDB(TickKline & kline);  //将kline 数据插入到数据库
	void  updateKlineDB(TickKline & kline); //更新kline数据库 /******
	string getTablenameBytype(string type);
	//从数据库里面获取最新的所有周期K线的信息 来初始化lasttickklines 的总量、成交量、开、高、低、收
	void GetLastTickKline(vector<TickKline> &lasttickklines);
  
	/*========和计算tick指标相关的数据库操作=========*/
	//string GetTablenameBypt(PeriodType pt)
	void GetKlinesBeforeId(Period pt, int id, int n, vector<IndexKLine>& ks, vector<double>& ks_close);

	void GetKlinesBeforeUpdateTime(Period pt, string updateTime, int n, vector<IndexKLine>& ks, vector<double>& ks_close);

	//取当前数据库最新tick的数据
	int GetLastTick(subtick &sub_tick);
	//根据id获取K线
	void GetKlineById(Period pt, int id, IndexKLine &k);
	//获取当前tickk
	void GetCurrenttickkById(Period pt, int id,TickKline &currenttick);
	//获取当前daytick 的开高低收
	void GetDayData(Period pt, int id,Kline &daykline);

	void  InitCon();     //初始化数据库连接
	void  CloseCon();     //断开与数据的连接

public:


private:	
	void Producttablename(); //生成表名
	bool Cretetable();  //创建表
	

private:

	mutex kline_mutex;
	mutex tickk_mutex;
	string pre;      //合约码
	string klinedbname;  //数据库名称
	MYSQL klinecon;   //K线数据库连接 
	MYSQL tickcon;     //tick  数据库连接
	vector<string> tablenames; // k线表名

	
	//vector<TickKline> lasttickklines; //各个周期的上一根K线
};

