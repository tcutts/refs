#include "inc/globals.h"
#include "inc/rsrtopt.h"

int *flgs;
int ReSort;
TSName *SrtName;

const int SrtStrNo[] = {4, 6, 1, 5, 2, 8, 7};
const _TCHAR wsp[] = _T(" \t\r\n");

void NameOpt_OnCommand(HWND Dlg, int id, HWND hwndCtl, UINT codeNotify)
{
  _TCHAR tSep[21];

  switch (id)
  {
  case IDOK:
  {
    GetDlgItemText(Dlg, id_surname, tSep, 20);
    if (!_tcspbrk(tSep, wsp))
    {
      lstrcpy(SrtName->separator, tSep);
      SrtName->sort_method = IsDlgButtonChecked(Dlg, idr_firstname);

      if (!SrtName->sort_method)
        SrtName->surname_last = IsDlgButtonChecked(Dlg, id_family);

      MSortName = *SrtName;
      EndDialog(Dlg, IDOK);
    }
    else
      ErrorBox(Dlg, err_BadNameSep);
    break;
  }
  case IDCANCEL:
    EndDialog(Dlg, IDCANCEL);
    break;
  case id_cmpsur:
  case idr_firstname:
  {
    EnableWindow(GetDlgItem(Dlg, id_family), id == id_cmpsur);
    EnableWindow(GetDlgItem(Dlg, id_surname), id == id_cmpsur);
    break;
  }
  case cm_Help:
    WinHelp(FrameWnd, HelpName, HELP_CONTEXT, 7);
  }
}

BOOL NameOpt_OnInitDialog(HWND Dlg, HWND hwndFocus, LPARAM lParam)
{

  if (!ActiveFile)
    SrtName = &MSortName;
  else
    SrtName = &ActiveFile->NameSort;
  SetDlgItemText(Dlg, id_surname, SrtName->separator);
  CheckRadioButton(Dlg, id_cmpsur, idr_firstname, id_cmpsur + SrtName->sort_method);
  CheckDlgButton(Dlg, id_family, SrtName->surname_last);
  EnableWindow(GetDlgItem(Dlg, id_family), (SrtName->sort_method) ? FALSE : TRUE);
  EnableWindow(GetDlgItem(Dlg, id_surname), (SrtName->sort_method) ? FALSE : TRUE);
  return TRUE;
}

BOOL CALLBACK NameOptProc(HWND Dlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  switch (Msg)
  {
    HANDLE_MSG(Dlg, WM_COMMAND, NameOpt_OnCommand);
    HANDLE_MSG(Dlg, WM_INITDIALOG, NameOpt_OnInitDialog);
  }
  return (FALSE);
}

int NameOpts(HWND Wnd)
{
  return DialogBox(ResInstance, _T("NAME"), Wnd, NameOptProc);
}

void SrtOpt_OnCommand(HWND Dlg, int id, HWND hwndCtl, UINT codeNotify)
{
  int N, o, t, CantFinish, tmp;

  switch (id)
  {
  case IDOK:
  {
    tmp = CantFinish = FALSE;
    for (N = 0; N <= 2; N++)
    {
      // get the selections and put them in flgs
      o = ComboBox_GetCurSel(GetDlgItem(Dlg, id_SortA + N));
      if ((N > 0) && (o != 6))
        for (t = 0; t < N; t++)
          // duplicated fields are not allowed
          CantFinish |= (o == (flgs[t] & 7));
      o += (ComboBox_GetCurSel(GetDlgItem(Dlg, id_DSortA + N)) << 3);
      tmp |= (o != flgs[N]);
      flgs[N] = o;
    }
    if (CantFinish)
      ErrorBox(Dlg, err_BadSort);
    else
    {
      if (tmp)
      {
        for (N = 0; N <= 2; N++)
          MSortFlags[N] = flgs[N];
        ReSort = TRUE;
      }
      if (ReSort && ActiveFile)
        PostMessage(ActiveFile->Window, WM_RESORT, 0, 0);
      EndDialog(Dlg, IDOK);
    }
    break;
  }
  case IDCANCEL:
  {
    if (ReSort && ActiveFile)
      PostMessage(ActiveFile->Window, WM_RESORT, 0, 0);
    EndDialog(Dlg, IDCANCEL);
    break;
  }
  case id_names:
    ReSort = (NameOpts(Dlg) == IDOK);
    break;
  case cm_Help:
    WinHelp(FrameWnd, HelpName, HELP_CONTEXT, 2);
    break;
  }
}

BOOL SrtOpt_OnInitDialog(HWND Dlg, HWND hwndFocus, LPARAM lParam)
{
  int N, o;
  _TCHAR t1[RES_STR], t2[RES_STR];

  // set up controls with appropriate flags
  ReSort = FALSE;
  if (!ActiveFile)
    flgs = MSortFlags;
  else
    flgs = ActiveFile->SortFlags;
  for (N = 0; N <= 6; N++)
  {
    LoadString(ResInstance, SrtStrNo[N], t1, RES_STR - 1);
    if (N < 2)
      LoadString(ResInstance, str_Ascending + N, t2, RES_STR - 1);
    for (o = id_SortA; o <= id_SortC; o++)
    {
      if (!((o == id_SortA) && (N == 6)))
        ComboBox_AddString(GetDlgItem(Dlg, o), t1);
      if (N < 2)
        ComboBox_AddString(GetDlgItem(Dlg, o + 3), t2);
    }
  }
  for (N = 0; N <= 2; N++)
  {
    ComboBox_SetCurSel(GetDlgItem(Dlg, id_SortA + N), flgs[N] & 7);
    ComboBox_SetCurSel(GetDlgItem(Dlg, id_DSortA + N), flgs[N] >> 3);
  }
  return TRUE;
}

BOOL CALLBACK SrtOptProc(HWND Dlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  switch (Msg)
  {
    HANDLE_MSG(Dlg, WM_COMMAND, SrtOpt_OnCommand);
    HANDLE_MSG(Dlg, WM_INITDIALOG, SrtOpt_OnInitDialog);
  }
  return (FALSE);
}

int SortOpts(void)
{
  return DialogBox(ResInstance, _T("OPTSORT"), FrameWnd, SrtOptProc);
}
