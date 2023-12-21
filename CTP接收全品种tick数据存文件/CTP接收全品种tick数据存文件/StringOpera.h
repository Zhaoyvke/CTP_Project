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
	//��ʽ�������ַ��� Ϊ yyyy/mm/dd hh:mm:ss.f����ʽ
	static string DeleteNotNum(string src);
	//�ҵ���һ�������ַ����±�
	static int FindFirstChar(string & temp);
};
#endif // !STRINGOPER
