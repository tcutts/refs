/*********************************************************/
/**                                                     **/
/**      Medline.C - MedLine import filter              **/
/**                                                     **/
/**      This file is (C) Tim Cutts 1993,1996 and may   **/
/**      not be redistributed in its present form, but  **/
/**      may be used, modified, in other programs.      **/
/**                                                     **/
/*********************************************************/

#include <tchar.h>
#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <malloc.h>
#include <windowsx.h>

// Method of marking functions for export differs between
// Win16 and Win32
#ifdef WIN32
#define t_export _declspec(dllexport)
#define SSCANF _stscanf
#else
#include "../../../src/sscanf/wsscanf.h"
#define t_export CALLBACK _export
#define SSCANF wsscanf
#endif

#include "../../inc/imptfr.h"
#include "../../rimpexp/rimpexp.h"

#define CODE(x, y) \
  case x:          \
    p = &Tmp.y;    \
    break
#define RESET_SPLITS \
  v = 0;             \
  j[0] = d[0] = junk[0] = a[0] = p[0] = e[0] = pub[0] = n[0] = _T('\0');
#define SPLITFIELD(a, A)                     \
  if ((a[0] != _T('\0')) && (Tmp.A == NULL)) \
    Tmp.A = _tcsdup(a);
#define NUMFIELD(n, N)      \
  if (n && (Tmp.N == NULL)) \
  {                         \
    _itot(n, junk, 10);     \
    Tmp.N = _tcsdup(junk);  \
  }

long BufSz;
LPTSTR tstr1;
LPTSTR tstr2;
LPTSTR *p;
static TImportRef Tmp;
int EoF, Opt;
HINSTANCE hInst;

LPTSTR FirstNonWhite(LPTSTR Ap)
{
  LPTSTR Bp;
  for (Bp = Ap; _tcschr(_T("\r\n\t: -"), Bp[0]); Bp++)
  {
  }
  return Bp;
}

void AddStuff(LPTSTR Work, LPTSTR Src, LPTSTR *Dest, int Indent)
{
  if (*Dest)
  {
    lstrcpy(Work, *Dest);
    free(*Dest);
    if ((p == &Tmp.Authors) ||
        (p == &Tmp.Keywords) ||
        ((p == &Tmp.Text) && (Indent == -1)))
      lstrcat(Work, _T("\r\n"));
    else
      lstrcat(Work, _T("\x01"));
  }
  else
    Work[0] = _T('\0');
  lstrcat(Work, FirstNonWhite(&Src[(Indent == -1) ? 0 : Indent]));
  if (Indent == -1)
    lstrcat(Work, _T("\r\n"));
  *Dest = _tcsdup(Work);
}

void SplitSource(void)
{
  char j[200], junk[400], a[200], p[20], n[20], e[100], pub[200], d[20];
  int v, f;

  // We want to split the source into Journal, Year, Vol, No, Pages, OtherStuff, Junk if possible
  // In descending order of preference, the SO formats we are looking for are probed with sscanf.
  // For some, we will allow a poor match.  If none match the SO line, keep the whole thing, and MessageBox.

  // SO  - A Jou YYYY MMM;Vol(No):p-p
  // "%[^0-9]%d%[^;]; %d (%d) : %[0-9-]", Journal, Date, Junk, Vol, No, Pages

  // SO:    A Jou. YYYY MMM; Vol(No): p-p
  // This will also fit the above string

  RESET_SPLITS;

  f = SSCANF(Tmp.Journal, _T("%[^0-9]%[^;]; %d ( %[^)]) : %[0-9-]"), &j, &d, &v, &n, &p);
  if (f >= 5) // looks good!
    goto PutInRef;

  // In this case address contains ; characters.
  // "%[^.]. %d, No. %d, %[0-9] %[^;]; %[^\0]", Journal, Date, No, Pages, Junk, Address

  RESET_SPLITS;

  f = SSCANF(Tmp.Journal, _T("%[^.].%[0-9] , No. %[0-9-/], %[0-9] %[^;]; %[^\0]"), &j, &d, &n, &p, &junk, &a);
  if (f >= 4) // looks good!
    goto PutInRef;

  // "%[^.]. %d , %d : %d , %[0-9-]", Journal, Date, Vol, No, Pages
  // eg: SO: Environmental-Entomology. 1973, 2: 3, 401-407; 5 ref., 5 fig.

  RESET_SPLITS;

  f = SSCANF(Tmp.Journal, _T("%[^.]. %[0-9] , %d : %[0-9-/] , %[0-9-]"), &j, &d, &v, &n, &p);
  if (f == 5) // looks good!
    goto PutInRef;

  // "%[^.]. %d , %d , %[0-9-]", Journal, Date, Vol, Pages
  // eg: SO: Annales-du-Tabac,-2. 1986, 20, 93-104; 6 ref., 13 fig.

  RESET_SPLITS;

  f = SSCANF(Tmp.Journal, _T("%[^.]. %[0-9] , %d , %[0-9-]"), &j, &d, &v, &p);
  if (f == 4) // looks good!
    goto PutInRef;

  // "%[^.]. %d ; %d : %[0-9-]", Journal, Date, Vol, Pages
  // eg: SO: Agents-Actions-Suppl. 1995; 46: 77-84

  RESET_SPLITS;

  f = SSCANF(Tmp.Journal, _T("%[^.]. %[0-9] ; %d : %[0-9-]"), &j, &d, &v, &p);
  if (f == 4) // looks good!
    goto PutInRef;

  // SO: J-Clin-Psychiatry. 1996; 57 Suppl 6: 28-32
  // "%[^.]. %d ; %d %[^:]: %[0-9-]"

  RESET_SPLITS;

  f = SSCANF(Tmp.Journal, _T("%[^.]. %[0-9] ; %d %[^:]: %[0-9-]"), &j, &d, &v, &n, &p);
  if (f == 5)
    goto PutInRef;

  // Do a search for Editor before applying this one.
  // "%[^:]: %[^0-9]%d, %[0-9-];%[^;]; %[^.]", Editor, Journal, Date, Pages, Address, Publisher
  // eg: SO: Rodriguez, J. G. (Editor): Recent advances in acarology. Volume I. 1979, 213-220; 10 ref. New York, USA; Academic Press.

  if (_tcsstr(Tmp.Journal, _T("(Editor)")))
  {

    RESET_SPLITS;

    f = SSCANF(Tmp.Journal, _T("%[^:]: %[^0-9]%[0-9], %[0-9-];%[^;]; %[^.]"), &e, &j, &d, &p, &a, &pub);
    if (f >= 5) // looks good!
      goto InBook;
  }

  // Address has commas
  // "%[^.]. %[^,], %d, %[^.]. %[^,], %[0-9-];%[^.].", Journal, Junk, Year, Address, Junk, Pages, Junk

  RESET_SPLITS;

  f = SSCANF(Tmp.Journal, _T("%[^.]. %[^,], %[0-9], %[^.]. %[^,], %[0-9-];%[^.]."), &j, &junk, &d, &a, &junk, &p, &junk);
  if (f >= 5) // looks good!
    goto PutInRef;

  // "%d , %[^0-9-]%[0-9-] ; %[^;]; [^\0]", Year, Junk, Pages, City, Publisher
  // eg: SO: 1986, 96 pp.; 23 ref. Harare, Zimbabwe; Crop Science Department, University of Zimbabwe.

  RESET_SPLITS;

  f = SSCANF(Tmp.Journal, _T(" %[0-9] ,%[^0-9]%[0-9-] pp. ; %[^;]; [^\0]"), &d, &junk, &p, &a, &pub);
  if (f >= 3) // looks good!
    goto InBook;

  // "%d , %[^0-9]%[0-9-] pp. [^\0]", Year, Junk, Pages, City
  //     SO: 1985, 228pp.; many ref., Thesis, University of Southampton, UK. Southampton, UK.

  RESET_SPLITS;

  f = SSCANF(Tmp.Journal, _T(" %[0-9] , %[^0-9]%[0-9-] pp. [^\0]"), &d, &junk, &p, &a);
  if (f >= 2) // looks good!
    goto InBook;

  // If we're still here we have not managed to split the SO line, so keep it as is for the user to deal with.
  return;

InBook:
  if (Tmp.Title)
    lstrcpy(j, Tmp.Title);

  Tmp.RefType = 1;

PutInRef:
  // We have successfully split the SO field.  Now to put everything in Tmp.

  free(Tmp.Journal);
  Tmp.Journal = NULL;

  SPLITFIELD(j, Journal);
  SPLITFIELD(e, Editor);
  SPLITFIELD(p, Pages);
  SPLITFIELD(a, City);
  SPLITFIELD(pub, Publisher);
  SPLITFIELD(n, VolNo);
  SPLITFIELD(d, Date);
  NUMFIELD(v, Vol);
}

void RemoveHyphens(char **Field, BOOL IsNames)
{
  // Removes hyphens from fields, inserting a comma if these are names
  char *p, *q;

  if (*Field == NULL)
    return;

  p = *Field;
  q = tstr1;

  do
  {
    if (*p != _T('-'))
      *q = *p;
    else
    {
      if (IsNames)
      {
        *q = _T(',');
        q++;
      }
      *q = _T(' ');
    }
    p++;
    q++;
  } while (p[0] != _T('\0'));

  *q = _T('\0');

  free(*Field);
  *Field = _tcsdup(tstr1);
}

#ifdef WIN32
TImportRef t_export *LoadRef(HWND AParent, LPMMIOINFO FS)
{
#else
TImportRef FAR *PASCAL _export LoadRef(HWND AParent, LPMMIOINFO FS, LPTSTR INIPath)
{
#endif
  LPTSTR p2;
  int Code, Indent;

  Tmp.Result = 0;
  Tmp.RefType = 0;

  p = &Tmp.Authors;

  if (Opt == -1)
    Opt = GetConfigInt(_T("MedLine"), _T("Opt"), 7);

  do
  {
    if (*p)
      free(*p);
    *p = NULL;
    p++;
  } while (p <= &Tmp.SortStr);

  p = NULL;

  do
  {
    ReadLine(FS, tstr1, &EoF);
  } while ((!EoF) &&
           ((tstr1[0] == _T('\0')) ||
            (tstr1[0] == _T('0')) ||
            (_ttol(tstr1) != 0) ||
            (_tcsstr(tstr1, _T("-------"))) ||
            (_tcsstr(tstr1, _T("MEDLINE")))));

  if (EoF)
  {
    Tmp.Result = 2;
    return &Tmp;
  }

  while ((!EoF) &&
         (tstr1[0] != _T('\0')) &&
         (SSCANF(tstr1, _T("%[-]\0"), tstr2) != 1))
  {

#ifdef _UNICODE
#error Broken!
#endif
    Code = ((unsigned int)tstr1[0] << 8) + (unsigned int)tstr1[1];

    Indent = 2; // Most fields have a 2 character tag.

    switch (Code)
    {
    case 0x2020:
      break; // This is a continuation of the last field encountered.

      // The following tags have no equivalent.  Put them in abstract
      // with their tags still intact

    case 0x544F: // TO
    case 0x4F54: // OT
    case 0x2A4C: // *L
    case 0x4953: // IS
    case 0x4350: // CP
    case 0x5053: // PS
    case 0x434E: // CN
    case 0x524E: // RN
    case 0x414E: // AN
    case 0x5444: // UD
    case 0x5349: // SI
    case 0x5341: // SB
    {
      if ((Opt & 8) == 0)
      { // then we don't want unknown fields in the abstract
        p = NULL;
        break;
      }
    }
    case 0x4341: // CA These are citations.  Keep CAB: so these are demarcated.
    {
      Indent = -1; // Triggers addstuff to put in new lines.
      p = &Tmp.Text;
    }
    case 0x434D:             // CM
      CODE(0x4142, Text);    // AB
    case 0x494E:             // IN
      CODE(0x4144, City);    // AD
      CODE(0x4155, Authors); // AU
    case 0x4450:             // DP
    case 0x5059:             // PY
    {
      p = &Tmp.Date;
      break;
    }
    case 0x4D49: // MI
    case 0x4D4A: // MJ
    case 0x4D45:
      Indent = 4; // ME
    case 0x4445:  // DE
    case 0x4554:  // ET
    case 0x4C53:  // LS
    case 0x4C41:  // LA
    case 0x5354:  // ST
    case 0x4D48:  // MH
    case 0x4E4D:  // NM
    case 0x5447:  // TG
    case 0x4753:  // GS
    case 0x5054:  // PT
    {
      p = &Tmp.Keywords;
      break;
    }
      CODE(0x5047, Pages);   // PG
    case 0x5441:             // TA
      CODE(0x534F, Journal); // SO
      CODE(0x5449, Title);   // TI
      CODE(0x5649, Vol);     // VI

    default:
      Indent = 0;
    }

    if (p)
      AddStuff(tstr2, tstr1, p, Indent);

    ReadLine(FS, tstr1, &EoF);
  }

  if (EoF)
    Tmp.Result = 1;

  // Strip all #1's inserted before
  for (p = &Tmp.Authors; p < &Tmp.SortStr; p++)
  {

    p2 = *p;

    while (p2)
    {

      p2 = _tcschr(p2, _T('\x01'));

      if (p2)
        p2[0] = _T(' ');
    }
  }

  p2 = Tmp.Authors;

  while (p2)
  {
    p2 = _tcsstr(p2, _T("; "));
    if (p2)
    {
      p2[0] = _T('\r');
      p2[1] = _T('\n');
    }
  }

  // Split keywords up if necessary
  p2 = Tmp.Keywords;
  while (p2)
  {
    p2 = _tcsstr(p2, _T("; "));
    if (p2)
    {
      p2[0] = _T('\r');
      p2[1] = _T('\n');
    }
  }

  // Do optional stuff

  if ((Opt & 1) && Tmp.Journal)
    SplitSource();

  if (Opt & 2)
  {
    RemoveHyphens(&Tmp.Authors, TRUE);
    RemoveHyphens(&Tmp.Keywords, FALSE);
    RemoveHyphens(&Tmp.Journal, FALSE);
  }

  if (Opt & 4)
  {

    lstrcpy(tstr1, _T("unread"));

    if (Tmp.Keywords)
    {
      lstrcat(tstr1, _T("\r\n"));
      lstrcat(tstr1, Tmp.Keywords);
      free(Tmp.Keywords);
    }

    Tmp.Keywords = _tcsdup(tstr1);
  }

  // remove everything from the final . in the journal
  for (
      p2 = &Tmp.Journal[lstrlen(Tmp.Journal) - 1];
      (p2 != Tmp.Journal) && (_tcschr("\t .", p2[0]) != NULL);
      p2--)
    ;

  if (p2 != Tmp.Journal)
    p2[0] = _T('\0');

  return &Tmp;
}

LPTSTR t_export WhoAmI(void)
{
  return _T("MedLine format");
}

LPTSTR t_export GetSpecs(void)
{
  return _T("MedLine text file (*.med, *.mdl)\0*.MED;*.MDL\0All files (*.*)\0*.*\0\0");
}

BOOL Opt_OnInitDialog(HWND dlg, HWND hwndFocus, LPARAM lParam)
{
  int N;

  N = GetConfigInt(_T("MedLine"), _T("Opt"), 1);
  CheckDlgButton(dlg, 103, N & 1);
  CheckDlgButton(dlg, 104, (N & 2) >> 1);
  CheckDlgButton(dlg, 105, (N & 4) >> 2);
  CheckDlgButton(dlg, 106, (N & 8) >> 3);
  return TRUE;
}

void Opt_OnCommand(HWND Dialog, int id, HWND hwndCtl, UINT codeNotify)
{
  switch (id)
  {
  case IDOK:
    EndDialog(Dialog,
              IsDlgButtonChecked(Dialog, 103) +
                  (IsDlgButtonChecked(Dialog, 104) << 1) +
                  (IsDlgButtonChecked(Dialog, 105) << 2) +
                  (IsDlgButtonChecked(Dialog, 106) << 3));
    break;
  case IDCANCEL:
    EndDialog(Dialog, -1);
    break;
  }
}

BOOL CALLBACK OptProc(HWND Dlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  switch (Msg)
  {
    HANDLE_MSG(Dlg, WM_INITDIALOG, Opt_OnInitDialog);
    HANDLE_MSG(Dlg, WM_COMMAND, Opt_OnCommand);
  }
  return FALSE;
}

#ifdef WIN32
void t_export Opts(HWND AParent)
{
#else
void t_export Opts(HWND AParent, LPTSTR APath)
{
#endif

  Opt = DialogBox(hInst, _T("OPTS"), AParent, OptProc);
  if (Opt != -1)
    SetConfigInt(_T("MedLine"), _T("Opt"), Opt);
}

#ifdef WIN32

BOOL WINAPI DllMain(

    HINSTANCE hinstDLL, // handle of DLL module
    DWORD fdwReason,    // reason for calling function
    LPVOID lpvReserved  // reserved
)
{

  switch (fdwReason)
  {
  case DLL_PROCESS_ATTACH:
  {
    BufSz = GetBufSz();
    tstr1 = (char *)malloc(BufSz);
    tstr2 = (char *)malloc(BufSz);
    hInst = hinstDLL;
    Opt = -1;
    return ((tstr1 && tstr2) ? TRUE : FALSE);
  }
  case DLL_PROCESS_DETACH:
  {
    free(tstr1);
    free(tstr2);
    break;
  }
  }
  return TRUE;
}

#else
int t_export WEP(int nParameter)
{
  free(tstr1);
  free(tstr2);
  return 1;
}

int t_export LibMain(HINSTANCE hInstance, WORD wDataSeg, WORD cbHeapSize, LPSTR lpCmdLine)
{

  hInst = hInstance;
  BufSz = GetBufSz();
  if (BufSz)
  {
    tstr1 = (char *)malloc(BufSz);
    tstr2 = (char *)malloc(BufSz);
    hInst = hInstance;
    Opt = -1;
    if (tstr1 && tstr2)
      return 1;
    else
      return 0;
  }
  else
    return 0;
}
#endif
