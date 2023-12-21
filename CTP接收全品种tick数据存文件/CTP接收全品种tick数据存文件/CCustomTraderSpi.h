#pragma once
#include"../include/ctp_include/ThostFtdcMdApi.h"
//#include "ThostFtdcTraderApi.h"
#include  "Config.h"
/*该类继承交易接口类 主要实现了和交易相关的接口*/
class CCustomTraderSpi :public CThostFtdcTraderSpi
{
public:
	CCustomTraderSpi();
	~CCustomTraderSpi();
	//接口实现
	void OnFrontConnected();
	///客户端认证请求
	void  ReqAuthenticate();
	///登录请求
	void reqUserLogin();
	
	///客户端认证响应
	virtual void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///登录请求响应
	void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///错误应答
	void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	void OnFrontDisconnected(int nReason);
	
	///请求查询合约响应
	virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;


	///判断是否返回有错
	bool isErrorRspInfo(CThostFtdcRspInfoField *pRspInfo);
};

