#include "Index_Base.h"

Index_Base::Index_Base()
{
}

void Index_Base::clearmacdv() {
	es.clear();
	ep.clear();
	ed.clear();
}

void Index_Base::clearkdjv() {
	lv.clear();
	hv.clear();
	sv.clear();
	kv.clear();
	dv.clear();;
}

double Index_Base::EMA(int n, vector<double> &x, int cur, vector<double>& r)
{
	double y = x[cur + 149];//开始的y值
	r.push_back(y);
	for (int i = cur + 148; i >= cur; i--)		y = (2 * x[i] + (n - 1) * y) / (n + 1), r.push_back(y);
	return y;
}

double Index_Base::countdiff(vector<double> &close, int cur, int s, int p)
{
	double x = EMA(s, close, cur, es), y = EMA(p, close, cur, ep);
	ema_s[pt] = x, ema_p[pt] = y;
	return x - y;
}

double Index_Base::countMacd(vector<double> &close, int cur, int s, int p, int m)
{
	double DIFF = countdiff(close, cur, s, p);
	vector<double> v;
	for (int i = 0; i < 150; i++)	v.push_back(es[i] - ep[i]);
	reverse(v.begin(), v.end());
	double DEA = EMA(m, v, 0, ed);
	clearmacdv();//恢复状态
	curdiff[pt] = DIFF;
	curdea[pt] = DEA;
	curmacd[pt] = 2 * (DIFF - DEA);
	return curmacd[pt];
}

double Index_Base::LLV(int n, vector<double> &x, int cur, vector<double>& ans)
{
	if (!n)	return x[cur];
	deque<double> q;
	for (int i = cur + 88 + n; i >= cur; i--) {
		while (q.size() && q.front() >= i + 9)	q.pop_front();
		while (q.size() && x[q.back()] >= x[i])	q.pop_back();
		q.push_back(i);
		if (i <= cur + 89)	ans.push_back(x[q.front()]);
	}
	/*lo[pt] = {q.front(),cur};
	while (q.size()) {
		int t = q.front();
		low[pt].push_back(x[t]);
		q.pop_front();
	}*/
	return ans.back();
}

double Index_Base::HHV(int n, vector<double> &x, int cur, vector<double>& ans)
{
	if (!n)	return x[cur];
	deque<double> q;
	for (int i = cur + 88 + n; i >= cur; i--) {
		while (q.size() && q.front() >= i + 9)	q.pop_front();
		while (q.size() && x[q.back()] <= x[i])	q.pop_back();
		q.push_back(i);
		if (i <= cur + 89)	ans.push_back(x[q.front()]);
	}
	/*hi[pt] = { q.front(),cur };
	while (q.size()) {
		int t = q.front();
		high[pt].push_back(x[t]);
		q.pop_front();
	}*/
	return ans.back();
}

double Index_Base::RSV(int n, vector<double> &c, vector<double> &l, vector<double> &h, int cur, vector<double>& ans)
{
	LLV(n, l, cur, lv), HHV(n, h, cur, hv);
	double rsv;
	for (int i = 0, j = cur + 89; i < 90; i++, j--) {
		rsv = (c[j] - lv[i]) / (hv[i] - lv[i]) * 100;
		ans.push_back(rsv);
	}
	return ans.back();
}

double Index_Base::SMA(int n, int m, vector<double> &x, vector<double>& ans)
{
	double y = x[0];
	ans.push_back(y);
	for (int i = 1; i < 90; i++)	y = (m * x[i] + (n - m) * y) / n, ans.push_back(y);
	return y;
}

double Index_Base::J(int p1, int p2, int n, vector<double> &c, vector<double> &l, vector<double> &h, int cur)
{
	RSV(n, c, l, h, cur, sv);
	double K = SMA(p1, 1, sv, kv);
	double D = SMA(p2, 1, kv, dv);
	clearkdjv();//恢复状态
	curj[pt] = 3 * K - 2 * D;
	curk[pt] = K, curd[pt] = D;
	return curj[pt];
}

double Index_Base::SLLV(int n, vector<double>& x, int cur)
{
	double sl = 10000;
	for (int i = cur; i < cur + n; i++)	if (x[i] < sl)	sl = x[i];
	return sl;
}

double Index_Base::SHHV(int n, vector<double>& x, int cur)
{
	double sh = 0;
	for (int i = cur; i < cur + n; i++)	if (x[i] > sh)	sh = x[i];
	return sh;
}

double Index_Base::WR(vector<double>& h, vector<double>& l, double close, int m)
{
	double hh = SHHV(m, h, 0), ll = SLLV(m, l, 0);
	return -100 * (hh - close) / (hh - ll);
}

double Index_Base::GMMA(vector<double>& x, int n)
{
	double y = x[149];//开始的y值
	for (int i = 148; i >= 0; i--)		y = (2 * x[i] + (n - 1) * y) / (n + 1);
	return y;
}

Index_Base::~Index_Base()
{
}
