#pragma once
#include"../include/ctp_include/ThostFtdcMdApi.h"
//#include "ThostFtdcTraderApi.h"
#include  "Config.h"
/*����̳н��׽ӿ��� ��Ҫʵ���˺ͽ�����صĽӿ�*/
class CCustomTraderSpi :public CThostFtdcTraderSpi
{
public:
	CCustomTraderSpi();
	~CCustomTraderSpi();
	//�ӿ�ʵ��
	void OnFrontConnected();
	///�ͻ�����֤����
	void  ReqAuthenticate();
	///��¼����
	void reqUserLogin();
	
	///�ͻ�����֤��Ӧ
	virtual void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///��¼������Ӧ
	void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///����Ӧ��
	void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
	void OnFrontDisconnected(int nReason);
	
	///�����ѯ��Լ��Ӧ
	virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;


	///�ж��Ƿ񷵻��д�
	bool isErrorRspInfo(CThostFtdcRspInfoField *pRspInfo);
};

