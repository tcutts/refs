#include "imptfr.h"

#define FSBUFFSZ 32768L
    
#ifdef WIN32

//Win32 does not use INI files.  Use functions in RIMPEXP instead.
typedef void (CALLBACK *OPTPROC)(HWND);
typedef TImportRef *(CALLBACK *IMPPROC)(HWND, LPMMIOINFO);
typedef int (CALLBACK *EXPPROC)(HWND, LPImportRef, LPMMIOINFO);

//Win32 also seems to be case sensitive on DLL imports.
#define OPTS "Opts"
#define LOADREF "LoadRef"
#define SAVEREF "SaveRef"
#define GETSPECS "GetSpecs"
#define WHOAMI "WhoAmI"

#else

typedef void (CALLBACK *OPTPROC)(HWND, LPTSTR);
typedef TImportRef *(CALLBACK *IMPPROC)(HWND, LPMMIOINFO, LPTSTR);
typedef int (CALLBACK *EXPPROC)(HWND, LPImportRef, LPMMIOINFO, LPTSTR);

#define OPTS "OPTS"
#define LOADREF "LOADREF"
#define SAVEREF "SAVEREF"
#define GETSPECS "GETSPECS"
#define WHOAMI "WHOAMI"

#endif
    
typedef _TCHAR *(CALLBACK *NPROC)(void);

// currently selected library stored here
extern _TCHAR libname[14], thenum[4], *flts[32];
extern HINSTANCE LibHnd;
extern int n;
extern int OEMode;
extern int Finished;
extern OPTPROC optproc;
extern IMPPROC ImpProc;
extern EXPPROC ExpProc;

//REFIMP.CPP
extern void DeleteOldFile(_TCHAR *);
extern int ImpRefs(LPRefWndData, int, int);
extern int ChooseFileFormat(int);
extern "C" BOOL CALLBACK _export ImpDlgProc(HWND, UINT, WPARAM, LPARAM);
