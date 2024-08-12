#include "inc/globals.h"
#ifndef CUSTOM
#include "inc/refnag.h"
#include <time.h>

#ifndef WIN32
#include "rimpexp/rimpexp.h"
#endif

#include "inc/rsetlang.h"

#define ALLOWED_DAYS 30

_TCHAR inline *TranslateFrom(_TCHAR *Ptr)
{
  int N;

  for (N = 0; N <= 15; N++)
    Ptr[N] = (_TCHAR)(((BYTE)Ptr[N] - 14) ^ (BYTE)FileSpecs[N % 8]);
  return (Ptr);
}

void inline TranslateTo(_TCHAR *Ptr)
{
  int n;

  for (n = 0; n <= 15; n++)
    Ptr[n] = (_TCHAR)(((BYTE)Ptr[n] ^ (BYTE)(FileSpecs[n % 8])) + 14);
}

int CheckRegister(_TCHAR *Ptr)
{
  int n;
  long Checksum;
  int Sum = 0;

  for (n = 0; n <= 15; n++)
    Sum += (BYTE)Ptr[n];

  Checksum = (((MajorVersion - 0x00070008L) * 7) + 103) % 256;

  return (Sum % 256 == Checksum);
}

void RegProc_OnCommand(HWND Dlg, int id, HWND hwndCtl, UINT codeNotify)
{
  _TCHAR t1[RES_STR], t2[RES_STR];
  HKEY hkNag;
#ifdef WIN32
  DWORD dwDisposition;
#endif

  switch (id)
  {
  case IDOK:
  {
    GetDlgItemText(Dlg, ide_Code, t1, sizeof(t1) / sizeof(_TCHAR));
    if (CheckRegister(t1))
    {
      TranslateTo(t1);
#ifdef WIN32

      RegCreateKeyEx(
          HKEY_LOCAL_MACHINE,
          REG_VER_KEY,
          0,
          NULL,
          REG_OPTION_NON_VOLATILE,
          KEY_ALL_ACCESS,
          NULL,
          &hkNag,
          &dwDisposition);

      RegSetValueEx(
          hkNag,
          _T("ver"),
          0,
          REG_SZ,
          (BYTE *)t1,
          lstrlen(t1) * sizeof(_TCHAR));

      GetDlgItemText(Dlg, ide_Name, t1, RES_STR - 1);

      RegSetValueEx(
          hkNag,
          _T("user"),
          0,
          REG_SZ,
          (BYTE *)t1,
          lstrlen(t1) * sizeof(TCHAR));

      RegDeleteValue(hkNag, _T("vert"));
#else
      RegCreateKey(HKEY_CLASSES_ROOT, _T("Refs\\tjrc"), &hkNag);
      RegSetValue(hkNag, _T("ver"), REG_SZ, t1, lstrlen(t1));
      GetDlgItemText(Dlg, ide_Name, t1, RES_STR - 1);
      RegSetValue(hkNag, _T("user"), REG_SZ, t1, lstrlen(t1));
      RegDeleteKey(hkNag, _T("vert"));
#endif
      RegCloseKey(hkNag);
      Registered = TRUE;

      LoadString(ResInstance,
                 msg_Registered1,
                 t1, sizeof(t1) / sizeof(_TCHAR));

      LoadString(ResInstance,
                 msg_Registered2,
                 t2,
                 sizeof(t2) / sizeof(_TCHAR));

      MessageBox(Dlg, t1, t2, MB_OK | MB_ICONINFORMATION);

      EndDialog(Dlg, IDOK);
    }
    else
      ErrorBox(Dlg, err_BadRegister);

    break;
  }
  case IDCANCEL:
    EndDialog(Dlg, IDCANCEL);
  }
}

BOOL CALLBACK RegProc(HWND Dlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  switch (Msg)
  {
    HANDLE_MSG(Dlg, WM_COMMAND, RegProc_OnCommand);
  }
  return (FALSE);
}

#ifdef FERIC

BOOL TimeNag_OnEraseBackground(HWND Dlg, HDC DC)
{
  HDC MemDC;
  HBITMAP OldBitMap, BitMap;
  BITMAP BM;
  RECT sr;
  HBRUSH brush;

  brush = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
  BitMap = LoadBitmap(hinstCurrent, _T("FERICP"));
  MemDC = CreateCompatibleDC(DC);
  OldBitMap = SelectBitmap(MemDC, BitMap);
  GetObject(BitMap, sizeof(BM), &BM);
  GetClientRect(Dlg, &sr);
  FillRect(DC, &sr, brush);
  sr.left = (sr.right / 2) - (BM.bmWidth / 2);
  sr.top = 10;
  sr.right = sr.left + BM.bmWidth;
  sr.bottom = sr.top + BM.bmHeight;
  BitBlt(DC, sr.left, sr.top, BM.bmWidth, BM.bmHeight, MemDC, 0, 0, SRCCOPY);
  DeleteBitmap(SelectBitmap(MemDC, OldBitMap));
  DeleteDC(MemDC);

  return TRUE;
}

void TimeNag_OnCommand(HWND Dlg, int id, HWND hwndCtl, UINT codeNotify)
{
  switch (id)
  {
  case IDOK:
    EndDialog(Dlg, IDOK);
    break;
  case cm_Help:
    WinHelp(Dlg, HelpName, HELP_CONTEXT, 10);
    break;
  case cm_Help - 1:
    WinHelp(Dlg, HelpName, HELP_CONTEXT, 11);
    break;
  case id_BRegister:
  {
    if (DialogBox(ResInstance, _T("REGISTER"), Dlg, RegProc) == IDOK)
      EndDialog(Dlg, IDOK);
  }
  }
}

BOOL CALLBACK TimeNagProc(HWND Dlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  switch (Msg)
  {
    HANDLE_MSG(Dlg, WM_ERASEBKGND, TimeNag_OnEraseBackground);
    HANDLE_MSG(Dlg, WM_COMMAND, TimeNag_OnCommand);
  }
  return (FALSE);
}
#else // not FERIC

void NagProc_OnCommand(HWND Dlg, int id, HWND hwndCtl, UINT codeNotify)
{
  switch (id)
  {
  case IDOK:
    EndDialog(Dlg, IDOK);
    break;
  case cm_Help:
    WinHelp(Dlg, HelpName, HELP_CONTEXT, 3);
  }
}

BOOL CALLBACK NagProc(HWND Dlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  switch (Msg)
  {
    HANDLE_MSG(Dlg, WM_COMMAND, NagProc_OnCommand);
  }
  return (FALSE);
}

long t_diff;
int countdown;
UINT a_timer;

BOOL TimeNag_OnInitDialog(HWND Dlg, HWND hwndFocus, LPARAM lParam)
{
  _TCHAR m1[RES_STR];
  _TCHAR m2[RES_STR];

  a_timer = SetTimer(Dlg, 1, 1000, NULL);
  countdown = 30;
  EnableWindow(GetDlgItem(Dlg, IDOK), FALSE);
  LoadString(ResInstance, nag_timeleft, m1, sizeof(m1) / sizeof(_TCHAR));
  wsprintf(m2, m1, t_diff);
  SetDlgItemText(Dlg, 123, m2);
  return TRUE;
}

void TimeNag_OnTimer(HWND Dlg, UINT id)
{
  _TCHAR m1[RES_STR];
  _TCHAR m2[RES_STR];

  countdown--;
  LoadString(ResInstance, nag_timeleft, m1, sizeof(m1) / sizeof(_TCHAR));
  wsprintf(m2, m1, countdown);
  SetDlgItemText(Dlg, 123, m2);
  if (!countdown)
  {
    KillTimer(Dlg, a_timer);
    a_timer = 0;
    EnableWindow(GetDlgItem(Dlg, IDOK), TRUE);
  }
}

void TimeNag_OnCommand(HWND Dlg, int id, HWND hwndCtl, UINT codeNotify)
{
  switch (id)
  {
  case IDOK:
    EndDialog(Dlg, IDOK);
    break;
  case cm_Help:
    WinHelp(Dlg, HelpName, HELP_CONTEXT, 3);
    break;
  case id_BRegister:
  {
    if (DialogBox(ResInstance, _T("REGISTER"), Dlg, RegProc) == IDOK)
    {
      if (a_timer)
        KillTimer(Dlg, a_timer);
      EndDialog(Dlg, IDOK);
    }
  }
  }
}

BOOL CALLBACK TimeNagProc(HWND Dlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  switch (Msg)
  {
    HANDLE_MSG(Dlg, WM_INITDIALOG, TimeNag_OnInitDialog);
    HANDLE_MSG(Dlg, WM_TIMER, TimeNag_OnTimer);
    HANDLE_MSG(Dlg, WM_COMMAND, TimeNag_OnCommand);
  }
  return (FALSE);
}

void NewTimeStamp(HKEY hkNag, time_t timestamp, DWORD ver)
{
  _TCHAR t1[RES_STR];

  _ltot(timestamp, t1, 10);
#ifdef WIN32
  // time
  RegSetValueEx(
      hkNag,
      _T("vert"),
      0,
      REG_SZ,
      (BYTE *)t1,
      lstrlen(t1) * sizeof(_TCHAR));

  // version
  _ltot(ver, t1, 10);

  RegSetValueEx(
      hkNag,
      _T("vern"),
      0,
      REG_SZ,
      (BYTE *)&t1,
      lstrlen(t1) * sizeof(_TCHAR));

#else

  RegSetValue(
      hkNag,
      _T("vert"),
      REG_SZ,
      t1,
      lstrlen(t1) * sizeof(_TCHAR));
  _ltot(ver, t1, 10);

  RegSetValue(
      hkNag,
      _T("vern"),
      REG_SZ,
      t1,
      lstrlen(t1) * sizeof(_TCHAR));
#endif
}

BOOL CheckStampVersion(HKEY hkNag, DWORD ver)
{
  // Retrieves version stamp and checks it
  DWORD cb = RES_STR;
  DWORD n;
  _TCHAR t[RES_STR];

#ifdef WIN32
  DWORD dwType;

  if (RegQueryValueEx(
          hkNag,
          _T("vern"),
          NULL,
          &dwType,
          (BYTE *)t,
          &cb) == ERROR_SUCCESS)
  {
#else
  if (RegQueryValue(hkNag,
                    _T("vern"),
                    t,
                    (long *)&cb) == ERROR_SUCCESS)
  {
#endif
    t[cb] = _T('\0');
    n = _ttol(t);
    return (n >= ver); // only reset timer if this version is newer than the old.
  }
  else
    return FALSE;
}

void Naughty(LPCTSTR dialog)
{
  MessageBox(0,
             _T("This dialog could not be executed.  \
This is either a bug or an attempt to hack the nag screen.\n\n\
If the former, please report it to the author.\nIf the latter, \
and you are the hacker: tough, I anticipated this one!\n\n\
If you are not the perpetrator, please also report this to the author.  \
Refs will now terminate.\n"),
             dialog, MB_ICONSTOP | MB_OK);

  FreeLibrary(ResInstance);

#ifndef WIN32
  if (CommCtrlAvail)
    FreeLibrary(CommCtrlAvail);
#endif
  exit(1);
}

void CheckTimeStamp(HWND AParent)
{
  DWORD cb = RES_STR - 1;
  time_t cur_time;
  time_t old_time;
  HKEY hkNag;
  _TCHAR t1[RES_STR];

#ifdef WIN32
  DWORD dwDisposition;
  DWORD dwType;
#endif

  // Get current time
  cur_time = time(NULL);

// Open key and get time value
#ifdef WIN32

  if (RegCreateKeyEx(
          HKEY_LOCAL_MACHINE,
          REG_VER_KEY,
          0,
          NULL,
          REG_OPTION_NON_VOLATILE,
          KEY_ALL_ACCESS,
          NULL,
          &hkNag,
          &dwDisposition) == ERROR_SUCCESS)
  {

    if (RegQueryValueEx(
            hkNag,
            _T("vert"),
            NULL,
            &dwType,
            (BYTE *)t1,
            &cb) == ERROR_SUCCESS)
    {
#else
  if (RegCreateKey(HKEY_CLASSES_ROOT,
                   _T("Refs\\tjrc"),
                   &hkNag) == ERROR_SUCCESS)
  {

    if (RegQueryValue(hkNag,
                      _T("vert"),
                      t1,
                      (long *)&cb) == ERROR_SUCCESS)
    {

#endif
      // Timestamp was there, so get the time
      old_time = _ttol(t1);
      t_diff = (cur_time - old_time) / (60L * 60 * 24);

      if (CheckStampVersion(hkNag, MajorVersion))
      {
        if (t_diff > ALLOWED_DAYS)
        {
          if (DialogBox(ResInstance,
                        _T("NAG"),
                        AParent,
                        TimeNagProc) == -1)

            Naughty(_T("NAG"));
        }
      }
      else
      {
        if (DialogBox(ResInstance,
                      _T("NAGFIRST"),
                      AParent,
                      NagProc) == -1)

          Naughty(_T("NAGFIRST"));

        NewTimeStamp(hkNag, cur_time, MajorVersion);
      }
    }
    else
    {
      // No time value in Registry, so
      // Refs has not been run on this machine before
      if (DialogBox(ResInstance,
                    _T("NAGFIRST"),
                    AParent,
                    NagProc) == -1)

        Naughty(_T("NAGFIRST"));

      NewTimeStamp(hkNag, cur_time, MajorVersion);
    }
    RegCloseKey(hkNag);
  }
}

#endif // not FERIC

void NagScreen(HWND AParent)
{
  DWORD cb = RES_STR - 1;
  long r;
  _TCHAR t1[RES_STR];
  HKEY hkNag;
#ifdef WIN32
  DWORD dwType;
#else
  _TCHAR t2[RES_STR];
#endif

  Registered = FALSE;

#ifdef WIN32
  if ((r = RegOpenKeyEx(
           HKEY_LOCAL_MACHINE,
           REG_VER_KEY,
           0,
           KEY_READ,
           &hkNag)) == ERROR_SUCCESS)
  {

    r = RegQueryValueEx(
        hkNag,
        _T("ver"),
        NULL,
        &dwType,
        (BYTE *)t1,
        &cb);

#else
  if ((r = RegOpenKey(
           HKEY_CLASSES_ROOT,
           _T("Refs\\tjrc"),
           &hkNag)) == ERROR_SUCCESS)
  {

    r = RegQueryValue(
        hkNag,
        _T("ver"),
        t1,
        (long *)&cb);

#endif
    RegCloseKey(hkNag);
    Registered = (r == ERROR_SUCCESS);
  }
#ifndef WIN32
  if (!Registered)
  {
    Registered = GetPrivateProfileString(DStrFiles,
                                         "Register",
                                         "", t1, SCRATCH_SIZE - 1,
                                         GetINIFilePath());
    if (Registered)
    {
      WritePrivateProfileString(DStrFiles,
                                "Register", NULL, GetINIFilePath());

      GetPrivateProfileString(DStrFiles, "Name", "The Unknown User",
                              t2, SCRATCH_SIZE - 1, GetINIFilePath());

      WritePrivateProfileString(DStrFiles, "Register", NULL,
                                GetINIFilePath());

      RegCreateKey(HKEY_CLASSES_ROOT, "Refs\\tjrc", &hkNag);
      RegSetValue(hkNag, "ver", REG_SZ, t1, lstrlen(t1));
      RegSetValue(hkNag, "user", REG_SZ, t2, lstrlen(t2));
      RegDeleteKey(hkNag, "vert");
      RegCloseKey(hkNag);
    }
  }
#endif
  if (Registered)
    Registered = CheckRegister(TranslateFrom(t1));
  if (!Registered)
  {
#ifndef FERIC
    CheckTimeStamp(AParent);
#else
    DialogBox(
        hinstCurrent,
        "FERICD",
        AParent,
        TimeNagProc);
#endif
  }
}
#endif // not CUSTOM
