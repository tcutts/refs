#include "inc/globals.h"
#include "inc/rcutpast.h"
#include "inc/refpaint.h"
#include "rimpexp/rimpexp.h"

LPSrchColl CutPasteColl;

void DeleteThem(LPRefWndData DelFrom, int NoWarn){
// NoWarn is used internally to force some deletions
  int N, T, *AnInt, *Ptr;
  _TCHAR t1[RES_STR], t2[RES_STR];

  N = ListBox_GetSelCount(DelFrom->ListWnd);
  
  if (N){
  
    // Ask user for confirmation if necessary
    T = IDYES;
  
    if ((DelFrom!=BibData) && (!NoWarn) && ((MasterFlags & 48) > 16)){
  
      if ((N>1) || ((MasterFlags & 48)==48)){
        
        LoadString(ResInstance, err_ConfirmDel, t1, SCRATCH_SIZE-1);
        LoadString(ResInstance, wrn_Warning, t2, SCRATCH_SIZE-1);
        T = MessageBox(FrameWnd, t1, t2, MB_YESNO | MB_ICONSTOP);
      
      }
      
    }
    
    if (T!=IDYES)
      return;
    
    // Get selected items
    Ptr = (int *)malloc(N*sizeof(int));
    
    if (Ptr){
      
      ListBox_GetSelItems(DelFrom->ListWnd, N, Ptr);
      
      for (AnInt=&Ptr[N-1] ; AnInt >= Ptr ; AnInt--){
        // Get the ref to be removed
        DelFrom->Refs->atremove((long)*AnInt);
        ListBox_DeleteString(DelFrom->ListWnd, *AnInt);
      }


#ifdef WIN32
      DefaultStatus();
#else
      InvalidateRect(FrameWnd, &StatusRect, TRUE);
#endif

      // Reset selection to top of (ex) selected bunch
      ListBox_SetCurSel(DelFrom->ListWnd, *Ptr);
      DelFrom->NeedsSaving = TRUE;

      if (DelFrom==BibData){
        // if bibliography is now empty, destroy it completely
        if (DelFrom->Refs->count==0){
          SendMessage(DelFrom->Window, WM_CLOSE, 0, 0);
          BibData = NULL;
        }
        // Redraw the client window so that all references get updated properly by the change
        RedrawWindow(ClientWnd, NULL, NULL, RDW_FRAME | RDW_INVALIDATE | RDW_ALLCHILDREN);
      }

      free(Ptr);
    }
  }
}


void CopyThem(LPRefWndData CpFrom){
  int *AnInt, *Ptr, N;

  // Get selected items, and place them in the CutPasteColl
  N = ListBox_GetSelCount(CpFrom->ListWnd);
  Ptr = (int *)malloc(N*sizeof(int));
  if (Ptr){
    ListBox_GetSelItems(CpFrom->ListWnd,  N, Ptr);
    
    if (CutPasteColl)
      delete CutPasteColl;
    
    CutPasteColl = new TSrchColl(20, FALSE, NULL);
    
    for (AnInt = &Ptr[N-1] ; AnInt>=Ptr; AnInt--)
      CutPasteColl->insert(((LPRef)CpFrom->Refs->at((long)*AnInt))->Duplicate());
    free(Ptr);
  }
}


void AddTheWords(LPRef a, LPTSTR somewords){
  LPTSTR p, t;
  int n;

  if (!a->keywords)
    a->keywords=_tcsdup(somewords);
  else {
  
    t=(LPTSTR)malloc(SCRATCH_SIZE);
  
    n = _stprintf(t, _T("%s"), a->keywords) - 1;
    p = &t[n];
  
    free(a->keywords);
  
    if (!_tcschr(_T("\r\n"), *p))
      lstrcat(t, _T("\r\n"));
  
    lstrcat(t, somewords);
  
    a->keywords=_tcsdup(t);

    free(t); 
  }
}


void Key_OnCommand(HWND Dlg, int id, HWND hwndCtl, UINT codeNotify){
  long n, t;
  int *p, *a;
  _TCHAR *w, *ow, num[8], a_word[128], *t1, *t2;
  HWND TWnd;
  HCURSOR OC;

  switch (id){
    case button_Save:{

      CCursor = LoadCursor(0, IDC_WAIT);
      OC = SetCursor(CCursor);

      EnableWindow(Dlg, FALSE);
      
      DeleteConfigTree(_T("Keywords"));
      
      for (n=0, t=ListBox_GetCount(keylist); n<t ; n++){

        _itot(n, num, 10);
        ListBox_GetText(keylist, n, a_word);
        SetConfigStr(_T("Keywords"), num, a_word);

        if ((n & HOW_OFTEN)==0)
          Pause(0, FALSE);

      }
      
      EnableWindow(Dlg, TRUE);
      
      CCursor=OC;
      SetCursor(OC);
      
      break;
    }

    case IDOK:{
      
      words[0]=_T('\0');
      
      for (n=0, t=ListBox_GetCount(keylist); n<t ; n++){
        
        if (ListBox_GetSel(keylist, n)>0){
          
          ListBox_GetText(keylist, n, a_word);
          
          if (words[0]!=_T('\0'))
            lstrcat(words, _T("\r\n"));
    
          if ((lstrlen(words)+lstrlen(a_word))<399)
            lstrcat(words, a_word);

        }
      
      }
      
      EndDialog(Dlg, IDOK);
      break;
    }
    
    case IDCANCEL:{  
      words[0]=_T('\0');
      EndDialog(Dlg, IDCANCEL);
      break;
    }
    
    case edit_Add:{
      if (codeNotify==EN_CHANGE){
        n=Edit_LineLength(GetDlgItem(Dlg, edit_Add), 0);
        EnableWindow(GetDlgItem(Dlg, button_Add), n!=0);
      }
      break;
    }
    
    case id_KeyList:{
      
      if (codeNotify==LBN_SELCHANGE){
        n=ListBox_GetSelCount(keylist);
        EnableWindow(GetDlgItem(Dlg, button_Del), n>0);
        EnableWindow(GetDlgItem(Dlg, IDOK), CanAddToRef && (n>0));
        EnableWindow(GetDlgItem(Dlg, button_Edit), n==1);
      }
      break;
    }

    case button_Add:{
      
      GetDlgItemText(Dlg, edit_Add, words, 399);
      
      for (w=_tcschr(words, _T('\r')); w!=NULL; w=_tcschr(w, _T('\r'))){
        w[0]=_T(' ');
        w[1]=_T(' ');
      }
      
      if (ListBox_FindStringExact(keylist, -1, words)==LB_ERR)
        ListBox_AddString(keylist, words);
       
      break;
    }
    
    case button_Del:{

      n=ListBox_GetSelCount(keylist);
      p=(int *)malloc(n*sizeof(int));

      if (p) {
        ListBox_GetSelItems(keylist, n, p);

        for (a=&p[n-1]; a>=p; a--)
          ListBox_DeleteString(keylist, *a);

        EnableWindow(GetDlgItem(Dlg, button_Del), FALSE);
        EnableWindow(GetDlgItem(Dlg, button_Edit), FALSE);

        free(p);
      }
      break;
    }

    case button_Edit:{
      p=(int *)malloc(sizeof(int));

      if (p) {
        ListBox_GetSelItems(keylist, 1, p);
        ListBox_GetText(keylist, *p, words);
        SetDlgItemText(Dlg, edit_Add, words);
        ListBox_DeleteString(keylist, *p);

        EnableWindow(GetDlgItem(Dlg, button_Del), FALSE);
        EnableWindow(GetDlgItem(Dlg, button_Edit), FALSE);
        free(p);
      }
      break;
    }
    
    case idb_Scan:{
      t1=(_TCHAR *)malloc(SCRATCH_SIZE);
      t2=(_TCHAR *)malloc(SCRATCH_SIZE);

      CCursor=LoadCursor(0, IDC_WAIT);
      OC = SetCursor(CCursor);

      EnableWindow(Dlg, FALSE);
      
      TWnd = CreateDialogParam(ResInstance, _T("CLEAN"), Dlg, CleanProc, 0);
      
      LoadString(ResInstance, str_Scanning, a_word, sizeof(a_word)/sizeof(_TCHAR));
      SetWindowText(TWnd, a_word);
      
      LoadString(ResInstance, fmt_Scanning, a_word, sizeof(a_word)/sizeof(_TCHAR));
      
      for (n=0, t=0 ; n<ActiveFile->Refs->count && t>=0 ; n++){
      
        if ((n & HOW_OFTEN)==0){
          wsprintf(t1, a_word, n);
          SetDlgItemText(TWnd, id_LoadingRef, t1);
          Pause(TWnd, FALSE);
        }
      
        w=((LPRef)ActiveFile->Refs->at(n))->keywords;
      
        if (w){
      
          lstrcpy(t2, w);
      
          w=t2;
      
          do {
            ow=w;
            w=_tcschr(w, _T('\r'));
      
            if (w) {
              *w=_T('\0');
              w+=2;
            }
      
            if ((IsCharAlphaNumeric(*ow) && ListBox_FindStringExact(keylist, 0, ow)==LB_ERR))
              t=ListBox_AddString(keylist, ow);
      
          } while (w && (t>=0));
      
        }
      }
      free(t2);
      free(t1);
      DestroyWindow(TWnd);
      BringWindowToTop(Dlg);
      EnableWindow(Dlg, TRUE);

      CCursor=OC;
      SetCursor(OC);

      EnableWindow(GetDlgItem(Dlg, idb_Scan), FALSE);
      break;
    }
    case cm_Help: WinHelp(FrameWnd, HelpName, HELP_CONTEXT, 9);break;
  }
}


BOOL Key_OnInitDialog(HWND Dlg, HWND hwndFocus, LPARAM lParam){
  long n, t;
  _TCHAR num[8];

  keylist=GetDlgItem(Dlg, id_KeyList);

  for (n=0, t=1; t; n++){
    _ltot(n, num, 10);
    t=GetConfigStr(words, 399, _T("Keywords"), num, _T(""));
    if (t)
      ListBox_AddString(keylist, words); 
  }

  CanAddToRef = lParam;

  EnableWindow(GetDlgItem(Dlg, button_Add), FALSE);
  EnableWindow(GetDlgItem(Dlg, button_Del), FALSE);
  EnableWindow(GetDlgItem(Dlg, button_Edit), FALSE);
  EnableWindow(GetDlgItem(Dlg, IDOK), FALSE);
  EnableWindow(GetDlgItem(Dlg, idb_Scan), ActiveFile!=NULL);

  return TRUE;
}


BOOL inline Key_OnSetCursor(HWND hwnd, HWND hwndCursor, UINT codeHitTest, UINT msg){

  SetCursor(CCursor);
  return TRUE;

}


BOOL CALLBACK  KeyProc(HWND Dlg, UINT Msg, WPARAM wParam, LPARAM lParam){

  switch (Msg){

    HANDLE_MSG(Dlg, WM_COMMAND, Key_OnCommand);
    HANDLE_MSG(Dlg, WM_SETCURSOR, Key_OnSetCursor);
    HANDLE_MSG(Dlg, WM_INITDIALOG, Key_OnInitDialog);

  }

  return(FALSE);

}


int inline GetWordsToAdd(HWND awnd, int canadd){
  return DialogBoxParam(ResInstance, _T("KEYWORDS"), awnd, KeyProc, canadd);
}


void AddKeyword(LPRefWndData AddTo){
  int *AnInt, *Ptr, N;

  if (GetWordsToAdd(AddTo ? AddTo->Window : FrameWnd, AddTo!=NULL)==IDOK){

    // Get selected items
    if (AddTo) {

      AddTo->NeedsSaving = TRUE;
      
      N = ListBox_GetSelCount(AddTo->ListWnd);
      Ptr = (int *)malloc(N*sizeof(int));

      if (Ptr){
      
        ListBox_GetSelItems(AddTo->ListWnd,  N, Ptr);
        
        for (AnInt=&Ptr[N-1]; AnInt>=Ptr ; AnInt--)
          AddTheWords((TRef *)(AddTo->Refs->at((long)*AnInt)), words);
          
      }
      
    }
  }
}


void PasteIt(LPRefWndData PasteTo, LPRef ARef){
  LPRef Tmp;
  long n;

  Tmp = ARef->Duplicate();

  if ((n=PasteTo->Refs->insert(Tmp))>=0){

    PasteTo->Refs->display(n);

#ifdef SERIALNO    
    PasteTo->Refs->assign_serial(Tmp);
#endif

    if (PasteTo->ListFlags & FLG_SELECT_NEW)
      ListBox_SetSel(PasteTo->ListWnd, TRUE, PasteTo->Refs->indexof(Tmp));

    PasteTo->NeedsSaving = TRUE;

  }
}

void PasteThem(LPRefWndData PasteTo){
  long N, t;

  // disable redraws while inserting, for speed
  SetWindowRedraw(PasteTo->ListWnd, FALSE);
  
  t = CutPasteColl->count-1;
  
  for (N = 0; N<=t ; N++)
    PasteIt(PasteTo, (LPRef)(CutPasteColl->at(N)));
  
  // Redraw list box
  SetWindowRedraw(PasteTo->ListWnd, TRUE);
  InvalidateRect(PasteTo->ListWnd, NULL, TRUE);

}

void AddToBib(LPRefWndData AddFrom){
  LPRef ARef;
  int *AnInt, *Ptr, N;
  HWND AddWnd;
  long t;

  N = ListBox_GetSelCount(AddFrom->ListWnd);

  if (N)
  {
    // Get exactly space required for lb_GetSelItems
    Ptr=(int *)malloc(N*sizeof(int));

    if (Ptr){

      if (!BibData){
        // Bibliography does not exist, so create it
        AddWnd = ActiveFile->Window;
        SendMessage(FrameWnd, WM_COMMAND, cm_BibCreate, 0);

        // and activate it
        SendMessage(ClientWnd, WM_MDIACTIVATE, (WPARAM)AddWnd, 0);
        BringWindowToTop(BibData->Window);

      }

      // Get list of selected items
      ListBox_GetSelItems(AddFrom->ListWnd, N, Ptr);

      SetWindowRedraw(AddFrom->Window, FALSE);
      SetWindowRedraw(BibData->Window, FALSE);
      
      for (AnInt = Ptr ; AnInt<=&Ptr[N-1] ; AnInt++)
      {

        // Get selected reference
        ARef = (LPRef)AddFrom->Refs->at((long)*AnInt);

        if (BibData->Refs->indexof(ARef)==-1)
        {
          // Bung it in the bibliography
          t=BibData->Refs->insert(ARef);
        
          // Show it if bibliography is in list mode
          if (!BibIsFormatted)
            BibData->Refs->display(t);
        
          // Redraw string in file window in new colour
          ListBox_DeleteString(AddFrom->ListWnd, *AnInt);
          AddFrom->Refs->display(*AnInt);
          ListBox_SetSel(AddFrom->ListWnd, TRUE, *AnInt);

        }
      }

      SetWindowRedraw(BibData->Window, TRUE);
      RedrawWindow(BibData->Window, NULL, NULL, RDW_INVALIDATE);
      SetWindowRedraw(AddFrom->Window, TRUE);
      RedrawWindow(AddFrom->Window, NULL, NULL, RDW_INVALIDATE);

      if (BibIsFormatted)  // Redraw edit control contents
        BibData->Format(BibIsFormatted);

      free(Ptr);
    }
  }
}
