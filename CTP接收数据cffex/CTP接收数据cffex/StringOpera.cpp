#include "StringOpera.h"



StringOpera::StringOpera()
{
}


StringOpera::~StringOpera()
{
}
void StringOpera::SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c)
{
	std::string::size_type pos1, pos2;
	pos2 = s.find(c);   /****/
	pos1 = 0;
	while (std::string::npos != pos2)//说明查找没有匹配
	{
		v.push_back(s.substr(pos1, pos2 - pos1));//获得字符串s中从第pos1位开始的长度为pos2 - pos1的字符串

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}

void StringOpera::ReplaceAll(string &s, const string &src, const std::string& desc) {
	std::string::size_type pos;
	pos = s.find(src);
	while (std::string::npos != pos)
	{
		s.replace(pos, 1, desc);
		pos = s.find(src);
	}
}
string StringOpera::DeleteNotNum(string src)
{
	char s[100];
	if (FindFirstChar(src)==-1) {
		int year, month, day;
		sscanf(src.c_str(),"%04d%02d%02d",&year,&month,&day);
		sprintf_s(s, "%04d/%02d/%02d", year, month, day); 
		return s;
	}
	int i = 0;
	for (; i < src.size(); i++) {
		if (src[i] >= '0'&&src[i] <= '9') {
			s[i] = src[i];
		}
		else {
			s[i] = '#';
		}
	}
	s[i] = '\0';
	vector<string> res;
	SplitString(s,res,"#");
	string temp;
	int j = 0;
	for (int k = 0; k < res.size();k++,j++) {
		if (res[k].size() % 2 != 0) {
			res[k] = "0" + res[k];
		}
		if (j<2) {
			temp += res[k] + "/";
		}
		else if(j==2){
			temp += res[k] + " ";
		}
		else if (j>2 && j< res.size()-1) {
			temp += res[k] + ":";
		}
		else if (j = res.size() - 1) {
			temp += res[k];
		}
	}
	return temp;
}
int StringOpera::FindFirstChar(string &temp) {
	for (int i = 0; i < temp.size(); i++) {
		if ((temp[i] >= '0' && temp[i] <= '9')) {
			return i;
		}
	}
	return -1;
}