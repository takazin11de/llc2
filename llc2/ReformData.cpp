#include "ReformData.h"

#include <windows.h>
#include <string>
#include <list>
#include <iostream>
#include <iomanip>

#include "DataStructure.h"
#include "alignment.h"

void ReformData(void)
{
	list<dataOfData>::iterator it=::dataOfDatas.begin();
	while(it!=::dataOfDatas.end())
	{
		*((int *)(&binOfText[(*it).posInsertCode]))=
			(*it).posInData+::posDataMemo+IB;
		it++;
	}
}