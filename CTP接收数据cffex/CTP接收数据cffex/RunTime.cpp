#include "RunTime.h"


void RunTime::StartTiming()
{
		count++;
		if (count > 1000) {
			count = 1;
		}
		start = clock(); //开始计时 其实就是毫秒数
		isStart = true;
}

void RunTime::EndTiming()
{
	if (isStart) { //如果已经开始
		finish = clock();  //结束计时 其实也是毫秒数
		isStart = false;
		this->PrintRunTime(); //打印
	}

	
}

void RunTime::PrintRunTime()
{
	char run[500];
	sprintf_s(run, "Thread running--%d--%d\n", count, finish-start);
	OutputDebugStringA(run);
}

RunTime::~RunTime()
{
}
