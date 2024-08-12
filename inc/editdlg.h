// Structure associated with each edit window:

typedef struct
{
  // Reference being edited
  LPRef ThisRef;
  // Current scrollbar positions
  int cur_x, cur_y;
  int ScrollRangeX;
  int ScrollRangeY;
  // Current and old window dimensions
  RECT OEdit;
  TESz EditSize;
} EditData;

// Controls to be moved
extern int ctls_to_move[23][2];
extern int CtrlID[MAX_FIELDS];
extern HWND CurrentEditor;

extern TESz NEAR EditSize;

extern void EditIt(long N);
extern "C" BOOL CALLBACK _export EditRef(HWND, UINT, WPARAM, LPARAM);
