#include "inc/globals.h"
#include "inc/refpaint.h"
#include "rimpexp/rimpexp.h"
#include "inc/editdlg.h"
#include "inc/authdlg.h"

// Special interprets any _TCHARacter following a backslash
LPTSTR Special(LPTSTR atarget, LPTSTR Ptr)
{

  _TCHAR t[2];

  Ptr++;
  switch (*Ptr)
  {
  case _T('n'):
    lstrcat(atarget, _T("\r\n"));
    break;
  case _T('t'):
    lstrcat(atarget, _T("\t"));
    break;
  default:
  {
    *t = *Ptr;
    t[1] = _T('\0');
    lstrcat(atarget, t);
  }
  }
  return (Ptr);
}

// Formats a reference according to the current format string
int TRef::FormatRef(LPTSTR ATarget)
{
  LPTSTR Ptr;
  _TCHAR t[2];
  int n;

#ifdef WIN32
  _try
  {
#endif

    Ptr = FmtString;
    ATarget[0] = _T('\0');
    while (Ptr && (*Ptr != _T('\0')))
    {
      while ((*Ptr != _T('<')) && (*Ptr != _T('\0')))
      {
        if (*Ptr == _T('\\'))
          Ptr = Special(ATarget, Ptr);
        else
        {
          t[1] = _T('\0');
          t[0] = Ptr[0];
          lstrcat(ATarget, t);
        }
        Ptr++;
      }

      if (*Ptr != _T('\0'))
        Ptr = DoToken(ATarget, Ptr + 1);

      if (Ptr && (*Ptr != _T('\0')))
        Ptr++;
    }

    n = lstrlen(ATarget);

    // Uncomment the following if you want to enforce blank
    // lines between references.
    /*
      if (n>0){
        lstrcat(ATarget, _T("\r\n\r\n"));
        n+=4;
      }
    */

    return n;

#ifdef WIN32
  }

  _except(GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
  {

    // Damn fool user can't write bloody format scripts

    MessageBox(0, _T("Internal error:  Either your format string is incorrect\nor there is a bug in Refs.\n\nCheck your < and > _TCHARacters are balanced"), FmtName, MB_OK | MB_ICONSTOP);
    ATarget[0] = _T('\0');
    return 0;
  }

#endif
}

_TCHAR *GetStringSlash(_TCHAR *from, _TCHAR *to)
{
  _TCHAR *p, t[2];

  p = from + 1;
  to[0] = t[1] = _T('\0');

  while ((*p != _T('\0')) && (*p != _T('/')))
  {
    if (*p == _T('\\'))
      p = Special(to, p);
    else
    {
      t[0] = p[0];
      lstrcat(to, t);
    }
    p++;
  }
  if (*p == _T('\0'))
    return NULL;
  else
    return (p);
}

LPTSTR TRef::ProcessAuthorFormat(LPTSTR from, AuthorOpt *f)
{

  _TCHAR *p;

  // Establish defaults
  f->bInitialsFirst = FALSE;
  f->bAndBeforeLast = TRUE;
  f->bWantEtAl = TRUE;
  f->bWantInitials = TRUE;
  f->bAllCaps = FALSE;
  lstrcpy(f->lpszNameSep, _T(", "));
  lstrcpy(f->lpszInitNameSep, _T(", "));
  lstrcpy(f->lpszAnd, _T(" and "));
  lstrcpy(f->lpszEtAl, _T(" et al"));
  f->iNumAuthors = 1;

  p = from;

  // Get broad type
  switch (*p)
  {
  case _T('1'):
    f->iNumAuthors = 1;
    p++;
    break;
  case _T('2'):
    f->iNumAuthors = 2;
    p++;
    break;
  case _T('3'):
    f->iNumAuthors = 3;
    p++;
    break;
  default:
    return p;
  }

  // Get options
  while (p)
  {
    switch (*p)
    {
    case _T('\0'):
      return NULL;
    case _T('i'):
      f->bInitialsFirst = TRUE;
      break;
    case _T('a'):
      f->bAndBeforeLast = FALSE;
      break;
    case _T('e'):
      f->bWantEtAl = FALSE;
      break;
    case _T('s'):
      f->bWantInitials = FALSE;
      break;
    case _T('n'):
      f->iNumAuthors |= 4;
      break;
    case _T('c'):
      f->bAllCaps = TRUE;
      break;
    case _T('A'):
      p = GetStringSlash(p, f->lpszAnd);
      break;
    case _T('E'):
      p = GetStringSlash(p, f->lpszEtAl);
      break;
    case _T('N'):
      p = GetStringSlash(p, f->lpszNameSep);
      break;
    case _T('S'):
      p = GetStringSlash(p, f->lpszInitNameSep);
      break;
    default:
      return p;
    }
    ++p;
  }
  return NULL;
}

void TRef::ArrangeName(_TCHAR *from, _TCHAR *to, AuthorOpt *f, _TCHAR *scanfstr)
// This rearranges a name in accordance with the instructions in AuthorOpt
// and the separator used in the sorting of names.
{
  _TCHAR t[64], t1[64], j[64], *p;
  int n;

  // Try to split the name
  n = _stscanf(from, scanfstr, t, j, t1);

  if (n != 3)
  {
    // We need to pick out the surname and initials by hand.
    if (MSortName.surname_last)
    {
      for (p = strend(from) - 1;
           (p != from) && (_tcschr(_T(" \t,;._:-/"), *p) == NULL);
           p--)
        ;

      if (p != from)
      {
        p[0] = _T('\0');
        lstrcpy(t, &p[1]);
        lstrcpy(t1, from);
      }
      else
      {
        // No initials
        lstrcpy(t, from);
        t1[0] = _T('\0');
      }
    }
    else
    {
      // Surname first
      n = _stscanf(from, _T("%s %[^\r]"), t, t1);

      if (n == 1)
        t1[0] = _T('\0');
    }
  }

  if (!f->bWantInitials)
  {
    n = lstrlen(t) - 1;
    if (t[n] == _T('\r'))
      t[n] = _T('\0');
    lstrcpy(to, t);
    return;
  }

  // t now contains the surname, and t1 contains the initials.
  if (t1[0] == _T('\0'))
    _stscanf(from, _T("%[^\r]"), to);
  else
  {
    n = lstrlen(t) - 1;
    if (t[n] == _T('\r'))
      t[n] = _T('\0');
    if (f->bInitialsFirst)
      wsprintf(to, _T("%s %s"), t1, t);
    else
      wsprintf(to, _T("%s%s%s"), t, f->lpszInitNameSep, t1);
  }
}

void TRef::ArrangeAuthors(_TCHAR *atarget, _TCHAR **author_list, int num_authors, AuthorOpt *f)
// This arranges the authors in author_list appropriately according to AuthorOpt
{
  int n;

  switch (f->iNumAuthors & 3)
  {
  case 1:
  { // all authors/editors
    atarget[0] = _T('\0');
    for (n = 0; n < num_authors; n++)
    {
      lstrcat(atarget, author_list[n]);
      if (f->bAndBeforeLast && (n == (num_authors - 2)))
        lstrcat(atarget, f->lpszAnd);
      else
      {
        if (n != (num_authors - 1))
          lstrcat(atarget, f->lpszNameSep);
      }
    }
    break;
  }

  case 2:
  { // first only
    lstrcpy(atarget, author_list[0]);
    break;
  }

  case 3:
  { // 2/(1 et al)
    switch (num_authors)
    {
    case 1:
      lstrcpy(atarget, author_list[0]);
      break;
    case 2:
      wsprintf(atarget, _T("%s%s%s"), author_list[0],
               f->bAndBeforeLast ? f->lpszAnd : f->lpszNameSep,
               author_list[1]);
      break;
    default:
    {
      lstrcpy(atarget, author_list[0]);
      if (f->bWantEtAl)
        lstrcat(atarget, f->lpszEtAl);
    }
    }
    break;
  }
  }
}

void TRef::FormatAuthors(_TCHAR *atarget, AuthorOpt *f, _TCHAR *AorE)
{
#ifdef MAX_NAMELENGTH
#error Whoops!  MAX_NAMELENGTH already defined!
#endif
#define MAX_NAMELENGTH 128
  int n, num_authors, m;
  _TCHAR **author_list;
  _TCHAR t[MAX_NAMELENGTH], t1[MAX_NAMELENGTH], s[40];

  _TCHAR *p, *q;

  // Build a scanf string with the separators being used
  wsprintf(s, _T("%%[^%s]%%[%s] %%[^\r]\r"), MSortName.separator, MSortName.separator);

  // How many authors do we have?
  for (num_authors = 1, p = _tcschr(AorE, _T('\n'));
       (p != NULL) && (p[1] != _T('\0'));
       num_authors++, p = _tcschr(++p, _T('\n')))
    ;

  // Allocate the array of pointers appropriately
  author_list = (_TCHAR **)malloc(num_authors * sizeof(_TCHAR *));

  // For each author, copy him to the t buffer, rearrange him,
  // and then _tcsdup him into the author_list array.
  for (n = 0, p = AorE;
       n < num_authors;
       n++)
  {
    for (q = t, m = 0;
         (++m < MAX_NAMELENGTH) && (p[0] != _T('\n')) && (p[0] != _T('\0'));
         p++, q++)
    {
      q[0] = p[0];
    }

    if (m == MAX_NAMELENGTH)
      MessageBox(
          0,
          _T("Author name truncated at 127 characters.\nCheck the file does not have multiple authors on a single line."),
          NULL, MB_OK | MB_ICONSTOP);

    if (p[0] == _T('\0'))
    {
      q[0] = _T('\r');
      q++;
    }

    q[0] = _T('\0');

    if (f->iNumAuthors & 4) // Don't want the name rearranged
    {
      q--;
      q[0] = _T('\0');
      author_list[n] = _tcsdup(t);
    }
    else
    {
      ArrangeName(t, t1, f, s);

      author_list[n] = _tcsdup(t1);
    }

    if (f->bAllCaps)
#ifdef WIN32
      CharUpper(author_list[n]);
#else
      AnsiUpper(author_list[n]);
#endif

    p++;
  }

  // Now arrange the authors in the final target
  ArrangeAuthors(atarget, author_list, num_authors, f);

  // Free authors
  for (n = 0;
       n < num_authors;
       n++)

    free(author_list[n]);

  // Free list of pointers
  free(author_list);
}

// Formats an individual < > pair within the format string
LPTSTR TRef::DoToken(LPTSTR ATarget, LPTSTR Fmt)
{
  LPTSTR Ptr, Tmp, TheFld, s1;
  int Recurse, so;
  _TCHAR t[2];
  _TCHAR CurFld;
  AuthorOpt AFmt;

  Ptr = Fmt;
  CurFld = *Ptr;

  // is this a 'not' field?
  so = (CurFld != _T('!'));

  if (!so)
  {
    Ptr++;
    CurFld = *Ptr;
  }

  TheFld = NULL;

  switch (CurFld)
  {
  case _T('A'):
  case _T('E'):
  {

    // Process options if they are there
    Ptr = ProcessAuthorFormat(++Ptr, &AFmt);

    if (CurFld == _T('A'))
      TheFld = authors;
    else
      TheFld = editor;

    Ptr--;

    break;
  }

  case _T('B'):
  {
    if (reftype == 1)
      TheFld = journal;
    break;
  }

  case _T('C'):
    TheFld = city;
    break;
  case _T('D'):
    TheFld = date;
    break;

  case _T('I'):
    TheFld = publisher;
    break;

  case _T('J'):
  {
    if (reftype == 0)
      TheFld = journal;
    break;
  }

  case _T('K'):
    TheFld = keywords;
    break;
  case _T('N'):
    TheFld = volno;
    break;
  case _T('P'):
    TheFld = pages;
    break;
  case _T('R'):
  {
    if (reftype == 2)
      TheFld = journal;
    break;
  }

  case _T('T'):
    TheFld = title;
    break;
  case _T('V'):
    TheFld = vol;
    break;
  case _T('X'):
    TheFld = text;
    break;

  default:
    TheFld = NULL;
  }

  Ptr++;

  if ((so && TheFld) || ((!so) && (!TheFld)))
  {
    while ((Ptr[0] != _T('>')) && (Ptr[0] != _T('\0')))
    {
      switch (Ptr[0])
      {
      case _T('<'):
        Ptr = DoToken(ATarget, Ptr + 1);
        break;

      case _T('@'):
      {
        if (so)
        {
          s1 = (_TCHAR *)malloc(SCRATCH_SIZE);

          switch (CurFld)
          {
          case _T('A'):
          case _T('E'):
          {
            FormatAuthors(s1, &AFmt, TheFld);
            lstrcat(ATarget, s1);
            break;
          }

          case _T('K'):
          {
            lstrcpy(s1, TheFld);
            Tmp = s1;

            do
            {
              Tmp = _tcschr(Tmp, _T('\r'));

              if (Tmp)
              {
                Tmp[0] = _T(';');
                Tmp[1] = _T(' ');
              }

            } while (Tmp);

            lstrcat(ATarget, s1);
            break;
          }

          default:
            if (TheFld)
              lstrcat(ATarget, TheFld);
          }

          free(s1);
        }
        else
          lstrcat(ATarget, _T("\\@"));

        break;
      }

      case _T('\\'):
        Ptr = Special(ATarget, Ptr);
        break;

      default:
      {
        t[1] = _T('\0');
        t[0] = Ptr[0];
        lstrcat(ATarget, t);
      }
      }

      if (!Ptr)
        return NULL;

      Ptr++;
    }

    return (Ptr);
  }
  else
  {
    Recurse = 1;

    while ((Recurse > 0) && (Ptr[0] != _T('\0')))
    {
      switch (Ptr[0])
      {
      case _T('<'):
        Recurse++;
        break;
      case _T('>'):
        Recurse--;
        break;
      case _T('\\'):
        Ptr++;
      }

      if (Recurse > 0)
        Ptr++;
    }

    if (*Ptr == _T('\0'))
      return (NULL);
    else
      return (Ptr);
  }
}

// Duplicates a reference
TRef *TRef::Duplicate(void)
{

  LPRef Tmp;
  LPTSTR *s, *d;

  Tmp = new TRef;

  Tmp->reftype = reftype;
  Tmp->links = 0;

  for (s = &authors, d = &Tmp->authors; s <= &sortstr; s++, d++)
  {
    if (*s)
      *d = _tcsdup(*s);
  }

  return (Tmp);
}

_TCHAR *TRef::GetNextNum(_TCHAR *from, _TCHAR *atarget)
{
  int f = 0;
  int n = 0;
  _TCHAR *p, d[RES_STR];

#ifdef WIN32
  _try
  {
#endif

    // get beginning of a number
    f = _stscanf(from, _T("%[^0-9]%n"), &d, &n);

    p = (f == 1) ? &from[n] : from;

    // Now get the number itself
    f = _stscanf(p, _T("%[0-9]%n"), &d, &n);

    if (f == 1)
    {
      lstrcpy(atarget, d);
      return (&p[n]);
    }

#ifdef WIN32
  }

  _except(GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
  {

    atarget[0] = _T('\0');
    return NULL;
  }

#endif

  atarget[0] = _T('\0');

  return NULL;
}

int TRef::GetYear(_TCHAR *atarget)
{
  _TCHAR *p;
  int t;

  t = -1;

  if (date)

    for (p = GetNextNum(date, atarget);
         (p && ((t = _ttoi(atarget)) < 32));
         p = GetNextNum(p, atarget))
      ;

  return (t);
}

void TRef::GetSortStr(_TCHAR *ATarget, int Flags, _TCHAR *t)
{
  // t should point to a scratch buffer that GetSortStr can
  // safely use.
  AuthorOpt a;
  _TCHAR *NameFrom, Year[8];

  ATarget[0] = _T('\0');

  if ((Flags & FLG_EDITOR) || (authors == NULL))
    NameFrom = editor;
  else
    NameFrom = authors;

  if (NameFrom)
  {
    a.bInitialsFirst = FALSE;
    a.bAndBeforeLast = TRUE;
    a.bWantEtAl = TRUE;
    a.bWantInitials = TRUE;
    a.bAllCaps = FALSE;
    lstrcpy(a.lpszNameSep, _T(", "));
    lstrcpy(a.lpszInitNameSep, _T(", "));
    wsprintf(a.lpszAnd, _T(" %s "), AndWord);
    lstrcpy(a.lpszEtAl, _T(" et al"));
    a.iNumAuthors = (Flags & 3) + 4;

    FormatAuthors(ATarget, &a, NameFrom);
  }

  lstrcat(ATarget, _T("\t")); // Tab

  if (date)
  {
    lstrcat(ATarget, _T("("));

    if (
        (Flags & FLG_YEAR_ONLY) &&
        (_tcschr(date, _T(' ')) || _tcschr(date, _T('/'))))
      // There's a space in the date
      lstrcat(ATarget, (GetYear(Year) > 31) ? Year : date);
    else
      lstrcat(ATarget, date);

    lstrcat(ATarget, _T(")"));
  }

  if (Flags & FLG_SHOW_TITLE)
  {
    if (title)
    {
      lstrcat(ATarget, _T("  "));
      lstrcat(ATarget, title);
    }
    else
    {
      if (journal)
      {
        lstrcat(ATarget, _T("  "));
        lstrcat(ATarget, journal);
      }
    }
  }
}

TRef::TRef(void)
{
  Init();
}

void TRef::Init(void)
{
  reftype = DfltSrc;
  links = serial_no = 0;
  hwndEditor = NULL;
  authors = title = text = journal = NULL;
  date = _tcsdup(DfltYr);
  keywords = vol = volno = pages = publisher = city = editor = sortstr = NULL;
  OpenedFrom = NULL;
}

int inline TRef::DoDlg(_TCHAR *Dlg, DLGPROC Proc)
{
  return DialogBoxParam(ResInstance, Dlg, FrameWnd, Proc, (long)this);
}

void TRef::Edit(int AddFlags)
{

  HWND t;

  if (hwndEditor) // Already being edited... activate it.
    t = hwndEditor;
  else
  {

    Flags &= ~(RF_CanBrowse | RF_EditModal);
    Flags |= AddFlags;

    if (Flags & RF_EditModal)
      DoDlg(_T("EDITREF"), EditRef);
    else
      t = CreateDialogParam(ResInstance,
                            _T("EDITREF"),
                            0,
                            EditRef,
                            (LPARAM)this);
  }
}

int TRef::ETitle(void)
{
  return (DoDlg(_T("ETITLE"), EAuthors));
}

TRef::~TRef(void)
{
  LPTSTR *s;
  for (s = &authors; s <= &sortstr; s++)
    if (*s)
    {
      free(*s);
      *s = NULL;
    }
}
