#include "inc/globals.h"
#include "inc/refinopt.h"

void InOpt_OnCommand(HWND Dlg, int id, HWND hwndCtl, UINT codeNotify){
  switch (id){
    case IDOK:{
      GetDlgItemText(Dlg, id_DefYear, DfltYr, 20);
      DfltSrc = IsDlgButtonChecked(Dlg, id_Article+1);
      if (!DfltSrc) 
        DfltSrc = IsDlgButtonChecked(Dlg, id_Article+2) << 1;
      EndDialog(Dlg, IDOK);
      break;
    }
    case IDCANCEL: EndDialog(Dlg, IDCANCEL);
  }
}

BOOL InOpt_OnInitDialog(HWND Dlg, HWND hwndFocus, LPARAM lParam){
  SetDlgItemText(Dlg, id_DefYear, DfltYr);
  CheckRadioButton(Dlg, id_Article, id_Article+2, id_Article+DfltSrc);
  return(FALSE);
}

BOOL CALLBACK  InOptProc(HWND Wnd, UINT Msg, WPARAM wParam, LPARAM lParam){
  switch (Msg){
    HANDLE_MSG(Wnd, WM_INITDIALOG, InOpt_OnInitDialog);
    HANDLE_MSG(Wnd, WM_COMMAND, InOpt_OnCommand);
  }
  return(FALSE);
}

void InputOpts(void){
  DialogBox(ResInstance, _T("INOPT"), FrameWnd, InOptProc);
}
