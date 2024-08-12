#include "inc/globals.h"
#include "inc/authdlg.h"

void EditAuth(long N)
{
  LPRef Tmp;

  // Works the same way as EditIt
  if ((ActiveFile != BibData) && (N != -1))
  {

    Tmp = (LPRef)(ActiveFile->Refs->at(N));

    if (Tmp->ETitle() == IDOK)
      SendMessage(FrameWnd, WM_EDITCLOSING, 0, (LPARAM)Tmp);
  }
  SetFocus(ActiveFile->ListWnd);
}

int EBuf2Dlg(HWND Dlg, LPRef ARef)
{
  // Return FALSE if this reference already has authors
  SetDlgItemText(Dlg, id_Authors, ARef->authors ? ARef->authors : _T(""));
  SetDlgItemText(Dlg, id_Year, ARef->date ? ARef->date : _T(""));
  CheckRadioButton(Dlg, id_Article, id_Article + 2, id_Article + ARef->reftype);
  return (ARef->authors == NULL);
}

int EDlg2Buf(HWND Dlg, LPRef ARef)
{
  LPTSTR t;

  t = (LPTSTR)malloc(SCRATCH_SIZE);
  GetDlgItemText(Dlg, id_Authors, t, SCRATCH_SIZE - 2);

  if (ARef->authors)
    free(ARef->authors);

  if (*t != _T('\0'))
    ARef->authors = _tcsdup(t);
  else
    ARef->authors = NULL;

  GetDlgItemText(Dlg, id_Year, t, 20);

  if (ARef->date)
    free(ARef->date);

  if (*t != _T('\0'))
    ARef->date = _tcsdup(t);
  else
    ARef->date = NULL;

  ARef->reftype = IsDlgButtonChecked(Dlg, id_Article + 1);

  if (ARef->reftype == 0)
    ARef->reftype = IsDlgButtonChecked(Dlg, id_Article + 2) << 1;

  ARef->GetSortStr(t, FLG_SORT_INTERNAL, ActiveFile->Refs->s1);

  free(ARef->sortstr);
  ARef->sortstr = _tcsdup(t);

  free(t);
  return TRUE;
}

BOOL EA_OnInitDialog(HWND Wnd, HWND hwndFocus, LPARAM lParam)
{
  LPRef ThisRef;

  ThisRef = (LPRef)lParam;
  SetWindowLong(Wnd, DWL_USER, (long)ThisRef);

  if (EBuf2Dlg(Wnd, ThisRef))
    ThisRef->Flags |= RF_NeedsUpdating;

  return TRUE;
}

void EA_OnCommand(HWND Wnd, int id, HWND hwndCtl, UINT codeNotify)
{
  LPRef ThisRef;

  ThisRef = (LPRef)GetWindowLong(Wnd, DWL_USER);

  if (codeNotify == EN_UPDATE)
    ThisRef->Flags |= RF_NeedsUpdating;

  switch (id)
  {

  case id_Article:
  case id_Article + 1:
  case id_Article + 2:
    ThisRef->Flags |= RF_NeedsUpdating;
    break;

  case IDOK:
  {
    if (ThisRef->Flags & RF_NeedsUpdating)
    {
      if (EDlg2Buf(Wnd, ThisRef))
      {
        if (ActiveFile)
          ActiveFile->NeedsSaving = TRUE;
        EndDialog(Wnd, IDOK);
      }
    }
    else
      EndDialog(Wnd, IDCANCEL);

    break;
  }

  case IDCANCEL:
    EndDialog(Wnd, IDCANCEL);
    break;
  }
}

BOOL CALLBACK EAuthors(HWND Wnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  switch (Msg)
  {
    HANDLE_MSG(Wnd, WM_INITDIALOG, EA_OnInitDialog);
    HANDLE_MSG(Wnd, WM_COMMAND, EA_OnCommand);
  }
  return (FALSE);
}
