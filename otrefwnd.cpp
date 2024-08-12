#include "inc/globals.h"
#include "inc/reffont.h"
#include "inc/refimp.h"
#include "inc/refpaint.h"
#ifdef CC_TOOLBAR
#include "inc/rtoolbar.h"
#endif
#ifdef WIN32
#include "inc/refframe.h"
#endif
#ifdef USE_RTF
#include "inc/redit.h"
#endif

extern _TCHAR LastDir[MAX_PATH];
extern void Dlg2Buf(HWND Dlg, LPRef ARef);

UINT CALLBACK OpenHook(HWND Wnd, UINT wm, WPARAM wParam, LPARAM lParam)
{
#ifndef WIN32
  if (IsCtl3D && (wm == WM_INITDIALOG))
    Ctl3dSubclassDlg(Wnd, CTL3D_ALL);
#endif
  return (0);
}

TRefWndData::TRefWndData(void)
{
  int n;

  // set up flags
  for (n = 0; n <= 2; n++)
    SortFlags[n] = MSortFlags[n];
  ListFlags = MasterFlags;
  NameSort = MSortName;
  ClmnWdth = MasterWdth;
  SrchFlag = DefSrchFlag;
  Refs = new TSrchColl(100, FALSE, this);
  SWnd = 0;
  *FPath = _T('\0'); // clear name field
  SrchPat = NULL;
  NeedsSaving = FALSE;
}

// Updates the current reference
long TRefWndData::UpdateCurrent(void)
{
  long N;

  Current = NULL;

  // Update 'current' pointer to latest selection
  if (ListBox_GetSelCount(ListWnd) == 1)
  {

    N = ListBox_GetCurSel(ListWnd);

    if (N != -1)
    {
      Current = (LPRef)(Refs->at(N));
      return (N);
    }
    else
      return (-1);
  }
  else
    return (-1);
}

void TRefWndData::NameWnd(void)
{
  /*
  1. If filename,  use that
  2. If bibliography use that
  3. If search results, use that
  */

  if (*FPath != _T('\0'))
    lstrcpy(Refs->s1, FPath);

  else
  {

    if (this == BibData) // get appropriate 'bibliography' translation
      LoadString(ResInstance, str_BibWndName, Refs->s1, MAX_PATH - 1);

    else
    {

      if (SrchPat) // it's a search window
        lstrcpy(Refs->s1, SrchPat);

      else // it has not yet been named
        lstrcpy(Refs->s1, Untitled);
    }
  }

  SetWindowText(Window, Refs->s1);
}

void TRefWndData::Format(int AsEdit)
{

  RECT BRect, SRect;
  LPTSTR BibTeX;

#ifdef WIN32

  HCURSOR OCursor;

  CCursor = LoadCursor(0, IDC_WAIT);
  OCursor = SetCursor(CCursor);
#endif

#ifdef USE_RTF // Get rid of the existing window
  _try
  {
    // if it is not already formatted, this free generates an access violation, so trap it.
    delete ((hRichEdit)ListWnd);
  }
  _except(GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
  {
    DestroyWindow(ListWnd);
  }

#else
  DestroyWindow(ListWnd);
#endif

  if (BibIsFormatted)
  { // create an edit window

    GetClientRect(Window, &BRect);
    GetWindowRect(SWnd, &SRect);

#ifdef USE_RTF
    ListWnd = (HWND) new TRichEdit(
        WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_WANTRETURN | ES_SUNKEN | WS_BORDER,
        0, 0,
        BRect.right - BRect.left,
        BRect.bottom - BRect.top - (SRect.bottom - SRect.top),
        Window,
        (HMENU)100);

    // Give it the current printer font
    ((hRichEdit)ListWnd)->SetFaceName(PrnFnt->AFnt, 0);
    ((hRichEdit)ListWnd)->SetPointSize(PrnFnt->AFnt, 0);

#else
    ListWnd = CreateWindowEx(
        0,
        _T("Edit"),
        _T(""),
        WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_WANTRETURN | WS_BORDER,
        0, 0,
        BRect.right - BRect.left,
        BRect.bottom - BRect.top - (SRect.bottom - SRect.top),
        Window,
        (HMENU)100,
        hinstCurrent,
        NULL);

    // Give it the current printer font
    SetWindowFont(ListWnd, PrnFnt->SFont, FALSE);
#endif

    // Allocate the memory to format the references into
    if ((BibTeX = (LPTSTR)malloc(MAX_EDIT_CONTENTS)) == NULL)
    {
      // can't do edit window, so go back to list
      ErrorBox(Window, err_NoMem);
#ifdef USE_RTF
      delete ((hRichEdit)ListWnd);
#else
      DestroyWindow(ListWnd);
#endif
      BibIsFormatted = FALSE;
      CreateMainList();
      return;
    }

    if (Refs->FillBibWnd(0, BibTeX) != Refs->count)
      ErrorBox(Window, err_BibTooBig);

#ifdef USE_RTF
    if (_tcsstr(BibTeX, _T("\\rtf")))
      ((hRichEdit)ListWnd)->SetData(BibTeX, SF_RTF);
    else
#endif
      Edit_SetText(ListWnd, BibTeX);

    // Free the memory again
    free(BibTeX);
  }
  else
  {

    // We want the database list
    CreateMainList();
    Refs->redisplay();
  }

#ifdef WIN32
  // put the cursor back the way it was.
  CCursor = OCursor;
  SetCursor(CCursor);
#endif
}

void TRefWndData::ReSort(void)
{
  LPSrchColl T;
  long n, Tot;
  int pcnt;
  _TCHAR PctFmt[20];
  HWND Dlg;

  if (Refs && (Refs->count > 1))
  {

    // Create progress dialog
    Dlg = CreateDialog(ResInstance, _T("CLEAN"), Window, CleanProc);
    EnableWindow(FrameWnd, FALSE);

    // load format string
    LoadString(ResInstance, str_Sorting, PctFmt, sizeof(PctFmt) / sizeof(_TCHAR));

    // create new collection
    T = new TSrchColl(Refs->limit, FALSE, this);

    // insert them all
    Tot = Refs->count - 1;

    for (n = 0; n <= Tot; n++)
    {

      T->insert(Refs->at(n));

      // every so often give the other tasks a chance, and update the progress dlg
      if ((n & HOW_OFTEN) == HOW_OFTEN)
      {
        pcnt = (100 * n) / Tot;
        wsprintf(Refs->s1, PctFmt, pcnt);
        SetDlgItemText(Dlg, id_LoadingRef, Refs->s1);
        Pause(Dlg, FALSE);
      }
    }

    // clear out the old collection...
    Refs->removeall();

    // ... and delete it
    delete Refs;

    // and then replace it with the new one
    Refs = T;

    // redisplay everything and return things to normal
    Refs->redisplay();
    EnableWindow(FrameWnd, TRUE);
    DestroyWindow(Dlg);
  }
}

BOOL Srch_OnInitDialog(HWND Dlg, HWND hwndFocus, LPARAM lParam)
{
  int n;
  HWND cb_by;
  _TCHAR t[64];

  switch (stflg)
  {
  case cm_ExpandSrch:
  case cm_NarrowSrch:
  {
    LoadString(ResInstance, stflg - cm_NarrowSrch + str_NarrowSrch, t, sizeof(t) / sizeof(_TCHAR));
    SetWindowText(Dlg, t);
    break;
  }
  }

  // get window handle of combo box
  cb_by = GetDlgItem(Dlg, id_SrchBy);

  // add the types of search
  for (n = 1; n < SHOW_ALL; n++)
  {
    LoadString(ResInstance, n, t, sizeof(t) / sizeof(_TCHAR));
    ComboBox_AddString(cb_by, t);
  }

  // select the form of search last tried
  ComboBox_SetCurSel(cb_by, SrchBy - 1);

  // set the case sensitivity etc last used
  CheckDlgButton(Dlg, id_Case, ((SrchFlags & SF_IGNORECASE) == 0));
  CheckDlgButton(Dlg, id_Not, ((SrchFlags & SF_NOT) != 0));
  CheckDlgButton(Dlg, id_Regexp, ((SrchFlags & SF_REGEXP) != 0));

  // Set last search in box
  SetDlgItemText(Dlg, id_SrchFor, SrchFor);

  return TRUE;
}

void Srch_OnCommand(HWND Dlg, int id, HWND hwndCtl, UINT codeNotify)
{

  switch (id)
  {
  case IDOK:
  {
    // get data from controls
    SrchBy = 1 + ComboBox_GetCurSel(GetDlgItem(Dlg, id_SrchBy));
    SrchFlags = (IsDlgButtonChecked(Dlg, id_Case) ? 0 : SF_IGNORECASE);
    if (IsDlgButtonChecked(Dlg, id_Not))
      SrchFlags |= SF_NOT;
    if (IsDlgButtonChecked(Dlg, id_Regexp))
      SrchFlags |= SF_REGEXP;

    // got to search for something!
    if (GetDlgItemText(Dlg, id_SrchFor, SrchFor, sizeof(SrchFor) / sizeof(_TCHAR)) > 0) // there is something in the text box
      EndDialog(Dlg, IDOK);
    else
      ErrorBox(Dlg, err_SrchStr);
    break;
  }

  case IDCANCEL:
    EndDialog(Dlg, IDCANCEL);
  }
}

BOOL CALLBACK SrchDlg(HWND Dlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  switch (Msg)
  {
    HANDLE_MSG(Dlg, WM_INITDIALOG, Srch_OnInitDialog);
    HANDLE_MSG(Dlg, WM_COMMAND, Srch_OnCommand);
  }
  return (FALSE);
}

void SearchAll(LPSrchColl AddTo)
{

  HCURSOR OC;
  HWND cWnd;
  LPRefWndData WorkDat;
  _TCHAR t[64];

  // create progress dialog
  AddTo->ProgressWnd = CreateDialog(ResInstance, _T("CLEAN"), FrameWnd, CleanProc);

  LoadString(ResInstance, str_Searching, t, sizeof(t) / sizeof(_TCHAR));
  SetDlgItemText(AddTo->ProgressWnd, id_LoadingRef, t);

  EnableWindow(FrameWnd, FALSE);

  CCursor = LoadCursor(0, IDC_WAIT);
  OC = SetCursor(CCursor);

  for (cWnd = ActiveFile->Window;
       cWnd != NULL;
       cWnd = GetNextWindow(cWnd, GW_HWNDNEXT))
  {

    GetClassName(cWnd, t, sizeof(t));

    if (lstrcmp(t, FILECLASS) == 0)
    {

      WorkDat = (LPRefWndData)GetWindowLong(cWnd, 0);

      // and search it if it is set searchable
      if (WorkDat->SrchFlag)
        WorkDat->Refs->refsrch(SrchBy, SrchFor, AddTo, SrchFlags);
    }
  }

  CCursor = OC;

  SetCursor(OC);
  EnableWindow(FrameWnd, TRUE);
  DestroyWindow(AddTo->ProgressWnd);
  AddTo->ProgressWnd = NULL;
}

void TRefWndData::NewSearch(int WhatSort)
{
  long n;
  LPSrchColl T;
  LPRefWndData TW;

  stflg = WhatSort;
  n = IDOK;

  // In most cases ask for the search criteria
  if (WhatSort != cm_RefAll)
    n = DialogBox(ResInstance, _T("NEWSRCH"), FrameWnd, SrchDlg);

  // If we really do want to do the search
  if (n != IDCANCEL)
  {

    switch (WhatSort)
    {

    case cm_RefSearch:
    case cm_ExpandSrch:
    {

      if (WhatSort == cm_RefSearch)
      {

        // Create new Window
        SendMessage(FrameWnd, WM_COMMAND, cm_FileNew, 0);
        TW = NewWnd;

        // Make it save as by clearing the file path
        *(TW->FPath) = _T('\0');

        // Stop it being searched
        TW->SrchFlag = FALSE;
        Button_SetCheck(TW->SWnd, 0);
      }
      else // if expanding the search, use the current window
        TW = this;

      // Add to window's collection all matching items
      SetWindowRedraw(TW->ListWnd, FALSE);
      SearchAll(TW->Refs);
      SetWindowRedraw(TW->ListWnd, TRUE);

      // set results
      n = TW->Refs->count;
      break;
    }

    case cm_RefAll:
      TW = this;
      break; // just show all the references

    case cm_NarrowSrch:
    {

      // use the current window
      TW = this;

      // create a new colelction to put the results in
      T = new TSrchColl(20, FALSE, this);

      // don't update the window yet
      SetWindowRedraw(ListWnd, FALSE);

      // search this window only
      n = Refs->refsrch(SrchBy, SrchFor, T, SrchFlags);

      // now update the window
      SetWindowRedraw(ListWnd, TRUE);

      if (n)
      { // We found some, so replace the window's collection

        delete Refs;
        Refs = T;
      }

      else // we found nothing so leave things as they were
        delete T;

      break;
    }
    }

    // Redisplay window contents
    TW->Refs->redisplay();

    if (n == 0)
    { // We found nothing
      ErrorBox(FrameWnd, wrn_None);

      if (WhatSort == cm_RefSearch) // Window must be empty, so close window again
        SendMessage(TW->Window, WM_CLOSE, 0, 0);
    }
    else
    {

      if (WhatSort != cm_RefAll)
      { // sort out the new search pattern description

        LoadString(ResInstance, SrchBy + 20, Refs->s2, SCRATCH_SIZE);

        if (SrchFlags & SF_NOT)
          lstrcat(Refs->s2, _T("!"));

        wsprintf(Refs->s1, _T("%s\"%s\""), Refs->s2, SrchFor);

        if (WhatSort != cm_RefSearch)
        {
          wsprintf(Refs->s2, _T("{ %s"), TW->SrchPat);
        }

        switch (WhatSort)
        {
        case cm_ExpandSrch:
          lstrcat(Refs->s2, _T(" } , { "));
          break;
        case cm_NarrowSrch:
          lstrcat(Refs->s2, _T(" } + { "));
          break;
        case cm_RefSearch:
          lstrcpy(Refs->s2, Refs->s1);
          break;
        case cm_RefAll:
          Refs->s2[0] = _T('\0');
        }

        if (Refs->s2[0] != _T('\0'))
        {

          if (WhatSort != cm_RefSearch)
          {
            strlcat(Refs->s2, Refs->s1, SCRATCH_SIZE - 4);
            lstrcat(Refs->s2, _T(" }"));
          }

          // if there's already a search pattern, destroy and replace it
          if (TW->SrchPat)
          {
            free(TW->SrchPat);
          }

          TW->SrchPat = _tcsdup(Refs->s2);

          // set the name of the window
          TW->NameWnd();
        }

        // tell the user what (s)he has found
        LoadString(ResInstance, fmt_StatusBar, Refs->s1, SCRATCH_SIZE - 1);
        wsprintf(Refs->s2, Refs->s1, n, TW->SrchPat);
        LoadString(ResInstance, msg_SrchResults, Refs->s1, SCRATCH_SIZE - 1);
        MessageBox(TW->Window, Refs->s2, Refs->s1, MB_ICONINFORMATION | MB_OK);
      }
    }
  } // n!=IDCANCEL

#ifdef CC_TOOLBAR
  // some toolbar buttons may need updating
  UpdateButtons();
#endif

  // redraw the status window
#ifdef WIN32
  DefaultStatus();
#else
  InvalidateRect(FrameWnd, &StatusRect, TRUE);
#endif
}

TRefWndData::~TRefWndData()
{
  // get rid of any search description
  if (SrchPat)
    free(SrchPat);

  // destroy the reference collection
  DestroyColls();
}

void TRefWndData::Resize(int cx, int cy)
{

  RECT SRect;

  GetWindowRect(SWnd, &SRect);

  // resize the list box or edit window
#ifdef USE_RTF
  if ((this == BibData) && (BibIsFormatted))
    MoveWindow(((hRichEdit)ListWnd)->hWnd, 0, 0, cx, cy - (SRect.bottom - SRect.top), TRUE);
  else
#endif
    MoveWindow(ListWnd, 0, 0, cx, cy - (SRect.bottom - SRect.top), TRUE);

  // resize the searchable checkbox
  MoveWindow(SWnd, 1, cy - (SRect.bottom - SRect.top), cx - 1, SRect.bottom - SRect.top, TRUE);
}

void TRefWndData::DestroyColls(void)
{

  HWND TWnd;

  TWnd = CreateDialog(ResInstance, _T("CLEAN"), Window, CleanProc);
  delete Refs;
  DestroyWindow(TWnd);
}

void TRefWndData::CreateMainList(void)
{

  unsigned long Flags;
  RECT Rect, SRect;
  HDC DC;

  GetClientRect(Window, &Rect);

  if (!SWnd)
  {

    DFont = (HFONT)GetStockObject(SYSTEM_FONT);
    DC = GetDC(FrameWnd);
    SelectFont(DC, DFont);
    GetTextMetrics(DC, &TM);
    StatusHeight = TM.tmHeight;
    ReleaseDC(FrameWnd, DC);

    // if there's no searchable button, create one.

    LoadString(ResInstance, str_Searchable, Refs->s1, SCRATCH_SIZE - 1);
    SWnd = CreateWindowEx(
        0,
        _T("Button"),
        Refs->s1,
        WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
        0, 0,
        Rect.right - Rect.left,
        StatusHeight,
        Window,
        (HMENU)801,
        hinstCurrent,
        NULL);

#ifndef WIN32
    // and 3D subclass it
    if (IsCtl3D)
      Ctl3dSubclassCtl(SWnd);
#endif

    // initialise its checked state
    Button_SetCheck(SWnd, SrchFlag);
  }

  GetWindowRect(SWnd, &SRect);

  if (!(ListFlags & 4)) // user wants no titles
    Flags = WS_VISIBLE | WS_CHILD | WS_BORDER | LBS_NOINTEGRALHEIGHT | LBS_NOTIFY | LBS_EXTENDEDSEL | LBS_MULTICOLUMN | LBS_OWNERDRAWFIXED | WS_HSCROLL;

  else // user has elected to show titles
    Flags = WS_VISIBLE | WS_CHILD | WS_BORDER | LBS_NOINTEGRALHEIGHT | LBS_NOTIFY | LBS_EXTENDEDSEL | LBS_OWNERDRAWFIXED | WS_VSCROLL | WS_HSCROLL;

  // create the listbox
  ListWnd = CreateWindowEx(
#ifdef WIN32
      WS_EX_CLIENTEDGE,
#else
      0,
#endif
      _T("ListBox"), _T(""),
      Flags,
      0, 0,
      Rect.right - Rect.left,
      Rect.bottom - Rect.top - (SRect.bottom - SRect.top),
      Window,
      (HMENU)800,
      hinstCurrent,
      NULL);

  // if the title is not being displayed, set the column width of the multicolumn box.
  if (!(ListFlags & 4))
    ListBox_SetColumnWidth(ListWnd, (ClmnWdth + 1) * CharWidth + DateWidth);

  // set the tabstop for the date
  Stops = ClmnWdth * CharWidth; // Current guess for tabstops
}

BOOL InitFile(int IsSave, int GetName, _TCHAR *FileSp, _TCHAR *FPath)
{

  static _TCHAR Wibble[MAX_PATH];
  static _TCHAR TPth[MAX_PATH];
  _TCHAR *Ptr;
  long FFlags;
  int r;
  struct _stat statbuf;
  OPENFILENAME TOF;

  // Copy names to scratch variables
  if (IsSave || (!GetName))
    lstrcpy(Wibble, FPath);
  else
    Wibble[0] = _T('\0');

#ifdef WIN32
  FFlags = IsSave ? OFN_ENABLEHOOK | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT : OFN_ENABLEHOOK | OFN_HIDEREADONLY | OFN_FILEMUSTEXIST;

  // if we're running under Windows 95 we can use the explorer style dialogs
  if (Is95)
    FFlags |= OFN_EXPLORER;

#else
  FFlags = IsSave ? OFN_ENABLEHOOK | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT : OFN_ENABLEHOOK | OFN_HIDEREADONLY | OFN_FILEMUSTEXIST;
#endif

  if (GetName || (Wibble[0] == '\0'))
  { // need to get filename

    // fill out structure
    TOF.lStructSize = sizeof(OPENFILENAME);
    TOF.hwndOwner = FrameWnd;
    TOF.lpstrFilter = FileSp;
    TOF.lpstrCustomFilter = NULL;
    TOF.nMaxCustFilter = 0;
    TOF.nFilterIndex = 1;
    TOF.lpstrFile = Wibble;
    TOF.nMaxFile = sizeof(Wibble);
    TOF.lpstrFileTitle = NULL;
    TOF.nMaxFileTitle = 0;
    // set last used directory if possible
    TOF.lpstrInitialDir = (LastDir[0] == _T('\0')) ? NULL : LastDir;
    TOF.lpstrTitle = NULL;
    TOF.Flags = FFlags;
    TOF.nFileOffset = TOF.nFileExtension = 0;
    Ptr = strend(FileSp);
    Ptr += 3;
    TOF.lpstrDefExt = Ptr;
    TOF.lpfnHook = OpenHook;
    TOF.lCustData = 0;
    TOF.hInstance = hinstCurrent;

    // get the filename
    r = IsSave ? GetSaveFileName(&TOF) : GetOpenFileName(&TOF);

    if (!r)
    {
      return (FALSE);
    }
  }

  // get an absolute path to the file
#ifdef WIN32
  if (GetFullPathName(Wibble, MAX_PATH, TPth, &Ptr))
#else
  if (_fullpath(TPth, Wibble, MAX_PATH))
#endif
    lstrcpy(Wibble, TPth);

  // Does the file exist?
  r = _tstat(Wibble, &statbuf);

  if ((!IsSave) && r)
  { // no it doesn't!
    ErrorBox(FrameWnd, err_NoFile);
    DeleteOldFile(Wibble);
  }

  else
  { // it may do, but doesn't matter coz we're saving

    if ((IsSave) && (MakeBak) && (!r))
    { // Backup to .BAK file

      lstrcpy(TPth, Wibble);
      Ptr = _tcsrchr(TPth, _T('.'));

      if (Ptr) // no filetype supplied
        *Ptr = _T('\0');

      lstrcat(TPth, _T(".BAK"));

      // rename old file
      _trename(Wibble, TPth);
    }

    // store the new file name and set the current data directory
    lstrcpy(FPath, Wibble);
    Ptr = _tcsrchr(Wibble, _T('\\'));
    if (Ptr)
    {
      Ptr[0] = _T('\0');
      lstrcpy(LastDir, Wibble);
    }

    return (TRUE);
  }
  return (FALSE);
}

void BibSave(void)
{
  _TCHAR APath[MAX_PATH];
  FILE *f;
  long n;
  LPTSTR p;

  LPSrchColl s;

  *APath = _T('\0');

  p = _tcsstr(FmtPrefix, _T("\\rtf"));

  if (InitFile(TRUE,
               TRUE,
               (p ? RTFFSpecs : BibFSpecs),
               APath))
  {
    if ((f = _tfopen(APath, _T("wb"))) != NULL)
    {

      s = BibData->Refs;
      _ftprintf(f, _T("%s"), FmtPrefix);

      for (n = 0; n < s->count; n++)
      {
        ((LPRef)(s->at(n)))->FormatRef(s->s1);
        _ftprintf(f, _T("%s"), s->s1);
      }

      _ftprintf(f, _T("%s"), FmtSuffix);
      fclose(f);
    }
  }
  /*   BibTeX=(LPTSTR)malloc(MAX_EDIT_CONTENTS);

    if (BibTeX){

      Edit_GetText(BibData->ListWnd, BibTeX, MAX_EDIT_CONTENTS-1);

      if (InitFile(TRUE, TRUE, BibFSpecs, APath)){
        f=_tfopen(APath, _T("wb"));
        _ftprintf(f, _T("%s"), BibTeX);
        fclose(f);
      }

      free(BibTeX);
      BibTeX=NULL;

    }
  */

  // need an error message here
}

int TRefWndData::CanClose(void)
{
  int r, t;
  LPRef ARef;

  t = TRUE;

  if (SrchPat) // Can always close search windows
    return TRUE;

  // First determine whether any references in this file are currently being edited
  for (r = 0;
       r < Refs->count;
       r++)
  {
    ARef = (LPRef)Refs->at(r);
    if (ARef->hwndEditor)
    {
      // Reference is being edited
      if (ARef->Flags & RF_NeedsUpdating)
      {
        GetWindowText(ARef->hwndEditor, Refs->s1, RES_STR);
        wsprintf(Refs->s2, _T("The open reference \"%s\" has been changed.\nUpdate in file(s)?"), Refs->s1);
        if (MessageBox(FrameWnd, Refs->s2, _T("Warning!"), MB_YESNO | MB_ICONQUESTION) == IDYES)
        {
          Dlg2Buf(ARef->hwndEditor, ARef);
          NeedsSaving = TRUE;
        }
      }
    }
  }

  if (NeedsSaving)
  {

    LoadString(ResInstance, wrn_NeedSave, Refs->s1, SCRATCH_SIZE - 1);

    if (*FPath != _T('\0'))
      lstrcpy(Refs->s2, FPath);

    else
      GetWindowText(Window, Refs->s2, SCRATCH_SIZE - 1);

    r = MessageBox(FrameWnd, Refs->s1, Refs->s2, MB_YESNOCANCEL | MB_ICONSTOP);

    t = (r != IDCANCEL);

    if (r == IDYES)
      t = *FPath != _T('\0') ? ImpRefs(this, cm_FSave, FALSE) : ImpRefs(this, cm_FSaveAs, TRUE);
  }

  return t;
}
