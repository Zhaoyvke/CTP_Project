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
static int Recconect_num = 0;//与CTP平台建立网络连接的次数

///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
void CCustomMdSpi::OnFrontConnected()
{ 
	cout << "=======建立网络连接成功========";

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

		m_Inst2filepath.clear();  //清空instrument to filepath 的键值map容器 

		if(Recconect_num==0)
		{
			m_thread = std::thread(&CCustomMdSpi::DealMarketData, this);  //开启线程看是否接收到tick
			Recconect_num++;
		}
		

		// 开始订阅行情
		int rt = mdApi->SubscribeMarketData(pInstrumentID, instrumentNum);
		if (!rt)
			std::cout << ">>>>>>发送订阅行情请求成功" << std::endl;
		else
			std::cerr << "--->>>发送订阅行情请求失败" << std::endl;
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
		// 如果需要存入文件或者数据库，在这里创建表头,不同的合约单独存储

	}

}
///深度行情验证应答
void CCustomMdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField * pDepthMarketData)
{

	cout << "=====获得深度行情=====" << endl;
	cout << "交易日： " << pDepthMarketData->TradingDay << endl;
	cout << "更新时间" << pDepthMarketData->UpdateTime << "." << pDepthMarketData->UpdateMillisec << endl;
	string trinday = pDepthMarketData->TradingDay;
	string  uptime = pDepthMarketData->UpdateTime;
	int mill = pDepthMarketData->UpdateMillisec;
	char timelocal[30];
	SYSTEMTIME exe_time;
	GetLocalTime(&exe_time);
	sprintf_s(timelocal, "%d/%02d/%02d %02d:%02d:%02d:%03d", exe_time.wYear, exe_time.wMonth, exe_time.wDay, exe_time.wHour, exe_time.wMinute, exe_time.wSecond, exe_time.wMilliseconds);
	string time1 = timelocal;
	string conne="本地时间:"+ time1+"交易日： " + trinday+"更新时间"+ uptime+"."+to_string(mill);
	//WriteLog::writeloginfo(conne);
	//判断交易时间是否合法
	string pre = pDepthMarketData->InstrumentID;//交易合约
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
		//	strcpy(Path, (m_Inst2filepath.find(pDepthMarketData->InstrumentID)->second).c_str());//copy 文件路径
		//}
		//else
		//{
		//	cerr << "未找到该合约码对应存储路径" << endl;
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

		//获取当前时间 (本地时间)
		time_t local = time(NULL);
		struct tm* slocaltime = localtime(&local);  //转换时间格式
		char CurrentTime[32];  //用来记录当前时间
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
		ticks.pop();//从队列的开头删除一个元素
		if (strcmp(tick->instumentId,"")!=0)
		{
			if (m_instrumentID2Ckline.find(tick->instumentId) != m_instrumentID2Ckline.end())
			{
				map<string, CTPDatatransForKline*>::iterator iter = m_instrumentID2Ckline.find(tick->instumentId);
				
				iter->second->CaltickkAndInsertDB(tick); 	//生成K线并保存入数据库
			}
			else
			{
				CTPDatatransForKline *ctptransfor = new CTPDatatransForKline(tick->instumentId);
				ctptransfor->CaltickkAndInsertDB(tick);	//生成K线并保存入数据库
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
		OutputDebugStringA("未找到与该品种匹配的交易所");
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
	tick->PreOpenInterest = pDepthMarketData->PreOpenInterest; //昨日持仓量
	tick->totalvolume= pDepthMarketData->Volume;
	tick->buyprice = pDepthMarketData->BidPrice1;//买一价
	tick->buyqty = pDepthMarketData->BidVolume1;//买一量
	tick->sellprice = pDepthMarketData->AskPrice1;//卖一价
	tick->sellqty = pDepthMarketData->AskVolume1;//卖一量

	ProductTime(pDepthMarketData->TradingDay, pDepthMarketData->ActionDay, pDepthMarketData->UpdateTime, pDepthMarketData->UpdateMillisec, tick->tradeDay, tick->updateTime, tick->local);
}

void CCustomMdSpi::ProductTime(const char * CTPtradeDay, const char *CTPActionDay, const char * CTPupdatetime,int millsec, char * ticktradeDay, char * updateTime, char * local)
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

		sprintf(updateTime, "%04d/%02d/%02d %02d:%02d", ac_year, ac_month, ac_day,hour,min); //精确到年月日时分
		sprintf(local,"%04d/%02d/%02d %02d:%02d:%02d.%03d", ac_year, ac_month, ac_day, hour, min, second, Mins);//精确到毫秒
	}

}


