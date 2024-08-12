//REFPAINT.CPP
extern void DefaultStatus(void);
extern void Paint(void);
#ifdef WIN32
extern void DrawStatus(LPTSTR, int);
#else
extern void DrawStatus(HDC, LPTSTR);
#endif
