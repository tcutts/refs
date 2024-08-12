typedef struct {
  BYTE Result, RefType;
  LPTSTR Authors, Date, Title, Journal, Vol, VolNo, Pages, Text;
  LPTSTR Keywords, Publisher, City, Editor, SortStr;
} TImportRef;

// These offsets should allow you to treet the address of Authors
// as an LPSTR* and then you can use these offsets to reach members
// of that array.

#define O_NONE        -1
#define O_AUTHORS      0
#define O_DATE         1
#define O_TITLE        2
#define O_JOURNAL      3
#define O_VOL          4
#define O_VOLNO        5
#define O_PAGES        6
#define O_TEXT         7
#define O_KEYWORD      8
#define O_PUBLISHER    9
#define O_CITY        10
#define O_EDITOR      11

typedef TImportRef FAR* LPImportRef;
