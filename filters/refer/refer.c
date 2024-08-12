/*
{*******************************************************}
{*                                                     *}
{*      REFER.C   - refer module                       *}
{*                  for Refs 7.8                       *}
{*                                                     *}
{*      This file is (C) Tim Cutts 1993-1996 and may   *}
{*      not be redistributed in its present form, but  *}
{*      may be used, modified, in other programs.      *}
{*                                                     *}
{*******************************************************}
*/

#ifdef UNICODE
#define _UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <mmsystem.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <malloc.h>
#include <windowsx.h>

// Method of marking functions for export differs between Win16 and Win32

#ifdef WIN32
#define t_export _declspec(dllexport)
#else
#define t_export CALLBACK _export
#endif

#include "../../inc/imptfr.h"
#include "../../rimpexp/rimpexp.h"

#define DOFIELD(x)          \
  if (!x)                   \
  {                         \
    x = _tcsdup(&tstr1[3]); \
  }

HINSTANCE hInst;

LPTSTR tstr1;
LPTSTR tstr2;

BOOL EoF;
static TImportRef Tmp;
long FSBufSz;
int Opt;

_TCHAR *FirstNonWhite(_TCHAR *APtr)
{
  _TCHAR *BPtr;

  BPtr = APtr;
  while (_tcschr(_T(" \n\r\t"), BPtr[0]))
    BPtr++;
  return (BPtr);
}

void AddStuff(LPImportRef T, LPTSTR Work, LPTSTR Src, LPTSTR *Dest)
{
  LPTSTR wibble;

  if (*Dest)
  {
    lstrcpy(Work, *Dest);
    free(*Dest);
    if ((Dest == &T->Authors) || (Dest == &T->Keywords))
      lstrcat(Work, _T("\r\n"));
    else
      lstrcat(Work, _T("\x01"));
  }
  else
    Work[0] = _T('\0');
  wibble = FirstNonWhite(&Src[2]);
  lstrcat(Work, wibble);
  *Dest = _tcsdup(Work);
}

void DoAbstract(LPTSTR Src, LPImportRef T)
{
  *tstr2 = _T('\0');
  if (T->Text)
  {
    lstrcpy(tstr2, T->Text);
    free(T->Text);
    lstrcat(tstr2, _T("\r\n\r\n"));
  }
  lstrcat(tstr2, Src);
  T->Text = _tcsdup(tstr2);
}

int MMIOprintf(LPMMIOINFO FS, _TCHAR *fmt, ...)
{
  va_list ap;
  int c;

  va_start(ap, fmt);
  c = vMMIOprintf(FS, fmt, ap);
  va_end(ap);
  return (c);
}

void SaveField(LPMMIOINFO FS, LPTSTR x, LPTSTR y)
{
  if (x)
  {
    if (Opt)
    {
#ifdef _UNICODE
#else
      AnsiToOem(x, tstr1);
#endif
      MMIOprintf(FS, y, tstr1);
    }
    else
      MMIOprintf(FS, y, x);
  }
}

void SaveLst(LPMMIOINFO F, _TCHAR *APtr, _TCHAR *ATag)
{
  _TCHAR *Ptr, *Ptr2, *p;

  if (APtr)
  {
    p = Opt ? tstr1 : APtr;
    if (Opt)
#ifdef _UNICODE
    {
    };
#else
      AnsiToOem(APtr, tstr1);
#endif

    Ptr = p;
    do
    {
      if ((Ptr2 = _tcschr(Ptr, _T('\r'))) != NULL)
        *Ptr2 = _T('\0');
      while ((*Ptr == _T('\r')) || (*Ptr == _T('\n')) || (*Ptr == _T(' ')))
        Ptr++;
      if (*Ptr != _T('\0'))
        MMIOprintf(F, ATag, Ptr);
      Ptr = Ptr2;
      if (Ptr2)
        *Ptr2 = _T('\r');
      Ptr++;
    } while (Ptr2);
  }
}

#ifdef WIN32
int t_export SaveRef(HWND aparent, LPImportRef Ref, LPMMIOINFO FS)
{
#else
int t_export SaveRef(HWND aparent, LPImportRef Ref, LPMMIOINFO FS, _TCHAR *INIPath)
{
#endif

  LPTSTR Ptr, Ptr2, p;

  SaveLst(FS, Ref->Authors, _T("%%A %s\r\n"));
  SaveField(FS, Ref->Date, _T("%%D %s\r\n"));
  SaveField(FS, Ref->Title, _T("%%T %s\r\n"));
  switch (Ref->RefType)
  {
  case 0:
    SaveField(FS, Ref->Journal, _T("%%J %s\r\n"));
    break;
  case 1:
    SaveField(FS, Ref->Journal, _T("%%B %s\r\n"));
    break;
  case 2:
    SaveField(FS, Ref->Journal, _T("%%R %s\r\n"));
  }
  SaveField(FS, Ref->Publisher, _T("%%I %s\r\n"));
  SaveField(FS, Ref->City, _T("%%C %s\r\n"));
  SaveLst(FS, Ref->Editor, _T("%%E %s\r\n"));
  SaveField(FS, Ref->Vol, _T("%%V %s\r\n"));
  SaveField(FS, Ref->VolNo, _T("%%N %s\r\n"));
  SaveField(FS, Ref->Pages, _T("%%P %s\r\n"));
  if (Ref->Keywords)
  {
    p = Opt ? tstr2 : Ref->Keywords;
    if (Opt)
#ifdef _UNICODE
    {
    };
#else
      AnsiToOem(Ref->Keywords, tstr2);
#endif
    lstrcpy(tstr1, p);
    Ptr = _tcsstr(tstr1, _T("\r\n"));
    while (Ptr)
    {
      *Ptr = _T(',');
      Ptr[1] = _T(' ');
      Ptr = _tcsstr(&Ptr[2], _T("\r\n"));
    }
    MMIOprintf(FS, _T("%%K %s\r\n"), tstr1);
  }
  if (Ref->Text)
  {
    if (Opt)
#ifdef _UNICODE
    {
    }
#else
      AnsiToOem(Ref->Text, tstr2);
#endif
    else
      lstrcpy(tstr2, Ref->Text);
    Ptr = tstr2;
    do
    {
      // Strip any CRLF's
      Ptr = _tcsstr(tstr2, _T("\r\n\r\n"));
      if (Ptr)
      {
        *Ptr = _T('\0');
        lstrcpy(tstr1, tstr2);
        lstrcat(tstr1, &Ptr[2]);
        lstrcpy(tstr2, tstr1);
      }
    } while (Ptr);
    lstrcpy(tstr1, tstr2);
    Ptr = tstr1;
    while (Ptr && (*Ptr == _T('%')))
    {
      Ptr2 = _tcschr(Ptr, _T('\r'));
      if (Ptr2)
      {
        *Ptr2 = _T('\0');
        MMIOprintf(FS, _T("%s\r\n"), Ptr);
        Ptr = &Ptr2[2];
      }
      else
      {
        MMIOprintf(FS, _T("%s\r\n"), Ptr);
        Ptr = NULL;
      }
    }
    if (Ptr && (*Ptr != _T('\0')))
      MMIOprintf(FS, _T("%%X %s\r\n"), Ptr);
  }
  WriteLine(FS, _T("\r\n")); // Blank line separates references
  return (FALSE);
}

#ifdef WIN32
TImportRef t_export *LoadRef(HWND aparent, MMIOINFO *FS)
{
#else
TImportRef FAR *PASCAL _export LoadRef(HWND aparent,
                                       LPMMIOINFO FS,
                                       _TCHAR *INIPath)
{
#endif
  _TCHAR *Ptr2, **foo;

  for (foo = &Tmp.Authors; foo <= &Tmp.Editor; foo++)
  {
    if (*foo)
    {
      free(*foo);
      *foo = NULL;
    }
  }

  do
    ReadLine(FS, tstr1, &EoF);
  while ((!EoF) && (tstr1[0] == _T('\0')));

  if (EoF)
  {
    Tmp.Result = 2;
    return (&Tmp);
  }

  do
  {
    if (*tstr1 == _T('%'))
    { // New field
      if (tstr1[2] != _T('\0'))
      { // field does have something in it
        if (Opt)
#ifdef _UNICODE
        {
        };
#else
          OemToAnsi(tstr1, tstr1);
#endif
        switch (tstr1[1])
        {
        case _T('A'):
        case _T('E'):
        {
          foo = (tstr1[1] == _T('A')) ? &Tmp.Authors : &Tmp.Editor;
          if (*foo == NULL)
            *foo = _tcsdup(&tstr1[3]);
          else
          {
            lstrcpy(tstr2, *foo);
            free(*foo);
            lstrcat(tstr2, _T("\r\n"));
            lstrcat(tstr2, &tstr1[3]);
            *foo = _tcsdup(tstr2);
          }
          break;
        }
        case _T('C'):
          DOFIELD(Tmp.City);
          break;
        case _T('D'):
          DOFIELD(Tmp.Date);
          break;
        case _T('I'):
          DOFIELD(Tmp.Publisher);
          break;
        case _T('J'):
        case _T('B'):
        case _T('R'):
        {
          DOFIELD(Tmp.Journal);
          switch (tstr1[1])
          {
          case _T('J'):
            Tmp.RefType = 0;
            break;
          case _T('B'):
            Tmp.RefType = 1;
            break;
          case _T('R'):
            Tmp.RefType = 2;
          }
          break;
        }
        case _T('K'):
        {
          DOFIELD(Tmp.Keywords)
          else
          {
            lstrcpy(tstr2, Tmp.Keywords);
            free(Tmp.Keywords);
            lstrcat(tstr2, _T(", "));
            lstrcat(tstr2, &tstr1[3]);
            Tmp.Keywords = _tcsdup(tstr2);
          }
          break;
        }
        case _T('P'):
          DOFIELD(Tmp.Pages);
          break;
        case _T('T'):
          DOFIELD(Tmp.Title);
          break;
        case _T('V'):
          DOFIELD(Tmp.Vol);
          break;
        case _T('N'):
          DOFIELD(Tmp.VolNo);
          break;
        case _T('X'):
          DoAbstract(&tstr1[3], &Tmp);
          break;
        default:
          DoAbstract(tstr1, &Tmp);
        }
      }
    }
    else
      DoAbstract(tstr1, &Tmp); // More Abstract
    ReadLine(FS, tstr1, &EoF);
  } while ((!EoF) && (tstr1[0] != _T('\0')));
  if (Tmp.Keywords)
  { // place each keyword on a separate line
    for (Ptr2 = _tcsstr(Tmp.Keywords, _T(", ")); Ptr2 != NULL; Ptr2 = _tcsstr(Tmp.Keywords, _T(", ")))
    {
      *Ptr2 = _T('\r');
      Ptr2[1] = _T('\n');
    }
  }
  Tmp.Result = EoF ? 1 : 0;
  return (&Tmp);
}

LPTSTR t_export WhoAmI(void)
{
  return (_T("Refer format"));
}

LPTSTR t_export GetSpecs(void)
{
  return (_T("Refer text file (*.ref)\0*.REF\0All files (*.*)\0*.*\0\0"));
}

BOOL Opt_OnInitDialog(HWND dlg, HWND hwndFocus, LPARAM lParam)
{
  int n;

  n = GetConfigInt(_T("Refer"), _T("Opt"), 0);
  CheckDlgButton(dlg, 101, n);
  return TRUE;
}

void Opt_OnCommand(HWND Dialog, int id, HWND hwndCtl, UINT codeNotify)
{
  switch (id)
  {
  case IDOK:
    EndDialog(Dialog, IsDlgButtonChecked(Dialog, 101));
    break;
  case IDCANCEL:
    EndDialog(Dialog, -1);
    break;
  }
}

BOOL CALLBACK OptProc(HWND Dlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  switch (Msg)
  {
    HANDLE_MSG(Dlg, WM_INITDIALOG, Opt_OnInitDialog);
    HANDLE_MSG(Dlg, WM_COMMAND, Opt_OnCommand);
  }
  return FALSE;
}

#ifdef WIN32
void t_export Opts(HWND aparent)
{
#else
void t_export Opts(HWND aparent, _TCHAR *INIPath)
{
#endif
  int n;

  n = DialogBox(hInst, _T("OPTS"), aparent, OptProc);
  if (n >= 0)
    SetConfigInt(_T("Refer"), _T("Opt"), n);
}

#ifdef WIN32
BOOL WINAPI DllMain(

    HINSTANCE hinstDLL, // handle of DLL module
    DWORD fdwReason,    // reason for calling function
    LPVOID lpvReserved  // reserved
)
{

  _TCHAR **foo;

  switch (fdwReason)
  {
  case DLL_PROCESS_ATTACH:
  {
    FSBufSz = GetBufSz();
    hInst = hinstDLL;
    tstr1 = (_TCHAR *)malloc(FSBufSz);
    tstr2 = (_TCHAR *)malloc(FSBufSz);
    Opt = GetConfigInt(_T("Refer"), _T("Opt"), 0);
    return ((tstr1 && tstr2) ? TRUE : FALSE);
  }
  case DLL_PROCESS_DETACH:
  {
    free(tstr1);
    free(tstr2);
    break;
  }
  }
  return TRUE;
}

#else

int t_export WEP(int nParameter)
{
  free(tstr1);
  free(tstr2);
  return 1;
}

int t_export LibMain(HINSTANCE hInstance, WORD wDataSeg, WORD cbHeapSize, LPTSTR lpCmdLine)
{

  _TCHAR **foo;

  FSBufSz = GetBufSz();
  if (FSBufSz)
  {
    for (foo = &(Tmp.Authors); foo <= &(Tmp.Editor); foo++)
      *foo = NULL;
    tstr1 = (LPTSTR)malloc(FSBufSz);
    tstr2 = (LPTSTR)malloc(FSBufSz);
    hInst = hInstance;
    Opt = GetConfigInt(_T("Refer"), _T("Opt"), 0);
    if (tstr1 && tstr2)
      return 1;
    else
      return 0;
  }
  else
    return 0;
}
#endif
