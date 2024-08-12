#include "inc/globals.h"
#include "inc/refchild.h"
#include "inc/rcutpast.h"
#include "inc/reffont.h"
#ifdef CC_TOOLBAR
#include "inc/rtoolbar.h"
#include "inc/refframe.h"
#endif
#ifdef WIN32
#include "inc/refpaint.h"
#endif
#include "inc/editdlg.h"
#include "inc/authdlg.h"
#include "inc/redit.h"

int CanDrag(void)
{

  _TCHAR t1[128], t2[128];

  if (!(MasterFlags & FLG_CONFIRM_MOUSE))
    return (TRUE);
  else
  {
    LoadString(ResInstance, wrn_Mouse, t1, sizeof(t1) / sizeof(_TCHAR));
    LoadString(ResInstance, wrn_Warning, t2, sizeof(t2) / sizeof(_TCHAR));
    return (MessageBox(FrameWnd, t1, t2, MB_YESNO | MB_ICONQUESTION) == IDYES);
  }
}

void Child_OnCommand(HWND Window, int id, HWND hwndCtl, UINT codeNotify)
{
  LPRefWndData WorkDat;

  WorkDat = (LPRefWndData)GetWindowLong(Window, 0);

  switch (id)
  {
  case 800:
  { // MainListBox

#ifdef CC_TOOLBAR
    // has the edit/list box changed?
    if ((codeNotify == EN_UPDATE) || (codeNotify == LBN_SELCHANGE))
    {

#ifndef WIN32
      if (CommCtrlAvail)
#endif
        UpdateButtons();
    }

#endif

    if (codeNotify == LBN_DBLCLK)
    {
      // which dialog has user double-clicked for?
      if (!(GetAsyncKeyState(VK_CONTROL) & 0xC000))
        EditIt(WorkDat->UpdateCurrent());
      else
        EditAuth(WorkDat->UpdateCurrent());
    }

    break;
  }

  case 801:
  { // Searchable check box
    if (codeNotify == BN_CLICKED)
      WorkDat->SrchFlag = !WorkDat->SrchFlag;
    break;
  }

  case WM_CUT:
  case WM_COPY:
  case WM_PASTE:
  case WM_UNDO:
  {
    // if these are for the formatted bibliography,  send them
    // direct to the edit control for Windows to deal with

    if ((WorkDat == BibData) && BibIsFormatted)
    {

      if (BibIsFormatted)
#ifdef USE_RTF
        SendMessage(((hRichEdit)WorkDat->ListWnd)->hWnd, id, 0, 0);
#else
        SendMessage(WorkDat->ListWnd, id, 0, 0);
#endif
    }
    else
    {

      switch (id)
      {

      case WM_CUT:
      {
        CopyThem(WorkDat);
        DeleteThem(WorkDat, TRUE);
        break;
      }

      case WM_COPY:
        CopyThem(WorkDat);
        break;

      case WM_PASTE:
        PasteThem(WorkDat);
        break;
      }
    }
#ifdef CC_TOOLBAR
#ifndef WIN32
    if (CommCtrlAvail)
#endif
      UpdateButtons();
#endif
    break;
  }

  case cm_FormatChng:
    WorkDat->Format(BibIsFormatted);
    break;

  case cm_AddToBib:
    AddToBib(WorkDat);
    break;

  default:
    FORWARD_WM_COMMAND(Window, id, hwndCtl, codeNotify, DefMDIChildProc);
  }
}

BOOL Child_OnSetCursor(HWND Window, HWND hwndCursor, UINT codeHitTest, UINT msg)
{
  LPRefWndData WorkDat;
  int n, MButton;
  HWND h;
  _TCHAR t[12];
  BOOL IsTrue;
  POINT Pnt;

  // If Refs is doing something long, show an hourglass
  if (!IsWindowEnabled(FrameWnd))
  {
    SetCursor(LoadCursor(0, IDC_WAIT));
    return TRUE;
  }

  WorkDat = (LPRefWndData)GetWindowLong(Window, 0);

  if ((msg == WM_RBUTTONUP) || (msg == WM_RBUTTONDOWN))
  {

    // Mouse button state is changing

    if (msg == WM_RBUTTONUP)
    {

      // Mouse button is coming up
      if (FromWnd)
      {

        // We have a valid window from which references are coming

        // Which window are we in now?
        GetCursorPos(&Pnt);
        h = WindowFromPoint(Pnt);
        GetClassName(h, t, sizeof(t) - 1);

        if (!_tcsstr(t, FILECLASS))
          h = GetParent(h);

        if ((WorkDat != FromWnd) && (!WorkDat->SrchPat))
        {
          // Window is not the original window, and is not a search result window
          IsTrue = ((GetAsyncKeyState(VK_SHIFT) & 0xC000) != 0);
          if (CanDrag)
          {
            if (WorkDat != BibData)
            {
              CopyThem(FromWnd);
              if (IsTrue) // shift is down
                DeleteThem(FromWnd, TRUE);
              PasteThem(WorkDat);
            }
            else
            {
              AddToBib(FromWnd);
            }
            FromWnd = NULL;
          }
        }
        else
          // You can't put that here!
          MessageBeep(0xFFFF);

        RBtnDown = FALSE;
        CCursor = LoadCursor(0, IDC_WAIT);
        SetCursor(CCursor);
      }
    }

    // If the button was not down before, and is coming dow now...
    if ((!RBtnDown) && (msg == WM_RBUTTONDOWN))
    {
      n = ListBox_GetSelCount(WorkDat->ListWnd);
      if (n)
      {
        RBtnDown = TRUE;
        FromWnd = WorkDat;
        CCursor = (n == 1) ? SCursor : MCursor;
      }
      else
      {
        // No references selected, do nothing.
        RBtnDown = FALSE;
        FromWnd = NULL;
      }
    }
  }
  else
  {

    // not a buttonup or buttondown message

    // establish which is the non-default mouse button
    IsTrue = SwapMouseButton(TRUE);
    SwapMouseButton(IsTrue);
    MButton = (IsTrue) ? VK_LBUTTON : VK_RBUTTON;

    // Is it down?
    if (!(GetAsyncKeyState(MButton) & 0xC000))
    { // button is up and we have a valid source
      // Reset the main cursor to an arrow
      CCursor = LoadCursor(0, IDC_ARROW);
      FromWnd = NULL;
      RBtnDown = FALSE;
    };
  }

  if ((codeHitTest == HTCLIENT) || (codeHitTest == HTCAPTION))
  {
    SetCursor(CCursor);
    return (TRUE);
  }

  return FORWARD_WM_SETCURSOR(Window, hwndCursor, codeHitTest, msg, DefMDIChildProc);
}

BOOL Child_OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
  LPRefWndData WorkDat;

  WorkDat = ((LPRefWndData)((LPMDICREATESTRUCT)lpCreateStruct->lpCreateParams)->lParam);

  WorkDat->Window = hwnd;

  SetWindowLong(hwnd, 0, (long)WorkDat);

  // Create listbox
  WorkDat->CreateMainList();

  Clients++;

  return TRUE;
}

void Child_OnSize(HWND hwnd, UINT state, int cx, int cy)
{
  LPRefWndData WorkDat;

  WorkDat = (LPRefWndData)GetWindowLong(hwnd, 0);
  IsMaximized = (state == SIZE_MAXIMIZED);

  if (state != SIZE_MINIMIZED)
    WorkDat->Resize(cx, cy);

  FORWARD_WM_SIZE(hwnd, state, cx, cy, DefMDIChildProc);
}

void Child_OnDestroy(HWND hwnd)
{
  LPRefWndData WorkDat;

  WorkDat = (LPRefWndData)GetWindowLong(hwnd, 0);

  if (WorkDat == BibData)
  {
    // the destructor also destroys the contents by default, so...
    WorkDat->Refs->removeall();
    BibData = NULL;
    RedrawWindow(ClientWnd, NULL, NULL, RDW_FRAME | RDW_INVALIDATE | RDW_ALLCHILDREN);
  }
  delete WorkDat;
  Clients--;
  if (!Clients)
    ActiveFile = NULL;
}

void Child_OnClose(HWND hwnd)
{
  LPRefWndData WorkDat;

  WorkDat = (LPRefWndData)GetWindowLong(hwnd, 0);

  if ((BibData == WorkDat) || (WorkDat->CanClose()))
  {
    // if we can close  destroy ourselves
    SendMessage(ClientWnd, WM_MDIDESTROY, (WPARAM)hwnd, 0);
    ClosedThisOne = TRUE;
  }
  else
    ClosedThisOne = FALSE;
}

void Child_OnDrawItem(HWND hwnd, const DRAWITEMSTRUCT *Ptr)
{
  HDC MemDC;
  LPRef ThisRef;
  LPRefWndData WorkDat;
  COLORREF TxtCol, BkCol, OTCol;
  HBRUSH Brsh;
  HBITMAP OHndM;
  HFONT OHndF;
  int cur_ext, new_ext;
  int OBMode, IsSel, RCWidth;
  LPTSTR APtr;
  SIZE sz;

  // Fun Fun Fun!  Drawing Owner-drawn list items
  WorkDat = (LPRefWndData)GetWindowLong(hwnd, 0);

  if (Ptr->itemID >= (DWORD)WorkDat->Refs->count)
    return;

  // Get reference to be displayed here
  if (WorkDat->Refs->count != 0)
    ThisRef = (LPRef)WorkDat->Refs->at(Ptr->itemID);
  if (Ptr->itemAction & (ODA_SELECT | ODA_DRAWENTIRE))
  {
    if (Ptr->itemState & ODS_SELECTED)
    {
      // get selected background colour
      BkCol = GetSysColor(COLOR_HIGHLIGHT);
      // get appropriate colour for bibliography, if necessary
      if ((!BibData) || (BibData->Refs->indexof(WorkDat->Refs->at(Ptr->itemID))) == -1)
        TxtCol = GetSysColor(COLOR_HIGHLIGHTTEXT);
      else
        TxtCol = BibCol;
      IsSel = 1;
    }
    else
    {
      // similarly for unselected items
      BkCol = GetSysColor(COLOR_WINDOW);
      if ((!BibData) || (BibData->Refs->indexof(WorkDat->Refs->at(Ptr->itemID))) == -1)
        TxtCol = GetSysColor(COLOR_WINDOWTEXT);
      else
        TxtCol = BibCol;
      IsSel = 0;
    }

    // fill background with appropriate colour
    Brsh = CreateSolidBrush(BkCol);
    FillRect(Ptr->hDC, &Ptr->rcItem, Brsh);
    DeleteObject(Brsh);

    if (ListHeight >= 17)
    {
      MemDC = CreateCompatibleDC(Ptr->hDC);
      /*Get appropriate bitmap and copy it
       The transparent bitmaps are generated only once in CreateBitmaps
       to conserve speed.  They are re-made on receipt of a wm_SysColorChange*/
      OHndM = SelectBitmap(MemDC, BmpHnd[ThisRef->reftype * 2 + IsSel]);
      BitBlt(Ptr->hDC, Ptr->rcItem.left, Ptr->rcItem.top + (Ptr->rcItem.bottom - Ptr->rcItem.top) / 2 - 7, 30, 15, MemDC, 0, 0, SRCCOPY);
      SelectBitmap(MemDC, OHndM);
      DeleteDC(MemDC);
    }

    // Draw text
    OHndF = SelectFont(Ptr->hDC, ListFnt->SFont);
    OBMode = SetBkMode(Ptr->hDC, TRANSPARENT);
    OTCol = SetTextColor(Ptr->hDC, TxtCol);

    // Get string to display from reference
    ThisRef->GetSortStr(WorkDat->Refs->s1, WorkDat->ListFlags | FLG_YEAR_ONLY, WorkDat->Refs->s2);
    lstrcpy(WorkDat->Refs->s2, WorkDat->Refs->s1);

    APtr = _tcsrchr(WorkDat->Refs->s2, _T('\t'));

    if (!APtr)
      APtr = strend(WorkDat->Refs->s2);

    APtr[0] = _T('\0');

    // chop bits off and add ellipsis until it fits the column nicely
    RCWidth = WorkDat->Stops - ((ListHeight >= 17) ? 40 : 10);

    for (GetTextExtentPoint(Ptr->hDC, WorkDat->Refs->s2, lstrlen(WorkDat->Refs->s2), &sz);
         sz.cx > RCWidth;
         GetTextExtentPoint(Ptr->hDC, WorkDat->Refs->s2, lstrlen(WorkDat->Refs->s2), &sz))
    {

      APtr--;
      lstrcpy(APtr, _T("..."));
    }

    lstrcat(WorkDat->Refs->s2, _tcschr(WorkDat->Refs->s1, _T('\t')));

    if (WorkDat->ListFlags & FLG_SHOW_TITLE)
    {
      new_ext = LOWORD(GetTabbedTextExtent(Ptr->hDC, WorkDat->Refs->s2, lstrlen(WorkDat->Refs->s2), 1, &WorkDat->Stops));
      cur_ext = ListBox_GetHorizontalExtent(WorkDat->ListWnd);
      if (new_ext > cur_ext)
        ListBox_SetHorizontalExtent(WorkDat->ListWnd, new_ext);
    }

    TabbedTextOut(Ptr->hDC,
                  Ptr->rcItem.left + ((ListHeight < 17) ? 4 : 30),
                  Ptr->rcItem.top + 1,
                  WorkDat->Refs->s2,
                  lstrlen(WorkDat->Refs->s2),
                  1,
                  &WorkDat->Stops,
                  Ptr->rcItem.left);

    // Restore old text modes
    SetTextColor(Ptr->hDC, OTCol);
    SetBkMode(Ptr->hDC, OBMode);
    SelectFont(Ptr->hDC, OHndF);

    if (Ptr->itemState & ODS_FOCUS)
      DrawFocusRect(Ptr->hDC, &Ptr->rcItem);
  }

  if (Ptr->itemAction & ODA_FOCUS)
    DrawFocusRect(Ptr->hDC, &Ptr->rcItem);
}

void inline Child_OnMeasureItem(HWND hwnd, LPMEASUREITEMSTRUCT Ptr)
{
  Ptr->itemHeight = ListHeight;
}

void Child_MDIActivate(HWND hwnd, BOOL fActive, HWND hwndActivate, HWND hwndDeactivate)
{

  ActiveFile = (LPRefWndData)GetWindowLong(hwndActivate, 0);

  if (ActiveFile)
    SetFocus(ActiveFile->ListWnd);

#ifdef WIN32
  UpdateButtons();
  DefaultStatus();
#else
  InvalidateRect(FrameWnd, &StatusRect, TRUE);
#endif
}

LRESULT CALLBACK RefChildProc(HWND Window, UINT Msg, WPARAM wParam, LPARAM lParam)
{

  switch (Msg)
  {
    HANDLE_MSG(Window, WM_COMMAND, Child_OnCommand);
    HANDLE_MSG(Window, WM_SETCURSOR, Child_OnSetCursor);
    HANDLE_MSG(Window, WM_CREATE, Child_OnCreate);
    HANDLE_MSG(Window, WM_SIZE, Child_OnSize);
    HANDLE_MSG(Window, WM_CLOSE, Child_OnClose);
    HANDLE_MSG(Window, WM_DESTROY, Child_OnDestroy);
    HANDLE_MSG(Window, WM_DRAWITEM, Child_OnDrawItem);
    HANDLE_MSG(Window, WM_MEASUREITEM, Child_OnMeasureItem);
    HANDLE_MSG(Window, WM_MDIACTIVATE, Child_MDIActivate);
  case WM_RESORT:
    ((LPRefWndData)GetWindowLong(Window, 0))->ReSort();
    break;
  default:
  {
    return (DefMDIChildProc(Window, Msg, wParam, lParam));
  }
  } // case Message
  return (0);
}
