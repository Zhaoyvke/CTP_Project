#include "CCustomMdSpi.h"
#include "CCustomTraderSpi.h"
#include "DealSpicalTime.h"
#include <iostream>
#include <vector>
#include <map>
using namespace std;
// ���ӿ�
#pragma comment (lib, "thostmduserapi_se.lib") //����CTP��̬��
#pragma comment (lib, "thosttraderapi_se.lib")
#pragma comment (lib,"libmysql.lib")    //�������ݿ⶯̬��
/*==========================ȫ�ֱ���=======================*/
//���ײ���
CThostFtdcTraderApi *TraderApi;
//�������
CThostFtdcMdApi *mdApi;
// �����Լ�����б�
char *pInstrumentID[100] = {};// �����Լ�����б��С��ϡ���֣��������ѡһ��

// �����Լ��������
int instrumentNum = 0;
//�ļ�·��
char filePath[100] = { '\0' };
//���齻��ǰ�õ�ַ
char mdfront_addr[] = MDFRONT_ADDR;
//����ǰ�õ�ַ
char traderfront[] = TRADERFRONT_ADDR;

//����ʱ�䴦����
DealSpicalTime  dealspicaltime;

vector<string> Ins = {
	/*���ڽ�����  Ʒ������Ҫ��д*/
	"IF2212","IF2205","IF2206","IF2209",
};

map<string, string> m_instrument2dbname;
int main()
{
	//step1 ��ʼ����Լ��
	instrumentNum = Ins.size();  //�����Լ��������
	for (int i = 0; i < Ins.size(); i++) {
		char * InsCell = (char*)Ins[i].c_str();
		pInstrumentID[i] = InsCell;
	}
	//m_instrument2dbname.insert(make_pair("rb","shfe"));  //rbƷ�ֶ�Ӧ�����ݿ�Ϊ���Ƹ�
	m_instrument2dbname.insert(make_pair("IF", "cffex"));  //IFƷ�ֶ�Ӧ�����ݿ�Ϊ����300
	m_instrument2dbname.insert(make_pair("IC", "cffex"));  //IFƷ�ֶ�Ӧ�����ݿ�Ϊ����300
	m_instrument2dbname.insert(make_pair("IH", "cffex"));  //IFƷ�ֶ�Ӧ�����ݿ�Ϊ����300

	//step2 ��ʼ���ļ�����·��
	strcpy(filePath, "../AllData/");  //Ϊ�����ļ���·����ֵ								  
	 //��ʼ�������߳�
	cout << "��ʼ������..." << endl;
	mdApi = CThostFtdcMdApi::CreateFtdcMdApi();   // ��������ʵ��
	CThostFtdcMdSpi *pMdUserSpi = new CCustomMdSpi;  // ��������ص�ʵ��
	mdApi->RegisterSpi(pMdUserSpi);               // ע���¼���
	mdApi->RegisterFront(mdfront_addr);           // ��������ǰ�õ�ַ
	
	mdApi->Init();                                // ��������
	mdApi->Join();
	delete pMdUserSpi;
	mdApi->Release();

	system("pause");
	return 0;
}