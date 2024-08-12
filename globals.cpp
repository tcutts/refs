#define IN_GLOBALS_CPP
#include "inc/globals.h"
#include "inc/refimp.h"

#ifdef _DEBUG
// file for debug output
FILE *dbg;
#endif

// flag set if we are running under Windows 95
int Is95;

#ifdef CC_TOOLBAR
HWND NextClipChain;
#ifndef WIN32
HINSTANCE CommCtrlAvail;
INITCOMMCTRLPROC InitCommonControlsDynamic;
CREATETOOLBARPROC CreateToolbarDynamic;
#endif
#endif

// module instance handle
HINSTANCE hinstCurrent;

BOOL ClosedThisOne;

// font used in database windows
HFONT datafont;

#ifdef FERIC
_TCHAR *TitleName = _T("Feric Refs");
#else
_TCHAR *TitleName = _T("Refs");
#endif
_TCHAR *FRAMECLASS = _T("TCRefFrame");
_TCHAR *FILECLASS = _T("TCRefChild");
_TCHAR *EDITCLASS = _T(ECLSNAME);

  // file names
#ifdef WIN32
_TCHAR HelpName[MAX_PATH] = _T("REFS32.HLP");
#else
_TCHAR HelpName[MAX_PATH] = _T("REFS.HLP");
#endif
_TCHAR DefModule[MAX_PATH] = _T("REFER.FLT");

  // INI file sections and members
_TCHAR *DStrFiles = _T("Files");
_TCHAR *DStrEditor = _T("EditDlg");
_TCHAR *DStrShow = _T("AutoView");
_TCHAR *DStrDisplay = _T("Display");
_TCHAR *DStrInput = _T("Input");
_TCHAR *DStrBib = _T("Bibliography");
_TCHAR *DStrBIsF = _T("BibIsForm");
_TCHAR *DStrBibCol1  = _T("BibCol1");
_TCHAR *DStrBibCol2 = _T("BibCol2");
_TCHAR *DStrDefSrc = _T("DefaultSource");
_TCHAR *DStrDefYr = _T("DefaultYear");
_TCHAR *DStrFmt = _T("Format");
_TCHAR *DStrFmts = _T("Formats");
_TCHAR *DStrBak = _T("Backup");
_TCHAR *DStrList = _T("List");
_TCHAR *DStrClmnWdth = _T("ColumnWidth");
_TCHAR *DStr1993 = _T("1994");
_TCHAR *DStrDefCase = _T("Search");
_TCHAR *DStrDefSrch = _T("SrchWnd");
_TCHAR *DStrSrchBy = _T("SrchBy");
_TCHAR *DStrSort = _T("Sort");
_TCHAR *DStrFonts = _T("Fonts");
_TCHAR *DStrPrint = _T("Printer");
_TCHAR *DStrLink = _T("Link");
_TCHAR *DStrNames = _T("Names");
_TCHAR *DStrSurLast = _T("SurLast");
_TCHAR *DStrNameSrt = _T("Method");
_TCHAR *DStrSurSep = _T("SurSep");
_TCHAR *DStr3D = _T("Is3D");

// space for word used in author lists meaning "and"
_TCHAR AndWord[12];

// file spec strings used with GetSaveFilename etc
_TCHAR *FileSpecs = _T("Refer file (*.ref)\0*.REF\0All files (*.*)\0*.*\0\0");
_TCHAR *BibFSpecs = _T("Text file  (*.TXT)\0*.TXT\0All files (*.*)\0*.*\0\0");
_TCHAR *RTFFSpecs = _T("Rich text file (*.RTF)\0*.RTF\0All files (*.*)\0*.*\0\0");
// most recently used file list
_TCHAR *OldFile[OLD_FILES] = {NULL, NULL, NULL, NULL, NULL, NULL};

// bitmap handles for listboxes
HBITMAP  BmpHnd[6] = {0,0,0,0,0,0};

// miscellaneous flags
int IsMaximized = FALSE;
#ifndef CUSTOM
int Registered = FALSE;
#else
int Registered = TRUE;
#endif

// resource module handle
HINSTANCE ResInstance = 0;

// master sorting flags
int MSortFlags[3] = {0,9,2};

// what is the active database?
LPRefWndData ActiveFile = NULL;

// pointer to bibliography object
LPRefWndData BibData = NULL;

// Window from which a drag is coming
LPRefWndData FromWnd;

// Temporary store of newly created windows.
LPRefWndData NewWnd;

// how many MDI clients currently around?
int Clients = 0;

// more flags
int MakeBak, DefSrchFlag, AutoShow, IsCtl3D;
UINT HlpMsg;
int MasterFlags;
TSName NEAR MSortName;

// window handles etc
HWND FrameWnd=NULL;
HWND ClientWnd=NULL;
HMENU FMenu=NULL;
HACCEL Accs;

#ifndef WIN32
RECT NEAR StatusRect;
#endif
int StatusHeight;

int ListHeight;
int CharWidth, DateWidth;
TEXTMETRIC NEAR TM;

int RBtnDown;
HCURSOR SCursor, MCursor, CCursor;

// font handles
HFONT DFont;
LPRefFont PrnFnt;
LPRefFont ListFnt;
LPRefFont EditFnt;

// yet more flags and options
COLORREF BibCol;
int BibIsFormatted, MasterWdth;

// what's the default year/source
_TCHAR DfltYr[20];
int DfltSrc;

// current bibliography format name
_TCHAR FmtName[MAX_FMT_LENGTH];
// and its component strings
_TCHAR FmtString[MAX_FMT_LENGTH];
_TCHAR FmtPrefix[MAX_FMT_LENGTH];
_TCHAR FmtSuffix[MAX_FMT_LENGTH];

#ifndef WIN32
// Where's the INI file?
_TCHAR INIFile[MAX_PATH];
#endif

// name for untitled files
_TCHAR Untitled[32];

// pointer to currently selected reference
// this ought to be moved into TRefWndData at some point
LPRef Current;

// searching routines
int SrchBy = 3;
_TCHAR SrchFor[256];
int SrchFlags, stflg;

// stuff used by RCUTPAST
_TCHAR words[400];
HWND keylist;
int CanAddToRef;

void ErrorBox(HWND AParent, int Err) {
  _TCHAR t[RES_STR];

  LoadString(ResInstance, Err, t, RES_STR);
  MessageBox(AParent, t, NULL, MB_OK | MB_ICONEXCLAMATION);
}

// Globals used by REFIMP.CPP
// currently selected library stored here
_TCHAR libname[14], thenum[4], *flts[32];
HINSTANCE LibHnd;
int n, OEMode, Finished;
OPTPROC optproc;
IMPPROC ImpProc;
EXPPROC ExpProc;

// a few globally useful functions

_TCHAR *mstrchr(_TCHAR *p, _TCHAR c){
  _TCHAR *q;
  for (q=p ; (*q!=_T('\0'))&&(*q!=c) ; q++) {}
  return ((*q==c) ? q : NULL);
}

void inline strlcpy(_TCHAR *d, _TCHAR *s, long l){
  long n;
  for (n=0; (n<l) && (s[n]!=_T('\0')); d[n]=s[n], n++);
  d[n]=s[n];
  d[n+1]='\0';
}

void inline strlcat(_TCHAR *d, _TCHAR *s, long l){
  long n;

  n=lstrlen(d);
  strlcpy(&d[n], s, l-n);
}

BOOL inline Clean_OnSetCursor(HWND hwnd, HWND hwndCursor, UINT codeHitTest, UINT msg){
  CCursor = LoadCursor(0, IDC_WAIT);
  SetCursor(CCursor);
  return TRUE;
}


BOOL  CALLBACK CleanProc(HWND Dlg, UINT Msg, WPARAM wParam, LPARAM lParam) {
  
  switch (Msg){
    HANDLE_MSG(Dlg, WM_SETCURSOR, Clean_OnSetCursor);
  }
  
  return FALSE;
}

void Pause(HWND Dlg, int fAbort) {
  MSG Msg;

  while ((!fAbort) && PeekMessage(&Msg, 0, 0, 0, PM_REMOVE)) {
    if ((!Dlg) || (!IsDialogMessage(Dlg, &Msg))) {
      TranslateMessage(&Msg);
      DispatchMessage(&Msg);
    }
  }
}

#undef IN_GLOBALS_CPP
