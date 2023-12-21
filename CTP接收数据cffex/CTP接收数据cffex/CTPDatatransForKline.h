#pragma once
#include "CTPDBoperator.h"
#include "TimeDeal.h"
#include "KlineStruct.h"
#include <thread>
#include"DealSpicalTime.h"
#include "AnalysisBox.h"
#include "IndexStruct.h"
#include "RunTime.h"
#include "dif2price.h"
#include "Index_Base.h"
class CTPDatatransForKline
{
public:
	CTPDatatransForKline(string instrumentID);
	~CTPDatatransForKline();

	void CaltickkAndInsertDB(Tick *tick);//计算K线并且存入数据库
	
	void convertUpdateTime(string const& updatetime, string &descupdateTime, int pt);//pt传入转化周期 1,3,5,30,30,60 24*60  以分钟为单位
private:
	bool tickisUpdate(Tick *tick);  //判断tick是否需要更新
	

	void updateXperiodkline(Tick *tick, int X, Period pt);  //tick 代表数据 pt代表周期

	void Caltickkline(TickKline & nowtickkline, Tick *tick, string const &newupdateTime, Period pt);//********（计算k线更新后的值？）
	//计算K线类型
	int calKlineType(double open, double close, double lastclose);
	//k线赋值  将 srctickkline的值赋值给 desctickkline
	void copyTickKline(TickKline &srctickkline, TickKline &desctickkline); 
	//对updateTime计算出离整点开差几分钟 type传入的是周期 以分钟为单位 
	 int calDIffTimeMins(string const &updateTime, int Type);
	
	 
	  /*和指标生成相关的函数*/
public:
	//通过id 获取当前tickk
	void ProductOneKind(int id, Period pt, CSVLine &csvl);
	//通过id 获取当前day 的开高低收
	void GetCurrenttickByid(int id, TickKline&currenttick);
	
	void GetCurrentDayData(int id,Kline &daykline);
	void StarConvert(int id);
	void SaveindexCsv(ofstream & fwrite, TickKline &Currenttickk, const CSVLine &csv_tick, const CSVLine & csv_1, const CSVLine & csv_3, const CSVLine & csv_5, const CSVLine & csv_15, const CSVLine & csv_30,Kline &daykline);
	
	//用来计算2价差的函数
	void Cal2difBaseprice(subtick sub_tick);

	void Save2difpriceCsv();
	void writelog(double baseprice,double tickprice,string baselocal,string ticklocal);//记录不符合条件的tick日志
	void  writelocal(string local,double tickprice);
	//判断Kdj是否为空值
	//void JudgeKDjIsNan(const CSVLine &csv_tick, const CSVLine & csv_1, const CSVLine & csv_3, const CSVLine & csv_5, const CSVLine & csv_15, const CSVLine & csv_30);
	
	void KLineDataPicker(vector<IndexKLine> &K0, vector<double> &Kdata, string datatype);
private:
	CTPDBoperator *ctpOper;  //与数据库操作相关的对象
	AnalysisBox  indexOper;  //计算指标的对象
	string exchange;  //数据库名称
	string pre;      //品种名称
	string  indexcsvpre; //csv文件的名称
	int lasttickkid;//记录上一个tick的id  计算指标时会用到
	vector<TickKline> lasttickklines; //各个周期的上一根tickk线
	vector<double>LastTickklinesClosePrices;//各个周期上一个K线的收盘价

	kline2price current2pricekline;// 当前基价
	int num;//用来记录两个基价间的tick个数
	string last3pricetradeday;
	string lastXpriceupdateTime_hour = ""; //上一个tick对应的周期时间的 hour

	bool IsRestart;//判断基价程序是否从重新计算

	string endtime;//收盘时间点
	//string currentpriceupdateTime_hour; //当前tick对应周期时间的  hour

	double difprice;//差价
	Index_Base indl;

	double prebase1, prebase2;
	int isbase1, isbase2, y_type1, y_type2;
	int prehour, curhour;
	ofstream fday;
};

