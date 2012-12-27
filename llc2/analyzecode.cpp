#include "Error.h"
#include <windows.h>
#include <string>
#include <list>
#include <vector>
#include <iostream>

#include "UsReadFile.h"
#include "DataStructure.h"
#include "preparefiles.h"
#include "analyzecode.h"
#include "alignment.h"

using namespace std;


list<dataOfDll> dataOfDlls;

int sizeIAT=0;
int posIAT=0;
int sizeIT=0;
int posIT=0;
int sizeLAT=0;
int posLAT=0;

int posDataDll=0;
int posDataEfunc=0;


int sumOfDll=0;
int sumDataDll=0;

int sumDataEfunc=0;
int sumOfEfunc=0;

vector<unsigned char> binOfCode;
vector<unsigned char> binOfCodeEcall;
vector<unsigned char> binOfData;

string curDll="";
int fileSize;
void AnalyzeCode(void)
{
	int data;
	//DWORD lpNumberOfByte;
	int count=0;
	

	//binOfCode.resize(0,0);
	//binOfCodeEcall.resize(0,0);
	//binOfData.resize(0,0);

	fileSize=SetFilePointer(mdlFile,0,0,FILE_END);
	//cout<<"���Ԍ���t�@�C���T�C�Y"<<fileSize<<endl;

	while(1)
	{
		if(count>fileSize-4) Error();
		if( UsReadFile( mdlFile, count, 4,&data) == 0 )
		{//�G���[�Ȃ�
			cout<<"���Ԍ���t�@�C��Read�G���["<<endl;
			Error();
		}else
		{//OK
			if( AnalyzePattern(count,data) == 0 )
			{
				//cout<<"�I��"<<endl;
				break;
			}
		}

	}
	return;
}


int AnalyzePattern(int &count,int data_)
{
	switch(data_)
	{
	case eof:
		//cout<<"EOF"<<endl;
		return 0;
		break;

	case DLL:
		//cout<<"DLL���m"<<endl;
		count+=4;
		AnalyzePatternDLL(count);
		break;
	case efunc:
		//cout<<"efunc���m"<<endl;
		count+=4;
		AnalyzePatternEfunc(count);
		break;
	case code:
		count+=4;
		//cout<<"code���m"<<endl;
		AnalyzePatternCode(count);
		break;
	case ecall:
		count+=4;
		//cout<<"ecall���m"<<endl;
		AnalyzePatternEcall(count);
		break;
	case ptrefunc:
		count+=4;
		//cout<<"ecall���m"<<endl;
		AnalyzePatternPtrEfunc(count);
		break;
	case data:
		count+=4;
		//cout<<"data���m"<<endl;
		AnalyzePatternData(count);
		break;
	case label:
		count+=4;
		//cout<<"lebel���m"<<endl;
		AnalyzePatternLabel(count);
		break;
	case jmp:
		count+=4;
		//cout<<"jmp���m"<<endl;
		AnalyzePatternJmp(count);
		break;
	case jmpcc:
		count+=4;
		//cout<<"jmpcc���m"<<endl;
		AnalyzePatternJmpcc(count);
		break;
	case func:
		count+=4;
		//cout<<"func���m"<<endl;
		AnalyzePatternFunc(count);
		break;
	case call:
		count+=4;
		//cout<<"call���m"<<endl;
		AnalyzePatternCall(count);
		break;
	case ptrfunc:
		count+=4;
		//cout<<"ptrfunc���m"<<endl;
		AnalyzePatternPtrFunc(count);
		break;
	case gvarini:
		count+=4;
		//cout<<"gvarini���m"<<endl;
		AnalyzePatternGvarIni(count);
		break;
	case ptrgvar:
		count+=4;
		//cout<<"ptrgvar���m"<<endl;
		AnalyzePatternPtrGvar(count);
		break;
	case mode:
		count+=4;
		//cout<<"mode���m"<<endl;
		AnalyzePatternMode(count);
		break;
	default:
		cout<<"�s���ȃR�[�h"<<hex<<data<<endl;
		Error();
		break;
	}
	return 1;
}


void AnalyzePatternDLL(int &count)
{
	int bufferLen;
	char *buffer;
	UsReadFile( mdlFile, count , 4,&bufferLen);
	count+=4;
	buffer=new char[bufferLen];

	UsReadFile( mdlFile, count , bufferLen,buffer);
	count+=bufferLen;
	//cout<<buffer<<endl;

	string str;
	str=buffer;

	int f_match=0;
	
	list<dataOfDll>::iterator it = ::dataOfDlls.begin();
	while(it!=::dataOfDlls.end())
	{

		if((*it).dllName==str)
		{
			f_match=1;//��v������t���O���Ă�
			//cout<<str<<" ����DLL�͓o�^�ς�"<<endl;
		}
		//cout<<(*it).dllName<<":"<<str<<endl;

		it++;
	}

	curDll=str;
	if(f_match==0)
	{
		dataOfDll a;
		a.dllName=str;
		a.numOfDll=sumOfDll;
		a.posInDataDll=sumDataDll;

		sumOfDll++;
		sumDataDll+=
			alignment(str.size()+1,2);

		::dataOfDlls.push_back(a);
		//cout<<str<<"��o�^���܂���"<<endl;
	}


	return;
}



void AnalyzePatternEfunc(int &count)
{
	int bufferLen;
	char *buffer;
	UsReadFile( mdlFile, count , 4,&bufferLen);
	count+=4;
	buffer=new char[bufferLen];

	UsReadFile( mdlFile, count , bufferLen,buffer);
	count+=bufferLen;
	//cout<<count<<endl;
	//cout<<bufferLen<<endl;
	string str;
	str=buffer;

	if(curDll!=""){

		list<dataOfDll>::iterator it=::dataOfDlls.begin();
		while(it!=::dataOfDlls.end()){
			if((*it).dllName==curDll){

				list<dataOfEfunc>::iterator
					it2=(*it).dataOfEfuncs.begin();
				int f_match=0;
				while(it2!=(*it).dataOfEfuncs.end())
				{
					//cout<<str<<":"<<(*it2).efuncName<<endl;
					if((*it2).efuncName==str){
						//cout<<str<<"���łɂ���efunc�͓o�^����Ă܂�"<<endl;
						f_match=1;
					}
					it2++;
				}
				if(f_match==0){
					dataOfEfunc a;
					a.efuncName=str;
					a.numEfunc=(*it).numOfEfuncs;//0����n�܂�
					a.posInFLAT=(*it).numOfEfuncs*4;
					a.posInSLAT=(*it).numOfEfuncs*4;
					a.posDataEfunc=sumDataEfunc;
					a.posInCodeEcall=sumOfEfunc*6+2;

					//a.numEfuncStr=(*it).sumOfEfuncStrSize;

					(*it).dataOfEfuncs.push_back(a);

					(*it).numOfEfuncs++;
					(*it).sizeFLAT=(*it).numOfEfuncs*4;
					(*it).sizeSLAT=(*it).numOfEfuncs*4;
					sumOfEfunc++;
					sumDataEfunc+=
						alignment(2+str.size()+1,2);//�������l��
					//(*it).sumOfEfuncStrSize+=
					//	alignment(2+str.size()+1,2);//�������l��

					char b[]={0xff,0x25,0,0,0,0};
					for(int i=0;i<6;i++){
						binOfCodeEcall.push_back(b[i]);
					}
	
					
					//cout<<str<<"��o�^���܂���"<<endl;
				}
				break;
			}
			it++;
		}
	}else{
		cout<<"efunc�̓o�^�ɂ�����DLL�̎w�肪�s��"<<endl;
		Error();
	}


	return;
}


void AnalyzePatternCode(int &count)
{
	int bufferLen;
	char *buffer;
	UsReadFile( mdlFile, count , 4,&bufferLen);
	count+=4;
	buffer=new char[bufferLen];
	//cout<<"codesize "<<bufferLen<<endl;

	UsReadFile( mdlFile, count , bufferLen,buffer);
	count+=bufferLen;

	for(int i=0;i<bufferLen;i++){
		binOfCode.push_back(buffer[i]);
	}
	//cout<<"�ʉ�"<<endl;
	//cout<<hex<<binOfCode.size()<<endl;

	return;
}


list<dataOfEcall> dataOfEcalls;
void AnalyzePatternEcall(int &count)
{
	int bufferLen;
	char *buffer;
	UsReadFile( mdlFile, count , 4,&bufferLen);
	count+=4;
	buffer=new char[bufferLen];

	UsReadFile( mdlFile, count , bufferLen,buffer);
	count+=bufferLen;
	string str;
	str=buffer;

	int f_match=0;
	list<dataOfDll>::iterator it=::dataOfDlls.begin();
	while(it!=::dataOfDlls.end())
	{
		list<dataOfEfunc>::iterator
			it2=(*it).dataOfEfuncs.begin();
		while(it2!=(*it).dataOfEfuncs.end())
		{
			if((*it2).efuncName==str){
				//cout<<str<<"����"<<endl;

				int b=binOfCode.size();
				//cout<<"binOfCode.size()"<< b<<endl;
				binOfCode.push_back(0xE8);
				binOfCode.push_back(0);
				binOfCode.push_back(0);
				binOfCode.push_back(0);
				binOfCode.push_back(0);

				//cout<<"E8 "<<binOfCode.size()<<endl;

				dataOfEcall a;
				a.str=str;
				a.posInsertCode=b+1;
				a.posBeginInCode=b+5;
				a.posEndInCodeEcall=
					(*it2).posInCodeEcall-2;//FF25�̕�
				dataOfEcalls.push_back(a);
				//cout<< a.posInsertCode<<endl;
				//cout<< a.posBeginInCode<<endl;
				//cout<< a.posEndInCodeEcall<<endl;
				f_match=1;
			}
			it2++;
			if(f_match==1) break;
		}
		if(f_match==1) break;
		it++;
	}
	if(f_match==0){
				cout<<str<<"�����ł���"<<endl;
				Error();
	}
	return;

}
list<dataOfPtrEfunc> dataOfPtrEfuncs;
void AnalyzePatternPtrEfunc(int &count)
{
	int bufferLen;
	char *buffer;
	UsReadFile( mdlFile, count , 4,&bufferLen);
	count+=4;
	buffer=new char[bufferLen];

	UsReadFile( mdlFile, count , bufferLen,buffer);
	count+=bufferLen;
	string str;
	str=buffer;

	int b=binOfCode.size();
	binOfCode.push_back(0);
	binOfCode.push_back(0);
	binOfCode.push_back(0);
	binOfCode.push_back(0);
	dataOfPtrEfunc a;
	a.efuncName=str;
	a.posInCode=b;
	dataOfPtrEfuncs.push_back(a);
	//cout<<"�O���֐� "<<str<<endl;
	//cout<<"�ʒu"<<a.posInCode<<endl;
	return;

}

list<dataOfData> dataOfDatas;
void AnalyzePatternData(int &count)
{
	int bufferLen;
	char *buffer;
	UsReadFile( mdlFile, count , 4,&bufferLen);
	count+=4;
	buffer=new char[bufferLen];

	UsReadFile( mdlFile, count , bufferLen,buffer);
	count+=bufferLen;
	//cout<<buffer<<endl;

	int c=binOfData.size();
	for(int i=0;i<bufferLen;i++)
	{
		binOfData.push_back(buffer[i]);
	}
	//cout<<":::: "<<binOfData.size()<<endl;

	int a=binOfCode.size();
	//binOfCode.push_back(0x68);
	binOfCode.push_back(0);
	binOfCode.push_back(0);
	binOfCode.push_back(0);
	binOfCode.push_back(0);

	dataOfData b;
	b.posInsertCode=a;
	b.posInData=c;

	::dataOfDatas.push_back(b);

	return;

}

list<dataOfLabel> dataOfLabels;
string curFuncName="";
void AnalyzePatternLabel(int &count)
{
	int bufferLen;
	char *buffer;
	UsReadFile( mdlFile, count , 4,&bufferLen);
	count+=4;
	buffer=new char[bufferLen];

	UsReadFile( mdlFile, count , bufferLen,buffer);
	count+=bufferLen;
	string str;
	str=buffer;

	if(curFuncName==""){
		cout<<"�֐����łȂ����߃��x����o�^�ł��܂���"<<endl;
		Error();
	}

	list<dataOfLabel>::iterator it=::dataOfLabels.begin();
	while(it!=::dataOfLabels.end())
	{

		if((*it).labelName==str){
			cout<<"���x�����d�o�^���悤�Ƃ��܂���"<<endl;
			Error();
		}
		it++;
	}
	
	dataOfLabel a;
	a.labelName=str;
	a.posInCode=binOfCode.size();

	dataOfLabels.push_back(a);

	//cout<<"���x�� "<<str<<" ��o�^���܂���"<<endl;
	//cout<<"�ʒu"<<binOfCode.size()<<endl;


	return;

}

list<dataOfJmp> dataOfJmps;
void AnalyzePatternJmp(int &count)
{
	int bufferLen;
	char *buffer;
	UsReadFile( mdlFile, count , 4,&bufferLen);
	count+=4;
	buffer=new char[bufferLen];

	UsReadFile( mdlFile, count , bufferLen,buffer);
	count+=bufferLen;
	string str;
	str=buffer;

	
	int b=binOfCode.size();
	binOfCode.push_back(0xE9);
	binOfCode.push_back(0);
	binOfCode.push_back(0);
	binOfCode.push_back(0);
	binOfCode.push_back(0);
	dataOfJmp a;
	a.labelName=str;
	a.posInCode=b+1;
	dataOfJmps.push_back(a);
	//cout<<"���x�� "<<str<<endl;
	//cout<<"�ʒu"<<a.posInCode<<endl;
	return;

}


void AnalyzePatternJmpcc(int &count)
{
	int bufferLen;
	int cc;
	char *buffer;
	UsReadFile( mdlFile, count , 4,&cc);
	count+=4;
	UsReadFile( mdlFile, count , 4,&bufferLen);
	count+=4;
	buffer=new char[bufferLen];

	UsReadFile( mdlFile, count , bufferLen,buffer);
	count+=bufferLen;
	string str;
	str=buffer;

	int b=binOfCode.size();
	binOfCode.push_back(0x0F);
	binOfCode.push_back(cc);
	binOfCode.push_back(0);
	binOfCode.push_back(0);
	binOfCode.push_back(0);
	binOfCode.push_back(0);
	dataOfJmp a;
	a.labelName=str;
	a.posInCode=b+2;
	dataOfJmps.push_back(a);
	//cout<<"���x�� "<<str<<endl;
	//cout<<"�ʒu"<<a.posInCode<<endl;
	//Error();
	return;

}
list<dataOfFunc> dataOfFuncs;
void AnalyzePatternFunc(int &count)
{
	int bufferLen;
	char *buffer;
	UsReadFile( mdlFile, count , 4,&bufferLen);
	count+=4;
	buffer=new char[bufferLen];

	UsReadFile( mdlFile, count , bufferLen,buffer);
	count+=bufferLen;
	string str;
	str=buffer;

	list<dataOfFunc>::iterator it=::dataOfFuncs.begin();
	while(it!=::dataOfFuncs.end())
	{

		if((*it).funcName==str){
			cout<<"�֐����d�o�^���悤�Ƃ��܂���"<<endl;
			Error();
		}
		it++;
	}

	curFuncName=str;
	dataOfFunc a;
	a.funcName=str;
	a.posInCode=binOfCode.size();

	dataOfFuncs.push_back(a);

	//cout<<"�֐� "<<str<<" ��o�^���܂���"<<endl;
	//cout<<"�ʒu"<<binOfCode.size()<<endl;
	return;

}
list<dataOfCall> dataOfCalls;
void AnalyzePatternCall(int &count)
{
	int bufferLen;
	char *buffer;
	UsReadFile( mdlFile, count , 4,&bufferLen);
	count+=4;
	buffer=new char[bufferLen];

	UsReadFile( mdlFile, count , bufferLen,buffer);
	count+=bufferLen;
	string str;
	str=buffer;

	int b=binOfCode.size();
	binOfCode.push_back(0xE8);
	binOfCode.push_back(0);
	binOfCode.push_back(0);
	binOfCode.push_back(0);
	binOfCode.push_back(0);
	dataOfCall a;
	a.funcName=str;
	a.posInCode=b+1;
	dataOfCalls.push_back(a);
	//cout<<"�֐� "<<str<<endl;
	//cout<<"�ʒu"<<a.posInCode<<endl;
	return;

}
list<dataOfPtrFunc> dataOfPtrFuncs;
void AnalyzePatternPtrFunc(int &count)
{
	int bufferLen;
	char *buffer;
	UsReadFile( mdlFile, count , 4,&bufferLen);
	count+=4;
	buffer=new char[bufferLen];

	UsReadFile( mdlFile, count , bufferLen,buffer);
	count+=bufferLen;
	string str;
	str=buffer;

	int b=binOfCode.size();
	binOfCode.push_back(0);
	binOfCode.push_back(0);
	binOfCode.push_back(0);
	binOfCode.push_back(0);
	dataOfPtrFunc a;
	a.funcName=str;
	a.posInCode=b;
	dataOfPtrFuncs.push_back(a);
	//cout<<"�֐� "<<str<<endl;
	//cout<<"�ʒu"<<a.posInCode<<endl;
	return;

}
list<dataOfGvarIni> dataOfGvarInis;
void AnalyzePatternGvarIni(int &count)
{
	int bufferLen;
	char *buffer;
	UsReadFile( mdlFile, count , 4,&bufferLen);
	count+=4;
	buffer=new char[bufferLen];

	UsReadFile( mdlFile, count , bufferLen,buffer);
	count+=bufferLen;
	string str;
	str=buffer;

	int gvarSize;
	int gvarIniSize;
	char *bufferData;

	UsReadFile( mdlFile, count , 4,&gvarSize);
	count+=4;

	UsReadFile( mdlFile, count , 4,&gvarIniSize);
	count+=4;
	bufferData=new char[gvarIniSize];

	UsReadFile( mdlFile, count , gvarIniSize,bufferData);
	count+=gvarIniSize;
	//string strData;
	//strData=bufferData;

	list<dataOfGvarIni>::iterator it=::dataOfGvarInis.begin();
	while(it!=::dataOfGvarInis.end())
	{

		if((*it).varName==str){
			cout<<"�L��ϐ����d�o�^���悤�Ƃ��܂���"<<endl;
			Error();
		}
		it++;
	}
	if(gvarIniSize>gvarSize){
		cout<<"�L��ϐ��ŏ������T�C�Y�����T�C�Y�𒴂��Ă���"<<endl;
		Error();
	}
	//cout<<binOfData.size()<<endl;
	//cout<<gvarSize<<endl;
	//cout<<gvarIniSize<<endl;
	int a=binOfData.size();
	for(int i=0;i<gvarIniSize;i++)
	{
		//cout<<i<<endl;
		binOfData.push_back(bufferData[i]);
	}
	//cout<<"ss"<<endl;
	for(int i=0;i<gvarSize-gvarIniSize;i++)
	{
		binOfData.push_back(0x0);
	}
	
	dataOfGvarIni b;
	b.posInData=a;
	b.varName=str;

	dataOfGvarInis.push_back(b);
	//cout<<str<<endl;

	return;

}
list<dataOfPtrGvar> dataOfPtrGvars;
void AnalyzePatternPtrGvar(int &count)
{
	int bufferLen;
	char *buffer;
	UsReadFile( mdlFile, count , 4,&bufferLen);
	count+=4;
	buffer=new char[bufferLen];

	UsReadFile( mdlFile, count , bufferLen,buffer);
	count+=bufferLen;
	string str;
	str=buffer;

	int b=binOfCode.size();
	binOfCode.push_back(0x0);
	binOfCode.push_back(0x0);
	binOfCode.push_back(0x0);
	binOfCode.push_back(0x0);

	dataOfPtrGvar a;
	a.varName=str;
	a.posInCode=b;
	dataOfPtrGvars.push_back(a);
	//cout<<str<<endl;
	return;

}
int modeExe=2;
void AnalyzePatternMode(int &count)
{
	int mode;
	//char *buffer;
	UsReadFile( mdlFile, count , 4,&mode);
	count+=4;

	modeExe=mode;
	return;

}
/*
void AnalyzePattern(int &count)
{
	int bufferLen;
	char *buffer;
	UsReadFile( mdlFile, count , 4,&bufferLen);
	count+=4;
	buffer=new char[bufferLen];

	UsReadFile( mdlFile, count , bufferLen,buffer);
	count+=bufferLen;
	string str;
	str=buffer;
	return;

}
*/
/*
	int f_match=0;
	list<****>::iterator it=::****s.begin();
	while(it!=::****s.end())
	{

		if((*it).****==str){
			f_match=1;
		}
		if(f_match==1) break;
		it++;
	}
	if(f_match==0){
	}


	int f_match=0;
	list<****>::iterator it=::****s.begin();
	while(it!=::****s.end())
	{
		it++;
	}
	*/