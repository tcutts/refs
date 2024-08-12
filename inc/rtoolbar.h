
#define TOOL_BUTTON_NO 21

extern HWND hWndToolbar;
extern void UpdateButtons(void);

#ifdef WIN32
extern TBBUTTON tbButtons[TOOL_BUTTON_NO];
#else
extern TBBUTTON tbButtons[TOOL_BUTTON_NO-1];
#endif

#ifdef WIN32
extern TOOLINFO tbToolInfo;
#endif
