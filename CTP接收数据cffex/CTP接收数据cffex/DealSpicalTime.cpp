#include "DealSpicalTime.h"



DealSpicalTime::DealSpicalTime()
{   /*=======================shfe==============================*/
	//品种为rb的
	string  type = "RB";
	map<string, string>  rb_Spical = { {"11:00", "11:30" },{"13:30", "14:30"},{"14:30", "15:00"} };
	map<string, string> rb_filter = { {"15:00:10","20:59:50"},{"23:00:10","23:59:50"},{"00:00:00","08:59:50"},{"11:30:10","13:29:50"} };
	vector<string> rb_close = { "11:30","15:00","23:00" };
	Spical_time.insert(make_pair(type, rb_Spical));
	Dirty_time.insert(make_pair(type,rb_filter));
	Close_time.insert(make_pair(type, rb_close));
	//品种为 cu的
	type = "CU";
	map<string, string>  cu_Spical = { {"11:00", "11:30" },{"13:30", "14:30"},{"14:30", "15:00"} };
	map<string, string> cu_filter = { { "15:00:10","20:59:50" },{ "01:00:10","08:59:50" },{ "11:30:10","13:29:50"}};
	vector<string> cu_close = { "11:30","15:00","01:00" };
	Spical_time.insert(make_pair(type, cu_Spical));
	Dirty_time.insert(make_pair(type,cu_filter));
	Close_time.insert(make_pair(type, cu_close));
	//品种为
	/*=======================dce===============================*/
	type = "JM";
	map<string, string>  jm_Spical = { {"11:00", "11:30" },{"13:30", "14:30"},{"14:30", "15:00"},{ "23:00", "23:30"}};
	map<string, string>jm_filter = { { "15:00:10","20:59:50" },{ "23:30:10","23:59:50" },{ "00.00.00","08:59:50" },{ "11:30:10","13:29:50"} };
	vector<string> jm_close = { "11:30","15:00","23:30" };
	Spical_time.insert(make_pair(type, jm_Spical));
	Dirty_time.insert(make_pair(type, jm_filter));
	Close_time.insert(make_pair(type, jm_close));
	type = "I";
	map<string, string>  i_Spical = { {"11:00", "11:30" },{"13:30", "14:30"},{"14:30", "15:00"},{ "23:00", "23:30"} };
	map<string, string>i_filter = { {"15:00:10","20:59:50" },{ "23:30:10","23:59:50" },{ "00.00.00","08:59:50" },{ "11:30:10","13:29:50"} };
	vector<string> i_close = { "11:30","15:00","23:30" };
	Spical_time.insert(make_pair(type, i_Spical));
	Dirty_time.insert(make_pair(type, i_filter));
	Close_time.insert(make_pair(type, i_close));

	/*======================zce================================*/
	type = "FG";
	map<string, string>  fg_Spical = { {"11:00", "11:30" },{"13:30", "14:30"},{"14:30", "15:00"},{ "23:00", "23:30"} };
	map<string, string>fg_filter = { {"15:00:10","20:59:50" },{ "23:30:10","23:59:50" },{ "00.00.00","08:59:50" },{ "11:30:10","13:29:50"} };
	vector<string> fg_close = { "11:30","15:00","23:30" };
	Spical_time.insert(make_pair(type, fg_Spical));
	Dirty_time.insert(make_pair(type, fg_filter));
	Close_time.insert(make_pair(type, fg_close));
	type = "SR";
	map<string, string>  sr_Spical = { {"11:00", "11:30" },{"13:30", "14:30"},{"14:30", "15:00"},{ "23:00", "23:30"} };
	map<string, string>sr_filter = { {"15:00:10","20:59:50" },{ "23:30:10","23:59:50" },{ "00.00.00","08:59:50" },{ "11:30:10","13:29:50"} };
	vector<string> sr_close = { "11:30","15:00","23:30" };
	Spical_time.insert(make_pair(type, sr_Spical));
	Dirty_time.insert(make_pair(type, sr_filter));
	Close_time.insert(make_pair(type, sr_close));
	/*====================cffex================================*/
	type = "IC";
	map<string, string>  ic_Spical = { { "09:30", "10:30" },{ "10:30", "11:30" } };
	map<string, string> ic_filter = { { "15:00:10","23:59:50" },{ "00.00.00","09:29:50" },{ "11:30:10","12:59:50" } };
	vector<string> ic_close = { "11:30","15:00" };
	Spical_time.insert(make_pair(type, ic_Spical));
	Dirty_time.insert(make_pair(type,ic_filter));
	Close_time.insert(make_pair(type,ic_close));
	type = "IH";
	map<string, string>  ih_Spical = { { "09:30", "10:30" },{ "10:30", "11:30" } };
	map<string, string> ih_filter = { { "15:00:10","23:59:50" },{ "00.00.00","09:29:50" },{ "11:30:10","12:59:50" } };
	vector<string> ih_close = { "11:30","15:00" };
	Spical_time.insert(make_pair(type, ih_Spical));
	Dirty_time.insert(make_pair(type, ih_filter));
	Close_time.insert(make_pair(type, ih_close));
	type = "IF";
	map<string, string>  if_Spical = { { "09:30", "10:30" },{ "10:30", "11:30" } };
	map<string, string> if_filter = { { "15:00:10","23:59:50" },{ "00.00.00","09:29:50" },{ "11:30:10","12:59:50" } };
	vector<string> if_close = { "11:30","15:00" };
	Spical_time.insert(make_pair(type, if_Spical));
	Dirty_time.insert(make_pair(type, if_filter));
	Close_time.insert(make_pair(type, if_close));

	/*======================ine=================================*/
	type = "SC";
	map<string, string>  sc_Spical = { { "11:00", "11:30" },{ "13:30", "14:30" },{ "14:30", "15:00" },{ "02:00", "02:30" } };
	map<string, string> sc_filtrer = { { "15:00:10","20:59:50" },{ "02:30:10","08:59:50" },{ "11:30:10","13:29:50" } };
	vector<string> sc_close = { "11:30","15:00","02:30" };
	Spical_time.insert(make_pair(type, sc_Spical));
	Dirty_time.insert(make_pair(type, sc_filtrer));
	Close_time.insert(make_pair(type, sc_close));
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
		//std::cout << Closetime << std::endl;
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
