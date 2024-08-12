#include "inc/globals.h"
#include "rimpexp/rimpexp.h"
#include "inc/jlistdlg.h"

// Titles of common lists in configuration
_TCHAR *INIKey[3] = {_T("Journals"), _T("Book_titles"), _T("Reports")};
_TCHAR *INIKeyPtr;

BOOL EList_OnInitDialog(HWND Wnd, HWND hwndFocus, LPARAM lParam){
  _TCHAR um[6], t[RES_STR];
  int n, c;

  INIKeyPtr = INIKey[lParam];
  SetWindowText(Wnd, INIKeyPtr);
  
  n=GetConfigInt(INIKeyPtr, _T("Number"), 0);
  EnableWindow(GetDlgItem(Wnd, idb_Delete), n);
  EnableWindow(GetDlgItem(Wnd, idb_Change), n);
  
  for (c = 1; c<=n ; c++)
  {
    _itot(c, um, 10);
    GetConfigStr(t, sizeof(t), INIKeyPtr, um, _T("Configuration Error"));
    ListBox_AddString(GetDlgItem(Wnd, id_CommonList), t);
  }

  return TRUE;
}


void EList_OnCommand(HWND Wnd, int id, HWND hwndCtl, UINT codeNotify){
  _TCHAR t1[6], t[RES_STR];
  int n, Curl;
  HWND lb;

  switch (id)
  {
    case IDOK:
    {
      DeleteConfigTree(INIKeyPtr);
      Curl = ListBox_GetCount(GetDlgItem(Wnd, id_CommonList));
      SetConfigInt(INIKeyPtr, _T("Number"), Curl);
    
      for (n = 1; n<=Curl ; n++)
      {
        _itot(n, t1, 10);
        ListBox_GetText(GetDlgItem(Wnd, id_CommonList), n-1, t);
        SetConfigStr(INIKeyPtr, t1, t);
      }
    
      EndDialog(Wnd, IDOK);
      break;
    }

    case IDCANCEL: EndDialog(Wnd, IDCANCEL);break;
    
    case id_CommonEdit:
    {
      n=GetDlgItemText(Wnd, id_CommonEdit, t, sizeof(t)/sizeof(_TCHAR));
    
      EnableWindow(GetDlgItem(Wnd, idb_Add),
                   (n>0) && ListBox_FindStringExact(GetDlgItem(Wnd, id_CommonList), 0, t)==LB_ERR);

      break;
    }
    
    case id_CommonList:
    {
      if (codeNotify==LBN_SELCHANGE)
      {
        
        Curl = ListBox_GetCurSel(GetDlgItem(Wnd, id));
        EnableWindow(GetDlgItem(Wnd, idb_Add), Curl!=-1);
        EnableWindow(GetDlgItem(Wnd, idb_Change), Curl!=-1);
        EnableWindow(GetDlgItem(Wnd, idb_Delete), Curl!=-1);
        
        if (Curl!=-1)
        {
          ListBox_GetText(GetDlgItem(Wnd, id), Curl, t);
          SetDlgItemText(Wnd, id_CommonEdit, t);
        }
      }
      break;
    }
    
    case idb_Add:
    case idb_Change:
    case idb_Delete:
    {
      lb=GetDlgItem(Wnd, id_CommonList);
      Curl=ListBox_GetCurSel(lb);
      
      if (id != idb_Add)
        ListBox_DeleteString(lb, Curl);
      
      if (id != idb_Delete)
      {
        GetDlgItemText(Wnd, id_CommonEdit, t, sizeof(t)/sizeof(_TCHAR));
        
        if (ListBox_FindStringExact(lb, 0, t) == LB_ERR)
          Curl = ListBox_AddString(lb, t);

      }

      n = ListBox_GetCount(lb);
      n = (n>0) && (ListBox_SetCurSel(lb, Curl)!=LB_ERR);

      if (ListBox_SetCurSel(lb, Curl)!=LB_ERR)
      {
        EnableWindow(GetDlgItem(Wnd, idb_Change), n);
        EnableWindow(GetDlgItem(Wnd, idb_Delete), n);
      }

      break;
    }
  }
}


BOOL CALLBACK  EListProc(HWND Wnd, UINT Msg, WPARAM wParam, LPARAM lParam){
  switch (Msg)
  {
    HANDLE_MSG(Wnd, WM_COMMAND, EList_OnCommand);
    HANDLE_MSG(Wnd, WM_INITDIALOG, EList_OnInitDialog);
  }
  return(FALSE);
}
