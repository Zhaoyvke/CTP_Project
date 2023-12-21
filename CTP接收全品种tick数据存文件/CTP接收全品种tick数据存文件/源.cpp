#include "CCustomMdSpi.h"
#include "CCustomTraderSpi.h"
#include "DealSpicalTime.h"
#include <iostream>
#include <vector>
#include <map>
#include <mutex>
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
//char *pInstrumentID[200] = {};// �����Լ�����б��С��ϡ���֣��������ѡһ��
volatile int singalnum=0; //ȫ�ֱ������ڽ��̼��ͨ��

mutex pInstrument_Mutex;//���������Լ������
// �����Լ��������
int instrumentNum = 0;
//�ļ�·��
//char filePath[100] = { '\0' };
//���齻��ǰ�õ�ַ
char mdfront_addr[] = MDFRONT_ADDR;
//����ǰ�õ�ַ
char traderfront[] = TRADERFRONT_ADDR;

//����ʱ�䴦����
DealSpicalTime  dealspicaltime;
mutex Dealspicaltime_Mutex;//��������ʱ�����õ���
map<string, string> m_instrument2Exchange;//��Լ�ͽ�����֮���ӳ��
mutex instrument2dbname_Mutex;//�����Լ�����ݿ�ӳ���ϵ���õ���

//vector<string> Path = { "E:/MarketData/SHFE/","E:/MarketData/CFFEX/","E:/MarketData/INE/","E:/MarketData/CZCE/","E:/MarketData/DCE/" };
//char targetpath[] = "../MarketData/";  //���ڴ���ļ���·��
char targetpath[] = "E:/MarketData/";  //���ڴ���ļ���·��
vector<string> Ins = {};
int main()
{

	/*   �������к�Լ�����ݣ���Ҫ��Trader�ӿڲ�ѯ���к�Լ
     	 Ȼ���MdSpi�ӿڽ��ж���
	*/
	////�Ϻ��ڻ�������
	//m_instrument2dbname.insert(make_pair("sn", "shfe_tick")); //����
	//m_instrument2dbname.insert(make_pair("al", "shfe_tick")); //����
	//m_instrument2dbname.insert(make_pair("ni", "shfe_tick")); //����
	//m_instrument2dbname.insert(make_pair("zn", "shfe_tick")); //��п
	//m_instrument2dbname.insert(make_pair("pb", "shfe_tick")); //��Ǧ
	//m_instrument2dbname.insert(make_pair("sp", "shfe_tick")); //ֽ��
	//m_instrument2dbname.insert(make_pair("ss", "shfe_tick")); //�����
	//m_instrument2dbname.insert(make_pair("hc", "shfe_tick")); //�����
	//m_instrument2dbname.insert(make_pair("fu", "shfe_tick")); //ȼ��
	//m_instrument2dbname.insert(make_pair("bu", "shfe_tick")); //����
	//m_instrument2dbname.insert(make_pair("wr", "shfe_tick")); //�߲�
	//m_instrument2dbname.insert(make_pair("au", "shfe_tick")); //�ƽ�
	//m_instrument2dbname.insert(make_pair("ag", "shfe_tick")); //����
	//m_instrument2dbname.insert(make_pair("ru", "shfe_tick")); //��
	//m_instrument2dbname.insert(make_pair("rb", "shfe_tick"));  //���Ƹ�
	//m_instrument2dbname.insert(make_pair("cu", "shfe_tick"));  //ͭ
	////�Ϻ���Դ�ڻ�������
	//m_instrument2dbname.insert(make_pair("sc", "ine_tick"));  //ԭ��
	//m_instrument2dbname.insert(make_pair("bc", "ine_tick"));  //����ͭ
	//m_instrument2dbname.insert(make_pair("lu", "ine_tick"));  //����ȼ��
	//m_instrument2dbname.insert(make_pair("nr", "ine_tick"));  //20�Ž�

	////�����ڻ�������Ʒ��
	//m_instrument2dbname.insert(make_pair("j", "dce_tick"));  //��̿
	//m_instrument2dbname.insert(make_pair("m", "dce_tick"));  //����
	//m_instrument2dbname.insert(make_pair("c", "dce_tick"));  //����
	//m_instrument2dbname.insert(make_pair("i", "dce_tick"));  //����ʯ
	//m_instrument2dbname.insert(make_pair("l", "dce_tick"));  //����
	//m_instrument2dbname.insert(make_pair("v", "dce_tick"));  //������ϩ
	//m_instrument2dbname.insert(make_pair("y", "dce_tick"));  //����
	//m_instrument2dbname.insert(make_pair("a", "dce_tick"));  //�ƴ�һ��
	//m_instrument2dbname.insert(make_pair("b", "dce_tick"));  //�ƴ󶹶���
	//m_instrument2dbname.insert(make_pair("pp", "dce_tick"));  //�۱�ϩ
	//m_instrument2dbname.insert(make_pair("jm", "dce_tick"));  //��ú
	//m_instrument2dbname.insert(make_pair("cs", "dce_tick"));  //���
	//m_instrument2dbname.insert(make_pair("pg","dce_tick"));  //Һ����
	//m_instrument2dbname.insert(make_pair("eg","dce_tick"));  //�Ҷ���	
	//m_instrument2dbname.insert(make_pair("fu", "dce_tick"));  //ȼ��
	//m_instrument2dbname.insert(make_pair("fb", "dce_tick"));  //��ά��
	//m_instrument2dbname.insert(make_pair("rr", "dce_tick"));  //����
	//m_instrument2dbname.insert(make_pair("bb", "dce_tick"));  //���ϰ�
	//m_instrument2dbname.insert(make_pair("jd", "dce_tick"));  //����
	//m_instrument2dbname.insert(make_pair("eb", "dce_tick"));  //����ϩ
	//
	//
	//

	////֣���ڻ�������
	//m_instrument2dbname.insert(make_pair("AP", "zce_tick"));  //ƻ��
	//m_instrument2dbname.insert(make_pair("CF", "zce_tick"));  //�޻�
	//m_instrument2dbname.insert(make_pair("CJ", "zce_tick"));  //����
	//m_instrument2dbname.insert(make_pair("CY", "zce_tick"));  //��ɴ
	//m_instrument2dbname.insert(make_pair("FG", "zce_tick"));  //����
	//m_instrument2dbname.insert(make_pair("SR", "zce_tick"));  //����
	//m_instrument2dbname.insert(make_pair("JR", "zce_tick"));  //����
	//m_instrument2dbname.insert(make_pair("LR", "zce_tick"));  //���̵�
	//m_instrument2dbname.insert(make_pair("RI", "zce_tick"));  //���̵�
	//m_instrument2dbname.insert(make_pair("TA", "zce_tick"));  //PTA
	//m_instrument2dbname.insert(make_pair("MA", "zce_tick"));  //�״�
	//m_instrument2dbname.insert(make_pair("OI", "zce_tick"));  //����
	//m_instrument2dbname.insert(make_pair("PF", "zce_tick"));  //����
	//m_instrument2dbname.insert(make_pair("PM", "zce_tick"));  //����
	//m_instrument2dbname.insert(make_pair("RM", "zce_tick"));  //����
	//m_instrument2dbname.insert(make_pair("RS", "zce_tick"));  //����
	//m_instrument2dbname.insert(make_pair("SA", "zce_tick"));  //����
	//m_instrument2dbname.insert(make_pair("SF", "zce_tick"));  //����
	//m_instrument2dbname.insert(make_pair("SM", "zce_tick"));  //�̹�
	//m_instrument2dbname.insert(make_pair("UR", "zce_tick"));  //����
	//m_instrument2dbname.insert(make_pair("WH", "zce_tick"));  //ǿ��
	//m_instrument2dbname.insert(make_pair("ZC", "zce_tick"));  //����ú

	////�Ϻ������ڻ�������
	//m_instrument2dbname.insert(make_pair("IF", "cffex_tick"));  //����300��ָ�ڻ�
	//m_instrument2dbname.insert(make_pair("IC", "cffex_tick"));  //��֤500��ָ�ڻ�
	//m_instrument2dbname.insert(make_pair("IH", "cffex_tick"));  //��֤50��ָ�ڻ�
	//m_instrument2dbname.insert(make_pair("TF", "cffex_tick"));  //5���ծ�ڻ�
	//m_instrument2dbname.insert(make_pair("TS", "cffex_tick"));  //2���ծ�ڻ�
	//m_instrument2dbname.insert(make_pair("T", "cffex_tick"));  //10���ծ�ڻ�

	TraderApi = CThostFtdcTraderApi::CreateFtdcTraderApi();
	CCustomTraderSpi *TradeSpi = new CCustomTraderSpi();
	////���

	TraderApi->RegisterSpi(TradeSpi);
	TraderApi->SubscribePublicTopic(THOST_TERT_QUICK);
	TraderApi->SubscribePrivateTopic(THOST_TERT_QUICK);
	TraderApi->RegisterFront(traderfront);
	

	//��ʼ�������߳�
	cout << "��ʼ������..." << endl;
	mdApi = CThostFtdcMdApi::CreateFtdcMdApi();   // ��������ʵ��
	CThostFtdcMdSpi *pMdUserSpi = new CCustomMdSpi;  // ��������ص�ʵ��
	mdApi->RegisterSpi(pMdUserSpi);               // ע���¼���
	mdApi->RegisterFront(mdfront_addr);           // ��������ǰ�õ�ַ

	TraderApi->Init();
	mdApi->Init();                                // ��������


	TraderApi->Join();
	delete TradeSpi;
	TraderApi->Release();
	

	mdApi->Join();
	delete pMdUserSpi;
	mdApi->Release();

	system("pause");
	return 0;
}