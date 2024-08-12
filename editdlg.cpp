#include "inc/globals.h"
#include "inc/reffont.h"
#include "inc/refprn.h"
#include "rimpexp/rimpexp.h"
#include "inc/rcutpast.h"
#include "inc/editdlg.h"
#include "inc/jlistdlg.h"

HFONT ArrowFnt;

// The size of the editing dialog
TESz NEAR EditSize;

// maxima dependent on resources
int max_r, max_b;

// Current editor for the message loop
HWND CurrentEditor;

// controls that must be moved when resizing EDITREF dialogs
int CtrlID[MAX_FIELDS] = {id_Title, id_Journal, id_Volume, id_Number, id_Pages, id_Text, id_Keywords, id_Publisher, id_City, id_Editor};

// These are the Edit dialog control IDs that need to be moved when the dialog
// is resized.
int ctls_to_move[23][2] = {
    {id_Text, -1},
    {id_Title, 0},
    {id_Number, 0},
    {idt_VolNo, 0},
    {id_Journal, 0},
    {idt_BookJou, 0},
    {idt_Volume, 0},
    {id_Volume, 0},
    {idt_Pages, 0},
    {id_Pages, 0},
    {idt_Publisher, 0},
    {id_Publisher, 0},
    {idt_Editor, 0},
    {id_Editor, 0},
    {idt_City, 0},
    {id_City, 0},
    {idt_Keywords, 0},
    {id_Keywords, 0},
    {IDOK, 0},
    {id_OkNew, 0},
    {IDCANCEL, 0},
    {id_GPrev, 0},
    {id_GNext, 0}};

void FillJList(HWND Dlg, LPRef Tmp)
{
  _TCHAR um[6], t[RES_STR];
  int Curl, n;
  HWND cb;

  cb = GetDlgItem(Dlg, id_Journal);
  GetWindowText(cb, t, sizeof(t));
  ComboBox_ResetContent(cb);
  SetWindowText(cb, t);

  n = GetConfigInt(INIKey[Tmp->reftype], _T("Number"), 0);

  for (Curl = 1; Curl <= n; Curl++)
  {
    _itot(Curl, um, 10);
    GetConfigStr(t, sizeof(t), INIKey[Tmp->reftype], um, _T("Configuration Error"));
    ComboBox_AddString(cb, t);
  }
}

void Buf2Dlg(HWND Dlg, LPRef ARef)
{
  LPTSTR *P, T, tmp;
  int n, goP, goN;
  LPRef r;

  ARef->Flags |= (RF_DontUpdate | RF_DontResort);

  FillJList(Dlg, ARef);

  tmp = (LPTSTR)malloc(SCRATCH_SIZE);

  ARef->GetSortStr(tmp, 1, ActiveFile->Refs->s1);

  T = _tcsrchr(tmp, _T('\t'));

  if (T)
    *T = _T(' ');

  SetWindowText(Dlg, tmp);

  LoadString(ResInstance, str_Journal + ARef->reftype, tmp, SCRATCH_SIZE / sizeof(_TCHAR));
  SetDlgItemText(Dlg, idt_BookJou, tmp);

  free(tmp);

  P = &ARef->title;

  for (n = 0; n < MAX_FIELDS; n++)
    SetDlgItemText(Dlg, CtrlID[n], P[n] ? P[n] : _T(""));

  EnableWindow(GetDlgItem(Dlg, id_OkNew), (ARef->OpenedFrom) && (ARef->OpenedFrom != BibData));

  goP = goN = FALSE;

  if ((ARef->OpenedFrom) && (ARef->Flags & RF_CanBrowse))
  {
    for (n = (ARef->OpenedFrom->Refs->indexof(ARef) + 1);
         n < (ARef->OpenedFrom->Refs->count);
         n++)
    {
      r = (LPRef)ARef->OpenedFrom->Refs->at(n);
      if (r->hwndEditor == NULL)
      {
        n = ARef->OpenedFrom->Refs->count;
        goN = TRUE;
      }
    }

    for (n = ARef->OpenedFrom->Refs->indexof(ARef) - 1;
         n >= 0;
         n--)
    {
      r = (LPRef)ARef->OpenedFrom->Refs->at(n);
      if (r->hwndEditor == NULL)
      {
        n = -1;
        goP = TRUE;
      }
    }
  }

  EnableWindow(GetDlgItem(Dlg, id_GNext), goN);
  EnableWindow(GetDlgItem(Dlg, id_GPrev), goP);

  ARef->Flags &= ~(RF_NeedsUpdating | RF_DontUpdate);
}

void Dlg2Buf(HWND Dlg, LPRef ARef)
{
  LPTSTR *Ptr, p, t;
  int n;

  t = (LPTSTR)malloc(SCRATCH_SIZE);

  Ptr = &ARef->title;

  for (n = 0; n < MAX_FIELDS; n++)
  {
    if (Ptr[n])
    {
      free(Ptr[n]);
      Ptr[n] = NULL;
    }

    if (GetDlgItemText(Dlg, CtrlID[n], t, SCRATCH_SIZE - 1))
    {
      if ((n == FLD_TITLE) || (n == FLD_PUBLISHER) || (n == FLD_CITY))
      {
        for (p = _tcschr(t, _T('\r')); p != NULL; p = _tcschr(p, _T('\r')))
        {
          p[0] = _T(' ');
          p[1] = _T(' ');
        }
      }

      Ptr[n] = _tcsdup(t);
    }
  }

  if (ActiveFile)
  {
    ARef->GetSortStr(t, FLG_SORT_INTERNAL, ActiveFile->Refs->s1);
    free(ARef->sortstr);
    ARef->sortstr = _tcsdup(t);
  }

  free(t);

  ARef->Flags &= ~RF_NeedsUpdating;

  PostMessage(FrameWnd, WM_EDITCLOSING, (WPARAM)Dlg, (LPARAM)ARef);
}

void EditIt(long N)
{
  LPRef Tmp;

  if (N != -1)
  {

    Tmp = (LPRef)(ActiveFile->Refs->at(N));

#ifndef MODAL_EDIT
    if (Tmp->hwndEditor)
    {
      EditData *ew = (EditData *)GetWindowLong(Tmp->hwndEditor, DWL_USER);
      ShowWindow(Tmp->hwndEditor, ew->EditSize.ismax ? SW_SHOWMAXIMIZED : SW_RESTORE);
    }
    else
    {
#endif
      Tmp->OpenedFrom = ActiveFile;
#ifdef MODAL_EDIT
      Tmp->Edit(RF_CanBrowse | RF_EditModal);
#else
    Tmp->Edit(RF_CanBrowse);
  }
#endif
    }
    else
    {
      // Creating a new reference
      Tmp = new TRef;

      if (!Tmp)
        return;

      // Edit authors, and abandon if cancelled
      if (Tmp->ETitle() != IDOK)
        delete Tmp;
      else
      {
        // Edit data fields, incrementing refcount to prevent it being deleted
        Tmp->OpenedFrom = ActiveFile;
        Tmp->Flags |= RF_NeedsInserting;
        Tmp->Edit(0);
      }
    }
#ifdef MODAL_EDIT
    // Make sure listbox still has input focus
    SetFocus(ActiveFile->ListWnd);
#endif
  }

  void CopyFmted(HWND Dlg, int DoWhat, LPRef ARef)
  {
    HANDLE AHnd;
    LPTSTR Ptr;
    LPTSTR t1, t2;
    int IsRTF;

    t1 = (LPTSTR)malloc(SCRATCH_SIZE);
    t2 = (LPTSTR)malloc(SCRATCH_SIZE);

    ARef->FormatRef(t2);
    _stprintf(t1, _T("%s%s%s"), FmtPrefix, t2, FmtSuffix);

    IsRTF = (int)_tcsstr(t1, "\\rtf");

    free(t2);

    AHnd = GlobalAlloc(GMEM_MOVEABLE, (lstrlen(t1) + 1) * sizeof(_TCHAR));

    if (AHnd)
    {
      Ptr = (_TCHAR *)GlobalLock(AHnd);
      lstrcpy(Ptr, t1);

      if (DoWhat == cm_Print)
      {
        GetWindowText(Dlg, t1, SCRATCH_SIZE - 1);
        PrintText(Dlg, Ptr, t1);
        GlobalUnlock(AHnd);
        GlobalFree(AHnd);
      }
      else
      {
        GlobalUnlock(AHnd);
        EmptyClipboard();
        if (IsRTF)
        {
          SetClipboardData(49279, AHnd);
          SetClipboardData(49398, AHnd);
        }
        else
        {
          SetClipboardData(CF_TEXT, AHnd);
        }
        CloseClipboard();
      }
    }
    free(t1);
  }

  void GotoRef(HWND Wnd, int toadd)
  {
    long N, no;
    _TCHAR t1[RES_STR], t2[RES_STR];
    EditData *ew;
    LPRefWndData f;
    LPRef old, nw;

    ew = (EditData *)GetWindowLong(Wnd, DWL_USER);

    old = ew->ThisRef;
    f = old->OpenedFrom;

    if (!f)
    {
      // This window has been orphaned, disable buttons and do nothing
      EnableWindow(GetDlgItem(Wnd, id_GPrev), FALSE);
      EnableWindow(GetDlgItem(Wnd, id_GNext), FALSE);
      return;
    }

    // Store index of currently edited reference.
    N = no = f->Refs->indexof(old);

    // Keep adding or subtracting until we find a
    // reference that is not being edited.
    do
    {
      N += toadd;

      if ((N < 0) || (N == f->Refs->count))
      {
        // There isn't one!  Disable the button and return
        EnableWindow(GetDlgItem(Wnd, N == 1 ? id_GNext : id_GPrev), FALSE);
        return;
      }
      else
        nw = (LPRef)(f->Refs->at(N));

    } while (nw->hwndEditor);

    LoadString(ResInstance, wrn_Warning, t2, RES_STR);
    LoadString(ResInstance, wrn_RefDirty, t1, RES_STR);

    // Update old one if necessary
    if ((old->Flags & RF_NeedsUpdating) &&
        (MessageBox(Wnd, t1, t2, MB_YESNO | MB_ICONSTOP) == IDYES))
      Dlg2Buf(Wnd, old);

    // Disable selection of old and select the new
    ListBox_SetSel(f->ListWnd, FALSE, no);
    ListBox_SetSel(f->ListWnd, TRUE, N);

    // Decrement link count
    old->links--;

    // Nullify links to windows
    old->hwndEditor = NULL;
    old->OpenedFrom = NULL;

    // ...add links to the new reference
    ew->ThisRef = nw;
    nw->links++;
    nw->hwndEditor = Wnd;
    nw->Flags = (nw->Flags & ~RF_NeedsInserting) | RF_CanBrowse;
    nw->OpenedFrom = f;

    // and trabsfer its contents to the window
    Buf2Dlg(Wnd, nw);

#ifdef MODAL_EDIT
    Current = nw;
#endif
  }

  void Edit_OnInitMenuPopup(HWND hwnd, HMENU hMenu, int item, BOOL fSystemMenu)
  {
    int n;
    BOOL IsTrue;
    EditData *ew;

    ew = (EditData *)GetWindowLong(hwnd, DWL_USER);

    switch (item)
    {

    case 0:
    {
      IsTrue = (BibData && (BibData->Refs->indexof(ew->ThisRef) != -1));
      EnableMenuItem(hMenu, cm_AddToBib, ((ActiveFile == BibData) || (ew->ThisRef->Flags & RF_NeedsInserting)) ? MF_GRAYED : MF_ENABLED);
      EnableMenuItem(hMenu, cm_AddKeyword, ((ActiveFile == BibData) || IsTrue) ? MF_GRAYED : MF_ENABLED);
      CheckMenuItem(hMenu, cm_AddToBib, IsTrue ? MF_CHECKED : MF_UNCHECKED);
      break;
    }

    case 1:
    {
      n = (Edit_CanUndo(GetFocus()) ? 1 : 0);
      EnableMenuItem(hMenu, 0, n | MF_BYPOSITION);
      n = (IsClipboardFormatAvailable(CF_TEXT) ? 0 : 1);
      EnableMenuItem(hMenu, 4, MF_BYPOSITION | n);
      break;
    }
    }
  }

  BOOL Edit_OnInitDialog(HWND Wnd, HWND hwndFocus, LPARAM lParam)
  {
    int n;
    _TCHAR t[12];

    RECT Wp;
    // Top left & Bottom right of controls
    POINT TL, BR;
    int width;
    EditData *ew;

    ew = new EditData;

    ew->ThisRef = (LPRef)lParam;

    // Update reference count so it doesn't get blitzed elsewhere
    ew->ThisRef->links++;

    // Prevent reference from being edited twice
    ew->ThisRef->hwndEditor = Wnd;

    SetWindowLong(Wnd, DWL_USER, (long)ew);

    GetClientRect(Wnd, &ew->OEdit);

#ifdef MODAL_EDIT
    EnableWindow(FrameWnd, FALSE);
#endif

    for (n = 0; n < MAX_FIELDS; n++)
    {

      GetClassName(GetDlgItem(Wnd, CtrlID[n]), t, sizeof(t));

      if ((lstrcmp(t, _T("Edit")) == 0) || (lstrcmp(t, _T("ComboBox")) == 0))
        SetWindowFont(GetDlgItem(Wnd, CtrlID[n]), EditFnt->SFont, TRUE);
    }

    if (ArrowFnt)
    {
      SetDlgItemText(Wnd, id_GPrev, _T("�")); // a left arrow in Wingdings
      SetDlgItemText(Wnd, id_GNext, _T("�")); // a right arrow
      SetWindowFont(GetDlgItem(Wnd, id_GPrev), ArrowFnt, TRUE);
      SetWindowFont(GetDlgItem(Wnd, id_GNext), ArrowFnt, TRUE);
    }

    if (ctls_to_move[0][1] == -1)
    {

      GetClientRect(Wnd, &Wp);
      width = Wp.right - Wp.left;

      max_b = max_r = 0;

      for (n = 0; n <= 22; n++)
      {
        GetWindowRect(GetDlgItem(Wnd, ctls_to_move[n][0]), &Wp);

        TL.x = Wp.left;
        TL.y = Wp.top;
        BR.x = Wp.right;
        BR.y = Wp.bottom;

        ScreenToClient(Wnd, &TL);
        ScreenToClient(Wnd, &BR);

        if (BR.x > max_r)
          max_r = BR.x;

        if (BR.y > max_b)
          max_b = BR.y;

        switch (n)
        {
        // for the title and abstract the parameter is the relative width of the window
        case 0:
        case 1:
          ctls_to_move[n][1] = width - (BR.x - TL.x);
          break;
        // for everything else it is the offset from the right side
        default:
          ctls_to_move[n][1] = width - TL.x;
        }
      }
    }

    Buf2Dlg(Wnd, ew->ThisRef);

    ew->cur_x = ew->cur_y = 0;

    n = EditSize.ismax;

    MoveWindow(Wnd, EditSize.x, EditSize.y, EditSize.w, EditSize.h, TRUE);
    ShowWindow(Wnd, n ? SW_SHOWMAXIMIZED : SW_SHOWNORMAL);

    return TRUE;
  }

  void Edit_OnSize(HWND Wnd, UINT state, int cx, int cy)
  {
    /* This function handles the resizing of the edit window.
       If the window is too small, then it should not move the controls, but activate the scrollbars instead.
       */
    RECT Wp;
    // Top left and bottom right of controls
    POINT TL, BR;
    EditData *ew;

    int c;
    int IsTooSmallX, WasTooSmallX;
    int IsTooSmallY, WasTooSmallY;

    ew = (EditData *)GetWindowLong(Wnd, DWL_USER);

    GetWindowRect(Wnd, &Wp);

    switch (state)
    {
    case SIZE_MAXIMIZED:
      ew->EditSize.ismax = TRUE;
      break;
    case SIZE_RESTORED:
      ew->EditSize.ismax = FALSE;
      break;
    }

    if (!ew->EditSize.ismax)
    {
      ew->EditSize.x = Wp.left;
      ew->EditSize.y = Wp.top;
      ew->EditSize.w = Wp.right - Wp.left;
      ew->EditSize.h = Wp.bottom - Wp.top;
    }

    // Find out exactly how we need to resize depending on current and old sizes
    WasTooSmallX = (ew->OEdit.right - ew->OEdit.left) < max_r;
    IsTooSmallX = cx < max_r;
    WasTooSmallY = (ew->OEdit.bottom - ew->OEdit.top) < max_b;
    IsTooSmallY = cy < max_b;

    for (c = 0; c <= 22; c++)
    {
      GetWindowRect(GetDlgItem(Wnd, ctls_to_move[c][0]), &Wp);

      TL.x = Wp.left;
      TL.y = Wp.top;
      BR.x = Wp.right;
      BR.y = Wp.bottom;

      ScreenToClient(Wnd, &TL);
      ScreenToClient(Wnd, &BR);

      switch (c)
      {
      // resize the abstract edit control to the height of the dialog minus a bit,
      // and the width to allow room for the other controls
      case 0:
      {
        MoveWindow(GetDlgItem(Wnd, ctls_to_move[c][0]),
                   TL.x,
                   TL.y,
                   (IsTooSmallX ? max_r : cx) - ctls_to_move[c][1],
                   (IsTooSmallY ? max_b : cy) - (TL.y + 10),
                   FALSE);
        break;
      }

      // Resize the title control to the width of the dialog or max_r, whichever is greater
      case 1:
      {
        MoveWindow(GetDlgItem(Wnd, ctls_to_move[c][0]),
                   TL.x,
                   TL.y,
                   (IsTooSmallX ? max_r : cx) - ctls_to_move[c][1],
                   Wp.bottom - Wp.top,
                   FALSE);
        break;
      }

      default:
      {
        // if new and old widths are both too small, don't need to do anything
        MoveWindow(GetDlgItem(Wnd, ctls_to_move[c][0]),
                   (IsTooSmallX ? max_r : cx) - ctls_to_move[c][1],
                   TL.y,
                   Wp.right - Wp.left,
                   Wp.bottom - Wp.top,
                   FALSE);
      }
      }
    }

    GetClientRect(Wnd, &Wp);

    ew->ScrollRangeX = max_r - (Wp.right - Wp.left);
    ew->ScrollRangeY = max_b - (Wp.bottom - Wp.top);

    SetScrollRange(Wnd, SB_HORZ, 0, ew->ScrollRangeX, FALSE);
    SetScrollRange(Wnd, SB_VERT, 0, ew->ScrollRangeY, FALSE);

    if ((WasTooSmallX) && (!IsTooSmallX))
      SendMessage(Wnd, WM_HSCROLL, SB_LEFT, 0);

    if ((WasTooSmallY) && (!IsTooSmallY))
      SendMessage(Wnd, WM_VSCROLL, SB_TOP, 0);

    ShowScrollBar(Wnd, SB_HORZ, IsTooSmallX);
    ShowScrollBar(Wnd, SB_VERT, IsTooSmallY);

    ew->OEdit.right = cx;
    ew->OEdit.bottom = cy;
    InvalidateRect(Wnd, &ew->OEdit, TRUE);
  }

  void Edit_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
  {
    LPTSTR t;
    LPRefWndData p;
    EditData *ew;
    long n;

    ew = (EditData *)GetWindowLong(hwnd, DWL_USER);

    if ((codeNotify == EN_CHANGE) || (codeNotify == CBN_SELENDOK) || (codeNotify == CBN_EDITCHANGE))
    {
      if (!(ew->ThisRef->Flags & RF_DontUpdate))
      {
        ew->ThisRef->Flags |= RF_NeedsUpdating;
        if (id == id_Title)
          ew->ThisRef->Flags &= ~RF_DontResort;
      }
    }
    else
    {

      switch (id)
      {
      case WM_CUT:
      case WM_COPY:
      case WM_PASTE:
      case WM_UNDO:
        SendMessage(GetFocus(), id, 0, 0);
        break;

      case cm_Help:
        WinHelp(hwnd, HelpName, HELP_CONTEXT, 1);
        break;
      case cm_CopyFormatted:
      case cm_Print:
      {
        if (ew->ThisRef->Flags & RF_NeedsUpdating)
          Dlg2Buf(hwnd, ew->ThisRef);

        if ((id == cm_Print) || (OpenClipboard(FrameWnd)))
          CopyFmted(hwnd, id, ew->ThisRef);

        break;
      }

      case IDOK:
      case id_OkNew:
      {
        if (ew->ThisRef->Flags & (RF_NeedsUpdating | RF_NeedsInserting))
        {
          Dlg2Buf(hwnd, ew->ThisRef);
          if (ew->ThisRef->Flags & RF_EditModal)
            EndDialog(hwnd, (ew->ThisRef->Flags & RF_DontResort) ? IDCANCEL : IDOK);

          //		  if (ew->ThisRef->Flags & RF_CanBrowse)
          //		    PostMessage(FrameWnd, WM_EDITCLOSING, (WPARAM)hwnd, (LPARAM)ew->ThisRef);
        }
        else
        {
          if (ew->ThisRef->Flags & RF_EditModal)
            EndDialog(hwnd, IDCANCEL);
        }
        EnableWindow(FrameWnd, TRUE);

        if (!(ew->ThisRef->Flags & RF_EditModal))
          DestroyWindow(hwnd);

        ew->ThisRef->hwndEditor = NULL;

        if (!(ew->ThisRef->Flags & (RF_NeedsInserting | RF_EditModal)))
        {
          ew->ThisRef->links--;
          ew->ThisRef->OpenedFrom = NULL;
        }

        EditSize = ew->EditSize;

        // Owning file must have been closed
        if (!ew->ThisRef->links)
          delete ew->ThisRef;

        delete ew;

        if (id == id_OkNew)
          PostMessage(FrameWnd, WM_COMMAND, cm_RefNew, 0);

        break;
      }

      case IDCANCEL:
      {
        EnableWindow(FrameWnd, TRUE);

        if (ew->ThisRef->Flags & RF_EditModal)
          EndDialog(hwnd, IDCANCEL);
        else
          DestroyWindow(hwnd);

        ew->ThisRef->hwndEditor = NULL;
        ew->ThisRef->OpenedFrom = NULL;

        EditSize = ew->EditSize;

        // Owning file must have been closed if links decrease to 0
        if (!(--ew->ThisRef->links))
          delete ew->ThisRef;

        delete ew;

        break;
      }

      case cm_AddToBib:
      {
        p = ActiveFile;

        if (BibData && ((n = BibData->Refs->indexof(ew->ThisRef)) >= 0))
        {
          BibData->Refs->atremove(n);

          if (BibData->Refs->count == 0)
          {
            // if bibliography is now empty, destroy it completely
            SendMessage(BibData->Window, WM_CLOSE, 0, 0);
            BibData = NULL;

            // Redraw the client window so that all references get updated properly by the change
            RedrawWindow(ClientWnd, NULL, NULL, RDW_FRAME | RDW_INVALIDATE | RDW_ALLCHILDREN);
          }
          else
          {

            if (!BibIsFormatted)
            {
              ListBox_DeleteString(BibData->ListWnd, n);
              ListBox_SetSel(BibData->ListWnd, TRUE, (n == BibData->Refs->count) ? n - 1 : n);
            }
            else
              BibData->Format(BibIsFormatted);
          }
        }
        else
        {
          if (!BibData)
            SendMessage(FrameWnd, WM_COMMAND, cm_BibCreate, 0);

          n = BibData->Refs->insert(ew->ThisRef);

          if (!BibIsFormatted)
            BibData->Refs->display(n);
          else
            BibData->Format(BibIsFormatted);

          SendMessage(ClientWnd, WM_MDIACTIVATE, (WPARAM)p->Window, 0);
        }

        // Redraw string in file window in new colour
        n = p->Refs->indexof(ew->ThisRef);
        ListBox_DeleteString(p->ListWnd, n);
        p->Refs->display(n);

        break;
      }

      case cm_AddKeyword:
      {
        t = (_TCHAR *)malloc(SCRATCH_SIZE);

        if (GetDlgItemText(hwnd, id_Keywords, t, SCRATCH_SIZE - 1))
        {

          if (ew->ThisRef->keywords)
            free(ew->ThisRef->keywords);

          ew->ThisRef->keywords = _tcsdup(t);
        }

        free(t);

        if (GetWordsToAdd(hwnd, TRUE) == IDOK)
        {
          AddTheWords(ew->ThisRef, words);
          ew->ThisRef->Flags |= RF_NeedsUpdating;
        }

        SetDlgItemText(hwnd, id_Keywords, ew->ThisRef->keywords);

        break;
      }

      case id_GPrev:
        GotoRef(hwnd, -1);
        break;
      case id_GNext:
        GotoRef(hwnd, 1);
        break;

      case cm_CJournals:
      case cm_CBooks:
      case cm_CReports:
      {
        if ((DialogBoxParam(ResInstance,
                            _T("LISTEDIT"),
                            hwnd,
                            EListProc,
                            id - cm_CJournals) == IDOK) &&
            (id == ew->ThisRef->reftype + cm_CJournals))

          FillJList(hwnd, ew->ThisRef);

        break;
      }
      }
    }
  }

  void Edit_OnHScroll(HWND hwnd, HWND hwndCtl, UINT code, int pos)
  {
    int cx;
    EditData *ew;

    ew = (EditData *)GetWindowLong(hwnd, DWL_USER);

    switch (code)
    {
    case SB_TOP:
      cx = 0 - ew->cur_x;
      break;
    case SB_BOTTOM:
      cx = ew->ScrollRangeX - ew->cur_x;
      break;
    case SB_PAGEDOWN:
      cx = (ew->cur_x < (ew->ScrollRangeX - 50)) ? 50 : (ew->ScrollRangeX - ew->cur_x);
      break;
    case SB_PAGEUP:
      cx = (ew->cur_x > 50) ? -50 : (0 - ew->cur_x);
      break;
    case SB_LINEDOWN:
      cx = (ew->cur_x < (ew->ScrollRangeX - 10)) ? 10 : (ew->ScrollRangeX - ew->cur_x);
      break;
    case SB_LINEUP:
      cx = (ew->cur_x > 10) ? -10 : (0 - ew->cur_x);
      break;
    case SB_THUMBPOSITION:
    case SB_THUMBTRACK:
      cx = pos - ew->cur_x;
      break;
    default:
      cx = 0;
    }

    if (cx)
    {
      ScrollWindow(hwnd, -cx, 0, NULL, NULL);
      ew->cur_x += cx;
      SetScrollPos(hwnd, SB_HORZ, ew->cur_x, TRUE);
    }
  }

  void Edit_OnVScroll(HWND hwnd, HWND hwndCtl, UINT code, int pos)
  {
    int cy;
    EditData *ew;

    ew = (EditData *)GetWindowLong(hwnd, DWL_USER);

    switch (code)
    {
    case SB_TOP:
      cy = 0 - ew->cur_y;
      break;
    case SB_BOTTOM:
      cy = ew->ScrollRangeY - ew->cur_y;
      break;
    case SB_PAGEDOWN:
      cy = (ew->cur_y < (ew->ScrollRangeY - 50)) ? 50 : (ew->ScrollRangeY - ew->cur_y);
      break;
    case SB_PAGEUP:
      cy = (ew->cur_y > 50) ? -50 : (0 - ew->cur_y);
      break;
    case SB_LINEDOWN:
      cy = (ew->cur_y < (ew->ScrollRangeY - 10)) ? 10 : (ew->ScrollRangeY - ew->cur_y);
      break;
    case SB_LINEUP:
      cy = (ew->cur_y > 10) ? -10 : (0 - ew->cur_y);
      break;
    case SB_THUMBPOSITION:
    case SB_THUMBTRACK:
      cy = pos - ew->cur_y;
      break;
    default:
      cy = 0;
    }

    if (cy)
    {
      ScrollWindow(hwnd, 0, -cy, NULL, NULL);
      ew->cur_y += cy;
      SetScrollPos(hwnd, SB_VERT, ew->cur_y, TRUE);
    }
  }

  void inline Edit_OnActivate(HWND hwnd, UINT state, HWND hwndActDeact, BOOL fMinimized)
  {
    CurrentEditor = (state == WA_INACTIVE) ? NULL : hwnd;
  }

  BOOL CALLBACK EditRef(HWND Wnd, UINT Msg, WPARAM wParam, LPARAM lParam)
  {
    if (Msg == HlpMsg)
      WinHelp(Wnd, HelpName, HELP_CONTEXT, 8);
    else
    {
      switch (Msg)
      {
        HANDLE_MSG(Wnd, WM_ACTIVATE, Edit_OnActivate);
        HANDLE_MSG(Wnd, WM_INITMENUPOPUP, Edit_OnInitMenuPopup);
        HANDLE_MSG(Wnd, WM_INITDIALOG, Edit_OnInitDialog);
        HANDLE_MSG(Wnd, WM_SIZE, Edit_OnSize);
        HANDLE_MSG(Wnd, WM_COMMAND, Edit_OnCommand);
        HANDLE_MSG(Wnd, WM_HSCROLL, Edit_OnHScroll);
        HANDLE_MSG(Wnd, WM_VSCROLL, Edit_OnVScroll);
      case WM_STOPBROWSING:
      {
        EnableWindow(GetDlgItem(Wnd, id_GPrev), FALSE);
        EnableWindow(GetDlgItem(Wnd, id_GNext), FALSE);
        EnableWindow(GetDlgItem(Wnd, id_OkNew), FALSE);
        break;
      }
      }
    }
    return (FALSE);
  }
