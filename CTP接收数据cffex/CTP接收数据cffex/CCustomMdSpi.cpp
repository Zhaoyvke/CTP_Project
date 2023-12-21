#include "CCustomMdSpi.h"
#include <iostream>
#include <fstream>
#include "DealSpicalTime.h"
#include "FileDeal.h"
#include "WriteLog.h"
using namespace std;
extern char *pInstrumentID[];
extern CThostFtdcMdApi *mdApi;
extern int instrumentNum;
extern char filePath[100];
extern DealSpicalTime  dealspicaltime;
extern map<string, string> m_instrument2dbname; 
static int Recconect_num = 0;//��CTPƽ̨�����������ӵĴ���

///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
void CCustomMdSpi::OnFrontConnected()
{ 
	cout << "=======�����������ӳɹ�========";

	WriteLog::writeloginfo("===�����������ӳɹ�===");  //д���س�����־��
	CThostFtdcReqUserLoginField loginreq;
	memset(&loginreq, 0, sizeof(loginreq));
	strcpy(loginreq.BrokerID, BROKER_ID);
	strcpy(loginreq.UserID, USER_ID);
	strcpy(loginreq.Password, PASSWORD);
	static int requestID = 0; // ������
	int  rt = mdApi->ReqUserLogin(&loginreq, requestID);
	if (!rt)
		std::cout << ">>>>>>���͵�¼����ɹ�" << std::endl;
	else
		std::cerr << "--->>>���͵�¼����ʧ��" << std::endl;

}
///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
void CCustomMdSpi::OnFrontDisconnected(int nReason)
{
	
	std::cerr << "=====�������ӶϿ�=====" << std::endl;
	std::cerr << "�����룺 " << nReason << std::endl;
	WriteLog::writeloginfo("===�������ӶϿ�===");  //д���س�����־��
}

///��¼������Ӧ
void CCustomMdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField * pRspUserLogin, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		std::cout << "=====�����˻���¼�ɹ�=====" << std::endl;
		std::cout << "�����գ� " << pRspUserLogin->TradingDay << std::endl;
		std::cout << "��¼ʱ�䣺 " << pRspUserLogin->LoginTime << std::endl;
		std::cout << "�����̣� " << pRspUserLogin->BrokerID << std::endl;
		std::cout << "�ʻ����� " << pRspUserLogin->UserID << std::endl;
		WriteLog::writeloginfo("===�����˻���¼�ɹ�===");

		m_Inst2filepath.clear();  //���instrument to filepath �ļ�ֵmap���� 

		if(Recconect_num==0)
		{
			m_thread = std::thread(&CCustomMdSpi::DealMarketData, this);  //�����߳̿��Ƿ���յ�tick
			Recconect_num++;
		}
		

		// ��ʼ��������
		int rt = mdApi->SubscribeMarketData(pInstrumentID, instrumentNum);
		if (!rt)
			std::cout << ">>>>>>���Ͷ�����������ɹ�" << std::endl;
		else
			std::cerr << "--->>>���Ͷ�����������ʧ��" << std::endl;
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}
///������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
void CCustomMdSpi::OnHeartBeatWarning(int nTimeLapse)
{
	std::cerr << "=====����������ʱ=====" << std::endl;
	std::cerr << "���ϴ�����ʱ�䣺 " << nTimeLapse << std::endl;
}
///�ǳ�Ӧ��
void CCustomMdSpi::OnRspUserLogout(CThostFtdcUserLogoutField * pUserLogout, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		std::cout << "=====�˻��ǳ��ɹ�=====" << std::endl;
		std::cout << "�����̣� " << pUserLogout->BrokerID << std::endl;
		std::cout << "�ʻ����� " << pUserLogout->UserID << std::endl;
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}
///����Ӧ��
void CCustomMdSpi::OnRspError(CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (bResult)
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}
///���鶩��Ӧ��
void CCustomMdSpi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField * pSpecificInstrument, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		std::cout << "=====��������ɹ�=====" << std::endl;
		std::cout << "��Լ���룺 " << pSpecificInstrument->InstrumentID << std::endl;
		// �����Ҫ�����ļ��������ݿ⣬�����ﴴ����ͷ,��ͬ�ĺ�Լ�����洢

	}

}
///���������֤Ӧ��
void CCustomMdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField * pDepthMarketData)
{

	cout << "=====����������=====" << endl;
	cout << "�����գ� " << pDepthMarketData->TradingDay << endl;
	cout << "����ʱ��" << pDepthMarketData->UpdateTime << "." << pDepthMarketData->UpdateMillisec << endl;
	string trinday = pDepthMarketData->TradingDay;
	string  uptime = pDepthMarketData->UpdateTime;
	int mill = pDepthMarketData->UpdateMillisec;
	char timelocal[30];
	SYSTEMTIME exe_time;
	GetLocalTime(&exe_time);
	sprintf_s(timelocal, "%d/%02d/%02d %02d:%02d:%02d:%03d", exe_time.wYear, exe_time.wMonth, exe_time.wDay, exe_time.wHour, exe_time.wMinute, exe_time.wSecond, exe_time.wMilliseconds);
	string time1 = timelocal;
	string conne="����ʱ��:"+ time1+"�����գ� " + trinday+"����ʱ��"+ uptime+"."+to_string(mill);
	//WriteLog::writeloginfo(conne);
	//�жϽ���ʱ���Ƿ�Ϸ�
	string pre = pDepthMarketData->InstrumentID;//���׺�Լ
	int position = StringOpera::FindFirstChar(pre);
	pre = pre.substr(0, position);
	_strupr(const_cast<char*>(pre.c_str()));
	string time = pDepthMarketData->UpdateTime;
	if (dealspicaltime.FindisinDirty(pre, time) == false && pDepthMarketData->Volume > 0)
	{
		//&&   pDepthMarketData->Volume > 0
		//dealspicaltime.JudgeLocatimeAndupdateTimeisEqual((char*)time.substr(0, 5).c_str())
		//char *Path = new char[100];
		//if (m_Inst2filepath.find(pDepthMarketData->InstrumentID) != m_Inst2filepath.end())
		//{
		//	strcpy(Path, (m_Inst2filepath.find(pDepthMarketData->InstrumentID)->second).c_str());//copy �ļ�·��
		//}
		//else
		//{
		//	cerr << "δ�ҵ��ú�Լ���Ӧ�洢·��" << endl;
		//	system("pause");
		//}

		std::unique_lock<std::mutex> lock(m_Mutex);

		Tick *tick = new Tick();
		CTPDatatransfortick(pDepthMarketData, tick);
		ticks.push(tick);
		lock.unlock();
		m_conVar.notify_all();
	}
}

void CCustomMdSpi::DealMarketData()
{
	
	while (true)
	{
		std::unique_lock<std::mutex> lock(m_Mutex);

		//��ȡ��ǰʱ�� (����ʱ��)
		time_t local = time(NULL);
		struct tm* slocaltime = localtime(&local);  //ת��ʱ���ʽ
		char CurrentTime[32];  //������¼��ǰʱ��
		sprintf(CurrentTime, "%02d:%02d", slocaltime->tm_hour, slocaltime->tm_min);
		if (ticks.empty())
		{
			m_conVar.wait_for(lock, std::chrono::milliseconds(50));
		}

		if (ticks.empty())
		{
			continue;
		}
		Tick * tick = ticks.front();
		ticks.pop();//�Ӷ��еĿ�ͷɾ��һ��Ԫ��
		if (strcmp(tick->instumentId,"")!=0)
		{
			if (m_instrumentID2Ckline.find(tick->instumentId) != m_instrumentID2Ckline.end())
			{
				map<string, CTPDatatransForKline*>::iterator iter = m_instrumentID2Ckline.find(tick->instumentId);
				
				iter->second->CaltickkAndInsertDB(tick); 	//����K�߲����������ݿ�
			}
			else
			{
				CTPDatatransForKline *ctptransfor = new CTPDatatransForKline(tick->instumentId);
				ctptransfor->CaltickkAndInsertDB(tick);	//����K�߲����������ݿ�
				m_instrumentID2Ckline.insert(make_pair(tick->instumentId, ctptransfor));
			}
		}
		
		lock.unlock();
	
	}

}

void CCustomMdSpi::CTPDatatransfortick(CThostFtdcDepthMarketDataField * pDepthMarketData, Tick * tick)
{
	
	if (m_instrument2dbname.find(string(pDepthMarketData->InstrumentID).substr(0, 2)) == m_instrument2dbname.end())
	{  //if(m_instrument2dbname.find(pDepthMarketData->ExchangeID)== m_instrument2dbname.end())
		OutputDebugStringA("δ�ҵ����Ʒ��ƥ��Ľ�����");
		return;
	}
	
	string jiaoyisuo;
	string stemp_instrumentID = pDepthMarketData->InstrumentID;
	if (m_instrument2dbname.find(stemp_instrumentID.substr(0, 2))!= m_instrument2dbname.end())//if (m_instrument2dbname.find(pDepthMarketData->ExchangeID) == m_instrument2dbname.end())
	{
		
		jiaoyisuo= m_instrument2dbname.find(stemp_instrumentID.substr(0, 2))->second;
	}
	
	_strupr(const_cast<char*>(stemp_instrumentID.c_str()));
	string instrumentID= _strupr(const_cast<char*>(jiaoyisuo.c_str()));
	instrumentID = instrumentID + "|F|" + stemp_instrumentID.substr(0, 2) +"|"+ stemp_instrumentID.substr(2);

	strcpy(tick->instumentId, instrumentID.c_str());
	tick->highprice= pDepthMarketData->HighestPrice;

	tick->lastprice= pDepthMarketData->LastPrice;
	tick->openprice= pDepthMarketData->OpenPrice;
	tick->lowprice= pDepthMarketData->LowestPrice;
	
	tick->openInterest= pDepthMarketData->OpenInterest;
	tick->PreOpenInterest = pDepthMarketData->PreOpenInterest; //���ճֲ���
	tick->totalvolume= pDepthMarketData->Volume;
	tick->buyprice = pDepthMarketData->BidPrice1;//��һ��
	tick->buyqty = pDepthMarketData->BidVolume1;//��һ��
	tick->sellprice = pDepthMarketData->AskPrice1;//��һ��
	tick->sellqty = pDepthMarketData->AskVolume1;//��һ��

	ProductTime(pDepthMarketData->TradingDay, pDepthMarketData->ActionDay, pDepthMarketData->UpdateTime, pDepthMarketData->UpdateMillisec, tick->tradeDay, tick->updateTime, tick->local);
}

void CCustomMdSpi::ProductTime(const char * CTPtradeDay, const char *CTPActionDay, const char * CTPupdatetime,int millsec, char * ticktradeDay, char * updateTime, char * local)
{
	if (CTPtradeDay != nullptr&&CTPupdatetime != nullptr&&CTPupdatetime != nullptr&&strcmp(CTPtradeDay,"")!=0)
	{
		int tr_year, tr_month, tr_day, ac_year, ac_month,ac_day,hour,min,second,Mins;
		//�����ݸ�ʽ������
		sscanf(CTPtradeDay,"%04d%02d%02d",&tr_year,&tr_month,&tr_day);

		sscanf(CTPActionDay, "%04d%02d%02d", &ac_year, &ac_month, &ac_day);
		sscanf(CTPupdatetime, "%02d:%02d:%02d", &hour, &min, &second);
		sscanf(to_string(millsec).c_str(), "%03d", &Mins);

		sprintf(ticktradeDay, "%04d/%02d/%02d", tr_year, tr_month, tr_day); //��ȷ��������

		sprintf(updateTime, "%04d/%02d/%02d %02d:%02d", ac_year, ac_month, ac_day,hour,min); //��ȷ��������ʱ��
		sprintf(local,"%04d/%02d/%02d %02d:%02d:%02d.%03d", ac_year, ac_month, ac_day, hour, min, second, Mins);//��ȷ������
	}

}


