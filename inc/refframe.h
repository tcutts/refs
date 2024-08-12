//REFFRAME.CPP
extern void NewClient(int, LPTSTR);
extern "C" LRESULT CALLBACK _export RefFrameProc(HWND, UINT, WPARAM, LPARAM);

#ifdef CC_TOOLBAR
extern void UpdateButtons(void);
#endif
