#include "Error.h"
#include <windows.h>
#include <string>
#include <list>
#include <vector>
#include <iostream>

#include "DataStructure.h"


using namespace std;

void ReformCall(void)
{
	//cout<<dataOfCalls.size()<<endl;
	list<dataOfCall>::iterator it=::dataOfCalls.begin();
	while(it!=::dataOfCalls.end())
	{
		int f_match=0;
		list<dataOfFunc>::iterator it2=::dataOfFuncs.begin();
		while(it2!=::dataOfFuncs.end())
		{
			//cout<<":"<<(*it).funcName<<":"<<(*it2).funcName<<":"<<endl;
			if((*it).funcName==(*it2).funcName){
				*((int *)&binOfText[(*it).posInCode])=
					(*it2).posInCode-((*it).posInCode+4);
				//cout<<"”­Œ©"<<endl;
				f_match=1;
			}

			it2++;
		}
		if(f_match==0){
			cout<<"ŠÖ” "<<(*it).funcName<<" ‚ªŒ©‚Â‚©‚è‚Ü‚¹‚ñ‚Å‚µ‚½"<<endl;
			Error();
		}

		it++;
	}

}

void ReformPtrFunc(void)
{
	//cout<<dataOfPtrFuncs.size()<<endl;
	list<dataOfPtrFunc>::iterator it=::dataOfPtrFuncs.begin();
	while(it!=::dataOfPtrFuncs.end())
	{
		int f_match=0;
		list<dataOfFunc>::iterator it2=::dataOfFuncs.begin();
		while(it2!=::dataOfFuncs.end())
		{
			//cout<<":"<<(*it).funcName<<":"<<(*it2).funcName<<":"<<endl;
			if((*it).funcName==(*it2).funcName){
				*((int *)&binOfText[(*it).posInCode])=
					(*it2).posInCode+::posTextMemo+IB;
				//cout<<"”­Œ©"<<endl;
				f_match=1;
			}

			it2++;
		}
		if(f_match==0){
			cout<<"ŠÖ” "<<(*it).funcName<<" ‚ªŒ©‚Â‚©‚è‚Ü‚¹‚ñ‚Å‚µ‚½"<<endl;
			Error();
		}

		it++;
	}

}