#include "CalcRdata.h"

#include <windows.h>
#include <string>
#include <list>
#include <iostream>
#include <iomanip>

#include "Error.h"
#include "DataStructure.h"
#include "alignment.h"

using namespace std;

int posRdataFile=0;
int sizeRdataFile=0;
int posRdataMemo=0;
//int sizeRdata=0;

int sizeRdata=0;
vector<unsigned char> binOfRdata;

void CalcRdata(void){
	

	int sumSLAT=0;
	int sumFLAT=0;

	list<dataOfDll>::iterator it;
	it = ::dataOfDlls.begin();
	while(it!=::dataOfDlls.end())
	{

		(*it).sizeFLAT+=4;//null‚ð‘«‚·
		(*it).sizeSLAT+=4;

		it++;
	}

	it = ::dataOfDlls.begin();
	while(it!=::dataOfDlls.end())
	{
		
		(*it).posFLAT=sumFLAT;
		sumFLAT+=(*it).sizeFLAT;

		(*it).posSLAT=sumSLAT;
		sumSLAT+=(*it).sizeSLAT;

		it++;
	}
	::sizeIAT=sumSLAT;
	::sizeLAT=sumFLAT;

	::sizeIT=::sumOfDll*4*5 + 4*5;
	
	::posIAT=0;
	::posIT=sizeIAT;
	::posLAT=posIT+sizeIT;
	::posDataDll=posLAT+sizeLAT;
	::posDataEfunc=sumDataDll+posDataDll;

	::sizeRdata=posDataEfunc+sumDataEfunc;

	::posRdataFile=::posTextFile+alignment(sizeText,0x200);
	::posRdataMemo=::posTextMemo+alignment(sizeText,0x1000);
	::sizeRdataFile=alignment(sizeRdata,0x200);

	::binOfRdata.resize(sizeRdataFile,0);

	//binOfRdata[0]=0xff;

	/*
	cout<<":"<<sizeIAT<<endl;
	cout<<":"<<posIAT<<endl;
	cout<<":"<<sizeIT<<endl;
	cout<<":"<<posIT<<endl;
	cout<<":"<<sizeLAT<<endl;
	cout<<":"<<posLAT<<endl;

	cout<<sumDataDll<<endl;
	cout<<posDataDll<<endl;

	cout<<sumDataEfunc<<endl;
	cout<<posDataEfunc<<endl;
	*/

	ClacRdataCodeEfunc();
	//FormRdata();

}

void ClacRdataCodeEfunc(void)
{
	int _posFLAT=0;
	list<dataOfDll>::iterator it=::dataOfDlls.begin();
	while(it!=::dataOfDlls.end())
	{
		(*it).posFLAT=_posFLAT;
		(*it).posSLAT=_posFLAT;
		_posFLAT+=(*it).sizeFLAT;
		list<dataOfEfunc>::iterator
			it2=(*it).dataOfEfuncs.begin();
		while(it2!=(*it).dataOfEfuncs.end())
		{
			(*it2).posInIAT=(*it).posFLAT+(*it2).posInFLAT;

			*((int *)&binOfCodeEcall[(*it2).posInCodeEcall])=
				(*it2).posInCodeEcall+::sizeCode+::posTextMemo+IB;

			it2++;
		}
		it++;
	}
}

void FormRdata(void)
{
	list<dataOfDll>::iterator it=::dataOfDlls.begin();
	while(it!=::dataOfDlls.end())
	{

		*((int *)&::binOfRdata[posIT+(*it).numOfDll*4*5])//FLAT‚ÌƒAƒhƒŒƒX
			=posLAT+(*it).posFLAT+posRdataMemo;
		*((int *)&::binOfRdata[posIT+(*it).numOfDll*4*5+4])
			=0;
		*((int *)&::binOfRdata[posIT+(*it).numOfDll*4*5+8])
			=0;
		*((int *)&::binOfRdata[posIT+(*it).numOfDll*4*5+12])
			=posDataDll+(*it).posInDataDll+posRdataMemo;
		*((int *)&::binOfRdata[posIT+(*it).numOfDll*4*5+16])//Slat
			=posIAT+(*it).posSLAT+posRdataMemo;

		//cout<<(*it).dllName<<endl;
		//cout<<(*it).dllName.size()<<endl;
		for(int i=0;i<(*it).dllName.size()+1;i++){
			::binOfRdata[posDataDll+(*it).posInDataDll+i]=
				*(unsigned char *)((*it).dllName.c_str()+i);

		}
			
		list<dataOfEfunc>::iterator
			it2=(*it).dataOfEfuncs.begin();
		while(it2!=(*it).dataOfEfuncs.end())
		{
			//cout<<":::"<<(int)(*it2).posInCodeEcall<<endl;
			*((int *)&::binOfRdata[posIAT+(*it).posSLAT+(*it2).posInSLAT])=
				posDataEfunc+(*it2).posDataEfunc+posRdataMemo;

			*((int *)&::binOfRdata[posLAT+(*it).posFLAT+(*it2).posInFLAT])=
				posDataEfunc+(*it2).posDataEfunc+posRdataMemo;

			for(int i=0;i<(*it2).efuncName.size()+1;i++){
				::binOfRdata[posDataEfunc+(*it2).posDataEfunc+i+2]=
					*(unsigned char *)((*it2).efuncName.c_str()+i);

			}

			*((int *)(&binOfText[::sizeCode+(*it2).posInCodeEcall]))=
				(*it2).posInIAT+::posRdataMemo+IB;

			it2++;
		}
		it++;
	}

	

}