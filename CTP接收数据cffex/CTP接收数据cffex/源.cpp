#include "CCustomMdSpi.h"
#include "CCustomTraderSpi.h"
#include "DealSpicalTime.h"
#include <iostream>
#include <vector>
#include <map>
using namespace std;
// 链接库
#pragma comment (lib, "thostmduserapi_se.lib") //加载CTP动态库
#pragma comment (lib, "thosttraderapi_se.lib")
#pragma comment (lib,"libmysql.lib")    //加载数据库动态库
/*==========================全局变量=======================*/
//交易参数
CThostFtdcTraderApi *TraderApi;
//行情参数
CThostFtdcMdApi *mdApi;
// 行情合约代码列表
char *pInstrumentID[100] = {};// 行情合约代码列表，中、上、大、郑交易所各选一种

// 行情合约订阅数量
int instrumentNum = 0;
//文件路径
char filePath[100] = { '\0' };
//行情交易前置地址
char mdfront_addr[] = MDFRONT_ADDR;
//交易前置地址
char traderfront[] = TRADERFRONT_ADDR;

//特殊时间处理类
DealSpicalTime  dealspicaltime;

vector<string> Ins = {
	/*金融交易所  品种名需要大写*/
	"IF2212","IF2205","IF2206","IF2209",
};

map<string, string> m_instrument2dbname;
int main()
{
	//step1 初始化合约码
	instrumentNum = Ins.size();  //行情合约订阅数量
	for (int i = 0; i < Ins.size(); i++) {
		char * InsCell = (char*)Ins[i].c_str();
		pInstrumentID[i] = InsCell;
	}
	//m_instrument2dbname.insert(make_pair("rb","shfe"));  //rb品种对应的数据库为螺纹钢
	m_instrument2dbname.insert(make_pair("IF", "cffex"));  //IF品种对应的数据库为沪深300
	m_instrument2dbname.insert(make_pair("IC", "cffex"));  //IF品种对应的数据库为沪深300
	m_instrument2dbname.insert(make_pair("IH", "cffex"));  //IF品种对应的数据库为沪深300

	//step2 初始化文件保存路径
	strcpy(filePath, "../AllData/");  //为保存文件的路径赋值								  
	 //初始化行情线程
	cout << "初始化行情..." << endl;
	mdApi = CThostFtdcMdApi::CreateFtdcMdApi();   // 创建行情实例
	CThostFtdcMdSpi *pMdUserSpi = new CCustomMdSpi;  // 创建行情回调实例
	mdApi->RegisterSpi(pMdUserSpi);               // 注册事件类
	mdApi->RegisterFront(mdfront_addr);           // 设置行情前置地址
	
	mdApi->Init();                                // 连接运行
	mdApi->Join();
	delete pMdUserSpi;
	mdApi->Release();

	system("pause");
	return 0;
}