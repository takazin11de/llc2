
void AnalyzeCode(void);
int AnalyzePattern(int &count,int data);
int UsReadFile(HANDLE hFile, int pos, int size,PVOID data);

void AnalyzePatternDLL(int &count);
void AnalyzePatternEfunc(int &count);
void AnalyzePatternCode(int &count);
void AnalyzePatternEcall(int &count);
void AnalyzePatternData(int &count);
void AnalyzePatternLabel(int &count);
void AnalyzePatternJmp(int &count);
void AnalyzePatternJmpcc(int &count);
void AnalyzePatternFunc(int &count);
void AnalyzePatternCall(int &count);
void AnalyzePatternPtrFunc(int &count);
void AnalyzePatternPtrEfunc(int &count);
void AnalyzePatternGvarIni(int &count);
void AnalyzePatternPtrGvar(int &count);
void AnalyzePatternMode(int &count);