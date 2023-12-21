#include "DealSpicalTime.h"



DealSpicalTime::DealSpicalTime()
{   
	//全品种
    //特殊时间组合

	/*==================和螺纹钢相同时间点的==================*/
	map<string, string>  rb_Spical = { {"11:00", "11:30" },{"13:30", "14:30"},{"14:30", "15:00"} };
	map<string, string> rb_filter = { {"15:00:10","20:59:50"},{"23:00:10","23:59:50"},{"00:00:00","08:59:50"},{"11:30:10","13:29:50"} };
	vector<string> rb_close = { "11:30","15:00","23:00" };
	//螺纹钢
	Spical_time.insert(make_pair("RB", rb_Spical));
	Dirty_time.insert(make_pair("RB", rb_filter));
	Close_time.insert(make_pair("RB", rb_close));
	//轧卷板
	Spical_time.insert(make_pair("HC", rb_Spical));
	Dirty_time.insert(make_pair("HC", rb_filter));
	Close_time.insert(make_pair("HC", rb_close));
	//沥青
	Spical_time.insert(make_pair("BU", rb_Spical));
	Dirty_time.insert(make_pair("BU", rb_filter));
	Close_time.insert(make_pair("BU", rb_close));
	//橡胶
	Spical_time.insert(make_pair("RU", rb_Spical));
	Dirty_time.insert(make_pair("RU", rb_filter));
	Close_time.insert(make_pair("RU", rb_close));
	//纸浆
	Spical_time.insert(make_pair("SP", rb_Spical));
	Dirty_time.insert(make_pair("SP", rb_filter));
	Close_time.insert(make_pair("SP", rb_close));
	
	//铁矿石
	Spical_time.insert(make_pair("I", rb_Spical));
	Dirty_time.insert(make_pair("I", rb_filter));
	Close_time.insert(make_pair("I", rb_close));
	//焦炭
	Spical_time.insert(make_pair("J", rb_Spical));
	Dirty_time.insert(make_pair("J", rb_filter));
	Close_time.insert(make_pair("J", rb_close));
	//焦煤
	Spical_time.insert(make_pair("JM", rb_Spical));
	Dirty_time.insert(make_pair("JM", rb_filter));
	Close_time.insert(make_pair("JM", rb_close));
	//豆粕
	Spical_time.insert(make_pair("M", rb_Spical));
	Dirty_time.insert(make_pair("M", rb_filter));
	Close_time.insert(make_pair("M", rb_close));
	//玉米
	Spical_time.insert(make_pair("C", rb_Spical));
	Dirty_time.insert(make_pair("C", rb_filter));
	Close_time.insert(make_pair("C", rb_close));
	//塑料
	Spical_time.insert(make_pair("L", rb_Spical));
	Dirty_time.insert(make_pair("L", rb_filter));
	Close_time.insert(make_pair("L", rb_close));
	//聚氯乙烯
	Spical_time.insert(make_pair("V", rb_Spical));
	Dirty_time.insert(make_pair("V", rb_filter));
	Close_time.insert(make_pair("V", rb_close));
	//豆油
	Spical_time.insert(make_pair("Y", rb_Spical));
	Dirty_time.insert(make_pair("Y", rb_filter));
	Close_time.insert(make_pair("Y", rb_close));
	//黄大豆一号
	Spical_time.insert(make_pair("A", rb_Spical));
	Dirty_time.insert(make_pair("A", rb_filter));
	Close_time.insert(make_pair("A", rb_close));
	//黄大豆二号
	Spical_time.insert(make_pair("B", rb_Spical));
	Dirty_time.insert(make_pair("B", rb_filter));
	Close_time.insert(make_pair("B", rb_close));
	//聚丙烯
	Spical_time.insert(make_pair("PP", rb_Spical));
	Dirty_time.insert(make_pair("PP", rb_filter));
	Close_time.insert(make_pair("PP", rb_close));
	//淀粉
	Spical_time.insert(make_pair("CS", rb_Spical));
	Dirty_time.insert(make_pair("CS", rb_filter));
	Close_time.insert(make_pair("CS", rb_close));
	//液化气
	Spical_time.insert(make_pair("PG", rb_Spical));
	Dirty_time.insert(make_pair("PG", rb_filter));
	Close_time.insert(make_pair("PG", rb_close));
	//乙二醇
	Spical_time.insert(make_pair("EG", rb_Spical));
	Dirty_time.insert(make_pair("EG", rb_filter));
	Close_time.insert(make_pair("EG", rb_close));
	//燃油
	Spical_time.insert(make_pair("FU", rb_Spical));
	Dirty_time.insert(make_pair("FU", rb_filter));
	Close_time.insert(make_pair("FU", rb_close));
	//纤维板
	Spical_time.insert(make_pair("FB", rb_Spical));
	Dirty_time.insert(make_pair("FB", rb_filter));
	Close_time.insert(make_pair("FB", rb_close));
	//粳米
	Spical_time.insert(make_pair("RR", rb_Spical));
	Dirty_time.insert(make_pair("RR", rb_filter));
	Close_time.insert(make_pair("RR", rb_close));
	//胶合板
	Spical_time.insert(make_pair("BB", rb_Spical));
	Dirty_time.insert(make_pair("BB", rb_filter));
	Close_time.insert(make_pair("BB", rb_close));
	//鸡蛋
	Spical_time.insert(make_pair("JD", rb_Spical));
	Dirty_time.insert(make_pair("JD", rb_filter));
	Close_time.insert(make_pair("JD", rb_close));
	//苯乙烯
	Spical_time.insert(make_pair("EB", rb_Spical));
	Dirty_time.insert(make_pair("EB", rb_filter));
	Close_time.insert(make_pair("EB", rb_close));
	//低硫燃油
	Spical_time.insert(make_pair("LU", rb_Spical));
	Dirty_time.insert(make_pair("LU", rb_filter));
	Close_time.insert(make_pair("LU", rb_close));
	//20号胶
	Spical_time.insert(make_pair("NR", rb_Spical));
	Dirty_time.insert(make_pair("NR", rb_filter));
	Close_time.insert(make_pair("NR", rb_close));
	//棉花
	Spical_time.insert(make_pair("CF", rb_Spical));
	Dirty_time.insert(make_pair("CF", rb_filter));
	Close_time.insert(make_pair("CF", rb_close));
	//棉纱
	Spical_time.insert(make_pair("CY", rb_Spical));
	Dirty_time.insert(make_pair("CY", rb_filter));
	Close_time.insert(make_pair("CY", rb_close));
	//玻璃
	Spical_time.insert(make_pair("FG", rb_Spical));
	Dirty_time.insert(make_pair("FG", rb_filter));
	Close_time.insert(make_pair("FG", rb_close));
	//白糖
	Spical_time.insert(make_pair("SR", rb_Spical));
	Dirty_time.insert(make_pair("SR", rb_filter));
	Close_time.insert(make_pair("SR", rb_close));
	//PTA
	Spical_time.insert(make_pair("TA", rb_Spical));
	Dirty_time.insert(make_pair("TA", rb_filter));
	Close_time.insert(make_pair("TA", rb_close));
	//甲醇
	Spical_time.insert(make_pair("MA", rb_Spical));
	Dirty_time.insert(make_pair("MA", rb_filter));
	Close_time.insert(make_pair("MA", rb_close));
	//菜油
	Spical_time.insert(make_pair("OI", rb_Spical));
	Dirty_time.insert(make_pair("OI", rb_filter));
	Close_time.insert(make_pair("OI", rb_close));
	//短纤
	Spical_time.insert(make_pair("PF", rb_Spical));
	Dirty_time.insert(make_pair("PF", rb_filter));
	Close_time.insert(make_pair("PF", rb_close));
	//菜粕
	Spical_time.insert(make_pair("RM", rb_Spical));
	Dirty_time.insert(make_pair("RM", rb_filter));
	Close_time.insert(make_pair("RM", rb_close));
	//纯碱
	Spical_time.insert(make_pair("SA", rb_Spical));
	Dirty_time.insert(make_pair("SA", rb_filter));
	Close_time.insert(make_pair("SA", rb_close));
	//动力煤
	Spical_time.insert(make_pair("ZC", rb_Spical));
	Dirty_time.insert(make_pair("ZC", rb_filter));
	Close_time.insert(make_pair("ZC", rb_close));
	//棕榈
	Spical_time.insert(make_pair("P", rb_Spical));
	Dirty_time.insert(make_pair("P", rb_filter));
	Close_time.insert(make_pair("P", rb_close));
	
	/*==================和铜相同时间点的==================*/
	map<string, string>  cu_Spical = { {"11:00", "11:30" },{"13:30", "14:30"},{"14:30", "15:00"} };
	map<string, string> cu_filter = { { "15:00:10","20:59:50" },{ "01:00:10","08:59:50" },{ "11:30:10","13:29:50"} };
	vector<string> cu_close = { "11:30","15:00","01:00" };
	//铜
	Spical_time.insert(make_pair("CU", cu_Spical));
	Dirty_time.insert(make_pair("CU", cu_filter));
	Close_time.insert(make_pair("CU", cu_close));
	//国际铜
	Spical_time.insert(make_pair("BC", cu_Spical));
	Dirty_time.insert(make_pair("BC", cu_filter));
	Close_time.insert(make_pair("BC", cu_close));
	//铝
	Spical_time.insert(make_pair("AL", cu_Spical));
	Dirty_time.insert(make_pair("AL", cu_filter));
	Close_time.insert(make_pair("AL", cu_close));
	//锡
	Spical_time.insert(make_pair("SN", cu_Spical));
	Dirty_time.insert(make_pair("SN", cu_filter));
	Close_time.insert(make_pair("SN", cu_close));
	//镍
	Spical_time.insert(make_pair("NI", cu_Spical));
	Dirty_time.insert(make_pair("NI", cu_filter));
	Close_time.insert(make_pair("NI", cu_close));
	//铅
	Spical_time.insert(make_pair("PB", cu_Spical));
	Dirty_time.insert(make_pair("PB", cu_filter));
	Close_time.insert(make_pair("PB", cu_close));
	//锌
	Spical_time.insert(make_pair("ZN", cu_Spical));
	Dirty_time.insert(make_pair("ZN", cu_filter));
	Close_time.insert(make_pair("ZN", cu_close));
	//不锈钢
	Spical_time.insert(make_pair("SS", cu_Spical));
	Dirty_time.insert(make_pair("SS", cu_filter));
	Close_time.insert(make_pair("SS", cu_close));

	
	/*==================和苹果相同时间点的==================*/
	map<string, string>  ap_Spical = { { "11:00", "10:30" },{"13:30", "14:30"},{"14:30", "15:00"} };
	map<string, string> ap_filter = { { "15:00:10","23:59:50" },{ "00.00.00","08:59:50" },{ "11:30:10","13:29:50" } };
	vector<string> ap_close = { "11:30","15:00" };

	//苹果
	Spical_time.insert(make_pair("AP", ap_Spical));
	Dirty_time.insert(make_pair("AP", ap_filter));
	Close_time.insert(make_pair("AP", ap_close));
	//线材
	Spical_time.insert(make_pair("WR", ap_Spical));
	Dirty_time.insert(make_pair("WR", ap_filter));
	Close_time.insert(make_pair("WR", ap_close));
	//红枣
	Spical_time.insert(make_pair("CJ", ap_Spical));
	Dirty_time.insert(make_pair("CJ", ap_filter));
	Close_time.insert(make_pair("CJ", ap_close));
	//粳稻
	Spical_time.insert(make_pair("JR", ap_Spical));
	Dirty_time.insert(make_pair("JR", ap_filter));
	Close_time.insert(make_pair("JR", ap_close));
	//晚籼稻
	Spical_time.insert(make_pair("LR", ap_Spical));
	Dirty_time.insert(make_pair("LR", ap_filter));
	Close_time.insert(make_pair("LR", ap_close));
	//早籼稻
	Spical_time.insert(make_pair("RI", ap_Spical));
	Dirty_time.insert(make_pair("RI", ap_filter));
	Close_time.insert(make_pair("RI", ap_close));
	//普麦
	Spical_time.insert(make_pair("PM", ap_Spical));
	Dirty_time.insert(make_pair("PM", ap_filter));
	Close_time.insert(make_pair("PM", ap_close));
	//菜籽
	Spical_time.insert(make_pair("RS", ap_Spical));
	Dirty_time.insert(make_pair("RS", ap_filter));
	Close_time.insert(make_pair("RS", ap_close));
	//硅铁
	Spical_time.insert(make_pair("SF", ap_Spical));
	Dirty_time.insert(make_pair("SF", ap_filter));
	Close_time.insert(make_pair("SF", ap_close));
	//锰硅
	Spical_time.insert(make_pair("SM", ap_Spical));
	Dirty_time.insert(make_pair("SM", ap_filter));
	Close_time.insert(make_pair("SM", ap_close));
	//菜粕
	Spical_time.insert(make_pair("RM", ap_Spical));
	Dirty_time.insert(make_pair("RM", ap_filter));
	Close_time.insert(make_pair("RM", ap_close));
	//尿素
	Spical_time.insert(make_pair("UR", ap_Spical));
	Dirty_time.insert(make_pair("UR", ap_filter));
	Close_time.insert(make_pair("UR", ap_close));
	//强麦
	Spical_time.insert(make_pair("WH", ap_Spical));
	Dirty_time.insert(make_pair("WH", ap_filter));
	Close_time.insert(make_pair("WH", ap_close));
	//生猪
	Spical_time.insert(make_pair("LH", ap_Spical));
	Dirty_time.insert(make_pair("LH", ap_filter));
	Close_time.insert(make_pair("LH", ap_close));
	//花生
	Spical_time.insert(make_pair("PK", ap_Spical));
	Dirty_time.insert(make_pair("PK", ap_filter));
	Close_time.insert(make_pair("PK", ap_close));
	/*==================和if相同时间点的==================*/
	map<string, string>  if_Spical = { { "09:30", "10:30" },{ "10:30", "11:30" } };
	map<string, string> if_filter = { { "15:00:10","23:59:50" },{ "00.00.00","09:29:50" },{ "11:30:10","12:59:50" } };
	vector<string> if_close = { "11:30","15:00" };
	//沪深300股指期货
	Spical_time.insert(make_pair("IF", if_Spical));
	Dirty_time.insert(make_pair("IF", if_filter));
	Close_time.insert(make_pair("IF", if_close));
	//中证500股指期货
	Spical_time.insert(make_pair("IC", if_Spical));
	Dirty_time.insert(make_pair("IC", if_filter));
	Close_time.insert(make_pair("IC", if_close));
	//上证50股指期货
	Spical_time.insert(make_pair("IH", if_Spical));
	Dirty_time.insert(make_pair("IH", if_filter));
	Close_time.insert(make_pair("IH", if_close));

	/*==================和国债期货相同时间点的==================*/
	map<string, string>  t_Spical = { { "09:15", "10:30" },{ "10:30", "11:30" } };
	map<string, string> t_filter = { { "15:15:10","23:59:50" },{ "00.00.00","09:14:50" },{ "11:30:10","12:59:50" } };
	vector<string> t_close = { "11:30","15:15" };
	//2年期国债期货
	Spical_time.insert(make_pair("TS", t_Spical));
	Dirty_time.insert(make_pair("TS", t_filter));
	Close_time.insert(make_pair("TS", t_close));
	//5年期国债期货
	Spical_time.insert(make_pair("TF", t_Spical));
	Dirty_time.insert(make_pair("TF", t_filter));
	Close_time.insert(make_pair("TF", t_close));
	//10年期国债期货
	Spical_time.insert(make_pair("T", t_Spical));
	Dirty_time.insert(make_pair("T", t_filter));
	Close_time.insert(make_pair("T", t_close));
	
	/*==================和原油相同时间点的==================*/

	map<string, string>  sc_Spical = { { "11:00", "11:30" },{ "13:30", "14:30" },{ "14:30", "15:00" },{ "02:00", "02:30" } };
	map<string, string> sc_filtrer = { { "15:00:10","20:59:50" },{ "02:30:10","08:59:50" },{ "11:30:10","13:29:50" } };
	vector<string> sc_close = { "11:30","15:00","02:30" };
	//原油
	Spical_time.insert(make_pair("SC", sc_Spical));
	Dirty_time.insert(make_pair("SC", sc_filtrer));
	Close_time.insert(make_pair("SC", sc_close));
	//黄金
	Spical_time.insert(make_pair("AU", sc_Spical));
	Dirty_time.insert(make_pair("AU", sc_filtrer));
	Close_time.insert(make_pair("AU", sc_close));
	//白银
	Spical_time.insert(make_pair("AG", sc_Spical));
	Dirty_time.insert(make_pair("AG", sc_filtrer));
	Close_time.insert(make_pair("AG", sc_close));
	
	
}


bool DealSpicalTime::FindisinDirty(string pre, string time)
{
	if (Dirty_time.find(pre) == Dirty_time.end())
	{
		return true;
	}
	else
	{
		map<string,string>::iterator  m_iter = Dirty_time.find(pre)->second.begin();
		for (m_iter; m_iter != Dirty_time.find(pre)->second.end(); m_iter++)
		{
			if (m_iter->first < time && time < m_iter->second)
			{
				return true;
			}
		}
		return false;
	}
	return true;
}

bool DealSpicalTime::FindisinSpical(string pre, string time, string &Spicaltime)
{
	if (Spical_time.find(pre) == Spical_time.end())
	{
		return true;
	}
	else
	{
		map<string, string>::iterator  m_iter = Spical_time.find(pre)->second.begin();
		for (m_iter; m_iter != Spical_time.find(pre)->second.end(); m_iter++)
		{
			if (m_iter->first < time && time < m_iter->second)
			{
				Spicaltime = m_iter->second;
				return true;
			}
		}
		return false;
	}
	return true;
}

bool DealSpicalTime::FindisinClose(string pre, string time, string &Closetime)
{
	if (Close_time.find(pre) == Close_time.end())
	{
		return true;
	}
	else
	{
		vector<string>::iterator iter = (Close_time.find(pre)->second).begin();
		for (iter; iter != (Close_time.find(pre)->second).end(); iter++)
		{
			if (time == (*iter))
			{
				Closetime = (*iter);
				return true;
			}
		}
		Closetime = "";
		return false;
	}

}

bool DealSpicalTime::JudgeLocatimeAndupdateTimeisEqual(char * updateTime)
{
	
		SYSTEMTIME LocalTlime;
		GetLocalTime(&LocalTlime);
		char local[512];
		sprintf(local, "%02d:%02d", LocalTlime.wHour, LocalTlime.wMinute);
		if (strcmp(local, updateTime) == 0)
			return true;
		else
			return false;
	

}

DealSpicalTime::~DealSpicalTime()
{
}
