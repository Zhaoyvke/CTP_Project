#ifndef FILEDEAL_H
#define FILEDEAL_H
#pragma once
#include<string>
#include<vector>
#include<io.h>
#include<mutex>
#include<Windows.h>
#include<iostream>
#include"StringOpera.h"
using namespace std;
/*
 将tick转为tickk和
*/
class FileDeal
{
public:
	FileDeal();

	//按照文件路径创建文件
	bool Craetefolder(char * pszDir);
	//获取文件夹下所有文件路径文件路径
	void GetFilesAll(string path, vector<string>& foldername);
	//将一个文件移动到另一个文件路径下去 专门将新生成的某些天的csv拷贝到备份文件夹中的
	void CopyFileToAnother(string oldfilepath,string newfilepath);
	//判断文件路径是存在
	bool JudgeFilepathIsExit(const string & strpath);

	~FileDeal();

private:
	mutex create_mutex;
};
#endif // !FILEDEAL_H

