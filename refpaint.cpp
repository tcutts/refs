#include "inc/globals.h"

#ifdef CC_STATUS
#include "inc/status.h"

void DrawStatus(LPTSTR AStr, int Section)
{
  // Set the text in the first part to normal.
  SendMessage(hWndStatus, SB_SETTEXT, Section,
              (LPARAM)AStr);
}

#else // not CC_STATUS

void DrawStatus(HDC DC, LPTSTR AStr)
{
  int OBMode;
  HPEN GreyP;

  // Draw status bar, without text

  GreyP = CreatePen(PS_SOLID, 0, 0x007F7F7F);
  SelectPen(DC, GreyP);

  MoveToEx(DC, StatusRect.right - 2, StatusRect.top + 2, NULL);
  LineTo(DC, StatusRect.left + 2, StatusRect.top + 2);
  LineTo(DC, StatusRect.left + 2, StatusRect.bottom - 3);
  MoveToEx(DC, StatusRect.left, StatusRect.bottom - 1, NULL);
  LineTo(DC, StatusRect.right - 2, StatusRect.bottom - 1);
  LineTo(DC, StatusRect.right - 2, StatusRect.top);

  SelectPen(DC, GetStockObject(WHITE_PEN));
  DeletePen(GreyP);

  LineTo(DC, StatusRect.left, StatusRect.top);
  LineTo(DC, StatusRect.left, StatusRect.bottom);
  MoveToEx(DC, StatusRect.left + 2, StatusRect.bottom - 3, NULL);
  LineTo(DC, StatusRect.right - 3, StatusRect.bottom - 3);
  LineTo(DC, StatusRect.right - 3, StatusRect.top + 2);

  SelectFont(DC, GetStockObject(SYSTEM_FONT));
  OBMode = SetBkMode(DC, TRANSPARENT);
  TextOut(DC, StatusRect.left + 5, StatusRect.top + 3, AStr, lstrlen(AStr));
  SetBkMode(DC, OBMode);
}
#endif

void DefaultStatus(void)
{
  long n;
  LPTSTR s, t, t1, t2;

#ifndef CC_STATUS
  HDC StDC;
#endif

  t = (LPTSTR)malloc(MAX_PATH * sizeof(_TCHAR) + 10);
  t1 = (LPTSTR)malloc(MAX_PATH * sizeof(_TCHAR) + 10);
  t2 = (LPTSTR)malloc(MAX_PATH * sizeof(_TCHAR) + 10);
  s = t2;
  s[0] = t1[0] = _T('\0');

  if (IsWindowEnabled(FrameWnd))
  {
    if (ActiveFile)
    {
      n = LoadString(ResInstance, fmt_RefNo, t, MAX_PATH + 9);
      t[n] = _T('\0');
      GetWindowText(ActiveFile->Window, s, SCRATCH_SIZE - 1);
      n = ActiveFile->Refs->count;
      wsprintf(t1, t, s, n);
    }
  }

#ifndef CC_STATUS
  StDC = GetDC(FrameWnd);

  SelectBrush(StDC, GetStockObject(LTGRAY_BRUSH));

  Rectangle(StDC, StatusRect.left, StatusRect.top, StatusRect.right, StatusRect.bottom);

  DrawStatus(StDC, t1);
  ReleaseDC(FrameWnd, StDC);

#else // CC_STATUS

  DrawStatus(t1, STATUS_MESSAGE_SECTION);

#endif
  free(t2);
  free(t1);
  free(t);
}

void Paint(void)
{
  PAINTSTRUCT TP;

  // Just paint status bar.  That's all
  BeginPaint(FrameWnd, &TP);
  DefaultStatus();
  EndPaint(FrameWnd, &TP);
}
