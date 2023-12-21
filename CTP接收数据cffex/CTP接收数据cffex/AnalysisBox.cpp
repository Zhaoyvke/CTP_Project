#include "AnalysisBox.h"

#include <cmath>
#include <cfloat>

AnalysisBox::AnalysisBox()
{
}

void AnalysisBox::KlineToClosePrice(std::vector<IndexKLine>* kline, std::vector<double> &Close)
{	
	for (unsigned int i = 0; i < kline->size(); i++) 
	{
		Close.push_back(kline->at(i).close);
	}
}


double AnalysisBox::CalculateMA(std::vector<double>* prices, int week)
{
	if (prices == NULL || prices->size() == 0)
	{
		OutputDebugString(TEXT( "CalculateMA: prices vec error") );
		return 1;
	}
	double sum = 0;
	for (int i = 0; i < week; i++) 
	{
		sum += prices->at(i);
	}
	return sum / week;
}


int AnalysisBox::CalculateBOLL(std::vector<double>* prices, int week, int k, BOLL & boll)
{
	if (prices == NULL || prices->size() == 0)
	{
		OutputDebugString(TEXT("CalculateBOLL: prices vec error"));
		return 1;
	}
	memset(&boll, 0, sizeof(BOLL));
	double MA = CalculateMA(prices, week);
	double MD = 0;
	for (int i = 0; i < week - 1; i++) {
		boll.MB += prices->at(i);
		MD += pow(prices->at(i) - MA, 2);
	}
	MD += pow(prices->at(week - 1) - MA, 2);
	boll.MB += prices->at(week - 1);
	MD = sqrt(MD / (week-1));
	boll.MB /= week ;
	boll.UP = boll.MB + k*MD;
	boll.DOWN = boll.MB - k*MD;
	return 0;
}


int AnalysisBox::getlowandhightandclose(std::vector<IndexKLine>&k, int a, int b, int rsvquan, Kdj &kdj)
{	
	if (k.size() == 0)
	{
		OutputDebugString(TEXT("getlowandhightandclose: K Line vec empty"));
		return 1;
	}
	for (int i = (b - a); i<(b - a + rsvquan); i++)
	{
		if (k[i].max > kdj.hight)
		{
			kdj.hight = k[i].max;
		}
		if (k[i].min < kdj.low)
		{
			kdj.low = k[i].min;
		}
	}
	return 0;
}


double AnalysisBox::getRSV(std::vector<IndexKLine>&k, int a, int b, int rsvquan, Kdj &kdj)
{
	if (k.size() == 0)
	{
		OutputDebugString(TEXT("getRSV: K Line vec empty"));
		return 1;
	}
	getlowandhightandclose(k, a, b, rsvquan, kdj);
	//（Cn－Ln） / （Hn－Ln）×100
	//cout << "k[b - a].close" << k[b - a].close << endl;
	double rsv1 = (k[b - a].close - kdj.low);
	rsv1 /= (kdj.hight - kdj.low);
	rsv1 *= 100;

	kdj.low = 9999;
	kdj.hight = 0;
	// cout << "getRSV rsv1:" << rsv1 << endl;
	return rsv1;

}

double AnalysisBox::getkdj_k(std::vector<IndexKLine>&k, int a, int b, int kquan, int rsvquan, Kdj &kdj)
{
	if (k.size() == 0)
	{
		OutputDebugString(TEXT("getkdj_k: K Line vec empty"));
		return 1;
	}
	if (a < 1)
	{
		return 50;
	}
	else
	{
		kdj.k = (kquan - 1) * getkdj_k(k, a - 1, b, kquan, rsvquan, kdj) / kquan;
		kdj.k += 1 * (getRSV(k, a, b, rsvquan, kdj)) / kquan;
		//cout << "getkdj_k" << kdj.k << endl;

		return kdj.k;
	}


}
double AnalysisBox::getkdj_d(std::vector<IndexKLine>&k, int a, int b, int dquan, int kquan, int rsvquan, Kdj &kdj)
{
	if (k.size() == 0)
	{
		OutputDebugString(TEXT("getkdj_d: K Line vec empty"));
		return 1;
	}
	if (a< 1)
	{
		return 50;
	}
	else
	{
		kdj.d = (dquan - 1)  * getkdj_d(k, a - 1, b, kquan, dquan, rsvquan, kdj) / dquan;
		kdj.d += 1 * (getkdj_k(k, a, b, kquan, rsvquan, kdj)) / dquan;
		//cout << "getkdj_d" << kdj.d << endl;
		return kdj.d;
	}

}

void AnalysisBox::CalculateKDJ(std::vector<IndexKLine> &k, int rsvquan, int kquan, int dquan, Kdj &kdj, int sda)
{
	if (k.size() == 0)
	{
		OutputDebugString(TEXT("CalculateKDJ: K Line vec empty"));
	}

	int b = sda;
	double kdj_k = getkdj_k(k, sda, b, kquan, rsvquan, kdj);
	//cout << "默认" << sda << "为起始的9周期的" << "kdj的k值" << kdj.k << endl;
	double kdj_d = getkdj_d(k, sda, b, dquan, kquan, rsvquan, kdj);
	//cout << "默认" << sda << "为起始的9周期的" << "kdj的d值" << kdj.d << endl;
	
	kdj.k = kdj_k;
	kdj.d = kdj_d;
	kdj.j = 3 * kdj_k - 2 * kdj_d;
	if (isnan(kdj.k)==true)
	{
		kdj.k = 0;
	}
	if (isnan(kdj.d) == true)
	{
		kdj.d = 0;
	}
	if (isnan(kdj.j) == true)
	{
		kdj.j = 0;
	}
	
	
}


//这里要注意的就是因为用到了erase函数，所以传进来的容器内容上是有所改变的,这点再调用的时候就需要特别注意了
//prices的大小要取150个
double AnalysisBox::CalculateEMA(std::vector<double> *prices, int days, std::vector<double> *ema)
{
	static double lastprice = 0;
	if (nums == 0) {
		nums = MACD_NUMS;
		return lastprice;
	}
	nums--;
	double a = 2.0 / (days + 1);
	std::vector<double>::iterator it = prices->begin();
	lastprice = (*it);
	double now = (*it)*a;
	prices->erase(it);
	double result = now + (1 - a)*CalculateEMA(prices, days, ema);
	if (ema != NULL)
	{
		ema->push_back(result);
	}
	return result;
}

double AnalysisBox::GetDIFF(std::vector<double>& diff, std::vector<double>* prices, int shortdays, int longdays)
{
	if (prices == NULL || prices->size() == 0)
	{
		OutputDebugString(TEXT("GetDIFF: prices vec error"));
		return 1;
	}
	std::vector<double> p;
	p.assign(prices->begin(), prices->end());
	std::vector<double> shortEMA;
	CalculateEMA(&p, shortdays, &shortEMA);
	p.assign(prices->begin(), prices->end());
	std::vector<double> longEMA;
	CalculateEMA(&p, longdays, &longEMA);
	for (unsigned int i = 0; i < shortEMA.size(); i++) {
		diff.push_back(shortEMA[i] - longEMA[i]);
	}
	return diff.back();
}

//macd的迭代是150次
double AnalysisBox::CalculateMACD(std::vector<double>* prices, MACDType &macd, int shortdays, int longdays, int diffdays)
{
	if (prices == NULL || prices->size() == 0)
	{
		OutputDebugString(TEXT("CalculateMACD: prices vec error"));
		return 1;
	}
	std::vector<double> p;
	p.assign(prices->begin(), prices->end());
	std::vector<double> diff;
	macd.DIFF = GetDIFF(diff, &p, shortdays, longdays);
	std::reverse(diff.begin(), diff.end());
	//获得DEA
	macd.DEA = CalculateEMA(&diff, diffdays, NULL);
	macd.MACD = 2 * (macd.DIFF - macd.DEA);
	return macd.DIFF - macd.DEA;
}


double AnalysisBox::GmmaAverage(std::vector<double> &pre_days_price, int cycle)
{
	if (pre_days_price.size() == 0)
	{
		OutputDebugString(TEXT("GmmaAverage: prices vec error"));
		return 1;
	}
	double sum2 = 0;
	double sum3 = 0;
	double sum4 = 0;
	double n;
	n = 2.0 / (cycle + 1);
	double sum5 = 0;
	for (int i = 1; i < pre_days_price.size(); i++) {
		sum5 = Multn((1 - n), i);
		sum3 = sum5 * pre_days_price[i];
		sum2 += sum3;
	}
	sum4 = n*(pre_days_price[0] + sum2);
	printf("%.3lf\n", sum4);
	return sum4;
}
void AnalysisBox::CalculateGmma(std::vector<double>& pre_days_price, GMMA &gmma)
{
	if (pre_days_price.size() == 0)
	{
		OutputDebugString(TEXT("CalculateGmma: prices vec error"));
	}
	gmma.EMA3 = GmmaAverage(pre_days_price, 3);
	gmma.EMA5 = GmmaAverage(pre_days_price, 5);
	gmma.EMA8 = GmmaAverage(pre_days_price, 8);
	gmma.EMA10 = GmmaAverage(pre_days_price, 10);
	gmma.EMA12 = GmmaAverage(pre_days_price, 12);
	gmma.EMA15 = GmmaAverage(pre_days_price, 15);
	gmma.EMA30 = GmmaAverage(pre_days_price, 30);
	gmma.EMA35 = GmmaAverage(pre_days_price, 35);
	gmma.EMA40 = GmmaAverage(pre_days_price, 40);
	gmma.EMA45 = GmmaAverage(pre_days_price, 45);
	gmma.EMA50 = GmmaAverage(pre_days_price, 50);
	gmma.EMA60 = GmmaAverage(pre_days_price, 60);
}

double AnalysisBox::Multn(double sum, int n)
{
	if (n == 1)
		return sum;
	else
		return sum*Multn(sum, n - 1);
}



AnalysisBox::~AnalysisBox()
{
}
