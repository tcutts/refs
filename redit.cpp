#include "inc/globals.h"
#ifdef USE_RTF
#include "inc/redit.h"

int TRichEdit::Print(FORMATRANGE *fr)
{
  return -1;
}

TRichEdit::TRichEdit(int wsStyle, int t, int l, int w, int h, HWND parent, HMENU id)
{
  ctlid = (int)id;

  hWnd = CreateWindowEx(
      WS_EX_CLIENTEDGE,
      _T("RICHEDIT"),
      _T(""),
      wsStyle,
      t, l, w, h,
      pwnd = parent,
      id,
      hinstCurrent,
      NULL);
}

TRichEdit::~TRichEdit(void)
{
  DestroyWindow(hWnd);
}

void TRichEdit::SetPointSize(LPLOGFONT AFnt, int selection)
{
  CHARFORMAT cf;

  if (!AFnt)
    return;

  // Fill out the CHARFORMAT structure to set the point size.
  cf.cbSize = sizeof(cf);
  cf.dwMask = CFM_SIZE;

  // Multiply by 20 to convert to twips, perhaps?
  cf.yHeight = AFnt->lfHeight;

  if (cf.yHeight < 0)
    cf.yHeight *= -1;

  // Set the point size.
  SendMessage(hWnd, EM_SETCHARFORMAT, selection, (LPARAM)&cf);
}

void TRichEdit::SetFaceName(LPLOGFONT AFnt, int selection)
// Replaces character formatting according to a LOGFONT structure
// see RTF_F_ flags for selection.
{
  CHARFORMAT cf;

  if (!AFnt)
    return;

  cf.cbSize = sizeof(CHARFORMAT);
  cf.dwMask = CFM_ITALIC | CFM_BOLD | CFM_UNDERLINE;

  SendMessage(hWnd, EM_GETCHARFORMAT, selection, (LPARAM)&cf);

  // Include the mask to ask the rich edit control for the current
  // typeface.
  cf.dwMask |= CFM_FACE;

  // Set the new typeface, preserving the previous effects.
  lstrcpy(cf.szFaceName, AFnt->lfFaceName);
  SendMessage(hWnd, EM_SETCHARFORMAT, selection,
              (LPARAM)&cf);
}

void TRichEdit::SelectAll(void)
{
  SendMessage(hWnd, EM_SETSEL, 0, -1);
}

DWORD CALLBACK RSetCallback(DWORD dwCookie,
                            LPBYTE pbBuff, LONG cb, LONG FAR *pcb)
{
  hRichEdit s;
  LONG n;
  DWORD t;

  s = (hRichEdit)dwCookie;

  n = s->length - s->sofar;

  if (n <= 0)
    return 1;

  t = (n >= cb) ? cb : n;

  memcpy(pbBuff, &s->d[s->sofar], t);
  s->sofar += t;

  *pcb = t;

  return 0;
}

int TRichEdit::SetData(LPTSTR data, int type)
{

  stream.dwCookie = (DWORD)this;
  stream.pfnCallback = RSetCallback;
  stream.dwError = 0;
  sofar = 0;
  length = (lstrlen(data) + 1) * sizeof(TCHAR);
  d = (LPBYTE)data;

  SendMessage(hWnd, EM_STREAMIN, (WPARAM)type, (LPARAM)&stream);

  return (stream.dwError);
}

DWORD CALLBACK RGetCallback(DWORD dwCookie,
                            LPBYTE pbBuff, LONG cb, LONG FAR *pcb)
{
  hRichEdit s;
  LONG n;
  DWORD t;

  s = (hRichEdit)dwCookie;

  // how much of buffer is left?
  n = s->length - s->sofar;

  // if nothing, return error
  if (n <= 0)
    return 1;

  // fill as much as possible
  t = (n >= cb) ? cb : n;

  memcpy(&s->d[s->sofar], pbBuff, t);
  s->sofar += t;

  *pcb = t;

  // If buffer was filled, return an error.
  if (t != (DWORD)cb)
    return 2;

  return 0;
}

int TRichEdit::GetData(LPTSTR data, int cbData, int type)
{
  stream.dwCookie = (DWORD)this;
  stream.pfnCallback = RSetCallback;
  stream.dwError = 0;
  sofar = 0;
  length = cbData;
  d = (LPBYTE)data;

  SendMessage(hWnd, EM_STREAMOUT, (WPARAM)type, (LPARAM)&stream);

  return (stream.dwError);
}

DWORD CALLBACK SaveCallback(DWORD dwCookie,
                            LPBYTE pbBuff, LONG cb, LONG FAR *pcb)
{
  WriteFile((HANDLE)dwCookie, pbBuff, cb, (DWORD FAR *)pcb, NULL);
  return 0;
}

extern _TCHAR LastDir[MAX_PATH];

int TRichEdit::Save(void)
{
  _TCHAR APath[MAX_PATH];
  LPTSTR p;
  HFILE hFile;
  OPENFILENAME of;
  OFSTRUCT ofs;

  *APath = _T('\0');

  of.lStructSize = sizeof(OPENFILENAME);
  of.hwndOwner = FrameWnd;
  of.hInstance = hinstCurrent;
  of.lpstrFilter = BibFSpecs;
  of.lpstrCustomFilter = NULL;
  of.nFilterIndex = 1;
  of.lpstrFile = APath;
  of.nMaxFile = MAX_PATH;
  of.lpstrFileTitle = NULL;
  of.lpstrInitialDir = (LastDir[0] == _T('\0')) ? NULL : LastDir;
  of.lpstrTitle = NULL;
  of.Flags = OFN_HIDEREADONLY | OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_EXPLORER;
  of.lpstrDefExt = "$_t";

  if (GetSaveFileName(&of))
  {
    p = _tcsstr(APath, of.lpstrDefExt);

    if (p) // want default extension
      lstrcpy(p, of.nFilterIndex == 1 ? "RTF" : "TXT");

    if (hFile = OpenFile(APath, &ofs, OF_CREATE))
    {
      stream.dwCookie = hFile;
      stream.dwError = 0;
      stream.pfnCallback = SaveCallback;

      SendMessage(hWnd, EM_STREAMOUT, (WPARAM)of.nFilterIndex == 1 ? SF_RTF : SF_TEXT, (LPARAM)&stream);

      CloseHandle((HANDLE)hFile);
      return 0;
    }
    return -1;
  }

  return IDCANCEL;
}

#endif // USE_RTF
