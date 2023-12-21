#pragma once

//计算二价差的结构体
struct kline2price
{
	char instumentID[30];    //合约码
	char tradeDay[35];    //交易日
	double openprice;   //3价差K线的开盘价
	double highprice;   //最高价
	double lowprice;   //最低价
	double closeprice;  //3价差K线的收盘价
	char openticklocal[35];// 开盘价对应tick的local时间
	char closeticklocal[35];//收盘价对应tick的local时间
	int  duration;
};
struct  subtick
{
	string instrumentID;
	string tradeDay;
	double tickprice;
	string local;
};