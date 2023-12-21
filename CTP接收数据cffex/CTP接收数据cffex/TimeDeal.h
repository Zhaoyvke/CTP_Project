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
	//type 0�������������� 1�������������� ʱ�� 2�������������� ʱ����
	void  StringToTime(char *date, int type, tm &desc_tm);

	//��������ת��   current_type ����ǰʱ����ʲô���� 0���������� 1���������� ʱ�� 2���������� ʱ����   dsc_type������Ҫת������������
	void  DateLengthConvert(char *date, char *afterdate, int befor_type, int after_type);

	//��ĳ��ʱ���ַ������мӼ��������ַ��� ,type 0�������������� 1�������������� ʱ�� 2�������������� ʱ����
	void  char_AddTime(char *date,char *desc_date, int addSec, int type);

	//��ĳ��ʱ���ַ������мӼ�������tm�ṹ�� type 0�������������� 1�������������� ʱ�� 2�������������� ʱ����
	void  tm_AddTime(char *date, int addSec, int type,tm &t);

	//�ж����ܼ�
	int  GetDayOfWeek(char *date);

	//��ȡ��ǰʱ���ʱ�����ϵ���һʱ��
	void  GetFirstModay(char *date,char *desc_date);

	//����һ��ʱ�䷵��һ������ �ֱ���5���ӵģ�3���ӵģ�30���ӵĵķ�������
	int  ModMinute(char *date,int minute,char *desc_date);

	int  FridaySeek(char* date, int num, vector<string> &s);

	//��ȡ��ǰstringʱ��
	string GetCurrentTimeString();

	 ~TimeDeal();

};

#endif