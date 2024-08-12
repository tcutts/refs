#include "inc/globals.h"
#include "inc/reflopts.h"

int TempWdth;

void LOpt_OnCommand(HWND Dlg, int id, HWND hwndCtl, UINT codeNotify)
{
  unsigned int n;

  switch (id)
  {
  case IDOK:
  {
    MasterFlags &= 0xFFB8;
    MasterFlags |= (IsDlgButtonChecked(Dlg, id_RefTitle) << 2) | (IsDlgButtonChecked(Dlg, id_SelectNew) << 6);

    for (n = 0; n <= 2; n++)
    {
      if (IsDlgButtonChecked(Dlg, id_AuthAll + n) == 1)
        MasterFlags |= (n + 1);
    }

    MasterWdth = TempWdth;

    if (ActiveFile)
    {
      ActiveFile->ClmnWdth = TempWdth;
      ActiveFile->ListFlags = MasterFlags;
      DestroyWindow(ActiveFile->ListWnd);
      ActiveFile->CreateMainList();
    }
    EndDialog(Dlg, IDOK);
    break;
  }
  case IDCANCEL:
    EndDialog(Dlg, IDCANCEL);
    break;
  case cm_Help:
    WinHelp(FrameWnd, HelpName, HELP_CONTEXT, 4);
    break;
  }
}

void LOpt_OnHScroll(HWND Dlg, HWND hwndCtl, UINT code, int pos)
{
  switch (code)
  {
  case SB_LINERIGHT:
    TempWdth++;
    break;
  case SB_LINELEFT:
    TempWdth--;
    break;
  case SB_PAGERIGHT:
    TempWdth += 5;
    break;
  case SB_PAGELEFT:
    TempWdth -= 5;
    break;
  case SB_THUMBPOSITION:
  case SB_THUMBTRACK:
    TempWdth = pos;
    break;
  }
  SetScrollPos(hwndCtl, SB_CTL, TempWdth, TRUE);
  TempWdth = GetScrollPos(hwndCtl, SB_CTL);
  SetDlgItemInt(Dlg, idt_ClmnWdth, TempWdth, TRUE);
}

BOOL LOpt_OnInitDialog(HWND Dlg, HWND hwndFocus, LPARAM lParam)
{
  HWND ScrollHnd;
  unsigned int TFlags;

  if (ActiveFile)
  {
    TempWdth = ActiveFile->ClmnWdth;
    TFlags = ActiveFile->ListFlags;
  }
  else
  {
    TempWdth = MasterWdth;
    TFlags = MasterFlags;
  }
  ScrollHnd = GetDlgItem(Dlg, ids_ClmnWdth);
  SetScrollRange(ScrollHnd, SB_CTL, 20, 100, FALSE);
  SetScrollPos(ScrollHnd, SB_CTL, TempWdth, TRUE);
  SetDlgItemInt(Dlg, idt_ClmnWdth, TempWdth, TRUE);
  CheckDlgButton(Dlg, (TFlags & 3) + (id_AuthAll - 1), 1);
  CheckDlgButton(Dlg, id_RefTitle, (TFlags & FLG_SHOW_TITLE) >> 2);
  CheckDlgButton(Dlg, id_SelectNew, (TFlags & FLG_SELECT_NEW) >> 6);
  return (TRUE);
}

/*Flags:
 Bit
 0,1    Author format    0-3
 2      Show title      4
 3      Not tabbed
 4,5    Deletion
 6      Select New      64
 7      Confirm mouse    128
 */
BOOL CALLBACK LOptProc(HWND Dlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  switch (Msg)
  {
    HANDLE_MSG(Dlg, WM_COMMAND, LOpt_OnCommand);
    HANDLE_MSG(Dlg, WM_HSCROLL, LOpt_OnHScroll);
    HANDLE_MSG(Dlg, WM_INITDIALOG, LOpt_OnInitDialog);
  }
  return (FALSE);
}

void ListOpts(void)
{
  if ((DialogBox(ResInstance, _T("LISTOPT"), FrameWnd, LOptProc) == IDOK) && ActiveFile)
    ActiveFile->Refs->redisplay();
}
