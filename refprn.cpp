#include "inc/globals.h"
#include <malloc.h>

#ifdef WIN32
#include <wingdi.h>
#else
#include <print.h>
#endif

#include "inc/rcutpast.h"
#include "inc/reffont.h"
#include "inc/refprn.h"

#ifdef USE_RTF
#include "inc/redit.h"
#endif

#ifdef WIN32
#define PRN_SZ 0x7FFF - MAX_FMT_LENGTH
#else
#define PRN_SZ 0x7FFFL - MAX_FMT_LENGTH
#endif

#ifdef FERIC
#define TOPTEXT _T("FERIC")
#undef WATERMARK
#else
#define TOPTEXT _T("Unregistered")
//  #ifdef WIN32
//    #undef WATERMARK
//  #else
//    #define WATERMARK
//  #endif
#endif

const int LeftMargin = 20;  /*mm*/
const int RightMargin = 15; /*mm*/
const _TCHAR wsp[] = _T(" \t\n");
_TCHAR *PrnData;
int LineSpace, LinesPerPage, LineLength;
long PageWidth, PhysWidth, CurrentLine;
int fAbort;
int IOStatus, CurPage;
int LeftSide, RightSide;
HWND PrnFromWnd, AbortDlgWnd;
HFONT PFont, OFnt;
#ifdef WATERMARK
HFONT UFont;
#endif
UINT OBMode;
HDC hdcPrinter;
PRINTDLG NEAR pd;
DOCINFO NEAR DocInfo;
TEXTMETRIC NEAR ptm;
LOGFONT NEAR Fnt;

#ifdef USE_RTF
FORMATRANGE fr;
#endif

void inline Abort_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
  if (id == IDCANCEL)
    fAbort = TRUE;
}

BOOL inline Abort_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
  SetDlgItemText(hwnd, idc_Filename, (_TCHAR *)lParam);
  fAbort = FALSE;
  return FALSE;
}

BOOL CALLBACK AbortDlg(HWND Dlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  switch (Msg)
  {
    HANDLE_MSG(Dlg, WM_COMMAND, Abort_OnCommand);
    HANDLE_MSG(Dlg, WM_INITDIALOG, Abort_OnInitDialog);
  }
  return (FALSE);
}

BOOL CALLBACK AbortProc(HDC prndc, int code)
{
  Pause(AbortDlgWnd, fAbort);
  return (!fAbort);
}

HDC GetPrinterDC(HWND FromWnd, int AllowSel)
{
  _TCHAR *DriverName, *DeviceName, *PortName;
  HDC DC;
  DEVMODE *DevMode;
  DEVNAMES *DevNames;

  PrnFromWnd = FromWnd;
  DevMode = NULL;
  pd.lStructSize = sizeof(PRINTDLG);
  pd.hwndOwner = PrnFromWnd;
  pd.hDevMode = pd.hDevNames = 0;
  pd.Flags = PD_ALLPAGES | PD_RETURNDC | PD_NOPAGENUMS | PD_SHOWHELP;
  if (!AllowSel)
    pd.Flags |= PD_NOSELECTION;
  if (!PrintDlg(&pd))
    return (0);
  if (pd.hDC)
    DC = pd.hDC;
  else
  {
    if (!pd.hDevNames)
      return (0);
    DevNames = (LPDEVNAMES)GlobalLock(pd.hDevNames);
    DriverName = (_TCHAR *)DevNames + DevNames->wDriverOffset;
    DeviceName = (_TCHAR *)DevNames + DevNames->wDeviceOffset;
    PortName = (_TCHAR *)DevNames + DevNames->wOutputOffset;
    GlobalUnlock(pd.hDevNames);
    if (pd.hDevMode)
      DevMode = (LPDEVMODE)GlobalLock(pd.hDevMode);
    DC = CreateDC(DriverName, DeviceName, PortName, DevMode);
    if (pd.hDevMode && DevMode)
      GlobalUnlock(pd.hDevMode);
  }
  if (pd.hDevNames)
    GlobalFree(pd.hDevNames);
  if (pd.hDevMode)
    GlobalFree(pd.hDevMode);
  return (DC);
}

int PrnSetup(LPTSTR Name)
{
  int N;
  HDC SDC;

  SetAbortProc(hdcPrinter, AbortProc);

  DocInfo.cbSize = sizeof(DOCINFO);
  DocInfo.lpszDocName = _tcsdup(Name);
  DocInfo.lpszOutput = NULL;

  if (PrnFnt)
  {
    if (PrnFnt->SFont == GetStockObject(SYSTEM_FONT))
      PFont = PrnFnt->SFont;
    else
    {
      Fnt = *(PrnFnt->AFnt);
      SDC = GetDC(FrameWnd);
      Fnt.lfHeight = Fnt.lfHeight * (GetDeviceCaps(hdcPrinter, LOGPIXELSY) / GetDeviceCaps(SDC, LOGPIXELSY));
      PFont = CreateFontIndirect(&Fnt);
      ReleaseDC(FrameWnd, SDC);
    }
  }

  OFnt = SelectFont(hdcPrinter, PFont);

  GetTextMetrics(hdcPrinter, &ptm);

  LineSpace = ptm.tmHeight + ptm.tmExternalLeading;
  LinesPerPage = (GetDeviceCaps(hdcPrinter, VERTRES) / LineSpace) - 1;

  PageWidth = GetDeviceCaps(hdcPrinter, HORZRES);  // pixels
  PhysWidth = GetDeviceCaps(hdcPrinter, HORZSIZE); // mm

  LeftSide = LeftMargin * (PageWidth / PhysWidth);
  RightSide = RightMargin * (PageWidth / PhysWidth);

  PageWidth = PageWidth - (LeftSide + RightSide);

#ifdef USE_RTF
  // Now do same for RichEdit stuff.
  fr.hdc = fr.hdcTarget = hdcPrinter;
  fr.chrg.cpMin = 0;
  fr.chrg.cpMax = -1;
  fr.rcPage.top = fr.rcPage.left = 0;
  fr.rc.right = fr.rcPage.right = PhysWidth * 567 / 10;
  fr.rc.bottom = fr.rcPage.bottom = GetDeviceCaps(hdcPrinter, VERTSIZE) * 567 / 10;
  fr.rc.top = 1440;
  fr.rc.right -= 1000;
  fr.rc.bottom -= 1440;
#endif

  if ((N = StartDoc(hdcPrinter, &DocInfo)) < 0)
  {
    ErrorBox(PrnFromWnd, err_NoPrnStart);
    SelectFont(hdcPrinter, OFnt);
  }
  else
  {
    CurPage = 1;
    fAbort = FALSE;
    AbortDlgWnd = CreateDialogParam(ResInstance, _T("ABORT"), PrnFromWnd, AbortDlg, (long)Name);
    ShowWindow(AbortDlgWnd, SW_NORMAL);
    UpdateWindow(AbortDlgWnd);
    EnableWindow(PrnFromWnd, FALSE);
    CurrentLine = 3;
    IOStatus = 0;
#ifdef WATERMARK
    if (!Registered)
    {
      // Set Transparent background
      OBMode = SetBkMode(hdcPrinter, TRANSPARENT);

      // Create font for watermark
      Fnt.lfHeight = 360;
      Fnt.lfWidth = 0;
      Fnt.lfEscapement = Fnt.lfOrientation = 0;
      Fnt.lfWeight = 700;
      Fnt.lfItalic = FALSE;
      Fnt.lfUnderline = FALSE;
      Fnt.lfStrikeOut = FALSE;
      Fnt.lfCharSet = ANSI_CHARSET;
      Fnt.lfOutPrecision = OUT_DEFAULT_PRECIS;
      Fnt.lfClipPrecision = CLIP_DEFAULT_PRECIS;
      Fnt.lfQuality = DEFAULT_QUALITY;
      Fnt.lfPitchAndFamily = VARIABLE_PITCH | FF_ROMAN;
      lstrcpy(Fnt.lfFaceName, _T("Times New Roman"));

      UFont = CreateFontIndirect(&Fnt);
    }
#endif
  }
  free((_TCHAR *)DocInfo.lpszDocName);
  return (N);
}

#ifdef WATERMARK
void PrintWatermark(int px, int py, LPTSTR text)
{

  int IsColour, len;
  int x, y;
  SIZE sz;
  HBRUSH OBrsh, Brsh;
  HBITMAP Wmk;
  UINT OColour;
  HFONT RFont;
  const BYTE dither[8] = {0x77, 0xFF, 0xDD, 0xFF, 0x77, 0xFF, 0xDD, 0xFF};

  IsColour = GetDeviceCaps(hdcPrinter, BITSPIXEL) > 1;
  RFont = SelectFont(hdcPrinter, UFont);
  OColour = SetTextColor(hdcPrinter, IsColour ? 0x00CFCFCF : 0x00000000);

  len = lstrlen(text);

  GetTextExtentPoint(
      hdcPrinter,
      TOPTEXT,
      len,
      &sz);

  x = px - sz.cx / 2;
  y = py - sz.cy / 2;

  TextOut(hdcPrinter, x, y, text, len);

  if (!IsColour)
  {
    // Do some nasty dithering

    // Load the dither pattern bitmap
    Wmk = CreateBitmap(8, 8, 1, 1, dither);

    // Create a pattern brush with it
    Brsh = CreatePatternBrush(Wmk);

    OBrsh = SelectBrush(hdcPrinter, Brsh);
    PatBlt(hdcPrinter, x, y, sz.cx, sz.cy, 0x00FA0089); // PDo

    // Tidy up
    SelectBrush(hdcPrinter, OBrsh);
    DeleteBrush(Brsh);
    DeleteBitmap(Wmk);
  } // BITSPIXEL==1

  SetTextColor(hdcPrinter, OColour);
  SelectFont(hdcPrinter, RFont);
}
#endif

void HeadFoot(LPTSTR Name)
{
  _TCHAR t[MAX_PATH + 40], t1[MAX_PATH + 40];
  UINT OTAlign;

#ifdef WATERMARK
  if (!Registered)
  {
    PrintWatermark(LeftSide + PageWidth / 2, LinesPerPage * LineSpace / 4, TOPTEXT);
    PrintWatermark(LeftSide + PageWidth / 2, LinesPerPage * 3 * LineSpace / 4, TitleName);
  }
#endif

  if (PrnFnt)
  {
    SelectFont(hdcPrinter, OFnt);
    OFnt = SelectFont(hdcPrinter, PFont);
  }

  LoadString(ResInstance, fmt_Page, t, MAX_PATH + 39);
  wsprintf(t1, t, CurPage);

#if !defined(WATERMARK) && !defined(FERIC)
  if (!Registered)
    lstrcat(t1, _T(" - Please Register!"));
#endif

  OTAlign = SetTextAlign(hdcPrinter, TA_CENTER | TA_TOP | TA_NOUPDATECP);

  TextOut(hdcPrinter, LeftSide + PageWidth / 2, LinesPerPage * LineSpace, t1, lstrlen(t1));
  TextOut(hdcPrinter, LeftSide + PageWidth / 2, LineSpace, Name, lstrlen(Name));

  SetTextAlign(hdcPrinter, OTAlign);

  lstrcat(t1, Name);
  SetDlgItemText(AbortDlgWnd, idc_Filename, t1);
}

void DocEnd(void)
{
  EndDoc(hdcPrinter);
  if (OFnt)
    SelectFont(hdcPrinter, OFnt);
  if (PFont != GetStockObject(SYSTEM_FONT))
    DeleteFont(PFont);

#ifdef WATERMARK
  if (!Registered)
  {
    SetBkMode(hdcPrinter, OBMode);
    DeleteFont(UFont);
    UFont = 0;
  }
#endif

  PFont = 0;
  EnableWindow(PrnFromWnd, TRUE);
  DestroyWindow(AbortDlgWnd);
}

void inline PrnDone(void)
{
  DeleteDC(hdcPrinter);
}

#ifndef USE_RTF

int FindWordEnd(LPTSTR Start, int WS)
{
  int WE;

  WE = WS;
  while ((Start[WE] != _T('\0')) && (!_tcschr(wsp, Start[WE])))
  {
    if (Start[WE] == _T('\r'))
      Start[WE] = ' ';
    WE++;
  }
  return (WE);
}

LPTSTR FindLineEnd(LPTSTR Start)
{

  int LE, NLE; // counts in TCHAR
  SIZE sz;

  // add words until the line is too long,  go to the previous end

  LE = -1;
  do
  {
    LE++;
    NLE = FindWordEnd(Start, LE);
    GetTextExtentPoint(hdcPrinter, Start, NLE + 1, &sz);
    if (sz.cx < PageWidth)
      LE = NLE;
  } while ((Start[NLE] != _T('\0')) && (Start[NLE] != _T('\n')) && (LE == NLE));
  switch (Start[LE])
  {
  case _T('\0'):
    return (NULL);
  case _T('\n'):
    return (&Start[LE]);
  default:
    return (&Start[LE - 1]);
  }
}

void PrintLine(LPTSTR Text, LPTSTR Name, int LineLength)
{
  if (CurrentLine == 3)
    HeadFoot(Name);
  TextOut(hdcPrinter, LeftSide, CurrentLine * LineSpace, Text, LineLength);
  CurrentLine++;
  if (CurrentLine > (LinesPerPage - 2))
  {
    IOStatus = EndPage(hdcPrinter);
    CurPage++;
    CurrentLine = 3;
    if ((IOStatus >= 0) && (!fAbort))
      IOStatus = StartPage(hdcPrinter);
  }
}

void PrintText(HWND FromWnd, _TCHAR *Text, _TCHAR *Name)
{
  _TCHAR *LB, *LE;

  hdcPrinter = GetPrinterDC(FromWnd, FALSE);
  if (!hdcPrinter)
    return;
  if (PrnSetup(Name) > 0)
  {
    IOStatus = StartPage(hdcPrinter);
    LB = Text;
    LE = LB;
    while ((IOStatus >= 0) && LE)
    {
      LE = FindLineEnd(LB);
      if (LE)
      {
        PrintLine(LB, Name, LE - LB);
        LB = LE + 1;
      }
    }
    if ((IOStatus >= 0) && (!fAbort))
      EndPage(hdcPrinter);
    DocEnd();
  }
  PrnDone();
}

void PrintColl(HWND FromWnd, LPSrchColl AColl)
{

  long FailedOn;
  LPTSTR Name;
  LPSrchColl PrnColl;
  int PrnSel;
  _TCHAR *LB, *LE, t[MAX_PATH + 20];
  int NmSz;

  PrnData = (LPTSTR)malloc(PRN_SZ + MAX_FMT_LENGTH);

  if (PrnData)
  {
    if (BibData && (BibData->Refs == AColl) && (BibIsFormatted))
      PrnSel = FALSE;
    else
      PrnSel = ((AColl != CutPasteColl) && (ListBox_GetSelCount(AColl->RefWnd->ListWnd) > 0));

    hdcPrinter = GetPrinterDC(FromWnd, PrnSel);

    if (!hdcPrinter)
      return;

    NmSz = GetWindowText(AColl->RefWnd->Window, t, MAX_PATH - 1) + lstrlen(TitleName) + 5;
    Name = (LPTSTR)malloc(NmSz);

    wsprintf(Name, _T("%s - %s"), TitleName, t);

    if (PrnSetup(Name) > 0)
    {
      if ((PrnSel = ((pd.Flags & PD_SELECTION) != 0)) != 0)
      {
        CopyThem(AColl->RefWnd);
        PrnColl = CutPasteColl;
      }
      else
        PrnColl = AColl;

      IOStatus = StartPage(hdcPrinter);
      FailedOn = PrnColl->FillBibWnd(0, PrnData);

      while ((!fAbort) && (IOStatus >= 0) && (FailedOn != -1))
      {
        LB = LE = PrnData;

        if (FailedOn == PrnColl->count)
        {
          lstrcat(PrnData, FmtSuffix);
          lstrcat(PrnData, _T("\n"));
        }

        while ((!fAbort) && (IOStatus >= 0) && LE)
        {
          LE = FindLineEnd(LB);
          if (LE)
            PrintLine(LB, Name, LE - LB);
          LB = LE + 1;
        }

        if ((FailedOn >= 0) && (FailedOn < PrnColl->count))
          FailedOn = PrnColl->FillBibWnd(FailedOn, PrnData);
        else
          FailedOn = -1;
      }

      if ((IOStatus >= 0) && (!fAbort))
        EndPage(hdcPrinter);

      DocEnd();

      if (PrnSel)
      {
        delete CutPasteColl;
        CutPasteColl = NULL;
      }
    }

    free(Name);
    PrnDone();
    free(PrnData);
  }
  else
    ErrorBox(PrnFromWnd, err_PrnMem);
}

#else

void PrintText(HWND FromWnd, _TCHAR *Text, _TCHAR *Name)
{
  _TCHAR *p;

  hdcPrinter = GetPrinterDC(FromWnd, FALSE);
  if (!hdcPrinter)
    return;
  if (PrnSetup(Name) > 0)
  {

    hRichEdit pw = new TRichEdit(
        WS_CHILD | ES_LEFT | ES_MULTILINE,
        0, 0,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        FrameWnd,
        (HMENU)100);

    int lTextOut = 0;
    int lTextAmt;

    StartPage(hdcPrinter);
    HeadFoot(Name);

    p = _tcsstr(Text, _T("\\rtf"));

    pw->SetFaceName(PrnFnt->AFnt, 0);
    pw->SetPointSize(PrnFnt->AFnt, 0);
    pw->SetData(Text, (p == NULL) ? SF_TEXT : SF_RTF);

    lTextAmt = SendMessage(pw->hWnd, WM_GETTEXTLENGTH, 0, 0);

    while (lTextOut < lTextAmt)
    {
      lTextOut = SendMessage(
          pw->hWnd,
          EM_FORMATRANGE,
          TRUE,
          (LPARAM)&fr);

      if (lTextOut < lTextAmt)
      {
        EndPage(hdcPrinter);
        StartPage(hdcPrinter);
        CurPage++;
        HeadFoot(Name);
        fr.chrg.cpMin = lTextOut;
        fr.chrg.cpMax = -1;
      }
    }

    EndPage(hdcPrinter);
    DocEnd();
  }
  PrnDone();
}

void PrintColl(HWND FromWnd, LPSrchColl AColl)
{

  long FailedOn;
  LPTSTR Name;
  LPSrchColl PrnColl;
  int PrnSel;
  _TCHAR t[MAX_PATH + 20];
  int NmSz;

  //  PrnData = (LPTSTR)malloc(PRN_SZ + MAX_FMT_LENGTH);
  PrnData = (LPTSTR)malloc(MAX_EDIT_CONTENTS);

  if (PrnData)
  {
    if (BibData && (BibData->Refs == AColl) && (BibIsFormatted))
      PrnSel = FALSE;
    else
      PrnSel = ((AColl != CutPasteColl) && (ListBox_GetSelCount(AColl->RefWnd->ListWnd) > 0));

    hdcPrinter = GetPrinterDC(FromWnd, PrnSel);

    if (!hdcPrinter)
      return;

    NmSz = GetWindowText(AColl->RefWnd->Window, t, MAX_PATH - 1) + lstrlen(TitleName) + 5;
    Name = (LPTSTR)malloc(NmSz);

    wsprintf(Name, _T("%s - %s"), TitleName, t);

    if (PrnSetup(Name) > 0)
    {
      if ((PrnSel = ((pd.Flags & PD_SELECTION) != 0)) != 0)
      {
        CopyThem(AColl->RefWnd);
        PrnColl = CutPasteColl;
      }
      else
        PrnColl = AColl;

      hRichEdit pw = new TRichEdit(
          WS_CHILD | ES_LEFT | ES_MULTILINE,
          0, 0,
          CW_USEDEFAULT,
          CW_USEDEFAULT,
          FrameWnd,
          (HMENU)100);

      int lTextOut = 0;
      int lTextAmt;

      IOStatus = StartPage(hdcPrinter);
      //      FailedOn = FillText(PrnColl, 0);
      FailedOn = PrnColl->FillBibWnd(0, PrnData);
      HeadFoot(Name);

      while ((!fAbort) && (IOStatus >= 0) && (FailedOn != -1))
      {
        pw->SetFaceName(PrnFnt->AFnt, 0);
        pw->SetPointSize(PrnFnt->AFnt, 0);
        pw->SetData(PrnData, SF_RTF);

        lTextAmt = SendMessage(pw->hWnd, WM_GETTEXTLENGTH, 0, 0);

        while (lTextOut < lTextAmt)
        {
          lTextOut = SendMessage(
              pw->hWnd,
              EM_FORMATRANGE,
              TRUE,
              (LPARAM)&fr);

          if (lTextOut < lTextAmt)
          {
            EndPage(hdcPrinter);
            StartPage(hdcPrinter);
            CurPage++;
            HeadFoot(Name);
            fr.chrg.cpMin = lTextOut;
            fr.chrg.cpMax = -1;
          }
        }

        if ((FailedOn >= 0) && (FailedOn < PrnColl->count))
        {
          //          FailedOn = FillText(PrnColl, FailedOn);
          EndPage(hdcPrinter);
          StartPage(hdcPrinter);
          CurPage++;
          HeadFoot(Name);
          FailedOn = PrnColl->FillBibWnd(FailedOn, PrnData);
          lTextOut = 0;
        }
        else
          FailedOn = -1;
      }

      if ((IOStatus >= 0) && (!fAbort))
        EndPage(hdcPrinter);

      DocEnd();

      if (PrnSel)
      {
        delete CutPasteColl;
        CutPasteColl = NULL;
      }

      delete pw;
    }

    free(Name);
    PrnDone();
    free(PrnData);
  }
  else
    ErrorBox(PrnFromWnd, err_PrnMem);
}

#endif // USE_RTF
