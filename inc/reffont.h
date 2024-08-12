#ifndef REFFONT_H

struct TRefFont {
  int Printer;
  HFONT SFont;
  LOGFONT *AFnt;
  CHOOSEFONT ChFnt;
  TRefFont(int Print);
  TRefFont(int Print, LPLOGFONT Desc);
  TRefFont(int Print, HWND Wnd);
  TRefFont(int Print, LPTSTR Section, LPTSTR Key);
  ~TRefFont(void);
  int Edit(HWND Wnd);
  void PutToIni(LPTSTR Section, LPTSTR Key);
  void SetListParms(HWND Wnd);
private:
  void Init(int Print);
  int Create(void);
  int CommDlg(int InitDlg, HWND Wnd);
};

typedef TRefFont * LPRefFont;

#define REFFONT_H
#endif
