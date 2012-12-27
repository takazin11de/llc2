#include "Error.h"
#include <windows.h>
#include <string>
#include <list>
#include <vector>
#include <iostream>

#include "DataStructure.h"


using namespace std;

void ReformJmp(void)
{
	//cout<<dataOfLabels.size()<<endl;
	list<dataOfJmp>::iterator it=::dataOfJmps.begin();
	while(it!=::dataOfJmps.end())
	{
		int f_match=0;
		list<dataOfLabel>::iterator it2=::dataOfLabels.begin();
		while(it2!=::dataOfLabels.end())
		{
			//cout<<":"<<(*it).labelName<<":"<<(*it2).labelName<<":"<<endl;
			if((*it).labelName==(*it2).labelName){
				*((int *)&binOfText[(*it).posInCode])=
					(*it2).posInCode-((*it).posInCode+4);
				//cout<<"”­Œ©"<<endl;
				f_match=1;
			}

			it2++;
		}
		if(f_match==0){
			cout<<"ƒ‰ƒxƒ‹ "<<(*it).labelName<<" ‚ªŒ©‚Â‚©‚è‚Ü‚¹‚ñ‚Å‚µ‚½"<<endl;
			Error();
		}

		it++;
	}

}
