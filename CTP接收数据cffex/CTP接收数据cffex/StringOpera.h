#ifndef STRINGOPERA_H
#define STRINGOPERA_H
#pragma once
#include<string>
#include<vector>
using namespace std;
class StringOpera
{
public:
	StringOpera();

	~StringOpera();
	static void SplitString(const std::string & s, std::vector<std::string>& v, const std::string & c);
	static void ReplaceAll(string & s, const string & src, const std::string & desc);
	//格式化日期字符串 为 yyyy/mm/dd hh:mm:ss.f的形式
	static string DeleteNotNum(string src);
	//找到第一个数字字符的下标
	static int FindFirstChar(string & temp);
};
#endif // !STRINGOPER
