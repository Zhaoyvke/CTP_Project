#pragma once
#include <string>
#include <vector>
#include <map>
#include "klineStruct.h"
#include "IndexStruct.h"
#include "dif2price.h"
#include "../include/mysql.h"
#include <iostream>
#include <mutex>
#define   LOCALHOST   "localhost"
#define   USER        "root"
#define   SQLPASSWORD "root"

using namespace std;
//����CTP����,������ݿ����
class CTPDBoperator
{
public:
	CTPDBoperator(string dbname,string tablepre);
	~CTPDBoperator();

	void  tickkinsertDB(TickKline & tickk);  //��tickk ���ݲ��뵽���ݿ�
	void  klineinsertDB(TickKline & kline);  //��kline ���ݲ��뵽���ݿ�
	void  updateKlineDB(TickKline & kline); //����kline���ݿ� /******
	string getTablenameBytype(string type);
	//�����ݿ������ȡ���µ���������K�ߵ���Ϣ ����ʼ��lasttickklines ���������ɽ����������ߡ��͡���
	void GetLastTickKline(vector<TickKline> &lasttickklines);
  
	/*========�ͼ���tickָ����ص����ݿ����=========*/
	//string GetTablenameBypt(PeriodType pt)
	void GetKlinesBeforeId(Period pt, int id, int n, vector<IndexKLine>& ks, vector<double>& ks_close);

	void GetKlinesBeforeUpdateTime(Period pt, string updateTime, int n, vector<IndexKLine>& ks, vector<double>& ks_close);

	//ȡ��ǰ���ݿ�����tick������
	int GetLastTick(subtick &sub_tick);
	//����id��ȡK��
	void GetKlineById(Period pt, int id, IndexKLine &k);
	//��ȡ��ǰtickk
	void GetCurrenttickkById(Period pt, int id,TickKline &currenttick);
	//��ȡ��ǰdaytick �Ŀ��ߵ���
	void GetDayData(Period pt, int id,Kline &daykline);

	void  InitCon();     //��ʼ�����ݿ�����
	void  CloseCon();     //�Ͽ������ݵ�����

public:


private:	
	void Producttablename(); //���ɱ���
	bool Cretetable();  //������
	

private:

	mutex kline_mutex;
	mutex tickk_mutex;
	string pre;      //��Լ��
	string klinedbname;  //���ݿ�����
	MYSQL klinecon;   //K�����ݿ����� 
	MYSQL tickcon;     //tick  ���ݿ�����
	vector<string> tablenames; // k�߱���

	
	//vector<TickKline> lasttickklines; //�������ڵ���һ��K��
};

