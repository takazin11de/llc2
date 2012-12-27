#include "DataStructure.h"

dataOfEfunc::dataOfEfunc()
{
	efuncName="";

	numEfunc=0;
	posInFLAT=0;
	posInSLAT=0;
	posDataEfunc=0;
	posInIAT=0;
	posInCodeEcall=0;
}

dataOfDll::dataOfDll()
{	
	dllName="";

	numOfDll=0;
	posInDataDll=0;
	numOfEfuncs=0;
	sizeSLAT=0;
	sizeFLAT=0;
	posSLAT=0;
	posFLAT=0;
}

dataOfEcall::dataOfEcall(){
	posInsertCode=0;//‚Ç‚±‚É‘}“ü‚·‚é‚©
	posBeginInCode=0;//‘Š‘ÎˆÊ’uŒvŽZ—p
	posEndInCodeEcall=0;//‘Š‘ÎˆÊ’uŒvŽZ—p
	str="";
}
dataOfPtrEfunc::dataOfPtrEfunc(){
	efuncName=""; 
	posInCode=0;
}

dataOfData::dataOfData(){
	posInsertCode=0;//‚Ç‚±‚É‘}“ü‚·‚é‚©
	posInData=0;
}
dataOfLabel::dataOfLabel(){
	labelName=""; 
	posInCode=0;
}


dataOfJmp::dataOfJmp(){
	labelName=""; 
	posInCode=0;
}
dataOfFunc::dataOfFunc(){
	funcName=""; 
	posInCode=0;
}
dataOfCall::dataOfCall(){
	funcName=""; 
	posInCode=0;
}
dataOfPtrFunc::dataOfPtrFunc(){
	funcName=""; 
	posInCode=0;
}
dataOfGvarIni::dataOfGvarIni(){
	varName=""; 
	posInData=0;
}
dataOfPtrGvar::dataOfPtrGvar(){
	varName=""; 
	posInCode=0;
}