
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

//��������ṹ��
struct deadCross {
	double open;
	double min;
	char datatime[20];
	char mindatatime[20];
};

//�ֲֵĽṹ��
struct position 
{
	char userID[20];			//�û���
	char instrument[20];		//Ʒ����
	char dateTime[30];			//�����µ���Ӧʱ��
	short tradeDirection;		//��������
	int num;					//����
	double prices;				//�µ��۸�
	int orderId;				//�µ����
	char strategy[20];			//�µ��Ĳ���
	int positionDirection;		//��ƽ����		0Ϊ����1Ϊƽ
	int status;					//��ƽ״̬		0Ϊ�ѿ���ûƽ��1Ϊ�ѿ�����ƽ��
	char KTime[30];       //�µ���ӦK��
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


//�����ߵĽṹ��
struct BOLL {
	double MB;  //�й�
	double UP;  //�Ϲ�
	double DOWN; //�¹�
};


//ADX�ṹ��
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