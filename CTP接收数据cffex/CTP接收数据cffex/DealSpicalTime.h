#pragma once
#include<map>
#include<vector>
#include<string>
#include <windows.h>
using namespace std;
/*�������ڳ�ʼ��Ʒ������ʱ���*/
class DealSpicalTime
{
public:
	DealSpicalTime();
	 
	//�ж�ʱ����Ƿ���map ������ʱ�����
	bool FindisinDirty(string pre,string time);
	//�ж�ʱ���Ƿ���map����ʱ�����
	bool FindisinSpical(string pre,string time,string &Spicaltime);

	//�ж�ʱ���Ƿ����ڱ���ʱ��
	bool FindisinClose(string pre,string time,string &Closetime);

	//�жϱ���ʱ�������ʱ���Ƿ����
	bool JudgeLocatimeAndupdateTimeisEqual(char *updateTime);
	~DealSpicalTime();
	
	map<string, map<string,string>> Dirty_time;  //ÿ��Ʒ�ֵ�������ʱ��� //map<rb,map<23:00,23.30>>
	map<string, map<string, string>>  Spical_time;//ÿ��Ʒ�ֵ�����ʱ���

	map<string, vector<string>>Close_time;  //ÿ��Ʒ�ֵı���ʱ���
	
};

