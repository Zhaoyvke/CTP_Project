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
//接收CTP数据,相关数据库操作
class CTPDBoperator
{
public:
	CTPDBoperator(string dbname,string tablepre);
	///将CTP格式的数据类型存入数据库
	void InsertToTickTable(CTPtick ctptick,string tablename);
	
	void Producttablename(); //生成表名
	bool Cretetable();  //创建表
	void  InitCon();     //初始化连接
	~CTPDBoperator();
private:

	string pre;      //合约码
	string tickdbname;  //数据库名称
	MYSQL tickcon;     //tick  数据库连接
	vector<string> tablenames; // tick表名

};

