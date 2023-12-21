#pragma once
#include<map>
#include<vector>
#include<string>
#include <windows.h>
using namespace std;
/*该类用于初始化品种特殊时间段*/
class DealSpicalTime
{
public:
	DealSpicalTime();
	 
	//判断时间段是否在map 脏数据时间段中
	bool FindisinDirty(string pre,string time);
	//判断时间是否在map特殊时间段中
	bool FindisinSpical(string pre,string time,string &Spicaltime);

	//判断时间是否属于闭市时间
	bool FindisinClose(string pre,string time,string &Closetime);

	//判断本地时间和周期时间是否相等
	bool JudgeLocatimeAndupdateTimeisEqual(char *updateTime);
	~DealSpicalTime();
	
	map<string, map<string,string>> Dirty_time;  //每个品种的脏数据时间段 //map<rb,map<23:00,23.30>>
	map<string, map<string, string>>  Spical_time;//每个品种的特殊时间段

	map<string, vector<string>>Close_time;  //每个品种的闭市时间段
	
};

