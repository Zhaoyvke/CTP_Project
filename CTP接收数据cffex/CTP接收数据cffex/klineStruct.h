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
	double totalvolume;//����
	double openInterest;   //��ֲ�
	double PreOpenInterest;//��ֲ�
	double buyprice;//��һ��
	int buyqty; //��һ��
	double sellprice;//��һ��
	int sellqty;//��һ��
	char local[35];
};
//K�߽ṹ��
struct  Kline
{
	char instumentId[30];
	char type[5];
	int sequence;//����
	char tradeDay[35];
	char updateTime[35];
	double totalvolume;
	double openInterest;
	double closeprice;
	int    volume;
	double openprice;
	double highprice;
	double lowprice;
	int klineType; //1 ����  0 ����
};

//tickK�߽ṹ��
struct TickKline :public Kline
{
	long long id;
	char local[35];
	double weibi; //ί��
	int  addposition;//�̿���������
	double  kaicangvolume;//�̿����ݿ���
	double pingcangvolume;//�̿�����ƽ��
	char Dealtype[10];//�ɽ�����
	char  direction[2];//��������
	double buyprice;//��һ��
	int buyqty; //��һ��
	double sellprice;//��һ��
	int sellqty;//��һ��
};
