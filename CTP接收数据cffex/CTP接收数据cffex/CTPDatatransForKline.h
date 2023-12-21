#pragma once
#include "CTPDBoperator.h"
#include "TimeDeal.h"
#include "KlineStruct.h"
#include <thread>
#include"DealSpicalTime.h"
#include "AnalysisBox.h"
#include "IndexStruct.h"
#include "RunTime.h"
#include "dif2price.h"
#include "Index_Base.h"
class CTPDatatransForKline
{
public:
	CTPDatatransForKline(string instrumentID);
	~CTPDatatransForKline();

	void CaltickkAndInsertDB(Tick *tick);//����K�߲��Ҵ������ݿ�
	
	void convertUpdateTime(string const& updatetime, string &descupdateTime, int pt);//pt����ת������ 1,3,5,30,30,60 24*60  �Է���Ϊ��λ
private:
	bool tickisUpdate(Tick *tick);  //�ж�tick�Ƿ���Ҫ����
	

	void updateXperiodkline(Tick *tick, int X, Period pt);  //tick �������� pt��������

	void Caltickkline(TickKline & nowtickkline, Tick *tick, string const &newupdateTime, Period pt);//********������k�߸��º��ֵ����
	//����K������
	int calKlineType(double open, double close, double lastclose);
	//k�߸�ֵ  �� srctickkline��ֵ��ֵ�� desctickkline
	void copyTickKline(TickKline &srctickkline, TickKline &desctickkline); 
	//��updateTime����������㿪����� type����������� �Է���Ϊ��λ 
	 int calDIffTimeMins(string const &updateTime, int Type);
	
	 
	  /*��ָ��������صĺ���*/
public:
	//ͨ��id ��ȡ��ǰtickk
	void ProductOneKind(int id, Period pt, CSVLine &csvl);
	//ͨ��id ��ȡ��ǰday �Ŀ��ߵ���
	void GetCurrenttickByid(int id, TickKline&currenttick);
	
	void GetCurrentDayData(int id,Kline &daykline);
	void StarConvert(int id);
	void SaveindexCsv(ofstream & fwrite, TickKline &Currenttickk, const CSVLine &csv_tick, const CSVLine & csv_1, const CSVLine & csv_3, const CSVLine & csv_5, const CSVLine & csv_15, const CSVLine & csv_30,Kline &daykline);
	
	//��������2�۲�ĺ���
	void Cal2difBaseprice(subtick sub_tick);

	void Save2difpriceCsv();
	void writelog(double baseprice,double tickprice,string baselocal,string ticklocal);//��¼������������tick��־
	void  writelocal(string local,double tickprice);
	//�ж�Kdj�Ƿ�Ϊ��ֵ
	//void JudgeKDjIsNan(const CSVLine &csv_tick, const CSVLine & csv_1, const CSVLine & csv_3, const CSVLine & csv_5, const CSVLine & csv_15, const CSVLine & csv_30);
	
	void KLineDataPicker(vector<IndexKLine> &K0, vector<double> &Kdata, string datatype);
private:
	CTPDBoperator *ctpOper;  //�����ݿ������صĶ���
	AnalysisBox  indexOper;  //����ָ��Ķ���
	string exchange;  //���ݿ�����
	string pre;      //Ʒ������
	string  indexcsvpre; //csv�ļ�������
	int lasttickkid;//��¼��һ��tick��id  ����ָ��ʱ���õ�
	vector<TickKline> lasttickklines; //�������ڵ���һ��tickk��
	vector<double>LastTickklinesClosePrices;//����������һ��K�ߵ����̼�

	kline2price current2pricekline;// ��ǰ����
	int num;//������¼�������ۼ��tick����
	string last3pricetradeday;
	string lastXpriceupdateTime_hour = ""; //��һ��tick��Ӧ������ʱ��� hour

	bool IsRestart;//�жϻ��۳����Ƿ�����¼���

	string endtime;//����ʱ���
	//string currentpriceupdateTime_hour; //��ǰtick��Ӧ����ʱ���  hour

	double difprice;//���
	Index_Base indl;

	double prebase1, prebase2;
	int isbase1, isbase2, y_type1, y_type2;
	int prehour, curhour;
	ofstream fday;
};

