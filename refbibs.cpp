#include "inc/globals.h"
#include "inc/refbibs.h"
#include "inc/reffont.h"
#include "rimpexp/rimpexp.h"

#ifdef USE_RTF
#include "inc/redit.h"
hRichEdit RichSample;
#endif

_TCHAR BibTempFmt[MAX_FMT_LENGTH];

void DoBibColDlg(void)
{
  COLORREF CustCols[] = {0xFFFFFFL, 0xFFFFFFL, 0xFFFFFFL, 0xFFFFFFL,
                         0xFFFFFFL, 0xFFFFFFL, 0xFFFFFFL, 0xFFFFFFL,
                         0xFFFFFFL, 0xFFFFFFL, 0xFFFFFFL, 0xFFFFFFL,
                         0xFFFFFFL, 0xFFFFFFL, 0xFFFFFFL, 0xFFFFFFL};
  CHOOSECOLOR CC;
  HWND cWnd;
  RECT Rect;

  CC.lStructSize = sizeof(CHOOSECOLOR);
  CC.hwndOwner = FrameWnd;
  CC.rgbResult = BibCol;
  CC.lpCustColors = CustCols;
  CC.Flags = CC_RGBINIT;
  if (ChooseColor(&CC))
  {

    BibCol = CC.rgbResult;

    if (ActiveFile)
    {

      for (cWnd = ActiveFile->Window;
           cWnd != NULL;
           cWnd = GetNextWindow(cWnd, GW_HWNDNEXT))
      {

        GetWindowRect(cWnd, &Rect);
        InvalidateRect(cWnd, &Rect, TRUE);
      }
    }
  }
}

void DecodeBibFmt(LPTSTR Fmt)
{

  _TCHAR *Ptr, ToAdd[2];

  Ptr = Fmt;
  FmtPrefix[0] = _T('\0');
  FmtSuffix[0] = _T('\0');
  ToAdd[1] = _T('\0');

  if (Ptr[0] == '[')
  {
    Ptr++;
    while ((Ptr[0] != ']') && (Ptr[0] != _T('\0')))
    {
      if (Ptr[0] == '\\')
        Ptr = Special(FmtPrefix, Ptr);
      else
      {
        ToAdd[0] = Ptr[0];
        lstrcat(FmtPrefix, ToAdd);
      }
      Ptr++;
    }
    Ptr++;
  }
  else
    FmtPrefix[0] = _T('\0');

  if (Ptr[0] == '[')
  {
    Ptr++;
    while ((Ptr[0] != ']') && (Ptr[0] != _T('\0')))
    {
      if (Ptr[0] == '\\')
        Ptr = Special(FmtSuffix, Ptr);
      else
      {
        ToAdd[0] = Ptr[0];
        lstrcat(FmtSuffix, ToAdd);
      }
      Ptr++;
    }
    Ptr++;
  }
  else
    FmtSuffix[0] = _T('\0');

  lstrcpy(FmtString, Ptr);
}

void UpdateSample(HWND TheDlg)
{

  LPRef Xmpl;
  LPTSTR t, t2;
  HWND cb;

  cb = GetDlgItem(TheDlg, id_FmtList);
  ListBox_GetText(cb, ListBox_GetCurSel(cb), FmtName);
  // This is really horrid - no checking for out of memory.
  // It's forgiveable for the new, since C++ doesn't have a fail concept (spit!)
  // But I really should check the mallocs.
  t = (LPTSTR)malloc(SCRATCH_SIZE);
  t2 = (LPTSTR)malloc(SCRATCH_SIZE);
  Xmpl = new TRef;
  Xmpl->authors = _tcsdup(_T("Bloggs, F\r\nSmith, J\r\nOther, AN"));
  Xmpl->title = _tcsdup(_T("An exciting paper"));
  Xmpl->date = _tcsdup(DStr1993);
  Xmpl->vol = _tcsdup(_T("000"));
  Xmpl->volno = _tcsdup(_T("0"));
  Xmpl->pages = _tcsdup(_T("0000-0000"));
  Xmpl->journal = _tcsdup(_T("The Journal"));
  Xmpl->publisher = _tcsdup(_T("Smith and Brown"));
  Xmpl->city = _tcsdup(_T("London"));
  Xmpl->editor = _tcsdup(_T("Brown, P"));
  Xmpl->keywords = _tcsdup(_T("Widgets\r\nDoofers"));
  Xmpl->text = _tcsdup(_T("This is a very good piece of work.\r\n\r\nBloggs et al have shown that widgets are in fact doofers!"));
  GetConfigStr(t, MAX_FMT_LENGTH, DStrFmts, FmtName, _T(""));
  DecodeBibFmt(t);
  Xmpl->FormatRef(t2);
  _stprintf(t, _T("%s%s%s"), FmtPrefix, t2, FmtSuffix);
#ifdef USE_RTF
  // We need to reset the font each time because some RTF formats could conceivably change it.
  RichSample->SetFaceName(PrnFnt->AFnt, 0);
  RichSample->SetPointSize(PrnFnt->AFnt, 0);
  if (_tcsstr(t, "\\rtf"))
    RichSample->SetData(t, SF_RTF);
  else
    SetWindowText(RichSample->hWnd, t);
#else
  SetDlgItemText(TheDlg, id_Sample, t);
#endif
  delete Xmpl;
  free(t2);
  free(t);
}

void BibEdit_OnCommand(HWND Dlg, int id, HWND hwndCtl, UINT codeNotify)
{

  switch (id)
  {
  case IDOK:
  {
    if (Edit_GetTextLength(GetDlgItem(Dlg, id_FmtEdit)))
    {
      GetDlgItemText(Dlg, id_FmtEdit, BibTempFmt, MAX_FMT_LENGTH);

      if (_tcschr(BibTempFmt, _T('\n')))
        ErrorBox(Dlg, err_CRInFmt);
      else
      {
        SetConfigStr(DStrFmts, FmtName, BibTempFmt);
        EndDialog(Dlg, IDOK);
      }
      break;
    }
  }
  case IDCANCEL:
    EndDialog(Dlg, IDCANCEL);
    break;
  case cm_Help:
    WinHelp(FrameWnd, HelpName, HELP_CONTEXT, 5);
    break;
  }
}

void BibName_OnCommand(HWND Dlg, int id, HWND hwndCtl, UINT codeNotify)
{

  switch (id)
  {
  case IDOK:
  {
    if (Edit_GetTextLength(GetDlgItem(Dlg, id_FmtEdit)))
    {
      GetDlgItemText(Dlg, id_FmtEdit, FmtName, MAX_FMT_LENGTH);
      EndDialog(Dlg, IDOK);
      break;
    }
  }
  case IDCANCEL:
    EndDialog(Dlg, IDCANCEL);
    break;
  }
}

BOOL inline BibEdit_OnInitDialog(HWND Dlg, HWND hwndFocus, LPARAM lParam)
{
  GetConfigStr(BibTempFmt, MAX_FMT_LENGTH, DStrFmts, FmtName, _T(""));
  SetDlgItemText(Dlg, id_FmtEdit, BibTempFmt);
  SetWindowText(Dlg, FmtName);
  return TRUE;
}

BOOL CALLBACK BibEditProc(HWND Dlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  switch (Msg)
  {
    HANDLE_MSG(Dlg, WM_COMMAND, BibEdit_OnCommand);
    HANDLE_MSG(Dlg, WM_INITDIALOG, BibEdit_OnInitDialog);
  }
  return (FALSE);
}

BOOL CALLBACK BibNameProc(HWND Dlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  switch (Msg)
  {
    HANDLE_MSG(Dlg, WM_COMMAND, BibName_OnCommand);
  }
  return (FALSE);
}

void BibFmt_OnCommand(HWND Dlg, int id, HWND hwndCtl, UINT codeNotify)
{
  HWND cb;
  int n;
  _TCHAR *t1;

  switch (id)
  {
  case id_FmtEdit:
  case id_FmtNew:
  {
    cb = GetDlgItem(Dlg, id_FmtList);
    if (id == id_FmtEdit)
    {
      n = ListBox_GetCurSel(cb);
      if (n == LB_ERR)
        break;
      ListBox_GetText(cb, n, FmtName);
    }
    else
    {
      if (DialogBox(ResInstance, _T("BIBNAME"), Dlg, BibNameProc) == IDCANCEL)
        break;

      if (ListBox_FindStringExact(cb, 0, FmtName) != LB_ERR)
      {
        ErrorBox(Dlg, err_BibAlready);
        break;
      }
    }

    if (DialogBox(ResInstance, _T("EDITBIB"), Dlg, BibEditProc) == IDOK)
    {

      if (id != id_FmtNew)
        ListBox_DeleteString(cb, n);

      ListBox_SetCurSel(cb, ListBox_AddString(cb, FmtName));

      UpdateSample(Dlg);
    }
    break;
  }

  case id_FmtDel:
  {
    cb = GetDlgItem(Dlg, id_FmtList);
    ListBox_GetText(cb, n = ListBox_GetCurSel(cb), FmtName);
    ListBox_DeleteString(cb, n);
    SetConfigStr(DStrFmts, FmtName, NULL);
    break;
  }

  case id_FmtList:
  {
    cb = GetDlgItem(Dlg, id_FmtList);
    n = ListBox_GetSelCount(cb);
    EnableWindow(GetDlgItem(Dlg, id_FmtDel), n);
    EnableWindow(GetDlgItem(Dlg, id_FmtEdit), n);

    if (codeNotify == LBN_SELCHANGE)
      UpdateSample(Dlg);
    break;
  }

  case IDOK:
  {
    t1 = (_TCHAR *)malloc(SCRATCH_SIZE);
    cb = GetDlgItem(Dlg, id_FmtList);
    ListBox_GetText(cb, n = ListBox_GetCurSel(cb), FmtName);

    GetConfigStr(t1, MAX_FMT_LENGTH, DStrFmts, FmtName, _T(""));
    DecodeBibFmt(t1);

    if (BibData && BibIsFormatted)
      PostMessage(BibData->Window, WM_COMMAND, cm_FormatChng, 0);

    free(t1);
  }

  case IDCANCEL:
  {
#ifdef USE_RTF
    delete (RichSample);
#endif
    EndDialog(Dlg, id);
    break;
  }
  case cm_Help:
    WinHelp(FrameWnd, HelpName, HELP_CONTEXT, 5);
    break;
  }
}

BOOL BibFmt_OnInitDialog(HWND Dlg, HWND hwndFocus, LPARAM lParam)
{
  _TCHAR *Ptr, *t;
#ifdef WIN32
  int r;
  DWORD disp, dwType;
  DWORD cb = MAX_PATH;
  DWORD cb2 = MAX_PATH;
  DWORD tcb = MAX_PATH;
  HKEY hkLocal, hkUser;
  _TCHAR t1[MAX_PATH], t2[MAX_PATH];
#endif
  int N;
  HWND w;
#ifdef USE_RTF
  RECT sr;
  POINT tl;
#endif

  t = (_TCHAR *)malloc(SCRATCH_SIZE);
  GetConfigStr(t, SCRATCH_SIZE - 1, DStrFmts, NULL, _T("\0\0"));

#ifdef WIN32
  // Copy default formats across from HKEY_LOCAL_MACHINE
  if (*t == _T('\0'))
  {
    if ((r = RegOpenKeyEx(
             HKEY_LOCAL_MACHINE,
             _T("Software\\TJRC\\Refs\\Formats"),
             0,
             KEY_READ,
             &hkLocal)) == ERROR_SUCCESS)
    {
      if ((r = RegCreateKeyEx(
               HKEY_CURRENT_USER,
               _T("Software\\TJRC\\Refs\\Formats"),
               0,
               NULL,
               REG_OPTION_NON_VOLATILE,
               KEY_WRITE,
               NULL,
               &hkUser,
               &disp)) == ERROR_SUCCESS)
      {
        for (N = 0;
             (r = RegEnumValue(
                  hkLocal,
                  N,
                  t1,
                  &cb,
                  NULL,
                  &dwType,
                  (LPBYTE)t2,
                  &cb2)) != ERROR_NO_MORE_ITEMS;
             N++)
        {
          r = RegSetValueEx(
              hkUser,
              t1,
              0,
              dwType,
              (LPBYTE)t2,
              cb2);

          cb = cb2 = tcb;
        }

        RegCloseKey(hkUser);

        GetConfigStr(t, SCRATCH_SIZE - 1, DStrFmts, NULL, _T("\0\0"));
      }
      else
      {
        t[0] = _T('\0');
      }
      RegCloseKey(hkLocal);
    }
    else
    {
      t[0] = _T('\0');
    }
  }
#endif

  w = GetDlgItem(Dlg, id_FmtList);

  Ptr = t;
  while (Ptr[0] != _T('\0'))
  {
    ListBox_AddString(w, Ptr);
    Ptr = strend(Ptr);
    Ptr++;
  }

  if (FmtName[0] == _T('\0'))
    N = 0;
  else
    N = ListBox_FindStringExact(w, 0, FmtName);
  if (N == -1)
    N = 0;

  ListBox_SetCurSel(w, N);
  ListBox_GetText(w, N, FmtName);

  free(t);

#ifdef USE_RTF
  w = GetDlgItem(Dlg, id_Sample);
  GetWindowRect(w, &sr);
  tl.x = sr.left;
  tl.y = sr.top;
  ScreenToClient(Dlg, &tl);
  DestroyWindow(w);
  RichSample = new TRichEdit(
      WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_WANTRETURN | ES_SUNKEN | WS_BORDER,
      tl.x, tl.y,
      sr.right - sr.left,
      sr.bottom - sr.top,
      Dlg,
      (HMENU)id_Sample);
#else
  if (PrnFnt && (PrnFnt->SFont))
    SetWindowFont(GetDlgItem(Dlg, id_Sample), PrnFnt->SFont, FALSE);
#endif

  UpdateSample(Dlg);
  return TRUE;
}

BOOL CALLBACK BibFmtProc(HWND Dlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  switch (Msg)
  {
    HANDLE_MSG(Dlg, WM_COMMAND, BibFmt_OnCommand);
    HANDLE_MSG(Dlg, WM_INITDIALOG, BibFmt_OnInitDialog);
  }
  return (FALSE);
}

void inline BibFormats(void)
{
  DialogBox(ResInstance, _T("BIBFMT"), FrameWnd, BibFmtProc);
}
