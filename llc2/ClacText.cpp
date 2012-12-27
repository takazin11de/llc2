#include "CalcText.h"
#include "DataStructure.h"
#include "alignment.h"

#include <iostream>
#include <iomanip>

using namespace std;

int posTextFile;
int sizeTextFile;
int posTextMemo;
int sizeText;

int sizeCode;
int sizeCodeEcall;

vector<unsigned char> binOfText;

void CalcText(void)
{
	//cout<<"cs"<<hex<<binOfCode.size()<<endl;
	::sizeCode=binOfCode.size();
	::sizeCodeEcall=binOfCodeEcall.size();

	::sizeText=::sizeCode+::sizeCodeEcall;

	::posTextFile=::sizeHeader;
	::posTextMemo=0x1000;//alignment(::sizeText,0x1000);
	::sizeTextFile=alignment(::sizeText, 0x200);


	

	binOfText=binOfCode;
	binOfText.insert(binOfText.end(),binOfCodeEcall.begin(),binOfCodeEcall.end());


	for(int i=0;i<sizeTextFile-sizeText;i++){
		binOfText.push_back(0);
	}

	return;
}