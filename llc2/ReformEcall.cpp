#include "ReformEcall.h"

#include <windows.h>
#include <string>
#include <list>
#include <iostream>
#include <iomanip>

#include "DataStructure.h"
#include "alignment.h"
#include "Error.h"

void ReformEcall(void)
{
	//cout<<"aaaiii"<<endl;
	list<dataOfEcall>::iterator it=::dataOfEcalls.begin();
	while(it!=::dataOfEcalls.end())
	{
		//cout<<"aaaiii "<<(*it).posBeginInCode<<endl;
		//cout<<"aaaiii "<<::sizeCode<<endl;
		//cout<<"aaaiii "<<(*it).posBeginInCode<<endl;
		*((int *)(&binOfText[(*it).posInsertCode]))=
			((*it).posEndInCodeEcall+::sizeCode)-(*it).posBeginInCode;
		it++;
	}

	return;
}


void ReformPtrEfunc(void)
{
	//cout<<dataOfPtrEfuncs.size()<<endl;
	list<dataOfPtrEfunc>::iterator it=::dataOfPtrEfuncs.begin();
	while(it!=::dataOfPtrEfuncs.end())
	{

		int f_match=0;
		list<dataOfDll>::iterator it2=::dataOfDlls.begin();
		while(it2!=::dataOfDlls.end())
		{
			list<dataOfEfunc>::iterator it3=(*it2).dataOfEfuncs.begin();
			while(it3!=(*it2).dataOfEfuncs.end())
			{
				if((*it3).efuncName==(*it).efuncName){
					f_match=1;
					*((int *)&binOfText[(*it).posInCode])=
						(*it3).posInCodeEcall-2+::sizeCode+::posTextMemo+IB;
				}
				it3++;
			}
			it2++;
		}


		if(f_match==0){
			cout<<"ŠO•”ŠÖ” "<<(*it).efuncName<<" ‚ªŒ©‚Â‚©‚è‚Ü‚¹‚ñ‚Å‚µ‚½"<<endl;
			Error();
		}

		it++;
	}

}