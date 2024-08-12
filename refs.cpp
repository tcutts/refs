#include "inc/globals.h"
#include "inc/refabout.h"
#include "rimpexp/rimpexp.h"
#ifdef OLE
#include <ole2.h>
#endif
#include "inc/refio.h"
#include "inc/editdlg.h"
#ifndef CUSTOM
#include "inc/refnag.h"
#endif
#include "inc/rsetlang.h"

#ifndef FERIC
#define SPLASH
#endif

#ifdef SPLASH

HBITMAP SBitmap;
long Ticks;

BOOL Splash_OnInitDialog(HWND Dlg, HWND hwndFocus, LPARAM lParam)
{
  BITMAP BM;
  RECT cr;
  RECT wr;
  int xb, yb;

  SetWindowText(Dlg, _T("Refs Loading..."));
  SBitmap = LoadBitmap(hinstCurrent, _T("SPLSH"));
  GetObject(SBitmap, sizeof(BM), &BM);

  GetClientRect(Dlg, &cr);
  GetWindowRect(Dlg, &wr);

  xb = (wr.right - wr.left) - (cr.right - cr.left);
  yb = (wr.bottom - wr.top) - (cr.bottom - cr.top);

  GetClientRect(GetDesktopWindow(), &cr);

  MoveWindow(
      Dlg,
      (cr.right - BM.bmWidth) / 2,
      (cr.bottom - BM.bmHeight) / 2,
      BM.bmWidth + xb,
      BM.bmHeight + yb,
      TRUE);

  return TRUE;
}

BOOL Splash_OnDestroy(HWND Dlg)
{
  DeleteBitmap(SBitmap);
  SBitmap = NULL;
  return FALSE;
}

BOOL Splash_OnEraseBkGnd(HWND Dlg, HDC DC)
{
  HDC MemDC;
  HBITMAP OldBitMap;
  BITMAP BM;

  MemDC = CreateCompatibleDC(DC);
  OldBitMap = SelectBitmap(MemDC, SBitmap);

  GetObject(SBitmap, sizeof(BM), &BM);

  BitBlt(DC, 0, 0, BM.bmWidth, BM.bmHeight, MemDC, 0, 0, SRCCOPY);

  SelectBitmap(MemDC, OldBitMap);
  DeleteDC(MemDC);

  return TRUE;
}

BOOL CALLBACK _export SplashProc(HWND Dlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{

  switch (Msg)
  {
    HANDLE_MSG(Dlg, WM_ERASEBKGND, Splash_OnEraseBkGnd);
    HANDLE_MSG(Dlg, WM_INITDIALOG, Splash_OnInitDialog);
    HANDLE_MSG(Dlg, WM_DESTROY, Splash_OnDestroy);
  }

  return FALSE;
}
#endif

#ifndef WIN32
void FindINIFile()
{
  _TCHAR rlib[MAX_PATH];
  struct _stat AFile;
  int N;

  // Find INI file
  N = GetWindowsDirectory(rlib, sizeof(rlib));

  if (rlib[N - 1] != _T('\\'))
    lstrcat(rlib, _T("\\"));

  lstrcat(rlib, _T("REFS.INI"));

  if (_tstat(rlib, &AFile) == -1)
  {
    GetModuleFileName(hinstCurrent, rlib, sizeof(rlib));
    lstrcpy(_tcsrchr(rlib, _T('.')), _T(".INI"));
  }

  SetINIFilePath(rlib);
  lstrcpy(INIFile, rlib);
}
#endif

void ActivateOtherRefs(HWND otherWnd, LPSTR lpCmdLine)
{

  BringWindowToTop(GetLastActivePopup(otherWnd));

#ifdef WIN32

  int N;
  COPYDATASTRUCT cds;

  for (N = 1; N < __argc; N++)
  {
    cds.lpData = __argv[N];
    cds.cbData = lstrlenA(__argv[N]);
    cds.dwData = cm_FOpen;
    SendMessage(otherWnd, WM_COPYDATA, 0, (LPARAM)&cds);
  }

#else

  LPSTR p, q;

  p = lpCmdLine;

  while ((p != NULL) && (p[0] != '\0'))
  {

    q = strchr(p, ' ');

    if (q)
      q[0] = '\0';

    SendMessage(otherWnd, WM_NEWDATA, 0, (LPARAM)p);

    if (q)
    {
      q[0] = ' ';
      p = &q[1];
    }
    else
      p = NULL;
  }

#endif
}

void LoadResourceDLL(_TCHAR *rlib)
{
  // Load requested Resource DLL

  int OEMode;

  // prevent load failures from producing a dialog
  OEMode = SetErrorMode(0x8000);
  GetConfigStr(rlib, 13, DStrDisplay, _T("Language"), _T("REFEN.DLL"));
  ResInstance = LoadLibrary(rlib);

  // restore old error reporting mode
  SetErrorMode(OEMode);

  if (ResInstance < (HINSTANCE)32)
  {
    MessageBox(0, _T("Cannot load any language resources!\r\nWhere is REFEN.DLL?"),
               _T("Refs: Fatal error!"), MB_ICONEXCLAMATION | MB_OK);
    exit(1);
  }
  else
    FreeLibrary(ResInstance);

  // free resources again - they will be loaded properly later.
  ResInstance = 0;
}

#if defined(CC_TOOLBAR) && !defined(WIN32)
void inline DynamicCommonControls(void)
{
  // Load requested Resource DLL

  int OEMode;

  // prevent load failures from producing a dialog
  OEMode = SetErrorMode(0x8000);
  CommCtrlAvail = LoadLibrary("COMMCTRL.DLL");

  // restore old error reporting mode
  SetErrorMode(OEMode);

  if (CommCtrlAvail >= (HINSTANCE)32)
  {

    CreateToolbarDynamic = (CREATETOOLBARPROC)GetProcAddress(CommCtrlAvail, "CREATETOOLBAR");
    InitCommonControlsDynamic = (INITCOMMCTRLPROC)GetProcAddress(CommCtrlAvail, "INITCOMMONCONTROLS");

    if (CreateToolbarDynamic && InitCommonControlsDynamic)
    {
      InitCommonControlsDynamic();
      return;
    }

    FreeLibrary(CommCtrlAvail);
  }

  CommCtrlAvail = 0;
  CreateToolbarDynamic = NULL;
  InitCommonControlsDynamic = NULL;
}
#endif

void inline CreateMDIClient(void)
{
  RECT FrmRect;
  CLIENTCREATESTRUCT Clnt;

  // Get Frame's client size so we know how bug to make the client
  GetClientRect(FrameWnd, &FrmRect);

  // Set MDI control menu
  Clnt.hWindowMenu = GetSubMenu(FMenu, 5);
  Clnt.idFirstChild = 800;

  // Create MDI client window
  ClientWnd = CreateWindowEx(
      0,
      _T("MDIClient"),
      NULL,
      WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL,
      CW_USEDEFAULT,
      CW_USEDEFAULT,
      FrmRect.right,
      FrmRect.bottom,
      FrameWnd,
      0,
      hinstCurrent,
      &Clnt);
}

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

  MSG Message;
  HWND otherWnd;

#ifdef SPLASH
  HWND SplashWnd;
#endif

  DWORD dwVersion;

  _TCHAR rlib[MAX_PATH * 2];

#if (defined WIN32) && (!defined _DEBUG)
  LPEXCEPTION_POINTERS Crunch;
#endif

#ifdef _DEBUG
  // A file to shove debug output into if necessary.
  dbg = _tfopen(_T("C:\\TJRC.TXT"), _T("w"));
#endif

  hinstCurrent = hInstance;

  GetRefsVersionInfo();

  otherWnd = FindWindow(FRAMECLASS, NULL);

  if (otherWnd)
  {
    ActivateOtherRefs(otherWnd, lpCmdLine);
    return 0;
  }

#ifdef SPLASH
  SplashWnd = CreateDialog(hinstCurrent, _T("SDLG"), 0, SplashProc);
  Ticks = GetTickCount();
#endif

  if (!hPrevInstance)
  {
    if (!FirstInst())
    {
      // Class initialization failed so
      MessageBox(0, _T("Refs could not initialize its window classes"), TitleName, MB_OK | MB_ICONSTOP);
#ifndef FERIC
      DestroyWindow(SplashWnd);
#endif
      return 1;
    }
  }

#ifdef OLE
  if (FAILED(OleInitialize(NULL)))
    return 1;
#endif

  // Make sure help button works in COMMDLG dialogs
  HlpMsg = RegisterWindowMessage(HELPMSGSTRING);

#ifndef WIN32
  FindINIFile();
#endif

  LoadResourceDLL(rlib);

  GetOpts();

  dwVersion = GetVersion();

#ifdef WIN32
  // Ensure that common control DLL is loaded
  InitCommonControls();
#ifdef USE_RTF
  HINSTANCE hRTFLib = LoadLibrary("RICHED32.DLL");
#endif
#else
#if defined(CC_STATUS) || defined(CC_TOOLBAR)
  DynamicCommonControls();
#endif
#endif

#ifdef WIN32

  if (dwVersion < 0x80000000)
  {
    // Windows NT
    Is95 = (LOBYTE(LOWORD(dwVersion)) >= 4);
  }
  else
  {
    if (LOBYTE(LOWORD(dwVersion)) < 4)
    {
      // Win32s
      MessageBox(0, _T("This version will not run with Win32s.\nUse either Windows NT� or Windows� 95\n\nThere is a 16-bit version available for Windows 3.x"), TitleName, MB_OK | MB_ICONSTOP);
      exit(1);
    }
    else
    {
      // Windows 95
      Is95 = TRUE;
    }
  }
#else
  Is95 = (LOBYTE(LOWORD(dwVersion)) >= 4);
#endif

  if (Is95) // If we're running under Windows 95, Ctl3d is unnecessary.
    IsCtl3D = FALSE;

#ifndef WIN32
  if (IsCtl3D)
  {
    // Register with CTL3D.DLL
    Ctl3dRegister(hInstance);
    Ctl3dAutoSubclass(hInstance);
  }
#endif

  // Create Frame window
  FrameWnd = CreateWindowEx(
      0,
      FRAMECLASS,
      TitleName,
      WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT,
      CW_USEDEFAULT,
      CW_USEDEFAULT,
      CW_USEDEFAULT,
      HWND_DESKTOP, 0,
      hinstCurrent,
      NULL);

  // Load resources, frame window's menu etc
  SetLanguage(rlib);

  // Create MDI client window
  CreateMDIClient();

  // Load command line files
  ActivateOtherRefs(FrameWnd, lpCmdLine);

#ifdef SPLASH
  // Now that windows are created, make sure 4 seconds have elapsed and
  // then blow the splash screen away.
  while ((GetTickCount() - Ticks) < 4000)
  {
  }
  DestroyWindow(SplashWnd);
  ;
#endif

  // Display all windows
  ShowWindow(FrameWnd, nCmdShow);
  UpdateWindow(FrameWnd);

#ifndef CUSTOM
  // Irritate those unregistered freeloaders!
  NagScreen(FrameWnd);
#endif

  // Main message loop
#if (defined WIN32) && (!defined _DEBUG)
  _try
  {
#endif

    while (GetMessage(&Message, 0, 0, 0))
    {
      if ((CurrentEditor == NULL) || (!IsDialogMessage(CurrentEditor, &Message)))
      {
        if (!TranslateMDISysAccel(ClientWnd, &Message))
        {
          if (!TranslateAccelerator(FrameWnd, Accs, &Message))
          {
            TranslateMessage(&Message);
            DispatchMessage(&Message);
          }
        }
      }
    }

#if (defined WIN32) && (!defined _DEBUG)
  }

  _except((Crunch = GetExceptionInformation())->ExceptionRecord->ExceptionCode == EXCEPTION_ACCESS_VIOLATION ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
  {

    MessageBox(0, _T("Whoops!  Refs has caught an unhandled exception.\nIn plain English, that means you have probably found a bug!\n\nPlease note down the details you are about to see."), NULL, MB_ICONSTOP | MB_OK);
    wsprintf(rlib,
             _T("An access violation occurred at the following address: %#.8x\n\nRefs will now show you its 'about' box.\nPlease note down the version numbers you see."),
             (long)Crunch->ExceptionRecord->ExceptionAddress);
    MessageBox(0, rlib, NULL, MB_ICONINFORMATION | MB_OK);
    FrameWnd = 0;
    About();
    MessageBox(0,
               _T("Now send those details to me, either by using the WWW form at:\n\nhttp://chiark.chu.cam.ac.uk:81/refs/bug.html\n\nOr by e-mail to:\n\ntjrc1@mole.bio.cam.ac.uk\n\n Thank you, and my apologies for any data loss."),
               _T("Instructions"), MB_ICONINFORMATION | MB_OK);
    return 0;
  }

#endif

  FreeLibrary(ResInstance);
  ResInstance = 0;

#if defined(CC_TOOLBAR) && !defined(WIN32)
  FreeLibrary(CommCtrlAvail);
#endif

#ifndef WIN32
  // Unhook us from CTL3D.DLL
  if (IsCtl3D)
    Ctl3dUnregister(hInstance);
#endif

#ifdef OLE
  OleUninitialize();
#endif

#ifdef _DEBUG
  fclose(dbg);
#endif

  return (0);
}
