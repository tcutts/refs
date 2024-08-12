#ifdef WIN32
extern "C" int t_export SaveRef(HWND, LPImportRef, LPMMIOINFO);
extern "C" TImportRef t_export *LoadRef(HWND, LPMMIOINFO);
extern "C" void t_export Opts(HWND);
#else
extern "C" int t_export SaveRef(HWND, LPImportRef, LPMMIOINFO, LPSTR);
extern "C" TImportRef t_export *LoadRef(HWND, LPMMIOINFO, LPSTR);
extern "C" void t_export Opts(HWND, LPSTR);
#endif
extern "C" LPSTR t_export WhoAmI(void);
extern "C" LPSTR t_export GetSpecs(void);

