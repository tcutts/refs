/*********************************************************/
/**                                                     **/
/**      Procite.C - Procite import filter              **/
/**                                                     **/
/**      This file is (C) Tim Cutts 1996 and may        **/
/**      not be redistributed in its present form, but  **/
/**      may be used, modified, in other programs.      **/
/**                                                     **/
/*********************************************************/

#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <malloc.h>
#include <ver.h>
#include <windowsx.h>

#include "procite.h"
#include "../../inc/imptfr.h"
#include "../../rimpexp/rimpexp.h"

/*
A2.	Abbott, D. H.////McNeilly, A. S.//Lunn, S. T.//Mulme, M. J.//Burden, F. J.
A5.	Adaptive value of spacing behaviour in population cycles of red grouse and other animals
A8.	Cohen, M. N.////Malpass, R. S.//Klein, H. G.
A8.	Gates, D. M.//Schmerl, R. B.
A10.	Advanced views in primate biology
A19.	London and Sydney
A19.	New Haven, Conn.
A20.	Academic Press Inc.
A21.	1988
A23.	106
A26.	pp. 41
A33.	Ecol. Stud.
A42.	0-521-32160-3
A46.	Reproduction/social/behaviour/social organisation/bat/season/environment

B8.	Clutton-Brock, T. H.////Guiness, F. E.//Albon, S. E.
B10.	An introduction to population genetics theory
B19.	Belmont, CA.
B20.	Am. Zool. 27(3)
B20.	Burgess Publishing
B21.	1954
B42.	0-8240-7024-0
B43.	173-214
B43.	Uni-NR: 85WC4900 523+3
B43.	pp 1-123
B46.	ecology/review

D2.	Agren, G.////Zhou, Q.//Zhong, W.
D5.	A BASIC program for use in teaching population dynamics
D5.	A Study of the biology of the wild rabbit, Oryctolagus cuniculus (L.) in confined populations
D10.	Acta Biotheoretica
D21.	1887
D21.	Oct. 1988
D23.	1
D23.	10
D23.	1008
D25.	197-210
D25.	2
D25.	3/4
D26.	1-13
D26.	pp. 71
D43.	(franz.)
D43.	Effect of ACTH on behaviour / memory processes
D43.	Hanne fragen
D43.	aus: Readings in Sociobiology
D43.	bei Cina
D46.	Reproduction/Aggression/behaviour/mouse/social/female/reproductive success

G2.	Boyce, J. L.
G5.	Development of dispersionary and anti-predator behaviour in young wild rabbits, Oryctolagus cuniculus L. in sand dunes
G19.	Aberdeen
G20.	Ludwig-Maximilians-Universit�t
G20.	University of Aberdeen
G21.	1983
G27.	163 pp.
G27.	288 pp.
G38.	yes
G43.	mein Freund Martin
G45.	092166347
G46.	rabbit/physiology gen./dominance/behaviour

K2.	Dixon, K.R.////Chapman, J.A.//Rongstad, O.J.//Orhelein, K.M.
K5.	A comparison of home range size in Sylvilagus floridanus and S. bachmani
K8.	Myers, K.//MacInnes, C.D.K10.	International Theoretical Congress
K13.	Nov 1989
K14.	Edmonton, Canada
K19.	Guelph
K20.	University of Guelph
K21.	1979
K26.	103-136
K46.	hare/food/consumption/digestibility/nutrition

*/
const char DocTypes[NUMTYPES] = "ABCDGK";

const int Mappings[NUMTYPES][NUMFIELDS] = {
    {O_NONE, O_NONE, O_AUTHORS, O_NONE, O_NONE, O_TITLE, O_NONE, O_NONE, O_EDITOR, O_NONE, // A
     O_JOURNAL, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_CITY,
     O_PUBLISHER, O_NONE, O_DATE, O_NONE, O_NONE, O_NONE, O_PAGES, O_NONE, O_NONE, O_NONE,
     O_NONE, O_NONE, O_NONE, O_JOURNAL, O_VOL, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE,
     O_NONE, O_NONE, O_KEYWORD, O_TEXT, O_KEYWORD, O_KEYWORD, O_KEYWORD},

    {O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_EDITOR, O_NONE, // B
     O_JOURNAL, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_CITY,
     O_PUBLISHER, O_DATE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE,
     O_NONE, O_NONE, O_NONE, O_PAGES, O_NONE, O_NONE, O_KEYWORD},

    {O_NONE, O_NONE, O_AUTHORS, O_NONE, O_CITY, O_TITLE, O_NONE, O_NONE, O_NONE, O_NONE, // C
     O_JOURNAL, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE,
     O_NONE, O_DATE, O_NONE, O_VOL, O_NONE, O_VOLNO, O_PAGES, O_NONE, O_NONE, O_NONE,
     O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE,
     O_NONE, O_NONE, O_KEYWORD, O_TEXT, O_KEYWORD, O_KEYWORD, O_KEYWORD},

    {O_NONE, O_AUTHORS, O_NONE, O_NONE, O_TITLE, O_NONE, O_NONE, O_NONE, O_NONE, O_JOURNAL, // D
     O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE,
     O_DATE, O_NONE, O_VOL, O_NONE, O_VOLNO, O_PAGES, O_NONE, O_NONE, O_NONE, O_NONE,
     O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE,
     O_NONE, O_NONE, O_NONE, O_NONE, O_KEYWORD, O_NONE, O_NONE},

    {O_NONE, O_NONE, O_AUTHORS, O_NONE, O_TITLE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, // G
     O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_CITY,
     O_CITY, O_DATE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_PAGES, O_NONE, O_NONE,
     O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE,
     O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_KEYWORD, O_KEYWORD},

    {O_NONE, O_NONE, O_AUTHORS, O_NONE, O_NONE, O_TITLE, O_NONE, O_NONE, O_EDITOR, O_NONE, // K
     O_NONE, O_NONE, O_NONE, O_KEYWORD, O_KEYWORD, O_NONE, O_NONE, O_NONE, O_NONE, O_CITY,
     O_PUBLISHER, O_DATE, O_NONE, O_NONE, O_NONE, O_NONE, O_PAGES, O_NONE, O_NONE, O_NONE,
     O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE,
     O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_NONE, O_KEYWORD}

};

long BufSz;
LPSTR tstr1;
LPSTR tstr2;
LPSTR r[NUMFIELDS];
static TImportRef Tmp;
int EoF, Opt;
HINSTANCE hInst;

#ifdef WIN32
TImportRef t_export *LoadRef(HWND AParent, LPMMIOINFO FS)
{
#else
TImportRef FAR *PASCAL _export LoadRef(HWND AParent, LPMMIOINFO FS, LPSTR INIPath)
{
#endif
  LPSTR *p;
  int m, n;

  Tmp.Result = 0;
  Tmp.RefType = 0;

  p = &Tmp.Authors;

  if (Opt == -1)
    Opt = GetConfigInt("ProCite", "Opt", 1);

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
    n = ReadLine(FS, tstr1, &EoF);
  } while ((!EoF) && (tstr1[0] == '\0'));

  m = n;

  while (m &&
         ((tstr1[n - 1] != '\"') ||
          ((tstr1[n - 1] == '\"') && (tstr1[n - 2] == ','))))
  {
    m = ReadLine(FS, tstr2, &EoF);

    if (m)
    {
      lstrcat(tstr1, &tstr2[1]);
      n += (m - 1);
    }
  }

  // If EoF then we may not have read a reference
  if (EoF)
  {
    if (tstr1[0] == '\0')
    {
      Tmp.Result = 2;
      return &Tmp;
    }
    else
      Tmp.Result = 1;
  }

  // Split record into its NUMFIELDS consituents.
  SplitRecord();

  if (Opt & 1)
  {

    lstrcpy(tstr1, "unread");

    if (Tmp.Keywords)
    {
      lstrcat(tstr1, "\r\n");
      lstrcat(tstr1, Tmp.Keywords);
      free(Tmp.Keywords);
    }

    Tmp.Keywords = strdup(tstr1);
  }

  return &Tmp;
}

LPSTR t_export WhoAmI(void)
{
  return "ProCite format";
}

LPSTR t_export GetSpecs(void)
{
  return "ProCite text file (*.asc, *.dat)\0*.ASC;*.DAT\0All files (*.*)\0*.*\0\0";
}

BOOL Opt_OnInitDialog(HWND dlg, HWND hwndFocus, LPARAM lParam)
{
  int N;

  N = GetConfigInt("ProCite", "Opt", 1);
  CheckDlgButton(dlg, 103, N & 1);
  return TRUE;
}

void Opt_OnCommand(HWND Dialog, int id, HWND hwndCtl, UINT codeNotify)
{
  switch (id)
  {
  case IDOK:
    EndDialog(Dialog,
              IsDlgButtonChecked(Dialog, 103));
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
void t_export Opts(HWND AParent, LPSTR APath)
{
#endif

  Opt = DialogBox(hInst, "OPTS", AParent, OptProc);
  if (Opt != -1)
    SetConfigInt("ProCite", "Opt", Opt);
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
    return ((tstr1 && tstr2 && CheckVer()) ? TRUE : FALSE);
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
    {
      if (CheckVer())
        return 0;
      else
      {
        MessageBox(0, "ProCite import requires RIMPEXP.DLL 1.3 or later", "PROCITE.FLT error", MB_ICONSTOP | MB_OK);
        return 1;
      }
    }
  }
  else
    return 0;
}
#endif

void SplitRecord(void)
{
  // ProCite records are comma delimited, and all entries are enclosed in quotes:
  // eg:  "a","b","c" etc
  char *p, *q, **base;
  int n, l, dt;

  p = tstr1;

  for (p = tstr1, n = 0; p != NULL; n++)
  {

    q = strstr(p, "\",\"");

    if (q)
      q[1] = '\0';

    l = wsprintf(tstr2, "%s", p) - 1;

    if (l > 1)
    {
      tstr2[l] = '\0';

      r[n] = strdup(&tstr2[1]);
    }
    else
      r[n] = NULL;

    p = (q ? &q[2] : q);

  } // for (p...)

  for (dt = 0;
       (dt < NUMTYPES) && (r[0][0] != DocTypes[dt]);
       dt++)
    ;

  if (dt == NUMTYPES)
  {
    // Unknown reference type, assume "C"
    dt = 1;
  }

  switch (dt)
  {
  case 0:
    Tmp.RefType = 1;
    break;
  default:
    Tmp.RefType = 0;
  }

  // Now put the reference into Tmp, processing names and keywords too.

  base = &Tmp.Authors;
  tstr2[0] = '\0';

  for (n = 1; n < NUMFIELDS; n++)
  {
    if (r[n])
    {

      switch (Mappings[dt][n])
      {
      case O_NONE:
        break;
      case O_AUTHORS:
      {
        ProcessNames(n);
        if (base[O_AUTHORS])
          free(base[O_AUTHORS]);
        base[O_AUTHORS] = strdup(r[n]);
        break;
      }
      case O_EDITOR:
      {
        ProcessNames(n);
        if (base[O_EDITOR])
          free(base[O_EDITOR]);
        base[O_EDITOR] = strdup(r[n]);
        break;
      }
      case O_KEYWORD:
      {
        ProcessKeywords(n);
        break;
      }
      default:
      {
        if (base[Mappings[dt][n]])
          free(base[Mappings[dt][n]]);

        base[Mappings[dt][n]] = strdup(r[n]);
      }
      }
    }
  }

  if (tstr2[0] != '\0')
    Tmp.Keywords = strdup(tstr2);
}

void ProcessKeywords(int Field)
{
  char *p, *q;

  p = r[Field];

  q = strchr(p, '/');

  while (q)
  {
    q[0] = '\0';
    if (tstr2[0] != '\0')
      lstrcat(tstr2, "\r\n");
    lstrcat(tstr2, p);

    p = &q[1];
    q = strchr(p, '/');
  }

  if (tstr2[0] != '\0')
    lstrcat(tstr2, "\r\n");
  lstrcat(tstr2, p);
}

int CheckVer(void)
{
  VS_FIXEDFILEINFO *rver;
  DWORD verHnd;
  DWORD verSz;
  UINT rlen;
  char t1[260];

  verSz = GetFileVersionInfoSize("RIMPEXP.DLL", &verHnd);
  GetFileVersionInfo("RIMPEXP.DLL", verHnd, sizeof(t1), t1);
  VerQueryValue(t1, "\\", (void **)&rver, &rlen);
  return (rver->dwFileVersionMS > 0x00010002);
}

void ProcessNames(int Field)
{
  // Names are separated by two forward slashes.
  // Replace these by "\r\n"
  char *p;

  for (p = strstr(r[Field], "//");
       p != NULL;
       p = strstr(p, "//"))

  {
    p[0] = '\r';
    p[1] = '\n';
  }
}
