#pragma once
//#include "ThostFtdcMdApi.h"
#include"../include/ctp_include/ThostFtdcMdApi.h"
#include "Config.h"
#include <windows.h>
#include "StringOpera.h"
#include <map>
#include <string>
#include <mutex>
#include <queue>
#include <thread>
#include  "Struct.h"
#include "CTPDBoperator.h"
#include "FileDeal.h"
/*该类主要实现了行情交易接口*/
class CCustomMdSpi:public CThostFtdcMdSpi
{
public:

	//当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
	virtual void OnFrontConnected();

	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	///@param nReason 错误原因
	///        0x1001 网络读失败
	///        0x1002 网络写失败
	///        0x2001 接收心跳超时
	///        0x2002 发送心跳失败
	///        0x2003 收到错误报文
	virtual void OnFrontDisconnected(int nReason);

	///登录请求响应
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///心跳超时警告。当长时间未收到报文时，该方法被调用。
	///@param nTimeLapse 距离上次接收报文的时间
	 void OnHeartBeatWarning(int nTimeLapse);
	///登出请求响应
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///错误应答
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///订阅行情应答
	virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///深度行情通知
	virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);
	
	//将CTP返回结构体装换为tick数据
	void CTPDatatransfortick(CThostFtdcDepthMarketDataField *pDepthMarketData,CTPtick *ctptick);

	//通过CTP接口的数据生成 交易日，updateTime和local时间
	void ProductTime(const char* ExchangeID, const char *CTPtradeDay, const char *CTPActionDay, const char *CTPupdatetime, int millsec,char*ticktradeDay,char*local);

	///将数据插入到数据库
	void InsertTicktoDB(CTPtick ctptick);

	//获得文件路径
	string GetFilePathByIns(string ins);

private:
	map<string, CTPDBoperator*> m_instrumentIDtoDBoper;  //合约码和数据库对应的容器

	map<string,string> InstoPath;//合约码和对应数据文件存储路径

	FileDeal Fd;//创建文件路径相关的类
	string ConnectTime;//创建网络连接时的时间
	bool IsTraderTime;//是否处于交易时间
};

