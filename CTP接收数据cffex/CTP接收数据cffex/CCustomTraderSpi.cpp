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
	std::cout << "=====�����������ӳɹ�=====" << std::endl;


	
	CThostFtdcReqUserLoginField loginreq;
	memset(&loginreq, 0, sizeof(loginreq));
	strcpy(loginreq.BrokerID, BROKER_ID);
	strcpy(loginreq.UserID, USER_ID);
	strcpy(loginreq.Password, PASSWORD);
	static int requestID = 0; // ������
	int  rt = TraderApi->ReqUserLogin(&loginreq, requestID);
	if (!rt)
		std::cout << ">>>>>>���͵�¼����ɹ�" << std::endl;
	else
		std::cerr << "--->>>���͵�¼����ʧ��" << std::endl;
}
void CCustomTraderSpi::OnRspUserLogin(CThostFtdcRspUserLoginField * pRspUserLogin, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		std::cout << "=====�����˻���¼�ɹ�=====" << std::endl;
		std::cout << "�����գ� " << pRspUserLogin->TradingDay << std::endl;
		std::cout << "��¼ʱ�䣺 " << pRspUserLogin->LoginTime << std::endl;
		std::cout << "�����̣� " << pRspUserLogin->BrokerID << std::endl;
		std::cout << "�ʻ����� " << pRspUserLogin->UserID << std::endl;
		
		// ��ʼ��������
		CThostFtdcQryInstrumentField *pQryInstrument =new CThostFtdcQryInstrumentField();
		strcpy(pQryInstrument->ExchangeID,"rb1901");
		int rt = TraderApi->ReqQryInstrument(pQryInstrument, 0);
		if (!rt)
			std::cout << ">>>>>>���Ͷ�����������ɹ�" << std::endl;
		else
			std::cerr << "--->>>���Ͷ�����������ʧ��" << std::endl;
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}
void CCustomTraderSpi::OnRspError(CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}
void CCustomTraderSpi::OnFrontDisconnected(int nReason)
{
}
//��ѯ��Լ״̬��Ӧ
void CCustomTraderSpi::OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField * pInstrumentStatus)
{
	std::cout << "����������" << pInstrumentStatus->ExchangeID << std::endl;
	std::cout <<"��Լ�ڽ������Ĵ���"<< pInstrumentStatus->ExchangeInstID << std::endl;
	std::cout <<"��Լ״̬"<< pInstrumentStatus->InstrumentStatus <<std::endl;
}

//void CCustomTraderSpi::OnRspQryInstrument(CThostFtdcInstrumentField * pInstrument, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
//{
//}
