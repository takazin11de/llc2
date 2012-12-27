
#include <Windows.h>

int UsReadFile(HANDLE hFile, int pos, int size,PVOID data){
	DWORD lpNumberOfByte;
	SetFilePointer(hFile,pos,0,FILE_BEGIN);
	int tmp=ReadFile(hFile,data,size,&lpNumberOfByte,0);
	return tmp;
}

int UsWriteFile(HANDLE hFile, int pos, int size,PVOID data){
	DWORD lpNumberOfByte;
	SetFilePointer(hFile,pos,0,FILE_BEGIN);
	int tmp=WriteFile(hFile,data,size,&lpNumberOfByte,0);
	return tmp;
}