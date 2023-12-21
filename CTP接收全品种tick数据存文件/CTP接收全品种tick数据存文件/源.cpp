#include "CCustomMdSpi.h"
#include "CCustomTraderSpi.h"
#include "DealSpicalTime.h"
#include <iostream>
#include <vector>
#include <map>
#include <mutex>
using namespace std;
// 链接库
#pragma comment (lib, "thostmduserapi_se.lib") //加载CTP动态库
#pragma comment (lib, "thosttraderapi_se.lib")
#pragma comment (lib,"libmysql.lib")    //加载数据库动态库
/*==========================全局变量=======================*/
//交易参数
CThostFtdcTraderApi *TraderApi;
//行情参数
CThostFtdcMdApi *mdApi;
// 行情合约代码列表
//char *pInstrumentID[200] = {};// 行情合约代码列表，中、上、大、郑交易所各选一种
volatile int singalnum=0; //全局变量用于进程间的通信

mutex pInstrument_Mutex;//订阅行情合约代码锁
// 行情合约订阅数量
int instrumentNum = 0;
//文件路径
//char filePath[100] = { '\0' };
//行情交易前置地址
char mdfront_addr[] = MDFRONT_ADDR;
//交易前置地址
char traderfront[] = TRADERFRONT_ADDR;

//特殊时间处理类
DealSpicalTime  dealspicaltime;
mutex Dealspicaltime_Mutex;//处理特殊时间所用的锁
map<string, string> m_instrument2Exchange;//合约和交易所之间的映射
mutex instrument2dbname_Mutex;//处理合约和数据库映射关系所用的锁

//vector<string> Path = { "E:/MarketData/SHFE/","E:/MarketData/CFFEX/","E:/MarketData/INE/","E:/MarketData/CZCE/","E:/MarketData/DCE/" };
//char targetpath[] = "../MarketData/";  //用于存放文件的路径
char targetpath[] = "E:/MarketData/";  //用于存放文件的路径
vector<string> Ins = {};
int main()
{

	/*   订阅所有合约的数据，需要从Trader接口查询所有合约
     	 然后从MdSpi接口进行订阅
	*/
	////上海期货交易所
	//m_instrument2dbname.insert(make_pair("sn", "shfe_tick")); //沪锡
	//m_instrument2dbname.insert(make_pair("al", "shfe_tick")); //沪铝
	//m_instrument2dbname.insert(make_pair("ni", "shfe_tick")); //沪镍
	//m_instrument2dbname.insert(make_pair("zn", "shfe_tick")); //沪锌
	//m_instrument2dbname.insert(make_pair("pb", "shfe_tick")); //沪铅
	//m_instrument2dbname.insert(make_pair("sp", "shfe_tick")); //纸浆
	//m_instrument2dbname.insert(make_pair("ss", "shfe_tick")); //不锈钢
	//m_instrument2dbname.insert(make_pair("hc", "shfe_tick")); //轧卷板
	//m_instrument2dbname.insert(make_pair("fu", "shfe_tick")); //燃油
	//m_instrument2dbname.insert(make_pair("bu", "shfe_tick")); //沥青
	//m_instrument2dbname.insert(make_pair("wr", "shfe_tick")); //线材
	//m_instrument2dbname.insert(make_pair("au", "shfe_tick")); //黄金
	//m_instrument2dbname.insert(make_pair("ag", "shfe_tick")); //白银
	//m_instrument2dbname.insert(make_pair("ru", "shfe_tick")); //橡胶
	//m_instrument2dbname.insert(make_pair("rb", "shfe_tick"));  //螺纹钢
	//m_instrument2dbname.insert(make_pair("cu", "shfe_tick"));  //铜
	////上海能源期货交易所
	//m_instrument2dbname.insert(make_pair("sc", "ine_tick"));  //原油
	//m_instrument2dbname.insert(make_pair("bc", "ine_tick"));  //国际铜
	//m_instrument2dbname.insert(make_pair("lu", "ine_tick"));  //低硫燃油
	//m_instrument2dbname.insert(make_pair("nr", "ine_tick"));  //20号胶

	////大连期货交易所品种
	//m_instrument2dbname.insert(make_pair("j", "dce_tick"));  //焦炭
	//m_instrument2dbname.insert(make_pair("m", "dce_tick"));  //豆粕
	//m_instrument2dbname.insert(make_pair("c", "dce_tick"));  //玉米
	//m_instrument2dbname.insert(make_pair("i", "dce_tick"));  //铁矿石
	//m_instrument2dbname.insert(make_pair("l", "dce_tick"));  //塑料
	//m_instrument2dbname.insert(make_pair("v", "dce_tick"));  //聚氯乙烯
	//m_instrument2dbname.insert(make_pair("y", "dce_tick"));  //豆油
	//m_instrument2dbname.insert(make_pair("a", "dce_tick"));  //黄大豆一号
	//m_instrument2dbname.insert(make_pair("b", "dce_tick"));  //黄大豆二号
	//m_instrument2dbname.insert(make_pair("pp", "dce_tick"));  //聚丙烯
	//m_instrument2dbname.insert(make_pair("jm", "dce_tick"));  //焦煤
	//m_instrument2dbname.insert(make_pair("cs", "dce_tick"));  //淀粉
	//m_instrument2dbname.insert(make_pair("pg","dce_tick"));  //液化气
	//m_instrument2dbname.insert(make_pair("eg","dce_tick"));  //乙二醇	
	//m_instrument2dbname.insert(make_pair("fu", "dce_tick"));  //燃油
	//m_instrument2dbname.insert(make_pair("fb", "dce_tick"));  //纤维板
	//m_instrument2dbname.insert(make_pair("rr", "dce_tick"));  //粳米
	//m_instrument2dbname.insert(make_pair("bb", "dce_tick"));  //胶合板
	//m_instrument2dbname.insert(make_pair("jd", "dce_tick"));  //鸡蛋
	//m_instrument2dbname.insert(make_pair("eb", "dce_tick"));  //苯乙烯
	//
	//
	//

	////郑州期货交易所
	//m_instrument2dbname.insert(make_pair("AP", "zce_tick"));  //苹果
	//m_instrument2dbname.insert(make_pair("CF", "zce_tick"));  //棉花
	//m_instrument2dbname.insert(make_pair("CJ", "zce_tick"));  //红枣
	//m_instrument2dbname.insert(make_pair("CY", "zce_tick"));  //棉纱
	//m_instrument2dbname.insert(make_pair("FG", "zce_tick"));  //玻璃
	//m_instrument2dbname.insert(make_pair("SR", "zce_tick"));  //白糖
	//m_instrument2dbname.insert(make_pair("JR", "zce_tick"));  //粳稻
	//m_instrument2dbname.insert(make_pair("LR", "zce_tick"));  //晚籼稻
	//m_instrument2dbname.insert(make_pair("RI", "zce_tick"));  //早籼稻
	//m_instrument2dbname.insert(make_pair("TA", "zce_tick"));  //PTA
	//m_instrument2dbname.insert(make_pair("MA", "zce_tick"));  //甲醇
	//m_instrument2dbname.insert(make_pair("OI", "zce_tick"));  //菜油
	//m_instrument2dbname.insert(make_pair("PF", "zce_tick"));  //短纤
	//m_instrument2dbname.insert(make_pair("PM", "zce_tick"));  //普麦
	//m_instrument2dbname.insert(make_pair("RM", "zce_tick"));  //菜粕
	//m_instrument2dbname.insert(make_pair("RS", "zce_tick"));  //菜籽
	//m_instrument2dbname.insert(make_pair("SA", "zce_tick"));  //纯碱
	//m_instrument2dbname.insert(make_pair("SF", "zce_tick"));  //硅铁
	//m_instrument2dbname.insert(make_pair("SM", "zce_tick"));  //锰硅
	//m_instrument2dbname.insert(make_pair("UR", "zce_tick"));  //尿素
	//m_instrument2dbname.insert(make_pair("WH", "zce_tick"));  //强麦
	//m_instrument2dbname.insert(make_pair("ZC", "zce_tick"));  //动力煤

	////上海金融期货交易所
	//m_instrument2dbname.insert(make_pair("IF", "cffex_tick"));  //沪深300股指期货
	//m_instrument2dbname.insert(make_pair("IC", "cffex_tick"));  //中证500股指期货
	//m_instrument2dbname.insert(make_pair("IH", "cffex_tick"));  //上证50股指期货
	//m_instrument2dbname.insert(make_pair("TF", "cffex_tick"));  //5年国债期货
	//m_instrument2dbname.insert(make_pair("TS", "cffex_tick"));  //2年国债期货
	//m_instrument2dbname.insert(make_pair("T", "cffex_tick"));  //10年国债期货

	TraderApi = CThostFtdcTraderApi::CreateFtdcTraderApi();
	CCustomTraderSpi *TradeSpi = new CCustomTraderSpi();
	////入口

	TraderApi->RegisterSpi(TradeSpi);
	TraderApi->SubscribePublicTopic(THOST_TERT_QUICK);
	TraderApi->SubscribePrivateTopic(THOST_TERT_QUICK);
	TraderApi->RegisterFront(traderfront);
	

	//初始化行情线程
	cout << "初始化行情..." << endl;
	mdApi = CThostFtdcMdApi::CreateFtdcMdApi();   // 创建行情实例
	CThostFtdcMdSpi *pMdUserSpi = new CCustomMdSpi;  // 创建行情回调实例
	mdApi->RegisterSpi(pMdUserSpi);               // 注册事件类
	mdApi->RegisterFront(mdfront_addr);           // 设置行情前置地址

	TraderApi->Init();
	mdApi->Init();                                // 连接运行


	TraderApi->Join();
	delete TradeSpi;
	TraderApi->Release();
	

	mdApi->Join();
	delete pMdUserSpi;
	mdApi->Release();

	system("pause");
	return 0;
}