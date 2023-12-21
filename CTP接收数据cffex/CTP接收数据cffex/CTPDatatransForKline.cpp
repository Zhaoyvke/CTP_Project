#include "CTPDatatransForKline.h"
#include "StringOpera.h"
#include "DealSpicalTime.h"
extern DealSpicalTime  dealspicaltime;
CTPDatatransForKline::CTPDatatransForKline(string instrumentID):num(0), endtime(""),last3pricetradeday(""),lasttickkid(0),lasttickklines(PTNUM), LastTickklinesClosePrices(PTNUM), prehour(0)
{
	memset(&current2pricekline,0,sizeof(kline2price));//初始化当前2价差K线变量
	if (instrumentID.empty() == false)
	{
		vector<string> res;
		StringOpera::SplitString(instrumentID,res,"|");
		exchange = res[0];
		pre = res[2];
		indexcsvpre = res[2] + res[3];
		if (pre == "RB") {
			difprice = 2;
		}
		else
		{
			difprice = 0.4;
		}
		
        string tablepre;
        tablepre = res[2] + res[3];//CSV文件名称
		
		ctpOper = new CTPDBoperator(exchange,tablepre);//tablepre--CSV文件名称
		ctpOper->GetLastTickKline(lasttickklines);//各个周期的上一根tickk线
		for (int i = 0; i < lasttickklines.size(); i++)
		{
			LastTickklinesClosePrices[i] = lasttickklines[i].closeprice;
		}
	}
	//string dayfile = "C:/" + indexcsvpre + "day.csv";
	//_strupr(const_cast<char*>(dayfile.c_str()));
	//fday.open(dayfile);
	//string  temp = "instrumentID,type,sequence,tradeDay,updateTime,totalvolume,openinterest,closeprice,volume,openprice,highprice,lowprice,klineType,addposition,openvolume,evenvolume,dealtype,direction,buyprice,buyqty,sellprice,sellqty,weibi,Id,local,";

	//temp.append("volume_tick,");
	//temp.append("macd_tick,dif_tick,dea_tick,");
	//temp.append("k_tick,d_tick,j_tick,");
	//temp.append("ma5_tick,ma10_tick,ma20_tick,ma60_tick,");
	//temp.append("bollup_tick,bolldown_tick,bollmid_tick,");


	//temp.append("updateTime_1min,volume_1min,open_1min,high_1min,low_1min,");
	//temp.append("macd_1min,dif_1min,dea_1min,");
	//temp.append("k_1min,d_1min,j_1min,");
	//temp.append("ma5_1min,ma10_1min,ma20_1min,ma60_1min,");
	//temp.append("bollup_1min,bolldown_1min,bollmid_1min,");

	//temp.append("updateTime_3min,volume_3min,open_3min,high_3min,low_3min,");
	//temp.append("macd_3min,dif_3min,dea_3min,");
	//temp.append("k_3min,d_3min,j_3min,");
	//temp.append("ma5_3min,ma10_3min,ma20_3min,ma60_3min,");
	//temp.append("bollup_3min,bolldown_3min,bollmid_3min,");

	//temp.append("updateTime_5min,volume_5min,open_5min,high_5min,low_5min,");
	//temp.append("macd_5min,dif_5min,dea_5min,");
	//temp.append("k_5min,d_5min,j_5min,");
	//temp.append("ma5_5min,ma10_5min,ma20_5min,ma60_5min,");
	//temp.append("bollup_5min,bolldown_5min,bollmid_5min,");

	//temp.append("updateTime_15min,volume_15min,open_15min,high_15min,low_15min,");
	//temp.append("macd_15min,dif_15min,dea_15min,");
	//temp.append("k_15min,d_15min,j_15min,");
	//temp.append("ma5_15min,ma10_15min,ma20_15min,ma60_15min,");
	//temp.append("bollup_15min,bolldown_15min,bollmid_15min,");


	//temp.append("updateTime_30min,volume_30min,open_30min,high_30min,low_30min,");
	//temp.append("macd_30min,dif_30min,dea_30min,");
	//temp.append("k_30min,d_30min,j_30min,");
	//temp.append("ma5_30min,ma10_30min,ma20_30min,ma60_30min,");
	//temp.append("bollup_30min,bolldown_30min,bollmid_30min,");
	//temp.append("open_day,high_day,low_day,close_day,");

	////lag1指标
	//temp.append("open_1min_lag1,high_1min_lag1,low_1min_lag1,close_1min_lag1,");
	//temp.append("macd_1min_lag1,dif_1min_lag1,dea_1min_lag1,");
	//temp.append("k_1min_lag1,d_1min_lag1,");
	//temp.append("ma5_1min_lag1,ma10_1min_lag1,ma20_1min_lag1,ma60_1min_lag1,");
	////temp.append("bollup_1min,bolldown_1min,bollmid_1min,");
	//temp.append("dif_open_1min,dif_high_1min,dif_low_1min,dif_close_1min,");
	//temp.append("dif_macd_1min,dif_dif_1min,dif_dea_1min,");
	//temp.append("dif_k_1min,dif_d_1min,");
	//temp.append("dif_ma5_1min,dif_ma10_1min,dif_ma20_1min,dif_ma60_1min,");
	////	temp.append("dif_bollup_1min,dif_bolldown_1min,dif_bollmid_1min,");


	//temp.append("open_3min_lag1,high_3min_lag1,low_3min_lag1,close_3min_lag1,");
	//temp.append("macd_3min_lag1,dif_3min_lag1,dea_3min_lag1,");
	//temp.append("k_3min_lag1,d_3min_lag1,");
	//temp.append("ma5_3min_lag1,ma10_3min_lag1,ma20_3min_lag1,ma60_3min_lag1,");

	//temp.append("dif_open_3min,dif_high_3min,dif_low_3min,dif_close_3min,");
	//temp.append("dif_macd_3min,dif_dif_3min,dif_dea_3min,");
	//temp.append("dif_k_3min,dif_d_3min,");
	//temp.append("dif_ma5_3min,dif_ma10_3min,dif_ma20_3min,dif_ma60_3min,");



	//temp.append("open_5min_lag1,high_5min_lag1,low_5min_lag1,close_5min_lag1,");
	//temp.append("macd_5min_lag1,dif_5min_lag1,dea_5min_lag1,");
	//temp.append("k_5min_lag1,d_5min_lag1,");
	//temp.append("ma5_5min_lag1,ma10_5min_lag1,ma20_5min_lag1,ma60_5min_lag1,");

	//temp.append("dif_open_5min,dif_high_5min,dif_low_5min,dif_close_5min,");
	//temp.append("dif_macd_5min,dif_dif_5min,dif_dea_5min,");
	//temp.append("dif_k_5min,dif_d_5min,");
	//temp.append("dif_ma5_5min,dif_ma10_5min,dif_ma20_5min,dif_ma60_5min,");


	//temp.append("open_15min_lag1,high_15min_lag1,low_15min_lag1,close_15min_lag1,");
	//temp.append("macd_15min_lag1,dif_15min_lag1,dea_15min_lag1,");
	//temp.append("k_15min_lag1,d_15min_lag1,");
	//temp.append("ma5_15min_lag1,ma10_15min_lag1,ma20_15min_lag1,ma60_15min_lag1,");

	//temp.append("dif_open_15min,dif_high_15min,dif_low_15min,dif_close_15min,");
	//temp.append("dif_macd_15min,dif_dif_15min,dif_dea_15min,");
	//temp.append("dif_k_15min,dif_d_15min,");
	//temp.append("dif_ma5_15min,dif_ma10_15min,dif_ma20_15min,dif_ma60_15min,");

	//temp.append("open_30min_lag1,high_30min_lag1,low_30min_lag1,close_30min_lag1,");
	//temp.append("macd_30min_lag1,dif_30min_lag1,dea_30min_lag1,");
	//temp.append("k_30min_lag1,d_30min_lag1,");
	//temp.append("ma5_30min_lag1,ma10_30min_lag1,ma20_30min_lag1,ma60_30min_lag1,");

	//temp.append("dif_open_30min,dif_high_30min,dif_low_30min,dif_close_30min,");
	//temp.append("dif_macd_30min,dif_dif_30min,dif_dea_30min,");
	//temp.append("dif_k_30min,dif_d_30min,");
	//temp.append("dif_ma5_30min,dif_ma10_30min,dif_ma20_30min,dif_ma60_30min,");
	//temp.append("wr14_1min,wr28_1min,wr34_1min,");
	//temp.append("gmma3_1min,gmma5_1min,gmma10_1min,gmma30_1min,gmma45_1min,gmma60_1min,");//GMMA：时间轴（1、3、5、30、60）；均线（3、5、10、30、45、60）
	//temp.append("gmma3_3min,gmma5_3min,gmma10_3min,gmma30_3min,gmma45_3min,gmma60_3min,");
	//temp.append("gmma3_5min,gmma5_5min,gmma10_5min,gmma30_5min,gmma45_5min,gmma60_5min,");
	//temp.append("gmma3_30min,gmma5_30min,gmma10_30min,gmma30_30min,gmma45_30min,gmma60_30min,");
	//temp.append("isbase1,isbase2,y_type1,y_type2");
	//fday << temp << endl;
	//fday.close();
}
void CTPDatatransForKline::CaltickkAndInsertDB(Tick * tick)
{
	//判断tick是否应该更新
	if (!this->tickisUpdate(tick)) /****/
	{
		return;
	}
	ctpOper->InitCon();  ///初始化数据库连接
	thread t1 = thread(std::bind(&CTPDatatransForKline::updateXperiodkline,this, tick, 1, ONEMIN));
	thread t3 = thread(std::bind(&CTPDatatransForKline::updateXperiodkline, this, tick, 3, THREEMIN));
	thread t5 = thread(std::bind(&CTPDatatransForKline::updateXperiodkline, this, tick, 5, FIVEMIN));
	thread t15 = thread(std::bind(&CTPDatatransForKline::updateXperiodkline, this, tick, 15, FIFTEENMIN));
	thread t30 = thread(std::bind(&CTPDatatransForKline::updateXperiodkline, this, tick, 30, THIRTMIN));
	thread t60 = thread(std::bind(&CTPDatatransForKline::updateXperiodkline, this, tick, 60, SIXTYMIN));
	thread tday = thread(std::bind(&CTPDatatransForKline::updateXperiodkline, this, tick, 24*60, DAY));

	t1.join();
	t3.join();
	t5.join();
	t15.join();
	t30.join();
	t60.join();
	tday.join();
  
	//
	//subtick sub_tick;
	//int CurrentTickid = ctpOper->GetLastTick(sub_tick);  //获取当前tickId
	//if (lasttickkid != CurrentTickid) //id 发生变化 代表tick更新
	//{
	//	/*===========================计算二价差==================================*/
	////	Cal2difBaseprice(sub_tick);

	//	/*=============================计算tick指标======================*/
	//	this->StarConvert(CurrentTickid);


	//}

	//lasttickkid = CurrentTickid;
    
	///关闭数据库连接
	ctpOper->CloseCon();
	
}

bool CTPDatatransForKline::tickisUpdate(Tick * tick)
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	char local[30];
	sprintf_s(local, "%02d:%02d:%02d", st.wHour, st.wMinute, st.wSecond);
	string m_local = local;
	//m_local = m_local.substr(11,8);
	string sublocal = string(tick->local).substr(11, 8);////接受数据的时间 分秒毫秒
	DealSpicalTime  DealSpicaltime;
    if (DealSpicaltime.FindisinDirty(pre, m_local) == true || DealSpicaltime.FindisinDirty(pre, sublocal) == true || (abs(tick->lastprice - 0) < 1e-4 || abs(tick->totalvolume - 0) < 1e-4))
	{//有特殊情况下m_local和sublocal会不是同一个，不是交易时间段的时候，有时交易所会测试连接发过来的数据是上个时间点的数据
			return false;
	}

	return true;
}

void CTPDatatransForKline::convertUpdateTime(string const & updatetime, string & descupdateTime, int pt)
{
	string time = updatetime.substr(updatetime.length() - 5, 5);//时分秒
	string date = updatetime.substr(0, 10);//年月日
	string closeTime;
	string SpicalTime;
	if (pt <= 15 && time == "10:15"&&  exchange!= "CFFEX") {//cffex这个交易所之外  其它的交易所在10点15到10点半是停盘的,他就得是10点15 而不是10点半
		descupdateTime = date + " 10:15";
		return;
	}
	if (dealspicaltime.FindisinClose(pre,time, closeTime)) 
	{
		descupdateTime = date + " " + closeTime;
		return;
	}
	if (pt == 60)   
	{ //小时
		if(dealspicaltime.FindisinSpical(pre,time, SpicalTime))
		{
				descupdateTime = date + " " + SpicalTime;
				return;
		}
	}

	unique_ptr<TimeDeal> deal(new TimeDeal());
	int mins = calDIffTimeMins(updatetime, pt);//取出分钟,计算当前时间到你所要专换的周期还差几分钟
	char date1[35];
	deal->char_AddTime(const_cast<char *>(updatetime.c_str()), date1, mins * 60, 1);//这个函数是用来计算时间的,9点03加7 怎么得出来的9点10分
	descupdateTime = date1; //更正后的时间结点
	if (pt == 30 && descupdateTime.substr(11, 5) == "10:30" && this->exchange != "CFFEX")
	{
		descupdateTime = descupdateTime.substr(0, 11) + "10:15";
	}

}
	
void CTPDatatransForKline::updateXperiodkline(Tick * tick, int X, Period pt)
{
	string srcupdateTime = tick->updateTime;
	TickKline nowtickkline;
	memset(&nowtickkline, 0, sizeof(nowtickkline));
	string newupdateTime;
	if (pt != DAY) {
		this->convertUpdateTime(srcupdateTime, newupdateTime, X);
	}
	else {
		newupdateTime = tick->tradeDay;
	}
	this->Caltickkline(nowtickkline, tick, newupdateTime, pt);
}

void CTPDatatransForKline::Caltickkline(TickKline & nowtickkline, Tick * tick, string const & newupdateTime, Period pt)//tick kline结构体的更新
{

	bool isNext = false;
	if (strcmp(newupdateTime.c_str(), lasttickklines[pt].updateTime) > 0) 
	{  //如果tick时间所在的周期已经是下一个周期了 那么开高低收都需要更新
		LastTickklinesClosePrices[pt] = lasttickklines[pt].closeprice;//各个周期的上一根tickk线  ->各个周期上一个K线的收盘价

		lasttickklines[pt].openprice = tick->lastprice;
		lasttickklines[pt].highprice = tick->lastprice;
		lasttickklines[pt].lowprice = tick->lastprice;
		lasttickklines[pt].volume = 0;
		isNext = true;//如果周期更新 插入K线数据库
	}
	if (strcmp(tick->tradeDay, lasttickklines[pt].tradeDay) > 0) 
	{    //交易日发生了变化
		lasttickklines[pt].totalvolume = 0;
		lasttickklines[pt].openInterest = tick->PreOpenInterest;  //昨日持仓量
	}
	tick->volume = tick->totalvolume - lasttickklines[pt].totalvolume;
	if (tick->volume == 0) 
	{
		return;
	}

	nowtickkline.totalvolume = tick->totalvolume;
	nowtickkline.openprice = lasttickklines[pt].openprice;
	nowtickkline.highprice = max(tick->lastprice, lasttickklines[pt].highprice);
	nowtickkline.lowprice = min(tick->lastprice, lasttickklines[pt].lowprice);
	nowtickkline.closeprice = tick->lastprice;
	nowtickkline.openInterest = tick->openInterest;
	strcpy_s(nowtickkline.updateTime, newupdateTime.c_str());
	if (pt == DAY) {
		nowtickkline.volume = tick->totalvolume;
	}
	else
	{
		nowtickkline.volume = tick->volume+lasttickklines[pt].volume;
	}

	strcpy_s(nowtickkline.tradeDay, tick->tradeDay);
	strcpy_s(nowtickkline.instumentId, tick->instumentId);
	strcpy_s(nowtickkline.local, tick->local);
	switch (pt)
	{
	case ONEMIN:strcpy_s(nowtickkline.type, "M");
		break;
	case THREEMIN:strcpy_s(nowtickkline.type, "3M");
		break;
	case FIVEMIN:strcpy_s(nowtickkline.type, "5M");
		break;
	case FIFTEENMIN:strcpy_s(nowtickkline.type, "15M");
		break;
	case THIRTMIN:strcpy_s(nowtickkline.type, "30M");
		break;
	case SIXTYMIN:strcpy_s(nowtickkline.type, "60M");
		break;
	case DAY:strcpy_s(nowtickkline.type, "D");
	default:
		break;
	}

	nowtickkline.klineType = this->calKlineType(lasttickklines[pt].openprice, tick->lastprice, LastTickklinesClosePrices[pt]);  //计算K线类型
	//计算K线类型 阴阳线
	if (tick->buyqty + tick->sellqty != 0)
	{
		nowtickkline.weibi = double(tick->buyqty - tick->sellqty) / (tick->buyqty + tick->sellqty);
	}//(委买手数－委卖手数)/ (委买手数＋委卖手数)×100 ％
	else
	{
		nowtickkline.weibi = 0;
	}

	nowtickkline.buyprice = tick->buyprice;  //买一价
	nowtickkline.buyqty = tick->buyqty;//买一量
	nowtickkline.sellprice = tick->sellprice;//卖一价
	nowtickkline.sellqty = tick->sellqty;//卖一量

	//===================计算盘口数据
	nowtickkline.addposition = tick->openInterest - lasttickklines[pt].openInterest; //增仓  今持仓-上个周期的持仓
	nowtickkline.kaicangvolume= double(nowtickkline.addposition + tick->volume) / 2;  //成交量中的开仓数量
	nowtickkline.pingcangvolume = tick->volume - (nowtickkline.kaicangvolume);   //成交量中的平仓数量

		//判断买卖方向
	if (tick->lastprice >= tick->sellprice)//如果当前tick的成交价格大于等于卖一价
	{
		strcpy(nowtickkline.direction, "B");
	}
	else if (tick->lastprice <= tick->buyprice) //如果当前tick的成交价格小于等于买一价
	{
		strcpy(nowtickkline.direction, "S");
	}
	else
	{
		strcpy(nowtickkline.direction, "B");

	}
	//判断成交类型
	if (nowtickkline.addposition < 0 && nowtickkline.addposition == tick->volume)  //如果仓差为负，且数量=成交量  成交类型为双平
	{
		strcpy(nowtickkline.Dealtype, "shuangping");
	}
	else if (nowtickkline.addposition < 0 && strcmp(nowtickkline.direction, "B") == 0) //如果仓差为负,且买卖方向为B, 成交类型为空平
	{
		strcpy(nowtickkline.Dealtype, "kongping");
	}
	else if (nowtickkline.addposition < 0 && strcmp(nowtickkline.direction, "S") == 0) //如果仓差为负,且买卖方向为S, 成交类型为多平
	{
		strcpy(nowtickkline.Dealtype, "duoping");
	}
	else if (nowtickkline.addposition == 0 && strcmp(nowtickkline.direction, "B") == 0)  //如果仓差为0，且买卖方向为B,成交类型为空换
	{
		strcpy(nowtickkline.Dealtype, "konghuan");
	}
	else if (nowtickkline.addposition == 0 && strcmp(nowtickkline.direction, "S") == 0)  //如果仓差为0，且买卖方向为S,成交类型为多换
	{
		strcpy(nowtickkline.Dealtype, "duohuan");
	}
	else if (nowtickkline.addposition > 0 && nowtickkline.addposition == tick->volume) //如果仓差为正，且数据量=成交量 成交类型为双开
	{
		strcpy(nowtickkline.Dealtype, "shuangkai");
	}
	else if (nowtickkline.addposition > 0 && strcmp(nowtickkline.direction, "B") == 0)//如果仓差为正,且买卖方向为B,成交类型为成交类型为多开
	{
		strcpy(nowtickkline.Dealtype, "duokai");
	}
	else if (nowtickkline.addposition > 0 && strcmp(nowtickkline.direction, "S") == 0)//如果仓差为正,且买卖方向为S,成交类型为成交类型为空开
	{
		strcpy(nowtickkline.Dealtype, "kongkai");
	}


	if (isNext)//如果周期更新 插入K线数据库
	{

		ctpOper->klineinsertDB(nowtickkline);


	}
	else  //如果周期未更新 更新K线数据库
	{
		ctpOper->updateKlineDB(nowtickkline);

	}

	this->copyTickKline(nowtickkline,lasttickklines[pt]);
	//将最新的tickK线插入tickK线数据库
	ctpOper->tickkinsertDB(nowtickkline);

}

int CTPDatatransForKline::calKlineType(double open, double close, double lastclose)//计算K线类型 阴阳线
{
	if (open > close) {
		return 0;
	}
	else if (open < close) {
		return 1;
	}
	else if (close > lastclose) {
		return 1;
	}
	else {
		return 0;
	}
}

void CTPDatatransForKline::copyTickKline(TickKline & srctickkline, TickKline & desctickkline)
{
	strcpy_s(desctickkline.instumentId, srctickkline.instumentId);
	desctickkline.closeprice = srctickkline.closeprice;
	desctickkline.highprice = srctickkline.highprice;
	desctickkline.id = srctickkline.id;
	desctickkline.klineType = srctickkline.klineType;
	strcpy_s(desctickkline.local, srctickkline.local);
	desctickkline.lowprice = srctickkline.lowprice;
	desctickkline.openInterest = srctickkline.openInterest;
	desctickkline.openprice = srctickkline.openprice;
	desctickkline.sequence = srctickkline.sequence;
	desctickkline.totalvolume = srctickkline.totalvolume;
	strcpy_s(desctickkline.tradeDay, srctickkline.tradeDay);
	strcpy_s(desctickkline.type, srctickkline.type);
	strcpy_s(desctickkline.updateTime, srctickkline.updateTime);
	desctickkline.volume = srctickkline.volume;
}

int CTPDatatransForKline::calDIffTimeMins(string const & updateTime, int Type)
{	
	//取出分钟
	string min = updateTime.substr(updateTime.length() - 2, 2);
	int mins = atoi(min.c_str()); //把参数 str 所指向的字符串转换为一个整数
	return Type - (mins%Type);
}


//根据id获取数据算指标
void CTPDatatransForKline::ProductOneKind(int id, Period pt, CSVLine & csvl) /******/
{
	memset(&csvl, 0, sizeof(csvl));
	IndexKLine current_k;
	ctpOper->GetKlineById(pt, id, current_k);
	if (strcmp(current_k.ID, "") == 0)
	{
		cout << "未找到当前" << pt << "min周期id为" << id << "的数据" << endl;
		system("pause");
		exit(0);
	}
	vector<IndexKLine> temp_ks;

	vector<double> temp_close;
	temp_close.push_back(current_k.close);
	if (pt == TICK)
	{
		sscanf(current_k.local, "%*s %d/%*s", &curhour);
		if (abs(curhour - prehour) >= 6) {
			isbase1 = 0;
			y_type1 = 0;
			isbase2 = 0;
			y_type2 = 0;
			prebase1 = current_k.close;
			prebase2 = current_k.close;
		}
		else if (curhour == 15 || curhour == 23) {
			isbase1 = 1;
			if (current_k.close > prebase1)	y_type1 = 1;
			else
			{
				y_type1 = -1;
				if (current_k.close == prebase1)	y_type1 = 0;
			}
			isbase2 = 1;
			if (current_k.close > prebase2)	y_type2 = 1;
			else
			{
				y_type2 = -1;
				if (current_k.close == prebase2)	y_type2 = 0;
			}
		}
		else {
			if (abs(current_k.close - prebase1) >= 1) {
				isbase1 = 1;
				if (current_k.close > prebase1)	y_type1 = 1;
				else
				{
					y_type1 = -1;
				}
				prebase1 = current_k.close;
			}
			else {
				isbase1 = 0;
				y_type1 = 0;
			}

			if (abs(current_k.close - prebase2) >= 2) {
				isbase2 = 1;
				if (current_k.close > prebase2)	y_type2 = 1;
				else
				{
					y_type2 = -1;
				}
				prebase2 = current_k.close;
			}
			else {
				isbase2 = 0;
				y_type2 = 0;
			}
		}
		prehour = curhour;
		current_k.open = current_k.close;
		current_k.max = current_k.close;
		current_k.min = current_k.close;
		temp_ks.push_back(current_k);
		ctpOper->GetKlinesBeforeId(pt, id, 160, temp_ks, temp_close);
	}
	else
	{
		temp_ks.push_back(current_k);
		ctpOper->GetKlinesBeforeUpdateTime(pt, current_k.datatime, 160, temp_ks, temp_close);
	}

	if (temp_ks.size() < 160) {
		cout << "历史K线不足160根" << endl;
		/*system("pause");
		exit(0);*/
		return;
	}
	csvl.open = current_k.open;
	csvl.max = current_k.max;
	csvl.min = current_k.min;
	csvl.close = current_k.close;
	csvl.hold = current_k.hold;
	csvl.vol = current_k.vol;
	if (pt == TICK)
	{
		if (strcmp(current_k.datatime, temp_ks[1].datatime) == 0) //如果相邻两个tick的周期时间相同
			csvl.vol = current_k.vol - temp_ks[1].vol;

	}
	strcpy(csvl.local, current_k.local);
	strcpy(csvl.ID, current_k.ID);
	strcpy(csvl.tradeday, current_k.tradeday);
	strcpy(csvl.datatime, current_k.datatime);

	vector<double> close, low, high;
	KLineDataPicker(temp_ks, close, "CLOSE");
	KLineDataPicker(temp_ks, low, "LOW");
	KLineDataPicker(temp_ks, high, "HIGH");
	indl.pt = pt;
	int p = 26, s = 12, m = 9;
	indl.countMacd(close, 0, s, p, m);
	csvl.MacdT.DEA = indl.curdea[pt];
	csvl.MacdT.DIFF = indl.curdiff[pt];
	csvl.MacdT.MACD = indl.curmacd[pt];
	indl.J(3, 3, 9, close, low, high, 0);
	csvl.kdj.k = indl.curk[pt];
	csvl.kdj.d = indl.curd[pt];
	csvl.kdj.j = indl.curj[pt];

	//indexOper.CalculateKDJ(temp_ks, 9, 3, 3, csvl.kdj);
	indexOper.CalculateBOLL(&temp_close, 26, 2, csvl.boll);
	//indexOper.CalculateMACD(&temp_close,csvl.MacdT, 12, 26, 9);
	csvl.ma5 = indexOper.CalculateMA(&temp_close, 5);
	csvl.ma10 = indexOper.CalculateMA(&temp_close, 10);
	csvl.ma20 = indexOper.CalculateMA(&temp_close, 20);
	csvl.ma60 = indexOper.CalculateMA(&temp_close, 60);


	if (pt == ONEMIN) {
		vector<double> close, low, high;
		KLineDataPicker(temp_ks, close, "CLOSE");
		KLineDataPicker(temp_ks, low, "LOW");
		KLineDataPicker(temp_ks, high, "HIGH");
		csvl.wr14 = indl.WR(high, low, close[0], 14);
		csvl.wr28 = indl.WR(high, low, close[0], 28);
		csvl.wr34 = indl.WR(high, low, close[0], 34);
	}
	if (pt != TICK && pt != FIFTEENMIN) {
		csvl.gmma3 = indl.GMMA(temp_close, 3);
		csvl.gmma5 = indl.GMMA(temp_close, 5);
		csvl.gmma10 = indl.GMMA(temp_close, 10);
		csvl.gmma30 = indl.GMMA(temp_close, 30);
		csvl.gmma45 = indl.GMMA(temp_close, 45);
		csvl.gmma60 = indl.GMMA(temp_close, 60);
	}

	temp_close.erase(temp_close.begin());
	temp_ks.erase(temp_ks.begin());
	close.erase(close.begin());
	low.erase(low.begin());
	high.erase(high.begin());

	csvl.open_lag1 = temp_ks[0].open;
	csvl.high_lag1 = temp_ks[0].max;
	csvl.low_lag1 = temp_ks[0].min;
	csvl.close_lag1 = temp_ks[0].close;

	indl.countMacd(close, 0, s, p, m);
	csvl.MacdT_lag1.DEA = indl.curdea[pt];
	csvl.MacdT_lag1.DIFF = indl.curdiff[pt];
	csvl.MacdT_lag1.MACD = indl.curmacd[pt];
	indl.J(3, 3, 9, close, low, high, 0);
	csvl.kdj_lag1.k = indl.curk[pt];
	csvl.kdj_lag1.d = indl.curd[pt];
	csvl.kdj_lag1.j = indl.curj[pt];

	//indexOper.CalculateMACD(&temp_close, csvl.MacdT_lag1, 12, 26, 9);
	csvl.ma5_lag1 = indexOper.CalculateMA(&temp_close, 5);
	csvl.ma10_lag1 = indexOper.CalculateMA(&temp_close, 10);
	csvl.ma20_lag1 = indexOper.CalculateMA(&temp_close, 20);
	csvl.ma60_lag1 = indexOper.CalculateMA(&temp_close, 60);
	// indexOper.CalculateKDJ(temp_ks, 9, 3, 3, csvl.kdj_lag1);
	// indexOper.CalculateBOLL(&temp_close, 26, 2, csvl.boll_lag1);

}

void CTPDatatransForKline::GetCurrenttickByid(int id, TickKline & currenttick)
{

	ctpOper->GetCurrenttickkById(TICK,id, currenttick);
}

void CTPDatatransForKline::GetCurrentDayData(int id, Kline & daykline)
{
	ctpOper->GetDayData(DAY,id,daykline);
}

void CTPDatatransForKline::StarConvert(int id)
{
	ifstream fread;
	ofstream fwrite;

	//用来存储单天指标所需要存储的变量
	string dayfile = "C:/" + indexcsvpre + "day.csv";
	_strupr(const_cast<char*>(dayfile.c_str()));
	fday.open(dayfile, ios::app);


	//string filename = "../" + indexcsvpre + ".csv";
	string filename = "C:/" + indexcsvpre + ".csv";

	_strupr(const_cast<char*>(filename.c_str()));
	
	fread.open(filename, ios::in);
	if (fread.peek() == EOF)
	{


		fwrite.open(filename, ios::trunc | ios::out);

		string  temp = "instrumentID,type,sequence,tradeDay,updateTime,totalvolume,openinterest,closeprice,volume,openprice,highprice,lowprice,klineType,addposition,openvolume,evenvolume,dealtype,direction,buyprice,buyqty,sellprice,sellqty,weibi,Id,local,";

		temp.append("volume_tick,");
		temp.append("macd_tick,dif_tick,dea_tick,");
		temp.append("k_tick,d_tick,j_tick,");
		temp.append("ma5_tick,ma10_tick,ma20_tick,ma60_tick,");
		temp.append("bollup_tick,bolldown_tick,bollmid_tick,");


		temp.append("updateTime_1min,volume_1min,open_1min,high_1min,low_1min,");
		temp.append("macd_1min,dif_1min,dea_1min,");
		temp.append("k_1min,d_1min,j_1min,");
		temp.append("ma5_1min,ma10_1min,ma20_1min,ma60_1min,");
		temp.append("bollup_1min,bolldown_1min,bollmid_1min,");

		temp.append("updateTime_3min,volume_3min,open_3min,high_3min,low_3min,");
		temp.append("macd_3min,dif_3min,dea_3min,");
		temp.append("k_3min,d_3min,j_3min,");
		temp.append("ma5_3min,ma10_3min,ma20_3min,ma60_3min,");
		temp.append("bollup_3min,bolldown_3min,bollmid_3min,");

		temp.append("updateTime_5min,volume_5min,open_5min,high_5min,low_5min,");
		temp.append("macd_5min,dif_5min,dea_5min,");
		temp.append("k_5min,d_5min,j_5min,");
		temp.append("ma5_5min,ma10_5min,ma20_5min,ma60_5min,");
		temp.append("bollup_5min,bolldown_5min,bollmid_5min,");

		temp.append("updateTime_15min,volume_15min,open_15min,high_15min,low_15min,");
		temp.append("macd_15min,dif_15min,dea_15min,");
		temp.append("k_15min,d_15min,j_15min,");
		temp.append("ma5_15min,ma10_15min,ma20_15min,ma60_15min,");
		temp.append("bollup_15min,bolldown_15min,bollmid_15min,");


		temp.append("updateTime_30min,volume_30min,open_30min,high_30min,low_30min,");
		temp.append("macd_30min,dif_30min,dea_30min,");
		temp.append("k_30min,d_30min,j_30min,");
		temp.append("ma5_30min,ma10_30min,ma20_30min,ma60_30min,");
		temp.append("bollup_30min,bolldown_30min,bollmid_30min,");
		temp.append("open_day,high_day,low_day,close_day,");

		//lag1指标
		temp.append("open_1min_lag1,high_1min_lag1,low_1min_lag1,close_1min_lag1,");
		temp.append("macd_1min_lag1,dif_1min_lag1,dea_1min_lag1,");
		temp.append("k_1min_lag1,d_1min_lag1,");
		temp.append("ma5_1min_lag1,ma10_1min_lag1,ma20_1min_lag1,ma60_1min_lag1,");
		//temp.append("bollup_1min,bolldown_1min,bollmid_1min,");
		temp.append("dif_open_1min,dif_high_1min,dif_low_1min,dif_close_1min,");
		temp.append("dif_macd_1min,dif_dif_1min,dif_dea_1min,");
		temp.append("dif_k_1min,dif_d_1min,");
		temp.append("dif_ma5_1min,dif_ma10_1min,dif_ma20_1min,dif_ma60_1min,");
		//	temp.append("dif_bollup_1min,dif_bolldown_1min,dif_bollmid_1min,");


		temp.append("open_3min_lag1,high_3min_lag1,low_3min_lag1,close_3min_lag1,");
		temp.append("macd_3min_lag1,dif_3min_lag1,dea_3min_lag1,");
		temp.append("k_3min_lag1,d_3min_lag1,");
		temp.append("ma5_3min_lag1,ma10_3min_lag1,ma20_3min_lag1,ma60_3min_lag1,");

		temp.append("dif_open_3min,dif_high_3min,dif_low_3min,dif_close_3min,");
		temp.append("dif_macd_3min,dif_dif_3min,dif_dea_3min,");
		temp.append("dif_k_3min,dif_d_3min,");
		temp.append("dif_ma5_3min,dif_ma10_3min,dif_ma20_3min,dif_ma60_3min,");



		temp.append("open_5min_lag1,high_5min_lag1,low_5min_lag1,close_5min_lag1,");
		temp.append("macd_5min_lag1,dif_5min_lag1,dea_5min_lag1,");
		temp.append("k_5min_lag1,d_5min_lag1,");
		temp.append("ma5_5min_lag1,ma10_5min_lag1,ma20_5min_lag1,ma60_5min_lag1,");

		temp.append("dif_open_5min,dif_high_5min,dif_low_5min,dif_close_5min,");
		temp.append("dif_macd_5min,dif_dif_5min,dif_dea_5min,");
		temp.append("dif_k_5min,dif_d_5min,");
		temp.append("dif_ma5_5min,dif_ma10_5min,dif_ma20_5min,dif_ma60_5min,");


		temp.append("open_15min_lag1,high_15min_lag1,low_15min_lag1,close_15min_lag1,");
		temp.append("macd_15min_lag1,dif_15min_lag1,dea_15min_lag1,");
		temp.append("k_15min_lag1,d_15min_lag1,");
		temp.append("ma5_15min_lag1,ma10_15min_lag1,ma20_15min_lag1,ma60_15min_lag1,");

		temp.append("dif_open_15min,dif_high_15min,dif_low_15min,dif_close_15min,");
		temp.append("dif_macd_15min,dif_dif_15min,dif_dea_15min,");
		temp.append("dif_k_15min,dif_d_15min,");
		temp.append("dif_ma5_15min,dif_ma10_15min,dif_ma20_15min,dif_ma60_15min,");

		temp.append("open_30min_lag1,high_30min_lag1,low_30min_lag1,close_30min_lag1,");
		temp.append("macd_30min_lag1,dif_30min_lag1,dea_30min_lag1,");
		temp.append("k_30min_lag1,d_30min_lag1,");
		temp.append("ma5_30min_lag1,ma10_30min_lag1,ma20_30min_lag1,ma60_30min_lag1,");

		temp.append("dif_open_30min,dif_high_30min,dif_low_30min,dif_close_30min,");
		temp.append("dif_macd_30min,dif_dif_30min,dif_dea_30min,");
		temp.append("dif_k_30min,dif_d_30min,");
		temp.append("dif_ma5_30min,dif_ma10_30min,dif_ma20_30min,dif_ma60_30min,");
		temp.append("wr14_1min,wr28_1min,wr34_1min,");
		temp.append("gmma3_1min,gmma5_1min,gmma10_1min,gmma30_1min,gmma45_1min,gmma60_1min,");//GMMA：时间轴（1、3、5、30、60）；均线（3、5、10、30、45、60）
		temp.append("gmma3_3min,gmma5_3min,gmma10_3min,gmma30_3min,gmma45_3min,gmma60_3min,");
		temp.append("gmma3_5min,gmma5_5min,gmma10_5min,gmma30_5min,gmma45_5min,gmma60_5min,");
		temp.append("gmma3_30min,gmma5_30min,gmma10_30min,gmma30_30min,gmma45_30min,gmma60_30min,");
		temp.append("isbase1,isbase2,y_type1,y_type2");
		fwrite << temp << endl;
	}
	else
	{
	  fwrite.open(filename, ios::app);
	}
	fread.close();
	RunTime r;
	r.StartTiming();
	CSVLine csv_tick, csv_1, csv_3, csv_5, csv_15, csv_30;
	TickKline Currenttick;
	Kline Daykline;
	//初始化变量
	memset(&csv_tick,0,sizeof(CSVLine));
	memset(&csv_1, 0, sizeof(CSVLine));
	memset(&csv_3, 0, sizeof(CSVLine));
	memset(&csv_5, 0, sizeof(CSVLine));
	memset(&csv_15, 0, sizeof(CSVLine));
	memset(&csv_30, 0, sizeof(CSVLine));
	memset(&Currenttick, 0, sizeof(TickKline));
	memset(&Daykline, 0, sizeof(Kline));


	this->ProductOneKind(id, TICK, csv_tick);
	this->ProductOneKind(id, ONEMIN, csv_1);
	this->ProductOneKind(id, THREEMIN, csv_3);
	this->ProductOneKind(id, FIVEMIN, csv_5);
	this->ProductOneKind(id, FIFTEENMIN, csv_15);
	this->ProductOneKind(id, THIRTMIN, csv_30);
	this->GetCurrenttickByid(id, Currenttick);
	this->GetCurrentDayData(id, Daykline);

	r.EndTiming();
	SaveindexCsv(fwrite, Currenttick,csv_tick, csv_1, csv_3, csv_5, csv_15, csv_30, Daykline);
}

void CTPDatatransForKline::SaveindexCsv(ofstream & fwrite, TickKline &Currenttickk, const CSVLine &csv_tick, const CSVLine & csv_1, const CSVLine & csv_3, const CSVLine & csv_5, const CSVLine & csv_15, const CSVLine & csv_30, Kline &daykline)
{

	stringstream temp;
	temp.setf(ios::fixed);
	temp.precision(6);
	temp << Currenttickk.instumentId << "," << Currenttickk.type << "," << Currenttickk.sequence << "," << Currenttickk.tradeDay << "," << Currenttickk.updateTime << ","<< Currenttickk.totalvolume<<","
         << Currenttickk.openInterest<<","<< Currenttickk.closeprice<<","<< Currenttickk.volume<<","<< Currenttickk.openprice<<","<< Currenttickk.highprice<<","<< Currenttickk.lowprice<<","<< Currenttickk.klineType<<","
		<< Currenttickk.addposition<<","<< Currenttickk.kaicangvolume<<","<< Currenttickk.pingcangvolume<<","<< Currenttickk.Dealtype<<","<< Currenttickk.direction<<","<< Currenttickk.buyprice<<","<< Currenttickk.buyqty<<","
		<< Currenttickk.sellprice<<","<< Currenttickk.sellqty<<","<< Currenttickk.weibi<<","<< Currenttickk.id<<","<< Currenttickk.local<<","
		<< csv_tick.vol << ","
		<< csv_tick.MacdT.MACD << "," << csv_tick.MacdT.DIFF << "," << csv_tick.MacdT.DEA << ","
		<< csv_tick.kdj.k << "," << csv_tick.kdj.d << "," << csv_tick.kdj.j << ","
		<< csv_tick.ma5 << "," << csv_tick.ma10 << "," << csv_tick.ma20 << "," << csv_tick.ma60 << ","
		<< csv_tick.boll.UP << "," << csv_tick.boll.DOWN << "," << csv_tick.boll.MB << ","

		<< csv_1.datatime << "," << csv_1.vol << "," << csv_1.open << "," << csv_1.max << "," << csv_1.min << ","
		<< csv_1.MacdT.MACD << "," << csv_1.MacdT.DIFF << "," << csv_1.MacdT.DEA << ","
		<< csv_1.kdj.k << "," << csv_1.kdj.d << "," << csv_1.kdj.j << ","
		<< csv_1.ma5 << "," << csv_1.ma10 << "," << csv_1.ma20 << "," << csv_1.ma60 << ","
		<< csv_1.boll.UP << "," << csv_1.boll.DOWN << "," << csv_1.boll.MB << ","



		<< csv_3.datatime << "," << csv_3.vol << "," << csv_3.open << "," << csv_3.max << "," << csv_3.min << ","
		<< csv_3.MacdT.MACD << "," << csv_3.MacdT.DIFF << "," << csv_3.MacdT.DEA << ","
		<< csv_3.kdj.k << "," << csv_3.kdj.d << "," << csv_3.kdj.j << ","
		<< csv_3.ma5 << "," << csv_3.ma10 << "," << csv_3.ma20 << "," << csv_3.ma60 << ","
		<< csv_3.boll.UP << "," << csv_3.boll.DOWN << "," << csv_3.boll.MB << ","


		<< csv_5.datatime << "," << csv_5.vol << "," << csv_5.open << "," << csv_5.max << "," << csv_5.min << ","
		<< csv_5.MacdT.MACD << "," << csv_5.MacdT.DIFF << "," << csv_5.MacdT.DEA << ","
		<< csv_5.kdj.k << "," << csv_5.kdj.d << "," << csv_5.kdj.j << ","
		<< csv_5.ma5 << "," << csv_5.ma10 << "," << csv_5.ma20 << "," << csv_5.ma60 << ","
		<< csv_5.boll.UP << "," << csv_5.boll.DOWN << "," << csv_5.boll.MB << ","



		<< csv_15.datatime << "," << csv_15.vol << "," << csv_15.open << "," << csv_15.max << "," << csv_15.min << ","

		<< csv_15.MacdT.MACD << "," << csv_15.MacdT.DIFF << "," << csv_15.MacdT.DEA << ","

		<< csv_15.kdj.k << "," << csv_15.kdj.d << "," << csv_15.kdj.j << ","

		<< csv_15.ma5 << "," << csv_15.ma10 << "," << csv_15.ma20 << "," << csv_15.ma60 << ","

		<< csv_15.boll.UP << "," << csv_15.boll.DOWN << "," << csv_15.boll.MB << ","



		<< csv_30.datatime << "," << csv_30.vol << "," << csv_30.open << "," << csv_30.max << "," << csv_30.min << ","

		<< csv_30.MacdT.MACD << "," << csv_30.MacdT.DIFF << "," << csv_30.MacdT.DEA << ","

		<< csv_30.kdj.k << "," << csv_30.kdj.d << "," << csv_30.kdj.j << ","

		<< csv_30.ma5 << "," << csv_30.ma10 << "," << csv_30.ma20 << "," << csv_30.ma60 << ","

		<< csv_30.boll.UP << "," << csv_30.boll.DOWN << "," << csv_30.boll.MB<<","
		
		<<daykline.openprice<<","<<daykline.highprice<<","<<daykline.lowprice<<","<<daykline.closeprice<<","
		
		//lag1 1min的指标
		<<csv_1.open_lag1<<","<< csv_1.high_lag1<<","<< csv_1.low_lag1 <<","<< csv_1.close_lag1<<","
		<<csv_1.MacdT_lag1.MACD<<","<< csv_1.MacdT_lag1.DIFF<<","<<csv_1.MacdT_lag1.DEA<<","
		<<csv_1.kdj_lag1.k<<","<<csv_1.kdj_lag1.d<<","
		<< csv_1.ma5_lag1<<","<< csv_1.ma10_lag1<<","<<csv_1.ma20_lag1<<","<< csv_1.ma60_lag1<<","

		<< csv_1.open-csv_1.open_lag1 << "," << csv_1.max- csv_1.high_lag1 << "," << csv_1.min- csv_1.low_lag1 <<"," << csv_1.close- csv_1.close_lag1 << ","
		<< csv_1.MacdT.MACD-csv_1.MacdT_lag1.MACD << "," << csv_1.MacdT.DIFF- csv_1.MacdT_lag1.DIFF << "," << csv_1.MacdT.DEA-csv_1.MacdT_lag1.DEA << ","
		<< csv_1.kdj.k-csv_1.kdj_lag1.k << "," << csv_1.kdj.d- csv_1.kdj_lag1.d << ","
		<< csv_1.ma5- csv_1.ma5_lag1 << "," << csv_1.ma10-csv_1.ma10_lag1 << "," << csv_1.ma20- csv_1.ma20_lag1 << "," << csv_1.ma60-csv_1.ma60_lag1 << ","
		
		//lag1 3min的指标
		<< csv_3.open_lag1 << "," << csv_3.high_lag1 << "," << csv_3.low_lag1 << "," << csv_3.close_lag1 << ","
		<< csv_3.MacdT_lag1.MACD << "," << csv_3.MacdT_lag1.DIFF << "," << csv_3.MacdT_lag1.DEA << ","
		<< csv_3.kdj_lag1.k << "," << csv_3.kdj_lag1.d << ","
		<< csv_3.ma5_lag1 << "," << csv_3.ma10_lag1 << "," << csv_3.ma20_lag1 << "," << csv_3.ma60_lag1 << ","

		<< csv_3.open - csv_3.open_lag1 << "," << csv_3.max - csv_3.high_lag1 << "," << csv_3.min - csv_3.low_lag1 << "," << csv_3.close - csv_3.close_lag1 << ","
		<< csv_3.MacdT.MACD - csv_3.MacdT_lag1.MACD << "," << csv_3.MacdT.DIFF - csv_3.MacdT_lag1.DIFF << "," << csv_3.MacdT.DEA - csv_3.MacdT_lag1.DEA << ","
		<< csv_3.kdj.k - csv_3.kdj_lag1.k << "," << csv_3.kdj.d - csv_3.kdj_lag1.d << ","
		<< csv_3.ma5 - csv_3.ma5_lag1 << "," << csv_3.ma10 - csv_3.ma10_lag1 << "," << csv_3.ma20 - csv_3.ma20_lag1 << "," << csv_3.ma60 - csv_3.ma60_lag1 << ","

		//lag1 5min的指标
		<< csv_5.open_lag1 << "," << csv_5.high_lag1 << "," << csv_5.low_lag1 << "," << csv_5.close_lag1 << ","
		<< csv_5.MacdT_lag1.MACD << "," << csv_5.MacdT_lag1.DIFF << "," << csv_5.MacdT_lag1.DEA << ","
		<< csv_5.kdj_lag1.k << "," << csv_5.kdj_lag1.d << ","
		<< csv_5.ma5_lag1 << "," << csv_5.ma10_lag1 << "," << csv_5.ma20_lag1 << "," << csv_5.ma60_lag1 << ","

		<< csv_5.open - csv_5.open_lag1 << "," << csv_5.max - csv_5.high_lag1 << "," << csv_5.min - csv_5.low_lag1 << "," << csv_5.close - csv_5.close_lag1 << ","
		<< csv_5.MacdT.MACD - csv_5.MacdT_lag1.MACD << "," << csv_5.MacdT.DIFF - csv_5.MacdT_lag1.DIFF << "," << csv_5.MacdT.DEA - csv_5.MacdT_lag1.DEA << ","
		<< csv_5.kdj.k - csv_5.kdj_lag1.k << "," << csv_5.kdj.d - csv_5.kdj_lag1.d << ","
		<< csv_5.ma5 - csv_5.ma5_lag1 << "," << csv_5.ma10 - csv_5.ma10_lag1 << "," << csv_5.ma20 - csv_5.ma20_lag1 << "," << csv_5.ma60 - csv_5.ma60_lag1 << ","

		//lag1 15min的指标
		<< csv_15.open_lag1 << "," << csv_15.high_lag1 << "," << csv_15.low_lag1 << "," << csv_15.close_lag1 << ","
		<< csv_15.MacdT_lag1.MACD << "," << csv_15.MacdT_lag1.DIFF << "," << csv_15.MacdT_lag1.DEA << ","
		<< csv_15.kdj_lag1.k << "," << csv_15.kdj_lag1.d << ","
		<< csv_15.ma5_lag1 << "," << csv_15.ma10_lag1 << "," << csv_15.ma20_lag1 << "," << csv_15.ma60_lag1 << ","

		<< csv_15.open - csv_15.open_lag1 << "," << csv_15.max - csv_15.high_lag1 << "," << csv_15.min - csv_15.low_lag1 << "," << csv_15.close - csv_15.close_lag1 << ","
		<< csv_15.MacdT.MACD - csv_15.MacdT_lag1.MACD << "," << csv_15.MacdT.DIFF - csv_15.MacdT_lag1.DIFF << "," << csv_15.MacdT.DEA - csv_15.MacdT_lag1.DEA << ","
		<< csv_15.kdj.k - csv_15.kdj_lag1.k << "," << csv_15.kdj.d - csv_15.kdj_lag1.d << ","
		<< csv_15.ma5 - csv_15.ma5_lag1 << "," << csv_15.ma10 - csv_15.ma10_lag1 << "," << csv_15.ma20 - csv_15.ma20_lag1 << "," << csv_15.ma60 - csv_15.ma60_lag1 << ","

		//lag1 30min的指标
		<< csv_30.open_lag1 << "," << csv_30.high_lag1 << "," << csv_30.low_lag1 << "," << csv_30.close_lag1 << ","
		<< csv_30.MacdT_lag1.MACD << "," << csv_30.MacdT_lag1.DIFF << "," << csv_30.MacdT_lag1.DEA << ","
		<< csv_30.kdj_lag1.k << "," << csv_30.kdj_lag1.d << ","
		<< csv_30.ma5_lag1 << "," << csv_30.ma10_lag1 << "," << csv_30.ma20_lag1 << "," << csv_30.ma60_lag1 << ","

		<< csv_30.open - csv_30.open_lag1 << "," << csv_30.max - csv_30.high_lag1 << "," << csv_30.min - csv_30.low_lag1 << "," << csv_30.close - csv_30.close_lag1 << ","
		<< csv_30.MacdT.MACD - csv_30.MacdT_lag1.MACD << "," << csv_30.MacdT.DIFF - csv_30.MacdT_lag1.DIFF << "," << csv_30.MacdT.DEA - csv_30.MacdT_lag1.DEA << ","
		<< csv_30.kdj.k - csv_30.kdj_lag1.k << "," << csv_30.kdj.d - csv_30.kdj_lag1.d << ","
		<< csv_30.ma5 - csv_30.ma5_lag1 << "," << csv_30.ma10 - csv_30.ma10_lag1 << "," << csv_30.ma20 - csv_30.ma20_lag1 << "," << csv_30.ma60 - csv_30.ma60_lag1 
		<< "," << csv_1.wr14 << "," << csv_1.wr28 << "," << csv_1.wr34 << ","
		<< csv_1.gmma3 << "," << csv_1.gmma5 << "," << csv_1.gmma10 << "," << csv_1.gmma30 << "," << csv_1.gmma45 << "," << csv_1.gmma60 << ","
		<< csv_3.gmma3 << "," << csv_3.gmma5 << "," << csv_3.gmma10 << "," << csv_3.gmma30 << "," << csv_3.gmma45 << "," << csv_3.gmma60 << ","
		<< csv_5.gmma3 << "," << csv_5.gmma5 << "," << csv_5.gmma10 << "," << csv_5.gmma30 << "," << csv_5.gmma45 << "," << csv_5.gmma60 << ","
		<< csv_30.gmma3 << "," << csv_30.gmma5 << "," << csv_30.gmma10 << "," << csv_30.gmma30 << "," << csv_30.gmma45 << "," << csv_30.gmma60 << ","
		<< isbase1 << "," << isbase2 << "," << y_type1 << "," << y_type2 << "\n";


	fwrite << temp.str();
	fday << temp.str();

	//关闭文件流
	fday.close();
	fwrite.close();
}

void CTPDatatransForKline::Cal2difBaseprice(subtick sub_tick)
{

	writelocal(sub_tick.local, sub_tick.tickprice);
	 //string currentpriceupdateTime_hour = string(tick->local).substr(11, 2);// 从local时间中截取中中间的hour
	 string currentpricehms = string(sub_tick.local).substr(11,8);// 从local时间中截取时分秒
	if (last3pricetradeday == "")
	{
		strcpy(current2pricekline.instumentID, sub_tick.instrumentID.c_str());
		strcpy(current2pricekline.tradeDay, sub_tick.tradeDay.c_str());
		current2pricekline.openprice = sub_tick.tickprice;
		current2pricekline.highprice = sub_tick.tickprice;
		current2pricekline.lowprice = sub_tick.tickprice;
		current2pricekline.closeprice = sub_tick.tickprice;
		strcpy(current2pricekline.openticklocal, sub_tick.local.c_str());
		strcpy(current2pricekline.closeticklocal, sub_tick.local.c_str());
		num = 0;
		
	}
	else if (sub_tick.tradeDay!=last3pricetradeday)
	{
		//if (IsRestart == false)  //避免重复记录
		//{
		//	Save2difpriceCsv();
		//}
		strcpy(current2pricekline.instumentID, sub_tick.instrumentID.c_str());
		strcpy(current2pricekline.tradeDay, sub_tick.tradeDay.c_str());
		current2pricekline.openprice = sub_tick.tickprice;
		current2pricekline.closeprice = sub_tick.tickprice;
		current2pricekline.highprice = sub_tick.tickprice;
		current2pricekline.lowprice = sub_tick.tickprice;
		strcpy(current2pricekline.openticklocal, sub_tick.local.c_str());
		strcpy(current2pricekline.closeticklocal, sub_tick.local.c_str());
		num = 0;
	}
	else if((strcmp(currentpricehms.c_str(),"15:00:00")==0|| strcmp(currentpricehms.c_str(), "23:00:00") == 0)&&(currentpricehms!= endtime) ) //当时间到达日盘收盘时,或者当时间到达夜盘收盘时。作为一个新的基价存入数据库
	{
		//if (IsRestart == false)  //避免重复记录
		//{
			current2pricekline.closeprice = sub_tick.tickprice;
			strcpy(current2pricekline.closeticklocal, sub_tick.local.c_str());
			current2pricekline.duration = num;
			if (current2pricekline.highprice < sub_tick.tickprice)
			{
				current2pricekline.highprice = sub_tick.tickprice;
			}
			if (sub_tick.tickprice < current2pricekline.lowprice)
			{
				current2pricekline.lowprice = sub_tick.tickprice;
			}
			Save2difpriceCsv();
			endtime = currentpricehms;
		//}
		strcpy(current2pricekline.instumentID, sub_tick.instrumentID.c_str());
		strcpy(current2pricekline.tradeDay, sub_tick.tradeDay.c_str());
		current2pricekline.openprice = sub_tick.tickprice;
		current2pricekline.closeprice = sub_tick.tickprice;
		current2pricekline.highprice = sub_tick.tickprice;
		current2pricekline.lowprice = sub_tick.tickprice;
		strcpy(current2pricekline.openticklocal, sub_tick.local.c_str());
		strcpy(current2pricekline.closeticklocal, sub_tick.local.c_str());
		num = 0;

	}
	else if (IsRestart == true)     /****///判断基价程序是否从重新计算
	{
		current2pricekline.closeprice = sub_tick.tickprice;
		if (current2pricekline.highprice < sub_tick.tickprice)
		{
			current2pricekline.highprice = sub_tick.tickprice;
		}
		if (sub_tick.tickprice < current2pricekline.lowprice)
		{
			current2pricekline.lowprice = sub_tick.tickprice;
		}
		strcpy(current2pricekline.closeticklocal, sub_tick.local.c_str());
		current2pricekline.duration = num;//用来记录两个基价间的tick个数
		if (abs(sub_tick.tickprice - current2pricekline.openprice) >= difprice)
		{
			Save2difpriceCsv();
			strcpy(current2pricekline.instumentID, sub_tick.instrumentID.c_str());
			strcpy(current2pricekline.tradeDay, sub_tick.tradeDay.c_str());
			current2pricekline.openprice = current2pricekline.closeprice;
			current2pricekline.highprice = current2pricekline.closeprice;
			current2pricekline.lowprice = current2pricekline.closeprice;

			strcpy(current2pricekline.openticklocal, current2pricekline.closeticklocal);

			num = 0;
		}

		IsRestart = false;
	}
	else
	{
		current2pricekline.closeprice = sub_tick.tickprice;
		if (current2pricekline.highprice < sub_tick.tickprice)
		{
			current2pricekline.highprice = sub_tick.tickprice;
		}
		if (sub_tick.tickprice < current2pricekline.lowprice)
		{
			current2pricekline.lowprice = sub_tick.tickprice;
		}
		strcpy(current2pricekline.closeticklocal, sub_tick.local.c_str());
		current2pricekline.duration = num;
		if (abs(sub_tick.tickprice - current2pricekline.openprice) >= difprice)
		{
			Save2difpriceCsv();
			IsRestart = true;

			strcpy(current2pricekline.instumentID, sub_tick.instrumentID.c_str());
			strcpy(current2pricekline.tradeDay, sub_tick.tradeDay.c_str());
			current2pricekline.openprice = current2pricekline.closeprice;
			current2pricekline.highprice = current2pricekline.closeprice;
			current2pricekline.lowprice = current2pricekline.closeprice;
		
			strcpy(current2pricekline.openticklocal, current2pricekline.closeticklocal);
			
			num = 0;
		}
		else
		{
		//	writelog(current2pricekline.openprice, sub_tick.tickprice, current2pricekline.openticklocal, sub_tick.local);  //将不满足条件的信息记录起来
		}
		
	}
	num++;
	last3pricetradeday = sub_tick.tradeDay;

}

void CTPDatatransForKline::Save2difpriceCsv()
{
	ifstream fread;
	ofstream fwrite;
	//string filename = "../" + indexcsvpre + ".csv";
	string filename = "C:/" + indexcsvpre + "Base" + ".csv";

	_strupr(const_cast<char*>(filename.c_str()));

	fread.open(filename, ios::in);
	if (fread.peek() == EOF)
	{


		fwrite.open(filename, ios::trunc | ios::out);
		string  temp = "InstrumentID,TradeDay,openprice,highprice,lowprice,closeprice,openticklocal,closeticklocal,duration";
		fwrite << temp << endl;
	}
	else
	{
		fwrite.open(filename, ios::app);
	}
	fread.close();


	stringstream temp;
	temp << current2pricekline.instumentID << "," << current2pricekline.tradeDay << "," << current2pricekline.openprice << "," << current2pricekline.highprice << "," << current2pricekline.lowprice << "," << current2pricekline.closeprice<<","<< current2pricekline.openticklocal << ","
		<< current2pricekline.closeticklocal << "," << current2pricekline.duration << endl;
	fwrite << temp.str();
	fwrite.close();
}

void CTPDatatransForKline::writelog(double baseprice, double tickprice, string baselocal, string ticklocal)
{
	ofstream fwrite;
	string filename = "../log.txt";
	fwrite.open(filename,ios::app);
	stringstream temp;
	temp << baselocal << "  " << baseprice << "  " << ticklocal << "  " << tickprice << endl;
	fwrite << temp.str();

	fwrite.close();

}

void CTPDatatransForKline::writelocal(string local, double tickprice)
{
	ofstream fwrite;
	string filename = "../loglocal.txt";
	fwrite.open(filename, ios::app);
	stringstream temp;
	temp << local << "  " << tickprice<< endl;
	fwrite << temp.str();

	fwrite.close();
}

void CTPDatatransForKline::KLineDataPicker(vector<IndexKLine>& K0, vector<double>& Kdata, string datatype)
{//把一连串k线的开高低收分别放到各自的容器中
	if (datatype == "OPEN")
		for (auto x : K0)	Kdata.push_back(x.open);
	if (datatype == "HIGH")
		for (auto x : K0)	Kdata.push_back(x.max);
	if (datatype == "LOW")
		for (auto x : K0)	Kdata.push_back(x.min);
	if (datatype == "CLOSE")
		for (auto x : K0)	Kdata.push_back(x.close);
}

CTPDatatransForKline::~CTPDatatransForKline()
{
	delete ctpOper;
}
