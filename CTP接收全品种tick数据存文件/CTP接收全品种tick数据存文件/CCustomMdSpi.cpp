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
extern mutex Dealspicaltime_Mutex;//处理特殊时间所用的锁
//extern char filePath[100];
extern DealSpicalTime  dealspicaltime;
extern map<string, string> m_instrument2Exchange;//合约和所在交易所之间的关系

//extern vector<string> Path;//数据文件存储路径
extern char targetpath[]; //文件存储位置
static int Recconect_num = 0;//与CTP平台建立网络连接的次数
///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
void CCustomMdSpi::OnFrontConnected()
{ 
	cout << "=======建立网络连接成功========";

	IsTraderTime = true;
	WriteLog::writeloginfo("===建立网络连接成功===");  //写入监控程序日志中
	CThostFtdcReqUserLoginField loginreq;
	memset(&loginreq, 0, sizeof(loginreq));
	strcpy(loginreq.BrokerID, BROKER_ID);
	strcpy(loginreq.UserID, USER_ID);
	strcpy(loginreq.Password, PASSWORD);
	static int requestID = 0; // 请求编号
	int  rt = mdApi->ReqUserLogin(&loginreq, requestID);
	if (!rt)
		std::cout << ">>>>>>发送登录请求成功" << std::endl;
	else
		std::cerr << "--->>>发送登录请求失败" << std::endl;
	char timelocal[30];
	SYSTEMTIME exe_time;
	GetLocalTime(&exe_time);
	//sprintf_s(timelocal, "%d/%02d/%02d %02d:%02d:%02d:%03d", exe_time.wYear, exe_time.wMonth, exe_time.wDay, exe_time.wHour, exe_time.wMinute, exe_time.wSecond, exe_time.wMilliseconds);
	sprintf_s(timelocal, "%02d:%02d:%02d",  exe_time.wHour, exe_time.wMinute, exe_time.wSecond);
	ConnectTime = timelocal;

	if ((ConnectTime>"15:15:00"&&ConnectTime<"21:00:00")||(ConnectTime >"01:00:00"&&ConnectTime < "09:00:00")) //非交易时间段
	{
		IsTraderTime = false;
	}

}
///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
void CCustomMdSpi::OnFrontDisconnected(int nReason)
{
	
	std::cerr << "=====网络连接断开=====" << std::endl;
	std::cerr << "错误码： " << nReason << std::endl;
	WriteLog::writeloginfo("===网络连接断开===");  //写入监控程序日志中
}

///登录请求响应
void CCustomMdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField * pRspUserLogin, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		std::cout << "=====行情账户登录成功=====" << std::endl;
		std::cout << "交易日： " << pRspUserLogin->TradingDay << std::endl;
		std::cout << "登录时间： " << pRspUserLogin->LoginTime << std::endl;
		std::cout << "经纪商： " << pRspUserLogin->BrokerID << std::endl;
		std::cout << "帐户名： " << pRspUserLogin->UserID << std::endl;
		WriteLog::writeloginfo("===行情账户登录成功===");


		//step1 初始化合约码
		while (singalnum == 0) // 等待行情接口查询合约响应成功后
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}


		string tradeDay = mdApi->GetTradingDay();
		cout << "交易日为：" << tradeDay << endl;
		char buf[512];
		sprintf(buf,"交易日为%s",tradeDay.c_str());
     	WriteLog::writeloginfo(buf);  //
		
		InstoPath.clear();
		
		instrumentNum = Ins.size();  //行情合约订阅数量
		char **pInstrumentID = new char*[instrumentNum];
		string InsPre="";//品种名
		for (int i = 0; i < Ins.size(); i++)
		{
			char * InsCell = (char*)Ins[i].c_str();
			pInstrumentID[i] = InsCell;


			//处理合约和存储路径之间的关系
			string InsID= Ins[i];
			char filepath[200];
			//交易所名
			string exchange = "";
			if (m_instrument2Exchange.find(InsID) != m_instrument2Exchange.end())
			{
				exchange = m_instrument2Exchange[InsID];
			}

			sprintf(filepath, "%s%s/", targetpath, exchange.c_str());
			//品种加月份
			int position=StringOpera::FindFirstChar(InsID);

			InsPre = InsID.substr(0, position);
			
			transform(InsPre.begin(), InsPre.end(), InsPre.begin(), ::toupper);//转换为大写

			InsPre = InsPre+ "_" + tradeDay.substr(0, 6); //截取字符到月份 然后和品种进行连接


			
			sprintf(filepath, "%s%s/", filepath, InsPre.c_str());

			Fd.Craetefolder(filepath); //创建对应文件夹路径
			
			


			
			sprintf(filepath, "%s%s.csv", filepath,string(InsID +"_"+tradeDay).c_str());
			if (_access(filepath,0)==-1) //判断该路径下文件是否存在  存在返回0 不存在返回-1
			{
				ofstream outfile;
				outfile.open(filepath, ios::app);
				outfile << "交易日," << "合约代码," << "交易所代码," << "合约在交易所的代码," << "最新价," << "上次结算价格," << "昨收盘," << "昨持仓量," << "今开盘," << "最高价," << "最低价," << "数量," << "成交金额," << "持仓量," << "今收盘," << "本次结算价," << "涨停板价," << "跌停板价," << "昨虚实度," << "今虚实度," << "最后修改时间," << "最后修改毫秒," << "申买价一," << "申买量一," << "申卖价一," << "申卖量一," << "申买价二," << "申买量二," << "申卖价二," << "申卖量二," << "申买价三," << "申买量三," << "申卖价三," << "申卖量三," << "申买价四," << "申买量四," << "申卖价四," << "申卖量四," << "申买价五," << "申买量五," << "申卖价五," << "申卖量五," << "当日均价," << "业务日期," << endl;
				outfile.close();

			}
			
			InstoPath.insert(make_pair(InsID, filepath));//将合约码和路径添加到映射
		}
		
		
		// 开始订阅行情
		int rt = mdApi->SubscribeMarketData(pInstrumentID, instrumentNum);
		if (!rt)
			std::cout << ">>>>>>发送订阅行情请求成功" << std::endl;
		else
			std::cerr << "--->>>发送订阅行情请求失败" << std::endl;
		
		//释放指针内存空间
	      //delete pInstrumentID; 
		  
		  WriteLog::writeloginfo("订阅行情");  //
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}
///心跳超时警告。当长时间未收到报文时，该方法被调用。
void CCustomMdSpi::OnHeartBeatWarning(int nTimeLapse)
{
	std::cerr << "=====网络心跳超时=====" << std::endl;
	std::cerr << "距上次连接时间： " << nTimeLapse << std::endl;
}
///登出应答
void CCustomMdSpi::OnRspUserLogout(CThostFtdcUserLogoutField * pUserLogout, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		std::cout << "=====账户登出成功=====" << std::endl;
		std::cout << "经纪商： " << pUserLogout->BrokerID << std::endl;
		std::cout << "帐户名： " << pUserLogout->UserID << std::endl;
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}
///错误应答
void CCustomMdSpi::OnRspError(CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (bResult)
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}
///行情订阅应答
void CCustomMdSpi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField * pSpecificInstrument, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		std::cout << "=====订阅行情成功=====" << std::endl;
		std::cout << "合约代码： " << pSpecificInstrument->InstrumentID << std::endl;
		
		string dbname;
		string dbpre;
		string instrumentId = pSpecificInstrument->InstrumentID;

	
	}

}
///深度行情验证应答
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
		////判断交易时间是否合法
		string pre = pDepthMarketData->InstrumentID;//交易合约
		int position = StringOpera::FindFirstChar(pre);
		pre = pre.substr(0, position);
		_strupr(const_cast<char*>(pre.c_str()));
		string time = pDepthMarketData->UpdateTime;
		if (IsTraderTime==false)
		{
			if ((ConnectTime > "01:00:00"&&ConnectTime < "09:00:00"))
			{
				if (time > ConnectTime && time< "09:01:00")  //处理早盘重新连接
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

	strcpy(ctptick->InstrumentID, pDepthMarketData->InstrumentID); //合约代码
	strcpy(ctptick->ExchangeID,pDepthMarketData->ExchangeID); //交易所代码
	strcpy(ctptick->ExchangeInstID, pDepthMarketData->ExchangeInstID);//合约在交易所的代码
	ctptick->LastPrice = pDepthMarketData->LastPrice;  //最新价
	ctptick->PreSettlementPrice = pDepthMarketData->PreSettlementPrice;//上次结算价
	ctptick->PreClosePrice = pDepthMarketData->PreClosePrice;//昨收盘
	ctptick->PreOpenInterest = pDepthMarketData->PreOpenInterest;//昨持仓量
	ctptick->OpenPrice = pDepthMarketData->OpenPrice;//今开盘
	ctptick->HighestPrice = pDepthMarketData->HighestPrice;//最高价
	ctptick->LowestPrice = pDepthMarketData->LowestPrice;//最低价
	ctptick->Volume = pDepthMarketData->Volume;//数量
	ctptick->Turnover = pDepthMarketData->Turnover;//成交金额
	ctptick->OpenInterest = pDepthMarketData->OpenInterest;//持仓量

	ctptick->ClosePrice = 0;//今收盘
	ctptick->SettlementPrice = 0;//本次结算价
	if (pDepthMarketData->LowerLimitPrice <= pDepthMarketData->ClosePrice&&pDepthMarketData->ClosePrice <= pDepthMarketData->UpperLimitPrice)
	{
		ctptick->ClosePrice = pDepthMarketData->ClosePrice;//今收盘 
	}
	if (pDepthMarketData->SettlementPrice < 10000) //test
	{
		ctptick->SettlementPrice = pDepthMarketData->SettlementPrice;//本次结算价
	}
	
	ctptick->UpperLimitPrice = pDepthMarketData->UpperLimitPrice;//涨停板价
	ctptick->LowerLimitPrice = pDepthMarketData->LowerLimitPrice;//跌停板价
	
	//ctptick->PreDelta = pDepthMarketData->PreDelta;//昨虚实度
	//ctptick->CurrDelta = pDepthMarketData->CurrDelta;//今虚实度

	ctptick->PreDelta = 0;//昨虚实度
	ctptick->CurrDelta = 0;//今虚实度

	ctptick->BidPrice1 = pDepthMarketData->BidPrice1;//申买价一
	ctptick->BidVolume1 = pDepthMarketData->BidVolume1;//申买量一
	ctptick->AskPrice1 = pDepthMarketData->AskPrice1;//申卖价一
	ctptick->AskVolume1 = pDepthMarketData->AskVolume1;//申卖量一

	ctptick->BidPrice2 = 0;//申买价二
	ctptick->BidVolume2 = 0;//申买量二
	ctptick->AskPrice2 =0;//申卖价二
	ctptick->AskVolume2 = 0;//申卖量二

	ctptick->BidPrice3 = 0;//申买价三
	ctptick->BidVolume3 = 0;//申买量三
	ctptick->AskPrice3 = 0;//申卖价三
	ctptick->AskVolume3 = 0;//申卖量三

	ctptick->BidPrice4 = 0;//申买价四
	ctptick->BidVolume4 = 0;//申买量四
	ctptick->AskPrice4 = 0;//申卖价四
	ctptick->AskVolume4 = 0;//申卖量四

	ctptick->BidPrice5 = 0;//申买价五
	ctptick->BidVolume5 = 0;//申买量五
	ctptick->AskPrice5 = 0;//申卖价五
	ctptick->AskVolume5 = 0;//申卖量五

	if (strcmp(pDepthMarketData->ExchangeID, "SHFE") == 0 || (pDepthMarketData->ExchangeID, "INE") == 0)
	{

		ctptick->BidPrice2 = pDepthMarketData->BidPrice2;//申买价二
		ctptick->BidVolume2 = pDepthMarketData->BidVolume2;//申买量二
		ctptick->AskPrice2 = pDepthMarketData->AskPrice2;//申卖价二
		ctptick->AskVolume2 = pDepthMarketData->AskVolume2;//申卖量二

		ctptick->BidPrice3 = pDepthMarketData->BidPrice3;//申买价三
		ctptick->BidVolume3 = pDepthMarketData->BidVolume3;//申买量三
		ctptick->AskPrice3 = pDepthMarketData->AskPrice3;//申卖价三
		ctptick->AskVolume3 = pDepthMarketData->AskVolume3;//申卖量三

		ctptick->BidPrice4 = pDepthMarketData->BidPrice4;//申买价四
		ctptick->BidVolume4 = pDepthMarketData->BidVolume4;//申买量四
		ctptick->AskPrice4 = pDepthMarketData->AskPrice4;//申卖价四
		ctptick->AskVolume4 = pDepthMarketData->AskVolume4;//申卖量四

		ctptick->BidPrice5 = pDepthMarketData->BidPrice5;//申买价五
		ctptick->BidVolume5 = pDepthMarketData->BidVolume5;//申买量五
		ctptick->AskPrice5 = pDepthMarketData->AskPrice5;//申卖价五
		ctptick->AskVolume5 = pDepthMarketData->AskVolume5;//申卖量五

	}

	ProductTime(pDepthMarketData->ExchangeID,pDepthMarketData->TradingDay, pDepthMarketData->ActionDay, pDepthMarketData->UpdateTime, pDepthMarketData->UpdateMillisec, ctptick->TradingDay, ctptick->local);
}

void CCustomMdSpi::ProductTime(const char* ExchangeID, const char * CTPtradeDay, const char *CTPActionDay, const char * CTPupdatetime,int millsec, char * ticktradeDay, char * local)
{
	if (CTPtradeDay != nullptr&&CTPupdatetime != nullptr&&CTPupdatetime != nullptr&&strcmp(CTPtradeDay,"")!=0)
	{
		int tr_year, tr_month, tr_day, ac_year, ac_month,ac_day,hour,min,second,Mins;
		//将数据格式化处理
		sscanf(CTPtradeDay,"%04d%02d%02d",&tr_year,&tr_month,&tr_day);

		sscanf(CTPActionDay, "%04d%02d%02d", &ac_year, &ac_month, &ac_day);
		sscanf(CTPupdatetime, "%02d:%02d:%02d", &hour, &min, &second);
		sscanf(to_string(millsec).c_str(), "%03d", &Mins);

		sprintf(ticktradeDay, "%04d/%02d/%02d", tr_year, tr_month, tr_day); //精确到年月日
		SYSTEMTIME st;
		GetLocalTime(&st);
		//sprintf(updateTime, "%04d/%02d/%02d %02d:%02d", ac_year, ac_month, ac_day,hour,min); //精确到年月日时分
		sprintf(local, "%04d/%02d/%02d %02d:%02d:%02d.%03d", st.wYear, st.wMonth, st.wDay, hour, min, second, Mins);//精确到毫秒

		if (strcmp(ExchangeID,"CZCE")==0)
		{
			
			sprintf(ticktradeDay, "%04d/%02d/%02d", st.wYear, st.wMonth, st.wDay);

			TimeDeal timedeal;
			int week = timedeal.GetDayOfWeek(ticktradeDay); //判断今天是周几

			if (week == 5 || week == 6) {
				if (hour > 15) { //周五 晚上 交易日为周一 加三天
					char descdate[35];
					timedeal.char_AddTime(ticktradeDay, descdate, 3 * 24 * 60 * 60, 0);
					strcpy(ticktradeDay, descdate);
				}
				else if (hour >= 0 && hour < 9 && week == 6) { //周五过零点 即周六 加两天 
					char descdate[35];
					timedeal.char_AddTime(ticktradeDay, descdate, 2 * 24 * 60 * 60, 0);
					strcpy(ticktradeDay, descdate);
				}
				//week=5 and 过零点 代表是周四过来的
			}
			else {
				if (hour > 15) { //平时晚上交易日加一天
					char descdate[35];
					timedeal.char_AddTime(ticktradeDay, descdate, 24 * 60 * 60, 0);
					strcpy(ticktradeDay, descdate);
				}
			}

		}
		
	}

}
//将数据插入到数据库
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



