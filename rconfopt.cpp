#include "inc/globals.h"
#include "inc/rconfopt.h"

void COpt_OnCommand(HWND Dlg, int id, HWND hwndCtl, UINT codeNotify){
  int n;

  switch (id){
    case IDOK:{
      MasterFlags &= 0xFF4F;
      for (n = 1; n<=3 ; n++){
        if (IsDlgButtonChecked(Dlg, (id_NeverDel-1) + n)) 
          MasterFlags |= (n << 4);
      }
      MasterFlags |= (IsDlgButtonChecked(Dlg, id_MouseConf)*128);
      EndDialog(Dlg, IDOK);
      break;
    }
    case IDCANCEL: EndDialog(Dlg, IDCANCEL);break;
  }
}


BOOL COpt_OnInitDialog(HWND Dlg, HWND hwndFocus, LPARAM lParam){
  CheckDlgButton(Dlg, (id_NeverDel-1)+((MasterFlags/16)&3), 1);
  CheckDlgButton(Dlg, id_MouseConf, ((MasterFlags/128)&1));
  return TRUE;
}


BOOL CALLBACK  COptProc(HWND Dlg, UINT Msg, WPARAM wParam, LPARAM lParam){
  switch (Msg){
    HANDLE_MSG(Dlg, WM_COMMAND, COpt_OnCommand);
    HANDLE_MSG(Dlg, WM_INITDIALOG, COpt_OnInitDialog);
  }
  return(FALSE);
}

void ConfOpts(void){
  DialogBox(ResInstance, _T("CONFIRM"), FrameWnd, COptProc);
}
