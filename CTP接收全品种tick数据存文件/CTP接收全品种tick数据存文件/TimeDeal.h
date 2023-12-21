#ifndef TIMEDEAL_H_
#define TIMEDEAL_H_

#pragma once

#include<iostream>
#include<ctime>
#include<vector>
#include<string.h>

using namespace std;
class TimeDeal
{
public:
	 TimeDeal();
	//type 0代表传的是年月日 1代表传的是年月日 时分 2代表传的是年月日 时分秒
	void  StringToTime(char *date, int type, tm &desc_tm);

	//进行日期转换   current_type 代表当前时间是什么类型 0代表年月日 1代表年月日 时分 2代表年月日 时分秒   dsc_type代表想要转换的日期类型
	void  DateLengthConvert(char *date, char *afterdate, int befor_type, int after_type);

	//对某个时间字符串进行加减，返回字符串 ,type 0代表传的是年月日 1代表传的是年月日 时分 2代表传的是年月日 时分秒
	void  char_AddTime(char *date,char *desc_date, int addSec, int type);

	//对某个时间字符串进行加减，返回tm结构体 type 0代表传的是年月日 1代表传的是年月日 时分 2代表传的是年月日 时分秒
	void  tm_AddTime(char *date, int addSec, int type,tm &t);

	//判断是周几
	int  GetDayOfWeek(char *date);

	//获取当前时间的时间轴上的周一时间
	void  GetFirstModay(char *date,char *desc_date);

	//给定一个时间返回一个余数 分别是5分钟的，3分钟的，30分钟的的分钟余数
	int  ModMinute(char *date,int minute,char *desc_date);

	int  FridaySeek(char* date, int num, vector<string> &s);

	//获取当前string时间
	string GetCurrentTimeString();

	 ~TimeDeal();

};

#endif