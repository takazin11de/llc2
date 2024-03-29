#include "FormData.h"
#include "DataStructure.h"
#include "alignment.h"

#include <iostream>
#include <iomanip>

using namespace std;

int posRsrcFile;
int sizeRsrcFile;
int posRsrcMemo;
int sizeRsrc;

vector<unsigned char> binOfRsrc;

void FormRsrc(void)
{
	unsigned char a[]={
		0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x01,0x00,
		0x18,0x00,0x00,0x00, 0x18,0x00,0x00,0x80, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00, 0x00,0x00,0x01,0x00, 0x01,0x00,0x00,0x00, 0x30,0x00,0x00,0x80,
		0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x01,0x00,
		0x00,0x00,0x00,0x00, 0x48,0x00,0x00,0x00, 0xFF,0xFF,0xFF,0xFF, 0x89,0x01,0x00,0x00,
		0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x3C,0x3F,0x78,0x6D, 0x6C,0x20,0x76,0x65,
		0x72,0x73,0x69,0x6F, 0x6E,0x3D,0x22,0x31, 0x2E,0x30,0x22,0x20, 0x65,0x6E,0x63,0x6F,
		0x64,0x69,0x6E,0x67, 0x3D,0x22,0x55,0x54, 0x46,0x2D,0x38,0x22, 0x20,0x73,0x74,0x61,
		0x6E,0x64,0x61,0x6C, 0x6F,0x6E,0x65,0x3D, 0x22,0x79,0x65,0x73, 0x22,0x3F,0x3E,0x0D,
		0x0A,0x3C,0x61,0x73, 0x73,0x65,0x6D,0x62, 0x6C,0x79,0x20,0x78, 0x6D,0x6C,0x6E,0x73,
		0x3D,0x22,0x75,0x72, 0x6E,0x3A,0x73,0x63, 0x68,0x65,0x6D,0x61, 0x73,0x2D,0x6D,0x69,
		0x63,0x72,0x6F,0x73, 0x6F,0x66,0x74,0x2D, 0x63,0x6F,0x6D,0x3A, 0x61,0x73,0x6D,0x2E,
		0x76,0x31,0x22,0x20, 0x6D,0x61,0x6E,0x69, 0x66,0x65,0x73,0x74, 0x56,0x65,0x72,0x73,
		0x69,0x6F,0x6E,0x3D, 0x22,0x31,0x2E,0x30, 0x22,0x3E,0x0D,0x0A, 0x3C,0x64,0x65,0x70,
		0x65,0x6E,0x64,0x65, 0x6E,0x63,0x79,0x3E, 0x0D,0x0A,0x3C,0x64, 0x65,0x70,0x65,0x6E,
		0x64,0x65,0x6E,0x74, 0x41,0x73,0x73,0x65, 0x6D,0x62,0x6C,0x79, 0x3E,0x0D,0x0A,0x3C,
		0x61,0x73,0x73,0x65, 0x6D,0x62,0x6C,0x79, 0x49,0x64,0x65,0x6E, 0x74,0x69,0x74,0x79,
		0x0D,0x0A,0x74,0x79, 0x70,0x65,0x3D,0x22, 0x77,0x69,0x6E,0x33, 0x32,0x22,0x0D,0x0A,
		0x6E,0x61,0x6D,0x65, 0x3D,0x22,0x4D,0x69, 0x63,0x72,0x6F,0x73, 0x6F,0x66,0x74,0x2E,
		0x57,0x69,0x6E,0x64, 0x6F,0x77,0x73,0x2E, 0x43,0x6F,0x6D,0x6D, 0x6F,0x6E,0x2D,0x43,
		0x6F,0x6E,0x74,0x72, 0x6F,0x6C,0x73,0x22, 0x0D,0x0A,0x76,0x65, 0x72,0x73,0x69,0x6F,
		0x6E,0x3D,0x22,0x36, 0x2E,0x30,0x2E,0x30, 0x2E,0x30,0x22,0x0D, 0x0A,0x70,0x72,0x6F,
		0x63,0x65,0x73,0x73, 0x6F,0x72,0x41,0x72, 0x63,0x68,0x69,0x74, 0x65,0x63,0x74,0x75,
		0x72,0x65,0x3D,0x22, 0x58,0x38,0x36,0x22, 0x0D,0x0A,0x70,0x75, 0x62,0x6C,0x69,0x63,
		0x4B,0x65,0x79,0x54, 0x6F,0x6B,0x65,0x6E, 0x3D,0x22,0x36,0x35, 0x39,0x35,0x62,0x36,
		0x34,0x31,0x34,0x34, 0x63,0x63,0x66,0x31, 0x64,0x66,0x22,0x0D, 0x0A,0x6C,0x61,0x6E,
		0x67,0x75,0x61,0x67, 0x65,0x3D,0x22,0x2A, 0x22,0x0D,0x0A,0x2F, 0x3E,0x0D,0x0A,0x3C,
		0x2F,0x64,0x65,0x70, 0x65,0x6E,0x64,0x65, 0x6E,0x74,0x41,0x73, 0x73,0x65,0x6D,0x62,
		0x6C,0x79,0x3E,0x0D, 0x0A,0x3C,0x2F,0x64, 0x65,0x70,0x65,0x6E, 0x64,0x65,0x6E,0x63,
		0x79,0x3E,0x0D,0x0A, 0x3C,0x2F,0x61,0x73, 0x73,0x65,0x6D,0x62, 0x6C,0x79,0x3E,0x0D,
		0x0A
	};

	for(int i=0;i<sizeof(a);i++){
		binOfRsrc.push_back(a[i]);
	}
	//sizeRsrc=alignment(binOfRsrc.size(),0x200);
	sizeRsrc=binOfRsrc.size();
	for(int i=0;i<sizeRsrc-binOfRsrc.size();i++){
		binOfRsrc.push_back(0);
	}

	posRsrcFile=posDataFile+sizeDataFile;
	sizeRsrcFile=alignment(sizeRsrc,0x200);
	posRsrcMemo=posDataMemo+alignment(sizeData,0x1000);

	*((int *)(&binOfRsrc[0x48]))=
		0x58+posRsrcMemo;
	//sizeRsrc=binOfRsrc.size();

	//for(int i=0;i<sizeRsrcFile-sizeRsrc;i++){
	//	binOfRsrc.push_back(0);
	//}

	return;
}


