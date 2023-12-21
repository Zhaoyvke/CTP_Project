#include "FileDeal.h"
#include<direct.h>
#define ACCESS _access 
#define MKDIR(a) _mkdir((a)) 
void FileDeal::GetFilesAll(string path, vector<string>& foldername)
{//�ļ����     
	long  hFile = 0;
	//�ļ���Ϣ
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

	//��ĩβ��/ 
	if (pszDir[iLen - 1] != '\\' && pszDir[iLen - 1] != '/')
	{
		pszDir[iLen] = '/';
		pszDir[iLen + 1] = '\0';
	}

	// ����Ŀ¼ 
	for (i = 0; i <= iLen; i++)
	{
		if (pszDir[i] == '\\' || pszDir[i] == '/')
		{
			pszDir[i] = '\0';

			//���������,���� 
			iRet = ACCESS(pszDir, 0);
			if (iRet != 0)
			{
				iRet = MKDIR(pszDir);
				if (iRet != 0)
				{
					return false;
				}
			}
			//֧��linux,������\����/ 
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
		cout << "Ŀ���ļ��� ������Data��β�� ����" << endl;
		system("pause");
		exit(0);
	}
	if (srcpath.find("Data2") != srcpath.length() - 5) {
		cout << "Դ�ļ��� ������Data2��β�� ����" << endl;
		system("pause");
		exit(0);
	}
	vector<string> files;
	this->GetFilesAll(srcpath,files);
	if (files.empty()) {
		cout << "�ļ���Ϊ��" << endl;
		return;
	}
	cout << "�㽫Ҫ�滻�ı����� ���飺    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
	for (int i = 0; i <files.size();i++) {
		cout << files[i] << endl;
	}
	cout << "�����Ƿ�Ҫ��ȻҪ�滻!!!!!!!!!!!!!!!!!!!!!!(y/n)" << endl;
	char c;
	cin >> c;
	if (c!='y') {
		cout << "���򼴽��ս�" << endl;
		system("pause");
		exit(0);
	}
	int pos = files[0].find("Data2")+5;
	for (int i = 0; i < files.size(); i++) {
		string filename= descpath+files[i].substr(pos);
		if (_access(filename.c_str(),0)!=-1) {
			if (remove(filename.c_str())==0) {
				cout << filename << "�ļ�ɾ���ɹ�" << endl;
			}
			else 
			{
				cout << filename << "�ļ�ɾ��ʧ��" << endl;
			}
		}
		if (CopyFile(files[i].c_str(), filename.c_str(), true)) {
			cout << files[i] << "�����ɹ�" << endl;
		}
		else {
			cout << files[i] << "����ʧ��" << endl;
		}
		
	}
	
}
bool FileDeal::JudgeFilepathIsExit(const string &strpath)
{

	bool ResVal = false;
	WIN32_FIND_DATA  findfileData;

	HANDLE hfind = FindFirstFile(strpath.c_str(), &findfileData);

	//&&(findfileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) //��������ж�Ŀ¼�����Ƿ���� Ҫ������仰

	if (hfind != INVALID_HANDLE_VALUE)
	{
		ResVal = true;    //���ڷ���true
	}

	FindClose(hfind);
	return ResVal;
}
FileDeal::~FileDeal()
{
}