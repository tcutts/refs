/*********************************************************/
/**                                                     **/
/**      BIDS.C      - BIDS Download format filter      **/
/**                                                     **/
/**      This file is (C) Tim Cutts 1993,1995 and may   **/
/**      not be redistributed in its present form, but  **/
/**      may be used, modified, in other programs.      **/
/**                                                     **/
/*********************************************************/

#include <tchar.h>
#include <windows.h>
#include <mmsystem.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <malloc.h>
#include <windowsx.h>

// Method of marking functions for export differs between
// Win16 and Win32
#ifdef WIN32
#define t_export _declspec(dllexport)
#else
#define t_export CALLBACK _export
#endif

#include "../../inc/imptfr.h"
#include "../../rimpexp/rimpexp.h"

HINSTANCE hInst;
LPTSTR tstr1;
LPTSTR tstr2;
LPTSTR *p;
static TImportRef Tmp;

int OptFlags;

BOOL EoF;
long BufSz;

_TCHAR *FirstNonWhite(_TCHAR *APtr)
{
  _TCHAR *BPtr;

  BPtr = APtr;
  while (strchr(" \n\r\t-", BPtr[0]))
    BPtr++;
  return (BPtr);
}

BOOL Opt_OnInitDialog(HWND Dialog, HWND hwndFocus, LPARAM lParam)
{
  OptFlags = GetConfigInt("BIDS", "Opts", 7);
  CheckDlgButton(Dialog, 101, (OptFlags & 1));
  CheckDlgButton(Dialog, 102, (OptFlags >> 1) & 1);
  CheckDlgButton(Dialog, 104, (OptFlags >> 2));
  return TRUE;
}

void Opt_OnCommand(HWND Dialog, int id, HWND hwndCtl, UINT codeNotify)
{
  switch (id)
  {
  case IDOK:
  {
    OptFlags = IsDlgButtonChecked(Dialog, 101) |
               (IsDlgButtonChecked(Dialog, 102) << 1) |
               (IsDlgButtonChecked(Dialog, 104) << 2);
    SetConfigInt("BIDS", "Opts", OptFlags);
  }
  case IDCANCEL:
    EndDialog(Dialog, id);
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
void t_export Opts(HWND AParent)
{
#else
void t_export Opts(HWND AParent, LPTSTR APath)
{
#endif
  DialogBox(hInst, "OPTDLG", AParent, OptProc);
}

void AddStuff(LPTSTR Work, LPTSTR Src, LPTSTR *Dest)
{
  if (*Dest)
  {
    lstrcpy(Work, *Dest);
    free(*Dest);
    lstrcat(Work, "\x01");
  }
  else
    Work[0] = '\0';
  lstrcat(Work, FirstNonWhite(&Src[2]));
  *Dest = strdup(Work);
}

void SepAuthors(void)
{
  LPTSTR Ptr2;
  LPTSTR Ptr3;

  /*Make authors line separated*/
  Ptr2 = Tmp.Authors;
  tstr1[0] = '\0';
  while (Ptr2)
  {
    Ptr3 = Ptr2;
    Ptr3[0] = (_TCHAR)((BYTE)(Ptr3[0]) & ~32);
    Ptr2 = strchr(Ptr3, ',');
    if (Ptr2)
    {
      Ptr2 += 2;
      while (IsCharAlpha(Ptr2[0]))
      {
        Ptr2[0] = (_TCHAR)((BYTE)(Ptr2[0]) & ~32);
        Ptr2++;
      }
    }
    Ptr2 = strchr(Ptr3, ';');
    if (Ptr2)
    {
      Ptr2[0] = '\0';
      lstrcat(tstr1, Ptr3);
      lstrcat(tstr1, "\r\n");
      Ptr2[0] = ':';
      Ptr2++;
    }
    else
      lstrcat(tstr1, Ptr3);
  }
  if (Tmp.Authors)
  {
    free(Tmp.Authors);
    Tmp.Authors = strdup(tstr1);
  }
}

void SepEditors(void)
{
  LPTSTR p;
  LPTSTR q;

  if (Tmp.Editor)
  {
    /*copy to temp*/
    lstrcpy(tstr1, Tmp.Editor);
    p = tstr1;
    while (p)
    {
      /*at the beginning of a name, so capitalise*/
      *p = (_TCHAR)((BYTE)(*p) & ~32);
      p++;
      q = strchr(p, '_');
      if (q)
      {
        /*found initials*/
        *q = '\0';
        /*LowerCase all up to the _*/
        AnsiLower(p);
        q++;
        lstrcpy(tstr2, q);
        lstrcat(tstr1, ", ");
        lstrcat(tstr1, tstr2);
        q++;
        p = strchr(q, ',');
        if (p)
        {
          *p = '\0';
          AnsiUpper(q);
          *p = ',';
        }
      }
      else
      {
        q = strchr(p, ',');
        if (q)
        {
          /*found next name*/
          *q = '\0';
          AnsiLower(p);
          p = q;
        }
        else
        {
          /*this is the last one*/
          AnsiLower(p);
          p = NULL;
        }
      }
      if (p)
      {
        p[0] = '\r';
        p[1] = '\n';
      }
    }
    free(Tmp.Editor);
    Tmp.Editor = strdup(tstr1);
  }
}

#define CODE(x, y) \
  case x:          \
    p = &Tmp.y;    \
    break

#ifdef WIN32
TImportRef t_export *LoadRef(HWND aparent, LPMMIOINFO FS)
{
#else
TImportRef FAR *PASCAL _export LoadRef(HWND AParent, LPMMIOINFO FS, _TCHAR *INIPath)
{
#endif
  LPTSTR Ptr2;
  unsigned int Code;
  int Finished;

  if (OptFlags == 0xFFFF)
    OptFlags = GetConfigInt("BIDS", "Opts", 7);

  Finished = FALSE;
  p = &Tmp.Authors;
  Tmp.Result = 0;
  Tmp.RefType = 0;
  do
  {
    if (*p)
      free(*p);
    *p = NULL;
    p++;
  } while (p <= &Tmp.SortStr);
  do
  {
    ReadLine(FS, tstr1, &EoF);
    Ptr2 = strstr(tstr1, "Record");
  } while ((!EoF) && (!Ptr2));
  if (EoF)
  {
    Tmp.Result = 2;
    return (&Tmp);
  }
  ReadLine(FS, tstr1, &EoF);
  ReadLine(FS, tstr1, &EoF);
  while ((!Finished) && (!EoF))
  {
    Code = ((unsigned int)tstr1[0] << 8) + (unsigned int)tstr1[1];
    switch (Code)
    {
    case 0x2000:
      Finished = TRUE;
      break;
    case 0x2020:
      break;                 // continue with current field
      CODE(0x4142, Text);    // AB
      CODE(0x4155, Authors); // AU
    case 0x4348:
    { // CH
      p = &Tmp.Vol;
      Tmp.RefType = 1;
      break;
    }
      CODE(0x434F, Text);     // CO
      CODE(0x4454, SortStr);  // DT
      CODE(0x4544, Editor);   // ED
      CODE(0x4741, Keywords); // GA
      CODE(0x4A4E, Journal);  // JN
      CODE(0x4B50, Keywords); // KP
      CODE(0x4E41, City);     // NA
      CODE(0x4E4F, VolNo);    // NO
      CODE(0x5047, Pages);    // PG
      CODE(0x5055, City);     // PU
      CODE(0x5059, Date);     // PY
      CODE(0x5449, Title);    // TI
      CODE(0x564F, Vol);      // VO
      CODE(0x5653, Keywords); // VS
    case 0x4845:
    case 0x534F:
    { // SO
      if (!Tmp.Journal)
        p = &Tmp.Journal;
      else
        p = &Tmp.Keywords;
      Tmp.RefType = 2;
      break;
    }
    default:
    {
      if (Code < 0x0100)
        Finished = TRUE;
      p = NULL;
    }
    }
    if (!Finished)
    {
      if (p)
        AddStuff(tstr2, tstr1, p);
      ReadLine(FS, tstr1, &EoF);
    }
  }
  if (EoF)
    Tmp.Result = 1;

  /*Strip all '\001''s inserted before*/
  p = &Tmp.Authors;
  do
  {
    Ptr2 = *p;
    while (Ptr2)
    {
      Ptr2 = strchr(Ptr2, '\x01');
      if (Ptr2)
        Ptr2[0] = ' ';
    }
    if ((*p) && (p != &Tmp.Text) && (OptFlags & 2))
    {
      AnsiLower(*p);
      if (IsCharAlpha(**p))
        **p = (_TCHAR)((BYTE)(**p) & ~32);
    }
    p++;
  } while (p <= &Tmp.SortStr);
  SepAuthors();
  SepEditors();
  /*Make Keywords line separated*/
  Ptr2 = Tmp.Keywords;
  while (Ptr2)
  {
    Ptr2 = strstr(Ptr2, ", ");
    if (Ptr2)
    {
      Ptr2[0] = '\r';
      Ptr2[1] = '\n';
      Ptr2[2] = (_TCHAR)((BYTE)(Ptr2[2]) & ~32);
    }
  }
  tstr1[0] = '\0';
  if (OptFlags & 1)
    lstrcat(tstr1, "unread");
  if ((OptFlags & 4) && (Tmp.SortStr))
  {
    if (tstr1[0] != '\0')
      lstrcat(tstr1, "\r\n");
    lstrcat(tstr1, Tmp.SortStr);
  }
  if (tstr1[0] != '\0')
  {
    if (Tmp.Keywords)
    {
      lstrcat(tstr1, "\r\n");
      lstrcat(tstr1, Tmp.Keywords);
      free(Tmp.Keywords);
    }
    Tmp.Keywords = strdup(tstr1);
  }
  return (&Tmp);
}

LPTSTR t_export WhoAmI(void)
{
  return _T("BIDS (ISI) Download format");
}

LPTSTR t_export GetSpecs(void)
{
  return _T("ISI text file (*.isi)\0*.ISI\0All files (*.*)\0*.*\0\0");
}

#ifdef WIN32
BOOL WINAPI DllMain(

    HINSTANCE hinstDLL, // handle of DLL module
    DWORD fdwReason,    // reason for calling function
    LPVOID lpvReserved  // reserved
)
{

  switch (fdwReason)
  {
  case DLL_PROCESS_ATTACH:
  {
    BufSz = GetBufSz();
    tstr1 = (_TCHAR *)malloc(BufSz);
    tstr2 = (_TCHAR *)malloc(BufSz);
    OptFlags = 0xFFFF;
    hInst = hinstDLL;
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

int CALLBACK _export WEP(int nParameter)
{
  free(tstr1);
  free(tstr2);
  return 1;
}

int CALLBACK _export LibMain(HINSTANCE hInstance, WORD wDataSeg, WORD cbHeapSize, LPTSTR lpCmdLine)
{

  BufSz = GetBufSz();
  if (BufSz)
  {
    tstr1 = (LPTSTR)malloc(BufSz);
    tstr2 = (LPTSTR)malloc(BufSz);
    hInst = hInstance;
    OptFlags = 0xFFFF;
    if (tstr1 && tstr2)
      return 1;
    else
      return 0;
  }
  else
    return 0;
}

#endif
