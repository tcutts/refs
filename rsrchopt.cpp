#include "inc/globals.h"
#include "inc/rsrchopt.h"

void SrchOpt_OnCommand(HWND Dlg, int id, HWND hwndCtl, UINT codeNotify)
{
  switch (id)
  {
  case IDOK:
  {
    DefSrchFlag = IsDlgButtonChecked(Dlg, id_Searchable);
    EndDialog(Dlg, IDOK);
    break;
  }
  case IDCANCEL:
    EndDialog(Dlg, IDCANCEL);
  }
}

BOOL SrchOpt_OnInitDialog(HWND Dlg, HWND hwndFocus, LPARAM lParam)
{
  CheckDlgButton(Dlg, id_Searchable, DefSrchFlag);
  return TRUE;
}

BOOL CALLBACK SrchOptProc(HWND Dlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  switch (Msg)
  {
    HANDLE_MSG(Dlg, WM_COMMAND, SrchOpt_OnCommand);
    HANDLE_MSG(Dlg, WM_INITDIALOG, SrchOpt_OnInitDialog);
  }
  return (FALSE);
}

int SrchOpts(void)
{
  return DialogBox(ResInstance, _T("SRCHOPT"), FrameWnd, SrchOptProc);
}
