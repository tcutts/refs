#include "inc/globals.h"
#include "inc/refabout.h"

BOOL About_OnInitDialog(HWND Wnd, HWND hwndFocus, LPARAM lParam)
{
  _TCHAR t1[MAX_PATH], t2[MAX_PATH], *p;
#ifndef CUSTOM
  HKEY hkNag;
  DWORD cb = MAX_PATH - 1;
#ifdef WIN32
  DWORD dwType;
#endif
  VS_FIXEDFILEINFO *rver;
  DWORD verSz;
  DWORD rvHnd;
  UINT rlen;

  verSz = GetFileVersionInfoSize(EXENAME, &rvHnd);

  GetFileVersionInfo(EXENAME, rvHnd, sizeof(t1), t1);

  if (verSz)
  {
    VerQueryValue(t1, _T("\\"), (void **)&rver, &rlen);

    wsprintf(t2, _T("Refs %d.%d.%d"),
             HIWORD(rver->dwProductVersionMS),
             LOWORD(rver->dwProductVersionMS),
             HIWORD(rver->dwProductVersionLS));

    SetDlgItemText(Wnd, 764, t2);

    wsprintf(t2, _T("%s: %d.%d.%d.%d"),
             EXENAME,
             HIWORD(rver->dwFileVersionMS),
             LOWORD(rver->dwFileVersionMS),
             HIWORD(rver->dwFileVersionLS),
             LOWORD(rver->dwFileVersionLS));

    SetDlgItemText(Wnd, 765, t2);
  }

  verSz = GetFileVersionInfoSize(_T("RIMPEXP.DLL"), &rvHnd);
  GetFileVersionInfo(_T("RIMPEXP.DLL"), rvHnd, sizeof(t1), t1);

  if (verSz)
  {
    VerQueryValue(t1, _T("\\"), (void **)&rver, &rlen);
    wsprintf(t2, _T("RIMPEXP.DLL: %d.%d.%d.%d"),
             HIWORD(rver->dwFileVersionMS),
             LOWORD(rver->dwFileVersionMS),
             HIWORD(rver->dwFileVersionLS),
             LOWORD(rver->dwFileVersionLS));

    SetDlgItemText(Wnd, 766, t2);
  }

  GetModuleFileName(ResInstance, t2, sizeof(t2));

  verSz = GetFileVersionInfoSize(t2, &rvHnd);

  GetFileVersionInfo(t2, rvHnd, sizeof(t1), t1);

  p = _tcsrchr(t2, _T('\\'));

  p++;

  if (verSz)
  {
    wsprintf(t1, _T("%s: %d.%d.%d.%d"),
             p,
             HIWORD(rver->dwFileVersionMS),
             LOWORD(rver->dwFileVersionMS),
             HIWORD(rver->dwFileVersionLS),
             LOWORD(rver->dwFileVersionLS));
  }
  else
    wsprintf(t1, _T("%s: No version info"), p);

  SetDlgItemText(Wnd, 767, t1);

  if (!Registered)
#ifdef FERIC
    lstrcpy(t1, _T("Forest Engineering Research Institute of Canada"));
#else
    LoadString(ResInstance, wrn_UnRgstr, t1, sizeof(t1) / sizeof(_TCHAR));
#endif
  else
  {
#ifdef WIN32
    if (RegOpenKeyEx(
            HKEY_LOCAL_MACHINE,
            REG_VER_KEY,
            0,
            KEY_READ,
            &hkNag) == ERROR_SUCCESS)
    {

      if (RegQueryValueEx(
              hkNag,
              _T("user"),
              NULL,
              &dwType,
              (LPBYTE)t2,
              &cb) == ERROR_SUCCESS)
#else
    if (RegOpenKey(HKEY_CLASSES_ROOT, _T("Refs\\tjrc"), &hkNag) == ERROR_SUCCESS)
    {
      if (RegQueryValue(hkNag, _T("user"), t2, (long *)&cb) == ERROR_SUCCESS)
#endif
        lstrcpy(t1, t2);
      RegCloseKey(hkNag);
    }
    else
      lstrcpy(t1, _T("The Unknown User"));
  }
  SetDlgItemText(Wnd, id_RegisteredTo, t1);
#else
  SetDlgItemText(Wnd, id_RegisteredTo, _T("A Company Ltd"));
#endif
  return (FALSE);
}

void About_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
  if (id == IDOK)
    EndDialog(hwnd, IDOK);
}

BOOL CALLBACK AboutProc(HWND Wnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  switch (Msg)
  {
    HANDLE_MSG(Wnd, WM_INITDIALOG, About_OnInitDialog);
    HANDLE_MSG(Wnd, WM_COMMAND, About_OnCommand);
  }
  return (FALSE);
}

void inline About(void)
{
  DialogBox(ResInstance, _T("ABOUT"), FrameWnd, AboutProc);
}
