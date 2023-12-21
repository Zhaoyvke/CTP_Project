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
/*������Ҫʵ�������齻�׽ӿ�*/
class CCustomMdSpi:public CThostFtdcMdSpi
{
public:

	//���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
	virtual void OnFrontConnected();

	///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
	///@param nReason ����ԭ��
	///        0x1001 �����ʧ��
	///        0x1002 ����дʧ��
	///        0x2001 ����������ʱ
	///        0x2002 ��������ʧ��
	///        0x2003 �յ�������
	virtual void OnFrontDisconnected(int nReason);

	///��¼������Ӧ
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
	///@param nTimeLapse �����ϴν��ձ��ĵ�ʱ��
	 void OnHeartBeatWarning(int nTimeLapse);
	///�ǳ�������Ӧ
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///����Ӧ��
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///��������Ӧ��
	virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�������֪ͨ
	virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);
	
	//��CTP���ؽṹ��װ��Ϊtick����
	void CTPDatatransfortick(CThostFtdcDepthMarketDataField *pDepthMarketData,CTPtick *ctptick);

	//ͨ��CTP�ӿڵ��������� �����գ�updateTime��localʱ��
	void ProductTime(const char* ExchangeID, const char *CTPtradeDay, const char *CTPActionDay, const char *CTPupdatetime, int millsec,char*ticktradeDay,char*local);

	///�����ݲ��뵽���ݿ�
	void InsertTicktoDB(CTPtick ctptick);

	//����ļ�·��
	string GetFilePathByIns(string ins);

private:
	map<string, CTPDBoperator*> m_instrumentIDtoDBoper;  //��Լ������ݿ��Ӧ������

	map<string,string> InstoPath;//��Լ��Ͷ�Ӧ�����ļ��洢·��

	FileDeal Fd;//�����ļ�·����ص���
	string ConnectTime;//������������ʱ��ʱ��
	bool IsTraderTime;//�Ƿ��ڽ���ʱ��
};

