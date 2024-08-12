
#ifndef CUSTOM
//REFNAG.CPP
extern void NagScreen(HWND);
extern void About(void);
extern "C" BOOL CALLBACK _export RegProc(HWND, UINT, WPARAM, LPARAM);
extern "C" BOOL CALLBACK _export NagProc(HWND, UINT, WPARAM, LPARAM);
extern "C" BOOL CALLBACK _export TimeNagProc(HWND, UINT, WPARAM, LPARAM);
#endif
