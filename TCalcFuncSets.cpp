#include "stdafx.h"
#include "TCalcFuncSets.h"
#include "Common.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//���ɵ�dll���������dll�뿽����ͨ���Ű�װĿ¼��T0002/dlls/����,���ڹ�ʽ���������а�

void TestPlugin1(int DataLen,float* pfOUT,float* pfINa,float* pfINb,float* pfINc)
{
	for(int i=0;i<DataLen;i++)
		pfOUT[i]=i;
}
FXing* Search_Di_FXing(vector<KXian*> KXianVector, int start){
	ofstream outfile("out.txt",ios::app);
	outfile <<"from "<<start<< "�����ѵ׷��ͺ���"<<'\n';
	FXing* FX_Di=new FXing;
	return FX_Di;
}
FXing* Search_Ding_FXing(vector<KXian*> KXianVector, int start){
	ofstream outfile("out.txt",ios::app);
	outfile <<"from "<<start<< "�����Ѷ����ͺ���"<<'\n';
	FXing* FX_Di=new FXing;
	FX_Di->First=KXianVector[start-1];
	FX_Di->Second=KXianVector[start];
	int i=1;
	while(BaoHan(FX_Di->Second, KXianVector[start+i])){
		FX_Di->Second->High=KXianVector[start+i]->High;
		i++;
	}
	FX_Di->Third=KXianVector[start+i];
	FXing* FX_Ding=new FXing;
	

	return FX_Ding;
}
std::vector<FXing*> SearchFenXing(vector<KXian*> KXianVector, int start, int fromMax){
	ofstream outfile("out.txt",ios::app);
	std::vector<FXing*> FXingVector;

	if(fromMax==1){
		FXing* Di_FXing = Search_Di_FXing(KXianVector, start);
	}else{
		FXing* Ding_FXing = Search_Ding_FXing(KXianVector, start);
	}
	return FXingVector;

}
void TestPlugin2(int DataLen,float* pfOUT,float* pfINa,float* pfINb,float* pfINc)
{
	ofstream outfile("out.txt",ios::app);	
	std::vector<KXian*> KXianVector;
	//����K������
	for(int i=0; i<DataLen; i++){
		KXian* KX = new KXian;
		KX->High = pfINa[i];
		KX->Low = pfINb[i];
		KX->i = i;
		KXianVector.push_back(KX);
		
	}
	//�ҵ�K����ߵ����͵�
	KXian* KX_Max = KXianVector[0];
	KXian* KX_Min = KXianVector[0];
	for(int i=0; i<KXianVector.size(); i++){
		KXian* KX = KXianVector[i];
		if(KXianVector[i]->High>KX_Max->High){
			KX_Max=KXianVector[i];
		}
		if(KXianVector[i]->Low<KX_Min->Low){
			KX_Min=KXianVector[i];
		}
		//outfile << "��ţ�" << KX->i << "�ߵ㣺" << KX->High << " �͵㣺" << KX->Low <<'\n';
	}
	outfile << "��ߵ㣺" << KX_Max->i << "��͵㣺" << KX_Min->i << "����������" << DataLen <<'\n';
	//�ҵ�Max��Min�ȽϿ�ǰ��һ������ʼ�з��������
	std::vector<FXing*> Fxlist;
	if(KX_Max->i>=KX_Min->i){ //Max��Min�󣬴�Min��ʼ����,fromMax=-1
		if(KX_Min->i!=0)
		{Fxlist = SearchFenXing(KXianVector,KX_Min->i,-1);}
		else
		{Fxlist = SearchFenXing(KXianVector,KX_Max->i,1);}
	}else{
		if(KX_Max->i!=0)
		{Fxlist = SearchFenXing(KXianVector,KX_Max->i,1);}
		else
		{Fxlist = SearchFenXing(KXianVector,KX_Min->i,-1);}
	}

	//�������ָ��
	for(int i=1;i<DataLen-1;i++)
	{
		if(i==KX_Max->i){
			pfOUT[i]=1;
		}
		else if(i==KX_Min->i){
			pfOUT[i]=-1;
		}
		else{
			pfOUT[i]=0;
		}
	}
	outfile<<"------------------------------------------------"<<'\n';
	outfile.close();
	ofstream debug_file("debug.txt",ios::trunc);
	for(int i=0; i<KXianVector.size(); i++){
		debug_file<<KXianVector[i]->High<<" "<<KXianVector[i]->Low<<'\n';
	}
	debug_file.close();
}


//���صĺ���
PluginTCalcFuncInfo g_CalcFuncSets[] = 
{
	{1,(pPluginFUNC)&TestPlugin1},
	{2,(pPluginFUNC)&TestPlugin2},
	{0,NULL},
};

//������TCalc��ע�ắ��
BOOL RegisterTdxFunc(PluginTCalcFuncInfo** pFun)
{
	if(*pFun==NULL)
	{
		(*pFun)=g_CalcFuncSets;
		return TRUE;
	}
	return FALSE;
}




int _tmain(int argc, _TCHAR* argv[])
{
	fstream file;
	file.open("C:\\zd_pazq_hy\\debug2.txt",ios::in);
	vector<float> pfINa_high;
	vector<float> pfINb_low;
	char buf[1024];
    while (file.getline(buf, sizeof(buf))) {
        std:string str(buf);
		vector<string> strarr = mySplit(str," ");
		float high = atof(strarr[0].c_str());
		pfINa_high.push_back(high);
		float low = atof(strarr[1].c_str());
		pfINb_low.push_back(low);
        cout << str << endl;
    }
	file.close();
	int DataLength = pfINa_high.size();
	float *out = new float[DataLength];
	float *pfINa = new float[DataLength];
	float *pfINb = new float[DataLength];
	float *pfINc = new float[DataLength];
	memcpy(pfINa, &pfINa_high[0], pfINa_high.size()*sizeof(float)); 
	memcpy(pfINb, &pfINb_low[0], pfINb_low.size()*sizeof(float)); 
	TestPlugin2(DataLength,out,pfINa,pfINb,pfINc);
	return 0;
}

