#include "DealSpicalTime.h"



DealSpicalTime::DealSpicalTime()
{   
	//ȫƷ��
    //����ʱ�����

	/*==================�����Ƹ���ͬʱ����==================*/
	map<string, string>  rb_Spical = { {"11:00", "11:30" },{"13:30", "14:30"},{"14:30", "15:00"} };
	map<string, string> rb_filter = { {"15:00:10","20:59:50"},{"23:00:10","23:59:50"},{"00:00:00","08:59:50"},{"11:30:10","13:29:50"} };
	vector<string> rb_close = { "11:30","15:00","23:00" };
	//���Ƹ�
	Spical_time.insert(make_pair("RB", rb_Spical));
	Dirty_time.insert(make_pair("RB", rb_filter));
	Close_time.insert(make_pair("RB", rb_close));
	//�����
	Spical_time.insert(make_pair("HC", rb_Spical));
	Dirty_time.insert(make_pair("HC", rb_filter));
	Close_time.insert(make_pair("HC", rb_close));
	//����
	Spical_time.insert(make_pair("BU", rb_Spical));
	Dirty_time.insert(make_pair("BU", rb_filter));
	Close_time.insert(make_pair("BU", rb_close));
	//��
	Spical_time.insert(make_pair("RU", rb_Spical));
	Dirty_time.insert(make_pair("RU", rb_filter));
	Close_time.insert(make_pair("RU", rb_close));
	//ֽ��
	Spical_time.insert(make_pair("SP", rb_Spical));
	Dirty_time.insert(make_pair("SP", rb_filter));
	Close_time.insert(make_pair("SP", rb_close));
	
	//����ʯ
	Spical_time.insert(make_pair("I", rb_Spical));
	Dirty_time.insert(make_pair("I", rb_filter));
	Close_time.insert(make_pair("I", rb_close));
	//��̿
	Spical_time.insert(make_pair("J", rb_Spical));
	Dirty_time.insert(make_pair("J", rb_filter));
	Close_time.insert(make_pair("J", rb_close));
	//��ú
	Spical_time.insert(make_pair("JM", rb_Spical));
	Dirty_time.insert(make_pair("JM", rb_filter));
	Close_time.insert(make_pair("JM", rb_close));
	//����
	Spical_time.insert(make_pair("M", rb_Spical));
	Dirty_time.insert(make_pair("M", rb_filter));
	Close_time.insert(make_pair("M", rb_close));
	//����
	Spical_time.insert(make_pair("C", rb_Spical));
	Dirty_time.insert(make_pair("C", rb_filter));
	Close_time.insert(make_pair("C", rb_close));
	//����
	Spical_time.insert(make_pair("L", rb_Spical));
	Dirty_time.insert(make_pair("L", rb_filter));
	Close_time.insert(make_pair("L", rb_close));
	//������ϩ
	Spical_time.insert(make_pair("V", rb_Spical));
	Dirty_time.insert(make_pair("V", rb_filter));
	Close_time.insert(make_pair("V", rb_close));
	//����
	Spical_time.insert(make_pair("Y", rb_Spical));
	Dirty_time.insert(make_pair("Y", rb_filter));
	Close_time.insert(make_pair("Y", rb_close));
	//�ƴ�һ��
	Spical_time.insert(make_pair("A", rb_Spical));
	Dirty_time.insert(make_pair("A", rb_filter));
	Close_time.insert(make_pair("A", rb_close));
	//�ƴ󶹶���
	Spical_time.insert(make_pair("B", rb_Spical));
	Dirty_time.insert(make_pair("B", rb_filter));
	Close_time.insert(make_pair("B", rb_close));
	//�۱�ϩ
	Spical_time.insert(make_pair("PP", rb_Spical));
	Dirty_time.insert(make_pair("PP", rb_filter));
	Close_time.insert(make_pair("PP", rb_close));
	//���
	Spical_time.insert(make_pair("CS", rb_Spical));
	Dirty_time.insert(make_pair("CS", rb_filter));
	Close_time.insert(make_pair("CS", rb_close));
	//Һ����
	Spical_time.insert(make_pair("PG", rb_Spical));
	Dirty_time.insert(make_pair("PG", rb_filter));
	Close_time.insert(make_pair("PG", rb_close));
	//�Ҷ���
	Spical_time.insert(make_pair("EG", rb_Spical));
	Dirty_time.insert(make_pair("EG", rb_filter));
	Close_time.insert(make_pair("EG", rb_close));
	//ȼ��
	Spical_time.insert(make_pair("FU", rb_Spical));
	Dirty_time.insert(make_pair("FU", rb_filter));
	Close_time.insert(make_pair("FU", rb_close));
	//��ά��
	Spical_time.insert(make_pair("FB", rb_Spical));
	Dirty_time.insert(make_pair("FB", rb_filter));
	Close_time.insert(make_pair("FB", rb_close));
	//����
	Spical_time.insert(make_pair("RR", rb_Spical));
	Dirty_time.insert(make_pair("RR", rb_filter));
	Close_time.insert(make_pair("RR", rb_close));
	//���ϰ�
	Spical_time.insert(make_pair("BB", rb_Spical));
	Dirty_time.insert(make_pair("BB", rb_filter));
	Close_time.insert(make_pair("BB", rb_close));
	//����
	Spical_time.insert(make_pair("JD", rb_Spical));
	Dirty_time.insert(make_pair("JD", rb_filter));
	Close_time.insert(make_pair("JD", rb_close));
	//����ϩ
	Spical_time.insert(make_pair("EB", rb_Spical));
	Dirty_time.insert(make_pair("EB", rb_filter));
	Close_time.insert(make_pair("EB", rb_close));
	//����ȼ��
	Spical_time.insert(make_pair("LU", rb_Spical));
	Dirty_time.insert(make_pair("LU", rb_filter));
	Close_time.insert(make_pair("LU", rb_close));
	//20�Ž�
	Spical_time.insert(make_pair("NR", rb_Spical));
	Dirty_time.insert(make_pair("NR", rb_filter));
	Close_time.insert(make_pair("NR", rb_close));
	//�޻�
	Spical_time.insert(make_pair("CF", rb_Spical));
	Dirty_time.insert(make_pair("CF", rb_filter));
	Close_time.insert(make_pair("CF", rb_close));
	//��ɴ
	Spical_time.insert(make_pair("CY", rb_Spical));
	Dirty_time.insert(make_pair("CY", rb_filter));
	Close_time.insert(make_pair("CY", rb_close));
	//����
	Spical_time.insert(make_pair("FG", rb_Spical));
	Dirty_time.insert(make_pair("FG", rb_filter));
	Close_time.insert(make_pair("FG", rb_close));
	//����
	Spical_time.insert(make_pair("SR", rb_Spical));
	Dirty_time.insert(make_pair("SR", rb_filter));
	Close_time.insert(make_pair("SR", rb_close));
	//PTA
	Spical_time.insert(make_pair("TA", rb_Spical));
	Dirty_time.insert(make_pair("TA", rb_filter));
	Close_time.insert(make_pair("TA", rb_close));
	//�״�
	Spical_time.insert(make_pair("MA", rb_Spical));
	Dirty_time.insert(make_pair("MA", rb_filter));
	Close_time.insert(make_pair("MA", rb_close));
	//����
	Spical_time.insert(make_pair("OI", rb_Spical));
	Dirty_time.insert(make_pair("OI", rb_filter));
	Close_time.insert(make_pair("OI", rb_close));
	//����
	Spical_time.insert(make_pair("PF", rb_Spical));
	Dirty_time.insert(make_pair("PF", rb_filter));
	Close_time.insert(make_pair("PF", rb_close));
	//����
	Spical_time.insert(make_pair("RM", rb_Spical));
	Dirty_time.insert(make_pair("RM", rb_filter));
	Close_time.insert(make_pair("RM", rb_close));
	//����
	Spical_time.insert(make_pair("SA", rb_Spical));
	Dirty_time.insert(make_pair("SA", rb_filter));
	Close_time.insert(make_pair("SA", rb_close));
	//����ú
	Spical_time.insert(make_pair("ZC", rb_Spical));
	Dirty_time.insert(make_pair("ZC", rb_filter));
	Close_time.insert(make_pair("ZC", rb_close));
	//���
	Spical_time.insert(make_pair("P", rb_Spical));
	Dirty_time.insert(make_pair("P", rb_filter));
	Close_time.insert(make_pair("P", rb_close));
	
	/*==================��ͭ��ͬʱ����==================*/
	map<string, string>  cu_Spical = { {"11:00", "11:30" },{"13:30", "14:30"},{"14:30", "15:00"} };
	map<string, string> cu_filter = { { "15:00:10","20:59:50" },{ "01:00:10","08:59:50" },{ "11:30:10","13:29:50"} };
	vector<string> cu_close = { "11:30","15:00","01:00" };
	//ͭ
	Spical_time.insert(make_pair("CU", cu_Spical));
	Dirty_time.insert(make_pair("CU", cu_filter));
	Close_time.insert(make_pair("CU", cu_close));
	//����ͭ
	Spical_time.insert(make_pair("BC", cu_Spical));
	Dirty_time.insert(make_pair("BC", cu_filter));
	Close_time.insert(make_pair("BC", cu_close));
	//��
	Spical_time.insert(make_pair("AL", cu_Spical));
	Dirty_time.insert(make_pair("AL", cu_filter));
	Close_time.insert(make_pair("AL", cu_close));
	//��
	Spical_time.insert(make_pair("SN", cu_Spical));
	Dirty_time.insert(make_pair("SN", cu_filter));
	Close_time.insert(make_pair("SN", cu_close));
	//��
	Spical_time.insert(make_pair("NI", cu_Spical));
	Dirty_time.insert(make_pair("NI", cu_filter));
	Close_time.insert(make_pair("NI", cu_close));
	//Ǧ
	Spical_time.insert(make_pair("PB", cu_Spical));
	Dirty_time.insert(make_pair("PB", cu_filter));
	Close_time.insert(make_pair("PB", cu_close));
	//п
	Spical_time.insert(make_pair("ZN", cu_Spical));
	Dirty_time.insert(make_pair("ZN", cu_filter));
	Close_time.insert(make_pair("ZN", cu_close));
	//�����
	Spical_time.insert(make_pair("SS", cu_Spical));
	Dirty_time.insert(make_pair("SS", cu_filter));
	Close_time.insert(make_pair("SS", cu_close));

	
	/*==================��ƻ����ͬʱ����==================*/
	map<string, string>  ap_Spical = { { "11:00", "10:30" },{"13:30", "14:30"},{"14:30", "15:00"} };
	map<string, string> ap_filter = { { "15:00:10","23:59:50" },{ "00.00.00","08:59:50" },{ "11:30:10","13:29:50" } };
	vector<string> ap_close = { "11:30","15:00" };

	//ƻ��
	Spical_time.insert(make_pair("AP", ap_Spical));
	Dirty_time.insert(make_pair("AP", ap_filter));
	Close_time.insert(make_pair("AP", ap_close));
	//�߲�
	Spical_time.insert(make_pair("WR", ap_Spical));
	Dirty_time.insert(make_pair("WR", ap_filter));
	Close_time.insert(make_pair("WR", ap_close));
	//����
	Spical_time.insert(make_pair("CJ", ap_Spical));
	Dirty_time.insert(make_pair("CJ", ap_filter));
	Close_time.insert(make_pair("CJ", ap_close));
	//����
	Spical_time.insert(make_pair("JR", ap_Spical));
	Dirty_time.insert(make_pair("JR", ap_filter));
	Close_time.insert(make_pair("JR", ap_close));
	//���̵�
	Spical_time.insert(make_pair("LR", ap_Spical));
	Dirty_time.insert(make_pair("LR", ap_filter));
	Close_time.insert(make_pair("LR", ap_close));
	//���̵�
	Spical_time.insert(make_pair("RI", ap_Spical));
	Dirty_time.insert(make_pair("RI", ap_filter));
	Close_time.insert(make_pair("RI", ap_close));
	//����
	Spical_time.insert(make_pair("PM", ap_Spical));
	Dirty_time.insert(make_pair("PM", ap_filter));
	Close_time.insert(make_pair("PM", ap_close));
	//����
	Spical_time.insert(make_pair("RS", ap_Spical));
	Dirty_time.insert(make_pair("RS", ap_filter));
	Close_time.insert(make_pair("RS", ap_close));
	//����
	Spical_time.insert(make_pair("SF", ap_Spical));
	Dirty_time.insert(make_pair("SF", ap_filter));
	Close_time.insert(make_pair("SF", ap_close));
	//�̹�
	Spical_time.insert(make_pair("SM", ap_Spical));
	Dirty_time.insert(make_pair("SM", ap_filter));
	Close_time.insert(make_pair("SM", ap_close));
	//����
	Spical_time.insert(make_pair("RM", ap_Spical));
	Dirty_time.insert(make_pair("RM", ap_filter));
	Close_time.insert(make_pair("RM", ap_close));
	//����
	Spical_time.insert(make_pair("UR", ap_Spical));
	Dirty_time.insert(make_pair("UR", ap_filter));
	Close_time.insert(make_pair("UR", ap_close));
	//ǿ��
	Spical_time.insert(make_pair("WH", ap_Spical));
	Dirty_time.insert(make_pair("WH", ap_filter));
	Close_time.insert(make_pair("WH", ap_close));
	//����
	Spical_time.insert(make_pair("LH", ap_Spical));
	Dirty_time.insert(make_pair("LH", ap_filter));
	Close_time.insert(make_pair("LH", ap_close));
	//����
	Spical_time.insert(make_pair("PK", ap_Spical));
	Dirty_time.insert(make_pair("PK", ap_filter));
	Close_time.insert(make_pair("PK", ap_close));
	/*==================��if��ͬʱ����==================*/
	map<string, string>  if_Spical = { { "09:30", "10:30" },{ "10:30", "11:30" } };
	map<string, string> if_filter = { { "15:00:10","23:59:50" },{ "00.00.00","09:29:50" },{ "11:30:10","12:59:50" } };
	vector<string> if_close = { "11:30","15:00" };
	//����300��ָ�ڻ�
	Spical_time.insert(make_pair("IF", if_Spical));
	Dirty_time.insert(make_pair("IF", if_filter));
	Close_time.insert(make_pair("IF", if_close));
	//��֤500��ָ�ڻ�
	Spical_time.insert(make_pair("IC", if_Spical));
	Dirty_time.insert(make_pair("IC", if_filter));
	Close_time.insert(make_pair("IC", if_close));
	//��֤50��ָ�ڻ�
	Spical_time.insert(make_pair("IH", if_Spical));
	Dirty_time.insert(make_pair("IH", if_filter));
	Close_time.insert(make_pair("IH", if_close));

	/*==================�͹�ծ�ڻ���ͬʱ����==================*/
	map<string, string>  t_Spical = { { "09:15", "10:30" },{ "10:30", "11:30" } };
	map<string, string> t_filter = { { "15:15:10","23:59:50" },{ "00.00.00","09:14:50" },{ "11:30:10","12:59:50" } };
	vector<string> t_close = { "11:30","15:15" };
	//2���ڹ�ծ�ڻ�
	Spical_time.insert(make_pair("TS", t_Spical));
	Dirty_time.insert(make_pair("TS", t_filter));
	Close_time.insert(make_pair("TS", t_close));
	//5���ڹ�ծ�ڻ�
	Spical_time.insert(make_pair("TF", t_Spical));
	Dirty_time.insert(make_pair("TF", t_filter));
	Close_time.insert(make_pair("TF", t_close));
	//10���ڹ�ծ�ڻ�
	Spical_time.insert(make_pair("T", t_Spical));
	Dirty_time.insert(make_pair("T", t_filter));
	Close_time.insert(make_pair("T", t_close));
	
	/*==================��ԭ����ͬʱ����==================*/

	map<string, string>  sc_Spical = { { "11:00", "11:30" },{ "13:30", "14:30" },{ "14:30", "15:00" },{ "02:00", "02:30" } };
	map<string, string> sc_filtrer = { { "15:00:10","20:59:50" },{ "02:30:10","08:59:50" },{ "11:30:10","13:29:50" } };
	vector<string> sc_close = { "11:30","15:00","02:30" };
	//ԭ��
	Spical_time.insert(make_pair("SC", sc_Spical));
	Dirty_time.insert(make_pair("SC", sc_filtrer));
	Close_time.insert(make_pair("SC", sc_close));
	//�ƽ�
	Spical_time.insert(make_pair("AU", sc_Spical));
	Dirty_time.insert(make_pair("AU", sc_filtrer));
	Close_time.insert(make_pair("AU", sc_close));
	//����
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
