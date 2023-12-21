#pragma once
#include <string>
#include <vector>
#include <map>
#include "Struct.h"
#include "../include/mysql.h"
#include <iostream>
#include "WriteLog.h"
#include <mutex>
#define   LOCALHOST   "localhost"
#define   USER        "root"
#define   SQLPASSWORD  "9L$!PYWb" //"I5sP9gGN" 

using namespace std;
//����CTP����,������ݿ����
class CTPDBoperator
{
public:
	CTPDBoperator(string dbname,string tablepre);
	///��CTP��ʽ���������ʹ������ݿ�
	void InsertToTickTable(CTPtick ctptick,string tablename);
	
	void Producttablename(); //���ɱ���
	bool Cretetable();  //������
	void  InitCon();     //��ʼ������
	~CTPDBoperator();
private:

	string pre;      //��Լ��
	string tickdbname;  //���ݿ�����
	MYSQL tickcon;     //tick  ���ݿ�����
	vector<string> tablenames; // tick����

};

