#include "Error.h"

#include <windows.h>
#include <string>
#include <list>
#include <vector>
#include <iostream>


using namespace std;

void Error(void){
	cout<<"処理を中断し終了します。"<<endl;
	ExitProcess(0);
	return;
}