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
 ��tickתΪtickk��
*/
class FileDeal
{
public:
	FileDeal();

	//�����ļ�·�������ļ�
	bool Craetefolder(char * pszDir);
	//��ȡ�ļ����������ļ�·���ļ�·��
	void GetFilesAll(string path, vector<string>& foldername);
	//��һ���ļ��ƶ�����һ���ļ�·����ȥ ר�Ž������ɵ�ĳЩ���csv�����������ļ����е�
	void CopyFileToAnother(string oldfilepath,string newfilepath);
	//�ж��ļ�·���Ǵ���
	bool JudgeFilepathIsExit(const string & strpath);

	~FileDeal();

private:
	mutex create_mutex;
};
#endif // !FILEDEAL_H

