#pragma once

/*该类用来写日志对程序动态进行记录*/
#include <string>
using namespace std;
class WriteLog
{
public:
	WriteLog();

	static void writeloginfo(string content);
	~WriteLog();
};

