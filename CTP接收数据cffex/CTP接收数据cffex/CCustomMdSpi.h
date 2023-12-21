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

	void DealMarketData();  //�ú������������̼߳���Ƿ���ܵ�tick
	
	//��CTP���ؽṹ��װ��Ϊtick����
	void CTPDatatransfortick(CThostFtdcDepthMarketDataField *pDepthMarketData,Tick *tick);

	//ͨ��CTP�ӿڵ��������� �����գ�updateTime��localʱ��
	void ProductTime(const char *CTPtradeDay, const char *CTPActionDay, const char *CTPupdatetime, int millsec,char*ticktradeDay,char *updateTime,char*local);

private:
	map<string, string> m_Inst2filepath;  //map ������ŵ��� ��Լ����ļ�·���ļ�ֵ��ϵ

	thread m_thread;
	mutable std::mutex m_Mutex;
	condition_variable m_conVar;
	queue<Tick*> ticks;

	map <string, CTPDatatransForKline *> m_instrumentID2Ckline;  //��Լ��������k�ߵ���ļ�ֵ��
	/*CTPDatatransForKline *ctpfotkline;*/
};

