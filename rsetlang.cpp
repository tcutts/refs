#include "inc/globals.h"
#include "inc/rsetlang.h"
#include "rimpexp/rimpexp.h"
#include "inc/editdlg.h"
#include <direct.h>

#ifdef WIN32
#define DESCRIBE "Describe"
#else
#define DESCRIBE "DESCRIBE"
#endif

_TCHAR LangStr[16], *Langs[8], verprob[] = _T("\nSome functionality may not work as expected.\n\nDo you want to use it anyway?");

long MajorVersion = 0;
long MinorVersion = 0;

void GetRefsVersionInfo(void)
{
  VS_FIXEDFILEINFO *rver;
  DWORD verSz;
  DWORD rvHnd;
  UINT rlen;
  _TCHAR t1[260];

  verSz = GetFileVersionInfoSize(EXENAME, &rvHnd);

  if (verSz)
  {
    GetFileVersionInfo(EXENAME, rvHnd, sizeof(t1), t1);
    VerQueryValue(t1, _T("\\"), (void **)&rver, &rlen);
    MajorVersion = rver->dwFileVersionMS;
    MinorVersion = rver->dwFileVersionLS;
  }
}

int CheckLanguageVersion(HWND Dlg, int n)
{
  VS_FIXEDFILEINFO *lver;
  DWORD verHnd;
  DWORD verSz;
  UINT llen;
  _TCHAR t2[260];

  verSz = GetFileVersionInfoSize(Langs[n], &verHnd);
  if (verSz)
  {
    GetFileVersionInfo(Langs[n], verHnd, sizeof(t2), t2);
    VerQueryValue(t2, _T("\\"), (void **)&lver, &llen);
    if (MajorVersion < lver->dwProductVersionMS)
    {
      wsprintf(t2, _T("%s was designed for a more\nrecent version of Refs.%s"), Langs[n], verprob);
      return (MessageBox(Dlg, t2, _T("Warning!"), MB_YESNO | MB_ICONINFORMATION));
    }
    if (MajorVersion > lver->dwProductVersionMS)
    {
      wsprintf(t2, _T("%s was designed for a previous\nversion of Refs.%s"), Langs[n], verprob);
      return (MessageBox(Dlg, t2, _T("Warning!"), MB_YESNO | MB_ICONINFORMATION));
    }
    return (IDYES);
  }
  else
  {
    wsprintf(t2, _T("%s contains no version information.\nIt is probably an old version.%s"), Langs[n], verprob);
    return (MessageBox(Dlg, t2, _T("Warning!"), MB_YESNO | MB_ICONINFORMATION));
  }
}

void DispLangs(HWND ADlg)
{
  int N, t;

  t = ListBox_GetCount(GetDlgItem(ADlg, id_LangList)) - 1;
  for (N = 0; N <= t; N++)
    free(Langs[N]);
}

_TCHAR *tlangptr;

void SetLang_OnCommand(HWND Dlg, int id, HWND hwndCtl, UINT codeNotify)
{
  int N;

  switch (id)
  {
  case IDOK:
  case id_LangList:
  {
    if ((id == IDOK) || (codeNotify == LBN_DBLCLK))
    {
      N = ListBox_GetCurSel(GetDlgItem(Dlg, id_LangList));
      if (CheckLanguageVersion(Dlg, N) == IDYES)
      {
        SetConfigStr(DStrDisplay, _T("Language"), Langs[N]);
        lstrcpy(tlangptr, Langs[N]);
        DispLangs(Dlg);
        EndDialog(Dlg, IDOK);
      }
    }
    break;
  }
  case IDCANCEL:
  {
    DispLangs(Dlg);
    EndDialog(Dlg, IDCANCEL);
    break;
  }
  }
}

BOOL SetLang_OnInitDialog(HWND Dlg, HWND hwndFocus, LPARAM lParam)
{
  LPTSTR p;
  _TCHAR t1[MAX_PATH];
  int N = 0;
  HINSTANCE LibHnd;
  HWND lb;
  SPECPROC SpecProc;
#ifndef WIN32
  int t;
  struct find_t finfo;
#else
  HANDLE hFind;
  BOOL t;
  WIN32_FIND_DATA finfo;
#endif

  tlangptr = (LPTSTR)lParam;
  // Fill List box with available DLLs
  GetModuleFileName(ResInstance, t1, MAX_PATH - 1);
  p = _tcsrchr(t1, _T('\\'));
  lstrcpy(LangStr, &p[1]);
  GetModuleFileName(hinstCurrent, t1, MAX_PATH - 1);
  p = _tcsrchr(t1, _T('\\'));
  p[0] = _T('\0');
  _tchdir(t1);
  if (*t1 != _T('\\')) // local machine
    _chdrive((BYTE)*t1 - (BYTE)'A' + 1);
  lstrcpy(t1, _T("REF*.DLL"));

  lb = GetDlgItem(Dlg, id_LangList);

#ifndef WIN32
  t = _dos_findfirst((_TCHAR *)t1, 0, &finfo);
  while ((t == 0) && (N < 8))
  {
    LibHnd = LoadLibrary(finfo.name);
    if (LibHnd >= (HINSTANCE)32)
    {
      SpecProc = (SPECPROC)GetProcAddress(LibHnd, "DESCRIBE");
      if (SpecProc)
      {
        Langs[ListBox_AddString(lb, SpecProc())] =
            _tcsdup(finfo.name);
        N++;
      }
      FreeLibrary(LibHnd);
      LibHnd = 0;
    }
    t = _dos_findnext(&finfo);
  }
#else
  hFind = FindFirstFile(t1, &finfo);
  if (hFind != INVALID_HANDLE_VALUE)
  {
    t = TRUE;
    while (t && (N < 8))
    {
      LibHnd = LoadLibrary(finfo.cFileName);
      if (LibHnd >= (HINSTANCE)32)
      {
        SpecProc = (SPECPROC)GetProcAddress(LibHnd, DESCRIBE);
        if (SpecProc)
        {
          Langs[ListBox_AddString(lb, SpecProc())] =
              _tcsdup(finfo.cFileName);
          N++;
        }
        FreeLibrary(LibHnd);
        LibHnd = 0;
      }
      t = FindNextFile(hFind, &finfo);
    }
  }
#endif

  SpecProc = (SPECPROC)GetProcAddress(ResInstance, DESCRIBE);
  lstrcpy(t1, SpecProc());
  ListBox_SetCurSel(lb, ListBox_FindString(lb, -1, t1));
  return TRUE;
}

BOOL CALLBACK SetLangProc(HWND Dlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  switch (Msg)
  {
    HANDLE_MSG(Dlg, WM_COMMAND, SetLang_OnCommand);
    HANDLE_MSG(Dlg, WM_INITDIALOG, SetLang_OnInitDialog);
  }
  return (FALSE);
}

void SetLanguage(LPTSTR DLL)
{
  HMENU NewMenu;
  HINSTANCE NewInst;
  HWND cWnd;
  LPRefWndData WorkDat;
  _TCHAR t1[MAX_PATH], t2[RES_STR];

  if ((DLL) || (DialogBoxParam(ResInstance, _T("LANGDLG"), FrameWnd, SetLangProc, (LPARAM)t2) == IDOK))
  {
    NewInst = LoadLibrary(DLL ? DLL : t2);
    if (NewInst > (HINSTANCE)32)
    {

      NewMenu = LoadMenu(NewInst, _T("MAIN"));

      if (FMenu)
      {
        FORWARD_WM_MDISETMENU(ClientWnd, TRUE, NewMenu, GetSubMenu(NewMenu, 5), SendMessage);
        DrawMenuBar(FrameWnd);
        DestroyMenu(FMenu);
      }
      else
        SetMenu(FrameWnd, NewMenu);

      FMenu = NewMenu;

      if (ResInstance)
        FreeLibrary(ResInstance);

      ResInstance = NewInst;

      if (BibData)
      {
        LoadString(ResInstance, str_BibWndName, t1, sizeof(t1) / sizeof(_TCHAR));
        SetWindowText(BibData->Window, t1);
      }

      LoadString(ResInstance, str_Searchable, t1, sizeof(t1) / sizeof(_TCHAR));
      LoadString(ResInstance, str_AndWord, AndWord, sizeof(AndWord) / sizeof(_TCHAR));
      LoadString(ResInstance, str_Untitled, Untitled, sizeof(Untitled) / sizeof(_TCHAR));

      if (ActiveFile)
      {
        for (cWnd = ActiveFile->Window;
             cWnd != NULL;
             cWnd = GetNextWindow(cWnd, GW_HWNDNEXT))
        {

          WorkDat = (LPRefWndData)GetWindowLong(cWnd, 0);
          SetWindowText(WorkDat->SWnd, t1);

          if ((WorkDat != BibData) &&
              (WorkDat->FPath[0] == '\0') &&
              (WorkDat->SrchPat == NULL))
            SetWindowText(WorkDat->Window, Untitled);
        }
      }

      // make sure edit control adjustments are re-made
      ctls_to_move[0][1] = -1;
    }
  }
}
