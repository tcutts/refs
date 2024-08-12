#include "inc/globals.h"
#include "inc/reffont.h"
#include "rimpexp/rimpexp.h"

TRefFont::TRefFont(int Print)
{
  Init(Print);
}

void TRefFont::Init(int Print)
{
  LPBYTE p;
  int n;

  Printer = Print;
  SFont = 0;

  AFnt = new LOGFONT;
  *(AFnt->lfFaceName) = _T('\0');
  AFnt->lfHeight = AFnt->lfWidth = 0;
  AFnt->lfEscapement = AFnt->lfItalic = 0;
  AFnt->lfWeight = FW_DONTCARE;
  AFnt->lfUnderline = AFnt->lfStrikeOut = 0;
  AFnt->lfCharSet = DEFAULT_CHARSET;
  AFnt->lfOutPrecision = OUT_DEFAULT_PRECIS;
  AFnt->lfClipPrecision = CLIP_DEFAULT_PRECIS;
  AFnt->lfQuality = DEFAULT_QUALITY;
  AFnt->lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;

  for (n = 0, p = (LPBYTE)&ChFnt; n < sizeof(CHOOSEFONT); n++)
    p[n] = 0;
}

TRefFont::~TRefFont(void)
{
  if (SFont)
    DeleteFont(SFont);
  if (AFnt)
    free(AFnt);
}

TRefFont::TRefFont(int Print, LPLOGFONT Desc)
{
  Init(Print);
  *AFnt = *Desc;
  if (!Create())
  {
    free(AFnt);
    AFnt = NULL;
  }
}

void TRefFont::PutToIni(_TCHAR *Section, _TCHAR *Key)
{
  int IU;
  _TCHAR T[82];

  IU = (AFnt->lfItalic << 8) + AFnt->lfUnderline;
  wsprintf(T, _T("%s,%d,%d,%d"), AFnt->lfFaceName, AFnt->lfHeight, AFnt->lfWeight, IU);
  SetConfigStr(Section, Key, T);
}

TRefFont::TRefFont(int Print, _TCHAR *Section, _TCHAR *Key)
{
  int n;
  _TCHAR t[82];

  Init(Print);
  GetConfigStr(t, sizeof(t) / sizeof(_TCHAR), Section, Key, _T(""));
  if (*t != _T('\0'))
  {
    _stscanf(t, _T("%[^,],%d,%d,%d"), &AFnt->lfFaceName, &AFnt->lfHeight, &AFnt->lfWeight, &n);
    AFnt->lfUnderline = n & 0x00FF;
    AFnt->lfItalic = n >> 8;
    if (!Create())
    {
      SFont = (HFONT)GetStockObject(SYSTEM_FONT);
      free(AFnt);
      AFnt = NULL;
    }
  }
  else
  {
    SFont = (HFONT)GetStockObject(SYSTEM_FONT);
    free(AFnt);
    AFnt = NULL;
  }
}

int TRefFont::Create(void)
{
  HFONT T;

  if ((T = CreateFontIndirect(AFnt)) != 0)
  {
    if (SFont)
      DeleteFont(SFont);
    SFont = T;
    return (TRUE);
  }
  return (FALSE);
}

int TRefFont::CommDlg(int InitDlg, HWND Wnd)
{
  _TCHAR *lpTemp, *lpPrintDevice, *lpPrintDriver, *lpPrintPort;
  int n;
  HDC pdc;
  _TCHAR T[82];

  if (Printer)
  {
    GetProfileString(_T("windows"), _T("device"), _T(""), T, 82);
    lpTemp = T;
    lpPrintDevice = lpTemp;
    lpPrintDriver = lpPrintPort = NULL;
    while (*lpTemp != _T('\0'))
    {
      if (*lpTemp == _T(','))
      {
        *lpTemp = _T('\0');
        lpTemp++;
        if (!lpPrintDriver)
          lpPrintDriver = lpTemp;
        else
          lpPrintPort = lpTemp;
      }
      else
        lpTemp++;
    }
    pdc = CreateDC(lpPrintDriver, lpPrintDevice, lpPrintPort, NULL);
  }
  else
    pdc = GetDC(Wnd);

  ChFnt.lStructSize = sizeof(CHOOSEFONT);
  ChFnt.hDC = pdc;
  ChFnt.Flags = Printer ? (CF_WYSIWYG | CF_BOTH) : CF_BOTH;
  if (InitDlg)
    ChFnt.Flags |= CF_INITTOLOGFONTSTRUCT;
  ChFnt.lpLogFont = AFnt;

  n = ChooseFont(&ChFnt);
  Printer ? DeleteDC(pdc) : ReleaseDC(Wnd, pdc);
  return (n);
}

TRefFont::TRefFont(int Print, HWND Wnd)
{
  Init(Print);
  if ((!CommDlg(Printer, Wnd)) || (!Create()))
  {
    free(AFnt);
    AFnt = NULL;
  }
}

int TRefFont::Edit(HWND Wnd)
{
  int T;

  if (!AFnt)
  {
    AFnt = new LOGFONT;
    T = CommDlg(FALSE, Wnd);
  }
  else
    T = CommDlg(TRUE, Wnd);
  if (T)
    T = Create();
  return (T);
}

void TRefFont::SetListParms(HWND Wnd)
{
  HDC pdc;
  HFONT O;
  SIZE sz;

  pdc = GetDC(Wnd);
  O = SelectFont(pdc, SFont);
  GetTextMetrics(pdc, &TM);
  ListHeight = TM.tmHeight + TM.tmExternalLeading + 1;
  CharWidth = TM.tmAveCharWidth;
  GetTextExtentPoint(pdc, _T("(2999)"), 6, &sz);
  DateWidth = sz.cx + 2;
  SelectFont(pdc, O);
  ReleaseDC(Wnd, pdc);
}
