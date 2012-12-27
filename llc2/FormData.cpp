#include "FormData.h"
#include "DataStructure.h"
#include "alignment.h"

#include <iostream>
#include <iomanip>

using namespace std;

int posDataFile;
int sizeDataFile;
int posDataMemo;
int sizeData;

void FormData(void)
{
	posDataFile=posRdataFile+sizeRdataFile;
	sizeDataFile=alignment(binOfData.size(),0x200);
	posDataMemo=posRdataMemo+alignment(sizeRdata,0x1000);
	sizeData=binOfData.size();

	//cout<<sizeDataFile<<endl;

	for(int i=0;i<sizeDataFile-sizeData;i++){
		binOfData.push_back(0);
	}
	//cout<<":"<<dec<<binOfData.size()<<endl;




	return;
}
