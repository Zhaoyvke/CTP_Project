#include "CCustomTraderSpi.h"
//#include "WriteLog.h"
#include <iostream>

extern CThostFtdcTraderApi *TraderApi;
extern char *pInstrumentID[];
extern int instrumentNum;
CCustomTraderSpi::CCustomTraderSpi()
{
}


CCustomTraderSpi::~CCustomTraderSpi()
{
}
void CCustomTraderSpi::OnFrontConnected()
{
	std::cout << "=====建立网络连接成功=====" << std::endl;


	
	CThostFtdcReqUserLoginField loginreq;
	memset(&loginreq, 0, sizeof(loginreq));
	strcpy(loginreq.BrokerID, BROKER_ID);
	strcpy(loginreq.UserID, USER_ID);
	strcpy(loginreq.Password, PASSWORD);
	static int requestID = 0; // 请求编号
	int  rt = TraderApi->ReqUserLogin(&loginreq, requestID);
	if (!rt)
		std::cout << ">>>>>>发送登录请求成功" << std::endl;
	else
		std::cerr << "--->>>发送登录请求失败" << std::endl;
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
		
		// 开始订阅行情
		CThostFtdcQryInstrumentField *pQryInstrument =new CThostFtdcQryInstrumentField();
		strcpy(pQryInstrument->ExchangeID,"rb1901");
		int rt = TraderApi->ReqQryInstrument(pQryInstrument, 0);
		if (!rt)
			std::cout << ">>>>>>发送订阅行情请求成功" << std::endl;
		else
			std::cerr << "--->>>发送订阅行情请求失败" << std::endl;
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}
void CCustomTraderSpi::OnRspError(CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}
void CCustomTraderSpi::OnFrontDisconnected(int nReason)
{
}
//查询合约状态响应
void CCustomTraderSpi::OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField * pInstrumentStatus)
{
	std::cout << "交易所代码" << pInstrumentStatus->ExchangeID << std::endl;
	std::cout <<"合约在交易所的代码"<< pInstrumentStatus->ExchangeInstID << std::endl;
	std::cout <<"合约状态"<< pInstrumentStatus->InstrumentStatus <<std::endl;
}

//void CCustomTraderSpi::OnRspQryInstrument(CThostFtdcInstrumentField * pInstrument, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
//{
//}
