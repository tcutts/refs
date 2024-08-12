#ifndef FULL_RC
  #include "..\..\inc\config.h"

  #ifdef WIN32
    #include <windows.h>
    #include <winver.h>
  #else
    #include "d:\msvc\include\windows.h"
    #include "d:\msvc\include\ver.h"
  #endif

  #include "..\..\inc\refs.h"

  #ifdef DUPLICATE
    #undef DUPLICATE
  #endif

  #define FULL_RC
#endif
