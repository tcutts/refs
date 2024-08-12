#ifdef __cplusplus
extern "C" {
#endif

// Please ignore all the UNICODE stuff.  This is for inclusion in a future
// version of Refs once Unicode has become a more widely adopted standard.

#ifdef WIN32
  int  GetConfigInt(LPTSTR, LPTSTR, int);
  int  GetConfigStr(LPTSTR, int, LPTSTR, LPTSTR, LPTSTR);
  void  SetConfigStr(LPTSTR, LPTSTR, LPTSTR);
  void  SetConfigInt(LPTSTR, LPTSTR, int);
  void  DeleteConfigTree(LPTSTR);

/* GetBufSz returns the size of the buffer being used for MMIO buffered
   file IO */
  long  GetBufSz(void);

/* SetBufSz sets the buffer size.  This is not intended for use by
   filters, and once it has been called once it simply returns the
   current size of the buffer.  REFS.EXE calls this immediately before
   it begins calling LoadRef or SaveRef in the filter. */
  long  SetBufSz(long);

#ifdef _UNICODE

  #define FFMT_ANSI 0
  #define FFMT_UNICODE_L 1
  #define FFMT_UNICODE_B 2
  #define FFMT_UNKNOWN -1

/* IsFileUnicode returns:
  FFMT_ANSI:      File is probably ANSI
  FFMT_UNICODE_L: File is (hopefully) little endian Unicode
  FFMT_UNICODE_B: File is big endian Unicode
  FFMT_UNKNOWN:   File format has not yet been determined.
 */
  int IsFileUnicode(void);

/* Simple write a null terminated string to the MMIO file.  64k max.
   No terminating CR or LF */
  int  WriteLineA(LPMMIOINFO, LPSTR);
  int  WriteLineW(LPMMIOINFO, LPWSTR);

/* same as vfprintf(), but to the MMIO file specified */
  int  vMMIOprintfA(LPMMIOINFO, LPSTR, va_list);
  int  vMMIOprintfW(LPMMIOINFO, LPWSTR, va_list);

/* Read a line from the MMIO file specified.  The terminating
   CRLF is discarded. Returns the number of characters read into the LPTSTR argument */

  int  ReadLineA(LPMMIOINFO, LPSTR, BOOL FAR *);
  int  ReadLineW(LPMMIOINFO, LPWSTR, BOOL FAR *);

  #define ReadLine ReadLineW
  #define WriteLine WriteLineW
  #define vMMIOprintf vMMIOprintfW
#else
  int  WriteLine(LPMMIOINFO, LPSTR);

  int  vMMIOprintf(LPMMIOINFO, LPSTR, va_list);
  
  int  ReadLine(LPMMIOINFO, LPSTR, BOOL FAR *);
#endif

#else // 16-bit Windows

  int FAR PASCAL GetConfigInt(LPTSTR, LPTSTR, int);
  int FAR PASCAL GetConfigStr(LPTSTR, int, LPTSTR, LPTSTR, LPTSTR);
  void FAR PASCAL SetConfigStr(LPTSTR, LPTSTR, LPTSTR);
  void FAR PASCAL SetConfigInt(LPTSTR, LPTSTR, int);
  void FAR PASCAL DeleteConfigTree(LPTSTR);

  char FAR * PASCAL GetINIFilePath(void);
  void FAR PASCAL SetINIFilePath(LPTSTR);

/* GetBufSz returns the size of the buffer being used for MMIO buffered
   file IO */
  long FAR PASCAL GetBufSz(void);

/* SetBufSz sets the buffer size.  This is not intended for use by
   filters, and once it has been called once it simply returns the
   current size of the buffer.  REFS.EXE calls this immediately before
   it begins calling LoadRef or SaveRef in the filter. */
  long FAR PASCAL SetBufSz(long);

/* Simple write a null terminated string to the MMIO file.  64k max.
   No terminating CR or LF */
  int FAR PASCAL WriteLine(LPMMIOINFO, LPTSTR);

/* same as vfprintf(), but to the MMIO file specified */
  int FAR PASCAL vMMIOprintf(LPMMIOINFO, LPTSTR, va_list);

/* Read a line from the MMIO file specified.  The terminating
   CRLF is discarded. Returns the number of characters read into the LPTSTR argument */

  int FAR PASCAL ReadLine(LPMMIOINFO, LPTSTR, BOOL FAR *);

#endif //!WIN32

#ifdef __cplusplus
}
#endif
