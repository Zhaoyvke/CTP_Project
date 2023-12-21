
#ifndef MYSTRUCT_H_
#define MYSTRUCT_H_
#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>



using namespace std;
//enum PeriodType
//{
//	TICK,ONEMINUTE, THREEMINUTE, FIVEMINUTE,FIFTEEN, THIRTYMINUTE
//};

enum KLineData
{
	OPEN, HIGH, LOW, CLOSE
};

//定义死叉结构体
struct deadCross {
	double open;
	double min;
	char datatime[20];
	char mindatatime[20];
};

//持仓的结构体
struct position 
{
	char userID[20];			//用户名
	char instrument[20];		//品种名
	char dateTime[30];			//极星下单响应时间
	short tradeDirection;		//买卖方向
	int num;					//手数
	double prices;				//下单价格
	int orderId;				//下单编号
	char strategy[20];			//下单的策略
	int positionDirection;		//开平方向		0为开，1为平
	int status;					//开平状态		0为已开，没平。1为已开，已平。
	char KTime[30];       //下单对应K线
};

struct Order
{
	
};

struct IndexKLine {
	double open;
	double close;
	double max;
	double min;
	int KLineType;
	double wavg;
	int vol;
	int hold;
	char tradeday[20];
	char datatime[20];
	char ID[30];
	char local[30];
};




struct MACDType {
	double DIFF;
	double DEA;
	double MACD;
};

struct  GMMA
{
    double EMA3;
	double EMA5;
	double EMA8;
	double EMA10;
	double EMA12;
	double EMA15;
	double EMA30;
	double EMA35;
	double EMA40;
	double EMA45;
	double EMA50;
	double EMA60;
};

struct Kdj {
	int rsv_zhouqi = 0;
	double low = 9999;
	double hight = 0;
	double rsv = 0;
	double k;
	double d;
	double j;
};


//布林线的结构体
struct BOLL {
	double MB;  //中轨
	double UP;  //上轨
	double DOWN; //下轨
};


//ADX结构体
struct ADX
{
	double pdi;
	double mdi;
	double adx;
	double adxR;
	double dx;
};
struct NodeInfo
{
	char indexname[40];
	char symbol[20];
	vector<double> value;
	int num;
	int fangXiang;
	double probability1;
	double probability2;
};



struct CSVLine :IndexKLine
{
	BOLL boll;
	BOLL boll_lag1;
	BOLL boll_lag2;
	MACDType MacdT;
	Kdj  kdj;
	MACDType MacdT_lag1;
	Kdj  kdj_lag1;
	MACDType MacdT_lag2;
	Kdj  kdj_lag2;
	double ma5;
	double ma10;
	double ma20;
	double ma60;
	double ma5_lag1;
	double ma10_lag1;
	double ma20_lag1;
	double ma60_lag1;
	double ma5_lag2;
	double ma10_lag2;
	double ma20_lag2;
	double ma60_lag2;

	double close_lag1;
	double close_lag2;
	double open_lag1;
	double open_lag2;
	double high_lag1;
	double high_lag2;
	double low_lag1;
	double low_lag2;

	double wr14;
	double wr28;
	double wr34;

	double gmma3;
	double gmma5;
	double gmma10;
	double gmma30;
	double gmma45;
	double gmma60;
};
#endif