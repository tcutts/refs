#ifndef GLOBALS_H
#ifdef UNICODE
#define _UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <mmsystem.h>
#include <shellapi.h>
#include <commdlg.h>

#include "config.h"

#ifdef WIN32
#include <wingdi.h>
#include <winver.h>
#else
#include <ctl3d.h>
#include <ver.h>
#endif

#if defined(CC_STATUS) || defined(CC_TOOLBAR)
#include <commctrl.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <dos.h>
#include <sys/stat.h>
#include <windowsx.h>

#ifdef _DEBUG
extern FILE *dbg;
#define TRACE(x)     \
  _ftprintf(dbg, x); \
  fflush(dbg)
#endif

#ifdef WIN32

// _export breaks VC++ 2.x, so define it to nothing
#define _export
#define EXENAME _T("REFS32.EXE")
#define REG_VER_KEY _T("Software\\TJRC\\RSet")
#define HAVE_STRSPNP

#else // not Win32

#define EXENAME _T("REFS.EXE")
#ifndef LPTSTR
#define LPTSTR LPSTR
#define LPCTSTR const LPSTR
#define _tcsspnp
#endif
#undef HAVE_STRSPNP

#endif // not Win32

#ifndef LPBOOL
#define LPBOOL BOOL *
#endif

#define strend(A) &A[lstrlen(A)]

// intra-program messages
#define WM_RESORT WM_USER + 2
#define WM_NEWDATA WM_USER + 3
#define WM_EDITCLOSING WM_USER + 4
#define WM_STOPBROWSING WM_USER + 5

#define SHOW_ALL 7
#define MAX_FIELDS 10

typedef struct
{
  int sort_method;
  int surname_last;
  _TCHAR separator[20];
} TSName;

typedef TSName *LPTSName;

typedef struct
{
  int x, y, w, h, ismax;
} TESz;

typedef TESz *LPTESz;

#include "refs.h"
#include "otref.h"
#include "otscoll.h"
#include "otrefwnd.h"

struct TRefFont;
typedef TRefFont *LPRefFont;

// bugger knows precisely how this works
typedef LPTSTR(CALLBACK *SPECPROC)(void);

#if !defined(WIN32) && defined(CC_TOOLBAR)
// function types for loading Common control functions in Windows 3.x
typedef void(CALLBACK *INITCOMMCTRLPROC)(void);
typedef HWND(CALLBACK *CREATETOOLBARPROC)(HWND, DWORD, WORD, int, HINSTANCE, WORD, LPTBBUTTON, int);
#endif

// GLOBALS.CPP
extern void strlcpy(LPTSTR, LPTSTR, long);
extern void strlcat(LPTSTR, LPTSTR, long);
extern _TCHAR *mstrchr(LPTSTR, _TCHAR);
extern void ErrorBox(HWND, int);
extern void Pause(HWND, int);
extern "C" BOOL CALLBACK CleanProc(HWND, UINT, WPARAM, LPARAM);

#ifndef IN_GLOBALS_CPP

#ifdef CC_TOOLBAR
extern HWND NextClipChain;
#ifndef WIN32
extern HINSTANCE CommCtrlAvail;
extern INITCOMMCTRLPROC InitCommonControlsDynamic;
extern CREATETOOLBARPROC CreateToolbarDynamic;
#endif
#endif

extern _TCHAR words[400];
extern HWND keylist;
extern int CanAddToRef;

extern int Is95;

extern HINSTANCE hinstCurrent;

extern HFONT datafont;
extern _TCHAR *TitleName;
extern _TCHAR *FRAMECLASS;
extern _TCHAR *FILECLASS;
extern _TCHAR *EDITCLASS;

// file names
extern _TCHAR HelpName[MAX_PATH];
extern _TCHAR DefModule[MAX_PATH];

// INI file sections and members
extern _TCHAR *DStrFiles;
extern _TCHAR *DStrEditor;
extern _TCHAR *DStrShow;
extern _TCHAR *DStrDisplay;
extern _TCHAR *DStrInput;
extern _TCHAR *DStrBib;
extern _TCHAR *DStrBIsF;
extern _TCHAR *DStrBibCol1;
extern _TCHAR *DStrBibCol2;
extern _TCHAR *DStrDefSrc;
extern _TCHAR *DStrDefYr;
extern _TCHAR *DStrFmt;
extern _TCHAR *DStrFmts;
extern _TCHAR *DStrBak;
extern _TCHAR *DStrList;
extern _TCHAR *DStrClmnWdth;
extern _TCHAR *DStr1993;
extern _TCHAR *DStrDefCase;
extern _TCHAR *DStrDefSrch;
extern _TCHAR *DStrSrchBy;
extern _TCHAR *DStrSort;
extern _TCHAR *DStrFonts;
extern _TCHAR *DStrPrint;
extern _TCHAR *DStrLink;
extern _TCHAR *DStrNames;
extern _TCHAR *DStrSurLast;
extern _TCHAR *DStrNameSrt;
extern _TCHAR *DStrSurSep;
extern _TCHAR *DStr3D;

// space for word used in author lists meaning "and"
extern _TCHAR AndWord[12];

// file spec strings used with GetSaveFilename etc
extern _TCHAR *FileSpecs;
extern _TCHAR *BibFSpecs;
extern _TCHAR *RTFFSpecs;
extern _TCHAR *OldFile[OLD_FILES];

// bitmap handles for listboxes
extern HBITMAP BmpHnd[6];

// miscellaneous flags
extern int IsMaximized;
extern int Registered;

// resource module handle
extern HINSTANCE ResInstance;

// master sorting flags
extern int MSortFlags[3];

// what is the active MDI child?
extern LPRefWndData ActiveFile;
// pointer to bibliography object
extern LPRefWndData BibData;
extern LPRefWndData FromWnd;
// how many MDI clients currently around?
extern int Clients;

// more flags
extern int MakeBak, DefSrchFlag, AutoShow, IsCtl3D;
extern UINT HlpMsg;
extern int MasterFlags;
extern TSName NEAR MSortName;

// Cursor handles
extern HCURSOR CCursor;
extern HCURSOR MCursor;
extern HCURSOR SCursor;

// mouse button state
extern int RBtnDown;

// window handles etc
extern HWND FrameWnd, ClientWnd;
extern HMENU FMenu;
extern HACCEL Accs;

#ifndef CC_STATUS
extern RECT NEAR StatusRect;
#endif

extern int StatusHeight;

extern int ListHeight, CharWidth, DateWidth;

// font handle
extern HFONT DFont;
extern LPRefFont PrnFnt;
extern LPRefFont ListFnt;
extern LPRefFont EditFnt;
extern TEXTMETRIC NEAR TM;

// yet more flags and options
extern COLORREF BibCol;
extern int BibIsFormatted, MasterWdth;

// what's the default year/source
extern _TCHAR DfltYr[20];
extern int DfltSrc;

// current bibliography format name
extern _TCHAR FmtName[MAX_FMT_LENGTH];
// and its strings
extern _TCHAR FmtString[MAX_FMT_LENGTH], FmtPrefix[MAX_FMT_LENGTH], FmtSuffix[MAX_FMT_LENGTH];

#ifndef WIN32
// Somewhere to store the INI file name.
extern _TCHAR INIFile[MAX_PATH];
#endif

// name for untitled files
extern _TCHAR Untitled[32];

extern LPRef Current;

// searching routines
extern int SrchBy;
extern _TCHAR SrchFor[256];
extern int SrchFlags, stflg;

#define SF_IGNORECASE 1
#define SF_NOT 2
#define SF_REGEXP 4

extern BOOL ClosedThisOne;
extern LPRefWndData NewWnd;

#endif // not IN_GLOBALS_CPP

#define GLOBALS_H
#endif //! GLOBALS_H
