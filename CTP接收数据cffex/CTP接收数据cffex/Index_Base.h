#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
using namespace std;
class Index_Base {
public:
	int pt;
	vector<double> es, ep, ed;
	vector<double> lv, hv, sv, kv, dv;
	double ema_s[6], ema_p[6], predea[6];
	double prek[6], pred[6];
	double curema_s[6], curema_p[6], curdea[6];
	double curk[6], curd[6];
	double curj[6], curdiff[6], curmacd[6];
	/*deque<double> low[6], high[6];//存储单调队列最后所有元素映射的值
	pair<int, int> lo[6],hi[6];//存储单调队列队头下标和遍历结束的下标*/

public:
	Index_Base();

	void clearmacdv();

	void clearkdjv();

	double EMA(int n, vector<double> &x, int cur, vector<double> &r);
	//计算DIFF
	double countdiff(vector<double> &close, int cur, int s, int p);
	//计算MACD指标
	double countMacd(vector<double> &close, int cur, int s, int p, int m);

	//计算LLV
	double LLV(int n, vector<double> &x, int cur, vector<double> &ans);

	//计算HHV
	double HHV(int n, vector<double> &x, int cur, vector<double> &ans);

	//计算RSV
	double RSV(int n, vector<double> &c, vector<double> &l, vector<double> &h, int cur, vector<double> &ans);
	//计算SMA
	double SMA(int n, int m, vector<double> &x, vector<double> &ans);
	//计算J
	double J(int p1, int p2, int n, vector<double> &c, vector<double> &l, vector<double> &h, int cur);

	double SLLV(int n, vector<double> &x, int cur);

	double SHHV(int n, vector<double> &x, int cur);

	double WR(vector<double> &h, vector<double> &l, double close, int m);

	double GMMA(vector<double> &x, int n);//顾比线


	~Index_Base();
};