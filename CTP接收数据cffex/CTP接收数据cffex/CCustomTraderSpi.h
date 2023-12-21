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

	//��¼������Ӧ
	void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//����Ӧ��
	void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
	void OnFrontDisconnected(int nReason);
	//��Լ����״̬֪ͨ
	virtual void OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus);
};

