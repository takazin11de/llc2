#include "GlobalVar.h"

#include "Error.h"
#include <windows.h>
#include <string>
#include <list>
#include <vector>
#include <iostream>

#include "DataStructure.h"


using namespace std;

void ReformGvar(void){
	//cout<<dataOfPtrFuncs.size()<<endl;
	list<dataOfPtrGvar>::iterator it=::dataOfPtrGvars.begin();
	while(it!=::dataOfPtrGvars.end())
	{
		int f_match=0;
		list<dataOfGvarIni>::iterator it2=::dataOfGvarInis.begin();
		while(it2!=::dataOfGvarInis.end())
		{
			//cout<<":"<<(*it).funcName<<":"<<(*it2).funcName<<":"<<endl;
			if((*it).varName==(*it2).varName){
				*((int *)&binOfText[(*it).posInCode])=
					(*it2).posInData+::posDataMemo+IB;
				//cout<<"”­Œ©"<<endl;
				f_match=1;
			}

			it2++;
		}
		if(f_match==0){
			cout<<"Lˆæ•Ï” "<<(*it).varName<<" ‚ªŒ©‚Â‚©‚è‚Ü‚¹‚ñ‚Å‚µ‚½"<<endl;
			Error();
		}

		it++;
	}
}