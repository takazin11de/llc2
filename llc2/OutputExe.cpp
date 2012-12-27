#include <iostream>
#include <iomanip>
#include <Windows.h>

#include "OutputExe.h"
#include "UsReadFile.h"
#include "DataStructure.h"
#include "alignment.h"
#include "preparefiles.h"

void OutputExe(void){
	UsWriteFile(exeFile, 0, sizeHeader,&binOfHeader[0]);

	UsWriteFile(exeFile, posTextFile, sizeTextFile,&binOfText[0]);

	UsWriteFile(exeFile, posRdataFile, sizeRdataFile,&binOfRdata[0]);

	UsWriteFile(exeFile, posDataFile, sizeDataFile,&binOfData[0]);

	UsWriteFile(exeFile, posRsrcFile, sizeRsrcFile,&binOfRsrc[0]);

	return;
}