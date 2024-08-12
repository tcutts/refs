#include <tchar.h>
#include <windows.h>

#ifdef WIN32
#define t_export _declspec(dllexport)
#else
#define t_export CALLBACK _export
#endif

#define str_DLLDescribe 590

char t[256];
HINSTANCE r;

LPTSTR t_export Describe(void){

  if (LoadString(r, str_DLLDescribe, t, sizeof(t)/sizeof(_TCHAR)))
  {
#ifdef _DEBUG
    MessageBox(0, t, NULL, MB_OK);
#endif
    return t;
  }
  else
  {
#ifdef WIN32
    LPVOID lpMessageBuffer;
 
    FormatMessage(
      FORMAT_MESSAGE_ALLOCATE_BUFFER |
      FORMAT_MESSAGE_FROM_SYSTEM,
      NULL,
      GetLastError(),
      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), //The user default language
      (LPTSTR) &lpMessageBuffer,
      0,
      NULL );
 
    //... now display this string

    MessageBox(0, (LPTSTR)lpMessageBuffer, NULL, MB_OK);
    // Free the buffer allocated by the system
 
    LocalFree( lpMessageBuffer );
#endif
    return (_T("Not known"));
  }
}

#ifdef WIN32

BOOL WINAPI DllMain(HINSTANCE  hinstDLL, DWORD  fdwReason, LPVOID  lpvReserved){
   if (fdwReason==DLL_PROCESS_ATTACH)
     r = hinstDLL;
   return TRUE;
}

#else

int t_export LibMain(HINSTANCE hInstance, WORD wDataSeg, WORD cbHeapSize, LPSTR lpCmdLine){
  r = hInstance;
  return 1;
}

#endif
