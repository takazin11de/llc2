#include "Error.h"
#include <Windows.h>
#include <iostream>
#include <string>

#include "preparefiles.h"
using namespace std;


HANDLE mdlFile;
HANDLE exeFile;

string mdlFileName;
string mdlFileName_;
string exeFileName;
void PrepareFiles(void)
{
	mdlFileName_=mdlFileName;;
	int loc = mdlFileName_.rfind( '.', mdlFileName_.size() );

	if(loc==string::npos){

	}else{
		mdlFileName_.erase(loc,mdlFileName_.size()-loc);
		exeFileName=mdlFileName_.insert(loc,".exe");

	}

	//cout<<"���Ԍ���t�@�C���ǂݍ���..."<<ends;
	if(INVALID_HANDLE_VALUE==(mdlFile=CreateFile(
		mdlFileName.c_str(),
		GENERIC_READ, 
		0, 
		0, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		0 )))
	{
		cout<<"���Ԍ���t�@�C���ǂݍ��� �G���["<<endl;
		Error();
	}
	//cout<<"����"<<endl;
	
	//cout<<"���s�t�@�C���m��..."<<ends;


	

	if(INVALID_HANDLE_VALUE==(exeFile=CreateFile(
		exeFileName.c_str(),
		GENERIC_WRITE, 
		0, 
		0, 
		CREATE_ALWAYS, 
		FILE_ATTRIBUTE_NORMAL, 
		0 )))
	{
		cout<<"���s�t�@�C���m�� �G���["<<endl;
		Error();
	}
	//cout<<"����"<<endl;
}