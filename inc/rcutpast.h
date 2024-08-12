extern LPSrchColl CutPasteColl;

//RCUTPAST.CPP
extern void DeleteThem(LPRefWndData, int);
extern void AddToBib(LPRefWndData);
extern void AddKeyword(LPRefWndData);
extern int GetWordsToAdd(HWND, int);
extern void AddTheWords(LPRef, LPTSTR);
extern void CopyThem(LPRefWndData);
extern void PasteIt(LPRefWndData, LPRef);
extern void PasteThem(LPRefWndData);
extern "C" BOOL CALLBACK KeyProc(HWND, UINT, WPARAM, LPARAM);
