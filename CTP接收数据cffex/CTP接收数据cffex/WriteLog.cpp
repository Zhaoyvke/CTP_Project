#include "WriteLog.h"
#include <time.h>
#include  <fstream>

WriteLog::WriteLog()
{
}

//内容写入日志文件
void WriteLog::writeloginfo(string content)
{
	time_t local = time(NULL);
	struct tm* slocaltime = localtime(&local);  //转换时间格式
	char CurrentTime[32];
	sprintf(CurrentTime, "%04d/%02d/%02d %02d:%02d:%02d", 1900 + slocaltime->tm_year, 1 + slocaltime->tm_mon, slocaltime->tm_mday,slocaltime->tm_hour,slocaltime->tm_min,slocaltime->tm_sec);
	
	string  filepath="../Programlog.txt";
	fstream writefile;
	writefile.open(filepath.c_str(),ios::out|ios::app);
	if (writefile.is_open()==true)
	{
		writefile << CurrentTime <<"	"<< content << endl;
	}
	writefile.close();
}

WriteLog::~WriteLog()
{
}
