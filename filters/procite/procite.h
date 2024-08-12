#define NUMFIELDS 47
#define NUMTYPES 6

#ifdef WIN32
#define t_export _declspec(dllexport)
#define SSCANF sscanf
#else
#include "..\src\sscanf\wsscanf.h"
#define t_export CALLBACK _export
#define SSCANF wsscanf
#endif

void ProcessNames(int Field);
void ProcessKeywords(int Field);
void SplitRecord(void);
int CheckVer(void);
