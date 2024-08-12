#include "inc/globals.h"
#include "inc/rcutpast.h"
#include "inc/refabout.h"
#include "inc/rconfopt.h"
#include "inc/refbibs.h"
#include "inc/refframe.h"
#include "inc/refimp.h"
#include "inc/refio.h"
#include "inc/refinopt.h"
#include "inc/reflopts.h"
#include "inc/refnag.h"
#include "inc/refpaint.h"
#include "inc/refprn.h"
#include "inc/rsetlang.h"
#include "inc/rsrtopt.h"
#include "inc/rsrchopt.h"
#include "inc/reffont.h"
#include "inc/editdlg.h"
#include "inc/authdlg.h"
#include "inc/redit.h"

#ifdef CC_STATUS

#include "inc/status.h"

HWND hWndStatus;

// status bar field widths
int aWidths[STATUS_FIELDS] = {-1};

#endif // CC_STATUS

#ifdef CC_TOOLBAR
#include "inc/rtoolbar.h"

HWND hWndToolbar;

#ifdef WIN32
TBBUTTON tbButtons[TOOL_BUTTON_NO] = {
    {0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
    {0, cm_FileNew, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
    {1, cm_FOpen, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
    {2, cm_FSave, 0, TBSTYLE_BUTTON, 0L, 0},
    {0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
    {6, cm_Print, 0, TBSTYLE_BUTTON, 0L, 0},
    {0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
    {3, WM_CUT, 0, TBSTYLE_BUTTON, 0L, 0},
    {4, WM_COPY, 0, TBSTYLE_BUTTON, 0L, 0},
    {5, WM_PASTE, 0, TBSTYLE_BUTTON, 0L, 0},
    {0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
    {9, cm_RefNew, 0, TBSTYLE_BUTTON, 0L, 0},
    {10, cm_AddToBib, 0, TBSTYLE_BUTTON, 0L, 0},
    {8, cm_BView, TBSTATE_ENABLED, TBSTYLE_CHECK, 0L, 0},
    {0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
    {11, cm_RefSearch, 0, TBSTYLE_BUTTON, 0L, 0},
    {12, cm_NarrowSrch, 0, TBSTYLE_BUTTON, 0L, 0},
    {13, cm_ExpandSrch, 0, TBSTYLE_BUTTON, 0L, 0},
    {0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
    {0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
    {7, cm_HelpIndex, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
};

TOOLINFO tbToolInfo;

#else

TBBUTTON tbButtons[TOOL_BUTTON_NO - 1] = {
    {0, cm_FileNew, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0},
    {1, cm_FOpen, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0},
    {2, cm_FSave, 0, TBSTYLE_BUTTON, 0},
    {0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0},
    {6, cm_Print, 0, TBSTYLE_BUTTON, 0},
    {0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0},
    {3, WM_CUT, 0, TBSTYLE_BUTTON, 0},
    {4, WM_COPY, 0, TBSTYLE_BUTTON, 0},
    {5, WM_PASTE, 0, TBSTYLE_BUTTON, 0},
    {0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0},
    {9, cm_RefNew, 0, TBSTYLE_BUTTON, 0},
    {10, cm_AddToBib, 0, TBSTYLE_BUTTON, 0},
    {8, cm_BView, TBSTATE_ENABLED, TBSTYLE_CHECK, 0},
    {0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0},
    {11, cm_RefSearch, 0, TBSTYLE_BUTTON, 0},
    {12, cm_NarrowSrch, 0, TBSTYLE_BUTTON, 0},
    {13, cm_ExpandSrch, 0, TBSTYLE_BUTTON, 0},
    {0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0},
    {0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0},
    {7, cm_HelpIndex, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0},
};
#endif

void UpdateClipButtons(void)
{

  BOOL CanCopy, CanPaste, CanCut, CanAddToBib;
  int n;

  if (ActiveFile)
  {
    // There is a document window active
    if ((BibIsFormatted) && (ActiveFile == BibData))
    {

      // It's the formatted bibliography
      CanPaste = IsClipboardFormatAvailable(CF_TEXT);
      CanCut = CanCopy = TRUE;
      CanAddToBib = FALSE;
    }

    else
    {
      // It's a database window
      n = ListBox_GetSelCount(ActiveFile->ListWnd);
      CanAddToBib = (ActiveFile != BibData) && (n != 0);
      CanCut = CanCopy = (n != 0);
      CanPaste = (CutPasteColl != NULL);
    }
  }
  else
    CanAddToBib = CanCut = CanPaste = CanCopy = FALSE;

  SendMessage(hWndToolbar, TB_ENABLEBUTTON, cm_AddToBib, MAKELONG(CanAddToBib, 0));
  SendMessage(hWndToolbar, TB_ENABLEBUTTON, WM_CUT, MAKELONG(CanCut, 0));
  SendMessage(hWndToolbar, TB_ENABLEBUTTON, WM_COPY, MAKELONG(CanCopy, 0));
  SendMessage(hWndToolbar, TB_ENABLEBUTTON, WM_PASTE, MAKELONG(CanPaste, 0));
}

void UpdateButtons(void)
{

  LPARAM FileState;
  BOOL CanNarrow;

#ifndef WIN32
  if (!CommCtrlAvail) // This is not Windows for Workgroups
    return;
#endif

  UpdateClipButtons();

  FileState = MAKELONG(ActiveFile != NULL, 0);

  // Initialise toolbar clipboard button states
  SendMessage(FrameWnd, WM_DRAWCLIPBOARD, 1, 0);

  // New file button
  SendMessage(hWndToolbar, TB_ENABLEBUTTON, cm_FileNew, MAKELONG(Clients < MAX_FILES, 0));

  // Print button
  SendMessage(hWndToolbar, TB_ENABLEBUTTON, cm_Print, FileState);

  // Save button
  SendMessage(hWndToolbar, TB_ENABLEBUTTON, cm_FSave, FileState);

  // New reference button
  SendMessage(hWndToolbar, TB_ENABLEBUTTON, cm_RefNew, MAKELONG((ActiveFile != NULL) && (ActiveFile != BibData), 0));

  // BView button
  SendMessage(hWndToolbar, TB_CHECKBUTTON, cm_BView, MAKELONG(BibIsFormatted, 0));

  // Search buttons
  CanNarrow = ((ActiveFile != NULL) && (ActiveFile->SrchPat));

  SendMessage(hWndToolbar, TB_ENABLEBUTTON, cm_RefSearch, FileState);
  SendMessage(hWndToolbar, TB_ENABLEBUTTON, cm_NarrowSrch, CanNarrow);
  SendMessage(hWndToolbar, TB_ENABLEBUTTON, cm_ExpandSrch, CanNarrow);
}

#endif // CC_TOOLBAR

BOOL CloseAllFiles(void)
{
  BOOL Successful;
  HWND cWnd;
  int WndList[MAX_FILES];
  int c, n;
  _TCHAR AClass[20];

  Successful = TRUE;

  if (ActiveFile)
  {

    // get all the window handles
    for (n = 0, cWnd = ActiveFile->Window;
         cWnd != NULL;
         cWnd = GetNextWindow(cWnd, GW_HWNDNEXT))
    {

      GetClassName(cWnd, AClass, sizeof(AClass) / sizeof(_TCHAR));

      if (lstrcmp(AClass, FILECLASS) == 0)
        WndList[n++] = (int)cWnd;
    }

    // close the windows in the list
    for (c = 0;
         (c < n) && Successful;
         c++)
    {

      SendMessage(ClientWnd, WM_MDIRESTORE, (WPARAM)WndList[c], 0);
      SendMessage((HWND)WndList[c], WM_CLOSE, 0, 0);
      Successful = Successful && ClosedThisOne;
    }
  }

  return (Successful);
}

void RecreateLists(void)
{
  HWND cWnd;
  LPRefWndData WD;

  if (!ActiveFile)
    return;

  for (cWnd = ActiveFile->Window;
       cWnd != NULL;
       cWnd = GetNextWindow(cWnd, GW_HWNDNEXT))
  {
    WD = (LPRefWndData)GetWindowLong(cWnd, 0);

    if ((WD != BibData) || (!BibIsFormatted))
    {

      DestroyWindow(WD->ListWnd);
      WD->CreateMainList();
      WD->Refs->redisplay();
    }
  }
}

void NewClient(int CType, LPTSTR name)
{

  LPRefWndData Tmp;
  MDICREATESTRUCT mdiNew;

  // Create new window object
  Tmp = new TRefWndData;

  if (Tmp)
  {

    if (name)
    { // Loading file from command line

      lstrcpy(Tmp->FPath, name);

#ifndef WIN32
      // Make name uppercase
      AnsiUpper(Tmp->FPath);
#endif
    }

    if ((CType == cm_FileNew) ||
        ((CType == cm_FOpen) && ImpRefs(Tmp, CType, (name == NULL))) ||
        ((CType == cm_FImport) && ImpRefs(Tmp, CType, TRUE)) ||
        (CType == cm_BibCreate))
    {

      // fill MDI child structure
      if (CType == cm_BibCreate)
        Tmp->SrchFlag = FALSE;

      mdiNew.szClass = FILECLASS;
      mdiNew.hOwner = hinstCurrent;
      mdiNew.szTitle = _T("");
      mdiNew.x = mdiNew.y = mdiNew.cx = mdiNew.cy = CW_USEDEFAULT;
      mdiNew.style = 0;
      mdiNew.lParam = (long)Tmp;

      ActiveFile = Tmp;

      SendMessage(ClientWnd, WM_MDICREATE, 0, (LPARAM)&mdiNew);

      switch (CType)
      {

      case cm_BibCreate:
        BibData = Tmp;
        break;

      case cm_FImport:
        Tmp->FPath[0] = _T('\0');
        break; // ensures that it can only be saved with File, Save As
      }

      ActiveFile->NameWnd();

      RedrawWindow(Tmp->Window, NULL, NULL, RDW_FRAME | RDW_INVALIDATE | RDW_ALLCHILDREN);

      // If not bibliography, and auto view all is set, fill that listbox!
      if ((CType != cm_BibCreate) && (CType != cm_FileNew) && AutoShow)
        SendMessage(FrameWnd, WM_COMMAND, cm_RefAll, (LPARAM)Tmp);

#ifdef CC_TOOLBAR
      UpdateButtons();
#endif
    }
  }
  NewWnd = Tmp;
}

void Frame_OnCommand(HWND Window, int id, HWND hwndCtl, UINT codeNotify)
{
  LPRefFont f;
  LPTSTR p;
  int n;

  if ((id > cm_FirstOld) && (id < (cm_FirstOld + OLD_FILES + 1)))

    NewClient(cm_FOpen, OldFile[id - (cm_FirstOld + 1)]);

  else
  {

    switch (id)
    {

    case cm_FileNew:
    case cm_FOpen:
    case cm_FImport:
    case cm_BibCreate:
      NewClient(id, NULL);
      break;

    case cm_FSaveAs:
    case cm_FSave:
    case cm_FExport:
      ImpRefs(ActiveFile, id, (id == cm_FSave) ? FALSE : TRUE);
      break;

    case cm_FClose:
      SendMessage(ActiveFile->Window, WM_CLOSE, 0, 0);
      break;

    case WM_CUT:
    case WM_COPY:
    case WM_PASTE:
    case WM_UNDO:
      SendMessage(ActiveFile->Window, WM_COMMAND, id, 0);
      break;

    case cm_Print:
      PrintColl(FrameWnd, ActiveFile->Refs);
      break;

    case cm_RefNew:
      EditIt(-1);
      break;

    case cm_RefEdit:
      EditIt(ActiveFile->UpdateCurrent());
      break;

    case cm_EAuthor:
      EditAuth(ActiveFile->UpdateCurrent());
      break;

    case cm_RefDel:
      DeleteThem(ActiveFile, FALSE);
      break;

    case cm_RefSearch:
    case cm_ExpandSrch:
    case cm_NarrowSrch:
    case cm_RefAll:
    {
#ifdef CC_TOOLBAR
#ifdef WIN32
      if ((codeNotify < 2) || (hwndCtl == hWndToolbar)) // it's an accelerator, toolbar or menu command
#else
      if ((codeNotify < 2) || (CommCtrlAvail && (hwndCtl == hWndToolbar))) // it's an accelerator, toolbar or menu command
#endif
#else
      if (codeNotify < 2) // it's an accelerator or menu command
#endif
        ActiveFile->NewSearch(id);
      else
#ifdef WIN32
        ((LPRefWndData)hwndCtl)->NewSearch(id);
#else
        ((LPRefWndData)MAKELPARAM((UINT)(hwndCtl), (codeNotify)))->NewSearch(id);
#endif
      break;
    }

    case cm_AddToBib:
      SendMessage(ActiveFile->Window, WM_COMMAND, id, 0);
      break;

    case cm_AddKeyword:
    {
      if (ActiveFile && ListBox_GetSelCount(ActiveFile->ListWnd) > 0)
        AddKeyword(ActiveFile);
      else
        AddKeyword(NULL);
      break;
    }

    case cm_HelpAbout:
      About();
      break;

    case cm_HelpOnHelp:
      WinHelp(Window, HelpName, HELP_HELPONHELP, 0);
      break;

    case cm_HelpIndex:
#ifdef WIN32
      WinHelp(Window, HelpName, HELP_FINDER, 0);
      break;
#else
      WinHelp(Window, HelpName, HELP_INDEX, 0);
      break;
#endif

    case cm_FExit:
      PostMessage(Window, WM_CLOSE, 0, 0);
      break;

    case cm_OptBak:
      MakeBak = !MakeBak;
      break;

    case cm_ListOpt:
      ListOpts();
      break;

    case cm_Confirm:
      ConfOpts();
      break;

    case cm_OInput:
      InputOpts();
      break;

    case cm_EditFont:
    case cm_PrintFont:
    case cm_DataFont:
    {

      switch (id)
      {
      case cm_EditFont:
        f = EditFnt;
        p = DStrEditor;
        break;
      case cm_PrintFont:
        f = PrnFnt;
        p = DStrPrint;
        break;
      case cm_DataFont:
        f = ListFnt;
        p = DStrList;
        break;
      }

      if (f == NULL)
      {

        f = new TRefFont(TRUE, FrameWnd);
        n = (f != NULL);
      }
      else
        n = f->Edit(FrameWnd);

      if (n)
      {
        f->PutToIni(DStrFonts, p);

        switch (id)
        {
        case cm_DataFont:
        {
          f->SetListParms(FrameWnd);
          RecreateLists();
          break;
        }

        case cm_PrintFont:
        {
          if (BibData && BibIsFormatted)
#ifndef USE_RTF
            SetWindowFont(BibData->ListWnd, f->SFont, TRUE);
#else
            BibData->Format(BibIsFormatted);
#endif
          break;
        }
        }
      }
      break;
    }

    case cm_OptSrch:
    {
      if ((SrchOpts() == IDOK) && ActiveFile)
        ActiveFile->NameWnd();
      break;
    }

    case cm_BibCol:
      DoBibColDlg();
      break;

    case cm_BFormat:
      BibFormats();
      break;

    case cm_BView:
    {
      BibIsFormatted = !BibIsFormatted;

#ifdef CC_TOOLBAR
      SendMessage(hWndToolbar, TB_CHECKBUTTON, cm_BView, MAKELONG(BibIsFormatted, 0));
#endif

      if (BibData)
        BibData->Format(BibIsFormatted);

      break;
    }

    case cm_FileFormat:
      ChooseFileFormat(0);
      break;

    case cm_AutoShowIt:
      AutoShow = !AutoShow;
      break;

    case cm_OptSort:
      SortOpts();
      break;

    case cm_SelectAll:
    {
      if ((ActiveFile == BibData) && BibIsFormatted)
#ifdef USE_RTF
        Edit_SetSel(((hRichEdit)BibData->ListWnd)->hWnd, 0, -1);
#else
        Edit_SetSel(BibData->ListWnd, 0, -1);
#endif
      else
      {
        ListBox_SelItemRange(ActiveFile->ListWnd, TRUE, 0, ActiveFile->Refs->count);
#ifdef CC_TOOLBAR
        UpdateButtons();
#endif
      }
      break;
    }

    case cm_Tile:
      SendMessage(ClientWnd, WM_MDITILE, MDITILE_SKIPDISABLED, 0);
      break;

    case cm_Cascade:
      SendMessage(ClientWnd, WM_MDICASCADE, MDITILE_SKIPDISABLED, 0);
      break;

    case cm_Arrange:
      SendMessage(ClientWnd, WM_MDIICONARRANGE, 0, 0);
      break;

    case cm_Language:
      SetLanguage(NULL);
      break;

#ifndef CUSTOM
    case cm_Register:
    {
      Registered = (DialogBox(ResInstance, _T("REGISTER"), Window, RegProc) == IDOK);
      break;
    }
#endif

#ifdef WIN32
    default:
      DefFrameProc(Window,
                   ClientWnd,
                   WM_COMMAND,
                   MAKEWPARAM((UINT)(id), (UINT)(codeNotify)),
                   (LPARAM)(HWND)(hwndCtl));
#else
    default:
      DefFrameProc(Window,
                   ClientWnd,
                   WM_COMMAND,
                   id,
                   MAKELPARAM(hwndCtl, codeNotify));
#endif
    }
  }
  DefaultStatus();
}

void Frame_OnEditClosing(HWND Dlg, LPRef ARef)
// Redisplays a reference after editing in all owning windows.
{
  _TCHAR AClass[20];
  HWND cWnd;
  LPRefWndData WD;
  long N;

  if (!ActiveFile)
    return;

  if (ARef->Flags & RF_NeedsInserting)
  {
    WD = ARef->OpenedFrom;
    if ((N = WD->Refs->insert(ARef)) >= 0)
    {
      WD->Refs->display(N);
      if (WD->ListFlags & FLG_SELECT_NEW)
        ListBox_SetSel(WD->ListWnd, TRUE, N);
      WD->NeedsSaving = TRUE;
    }

    if (--ARef->links)
    {
      ARef->OpenedFrom = NULL;
      ARef->Flags &= ~RF_NeedsInserting;
    }
    else
      delete ARef;
  }
  else
  {
    ARef->links++;

    for (cWnd = ActiveFile->Window;
         cWnd != NULL;
         cWnd = GetNextWindow(cWnd, GW_HWNDNEXT))
    {
      GetClassName(cWnd, AClass, sizeof(AClass));
      if (lstrcmp(AClass, FILECLASS) == 0)
      {
        WD = (LPRefWndData)GetWindowLong(cWnd, 0);
        if ((N = WD->Refs->indexofpointer(ARef)) != -1)
        {

          WD->NeedsSaving = TRUE;
          WD->Refs->atremove(N);
          ListBox_DeleteString(WD->ListWnd, N);
          N = WD->Refs->insert(ARef);
          WD->Refs->display(N);

#ifndef WIN32
          // Don't reset the selection if the reference has moved out of the scroll box.
          if (N > 0 && N < 8192)
#endif
            ListBox_SetSel(WD->ListWnd, TRUE, N);
        }
      }
    }

    ARef->links--;
  }
}

void Frame_OnInitMenuPopup(HWND Window, HMENU hMenu, int item, BOOL fSystemMenu)
{
  int n;
  HMENU FileMenu;
  _TCHAR t[MAX_PATH];

  // grey menu items as they appear
  if (!fSystemMenu)
  {

    if (IsMaximized) // compensate for presence of system menu
      item--;

    switch (item)
    {

    case 0:
    { // File menu
      if (OldFile[0])
      {

        FileMenu = GetSubMenu(FMenu, item - IsMaximized);

        do
        {
        } while (DeleteMenu(FileMenu, 14, MF_BYPOSITION));

        AppendMenu(FileMenu, MF_SEPARATOR, 0, NULL);

        for (n = 1; (n <= OLD_FILES) && (OldFile[n - 1]); n++)
        {
          wsprintf(t, _T("&%i "), n);
          lstrcat(t, OldFile[n - 1]);
          AppendMenu(FileMenu, MF_STRING, cm_FirstOld + n, t);
          EnableMenuItem(FMenu, cm_FirstOld + n, (Clients < MAX_FILES) ? MF_ENABLED : MF_GRAYED);
        }
      }

      EnableMenuItem(FMenu, cm_FImport, (Clients < MAX_FILES) ? MF_ENABLED : MF_GRAYED);
      EnableMenuItem(FMenu, cm_FileNew, (Clients < MAX_FILES) ? MF_ENABLED : MF_GRAYED);
      EnableMenuItem(FMenu, cm_FOpen, (Clients < MAX_FILES) ? MF_ENABLED : MF_GRAYED);
      EnableMenuItem(FMenu, cm_FSaveAs, (ActiveFile && (ActiveFile->Refs->count > 0)) ? MF_ENABLED : MF_GRAYED);
      EnableMenuItem(FMenu, cm_FExport, (ActiveFile && (ActiveFile->Refs->count > 0)) ? MF_ENABLED : MF_GRAYED);
      EnableMenuItem(FMenu, cm_FClose, ActiveFile ? MF_ENABLED : MF_GRAYED);
      EnableMenuItem(FMenu, cm_FSave, (ActiveFile && (ActiveFile->Refs->count > 0) && (ActiveFile != BibData) && (ActiveFile->FPath[0] != _T('\0'))) ? MF_ENABLED : MF_GRAYED);
      EnableMenuItem(FMenu, cm_Print, (ActiveFile && (ActiveFile->Refs->count > 0)) ? MF_ENABLED : MF_GRAYED);

      break;
    }

    case 1:
    { // EditMenu

      if ((ActiveFile) && (ActiveFile == BibData) && BibIsFormatted)
      {

#ifdef USE_RTF
        EnableMenuItem(FMenu, WM_UNDO, Edit_CanUndo(((hRichEdit)BibData->ListWnd)->hWnd) ? MF_ENABLED : MF_GRAYED);
#else
        EnableMenuItem(FMenu, WM_UNDO, Edit_CanUndo(BibData->ListWnd) ? MF_ENABLED : MF_GRAYED);
#endif
        EnableMenuItem(FMenu, WM_PASTE, IsClipboardFormatAvailable(CF_TEXT) ? MF_ENABLED : MF_GRAYED);
        EnableMenuItem(FMenu, WM_CUT, MF_ENABLED);
        EnableMenuItem(FMenu, WM_COPY, MF_ENABLED);
      }
      else
      {

        if (ActiveFile)
          n = ListBox_GetSelCount(ActiveFile->ListWnd);

        EnableMenuItem(FMenu, WM_UNDO, MF_GRAYED);
        EnableMenuItem(FMenu, WM_CUT, (ActiveFile && (n != 0)) ? MF_ENABLED : MF_GRAYED);
        EnableMenuItem(FMenu, WM_COPY, (ActiveFile && (n != 0)) ? MF_ENABLED : MF_GRAYED);
        EnableMenuItem(FMenu, WM_PASTE, (ActiveFile && CutPasteColl) ? MF_ENABLED : MF_GRAYED);
      }
      break;
    }

    case 2:
    { // Reference menu

      EnableMenuItem(FMenu, cm_RefNew, (ActiveFile && (ActiveFile != BibData)) ? MF_ENABLED : MF_GRAYED);
      EnableMenuItem(FMenu, cm_SelectAll, (ActiveFile && ActiveFile->Refs->count) ? MF_ENABLED : MF_GRAYED);

      n = 0;

      if (ActiveFile)
      {
        if ((!BibIsFormatted) || (ActiveFile != BibData))
          n = ListBox_GetSelCount(ActiveFile->ListWnd);
      }

      EnableMenuItem(FMenu, cm_AddToBib, (ActiveFile && (n != 0) && (ActiveFile != BibData)) ? MF_ENABLED : MF_GRAYED);
      EnableMenuItem(FMenu, cm_RefDel, (ActiveFile && (n != 0)) ? MF_ENABLED : MF_GRAYED);

#ifdef MODAL_EDIT
      EnableMenuItem(FMenu, cm_EAuthor, (ActiveFile && (n == 1) && (ActiveFile != BibData)) ? MF_ENABLED : MF_GRAYED);
      EnableMenuItem(FMenu, cm_RefEdit, (ActiveFile && (n == 1)) ? MF_ENABLED : MF_GRAYED);

#else
      if (!ActiveFile || (n != 1))
      {
        EnableMenuItem(FMenu, cm_RefEdit, MF_GRAYED);
        EnableMenuItem(FMenu, cm_EAuthor, MF_GRAYED);
      }
      else
      {
        n = ListBox_GetCurSel(ActiveFile->ListWnd);
        if (((LPRef)(ActiveFile->Refs->at(n)))->hwndEditor == NULL)
        {
          EnableMenuItem(FMenu, cm_RefEdit, MF_ENABLED);
          EnableMenuItem(FMenu, cm_EAuthor, (ActiveFile == BibData) ? MF_GRAYED : MF_ENABLED);
        }
        else
        {
          EnableMenuItem(FMenu, cm_RefEdit, MF_GRAYED);
          EnableMenuItem(FMenu, cm_EAuthor, MF_GRAYED);
        }
      }
#endif

      break;
    }

    case 3:
    { // Search menu

#ifdef WIN32
      EnableMenuItem(FMenu, cm_RefAll, ActiveFile ? MF_ENABLED : MF_GRAYED);
#else
      EnableMenuItem(FMenu, cm_RefAll, (ActiveFile && (ActiveFile->Refs->count < 8192)) ? MF_ENABLED : MF_GRAYED);
#endif
      EnableMenuItem(FMenu, cm_RefSearch, ActiveFile ? MF_ENABLED : MF_GRAYED);

      n = (ActiveFile && ActiveFile->SrchPat) ? MF_ENABLED : MF_GRAYED;

      EnableMenuItem(FMenu, cm_NarrowSrch, n);
      EnableMenuItem(FMenu, cm_ExpandSrch, n);

      break;
    }

    case 4:
    { // Options menu

      EnableMenuItem(FMenu, cm_BView, BibData ? MF_ENABLED : MF_GRAYED);
      CheckMenuItem(FMenu, cm_BView, BibIsFormatted ? MF_CHECKED : MF_UNCHECKED);
      CheckMenuItem(FMenu, cm_OptBak, MakeBak ? MF_CHECKED : MF_UNCHECKED);
      CheckMenuItem(FMenu, cm_AutoShowIt, AutoShow ? MF_CHECKED : MF_UNCHECKED);

      break;
    }

    case 5:
    { // Window menu

      n = Clients ? MF_ENABLED : MF_GRAYED;

      EnableMenuItem(FMenu, cm_Cascade, n);
      EnableMenuItem(FMenu, cm_Arrange, n);
      EnableMenuItem(FMenu, cm_Tile, n);

      break;
    }

#ifndef CUSTOM
    case 6:
    { // Help menu

      if (!Registered)
      {
        FileMenu = GetSubMenu(FMenu, (IsMaximized ? item + 1 : item));

        do
        {
        } while (DeleteMenu(FileMenu, 4, MF_BYPOSITION));

        LoadString(ResInstance, cm_Register, t, sizeof(t) / sizeof(_TCHAR));
        AppendMenu(FileMenu, MF_STRING, cm_Register, t);
      }
      break;
    }
#endif
    } // switch lparam
  }
}

void Frame_OnMenuSelect(HWND hwnd, HMENU hmenu, int item, HMENU hmenuPopup, UINT flags)
{
  _TCHAR t[RES_STR];

#ifndef CC_STATUS
  HDC StDC;

  // draw description string in status bar
  StDC = GetDC(hwnd);
  SelectBrush(StDC, GetStockObject(LTGRAY_BRUSH));

  Rectangle(StDC, StatusRect.left, StatusRect.top, StatusRect.right, StatusRect.bottom);
#endif

  if ((flags & (MF_POPUP | MF_SYSMENU)) == 0)
  {

    if (!LoadString(ResInstance, item, t, sizeof(t) / sizeof(_TCHAR)))
      t[0] = _T('\0');
  }
  else
    t[0] = _T('\0');

#ifndef CC_STATUS
  DrawStatus(StDC, t);
  ReleaseDC(hwnd, StDC);
#else
  DrawStatus(t, STATUS_MESSAGE_SECTION);
#endif
}

void Frame_OnSize(HWND hwnd, UINT state, int cx, int cy)
{

#ifdef CC_TOOLBAR
  RECT ToolRect;
#endif

#ifdef CC_STATUS
  RECT StatusRect;
#endif

#ifdef CC_TOOLBAR

#ifdef WIN32
  SendMessage(hWndToolbar, TB_AUTOSIZE, 0L, 0L);
#else
  if (CommCtrlAvail)
  {
    GetWindowRect(hWndToolbar, &ToolRect);
    MoveWindow(hWndToolbar, 0, 0, cx, ToolRect.bottom - ToolRect.top, TRUE);
#endif

  GetWindowRect(hWndToolbar, &ToolRect);

#ifdef CC_STATUS
  MoveWindow(hWndStatus, 0, cy - 10, cx, cy, TRUE);
  // Set the rectangles for the multiple parts of the status bar.
  // Make each 1/4 of the width of the client area.
  aWidths[0] = -1; // cx / 4;
  SendMessage(hWndStatus, SB_SETPARTS, 4, (LPARAM)aWidths);
  GetWindowRect(hWndStatus, &StatusRect);

  MoveWindow(
      ClientWnd,
      0,
      ToolRect.bottom - ToolRect.top,
      cx,
      cy - ((StatusRect.bottom - StatusRect.top) + (ToolRect.bottom - ToolRect.top)),
      TRUE);
#else // not CC_STATUS

#ifndef WIN32
  }
#endif

  StatusRect.bottom = cy;
  StatusRect.top = cy - StatusHeight - 6;
  StatusRect.right = cx;

#ifdef WIN32
  MoveWindow(
      ClientWnd,
      0,
      ToolRect.bottom - ToolRect.top,
      cx,
      cy - ((StatusHeight + 6) + (ToolRect.bottom - ToolRect.top)),
      TRUE);
#else
    MoveWindow(
        ClientWnd,
        0,
        CommCtrlAvail ? (ToolRect.bottom - ToolRect.top) : 0,
        cx,
        cy - ((StatusHeight + 6) + (CommCtrlAvail ? (ToolRect.bottom - ToolRect.top) : 0)),
        TRUE);
#endif // WIN32

#endif // CC_STATUS

#else // !CC_TOOLBAR
  // Resize client window with frame window
  StatusRect.bottom = cy;
  StatusRect.top = cy - StatusHeight - 6;
  StatusRect.right = cx;

  MoveWindow(ClientWnd, 0, 0, cx, StatusRect.top, TRUE);
#endif

  InvalidateRect(FrameWnd, &StatusRect, TRUE);
}

void inline Frame_OnEnable(HWND hwnd, BOOL fEnable)
{
  SetFocus(ActiveFile ? ActiveFile->ListWnd : FrameWnd);
}

void inline Frame_OnPaint(HWND hwnd)
{
  Paint();
}

#ifdef WIN32
BOOL Frame_OnCreate(HWND hwnd, CREATESTRUCT *lpCreateStruct)
{
#else
BOOL inline Frame_OnCreate(HWND hwnd, CREATESTRUCT *lpCreateStruct)
{
#endif

  HereWeGo();

#ifdef CC_TOOLBAR
  // Create toolbar
#ifdef WIN32
  hWndToolbar = CreateToolbarEx(
      hwnd,                                                 // parent
      WS_CHILD | WS_BORDER | WS_VISIBLE | TBSTYLE_TOOLTIPS, // window style
      IDB_TOOLBAR,                                          // toolbar id
      14,                                                   // number of bitmaps
      hinstCurrent,                                         // mod instance
      IDB_TOOLBAR,                                          // resource ID for bitmap
      (LPCTBBUTTON)&tbButtons,                              // address of buttons
      TOOL_BUTTON_NO,                                       // number of buttons
      16, 16,                                               // width & height of buttons
      16, 16,                                               // width & height of bitmaps
      sizeof(TBBUTTON));                                    // structure size
#else

  if (CommCtrlAvail == 0)
    return TRUE;

  hWndToolbar = CreateToolbarDynamic(
      hwnd,
      WS_CHILD | WS_BORDER | WS_VISIBLE,
      IDB_TOOLBAR,
      14,
      hinstCurrent,
      IDB_TOOLBAR,
      (LPTBBUTTON)&tbButtons,
      TOOL_BUTTON_NO);
#endif

  // update toolbar
  UpdateButtons();

  // put us in the clipboard chain to watch for text arrivals
  NextClipChain = SetClipboardViewer(hwnd);
#endif // CC_TOOLBAR

#ifdef CC_STATUS
  // Create status bar
  hWndStatus = CreateWindowEx(
      0L,                                               // extended style
      STATUSCLASSNAME,                                  // create status bar
      _T(""),                                           // window title
      WS_CHILD | WS_BORDER | WS_VISIBLE | SBS_SIZEGRIP, // window styles
      0, 0, 0, 0,                                       // x, y, width, height
      hwnd,                                             // parent window
      (HMENU)ID_STATUSBAR,                              // ID
      hinstCurrent,                                     // instance
      NULL);                                            // window data

  // Break the status bar into four parts.
  SendMessage(hWndStatus, SB_SETPARTS, STATUS_FIELDS, (LPARAM)aWidths);

#endif // CC_STATUS

  return TRUE;
}

void inline Frame_OnClose(HWND hwnd)
{

  if (CloseAllFiles())
    DestroyWindow(hwnd);
}

BOOL inline Frame_OnQueryEndSession(HWND hwnd)
{
  return CloseAllFiles();
}

void inline Frame_OnActivate(HWND hwnd, UINT state, HWND hwndActDeact, BOOL fMinimized)
{

  if ((state != WA_INACTIVE) && ActiveFile)
    SetFocus(ActiveFile->ListWnd);
  else
    FORWARD_WM_ACTIVATE(hwnd, state, hwndActDeact, fMinimized, DefWindowProc);
}

void inline Frame_OnDestroy(HWND hwnd)
{
#ifdef CC_TOOLBAR
  ChangeClipboardChain(hwnd, NextClipChain);
#endif
  BuggerOff();
}

void inline Frame_OnSysColorChange(HWND hwnd)
{
#ifndef WIN32
  if (IsCtl3D)
    Ctl3dColorChange();
#endif
  CreateBitmaps();
}

BOOL Frame_OnSetCursor(HWND hwnd, HWND hwndCursor, UINT codeHitTest, UINT msg)
{
  int IsTrue, MButton;

  if (!IsWindowEnabled(hwnd))
  {
    SetCursor(CCursor);
    return TRUE;
  }

  if (FromWnd)
  {
    IsTrue = SwapMouseButton(TRUE);
    SwapMouseButton(IsTrue);
    MButton = (IsTrue) ? VK_LBUTTON : VK_RBUTTON;

    // Is it down?
    if (GetAsyncKeyState(MButton) & 0xC000)
    {

#ifdef WIN32
      SetCursor(LoadCursor(0, IDC_NO));
#else
      SetCursor(LoadCursor(0, IDC_ARROW));
#endif
      return TRUE;
    }
  }

  return DefFrameProc(hwnd,
                      ClientWnd,
                      WM_SETCURSOR,
                      (WPARAM)(HWND)(hwndCursor),
                      MAKELPARAM((codeHitTest), (msg)));
}

LRESULT CALLBACK RefFrameProc(HWND Window, UINT Msg, WPARAM wParam, LPARAM lParam)
{

#ifdef CC_TOOLBAR
#ifdef WIN32
  _TCHAR szBuf[RES_STR];
  LPTOOLTIPTEXT lpToolTipText;
#endif
//  int n;
#endif

  if (Msg == HlpMsg)
  {

    WinHelp(Window, HelpName, HELP_CONTEXT, 8);
    return (0);
  }
  else
  {

    switch (Msg)
    {

      HANDLE_MSG(Window, WM_COMMAND, Frame_OnCommand);
      HANDLE_MSG(Window, WM_INITMENUPOPUP, Frame_OnInitMenuPopup);
      HANDLE_MSG(Window, WM_SIZE, Frame_OnSize);
      HANDLE_MSG(Window, WM_MENUSELECT, Frame_OnMenuSelect);
      HANDLE_MSG(Window, WM_ENABLE, Frame_OnEnable);
      HANDLE_MSG(Window, WM_PAINT, Frame_OnPaint);
      HANDLE_MSG(Window, WM_CREATE, Frame_OnCreate);
      HANDLE_MSG(Window, WM_CLOSE, Frame_OnClose);
      HANDLE_MSG(Window, WM_QUERYENDSESSION, Frame_OnQueryEndSession);
      HANDLE_MSG(Window, WM_DESTROY, Frame_OnDestroy);
      HANDLE_MSG(Window, WM_SYSCOLORCHANGE, Frame_OnSysColorChange);
      HANDLE_MSG(Window, WM_SETCURSOR, Frame_OnSetCursor);
      HANDLE_MSG(Window, WM_ACTIVATE, Frame_OnActivate);

    case WM_EDITCLOSING:
    {
      Frame_OnEditClosing((HWND)wParam, (LPRef)lParam);
      return (0);
    }

#ifdef WIN32
    case WM_COPYDATA:
    {

      if (((COPYDATASTRUCT *)lParam)->dwData == cm_FOpen)
      {

        NewClient(cm_FOpen, (LPTSTR)((COPYDATASTRUCT *)lParam)->lpData);
        return 0;
      }
      else
        return DefFrameProc(Window, ClientWnd, Msg, wParam, lParam);
    }
#else

    case WM_NEWDATA:
    {

      if (Clients < MAX_FILES)
        NewClient(cm_FOpen, (LPTSTR)lParam);
      else
        ErrorBox(FrameWnd, err_MaxFiles);

      return (0);
    }

#endif

#ifdef CC_TOOLBAR
    case WM_LBUTTONDBLCLK:
      // Double-click on the toolbar -- display the customization dialog.
      SendMessage(hWndToolbar, TB_CUSTOMIZE, 0L, 0L);
      return 0;

    case WM_CHANGECBCHAIN:
      if ((HWND)wParam == NextClipChain)
        NextClipChain = (HWND)lParam;
      return 0;

    case WM_DRAWCLIPBOARD:

      // Pass the message on
      if ((wParam == 0) || NextClipChain)
        SendMessage(NextClipChain, Msg, wParam, lParam);

#ifndef WIN32
      if (CommCtrlAvail)
#endif

        UpdateClipButtons();

      return 0;

#ifdef WIN32
    case WM_NOTIFY:
      switch (((LPNMHDR)lParam)->code)
      {

      case TBN_GETBUTTONINFO:
        // The toolbar needs information about a button.
        return FALSE;
        break;

      case TTN_NEEDTEXT:

        lpToolTipText = (LPTOOLTIPTEXT)lParam;
        LoadString(ResInstance,
                   lpToolTipText->hdr.idFrom, // string ID == cmd ID
                   szBuf,
                   sizeof(szBuf) / sizeof(_TCHAR));
        lpToolTipText->lpszText = szBuf;

        break;

      default:
        return TRUE;
        break;
      }
      return 0L;
      break;
#endif // WIN32

#endif // CC_TOOLBAR

    default:
    {
      return (DefFrameProc(Window, ClientWnd, Msg, wParam, lParam));
    }
    } // case Msg
  } // Msg==HlpMsg
}
