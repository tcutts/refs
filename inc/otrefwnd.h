#ifndef OTREFWND_H
#include "object.h"

#ifdef USE_RTF
#include "richedit.h"
#endif

struct TSrchColl;
typedef TSrchColl * LPSrchColl;

struct TRefWndData:TObject {
  _TCHAR FPath[MAX_PATH];
  _TCHAR *SrchPat;
  int SrchFlag, NeedsSaving;
  HWND Window, ListWnd, SWnd;
  LPSrchColl Refs;
  int ListFlags;
    /*widest string, used for horizontal scrollbar settings
     when looking at reference titles*/
  TSName NameSort;
  unsigned int ClmnWdth;
  int Stops;
  int SortFlags[3];
  TRefWndData(void);
  virtual ~TRefWndData(void);
  LONG UpdateCurrent(void);
  void CreateMainList(void);
  void DestroyColls(void);
  void Format(int AsEdit);
  void Resize(int cx, int cy);
  void ReSort(void);
  void NewSearch(int Whatsort);
  void NameWnd(void);
  int CanClose(void);
};

extern "C" UINT CALLBACK _export OpenHook(HWND, UINT, WPARAM, LPARAM);
extern "C" BOOL CALLBACK _export SrchDlg(HWND, UINT, WPARAM, LPARAM);
extern void BibSave(void);

#define OTREFWND_H

#endif
