#pragma once

//������۲�Ľṹ��
struct kline2price
{
	char instumentID[30];    //��Լ��
	char tradeDay[35];    //������
	double openprice;   //3�۲�K�ߵĿ��̼�
	double highprice;   //��߼�
	double lowprice;   //��ͼ�
	double closeprice;  //3�۲�K�ߵ����̼�
	char openticklocal[35];// ���̼۶�Ӧtick��localʱ��
	char closeticklocal[35];//���̼۶�Ӧtick��localʱ��
	int  duration;
};
struct  subtick
{
	string instrumentID;
	string tradeDay;
	double tickprice;
	string local;
};