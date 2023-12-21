#ifndef RUNTIME_H
#define RUNTIME_H
#pragma once

#include<thread>
#include<Windows.h>

using namespace std;
class RunTime
{
public:
	RunTime() { isStart = false; count = 0; };
	virtual void StartTiming(); //��ʼ��ʱ
	virtual void EndTiming();   //������ʱ
	
	virtual void PrintRunTime();  //��������ڴ�ӡ����ʱ��

	virtual ~RunTime();   
protected:
	clock_t start = 0L , finish = 0L;
	bool isStart; //�ж��Ƿ��п�ʼ��ʱ
	unsigned short count;  //�����Ѿ��ظ���ʱ Ҳ���� start��end���ٴ��� û1000�����¼���
};


#endif // !RUNTIME_H


