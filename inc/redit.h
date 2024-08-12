#ifdef USE_RTF

#define RTF_F_ALL		0
#define RTF_F_SELECTION	1

struct TRichEdit:TObject {
  LPBYTE d;
  DWORD sofar;
  DWORD length;
  EDITSTREAM stream;
  HWND pwnd;
  int ctlid;

  HWND hWnd;

  TRichEdit(int wsStyle, int t, int l, int w, int h, HWND parent, HMENU id);
  ~TRichEdit(void);
//  int GetText();
//  int GetRTF();
//  int SetText();
//  int SetRTF();
  int Save(void);
  int Print(FORMATRANGE * fr);
  int SetData(LPTSTR data, int type);
  int GetData(LPTSTR data, int cbdata, int type);
  void SetFaceName(LPLOGFONT AFnt, int selection);
  void SetPointSize(LPLOGFONT AFnt, int selection);
  void SelectAll(void);
};

typedef TRichEdit * hRichEdit;
#endif
