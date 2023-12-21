#ifndef ANALYSISBOX_H_
#define ANALYSISBOX_H_

#pragma once

#include<iostream>
#include<vector>
#include<Windows.h> 
#include"IndexStruct.h"
#define MACD_NUMS 150
class AnalysisBox
{
public:
	 AnalysisBox();

	//将k线容器转为相对应想要的容器(不使用!）
	void  KlineToClosePrice(std::vector<IndexKLine>* kline, std::vector<double> &Close);

	//计算均值
	double  CalculateMA(std::vector<double> *prices, int week);
	//计算布林线
	int  CalculateBOLL(std::vector<double>*prices, int week, int k, BOLL &boll);//求出股价的标准差及其信赖区间，从而确定股价的波动范围及未来走势，利用波带显示股价的安全高低价位，因而也被称为布林带。

	//EMA的计算
	double  CalculateEMA(std::vector<double> *prices, int days, std::vector<double> *ema);//指数移动平均值是以指数式递减加权的移动平均。

	//DEA的计算
	double  GetDIFF(std::vector<double> &diff, std::vector<double>* prices, int shortdays, int longdays);//

	//计算MACD指标,参数中有macd结构体引用，返回值是结构体中的成员变量macd

	double  CalculateMACD(std::vector<double> *prices, MACDType &macd, int shortdays, int longdays, int diffdays);

	//计算顾比均线
	double  GmmaAverage(std::vector<double> &pre_days_price, int cycle);
	void  CalculateGmma(std::vector<double> &pre_days_price, GMMA &gmma);

	double  Multn(double sum, int n);

	//计算KDJ
	void  CalculateKDJ(std::vector<IndexKLine>&k, int rsvquan, int kquan, int dquan, Kdj &kdj, int sda = 60);
	int  getlowandhightandclose(std::vector<IndexKLine>&k, int a, int b, int rsvquan, Kdj &kdj);
	double  getRSV(std::vector<IndexKLine>&k, int a, int b, int rsvquan, Kdj &kdj);
	double  getkdj_k(std::vector<IndexKLine>&k, int a, int b, int kquan, int rsvquan, Kdj &kdj);
	double  getkdj_d(std::vector<IndexKLine>&k, int a, int b, int dquan, int kquan, int rsvquan, Kdj &kdj);

	 ~AnalysisBox();

private:
	int nums = MACD_NUMS;

};
#endif