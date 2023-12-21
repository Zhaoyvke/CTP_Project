#include "RunTime.h"


void RunTime::StartTiming()
{
		count++;
		if (count > 1000) {
			count = 1;
		}
		start = clock(); //��ʼ��ʱ ��ʵ���Ǻ�����
		isStart = true;
}

void RunTime::EndTiming()
{
	if (isStart) { //����Ѿ���ʼ
		finish = clock();  //������ʱ ��ʵҲ�Ǻ�����
		isStart = false;
		this->PrintRunTime(); //��ӡ
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
