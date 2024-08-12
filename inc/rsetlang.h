extern long MajorVersion;
extern long MinorVersion;

// RSETLANG.CPP
extern void GetRefsVersionInfo(void);
extern void SetLanguage(LPTSTR);
extern "C" BOOL CALLBACK _export SetLangProc(HWND, UINT, WPARAM, LPARAM);

