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
	virtual void StartTiming(); //开始计时
	virtual void EndTiming();   //结束计时
	
	virtual void PrintRunTime();  //在输出窗口打印运行时间

	virtual ~RunTime();   
protected:
	clock_t start = 0L , finish = 0L;
	bool isStart; //判断是否有开始计时
	unsigned short count;  //用于已经重复计时 也就是 start和end多少次了 没1000次重新计数
};


#endif // !RUNTIME_H


