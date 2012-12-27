
#include <Windows.h>
#include <iostream>
#include <iomanip>

#include "preparefiles.h"
#include "analyzecode.h"
#include "CalcRdata.h"
#include "CalcText.h"
#include "FormData.h"
#include "FormHeader.h"
#include "ReformEcall.h"
#include "DataStructure.h"
#include "ReformData.h"
#include "OutputExe.h" 
#include "label.h"
#include "func.h"
#include "GlobalVar.h"
#include "FormRsrc.h"

#include "Error.h"

#define loop(a,b) for(int a=0;a<b;a++)

using namespace std;

int main(int argc, char *argv[])
{
	cout<<"LLC 0.005"<<endl;

	if(argc==1){
		cout<<"不正なファイル指定"<<endl;
		Error();
	}
	mdlFileName=argv[1];
	//cout<<argv[1]<<endl;

	PrepareFiles();

	AnalyzeCode();

	FormHeader();
	CalcText();
	CalcRdata();
	FormRdata();
	FormData();
	FormRsrc();

	FormHeader2();

	//ここまででサイズとポジションが決まり
	//バイナリができる。
	//ここからはバイナリを書き換える。

	ReformEcall();
	ReformData();
	ReformJmp();
	ReformCall();
	ReformPtrFunc();
	ReformPtrEfunc();
	ReformGvar();

	//ファイルを生成する。

	OutputExe();
	//cout<<"終了"<<endl;
	cout<<"OK"<<endl;

	return 0;
}


	/*
	for(int i=0;i<::sizeHeader;i++){
		if((i)%16==0) cout<<"\n"<<hex<<uppercase<<setfill('0')<<setw(4)<<i<<"   ";
		cout<<hex<<setw(2)<<uppercase<<setfill('0')<<(int)binOfHeader[i]<<"";
		if((i+1)%4!=0) cout<<" ";
		if((i+1)%4==0&&(i+1)%16!=0) cout<<" - ";
	}
	cout<<endl;
	
	for(int i=0;i<::sizeTextFile;i++){
		if((i)%16==0) cout<<"\n"<<hex<<uppercase<<setfill('0')<<setw(4)<<i<<"   ";
		cout<<hex<<setw(2)<<uppercase<<setfill('0')<<(int)binOfText[i]<<"";
		if((i+1)%4!=0) cout<<" ";
		if((i+1)%4==0&&(i+1)%16!=0) cout<<" - ";
	}
	cout<<endl;


	cout<<sizeRdata<<endl;
	cout<<::sizeRdataFile<<endl;
	for(int i=0;i<::sizeRdataFile;i++){
		if((i)%16==0) cout<<"\n"<<hex<<uppercase<<setfill('0')<<setw(4)<<i<<"   ";
		cout<<hex<<setw(2)<<uppercase<<setfill('0')<<(int)binOfRdata[i]<<"";
		if((i+1)%4!=0) cout<<" ";
		if((i+1)%4==0&&(i+1)%16!=0) cout<<" - ";
	}
	cout<<endl;

	for(int i=0;i<::sizeDataFile;i++){
		if((i)%16==0) cout<<"\n"<<hex<<uppercase<<setfill('0')<<setw(4)<<i<<"   ";
		cout<<hex<<setw(2)<<uppercase<<setfill('0')<<(int)binOfData[i]<<"";
		if((i+1)%4!=0) cout<<" ";
		if((i+1)%4==0&&(i+1)%16!=0) cout<<" - ";
	}
	cout<<endl;
	*/