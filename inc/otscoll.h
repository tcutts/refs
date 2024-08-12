#ifndef OTSCOLL_H
#include "mycolls.h"

#define FLG_SORT_ORDER 0x0008

struct TRefWndData;
typedef TRefWndData * LPRefWndData;

struct TRef;
typedef TRef * LPRef;

struct TSrchColl:TSortedCollection {
  LPTSTR s3;
  LPTSTR s2;
  LPTSTR s1;
  LPRefWndData RefWnd;
  long max_serial;
  HWND ProgressWnd; // for use by progress dialogs
  TSrchColl(long alimit, int allowdups, LPRefWndData aparent);
  virtual ~TSrchColl();
  virtual void removeall(void);
  virtual void atremove(long index);
  virtual void remove(LPObject item);
  virtual long atinsert(long index, LPObject item);
  virtual long insert(LPObject item);
#ifdef SERIALNO
  long assign_serial(LPRef item);
  void assign_serials(void);
#endif
  void redisplay(void);
  void display(long Index);
  virtual int compare(void *key1, void *key2);
  int refsrch(int by, LPTSTR txt, TSrchColl *addto, int flags);
  int forgetit(LPObject item, long anti);
  int FillBibWnd(long startfrom, LPTSTR BibTeX);
};

extern "C" BOOL CALLBACK _export DuplProc(HWND, UINT, WPARAM, LPARAM);

#define OTSCOLL_H
#endif
