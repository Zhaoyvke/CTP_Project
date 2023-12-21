#pragma once

enum  Period
{
   TICK,ONEMIN, THREEMIN, FIVEMIN, FIFTEENMIN, THIRTMIN, SIXTYMIN, DAY
};
const int PTNUM = 8;
struct  Tick
{
	char instumentId[30];
	char tradeDay[35];
	char updateTime[35];
	double lastprice;
	double openprice;
	double highprice;
	double lowprice;
	int    volume;
	double totalvolume;//总量
	double openInterest;   //今持仓
	double PreOpenInterest;//昨持仓
	double buyprice;//买一价
	int buyqty; //买一量
	double sellprice;//卖一价
	int sellqty;//卖一量
	char local[35];
};
//K线结构体
struct  Kline
{
	char instumentId[30];
	char type[5];
	int sequence;//序列
	char tradeDay[35];
	char updateTime[35];
	double totalvolume;
	double openInterest;
	double closeprice;
	int    volume;
	double openprice;
	double highprice;
	double lowprice;
	int klineType; //1 阳线  0 阴线
};

//tickK线结构体
struct TickKline :public Kline
{
	long long id;
	char local[35];
	double weibi; //委比
	int  addposition;//盘口数据增仓
	double  kaicangvolume;//盘口数据开仓
	double pingcangvolume;//盘口数据平仓
	char Dealtype[10];//成交类型
	char  direction[2];//买卖方向
	double buyprice;//买一价
	int buyqty; //买一量
	double sellprice;//卖一价
	int sellqty;//卖一量
};
