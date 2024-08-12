
#ifndef OTREF_H
#include "object.h"

#define FLD_TITLE           0
#define FLD_JOURNAL         1
#define FLD_VOLUME          2
#define FLD_VOLNO           3
#define FLD_PAGES           4
#define FLD_ABSTRACT        5
#define FLD_KEYWORDS        6
#define FLD_PUBLISHER       7
#define FLD_CITY            8
#define FLD_EDITORS         9

#define FLG_SHOW_TITLE    0x0004
#define FLG_NOT_TABBED    0x0008
#define FLG_SELECT_NEW    0x0040
#define FLG_CONFIRM_MOUSE 0x0080
#define FLG_EDITOR        0x0100
#define FLG_YEAR_ONLY     0x0200
#define FLG_SORT_INTERNAL 0x000D

typedef struct
{
  BOOL bInitialsFirst;
  BOOL bWantInitials;
  BOOL bAndBeforeLast;
  BOOL bWantEtAl;
  BOOL bAllCaps;
  int  iNumAuthors;
  _TCHAR lpszNameSep[12];
  _TCHAR lpszInitNameSep[4];
  _TCHAR lpszAnd[20];
  _TCHAR lpszEtAl[20];
} AuthorOpt;

#define RF_CanBrowse		(int)0x1
#define RF_NeedsUpdating	(int)0x2
#define RF_DontResort		(int)0x4
#define RF_DontUpdate		(int)0x8
#define RF_NeedsInserting	(int)0x10
#define RF_EditModal		(int)0x20

struct TRefWndData;
typedef TRefWndData * LPRefWndData;

struct TRef:TObject {
  int reftype, links, Flags;
  long serial_no;
  HWND hwndEditor;
  LPRefWndData OpenedFrom;
  _TCHAR *authors, *date, *title, *journal;
  _TCHAR *vol, *volno, *pages, *text, *keywords;
  _TCHAR *publisher, *city, *editor, *sortstr;
  TRef(void);
  void GetSortStr(_TCHAR *atarget, int flags, _TCHAR *t);
  virtual ~TRef(void);
  TRef FAR *Duplicate(void);
  void Edit(int allowmove);
  int ETitle(void);
  int FormatRef(_TCHAR *atarget);
  int GetYear(_TCHAR *atarget);
private:
  int DoDlg(_TCHAR *tmpl, DLGPROC proc);
  _TCHAR *DoToken(_TCHAR *atarget, _TCHAR *fmt);
  _TCHAR *GetNextNum(_TCHAR *from, _TCHAR *atarget);
  void ArrangeName(_TCHAR *from, _TCHAR *to, AuthorOpt *f, _TCHAR *scanfstr);
  void ArrangeAuthors(_TCHAR *atarget, _TCHAR **author_list, int num_authors, AuthorOpt *f);
  void FormatAuthors(_TCHAR *atarget, AuthorOpt *f, _TCHAR *AorE);
  _TCHAR *ProcessAuthorFormat(LPTSTR from, AuthorOpt *f);
  void Init(void);
};

typedef TRef * LPRef;

extern _TCHAR *Special(_TCHAR *atarget, _TCHAR *p);

#define OTREF_H

#endif
