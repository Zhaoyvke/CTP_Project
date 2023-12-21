#pragma once

//enum  Period
//{
//	ONEMIN, THREEMIN, FIVEMIN, FIFTEENMIN, THIRTMIN, SIXTYMIN, DAY
//};
const int PTNUM = 7;
struct CTPtick
{
	///tickʱ��
	char local[35];
	///������
	char TradingDay[12];
	///��Լ����
	char InstrumentID [31];
	///����������
	char ExchangeID[9];
	///��Լ�ڽ������Ĵ���
	char ExchangeInstID[31];
	///���¼�
	double	LastPrice;
	///�ϴν����
	double	PreSettlementPrice;
	///������
	double	PreClosePrice;
	///��ֲ���
	double	PreOpenInterest;
	///����
	double	OpenPrice;
	///��߼�
	double	HighestPrice;
	///��ͼ�
	double	LowestPrice;
	///����
	int	Volume;
	///�ɽ����
	double	Turnover;
	///�ֲ���
	double	OpenInterest;
	///������
	double	ClosePrice;
	///���ν����
	double	SettlementPrice;
	///��ͣ���
	double	UpperLimitPrice;
	///��ͣ���
	double	LowerLimitPrice;
	///����ʵ��
	double	PreDelta;
	///����ʵ��
	double	CurrDelta;
	
	///�����һ
	double	BidPrice1;
	///������һ
	int	BidVolume1;
	///������һ
	double	AskPrice1;
	///������һ
	int	AskVolume1;
	///����۶�
	double	BidPrice2;
	///��������
	int	BidVolume2;
	///�����۶�
	double	AskPrice2;
	///��������
	int	AskVolume2;
	///�������
	double	BidPrice3;
	///��������
	int BidVolume3;
	///��������
	double	AskPrice3;
	///��������
	int	AskVolume3;
	///�������
	double	BidPrice4;
	///��������
	int	BidVolume4;
	///��������
	double	AskPrice4;
	///��������
	int	AskVolume4;
	///�������
	double	BidPrice5;
	///��������
	int	BidVolume5;
	///��������
	double	AskPrice5;
	///��������
	int	AskVolume5;
	///���վ���
	double	AveragePrice;

};

//struct  Tick
//{
//	char instumentId[30]; 
//	char tradeDay[35];
//	char updateTime[35];
//	double lastprice;
//	double openprice;
//	double highprice;
//	double lowprice;
//	int volume;
//	double totalvolume;
//	double openInterest;
//	char local[35];
//	double weibi;
//};
////K�߽ṹ��
//struct  Kline
//{
//	char instumentId[30];
//	char type[5];
//	int sequence;
//	char tradeDay[35];
//	char updateTime[35];
//	double totalvolume;
//	double openInterest;
//	double closeprice;
//	int volume;
//	double openprice;
//	double highprice;
//	double lowprice;
//	int klineType;
//};
//
////tickK�߽ṹ��
//struct TickKline :public Kline
//{
//	long long id;
//	char local[35];
//	double weibi; //ί��
//};
