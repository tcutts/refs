#include "inc/globals.h"
#include "inc/rcutpast.h"
#include "inc/refbibs.h"
#include "inc/refchild.h"
#include "inc/reffont.h"
#include "inc/refframe.h"
#include "inc/refio.h"
#include "rimpexp/rimpexp.h"
#include "inc/editdlg.h"

extern HFONT ArrowFnt;
_TCHAR LastDir[MAX_PATH] = _T("");

int FirstInst(void)
{
  WNDCLASS WindowClass =
      {
          0,
          RefFrameProc,
          0,
          0,
          0,
          0,
          0,
          0,
          NULL,
          FRAMECLASS};

  WNDCLASS TRefChild =
      {
          0,
          RefChildProc,
          0,
          sizeof(LPRefWndData),
          0,
          0,
          0,
          0,
          NULL,
          FILECLASS};

  WNDCLASS TRefEdit =
      {
          CS_GLOBALCLASS,
          DefDlgProc,
          0,
          DLGWINDOWEXTRA,
          0,
          0,
          0,
          0,
          NULL,
          EDITCLASS};

  TRefEdit.hInstance = WindowClass.hInstance = TRefChild.hInstance = hinstCurrent;

  WindowClass.hIcon = LoadIcon(hinstCurrent, MAKEINTRESOURCE(1));
  TRefChild.hIcon = LoadIcon(hinstCurrent, MAKEINTRESOURCE(2));
  TRefEdit.hIcon = LoadIcon(hinstCurrent, MAKEINTRESOURCE(1));

  WindowClass.hCursor = TRefChild.hCursor = TRefEdit.hCursor = LoadCursor(0, IDC_ARROW);

  TRefEdit.hbrBackground = WindowClass.hbrBackground = TRefChild.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);

#ifdef WIN32
  if (RegisterClass(&WindowClass) || (GetLastError() == ERROR_CLASS_ALREADY_EXISTS))
  {
    if (RegisterClass(&TRefChild) || (GetLastError() == ERROR_CLASS_ALREADY_EXISTS))
    {
      if (RegisterClass(&TRefEdit) || (GetLastError() == ERROR_CLASS_ALREADY_EXISTS))
      {
        return (TRUE);
      }
    }
  }

#else
  if (RegisterClass(&WindowClass))
  {
    if (RegisterClass(&TRefChild))
    {
      if (RegisterClass(&TRefEdit))
        return (TRUE);
    }
  }
#endif
  return (FALSE);
}

void CreateBitmaps(void)
{
  /*Creates six bitmaps; selected and unselected versions of three
   small bitmp resources, using system default colours*/
  int n;
  HBRUSH Brsh;
  /*the following are working bitmaps to hold the two resource
   bitmaps that are combined into the finished bitmap*/
  HBITMAP BitHnd[2];
  HBITMAP OHndM;
  HBRUSH OHndT;
  HDC DC, MemDC, TempDC;
  COLORREF BkCol;

  if (BmpHnd[0])
  {
    // clear bitmaps if they already exist, say after a wm_SysColorChange
    for (n = 0; n <= 5; n++)
      DeleteBitmap(BmpHnd[n]);
  }
  for (n = 0; n <= 5; n++)
  { // Do it for each bitmap
    switch (n >> 1)
    {
    case 0:
    {
      BitHnd[0] = LoadBitmap(hinstCurrent, _T("ARTMASK"));
      BitHnd[1] = LoadBitmap(hinstCurrent, _T("ARTICLE"));
      break;
    }
    case 1:
    {
      BitHnd[0] = LoadBitmap(hinstCurrent, _T("BOOKMASK"));
      BitHnd[1] = LoadBitmap(hinstCurrent, _T("BOOK"));
      break;
    }
    case 2:
    {
      BitHnd[0] = LoadBitmap(hinstCurrent, _T("REPMASK"));
      BitHnd[1] = LoadBitmap(hinstCurrent, _T("REP"));
      break;
    }
    }
    if ((n & 1) == 0) // Get appropriate colour background
      BkCol = GetSysColor(COLOR_WINDOW);
    else
      BkCol = GetSysColor(COLOR_HIGHLIGHT);
    // and create a brush with it
    Brsh = CreateSolidBrush(BkCol);
    // get a screen DC, and make a compatible memory DC
    DC = GetDC(FrameWnd);
    MemDC = CreateCompatibleDC(DC);
    // Select mask bitmap
    OHndM = (HBITMAP)SelectBitmap(MemDC, BitHnd[0]);
    // Create our new bitmap
    BmpHnd[n] = CreateCompatibleBitmap(MemDC, 30, 15);
    TempDC = CreateCompatibleDC(DC);
    OHndT = (HBRUSH)SelectBrush(TempDC, Brsh);
    // Select bitmap so we're painting onto it
    SelectBitmap(TempDC, BmpHnd[n]);
    // Paint the bitmap with the appropriate background
    PatBlt(TempDC, 0, 0, 30, 15, PATCOPY);
    // Now copy the mask over, turning all non transparent areas black
    BitBlt(TempDC, 0, 0, 30, 15, MemDC, 0, 0, SRCAND);
    // Select the other resource bitmap
    SelectBitmap(MemDC, BitHnd[1]);
    /*combine this with the PatBlt/BitBlt generated before, this time
     with transparent areas of the bitmap black, and colour elsewhere*/
    BitBlt(TempDC, 0, 0, 30, 15, MemDC, 0, 0, SRCPAINT);
    // And now tidy up objects and device contexts.  Order is *very* crucial
    SelectBrush(TempDC, OHndT);
    DeleteBrush(Brsh);
    DeleteDC(TempDC);
    SelectBitmap(MemDC, OHndM);
    DeleteDC(MemDC);
    ReleaseDC(FrameWnd, DC);
    DeleteBitmap(BitHnd[0]);
    DeleteBitmap(BitHnd[1]);
  }
}

void GetOpts(void)
{
  int n;
  _TCHAR t[MAX_FMT_LENGTH], t2[MAX_FMT_LENGTH];

  IsCtl3D = GetConfigInt(DStrDisplay, DStr3D, TRUE);
  MakeBak = GetConfigInt(DStrFiles, DStrBak, TRUE);
  AutoShow = GetConfigInt(DStrFiles, DStrShow, TRUE);
  BibIsFormatted = GetConfigInt(DStrFiles, DStrBIsF, FALSE);
  DefSrchFlag = GetConfigInt(DStrDefCase, DStrDefCase, 1);
  SrchBy = GetConfigInt(DStrDefCase, DStrSrchBy, 3);
  MasterFlags = GetConfigInt(DStrDisplay, DStrList, 242);
  MasterWdth = GetConfigInt(DStrDisplay, DStrClmnWdth, 25);
  DfltSrc = GetConfigInt(DStrInput, DStrDefSrc, 0);
  SrchFlags = GetConfigInt(DStrInput, DStrDefCase, FALSE);
  EditSize.x = GetConfigInt(DStrEditor, _T("x"), 2);
  EditSize.y = GetConfigInt(DStrEditor, _T("y"), 2);
  EditSize.w = GetConfigInt(DStrEditor, _T("w"), 632);
  EditSize.h = GetConfigInt(DStrEditor, _T("h"), 475);
  EditSize.ismax = GetConfigInt(DStrEditor, _T("IsMax"), FALSE);
  MSortName.surname_last = GetConfigInt(DStrNames, DStrSurLast, TRUE);
  MSortName.sort_method = GetConfigInt(DStrNames, DStrNameSrt, 1);

  for (n = 0; n < OLD_FILES; n++)
  {
    _itot(n, t, 10);
    if (n < 3)
      MSortFlags[n] = GetConfigInt(DStrSort, t, MSortFlags[n]);
    if (GetConfigStr(t2, sizeof(t2) / sizeof(_TCHAR), DStrFiles, t, _T("")))
      OldFile[n] = _tcsdup(t2);
    else
      OldFile[n] = NULL;
  }

  GetConfigStr(DfltYr, 20, DStrInput, DStrDefYr, DStr1993);
  GetConfigStr(FmtName, MAX_FMT_LENGTH, DStrBib, DStrFmt, _T(""));
  GetConfigStr(DefModule, 32, DStrFiles, DStrFmt, _T("REFER.FLT"));
  GetConfigStr(MSortName.separator, 20, DStrNames, DStrSurSep, _T(","));
  GetConfigStr(LastDir, sizeof(LastDir), DStrFiles, _T("Dir"), _T(""));

#ifdef WIN32
  BibCol = GetConfigInt(DStrDisplay, DStrBibCol1, 0x00FF0000L);
#else
  BibCol = (GetConfigInt(DStrDisplay, DStrBibCol1, 0x00FF) << 16) +
           GetConfigInt(DStrDisplay, DStrBibCol2, 0);
#endif

  if (FmtName[0] == _T('\0'))
  {
    GetConfigStr(t, sizeof(t), DStrFmts, NULL, _T(""));
    if (t[0] == _T('\0'))
    {
      lstrcpy(FmtString, _T("<A@ ><D(@)><J, @><V @><P @>"));
      lstrcpy(FmtName, _T("Basic"));
    }
    else
    {
      lstrcpy(FmtName, t);
      GetConfigStr(t2, sizeof(t2), DStrFmts, t, _T(""));
    }
  }
  else
    GetConfigStr(t2, sizeof(t2), DStrFmts, FmtName, _T(""));
  if (t2[0] != _T('\0'))
    DecodeBibFmt(t2);
}

void HereWeGo(void)
{

#ifndef WIN32
  HDC DC;

  DFont = (HFONT)GetStockObject(SYSTEM_FONT);
  DC = GetDC(FrameWnd);
  SelectFont(DC, DFont);
  GetTextMetrics(DC, &TM);
  StatusHeight = TM.tmHeight;
  ReleaseDC(FrameWnd, DC);
#endif

  Accs = LoadAccelerators(hinstCurrent, _T("KEYS"));
  SCursor = LoadCursor(hinstCurrent, _T("SINGLE"));
  MCursor = LoadCursor(hinstCurrent, _T("MULTIPLE"));
  CCursor = LoadCursor(0, IDC_ARROW);

  // Get language-specific strings
  LoadString(ResInstance, str_AndWord, AndWord, sizeof(AndWord) / sizeof(_TCHAR));
  LoadString(ResInstance, str_Untitled, Untitled, sizeof(Untitled) / sizeof(_TCHAR));

  // Get other fonts
  ListFnt = new TRefFont(FALSE, DStrFonts, DStrList);
  ListFnt->SetListParms(FrameWnd);
  PrnFnt = new TRefFont(TRUE, DStrFonts, DStrPrint);
  EditFnt = new TRefFont(FALSE, DStrFonts, DStrEditor);

  ArrowFnt = CreateFont(
      -19, 0, 0, 0,
      0x190, 0, 0, 0,
      1, 0,
      0, 0,
      0,
      _T("Wingdings"));

  Clients = 0;
  ActiveFile = NULL;

  BmpHnd[0] = 0;
  CreateBitmaps();
}

void BuggerOff(void)
{
  int n;
  _TCHAR t2[RES_STR];

  DeleteConfigTree(DStrFiles);

  for (n = 0; n < OLD_FILES; n++)
  {
    _itot(n, t2, 10);
    if (n < 3)
    {
      SetConfigInt(DStrSort, t2, MSortFlags[n]);
    }
    if (OldFile[n])
    {
      SetConfigStr(DStrFiles, t2, OldFile[n]);
      free(OldFile[n]);
    }
  }

#ifdef WIN32
  SetConfigInt(DStrDisplay, DStrBibCol1, BibCol);
#else
  SetConfigInt(DStrDisplay, DStrBibCol1, HIWORD(BibCol));
  SetConfigInt(DStrDisplay, DStrBibCol2, LOWORD(BibCol));
#endif
  SetConfigInt(DStrFiles, DStrBak, MakeBak);
  SetConfigInt(DStrFiles, DStrShow, AutoShow);
  SetConfigInt(DStrFiles, DStrBIsF, BibIsFormatted);
  SetConfigInt(DStrDefCase, DStrDefCase, DefSrchFlag);
  SetConfigInt(DStrDefCase, DStrSrchBy, SrchBy);
  SetConfigInt(DStrDisplay, DStrList, MasterFlags);
  SetConfigInt(DStrDisplay, DStrClmnWdth, MasterWdth);
  SetConfigInt(DStrInput, DStrDefSrc, DfltSrc);
  SetConfigInt(DStrInput, DStrDefCase, SrchFlags);
  SetConfigInt(DStrEditor, _T("x"), EditSize.x);
  SetConfigInt(DStrEditor, _T("y"), EditSize.y);
  SetConfigInt(DStrEditor, _T("w"), EditSize.w);
  SetConfigInt(DStrEditor, _T("h"), EditSize.h);
  SetConfigInt(DStrEditor, _T("IsMax"), EditSize.ismax);
  SetConfigInt(DStrNames, DStrSurLast, MSortName.surname_last);
  SetConfigInt(DStrNames, DStrNameSrt, MSortName.sort_method);

  SetConfigStr(DStrInput, DStrDefYr, DfltYr);
  SetConfigStr(DStrFiles, DStrFmt, DefModule);
  SetConfigStr(DStrFiles, _T("Dir"), LastDir);

  if (FmtName[0] != _T('\0'))
    SetConfigStr(DStrBib, DStrFmt, FmtName);

  SetConfigStr(DStrNames, DStrSurSep, MSortName.separator);

  if (CutPasteColl)
    delete CutPasteColl;

  if (PrnFnt)
    delete PrnFnt;
  if (EditFnt)
    delete EditFnt;

  if (ArrowFnt)
    DeleteFont(ArrowFnt);

  DestroyMenu(FMenu);

  // Free bitmap handles
  for (n = 0; n <= 5; n++)
    DeleteBitmap(BmpHnd[n]);

  // Kill the help window if there is one
  WinHelp(FrameWnd, HelpName, HELP_QUIT, 0);

  PostQuitMessage(0); // Tell Windows we can now quit
}
