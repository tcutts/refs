#include "inc/globals.h"

#ifdef REGEXP
#include "../src/re/regexp.h"
#endif

typedef struct {
  LPRef ref, against;
} TCR;

typedef TCR * LPTCR;

LPTCR DRef;

  /*PtrData gives offsets of various fields in a TRef object, relative to
   the authors field.  The fields given are:
   Authors, Date, Title, Journal, Text, Keywords

   This is required by the TRef::Compare method*/

const int ptrdata[] = {0, 1, 2, 3, 8, 9};

struct TName:TObject {
  LPTSTR surname;
  LPTSTR rest;
  LPTSTR fullname;
  int current, failed;
  LPTSName sortname;
  TName(LPTSTR src, LPTSName how);
  ~TName(void);
  void getnextname(void);
  int comparewith(TName *cmpto);
};

typedef TName * LPName;


TName::TName(LPTSTR src, LPTSName how) {
  surname = rest = NULL;
  current = 0;
  failed = FALSE;
  fullname = src;
  sortname = how;
}


TName::~TName(void) {

  if (surname)
    free(surname);

  if (rest)
    free(rest);
}


void TName::getnextname(void) {
  _TCHAR *p, *p2, *q, t2[RES_STR], *t1;
  int n;

  if (surname)
    free(surname);
    
  if (rest)
    free(rest);
    
  surname = rest = NULL;
  
  // OK, first get the beginning of the next name
  if ((n=lstrlen(fullname))>=RES_STR){
  
    t1 = (_TCHAR *)malloc(n+2);
    q = t1;
  
  } else {
  
    t1=NULL;
    q=t2;
  
  }
  
  p = fullname; n = 0;
  
  while ((!failed) && (n<current)) {
  
    n++;
    p = _tcschr(p, _T('\r'));
    failed = (p==NULL);
    if (!failed){
	  // We want p to point to after this
#ifdef HAVE_STRSPNP
	  p = _tcsspnp(p, _T("\n\r \t"));
#else
	  while ((*p != _T('\0')) && (_tcschr(_T("\n\r_\t"), *p)==NULL))
	  	p++;
#endif
      failed = ((!p) || (*p == _T('\0')));
    }
  }
  
  if (failed)
    return;
    
  current++;
  
  // Now, look for a surname separator
  // finish with p pointing to the surname, p2 to the rest

  // copy the name to t
  for (n=0; (p[n]!=_T('\r')) && (p[n]!=_T('\0')); n++)
    q[n]=p[n];
  
  q[n]=_T('\0');
  
  // point p2 to separator if it's there.
  p2 = _tcspbrk(q, sortname->separator);
  
  if (!p2) {
    // no separator, so check whether surname is usually last
    if (sortname->surname_last) {
      // if so, look backwards for the last space/tab
      for (p=strend(q)-1;
          p>=q && (_tcschr(_T(" \t"), *p)==NULL);
          p--);
      
      if (p<=q)
        p=NULL;
      
      if (p) {
        // found space/tab
        p[0]=_T('\0');
        p2=q;
      } else {
        p2=NULL;
        p=q;
      }
        
    } else {
      // surname is usually first
      for (p=q;
          *p!=_T('\0') && (_tcschr(_T(" \t"), *p)==NULL);
           p++);
      
      if (*p==_T('\0')) {
        // did not find space tab
        p2=NULL; p=q;
      
      } else {
        *p=_T('\0');
        p2=p+1;
        p=q;
      }      
    }
  } else {
    // Found separator, therefore surname is first.
    *p2 = _T('\0');
    while (_tcschr(sortname->separator, p2[0]))
     p2++;
    p = q;
  }
  
  while (p2 && (_tcschr(_T(" \t"), *p2)))
    p2++;
  
  while (p && (_tcschr(_T(" \t"), *p)))
    p++;
  
  surname = p ? _tcsdup(p) : NULL;
  
  rest = p2 ? _tcsdup(p2) : NULL;
  
  if (t1){
    free(t1);
    t1=NULL;
  }
}

int TName::comparewith(TName *cmpto) {
  int t;
  
  if (failed)
    return(cmpto->failed ? 0 : -1);
  
  else {
    if (cmpto->failed)
      return 1;
    
    else {
      
      t = lstrcmpi(surname, cmpto->surname);
      
      if (t==0){
        
        if (!rest)
          t=cmpto->rest ? -1 : 0;
        
        else
          t=cmpto->rest ? lstrcmpi(rest, cmpto->rest) : 1;
      }
      
      return t;
    }
  }
}
              

int cmpnames(LPTSName sortname, LPTSTR aptr, LPTSTR bptr) {
  int t;
  LPName a, b;

  t=-1;
  
  switch (sortname->sort_method) {

    case 1: return(lstrcmpi(aptr, bptr));

    case 0:{
      a = new TName(aptr, sortname);
      b = new TName(bptr, sortname);

      do {
        a->getnextname();
        b->getnextname();
        t = a->comparewith(b);
      } while (!(t || a->failed || b->failed));

      delete a;
      delete b;
    }
  }
  return t;
}


LPTSTR MyStrPos(LPTSTR Src, LPTSTR Srch, int flags) {

// Note that Srch is not lowered; that is done in RefSearch
// to improve speed.

  LPTSTR t, SPtr;

  if ((!Src) || (!Srch))
    return NULL;
    
  if (flags & SF_IGNORECASE) {
    SPtr = _tcsdup(Src);
#ifdef WIN32
    CharLower(SPtr);
#else
    AnsiLower(SPtr);
#endif
    t = _tcsstr(SPtr, Srch);
    free(SPtr);
    return(t);
  } else
    return(_tcsstr(Src, Srch));
}


#ifdef REGEXP
long RegCmp(LPTSTR Src, regexp *rp, int flags)
{

  LPTSTR SPtr;
  long n = 0;

  if (flags & SF_IGNORECASE) {
    SPtr = _tcsdup(Src);
#ifdef WIN32
    CharLower(SPtr);
#else
    AnsiLower(SPtr);
#endif
    n = regexec(rp, SPtr);
    free(SPtr);
    return (n);
  }

  return (regexec(rp, Src));

}

long LineRegCmp(LPTSTR Src, regexp *rp, int flags)
{
// With some fields, you do not want the regexp to match
// Over two lines, so we need to check each line individually

  _TCHAR c;
  LPTSTR p, q, s;
  int n;


  if (flags & SF_IGNORECASE)
  {
    s = _tcsdup(Src);
#ifdef WIN32
    CharLower(s);
#else
    AnsiLower(s);
#endif
  }
  else
    s = Src;

  p = s;
  for (q = _tcspbrk(p, _T("\r\n"));
  	   (p != NULL);
	   q = _tcspbrk(p, _T("\r\n")))
		
  {
    if (q)
    { 
      c = q[0];
	  q[0] = _T('\0');
    }

    n = regexec(rp, p);

    if (q)
      q[0] = c;
	else
	  break;
    
    if (n)
      break;

	p = _tcsspnp(q, _T("\r\n"));

  }

  if (flags & SF_IGNORECASE)
    free(s);

  return n;

}

#endif

TSrchColl::TSrchColl(long alimit, int allowdups, LPRefWndData aparent) :
  TSortedCollection(alimit, allowdups) {
  RefWnd = aparent;
  ProgressWnd = NULL;
#ifdef SERIALNO
  max_serial = 0;
#endif
  s1=(LPTSTR)malloc(SCRATCH_SIZE);
  s2=(LPTSTR)malloc(SCRATCH_SIZE);
  s3=(LPTSTR)malloc(SCRATCH_SIZE);
}


void TSrchColl::atremove(long index) {
  LPRef t;

  t = (LPRef)at(index);

  t->links--;
  
  TSortedCollection::atremove(index);
  
  if (t->links<=0)  // nobody loves me any more!
    delete t;
    
}


BOOL Dupl_OnInitDialog(HWND Dlg, HWND hwndFocus, LPARAM lParam){
  int IsTrue;

  DRef = (LPTCR)lParam;
  SetDlgItemText(Dlg, ide_Example, DRef->ref->sortstr);
  IsTrue = (DRef->ref != DRef->against);
  EnableWindow(GetDlgItem(Dlg, 101), IsTrue);
  EnableWindow(GetDlgItem(Dlg, 105), IsTrue);
  IsTrue = (DRef->ref->hwndEditor == NULL);
  EnableWindow(GetDlgItem(Dlg, id_DEdit), IsTrue);
  return TRUE;
}


void Dupl_OnCommand(HWND Dlg, int id, HWND hwndCtl, UINT codeNotify){
  switch (id) {
  
    case id_DEdit: {
      EnableWindow(Dlg, FALSE);
      DRef->ref->Edit(RF_EditModal);
      EnableWindow(Dlg, TRUE);
      EndDialog(Dlg, IDOK);
      break;
    }
 
    case IDCANCEL:
    case id_Ignore:
    case idb_Replace: EndDialog(Dlg, id); break;

    case cm_Help: WinHelp(FrameWnd, HelpName, HELP_CONTEXT, 6); break;      
    case id_DEditAuth: {
      DRef->ref->ETitle();
      EndDialog(Dlg, IDOK);
    }
  }
}


BOOL CALLBACK  DuplProc(HWND Dlg, UINT Msg, WPARAM wParam, LPARAM lParam){
  switch (Msg) {
    HANDLE_MSG(Dlg, WM_COMMAND, Dupl_OnCommand);
    HANDLE_MSG(Dlg, WM_INITDIALOG, Dupl_OnInitDialog);
  }
  return(FALSE);
}


int TSrchColl::forgetit(LPObject item, long anti) {
  TCR t;
  int n;

  t.ref = (LPRef)item;
  t.against = (LPRef)at(anti);

  if (t.ref->hwndEditor)
    EnableWindow(t.ref->hwndEditor, FALSE);

  n = DialogBoxParam(ResInstance, _T("DUPLICATE"), FrameWnd, DuplProc, (LPARAM)(&t));

  if (t.ref->hwndEditor)
    EnableWindow(t.ref->hwndEditor, TRUE);
  return n;
}


long TSrchColl::insert(LPObject item) {
  long t,r;

  do {
    t = TSortedCollection::insert(item);
    
    if (t<0) 
      r = forgetit(item, (t+1)*-1);
  
  } while ((t<0) && (r==IDOK));
  
  if (t<0) {

    switch (r) {

      case id_Ignore: return(-1);

      case IDCANCEL: return(-2);

      case idb_Replace: {
        atremove((t+1)*-1);
        return(atinsert((t+1)*-1, item));
      }

    }
  }
  
  return t;
}


long TSrchColl::atinsert(long index, LPObject item){
  long t;

   t = TSortedCollection::atinsert(index, item);
  
  if (t!=-1)
    ((LPRef)item)->links++;
    
  return t;
}


void TSrchColl::removeall(void){

  if (RefWnd){
    ListBox_ResetContent(RefWnd->ListWnd);
    ListBox_SetHorizontalExtent(RefWnd->ListWnd, 0);
  }

  long n;
  LPRef a;

  if (count)
    for (n = (count-1) ; n>=0 ; n-- )
	{
	  a = (LPRef)at(n);

	  if ((a->hwndEditor) && (a->OpenedFrom == RefWnd))
	    SendMessage(a->hwndEditor, WM_STOPBROWSING, 0, 0);

      atremove(n);
	}

}


void TSrchColl::redisplay(void) {
  long n;
  LPRef a;
  
  SetWindowRedraw(RefWnd->ListWnd, FALSE);
  ListBox_ResetContent(RefWnd->ListWnd);
  
  for (n = 0; n<count ; n++) {
    a = (LPRef)at(n);
    a->GetSortStr(s1, RefWnd->ListFlags | FLG_YEAR_ONLY, s2);
    ListBox_AddString(RefWnd->ListWnd, s1);
  }
  
  SetWindowRedraw(RefWnd->ListWnd, TRUE);
  RedrawWindow(RefWnd->Window, NULL, NULL,
               RDW_FRAME | RDW_INVALIDATE | RDW_ALLCHILDREN);
               
}


void TSrchColl::display(long Index){
  
  ((LPRef)at(Index))->GetSortStr(s1, RefWnd->ListFlags, s2);
  ListBox_InsertString(RefWnd->ListWnd, Index, s1);
  
}

int TSrchColl::compare(void *key1, void *key2) {
  int n, t, s, order;
  _TCHAR **A, **B, ay[8], by[8];
  LPTSName SortName;

  if (key1==key2)
    return(0);
  else {
    n = 0;
    do {
      A = &(((LPRef)key1)->authors);
      B = &(((LPRef)key2)->authors);
      if (RefWnd)
        s = RefWnd->SortFlags[n] & 7;
      else
        s = MSortFlags[n] & 7;
      if (s!=6) {
        A+=ptrdata[s];
        B+=ptrdata[s];
        /*Time to do some fall-backs, if one or other is null
        and we're looking at Titles,  look at Journal*/
        if ((s==2) && (((long)*A & (long)*B)==0)) {
          if (*A==NULL)
            A++;
          if (*B==NULL)
            B++;
        }
        if (RefWnd)
          order = (RefWnd->SortFlags[n] & FLG_SORT_ORDER);
        else
          order = (MSortFlags[n] & FLG_SORT_ORDER);
        if (*A==NULL) {
          if (*B==NULL)
            t = 0;
          else
            t = 1;
        } else {
          if (*B==NULL)
            t = -1;
          else {
            switch (s){
              case 0: { //authors
                t=lstrcmpi(*A, *B);
                if (t){
                  if (!RefWnd)
                    SortName = &MSortName;
                  else
                    SortName = &RefWnd->NameSort;
                  t = cmpnames(SortName, *A, *B);
                }
                break;
              }
              case 1: { // date
                t=((LPRef)key1)->GetYear(ay)-((LPRef)key2)->GetYear(by);
                if (!t)
                  t=lstrcmpi(*A, *B);
                break;
              }
              case 2: { // journal
                t = lstrcmpi(*A, *B);
                if ((t==0) && (s==2))
                  t = ((LPRef)key1)->reftype-((LPRef)key2)->reftype;
                break;
              }
              default: t=lstrcmpi(*A, *B);
            }
          }
        }
        if (order)
          t = 0-t;
        n++;
      } else
        n = 3;
    } while ((n!=3) && (t==0));
    if (t<0)
      t=-1;
    if (t>0)
      t=1;
    return(t);
  }
}

int RefSearch(LPSrchColl AColl, int By, LPTSTR Txt, LPSrchColl AddTo,  int flags) {
  LPRef P;
  long TRes, n;
  long Found;
#ifdef REGEXP
  regexp *rp;
#endif

  TRes = n = 0;

// If not case sensitive, lower case the search term now, so
// that it doesn't have to be done every time.  Should be much
// faster than before!

  if (flags & SF_IGNORECASE)
#ifdef WIN32
    CharLower(Txt);
#else
    AnsiLower(Txt);
#endif    



#ifdef REGEXP
  // Compile a regular expression from Txt
  if (flags & SF_REGEXP)
    rp = regcomp(Txt);
#endif

  while (n < AColl->count) {
    if ((n & 15) == 0)
      Pause(AddTo->ProgressWnd, FALSE);
    Found = FALSE;
    P=(LPRef)AColl->at(n);
#ifdef REGEXP
    if (flags & SF_REGEXP)
	{
    switch (By) {
      case 1: Found = RegCmp(P->title, rp, flags); break;
      case 2: Found = LineRegCmp(P->keywords, rp, flags); break;
      case 3: Found = LineRegCmp(P->keywords, rp, flags) || RegCmp(P->title, rp, flags) || RegCmp(P->text, rp, flags);break;
      case 4: Found = LineRegCmp(P->authors, rp, flags);break;
      case 5: Found = RegCmp(P->journal, rp, flags);break;
      case 6: Found = RegCmp(P->date, rp, flags);break;
      case SHOW_ALL: Found = TRUE; break;
      default: Found = FALSE;
    }
	}
	else
	{
#endif
    switch (By) {
      case 1: Found = (long)MyStrPos(P->title, Txt, flags); break;
      case 2: Found = (long)MyStrPos(P->keywords, Txt, flags); break;
      case 3: Found = (long)MyStrPos(P->keywords, Txt, flags) || MyStrPos(P->title, Txt, flags) || MyStrPos(P->text, Txt, flags);break;
      case 4: Found = (long)MyStrPos(P->authors, Txt, flags);break;
      case 5: Found = (long)MyStrPos(P->journal, Txt, flags);break;
      case 6: Found = (long)MyStrPos(P->date, Txt, flags);break;
      case SHOW_ALL: Found = TRUE; break;
      default: Found = FALSE;
    }
#ifdef REGEXP
    }
#endif
    if (flags & SF_NOT)
      Found = !Found;
    if (Found) {
      if (AddTo->indexof(P)==-1){  // duplicate entries are pointless
        AddTo->insert(P);
        TRes++;
      }
    }
    n++;
  }

#ifdef REGEXP
  if (flags & SF_REGEXP)
    regfree(rp);
#endif

  return(TRes);
}


int TSrchColl::refsrch(int By, LPTSTR Txt, LPSrchColl AddTo, int sflags){
  return(RefSearch(this, By, Txt, AddTo, sflags));
}

void TSrchColl::remove(LPObject item){
  
  TSortedCollection::remove(item);
  
  if (((LPRef)item)->links <= 0)
    freeitem(item);
}

TSrchColl::~TSrchColl() {

  removeall(); // This will destroy only those with links==1

  free(s3);
  free(s2);
  free(s1);
}


#ifdef SERIALNO
long inline TSrchColl::assign_serial(LPRef Item)
{
	return (Item->serial_no = ++max_serial);
}

void TSrchColl::assign_serials(void)
{
  LPRef p;
  
	for (int n = 0; n<count ;n++)
	{
		p = (LPRef) at(n);
		
		if (p->serial_no == 0)
			assign_serial(p);
	}	
}
#endif



int TSrchColl::FillBibWnd(long startfrom, LPTSTR BibTeX) {
  long n, l, m;

  BibTeX[0] = _T('\0');

  // Prefix first
#ifdef USE_RTF

  LPTSTR p;
  int q, r;
  
  p = _tcsstr(FmtPrefix, _T("\\rtf"));

  if (!p)
    lstrcpy(BibTeX, _T("{\\rtf1\\ansi "));
#endif

  // If we're not starting from 0 we don't want the prefix
  if (!startfrom)
    lstrcat(BibTeX, FmtPrefix);
  
  for (n = startfrom, l = 0; n<count; n++) {
  
    // format the reference to temporary buffer
    ((LPRef)at(n))->FormatRef(s1);
#ifdef USE_RTF
    // If this is not an RTF format, we need to insert some RTF \par's for \n's
    if (!p)
	{
    for ( q = 0, r = 0;
	      s1[q]!=_T('\0');
		  q++, r++)
	  {
		s2[r] = s1[q];
	    if (s1[q]==_T('\n'))
		{
		  lstrcpy(&s2[++r], _T("\\par "));
		  r+=4;
		}
	  }
	lstrcpy(s1, s2);
	}
#endif
    
    // how long is the bibliography so far?
    m=lstrlen(s1);
    l+=m;
    
    // if this one will fit, add it
    if ((l+100)<MAX_EDIT_CONTENTS)
      lstrcat(BibTeX, s1);
      
    else {
      // ErrorBox(Window, err_BibTooBig);
      return(n);
    }
  }
  
  // Append the suffix
  lstrcat(BibTeX, FmtSuffix);
#ifdef USE_RTF
  if (!p)
    lstrcat(BibTeX, _T("}"));
#endif
  return(n);
}

