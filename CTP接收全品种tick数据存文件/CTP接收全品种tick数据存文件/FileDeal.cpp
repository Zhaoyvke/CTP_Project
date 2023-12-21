#include "FileDeal.h"
#include<direct.h>
#define ACCESS _access 
#define MKDIR(a) _mkdir((a)) 
void FileDeal::GetFilesAll(string path, vector<string>& foldername)
{//文件句柄     
	long  hFile = 0;
	//文件信息
	struct _finddata_t fileinfo;
	std::string p;
	if ((hFile = _findfirst(p.assign(path).append("\\\\*").c_str(), &fileinfo)) != -1)
	{
		do {
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					GetFilesAll(p.assign(path).append("\\\\").append(fileinfo.name), foldername);
				}
			}
			else
			{
				std::string folder = p.assign(path).append("\\\\").append(fileinfo.name);
				foldername.push_back(folder);
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}



bool FileDeal::Craetefolder(char* pszDir)
{
	unique_lock<mutex> lock(create_mutex);
	int i = 0;
	int iRet;
	int iLen = strlen(pszDir);

	//在末尾加/ 
	if (pszDir[iLen - 1] != '\\' && pszDir[iLen - 1] != '/')
	{
		pszDir[iLen] = '/';
		pszDir[iLen + 1] = '\0';
	}

	// 创建目录 
	for (i = 0; i <= iLen; i++)
	{
		if (pszDir[i] == '\\' || pszDir[i] == '/')
		{
			pszDir[i] = '\0';

			//如果不存在,创建 
			iRet = ACCESS(pszDir, 0);
			if (iRet != 0)
			{
				iRet = MKDIR(pszDir);
				if (iRet != 0)
				{
					return false;
				}
			}
			//支持linux,将所有\换成/ 
			pszDir[i] = '/';
		}
	}
	return true;

}


FileDeal::FileDeal()
{
}


void FileDeal::CopyFileToAnother(string srcpath, string descpath)
{
	if (descpath.find("Data")!= descpath.length()-4) {
		cout << "目标文件夹 不是以Data结尾的 请检查" << endl;
		system("pause");
		exit(0);
	}
	if (srcpath.find("Data2") != srcpath.length() - 5) {
		cout << "源文件夹 不是以Data2结尾的 请检查" << endl;
		system("pause");
		exit(0);
	}
	vector<string> files;
	this->GetFilesAll(srcpath,files);
	if (files.empty()) {
		cout << "文件夹为空" << endl;
		return;
	}
	cout << "你将要替换的表如下 请检查：    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
	for (int i = 0; i <files.size();i++) {
		cout << files[i] << endl;
	}
	cout << "检查后，是否要仍然要替换!!!!!!!!!!!!!!!!!!!!!!(y/n)" << endl;
	char c;
	cin >> c;
	if (c!='y') {
		cout << "程序即将终结" << endl;
		system("pause");
		exit(0);
	}
	int pos = files[0].find("Data2")+5;
	for (int i = 0; i < files.size(); i++) {
		string filename= descpath+files[i].substr(pos);
		if (_access(filename.c_str(),0)!=-1) {
			if (remove(filename.c_str())==0) {
				cout << filename << "文件删除成功" << endl;
			}
			else 
			{
				cout << filename << "文件删除失败" << endl;
			}
		}
		if (CopyFile(files[i].c_str(), filename.c_str(), true)) {
			cout << files[i] << "拷贝成功" << endl;
		}
		else {
			cout << files[i] << "拷贝失败" << endl;
		}
		
	}
	
}
bool FileDeal::JudgeFilepathIsExit(const string &strpath)
{

	bool ResVal = false;
	WIN32_FIND_DATA  findfileData;

	HANDLE hfind = FindFirstFile(strpath.c_str(), &findfileData);

	//&&(findfileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) //如果单单判断目录级别是否存在 要加上这句话

	if (hfind != INVALID_HANDLE_VALUE)
	{
		ResVal = true;    //存在返回true
	}

	FindClose(hfind);
	return ResVal;
}
FileDeal::~FileDeal()
{
}