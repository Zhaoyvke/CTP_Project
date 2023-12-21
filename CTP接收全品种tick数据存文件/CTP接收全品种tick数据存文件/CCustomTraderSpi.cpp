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
extern vector<string> Ins; //��ź�Լ���������
extern map<string, string> m_instrument2Exchange;//��ź�Լ�ͽ�����֮���ӳ��
extern volatile int singalnum; //ȫ�ֱ������ڽ��̼��ͨ��
extern mutex pInstrument_Mutex;//���������Լ������
extern char targetpath[]; //�ļ��洢λ��
unique_lock<std::mutex> lock;
CCustomTraderSpi::CCustomTraderSpi()
{

}


CCustomTraderSpi::~CCustomTraderSpi()
{

}
void CCustomTraderSpi::OnFrontConnected()
{
	std::cout << "=====�����������ӳɹ�=====" << std::endl;
	WriteLog::writeloginfo("==�����������ӳɹ�==trader");  //
	if (singalnum==0) //ֵΪ��
	{
		ReqAuthenticate();//����ͻ�����֤
	}
		
}
void CCustomTraderSpi::ReqAuthenticate()
{
	CThostFtdcReqAuthenticateField auth;
	memset(&auth, 0, sizeof(auth));
	strcpy(auth.BrokerID, BROKER_ID);
	strcpy(auth.UserID, USER_ID);
	strcpy(auth.AuthCode, AUTHCODE); //��֤��
	strcpy(auth.AppID, APPID); //appid
	static int requestID = 0; // ������
	int result = TraderApi->ReqAuthenticate(&auth, ++requestID);
	if (!result)
	{
		std::cout << ">>>���Ϳͻ�����֤��Ӧ�ɹ�" << std::endl;
		WriteLog::writeloginfo(">>>���Ϳͻ�����֤��Ӧ�ɹ�");  //
	}
	else
	{
		std::cout << ">>>���Ϳͻ�����֤��Ӧʧ��" << std::endl;
		WriteLog::writeloginfo(">>>���Ϳͻ�����֤��Ӧ�ɹ�");  //
	}
		
}
void CCustomTraderSpi::reqUserLogin()
{
	CThostFtdcReqUserLoginField loginreq;
	memset(&loginreq, 0, sizeof(loginreq));
	strcpy(loginreq.BrokerID, BROKER_ID);
	strcpy(loginreq.UserID, USER_ID);
	strcpy(loginreq.Password, PASSWORD);
	static int requestID = 0; // ������
	int  rt = TraderApi->ReqUserLogin(&loginreq, requestID);
	if (!rt)
		std::cout << ">>>>>>���ͽ��׵�¼����ɹ�" << std::endl;
	else
		std::cerr << "--->>>���ͽ��׵�¼����ʧ��" << std::endl;
}
void CCustomTraderSpi::OnRspAuthenticate(CThostFtdcRspAuthenticateField * pRspAuthenticateField, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
	if (isErrorRspInfo(pRspInfo))
	{
		if (bIsLast == true)
		{
			std::cout << "====�ͻ�����Ӧ�ɹ�====" << std::endl;
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
		std::cout << "=====�����˻���¼�ɹ�=====" << std::endl;
		std::cout << "�����գ� " << pRspUserLogin->TradingDay << std::endl;
		std::cout << "��¼ʱ�䣺 " << pRspUserLogin->LoginTime << std::endl;
		std::cout << "�����̣� " << pRspUserLogin->BrokerID << std::endl;
		std::cout << "�ʻ����� " << pRspUserLogin->UserID << std::endl;
		WriteLog::writeloginfo("==�����˻���¼�ɹ�==trader");  //
		// ��ʼ��ѯ��Լ
		CThostFtdcQryInstrumentField *pQryInstrument =new CThostFtdcQryInstrumentField();
		strcpy(pQryInstrument->ExchangeID,"");
		int rt = TraderApi->ReqQryInstrument(pQryInstrument, 0);
		if (!rt)
		{
			std::cout << ">>>>>>���Ͳ�ѯ��Լ����ɹ�" << std::endl;
			
		}
			
		else
			std::cerr << "--->>>���Ͳ�ѯ��Լ����ʧ��" << std::endl;
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}
void CCustomTraderSpi::OnRspError(CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}
void CCustomTraderSpi::OnFrontDisconnected(int nReason)
{
	std::cerr << "=====�������ӶϿ�=====" << std::endl;
	std::cerr << "�����룺 " << nReason << std::endl;
	WriteLog::writeloginfo("===�������ӶϿ�===Trader");  //д���س�����־��
}

void CCustomTraderSpi::OnRspQryInstrument(CThostFtdcInstrumentField * pInstrument, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
	if (pInstrument->ProductClass =='1') //��Ʒ����='1'Ϊ�ڻ�
	{
		std::cout << "����������" << pInstrument->ExchangeID << std::endl;
		std::cout << "��Լ����" << pInstrument->InstrumentID << std::endl;
		//std::cout << "��ǰ�Ƿ���" << pInstrument->IsTrading << std::endl;
		Ins.push_back(pInstrument->InstrumentID);

		m_instrument2Exchange.insert(make_pair(pInstrument->InstrumentID, string(pInstrument->ExchangeID))); //������Լ����ͽ�����֮��Ĺ�ϵӳ��
		//cout << Ins.size() << endl;
	}
	if (bIsLast == true)
	{
		singalnum = 1; //��Լ��ȡ���ʱ����ȫ�ֱ���Ϊ1;
	}
	
	
}

bool CCustomTraderSpi::isErrorRspInfo(CThostFtdcRspInfoField * pRspInfo)
{
	bool result = (pRspInfo != nullptr) && (pRspInfo->ErrorID == 0);
	return result;
}

