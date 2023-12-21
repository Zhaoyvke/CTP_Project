#include "CCustomTraderSpi.h"
//#include "WriteLog.h"
#include <iostream>
#include <mutex>
#include <vector>
#include <string>
#include <map>
#include "WriteLog.h"
using namespace std;
extern CThostFtdcTraderApi *TraderApi;
extern vector<string> Ins; //存放合约代码的容器
extern map<string, string> m_instrument2Exchange;//存放合约和交易所之间的映射
extern volatile int singalnum; //全局变量用于进程间的通信
extern mutex pInstrument_Mutex;//订阅行情合约代码锁
extern char targetpath[]; //文件存储位置
unique_lock<std::mutex> lock;
CCustomTraderSpi::CCustomTraderSpi()
{

}


CCustomTraderSpi::~CCustomTraderSpi()
{

}
void CCustomTraderSpi::OnFrontConnected()
{
	std::cout << "=====建立网络连接成功=====" << std::endl;
	WriteLog::writeloginfo("==建立网络连接成功==trader");  //
	if (singalnum==0) //值为零
	{
		ReqAuthenticate();//请求客户端认证
	}
		
}
void CCustomTraderSpi::ReqAuthenticate()
{
	CThostFtdcReqAuthenticateField auth;
	memset(&auth, 0, sizeof(auth));
	strcpy(auth.BrokerID, BROKER_ID);
	strcpy(auth.UserID, USER_ID);
	strcpy(auth.AuthCode, AUTHCODE); //认证码
	strcpy(auth.AppID, APPID); //appid
	static int requestID = 0; // 请求编号
	int result = TraderApi->ReqAuthenticate(&auth, ++requestID);
	if (!result)
	{
		std::cout << ">>>发送客户端认证响应成功" << std::endl;
		WriteLog::writeloginfo(">>>发送客户端认证响应成功");  //
	}
	else
	{
		std::cout << ">>>发送客户端认证响应失败" << std::endl;
		WriteLog::writeloginfo(">>>发送客户端认证响应成功");  //
	}
		
}
void CCustomTraderSpi::reqUserLogin()
{
	CThostFtdcReqUserLoginField loginreq;
	memset(&loginreq, 0, sizeof(loginreq));
	strcpy(loginreq.BrokerID, BROKER_ID);
	strcpy(loginreq.UserID, USER_ID);
	strcpy(loginreq.Password, PASSWORD);
	static int requestID = 0; // 请求编号
	int  rt = TraderApi->ReqUserLogin(&loginreq, requestID);
	if (!rt)
		std::cout << ">>>>>>发送交易登录请求成功" << std::endl;
	else
		std::cerr << "--->>>发送交易登录请求失败" << std::endl;
}
void CCustomTraderSpi::OnRspAuthenticate(CThostFtdcRspAuthenticateField * pRspAuthenticateField, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
	if (isErrorRspInfo(pRspInfo))
	{
		if (bIsLast == true)
		{
			std::cout << "====客户端响应成功====" << std::endl;
			std::cout << pRspAuthenticateField->BrokerID << std::endl;

			std::cout << pRspAuthenticateField->UserID << std::endl;
			reqUserLogin();
		}
	}
	else
	{
		std::cout << pRspInfo->ErrorID << std::endl;
		std::cout << pRspInfo->ErrorMsg << std::endl;
		exit(1);
	}
}
void CCustomTraderSpi::OnRspUserLogin(CThostFtdcRspUserLoginField * pRspUserLogin, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		std::cout << "=====交易账户登录成功=====" << std::endl;
		std::cout << "交易日： " << pRspUserLogin->TradingDay << std::endl;
		std::cout << "登录时间： " << pRspUserLogin->LoginTime << std::endl;
		std::cout << "经纪商： " << pRspUserLogin->BrokerID << std::endl;
		std::cout << "帐户名： " << pRspUserLogin->UserID << std::endl;
		WriteLog::writeloginfo("==交易账户登录成功==trader");  //
		// 开始查询合约
		CThostFtdcQryInstrumentField *pQryInstrument =new CThostFtdcQryInstrumentField();
		strcpy(pQryInstrument->ExchangeID,"");
		int rt = TraderApi->ReqQryInstrument(pQryInstrument, 0);
		if (!rt)
		{
			std::cout << ">>>>>>发送查询合约请求成功" << std::endl;
			
		}
			
		else
			std::cerr << "--->>>发送查询合约请求失败" << std::endl;
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}
void CCustomTraderSpi::OnRspError(CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}
void CCustomTraderSpi::OnFrontDisconnected(int nReason)
{
	std::cerr << "=====网络连接断开=====" << std::endl;
	std::cerr << "错误码： " << nReason << std::endl;
	WriteLog::writeloginfo("===网络连接断开===Trader");  //写入监控程序日志中
}

void CCustomTraderSpi::OnRspQryInstrument(CThostFtdcInstrumentField * pInstrument, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
	if (pInstrument->ProductClass =='1') //产品类型='1'为期货
	{
		std::cout << "交易所代码" << pInstrument->ExchangeID << std::endl;
		std::cout << "合约代码" << pInstrument->InstrumentID << std::endl;
		//std::cout << "当前是否交易" << pInstrument->IsTrading << std::endl;
		Ins.push_back(pInstrument->InstrumentID);

		m_instrument2Exchange.insert(make_pair(pInstrument->InstrumentID, string(pInstrument->ExchangeID))); //建立合约代码和交易所之间的关系映射
		//cout << Ins.size() << endl;
	}
	if (bIsLast == true)
	{
		singalnum = 1; //合约读取完成时设置全局变量为1;
	}
	
	
}

bool CCustomTraderSpi::isErrorRspInfo(CThostFtdcRspInfoField * pRspInfo)
{
	bool result = (pRspInfo != nullptr) && (pRspInfo->ErrorID == 0);
	return result;
}

