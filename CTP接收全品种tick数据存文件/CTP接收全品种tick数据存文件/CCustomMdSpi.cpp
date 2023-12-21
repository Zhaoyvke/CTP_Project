#include "CCustomMdSpi.h"
#include <iostream>
#include <fstream>
#include <direct.h>
#include <algorithm>
#include "DealSpicalTime.h"

#include "WriteLog.h"
#include "TimeDeal.h"
#include "StringOpera.h"
using namespace std;
//extern char *pInstrumentID[];
extern vector<string> Ins;
extern CThostFtdcMdApi *mdApi;
extern volatile int singalnum;
extern int instrumentNum;
extern mutex Dealspicaltime_Mutex;//��������ʱ�����õ���
//extern char filePath[100];
extern DealSpicalTime  dealspicaltime;
extern map<string, string> m_instrument2Exchange;//��Լ�����ڽ�����֮��Ĺ�ϵ

//extern vector<string> Path;//�����ļ��洢·��
extern char targetpath[]; //�ļ��洢λ��
static int Recconect_num = 0;//��CTPƽ̨�����������ӵĴ���
///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
void CCustomMdSpi::OnFrontConnected()
{ 
	cout << "=======�����������ӳɹ�========";

	IsTraderTime = true;
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
	char timelocal[30];
	SYSTEMTIME exe_time;
	GetLocalTime(&exe_time);
	//sprintf_s(timelocal, "%d/%02d/%02d %02d:%02d:%02d:%03d", exe_time.wYear, exe_time.wMonth, exe_time.wDay, exe_time.wHour, exe_time.wMinute, exe_time.wSecond, exe_time.wMilliseconds);
	sprintf_s(timelocal, "%02d:%02d:%02d",  exe_time.wHour, exe_time.wMinute, exe_time.wSecond);
	ConnectTime = timelocal;

	if ((ConnectTime>"15:15:00"&&ConnectTime<"21:00:00")||(ConnectTime >"01:00:00"&&ConnectTime < "09:00:00")) //�ǽ���ʱ���
	{
		IsTraderTime = false;
	}

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


		//step1 ��ʼ����Լ��
		while (singalnum == 0) // �ȴ�����ӿڲ�ѯ��Լ��Ӧ�ɹ���
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}


		string tradeDay = mdApi->GetTradingDay();
		cout << "������Ϊ��" << tradeDay << endl;
		char buf[512];
		sprintf(buf,"������Ϊ%s",tradeDay.c_str());
     	WriteLog::writeloginfo(buf);  //
		
		InstoPath.clear();
		
		instrumentNum = Ins.size();  //�����Լ��������
		char **pInstrumentID = new char*[instrumentNum];
		string InsPre="";//Ʒ����
		for (int i = 0; i < Ins.size(); i++)
		{
			char * InsCell = (char*)Ins[i].c_str();
			pInstrumentID[i] = InsCell;


			//�����Լ�ʹ洢·��֮��Ĺ�ϵ
			string InsID= Ins[i];
			char filepath[200];
			//��������
			string exchange = "";
			if (m_instrument2Exchange.find(InsID) != m_instrument2Exchange.end())
			{
				exchange = m_instrument2Exchange[InsID];
			}

			sprintf(filepath, "%s%s/", targetpath, exchange.c_str());
			//Ʒ�ּ��·�
			int position=StringOpera::FindFirstChar(InsID);

			InsPre = InsID.substr(0, position);
			
			transform(InsPre.begin(), InsPre.end(), InsPre.begin(), ::toupper);//ת��Ϊ��д

			InsPre = InsPre+ "_" + tradeDay.substr(0, 6); //��ȡ�ַ����·� Ȼ���Ʒ�ֽ�������


			
			sprintf(filepath, "%s%s/", filepath, InsPre.c_str());

			Fd.Craetefolder(filepath); //������Ӧ�ļ���·��
			
			


			
			sprintf(filepath, "%s%s.csv", filepath,string(InsID +"_"+tradeDay).c_str());
			if (_access(filepath,0)==-1) //�жϸ�·�����ļ��Ƿ����  ���ڷ���0 �����ڷ���-1
			{
				ofstream outfile;
				outfile.open(filepath, ios::app);
				outfile << "������," << "��Լ����," << "����������," << "��Լ�ڽ������Ĵ���," << "���¼�," << "�ϴν���۸�," << "������," << "��ֲ���," << "����," << "��߼�," << "��ͼ�," << "����," << "�ɽ����," << "�ֲ���," << "������," << "���ν����," << "��ͣ���," << "��ͣ���," << "����ʵ��," << "����ʵ��," << "����޸�ʱ��," << "����޸ĺ���," << "�����һ," << "������һ," << "������һ," << "������һ," << "����۶�," << "��������," << "�����۶�," << "��������," << "�������," << "��������," << "��������," << "��������," << "�������," << "��������," << "��������," << "��������," << "�������," << "��������," << "��������," << "��������," << "���վ���," << "ҵ������," << endl;
				outfile.close();

			}
			
			InstoPath.insert(make_pair(InsID, filepath));//����Լ���·����ӵ�ӳ��
		}
		
		
		// ��ʼ��������
		int rt = mdApi->SubscribeMarketData(pInstrumentID, instrumentNum);
		if (!rt)
			std::cout << ">>>>>>���Ͷ�����������ɹ�" << std::endl;
		else
			std::cerr << "--->>>���Ͷ�����������ʧ��" << std::endl;
		
		//�ͷ�ָ���ڴ�ռ�
	      //delete pInstrumentID; 
		  
		  WriteLog::writeloginfo("��������");  //
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
		
		string dbname;
		string dbpre;
		string instrumentId = pSpecificInstrument->InstrumentID;

	
	}

}
///���������֤Ӧ��
void CCustomMdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField * pDepthMarketData)
{
	string filepath = GetFilePathByIns(pDepthMarketData->InstrumentID);
	if (filepath != " ")
	{
		//char timelocal[30];
		//SYSTEMTIME exe_time;
		//GetLocalTime(&exe_time);
		//sprintf_s(timelocal, "%d/%02d/%02d %02d:%02d:%02d:%03d", exe_time.wYear, exe_time.wMonth, exe_time.wDay, exe_time.wHour, exe_time.wMinute, exe_time.wSecond, exe_time.wMilliseconds);
		//string time1 = timelocal;
		//
		//
		////�жϽ���ʱ���Ƿ�Ϸ�
		string pre = pDepthMarketData->InstrumentID;//���׺�Լ
		int position = StringOpera::FindFirstChar(pre);
		pre = pre.substr(0, position);
		_strupr(const_cast<char*>(pre.c_str()));
		string time = pDepthMarketData->UpdateTime;
		if (IsTraderTime==false)
		{
			if ((ConnectTime > "01:00:00"&&ConnectTime < "09:00:00"))
			{
				if (time > ConnectTime && time< "09:01:00")  //����������������
				{
					IsTraderTime = true;
				}
			}
			else
			{
				if (time > ConnectTime)
				{
					IsTraderTime = true;
				}
			}
		}
		
		if (dealspicaltime.FindisinDirty(pre, time) == false && IsTraderTime==true && pDepthMarketData->Volume > 0)
		{

			ofstream outfile;
			outfile.open(filepath, ios::app);
			outfile.setf(ios::fixed);
			outfile.precision(6);
			outfile << pDepthMarketData->TradingDay << "," << pDepthMarketData->InstrumentID << "," << pDepthMarketData->ExchangeID << "," << pDepthMarketData->ExchangeInstID << "," << pDepthMarketData->LastPrice << "," << pDepthMarketData->PreSettlementPrice << "," << pDepthMarketData->PreClosePrice << "," << pDepthMarketData->PreOpenInterest << "," << pDepthMarketData->OpenPrice << "," << pDepthMarketData->HighestPrice << "," << pDepthMarketData->LowestPrice << "," << pDepthMarketData->Volume << "," << pDepthMarketData->Turnover << "," << pDepthMarketData->OpenInterest << "," << 0 << "," << 0 << "," << pDepthMarketData->UpperLimitPrice << "," << pDepthMarketData->LowerLimitPrice << "," << 0 << "," << 0 << "," << pDepthMarketData->UpdateTime << "," << pDepthMarketData->UpdateMillisec << "," << pDepthMarketData->BidPrice1 << "," << pDepthMarketData->BidVolume1 << "," << pDepthMarketData->AskPrice1 << "," << pDepthMarketData->AskVolume1 << "," << pDepthMarketData->BidPrice2 << "," << pDepthMarketData->BidVolume2 << "," << pDepthMarketData->AskPrice2 << "," << pDepthMarketData->AskVolume2 << "," << pDepthMarketData->BidPrice3 << "," << pDepthMarketData->BidVolume3 << "," << pDepthMarketData->AskPrice3 << "," << pDepthMarketData->AskVolume3 << "," << pDepthMarketData->BidPrice4 << "," << pDepthMarketData->BidVolume4 << "," << pDepthMarketData->AskPrice4 << "," << pDepthMarketData->AskVolume4 << "," << pDepthMarketData->BidPrice5 << "," << pDepthMarketData->BidVolume5 << "," << pDepthMarketData->AskPrice5 << "," << pDepthMarketData->AskVolume5 << "," << pDepthMarketData->AveragePrice << "," << pDepthMarketData->ActionDay << endl;
			outfile.close();
		}
		
	}

	
	
}

void CCustomMdSpi::CTPDatatransfortick(CThostFtdcDepthMarketDataField * pDepthMarketData, CTPtick * ctptick)
{

	strcpy(ctptick->InstrumentID, pDepthMarketData->InstrumentID); //��Լ����
	strcpy(ctptick->ExchangeID,pDepthMarketData->ExchangeID); //����������
	strcpy(ctptick->ExchangeInstID, pDepthMarketData->ExchangeInstID);//��Լ�ڽ������Ĵ���
	ctptick->LastPrice = pDepthMarketData->LastPrice;  //���¼�
	ctptick->PreSettlementPrice = pDepthMarketData->PreSettlementPrice;//�ϴν����
	ctptick->PreClosePrice = pDepthMarketData->PreClosePrice;//������
	ctptick->PreOpenInterest = pDepthMarketData->PreOpenInterest;//��ֲ���
	ctptick->OpenPrice = pDepthMarketData->OpenPrice;//����
	ctptick->HighestPrice = pDepthMarketData->HighestPrice;//��߼�
	ctptick->LowestPrice = pDepthMarketData->LowestPrice;//��ͼ�
	ctptick->Volume = pDepthMarketData->Volume;//����
	ctptick->Turnover = pDepthMarketData->Turnover;//�ɽ����
	ctptick->OpenInterest = pDepthMarketData->OpenInterest;//�ֲ���

	ctptick->ClosePrice = 0;//������
	ctptick->SettlementPrice = 0;//���ν����
	if (pDepthMarketData->LowerLimitPrice <= pDepthMarketData->ClosePrice&&pDepthMarketData->ClosePrice <= pDepthMarketData->UpperLimitPrice)
	{
		ctptick->ClosePrice = pDepthMarketData->ClosePrice;//������ 
	}
	if (pDepthMarketData->SettlementPrice < 10000) //test
	{
		ctptick->SettlementPrice = pDepthMarketData->SettlementPrice;//���ν����
	}
	
	ctptick->UpperLimitPrice = pDepthMarketData->UpperLimitPrice;//��ͣ���
	ctptick->LowerLimitPrice = pDepthMarketData->LowerLimitPrice;//��ͣ���
	
	//ctptick->PreDelta = pDepthMarketData->PreDelta;//����ʵ��
	//ctptick->CurrDelta = pDepthMarketData->CurrDelta;//����ʵ��

	ctptick->PreDelta = 0;//����ʵ��
	ctptick->CurrDelta = 0;//����ʵ��

	ctptick->BidPrice1 = pDepthMarketData->BidPrice1;//�����һ
	ctptick->BidVolume1 = pDepthMarketData->BidVolume1;//������һ
	ctptick->AskPrice1 = pDepthMarketData->AskPrice1;//������һ
	ctptick->AskVolume1 = pDepthMarketData->AskVolume1;//������һ

	ctptick->BidPrice2 = 0;//����۶�
	ctptick->BidVolume2 = 0;//��������
	ctptick->AskPrice2 =0;//�����۶�
	ctptick->AskVolume2 = 0;//��������

	ctptick->BidPrice3 = 0;//�������
	ctptick->BidVolume3 = 0;//��������
	ctptick->AskPrice3 = 0;//��������
	ctptick->AskVolume3 = 0;//��������

	ctptick->BidPrice4 = 0;//�������
	ctptick->BidVolume4 = 0;//��������
	ctptick->AskPrice4 = 0;//��������
	ctptick->AskVolume4 = 0;//��������

	ctptick->BidPrice5 = 0;//�������
	ctptick->BidVolume5 = 0;//��������
	ctptick->AskPrice5 = 0;//��������
	ctptick->AskVolume5 = 0;//��������

	if (strcmp(pDepthMarketData->ExchangeID, "SHFE") == 0 || (pDepthMarketData->ExchangeID, "INE") == 0)
	{

		ctptick->BidPrice2 = pDepthMarketData->BidPrice2;//����۶�
		ctptick->BidVolume2 = pDepthMarketData->BidVolume2;//��������
		ctptick->AskPrice2 = pDepthMarketData->AskPrice2;//�����۶�
		ctptick->AskVolume2 = pDepthMarketData->AskVolume2;//��������

		ctptick->BidPrice3 = pDepthMarketData->BidPrice3;//�������
		ctptick->BidVolume3 = pDepthMarketData->BidVolume3;//��������
		ctptick->AskPrice3 = pDepthMarketData->AskPrice3;//��������
		ctptick->AskVolume3 = pDepthMarketData->AskVolume3;//��������

		ctptick->BidPrice4 = pDepthMarketData->BidPrice4;//�������
		ctptick->BidVolume4 = pDepthMarketData->BidVolume4;//��������
		ctptick->AskPrice4 = pDepthMarketData->AskPrice4;//��������
		ctptick->AskVolume4 = pDepthMarketData->AskVolume4;//��������

		ctptick->BidPrice5 = pDepthMarketData->BidPrice5;//�������
		ctptick->BidVolume5 = pDepthMarketData->BidVolume5;//��������
		ctptick->AskPrice5 = pDepthMarketData->AskPrice5;//��������
		ctptick->AskVolume5 = pDepthMarketData->AskVolume5;//��������

	}

	ProductTime(pDepthMarketData->ExchangeID,pDepthMarketData->TradingDay, pDepthMarketData->ActionDay, pDepthMarketData->UpdateTime, pDepthMarketData->UpdateMillisec, ctptick->TradingDay, ctptick->local);
}

void CCustomMdSpi::ProductTime(const char* ExchangeID, const char * CTPtradeDay, const char *CTPActionDay, const char * CTPupdatetime,int millsec, char * ticktradeDay, char * local)
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
		SYSTEMTIME st;
		GetLocalTime(&st);
		//sprintf(updateTime, "%04d/%02d/%02d %02d:%02d", ac_year, ac_month, ac_day,hour,min); //��ȷ��������ʱ��
		sprintf(local, "%04d/%02d/%02d %02d:%02d:%02d.%03d", st.wYear, st.wMonth, st.wDay, hour, min, second, Mins);//��ȷ������

		if (strcmp(ExchangeID,"CZCE")==0)
		{
			
			sprintf(ticktradeDay, "%04d/%02d/%02d", st.wYear, st.wMonth, st.wDay);

			TimeDeal timedeal;
			int week = timedeal.GetDayOfWeek(ticktradeDay); //�жϽ������ܼ�

			if (week == 5 || week == 6) {
				if (hour > 15) { //���� ���� ������Ϊ��һ ������
					char descdate[35];
					timedeal.char_AddTime(ticktradeDay, descdate, 3 * 24 * 60 * 60, 0);
					strcpy(ticktradeDay, descdate);
				}
				else if (hour >= 0 && hour < 9 && week == 6) { //�������� ������ ������ 
					char descdate[35];
					timedeal.char_AddTime(ticktradeDay, descdate, 2 * 24 * 60 * 60, 0);
					strcpy(ticktradeDay, descdate);
				}
				//week=5 and ����� ���������Ĺ�����
			}
			else {
				if (hour > 15) { //ƽʱ���Ͻ����ռ�һ��
					char descdate[35];
					timedeal.char_AddTime(ticktradeDay, descdate, 24 * 60 * 60, 0);
					strcpy(ticktradeDay, descdate);
				}
			}

		}
		
	}

}
//�����ݲ��뵽���ݿ�
void CCustomMdSpi::InsertTicktoDB(CTPtick ctptick)
{
	string tablename = ctptick.InstrumentID;
	tablename += "_tick";
	m_instrumentIDtoDBoper.find(ctptick.InstrumentID)->second->InsertToTickTable(ctptick, tablename);
}

string CCustomMdSpi::GetFilePathByIns(string ins)
{

	if (InstoPath.find(ins) != InstoPath.end())
	{
		return InstoPath[ins];
	}
	else
	{
		return " ";
	}
	
}



