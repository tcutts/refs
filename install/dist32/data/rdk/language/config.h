// Change this file to enable/disable features in Refs, and modify certain buffer sizes

// CC_TOOLBAR:  Adds code for a Common Controls toolbar
// CC_STATUS:   Uses a common controls status bar rather than Refs' own.
// MODAL_EDIT:  Allow only one reference to be edited at a time.  Safer, but less useful!
// USE_RTF:     Uses a Rich Edit Control for printing and bibliography formatting.  Incompatible with Win16.
// REGEXP:	Allow RegExp searches

#ifdef WIN32

  #define CC_TOOLBAR
  #define CC_STATUS
  #define REGEXP
  #ifndef USE_RTF
    #define USE_RTF
  #endif

  #ifdef R79
    #ifdef MODAL_EDIT
      #undef MODAL_EDIT
    #endif
  #else
    #define MODAL_EDIT
  #endif

  #ifdef  USE_RTF
    #define MAX_EDIT_CONTENTS 0x0000FFE0L
  #else
    #define MAX_EDIT_CONTENTS 0x0007FFFFL
  #endif

#else

  #define MODAL_EDIT
  #define REGEXP

  #ifdef USE_RTF
    #undef USE_RTF
  #endif

  #define MAX_EDIT_CONTENTS 0x7FFF

  #ifndef MAX_PATH
    #define MAX_PATH _MAX_PATH
  #endif

#endif

#define OLD_FILES 6    // Number of filenames to remember
#define MAX_FILES 63   // Max number of open files
#define HOW_OFTEN 63   // How often to update file open/save progress windows
#define RES_STR  128   // Max length of a resource string

#define SCRATCH_SIZE 16384*sizeof(_TCHAR)  // Size of scratch string buffers
#define MAX_FMT_LENGTH 512  // Maximum length of bibliography format
