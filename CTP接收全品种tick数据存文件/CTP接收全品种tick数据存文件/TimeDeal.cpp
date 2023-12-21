#include "TimeDeal.h"
#include<iostream>
#include<windows.h>

TimeDeal::TimeDeal()
{
}
//将字符串转为tm格式
void TimeDeal::StringToTime(char *date, int type,tm &desc_tm) 
{
	if (type == 0) {
		sscanf_s(date, "%4d/%2d/%2d ", &desc_tm.tm_year, &desc_tm.tm_mon, &desc_tm.tm_mday);
		desc_tm.tm_hour = 0;
		desc_tm.tm_min = 0;
		desc_tm.tm_sec = 0;
	}
	else if (type == 1) {
		sscanf_s(date, "%4d/%2d/%2d %d:%d", &desc_tm.tm_year, &desc_tm.tm_mon, &desc_tm.tm_mday, &desc_tm.tm_hour, &desc_tm.tm_min);
		desc_tm.tm_sec = 0;
	}
	else if (type==2) {
		sscanf(date, "%4d/%2d/%2d %d:%d:%d", &desc_tm.tm_year, &desc_tm.tm_mon, &desc_tm.tm_mday, &desc_tm.tm_hour, &desc_tm.tm_min,&desc_tm.tm_sec);
	}
	desc_tm.tm_year -= 1900;
	desc_tm.tm_mon -= 1;
	
}


void TimeDeal::DateLengthConvert(char *date,char *afterdate,int befor_type, int after_type) {

	string s = date;
	if (befor_type==0) {
		switch (after_type)
		{
		case 0:strcpy(afterdate, s.c_str()); break;
		case 1:s += " 00:00"; strcpy(afterdate, s.c_str()); break;
		case 2:s += " 00:00:00"; strcpy(afterdate, s.c_str()); break;
		default:
			break;
		}
	}
	else if (befor_type==1) {
		switch (after_type)
		{
		case 0:strcpy(afterdate, s.substr(0, 10).c_str()); break;
		case 1:strcpy(afterdate, s.c_str()); break;
		case 2:s += ":00"; strcpy(afterdate, s.c_str()); break;
		default:
			break;
		}
	}
	else if(befor_type==2){
		switch (after_type)
		{
		case 0:strcpy(afterdate, s.substr(0, 10).c_str()); break;
		case 1:strcpy(afterdate, s.substr(0, 16).c_str()); break;
		case 2:strcpy(afterdate, s.c_str()); break;
		default:
			break;
		}
	}

}




void TimeDeal::char_AddTime(char * date, char *desc_date, int addSec, int type)
{
	tm t;
	StringToTime(date, type,t);
	time_t t1 = mktime(&t);
	time_t t2 = t1 +addSec + 8 * 3600;
	tm *tt = gmtime(&t2);
	if (type == 0) {
		sprintf(desc_date, "%d/%02d/%02d", tt->tm_year + 1900, tt->tm_mon + 1, tt->tm_mday);
	}
	else if (type == 1) {
		sprintf(desc_date, "%d/%02d/%02d %02d:%02d", tt->tm_year + 1900, tt->tm_mon + 1, tt->tm_mday, tt->tm_hour, tt->tm_min);
	}else if (type==2) {
		sprintf(desc_date, "%d/%02d/%02d %02d:%02d:%02d", tt->tm_year + 1900, tt->tm_mon + 1, tt->tm_mday, tt->tm_hour, tt->tm_min,tt->tm_sec);
	}
}

void TimeDeal::tm_AddTime(char * date, int addSec, int type,tm &desc_tm)
{
	tm t;
	StringToTime(date, type,t);
	time_t t1 = mktime(&t);
	time_t t2 = t1 + addSec + 8 * 3600;
	desc_tm = *(gmtime(&t2));
}
int TimeDeal::GetDayOfWeek(char * date)
{
	tm t;
	StringToTime(date, 0, t);
	time_t t1 = mktime(&t);
	time_t t2 = t1  + 8 * 3600;
	tm *desc_tm = gmtime(&t2);
	if (desc_tm->tm_wday == 0) {
		desc_tm->tm_wday = 7;
	}
	return desc_tm->tm_wday;
}

void TimeDeal::GetFirstModay(char * date,char *descdate)
{
	if (GetDayOfWeek(date) == 1) {
		descdate = date;
	}
	int n = 1;
	while (true) {
		tm t;
		tm_AddTime(date, -n * 24 * 60 * 60, 0,t);
		if (t.tm_wday == 1) {
			time_t m = mktime(&t);
			m += 8 * 3600;
			t = *(gmtime(&m));
			sprintf(descdate, "%4d/%02d/%02d", t.tm_year + 1900, t.tm_mon + 1, t.tm_mday);
		}
		n++;
	}
}

int TimeDeal::ModMinute(char * date, int minute,char *desc_date)
{
	tm t;
	StringToTime(date,1,t);
	int mod = t.tm_min%minute;
	char_AddTime(date,desc_date,-mod*60,1);
	return mod;
}

// 某天之前的n个周五(含某天） 排列近--远

int TimeDeal::FridaySeek(char* date, int num, vector<string> &s)
{
	int noweek;
	string date1 = date;
	s.push_back(date1);
	noweek = GetDayOfWeek(date);
	for (int i = 0; i <= num; i++)
	{
		char fday0[20];
		char_AddTime(date, fday0,-(noweek + 2 + 7 * i)*24*60*60, 0);
		string fday = fday0;
		s.push_back(fday0);
	}
	return 0;
}

//获取当前string时间
string TimeDeal::GetCurrentTimeString()
{
	char time[30];
	SYSTEMTIME exe_time;
	GetLocalTime(&exe_time);
	sprintf_s(time, "%d/%02d/%02d %02d:%02d:%02d:%03d", exe_time.wYear, exe_time.wMonth, exe_time.wDay, exe_time.wHour, exe_time.wMinute, exe_time.wSecond, exe_time.wMilliseconds);
	string time1 = time;
	return time1;
}

TimeDeal::~TimeDeal()
{
}
