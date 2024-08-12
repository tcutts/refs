    #include "inc/globals.h"
    #include <direct.h>

    #include "inc/refio.h"
    #include "inc/refimp.h"
    #include "rimpexp/rimpexp.h"
	#include "inc/redit.h"

    void AppendOldFile(_TCHAR *Name){
      _TCHAR *t;
      int n,f;

      n = 0; f = 1;

      while (OldFile[n] && (n<OLD_FILES) && (f)){
        f = lstrcmpi(Name, OldFile[n]);
        n++;
      }

      if (f){

        if (OldFile[OLD_FILES-1])
          free(OldFile[OLD_FILES-1]);

        for (n=OLD_FILES-1; n>=1 ; n--)
          OldFile[n]=OldFile[n-1];

        OldFile[0] = _tcsdup(Name);

      } else {

        f = n-1;
        t = OldFile[n-1];

        while (f){
          OldFile[f] = OldFile[f-1];
          f--;
        }

        OldFile[0] = t;
      }

    }

    void DeleteOldFile(_TCHAR *Name){
      int n;

      for (n=0;
        ((n<OLD_FILES) && (OldFile[n]!=NULL) && (lstrcmpi(OldFile[n], Name)!=0));
        n++){}

      if ((n==OLD_FILES) || (OldFile[n]==NULL))
        return;

      free(OldFile[n]);

      while ((n<OLD_FILES) && (OldFile[n]!=NULL)){
        OldFile[n] = (n==(OLD_FILES-1)) ? NULL : OldFile[n+1];
        n++;
      }

    }
    

    void UpdateLibName(HWND Dlg){

      libname[0]=_T('\0');
      n = ListBox_GetCurSel(GetDlgItem(Dlg, id_ImpList));

      if (flts[n])
        lstrcpy(libname, flts[n]);
      else
        libname[0]=_T('\0');

      EnableWindow(GetDlgItem(Dlg, IDOK), libname[0]!=_T('\0'));

      LibHnd=LoadLibrary(libname);
      optproc=NULL;

      if (LibHnd>(HINSTANCE)32){
        optproc = (OPTPROC)GetProcAddress(LibHnd, OPTS);
        FreeLibrary(LibHnd);
      }

      EnableWindow(GetDlgItem(Dlg, id_ImpOpts), optproc!=NULL);
    }   


    void DispFlts(void){

      for (n = 0 ; n<=31; n++)

       if (flts[n]){
         free(flts[n]);
         flts[n]=NULL;
       }

    }
    

    int FilterList(HWND ListBox, long Cmd){
      _TCHAR *p;
      int n=0;
      NPROC nproc;
      BOOL test=FALSE;
      BOOL test2=FALSE;
      _TCHAR t1[MAX_PATH];

    #ifdef WIN32
      BOOL t;
      HANDLE hFind;
      WIN32_FIND_DATA finfo;
    #else
      int t;
    #ifdef __BORLANDC__
      find_t finfo;
    #else
      _find_t finfo;
    #endif
    #endif
    
      // Fill List box with available DLLs
      GetModuleFileName(hinstCurrent, t1, MAX_PATH-1);
      p=_tcsrchr(t1, _T('\\'));
      p[0]=_T('\0');
#ifdef WIN32
      if (*t1!=_T('\\'))
#endif
      _chdrive((BYTE)*t1-(BYTE)'A'+1);
      _tchdir(t1);
      lstrcpy(t1, _T("*.FLT"));
      SetBufSz(FSBUFFSZ);
    
    #ifndef WIN32
      t = _dos_findfirst(t1, 0, &finfo);

      while ((t==0)&&(n<31)){

        LibHnd = LoadLibrary(finfo.name);

        if (LibHnd >= (HINSTANCE)32){

          if ((!Cmd) || (Cmd==cm_FImport))
            test = (GetProcAddress(LibHnd, LOADREF) != NULL);

          if ((!Cmd) || (Cmd==cm_FExport))
            test2 = (GetProcAddress(LibHnd, SAVEREF) != NULL);

          switch (Cmd){
            case 0: test = (test && test2); break;
            case cm_FExport: test = test2;
          }  

          if (test){
            nproc = (NPROC)GetProcAddress(LibHnd, WHOAMI);
            flts[ListBox_AddString(ListBox, nproc())] = _tcsdup(finfo.name);
            n++;
          }

          FreeLibrary(LibHnd);
          LibHnd=0;
        }

        t=_dos_findnext(&finfo);
      }
    #else

      hFind = FindFirstFile(t1, &finfo);

      if (hFind!=INVALID_HANDLE_VALUE){

        t=TRUE;

        while (t && (n<31)){

          LibHnd = LoadLibrary(finfo.cFileName);

          if (LibHnd >= (HINSTANCE)32){

            if ((!Cmd) || (Cmd==cm_FImport))
              test = (GetProcAddress(LibHnd, LOADREF) != NULL);

            if ((!Cmd) || (Cmd==cm_FExport))
              test2 = (GetProcAddress(LibHnd, SAVEREF) != NULL);

            switch (Cmd){
              case 0: test = (test && test2); break;
              case cm_FExport: test = test2;
            }  

            if (test){
              nproc = (NPROC)GetProcAddress(LibHnd, WHOAMI);
              flts[ListBox_AddString(ListBox, nproc())] = _tcsdup(finfo.cFileName);
              n++;
            }

            FreeLibrary(LibHnd);
            LibHnd=0;
    }

    t=FindNextFile(hFind, &finfo);

        }
      }
    #endif
    
      return(n);
    }
    
    
    void ImpDlg_OnCommand(HWND Dlg, int id, HWND hwndCtl, UINT codeNotify){

      switch (id){

        case IDOK:{
          UpdateLibName(Dlg);
          DispFlts();
          EndDialog(Dlg, IDOK);
          break;
        }

        case IDCANCEL:{
          DispFlts();
          EndDialog(Dlg, IDCANCEL);
          break;
        }

        case id_ImpList:{

          if (codeNotify==LBN_SELCHANGE)
            UpdateLibName(Dlg);

          if (codeNotify==LBN_DBLCLK){
            UpdateLibName(Dlg);
            DispFlts();
            EndDialog(Dlg, IDOK);
    }

          break;
  }

        case id_ImpOpts:{

          UpdateLibName(Dlg);

          if (libname[0]!=_T('\0')){

            // load library
            LibHnd = LoadLibrary(libname);

            if (LibHnd >= (HINSTANCE)32){

              // get and run Opts function if possible
              optproc = (OPTPROC)GetProcAddress(LibHnd, OPTS);

              if (!optproc) 
                ErrorBox(Dlg, wrn_NoOptFunc);
              else
    #ifdef WIN32
                optproc(Dlg);
    #else
                optproc(Dlg, INIFile);
    #endif

              FreeLibrary(LibHnd);
        LibHnd=0;

            }
          }
        }
      }
    }
    
    
    BOOL ImpDlg_OnInitDialog(HWND Dlg, HWND hwndFocus, LPARAM lParam){
      int n;
      _TCHAR t[RES_STR];
    
      switch (lParam){
        case cm_FExport: n=LoadString(ResInstance, str_ChooseExp, t, sizeof(t)/sizeof(_TCHAR)); break;
        case 0: n=LoadString(ResInstance, cm_FileFormat, t, sizeof(t)/sizeof(_TCHAR)); break;
        default: n=0;
      }

      if (n)
        SetWindowText(Dlg, t);

      FilterList(GetDlgItem(Dlg, id_ImpList), lParam);

      EnableWindow(GetDlgItem(Dlg, IDOK), FALSE);
      EnableWindow(GetDlgItem(Dlg, id_ImpOpts), FALSE);

      return TRUE;
    }
    

    BOOL CALLBACK  ImpDlgProc(HWND Dlg, UINT Msg, WPARAM wParam, LPARAM lParam){

      switch (Msg){
        HANDLE_MSG(Dlg, WM_COMMAND, ImpDlg_OnCommand);
        HANDLE_MSG(Dlg, WM_INITDIALOG, ImpDlg_OnInitDialog);
      }

      return(FALSE);
    }
    

    int ChooseFileFormat(int Cmd){
      int n;
    
      n=DialogBoxParam(ResInstance, _T("IMPOPT"), FrameWnd, ImpDlgProc, Cmd);

      if ((!Cmd)&&(n==IDOK))
        lstrcpy(DefModule, libname);

      return(n);
    }
    

    void LoadRefs(LPRefWndData PData, LPMMIOINFO FS, HWND TWnd){
      LPRef Tmp;
      _TCHAR **SPtr, **DPtr, t[RES_STR];
      long r;
      long Impd=0;
      LPImportRef Red;
      LPRefWndData Old;
    

      Old = ActiveFile;
      ActiveFile = PData;

      LoadString(ResInstance, fmt_Importing, t, sizeof(t)/sizeof(_TCHAR));

      do {

      // import refs one by one from DLL until it returns a result > 1
    #ifdef WIN32
        Red = ImpProc(FrameWnd, FS);
    #else
        Red = ImpProc(FrameWnd, FS, INIFile);
    #endif

        Finished = (Red->Result != 0);

        if (Red->Result < 2){

          Tmp = new TRef;

          Tmp->reftype = Red->RefType;

          // copy transfer buffer to new reference
          for ( SPtr=&Red->Authors, DPtr=&Tmp->authors ; SPtr<=(&Red->Editor) ; SPtr++, DPtr++){

            if (*DPtr){
              free(*DPtr);
              *DPtr=NULL;
            }

            if (*SPtr)
              *DPtr = _tcsdup(*SPtr);
          
          }

          Tmp->GetSortStr(PData->Refs->s1, 13, PData->Refs->s2);
          Tmp->sortstr = _tcsdup(PData->Refs->s1);

          // Insert new reference 
          r = PData->Refs->insert(Tmp);

          if (r<0) 
            free(Tmp);

          Finished = (r==-2);

          Impd++;

          if ((Impd & HOW_OFTEN)==0){
            wsprintf(PData->Refs->s1, t, Impd);
            SetDlgItemText(TWnd, id_LoadingRef, PData->Refs->s1);
            Pause(TWnd, FALSE);
          }
        }
      } while (!Finished);
      
      ActiveFile = Old;

    }
    

    void SaveRefs(LPRefWndData PData, LPMMIOINFO FS, HWND TWnd){
      LPRef Tmp;
      _TCHAR **s, **d, t[RES_STR], t1[RES_STR];
      long n, f;
      TImportRef ToWrite;
    
      LoadString(ResInstance, fmt_SavedRefs, t, sizeof(t)/sizeof(_TCHAR)); 

      for (n=0 ; n<PData->Refs->count ; n++){

        Tmp = (LPRef)PData->Refs->at(n);

        for (s=&Tmp->authors, d=&ToWrite.Authors ; s < &Tmp->sortstr ; s++, d++)
          *d=(*s) ? _tcsdup(*s) : NULL;

        ToWrite.RefType=Tmp->reftype;

    #ifdef WIN32
        f=ExpProc(TWnd, &ToWrite, FS);
    #else
        f=ExpProc(TWnd, &ToWrite, FS, INIFile);
    #endif

        for (d=&ToWrite.Authors ; d < &ToWrite.SortStr ; d++) {
          if (*d) {
            free(*d);
            *d=NULL;
          }
        }

        if (f)
          return;

        if ((n & HOW_OFTEN)==0){
          wsprintf(t1, t, n);
          SetDlgItemText(TWnd, id_LoadingRef, t1);
          Pause(TWnd, FALSE);
        }

      }
      FS->dwFlags |= MMIO_DIRTY;
    }


    BOOL ImpRefs(LPRefWndData PData, int Cmd, int GetName){
      int AmSaving;
      int t;
      HCURSOR  OCursor;
      HMMIO afile;
      HWND TWnd;
      GLOBALHANDLE FSHnd;
      LPSTR FSBuff;
      LPTSTR p;
      _TCHAR t1[MAX_PATH];
      SPECPROC SpecProc;
      MMIOINFO FS = {0, NULL, NULL, 0, 0, 0, NULL, NULL, NULL, NULL, 0, 0, {0, 0, 0}, 0, 0, 0};
    
      AmSaving=((Cmd==cm_FSave)||(Cmd==cm_FSaveAs)||(Cmd==cm_FExport));

      if (AmSaving && (PData==BibData) && BibIsFormatted){
//#ifdef USE_RTF
//		((hRichEdit)BibData->ListWnd)->Save();
//#else
        BibSave();
//#endif
        return(TRUE);
      }

      t = FALSE;

      // Get format to import
      GetModuleFileName(hinstCurrent, t1, MAX_PATH-1);

      p=_tcsrchr(t1, _T('\\'));
      p[0]=_T('\0');
      _tchdir(t1);

#ifdef WIN32
      if ((*t1!=_T('\\'))) // on this machine
#endif
        _chdrive((*t1-'A')+1);

      if ((Cmd==cm_FImport)||(Cmd==cm_FExport)) {

        if (ChooseFileFormat(Cmd)==IDCANCEL){
          return(t);
  }

      } else
        lstrcpy(libname, DefModule);
      
      // Store the buffer size we're going to create in RIMPEXP.DLL
      SetBufSz(FSBUFFSZ);


      // load appropriate library
      LibHnd = LoadLibrary(libname);

      if (LibHnd >= (HINSTANCE)32){

        if (!AmSaving)
          ImpProc = (IMPPROC)GetProcAddress(LibHnd, LOADREF);
        else
          ExpProc = (EXPPROC)GetProcAddress(LibHnd, SAVEREF);

        SpecProc = (SPECPROC)GetProcAddress(LibHnd, GETSPECS);

        Finished = FALSE;

        // Get filename to open
        if (InitFile(AmSaving, GetName, SpecProc(), PData->FPath)){

          // create progress window
          TWnd = CreateDialogParam(ResInstance, _T("CLEAN"), FrameWnd, CleanProc, 0);

          EnableWindow(FrameWnd, FALSE);
          SetWindowText(TWnd, PData->FPath);
          CCursor = LoadCursor(0, IDC_WAIT);
          OCursor = SetCursor(CCursor);

          // open file
          afile = mmioOpen(PData->FPath,
               &FS,
               AmSaving ? (MMIO_CREATE | MMIO_ALLOCBUF | MMIO_WRITE) : (MMIO_ALLOCBUF | MMIO_READ));

          FSHnd = GlobalAlloc(GPTR | GMEM_DDESHARE, FSBUFFSZ+8);
          FSBuff = (LPSTR)GlobalLock(FSHnd);

          if (!afile){

            wsprintf(t1, _T("MMIOINFO.wErrorRet contains: %u"), FS.wErrorRet);
            MessageBox(FrameWnd, t1, _T("mmioOpen() failed"), MB_OK | MB_ICONSTOP);

          } else {

            mmioSetBuffer(afile, FSBuff, FSBUFFSZ, 0);
            mmioGetInfo(afile, &FS, 0);

            if (!AmSaving)
              LoadRefs(PData, &FS, TWnd);
            else
              SaveRefs(PData, &FS, TWnd);

            PData->NeedsSaving = (Cmd==cm_FImport);
            t = TRUE;

             
            if ((Cmd==cm_FOpen)||(Cmd==cm_FSaveAs))
              AppendOldFile(PData->FPath);
              
          }

          mmioSetInfo(afile, &FS, 0);
          
          if (AmSaving)
            mmioFlush(afile, 0);
          
          mmioClose(afile, 0);
          
          GlobalUnlock(FSHnd);
          GlobalFree(FSHnd);
          
          CCursor = OCursor;
          SetCursor(CCursor);

          EnableWindow(FrameWnd, TRUE);
          DestroyWindow(TWnd);

		  if (PData != BibData)
            SetWindowText(PData->Window, PData->FPath);

        }

        // release library
        FreeLibrary(LibHnd);
        LibHnd=0;

      }

      return(t);
    }
