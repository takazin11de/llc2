#include "FormData.h"
#include "DataStructure.h"
#include "alignment.h"

#include <iostream>
#include <iomanip>

using namespace std;
int sizeHeader;
vector<unsigned char> binOfHeader;

void FormHeader(void)
{
	unsigned char a[]={
		0x4D,0x5A,0x90,0x00, 0x03,0x00,0x00,0x00, 0x04,0x00,0x00,0x00, 0xFF,0xFF,0x00,0x00,
		0xB8,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x40,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x80,0x00,0x00,0x00,
		0x0E,0x1F,0xBA,0x0E, 0x00,0xB4,0x09,0xCD, 0x21,0xB8,0x01,0x4C, 0xCD,0x21,0x54,0x68,
		0x69,0x73,0x20,0x70, 0x72,0x6F,0x67,0x72, 0x61,0x6D,0x20,0x63, 0x61,0x6E,0x6E,0x6F,
		0x74,0x20,0x62,0x65, 0x20,0x72,0x75,0x6E, 0x20,0x69,0x6E,0x20, 0x44,0x4F,0x53,0x20,
		0x6D,0x6F,0x64,0x65, 0x2E,0x0D,0x0D,0x0A, 0x24,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,
		0x50,0x45,0x00,0x00, 0x4C,0x01,0xFF,0xFF, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00, 0xE0,0x00,0x0E,0x01, 0x0B,0x01,0x00,0x00, 0xFF,0xFF,0xFF,0xFF,
		0xFF,0xFF,0xFF,0xFF, 0x00,0x00,0x00,0x00, 0x00,0x10,0x00,0x00, 0x00,0x10,0x00,0x00,
		0xFF,0xFF,0xFF,0xFF, 0x00,0x00,0x40,0x00, 0x00,0x10,0x00,0x00, 0x00,0x02,0x00,0x00,
		0x04,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x04,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,
		0xFF,0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF,0xFF, 0x00,0x00,0x00,0x00, 0xFF,0xFF,0x00,0x00,
		0x00,0x00,0x10,0x00, 0x00,0x10,0x00,0x00, 0x00,0x00,0x10,0x00, 0x00,0x10,0x00,0x00,
		0x00,0x00,0x00,0x00, 0x10,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,
		0xFF,0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF,0xFF,
		0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0xFF,0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF,0xFF,
		0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x2E,0x74,0x65,0x78, 0x74,0x00,0x00,0x00,
		0xFF,0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF,0xFF,
		0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x20,0x00,0x00,0x60,
		0x2E,0x72,0x64,0x61, 0x74,0x61,0x00,0x00, 0xFF,0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF,0xFF,
		0xFF,0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF,0xFF, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00, 0x40,0x00,0x00,0x40, 0x2E,0x64,0x61,0x74, 0x61,0x00,0x00,0x00,
		0xFF,0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF,0xFF,
		0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x40,0x00,0x00,0xC0,
		0x2E,0x72,0x73,0x72, 0x63,0x00,0x00,0x00, 0xFF,0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF,0xFF,
		0xFF,0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF,0xFF, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00, 0x40,0x00,0x00,0x40, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00
	};
	//cout<<"�w�b�_"<<hex<<sizeof(a)<<endl;
	//cout<<":"<<endl;
	for(int i=0;i<sizeof(a);i++){
		binOfHeader.push_back(a[i]);
	}
	//cout<<"::"<<endl;
	sizeHeader=alignment(binOfHeader.size(),0x200);
	//cout<<hex<<binOfHeader.size()<<endl;
	//cout<<hex<<0x200<<endl;
	//cout<<hex<<sizeHeader<<endl;
	for(int i=0;i<sizeHeader-binOfHeader.size();i++){
		binOfHeader.push_back(0);
	}
	//cout<<"::::"<<endl;

	return;
}

void FormHeader2(void)
{
	*((short *)(&binOfHeader[0x86]))=
		0x0004;//�Z�N�V������

	*((int *)(&binOfHeader[0x9C]))=
		::sizeTextFile;

	*((int *)(&binOfHeader[0xA0]))=
		::sizeRdataFile+::sizeDataFile+::sizeRsrcFile;

	*((int *)(&binOfHeader[0xB0]))=
		::posRdataFile;

	*((int *)(&binOfHeader[0xD0]))=
		//::posDataMemo+alignment(sizeData,0x1000);
		::posRsrcMemo+alignment(sizeRsrc,0x1000);

	*((int *)(&binOfHeader[0xD4]))=
		::sizeHeader;

	*((short *)(&binOfHeader[0xDC]))=
		modeExe;//gui 2   cui 3;

	//�f�[�^�f�B�N�V���i��
	*((int *)(&binOfHeader[0x100]))=
		::posRdataMemo+::posIT;

	*((int *)(&binOfHeader[0x104]))=
		::sizeIT;

	*((int *)(&binOfHeader[0x108]))=
		::posRsrcMemo;

	*((int *)(&binOfHeader[0x108+4]))=
		::sizeRsrc;

	*((int *)(&binOfHeader[0x158]))=
		::posRdataMemo+::posIAT;

	*((int *)(&binOfHeader[0x15C]))=
		::sizeIAT;

	int a=0x180;
	
	*((int *)(&binOfHeader[a+0x0]))=
		::sizeText;

	*((int *)(&binOfHeader[a+0x4]))=
		::posTextMemo;

	*((int *)(&binOfHeader[a+0x8]))=
		::sizeTextFile;

	*((int *)(&binOfHeader[a+0xC]))=
		::posTextFile;

	
	a=0x1A8;
	
	*((int *)(&binOfHeader[a+0x0]))=
		::sizeRdata;

	*((int *)(&binOfHeader[a+0x4]))=
		::posRdataMemo;

	*((int *)(&binOfHeader[a+0x8]))=
		::sizeRdataFile;

	*((int *)(&binOfHeader[a+0xC]))=
		::posRdataFile;


	a=0x1D0;
	
	*((int *)(&binOfHeader[a+0x0]))=
		::sizeData;

	*((int *)(&binOfHeader[a+0x4]))=
		::posDataMemo;

	*((int *)(&binOfHeader[a+0x8]))=
		::sizeDataFile;

	*((int *)(&binOfHeader[a+0xC]))=
		::posDataFile;

	a=0x1F8;

	*((int *)(&binOfHeader[a+0x0]))=
		::sizeRsrc;

	*((int *)(&binOfHeader[a+0x4]))=
		::posRsrcMemo;

	*((int *)(&binOfHeader[a+0x8]))=
		::sizeRsrcFile;

	*((int *)(&binOfHeader[a+0xC]))=
		::posRsrcFile;

	

	return;
}