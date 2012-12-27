
#include <string>
#include <list>
#include <vector>

using namespace std;

enum
{
	eof=0,		//00
	DLL,		//01
	efunc,		//02
	ecall,		//03
	ptrefunc,	//04
	label,		//05
	jmp,		//06
	jmpcc,		//07
	func,		//08
	ptrfunc,	//09
	call,		//0A
	code,		//0B
	data,		//0C
	gvarini,	//0D
	ptrgvar,	//0E
	mode
};


class dataOfEfunc{
public:
	string efuncName;//��

	int numEfunc;//��������DLL���ŉ��Ԗڂ̊֐���//��
	int posInFLAT;//��
	int posInSLAT;//��
	int posDataEfunc;//������DataEfunc�ŉ������ڂ�\0���܂�//��
	int posInIAT;//��
	int posInCodeEcall;//��

	dataOfEfunc();
};

extern int modeExe;

extern int sizeIAT;
extern int posIAT;
extern int sizeIT;
extern int posIT;
extern int sizeLAT;
extern int posLAT;

extern int posDataDll;
extern int posDataEfunc;

extern int sumOfDll;
extern int sumDataDll;

extern int sumDataEfunc;
extern int sumOfEfunc;


extern int posTextFile;
extern int sizeTextFile;
extern int posTextMemo;
extern int sizeText;

extern int posRdataFile;
extern int sizeRdataFile;
extern int posRdataMemo;
extern int sizeRdata;

extern int posDataFile;
extern int sizeDataFile;
extern int posDataMemo;
extern int sizeData;

extern int posRsrcFile;
extern int sizeRsrcFile;
extern int posRsrcMemo;
extern int sizeRsrc;

extern int sizeCode;
extern int sizeCodeEcall;
extern int sizeHeader;



class dataOfDll{
public:
	string dllName;//��

	int numOfDll;//���Ԗڂ�DLL��//��
	int posInDataDll;//DataDLL�ŉ������ڂ�//��
	int numOfEfuncs;//��
	int sizeSLAT;//��
	int sizeFLAT;//��
	int posSLAT;//��
	int posFLAT;//��


	list<dataOfEfunc> dataOfEfuncs;

	dataOfDll();
};

class dataOfEcall{
public:

	string str;

	int posInsertCode;//�ǂ��ɑ}�����邩
	int posBeginInCode;//���Έʒu�v�Z�p
	int posEndInCodeEcall;//���Έʒu�v�Z�p


	dataOfEcall();
};
class dataOfPtrEfunc{
public:

	string efuncName; 
	int posInCode;

	dataOfPtrEfunc();
};


class dataOfData{
public:
	int posInsertCode;//�ǂ��ɑ}�����邩
	int posInData;

	dataOfData();
};

class dataOfLabel{
public:
	string labelName; 
	int posInCode;

	dataOfLabel();
};
class dataOfJmp{//jmpcc�Ƌ��p
public:
	string labelName; 
	int posInCode;

	dataOfJmp();
};
class dataOfFunc{
public:
	string funcName; 
	int posInCode;

	dataOfFunc();
};
class dataOfCall{
public:
	string funcName; 
	int posInCode;

	dataOfCall();
};

class dataOfPtrFunc{
public:
	string funcName; 
	int posInCode;

	dataOfPtrFunc();
};

class dataOfGvarIni{
public:
	string varName; 
	int posInData;

	dataOfGvarIni();
};

class dataOfPtrGvar{
public:
	string varName; 
	int posInCode;

	dataOfPtrGvar();
};

extern vector<unsigned char> binOfHeader;
extern vector<unsigned char> binOfText;
extern vector<unsigned char> binOfCode;
extern vector<unsigned char> binOfCodeEcall;
extern vector<unsigned char> binOfData;
extern vector<unsigned char> binOfRdata;
extern vector<unsigned char> binOfRsrc;

extern list<dataOfData> dataOfDatas;
extern list<dataOfEcall> dataOfEcalls;
extern list<dataOfPtrEfunc> dataOfPtrEfuncs;
extern list<dataOfDll> dataOfDlls;
extern list<dataOfLabel> dataOfLabels;
extern list<dataOfJmp> dataOfJmps;
extern list<dataOfFunc> dataOfFuncs;
extern list<dataOfCall> dataOfCalls;
extern list<dataOfPtrFunc> dataOfPtrFuncs;
extern list<dataOfGvarIni> dataOfGvarInis;
extern list<dataOfPtrGvar> dataOfPtrGvars;

#define IB (0x00400000)