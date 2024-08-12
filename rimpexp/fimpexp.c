#ifdef UNICODE
  #define _UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <malloc.h>

//Method of marking functions for export differs between
//Win16 and Win32
#ifdef WIN32
  #define t_export _declspec(dllexport)
  #define MAX_REG_SZ 32000
#else
  #ifndef LPTSTR
  	#define LPTSTR LPSTR
  	#define LPCTSTR const LPSTR
  #endif
  #define t_export CALLBACK _export
  #define lstrcpyA lstrcpy
  #define lstrlenA lstrlen
#endif

#ifndef RES_STR
  #define RES_STR 256
#endif

#ifndef MAX_PATH
  #define MAX_PATH _MAX_PATH
#endif


char *mstrchrA(char *p, char c){
// searches a buffer for an ANSI character
  char *q;
  for (q=p ; (*q!='\0')&&(*q!=c) ; q++) {}
  return ((*q==c) ? q : NULL);
}

#ifdef WIN32
wchar_t *mstrchrW(wchar_t *p, wchar_t c){
// Searches a buffer for a wide character
  wchar_t *q;
  for ( q=p ;
      (*q!=L'\0') &&(*q!=c) ;
      q++) {}
  return ((*q==c) ? q : NULL);
}
#endif

_TCHAR INIFile[MAX_PATH];

#ifdef _UNICODE
int FileIsUnicode;

int t_export IsFileUnicode(void)
{
  return FileIsUnicode;
}
#endif

//Configuration functions
#ifdef WIN32
int t_export GetConfigInt16(LPCTSTR section, LPCTSTR key, int def){
#else
int t_export GetConfigInt(LPTSTR section, LPTSTR key, int def){
#endif
  return GetPrivateProfileInt(section, key, def, INIFile);
}

#ifdef WIN32
int t_export GetConfigStr16(LPTSTR x, int sz, LPCTSTR section, LPCTSTR key, LPCTSTR def){
#else
int t_export GetConfigStr(LPTSTR x, int sz, LPTSTR section, LPTSTR key, LPTSTR def){
#endif
  return GetPrivateProfileString(section, key, def, x, sz, (LPCTSTR) INIFile);
}

#ifdef WIN32
void t_export SetConfigStr16(LPCTSTR section, LPCTSTR key, LPCTSTR x){
#else
void t_export SetConfigStr(LPTSTR section, LPTSTR key, LPTSTR x){
#endif
  WritePrivateProfileString(section, key, x, (LPCTSTR)INIFile);
}

#ifdef WIN32
void t_export DeleteConfigTree16(LPCTSTR section){
#else
void t_export DeleteConfigTree(LPTSTR section){
#endif
  WritePrivateProfileString(section, NULL, NULL, (LPCTSTR)INIFile);
}

#ifdef WIN32
void t_export SetConfigInt16(LPCTSTR section, LPCTSTR key, int x){
#else
void t_export SetConfigInt(LPTSTR section, LPTSTR key, int x){
#endif
  _TCHAR t[10];

  _itot(x, t, 10);
#ifdef WIN32
  SetConfigStr16(section, key, (LPCTSTR)t);
#else
  SetConfigStr(section, key, t);
#endif
}

#ifdef WIN32
// use the Registry, or the WIN.INI if under WIN32S.
int UseINI;

int t_export GetConfigStr(LPTSTR x, int sz, LPTSTR section, LPTSTR key, LPTSTR def){
  LPTSTR p;
  long cb=MAX_REG_SZ;

  HKEY hk;
  int r, i;
  DWORD dwType;
  LPTSTR t;

  if (UseINI)
    return GetConfigStr16(x, sz, section, key, def);
  
  // The maximum allowable size for a registry entry (in bytes)
  t=(_TCHAR *)malloc(MAX_REG_SZ);

  if (t == NULL)
    return(-1);

  wsprintf(t, _T("Software\\TJRC\\Refs\\%s"), section);
  
  r=RegOpenKeyEx(
      HKEY_CURRENT_USER,
      t,
      0,
      KEY_QUERY_VALUE,
      &hk); 

  if (r == ERROR_SUCCESS) {

    if (key==NULL) // Client wants list of values
    {
    
    for (i=0, p=x;
         (r=RegEnumValue(
           hk,
           i,
           t,
           &cb,
           NULL,
           &dwType,
           NULL,
           NULL))!=ERROR_NO_MORE_ITEMS;
         i++)

      {
        lstrcpy(p, t);
#ifdef _UNICODE
        p+=((cb>>1)+1);
#else
        p+=(cb+1);
#endif
        cb = MAX_REG_SZ;
      }

    if (i)
        p[0]=_T('\0');
    else
      lstrcpy(x, def);

    } else {
        
      r=RegQueryValueEx(
        hk,
        key,
        NULL,
        &dwType,
        (LPBYTE)x,
        &cb);

      if (r!=ERROR_SUCCESS)
        lstrcpy(x, def);
  }

    RegCloseKey(hk);

  } else
    lstrcpy(x, def);

  free(t);
  
  return (key!=NULL) ? lstrlen(x) : i ;
}

int t_export GetConfigInt(LPTSTR section, LPTSTR key, int def){
  _TCHAR t1[RES_STR];
  int r;

  if (UseINI)
    return GetConfigInt16(section, key, def);
  
  if (GetConfigStr(t1, RES_STR, section, key, _T(""))<=0)
    return def;

  r=_ttol(t1);

  return r;
}

void t_export DeleteConfigTree(LPTSTR section){
  HKEY hk;
  DWORD tcb,cb;
  _TCHAR t[RES_STR], t1[RES_STR];
  FILETIME ft;
  DWORD n;

  if (UseINI) {
    DeleteConfigTree16(section);
  return;
  }
  
  tcb=cb=RES_STR*sizeof(_TCHAR);
  wsprintf(t1, _T("Software\\TJRC\\Refs\\%s"), section);

  if (RegOpenKeyEx(HKEY_CURRENT_USER, t1, 0, KEY_WRITE, &hk)==ERROR_SUCCESS){
  for (n=0;
       RegEnumKeyEx(
         hk,
         n,
         t,
         &cb,
         NULL,
         NULL,
         NULL,
         &ft)==ERROR_SUCCESS;
       n++)
    {
      wsprintf(t1, _T("%s\\%s"), section, t);
      cb=tcb;
      DeleteConfigTree(t1);
    }
    RegCloseKey(hk);
  if (RegOpenKeyEx(HKEY_CURRENT_USER,
                   _T("Software\\TJRC\\Refs"),
                   0,
                   KEY_WRITE,
                   &hk)==ERROR_SUCCESS){
      RegDeleteKey(hk, section);
    RegCloseKey(hk);
  }
  }
}

void t_export SetConfigStr(LPTSTR section, LPTSTR key, LPTSTR x){
  _TCHAR t1[RES_STR];
  long cb=RES_STR*sizeof(_TCHAR);
  HKEY hk;
  DWORD dwDisposition;

  if (UseINI) {
    SetConfigStr16(section, key, x);
  return;
  }
  
  wsprintf(t1, _T("Software\\TJRC\\Refs\\%s"), section);
  
  if (RegCreateKeyEx(
           HKEY_CURRENT_USER,
           t1,
           0, 
           NULL,
           REG_OPTION_NON_VOLATILE,
           KEY_ALL_ACCESS,
           NULL,
           &hk,
           &dwDisposition) == ERROR_SUCCESS)
  {

    if (x)
      RegSetValueEx(
        hk,
        key,
        0,
        REG_SZ,
        (LPBYTE)x,
        (lstrlen(x)+1)*sizeof(_TCHAR));
    else
      RegDeleteValue(hk, key);

    RegCloseKey(hk);
  }
}

void t_export SetConfigInt(LPTSTR section, LPTSTR key, int x){
  _TCHAR t1[RES_STR];
  
  if (UseINI){
    SetConfigInt16(section, key, x);
  return;
  };

  _ltot(x, t1, 10);
  SetConfigStr(section, key, t1);
}
#endif // WIN32

// use REFS.INI

LPTSTR t_export GetINIFilePath(void){
  return (INIFile);
}

void t_export SetINIFilePath(LPTSTR a){
  lstrcpy(INIFile, a);
}


long BufSz;
LPTSTR tstr;

long t_export GetBufSz(void){
  return(BufSz);
}

long t_export SetBufSz(long SetTo){
  if (!BufSz)
    BufSz=SetTo;
  return(BufSz);
}

#ifdef _UNICODE
int t_export ReadLineA(LPMMIOINFO FS, LPSTR atarget, BOOL FAR *eof){
#else
int t_export ReadLine(LPMMIOINFO FS, LPSTR atarget, BOOL FAR *eof){
#endif
  char *Ptr, t;

  atarget[0]='\0';
  
  if (FS->pchNext)
    Ptr = strstr(FS->pchNext, "\r\n");
  
  if (!Ptr)
  {
    mmioAdvance(FS->hmmio, FS, MMIO_READ);
    Ptr=strstr(FS->pchNext, "\r\n");
  }

  *eof = (FS->pchNext >= FS->pchEndRead);
  
  if (!(*eof))
  {
    if (Ptr)
    {
      t=Ptr[0];
      Ptr[0]='\0';
      lstrcpyA(atarget, FS->pchNext);
      Ptr[0]=t;
      FS->pchNext = &Ptr[2];
    }
    else
      FS->pchNext = FS->pchEndRead;
  }

  return (lstrlenA(atarget));
}


#ifdef _UNICODE
#error This needs changing to use strstr()
int t_export ReadLineW(LPMMIOINFO FS, LPWSTR atarget, BOOL FAR *eof){
  wchar_t *Ptr, t;

  atarget[0]=L'\0';
  
  if (FS->pchNext)
    Ptr = mstrchrW((LPWSTR)FS->pchNext, L'\n');
  				   
  if (!Ptr)
  {
    mmioAdvance(FS->hmmio, FS, MMIO_READ);
    Ptr = mstrchrW((LPWSTR)FS->pchNext, L'\n');
  }

  if (FileIsUnicode == -1)
  {
    FileIsUnicode++;
    // We need to determine whether the file is Unicode, and if so, what byte order
    switch (*(LPWSTR)(FS->pchNext))
    {
      case 0xFEFF: // Big endian Unicode
        FileIsUnicode++;
      case 0xFFFE: // Little endian Unicode
        FileIsUnicode++;
        // Increment the pointer so we don't treat the first two characters as text
        FS->pchNext+=sizeof(wchar_t);
        break;
    }
  }

  if (!FileIsUnicode)
  {
    // We are trying to read an ANSI file into Unicode Refs.
    MessageBox(GetDesktopWindow(), _T("This file is ANSI.  Unicode Refs cannot yet read ANSI text files.\nUse the UCONVERT utility."), NULL, MB_ICONSTOP | MB_OK);
    *eof = TRUE;
    return 0; 
  }

  *eof = (FS->pchNext >= FS->pchEndRead);
  
  if (!(*eof))
  {
    if (Ptr)
    {
      t=Ptr[1];
      Ptr[1]=L'\0';
      lstrcpyW(atarget, (LPWSTR)FS->pchNext);
      Ptr[1]=t;
      FS->pchNext = (LPSTR) &Ptr[1];
      Ptr = mstrchrW(atarget, L'\r');

      if (Ptr)
        Ptr[0] = L'\0';
      else
        FS->pchNext = FS->pchEndRead;
    
    }
    else
      FS->pchNext = FS->pchEndRead;
  };

  return (lstrlenW(atarget));
}
#endif // _UNICODE


/* writes ANSI data to the FS buffer.  Returns 0 if successful. */
#ifdef _UNICODE
int t_export WriteLineA(LPMMIOINFO FS, LPSTR astr){
#else
#define WriteLineA WriteLine
int t_export WriteLine(LPMMIOINFO FS, LPSTR astr){
#endif
  long s, l;
  unsigned int r=0;
  
  if (!astr)
    return(-1);
  s=FS->pchEndWrite-FS->pchNext;
  l=lstrlenA(astr);
  if (s<l) {
    FS->dwFlags |= MMIO_DIRTY;
    r=mmioAdvance(FS->hmmio, FS, MMIO_WRITE);
  }
  if (r)
    return(r);
  lstrcpyA(FS->pchNext, astr);
  FS->pchNext+=l;
  return(r);
}

#ifdef _UNICODE
int t_export WriteLineW(LPMMIOINFO FS, LPWSTR astr){
  long s, l;
  unsigned int r=0;
  
  if (!astr)
    return(-1);
  s=FS->pchEndWrite-FS->pchNext;
  l=lstrlenW(astr)<<1;
  if (s<l) {
    FS->dwFlags |= MMIO_DIRTY;
    r=mmioAdvance(FS->hmmio, FS, MMIO_WRITE);
  }
  if (r)
    return(r);
  lstrcpyW((LPWSTR)FS->pchNext, astr);
  FS->pchNext+=l;
  return(r);
}
#endif // _UNICODE


#ifdef _UNICODE
int t_export vMMIOprintfA(LPMMIOINFO FS, LPSTR format, va_list argvlist){
#else
int t_export vMMIOprintf(LPMMIOINFO FS, LPSTR format, va_list argvlist){
#endif
  int t;

  /* Using vsprintf because wvsprintf has a 1024 byte limit */  
  t=vsprintf((LPSTR)tstr, format, argvlist);
  if (t)
    WriteLineA(FS, (LPSTR)tstr);
  return(t);
}


#ifdef _UNICODE
int t_export vMMIOprintfW(LPMMIOINFO FS, LPWSTR format, va_list argvlist){
  int t;

  /* Using vsprintf because wvsprintf has a 1024 byte limit */  
  t=vswprintf((LPWSTR)tstr, format, argvlist);
  if (t)
    WriteLineW(FS, (LPWSTR)tstr);
  return(t);
}
#endif //_UNICODE


#ifdef WIN32
BOOL WINAPI DllMain(

    HINSTANCE  hinstDLL,  // handle of DLL module 
    DWORD  fdwReason, // reason for calling function 
    LPVOID  lpvReserved   // reserved 
   ){

  DWORD dwVersion;

  switch (fdwReason){
    case DLL_PROCESS_ATTACH: {
      BufSz=0;
      tstr=(LPTSTR)malloc(32768);

#ifdef _UNICODE
      FileIsUnicode = -1;
#endif

      dwVersion = GetVersion();

     UseINI = FALSE;
     if (dwVersion < 0x80000000) {
       // Windows NT
       UseINI = FALSE;
     }
     else if (LOBYTE(LOWORD(dwVersion))<4) {
       // Win32s
       UseINI = TRUE;
     }
      return (tstr ? TRUE : FALSE);
    }
    case DLL_PROCESS_DETACH: {
      free(tstr);
      break;
    }
  }
  return TRUE;
}

#else  // WIN32
int t_export WEP(int nParameter){
/*  if (tstr)
    free(tstr);*/
  return(1);
}

int t_export LibMain(HINSTANCE hInstance, WORD wDataSeg, WORD cbHeapSize, LPSTR lpCmdLine){
  BufSz=0;
  tstr=(LPTSTR)malloc(32768);

  return (tstr ? 1 : 0);
}
#endif // WIN32
