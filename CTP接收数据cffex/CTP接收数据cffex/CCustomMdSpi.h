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
#include  "klineStruct.h"
#include "CTPDatatransForKline.h"
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

	void DealMarketData();  //该函数用来开启线程监控是否接受到tick
	
	//将CTP返回结构体装换为tick数据
	void CTPDatatransfortick(CThostFtdcDepthMarketDataField *pDepthMarketData,Tick *tick);

	//通过CTP接口的数据生成 交易日，updateTime和local时间
	void ProductTime(const char *CTPtradeDay, const char *CTPActionDay, const char *CTPupdatetime, int millsec,char*ticktradeDay,char *updateTime,char*local);

private:
	map<string, string> m_Inst2filepath;  //map 容器存放的是 合约码和文件路径的键值关系

	thread m_thread;
	mutable std::mutex m_Mutex;
	condition_variable m_conVar;
	queue<Tick*> ticks;

	map <string, CTPDatatransForKline *> m_instrumentID2Ckline;  //合约码与生成k线的类的键值对
	/*CTPDatatransForKline *ctpfotkline;*/
};

