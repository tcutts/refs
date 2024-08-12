# Microsoft Visual C++ Generated NMAKE File, Format Version 2.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Win95 Debug
!MESSAGE No configuration specified.  Defaulting to Win95 Debug.
!ENDIF 

!IF "$(CFG)" != "Win32 FERIC" && "$(CFG)" != "Win95 Release" && "$(CFG)" !=\
 "Win95 Debug" && "$(CFG)" != "Unicode Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "REFS32.MAK" CFG="Win95 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Win32 FERIC" (based on "Win32 (x86) Application")
!MESSAGE "Win95 Release" (based on "Win32 (x86) Application")
!MESSAGE "Win95 Debug" (based on "Win32 (x86) Application")
!MESSAGE "Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

################################################################################
# Begin Project
# PROP Target_Last_Scanned "Win95 Debug"
MTL=MkTypLib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Win32 FERIC"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Win32_FE"
# PROP BASE Intermediate_Dir "Win32_FE"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Win32_FE"
# PROP Intermediate_Dir "Win32_FE"
OUTDIR=.\Win32_FE
INTDIR=.\Win32_FE

ALL : $(OUTDIR)/REFS32.exe $(OUTDIR)/REFS32.map $(OUTDIR)/REFS32.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE CPP /nologo /G4 /Zp2 /W2 /YX"globals.h" /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /c
# ADD CPP /nologo /Zp2 /W2 /YX"globals.h" /O2 /D "NDEBUG" /D "FERIC" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "CC_TOOLBAR" /D "CC_STATUS" /D "STRICT" /FR /c
CPP_PROJ=/nologo /Zp2 /W2 /YX"globals.h" /O2 /D "NDEBUG" /D "FERIC" /D "WIN32"\
 /D "_WINDOWS" /D "_MBCS" /D "CC_TOOLBAR" /D "CC_STATUS" /D "STRICT"\
 /FR$(INTDIR)/ /Fp$(OUTDIR)/"REFS32.pch" /Fo$(INTDIR)/ /c 
CPP_OBJS=.\Win32_FE/
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG" /d "FERIC" /d "CC_TOOLBAR"
RSC_PROJ=/l 0x809 /fo$(INTDIR)/"REFS.res" /d "NDEBUG" /d "FERIC" /d\
 "CC_TOOLBAR" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"REFS32.bsc" 
BSC32_SBRS= \
	$(INTDIR)/GLOBALS.SBR \
	$(INTDIR)/MYCOLLS.SBR \
	$(INTDIR)/OBJECT.SBR \
	$(INTDIR)/OTREF.SBR \
	$(INTDIR)/OTREFWND.SBR \
	$(INTDIR)/OTSCOLL.SBR \
	$(INTDIR)/RCONFOPT.SBR \
	$(INTDIR)/RCUTPAST.SBR \
	$(INTDIR)/REFABOUT.SBR \
	$(INTDIR)/REFBIBS.SBR \
	$(INTDIR)/REFFONT.SBR \
	$(INTDIR)/REFCHILD.SBR \
	$(INTDIR)/REFFRAME.SBR \
	$(INTDIR)/REFIMP.SBR \
	$(INTDIR)/REFINOPT.SBR \
	$(INTDIR)/REFIO.SBR \
	$(INTDIR)/REFLOPTS.SBR \
	$(INTDIR)/REFNAG.SBR \
	$(INTDIR)/REFPAINT.SBR \
	$(INTDIR)/REFPRN.SBR \
	$(INTDIR)/REFS.SBR \
	$(INTDIR)/RSETLANG.SBR \
	$(INTDIR)/RSRCHOPT.SBR \
	$(INTDIR)/RSRTOPT.SBR \
	$(INTDIR)/JLISTDLG.SBR \
	$(INTDIR)/AUTHDLG.SBR \
	$(INTDIR)/EDITDLG.SBR

$(OUTDIR)/REFS32.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 version.lib ctl3d32s.lib oldnames.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib uuid.lib /NOLOGO /STACK:0x10240 /SUBSYSTEM:windows /MAP /MACHINE:IX86
# ADD LINK32 ctl3d32.lib version.lib oldnames.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib comctl32.lib advapi32.lib shell32.lib uuid.lib /NOLOGO /STACK:0x10240 /SUBSYSTEM:windows /INCREMENTAL:yes /MAP /MACHINE:IX86
LINK32_FLAGS=ctl3d32.lib version.lib oldnames.lib winmm.lib kernel32.lib\
 user32.lib gdi32.lib winspool.lib comdlg32.lib comctl32.lib advapi32.lib\
 shell32.lib uuid.lib /NOLOGO /STACK:0x10240 /SUBSYSTEM:windows /INCREMENTAL:yes\
 /PDB:$(OUTDIR)/"REFS32.pdb" /MAP:$(INTDIR)/"REFS32.map" /MACHINE:IX86\
 /OUT:$(OUTDIR)/"REFS32.exe" 
DEF_FILE=
LINK32_OBJS= \
	.\WIN95_RE\RIMPEXP32.lib \
	$(INTDIR)/GLOBALS.OBJ \
	$(INTDIR)/MYCOLLS.OBJ \
	$(INTDIR)/OBJECT.OBJ \
	$(INTDIR)/OTREF.OBJ \
	$(INTDIR)/OTREFWND.OBJ \
	$(INTDIR)/OTSCOLL.OBJ \
	$(INTDIR)/RCONFOPT.OBJ \
	$(INTDIR)/RCUTPAST.OBJ \
	$(INTDIR)/REFABOUT.OBJ \
	$(INTDIR)/REFBIBS.OBJ \
	$(INTDIR)/REFFONT.OBJ \
	$(INTDIR)/REFCHILD.OBJ \
	$(INTDIR)/REFFRAME.OBJ \
	$(INTDIR)/REFIMP.OBJ \
	$(INTDIR)/REFINOPT.OBJ \
	$(INTDIR)/REFIO.OBJ \
	$(INTDIR)/REFLOPTS.OBJ \
	$(INTDIR)/REFNAG.OBJ \
	$(INTDIR)/REFPAINT.OBJ \
	$(INTDIR)/REFPRN.OBJ \
	$(INTDIR)/REFS.OBJ \
	$(INTDIR)/RSETLANG.OBJ \
	$(INTDIR)/RSRCHOPT.OBJ \
	$(INTDIR)/RSRTOPT.OBJ \
	$(INTDIR)/REFS.res \
	$(INTDIR)/JLISTDLG.OBJ \
	$(INTDIR)/AUTHDLG.OBJ \
	$(INTDIR)/EDITDLG.OBJ

$(OUTDIR)/REFS32.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Win95 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Win95_Re"
# PROP BASE Intermediate_Dir "Win95_Re"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Win95_Re"
# PROP Intermediate_Dir "Win95_Re"
OUTDIR=.\Win95_Re
INTDIR=.\Win95_Re

ALL : $(OUTDIR)/REFS32.exe $(OUTDIR)/REFS32.map $(OUTDIR)/REFS32.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE CPP /nologo /G4 /Zp2 /W2 /YX"globals.h" /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "STRICT" /FR /c
# ADD CPP /nologo /Zp2 /W2 /YX"globals.h" /O2 /D "NDEBUG" /D "FOR95" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "CC_TOOLBAR" /D "CC_STATUS" /D "STRICT" /FR /c
# SUBTRACT CPP /X
CPP_PROJ=/nologo /Zp2 /W2 /YX"globals.h" /O2 /D "NDEBUG" /D "FOR95" /D "WIN32"\
 /D "WINVER=0x0400" /D "_WINDOWS" /D "_MBCS" /D "CC_TOOLBAR" /D "CC_STATUS" /D "STRICT"\
 /FR$(INTDIR)/ /Fp$(OUTDIR)/"REFS32.pch" /Fo$(INTDIR)/ /c 
CPP_OBJS=.\Win95_Re/
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG" /d "FOR95" /d "SPLASH" /d "CC_TOOLBAR"
RSC_PROJ=/l 0x809 /fo$(INTDIR)/"REFS.res" /d "NDEBUG" /d "FOR95" /d "SPLASH" /d\
 "CC_TOOLBAR" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"REFS32.bsc" 
BSC32_SBRS= \
	$(INTDIR)/GLOBALS.SBR \
	$(INTDIR)/MYCOLLS.SBR \
	$(INTDIR)/OBJECT.SBR \
	$(INTDIR)/OTREF.SBR \
	$(INTDIR)/OTREFWND.SBR \
	$(INTDIR)/OTSCOLL.SBR \
	$(INTDIR)/RCONFOPT.SBR \
	$(INTDIR)/RCUTPAST.SBR \
	$(INTDIR)/REFABOUT.SBR \
	$(INTDIR)/REFBIBS.SBR \
	$(INTDIR)/REFFONT.SBR \
	$(INTDIR)/REFCHILD.SBR \
	$(INTDIR)/REFFRAME.SBR \
	$(INTDIR)/REFIMP.SBR \
	$(INTDIR)/REFINOPT.SBR \
	$(INTDIR)/REFIO.SBR \
	$(INTDIR)/REFLOPTS.SBR \
	$(INTDIR)/REFNAG.SBR \
	$(INTDIR)/REFPAINT.SBR \
	$(INTDIR)/REFPRN.SBR \
	$(INTDIR)/REFS.SBR \
	$(INTDIR)/RSETLANG.SBR \
	$(INTDIR)/RSRCHOPT.SBR \
	$(INTDIR)/RSRTOPT.SBR \
	$(INTDIR)/JLISTDLG.SBR \
	$(INTDIR)/AUTHDLG.SBR \
	$(INTDIR)/EDITDLG.SBR

$(OUTDIR)/REFS32.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 version.lib ctl3d32.lib oldnames.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib uuid.lib /NOLOGO /STACK:0x10240 /SUBSYSTEM:windows /MAP /MACHINE:IX86
# ADD LINK32 version.lib oldnames.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib comctl32.lib advapi32.lib shell32.lib uuid.lib /NOLOGO /STACK:0x10240 /INCREMENTAL:yes /MAP /MACHINE:IX86 /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=version.lib oldnames.lib winmm.lib kernel32.lib user32.lib\
 gdi32.lib winspool.lib comdlg32.lib comctl32.lib advapi32.lib shell32.lib\
 uuid.lib /NOLOGO /STACK:0x10240 /INCREMENTAL:yes /PDB:$(OUTDIR)/"REFS32.pdb"\
 /MAP:$(INTDIR)/"REFS32.map" /MACHINE:IX86 /OUT:$(OUTDIR)/"REFS32.exe"\
 /SUBSYSTEM:windows,4.0  
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/RIMPEXP32.lib \
	$(INTDIR)/GLOBALS.OBJ \
	$(INTDIR)/MYCOLLS.OBJ \
	$(INTDIR)/OBJECT.OBJ \
	$(INTDIR)/OTREF.OBJ \
	$(INTDIR)/OTREFWND.OBJ \
	$(INTDIR)/OTSCOLL.OBJ \
	$(INTDIR)/RCONFOPT.OBJ \
	$(INTDIR)/RCUTPAST.OBJ \
	$(INTDIR)/REFABOUT.OBJ \
	$(INTDIR)/REFBIBS.OBJ \
	$(INTDIR)/REFFONT.OBJ \
	$(INTDIR)/REFCHILD.OBJ \
	$(INTDIR)/REFFRAME.OBJ \
	$(INTDIR)/REFIMP.OBJ \
	$(INTDIR)/REFINOPT.OBJ \
	$(INTDIR)/REFIO.OBJ \
	$(INTDIR)/REFLOPTS.OBJ \
	$(INTDIR)/REFNAG.OBJ \
	$(INTDIR)/REFPAINT.OBJ \
	$(INTDIR)/REFPRN.OBJ \
	$(INTDIR)/REFS.OBJ \
	$(INTDIR)/RSETLANG.OBJ \
	$(INTDIR)/RSRCHOPT.OBJ \
	$(INTDIR)/RSRTOPT.OBJ \
	$(INTDIR)/REFS.res \
	$(INTDIR)/JLISTDLG.OBJ \
	$(INTDIR)/AUTHDLG.OBJ \
	$(INTDIR)/EDITDLG.OBJ

$(OUTDIR)/REFS32.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Win95 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Win95_De"
# PROP BASE Intermediate_Dir "Win95_De"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Win95_De"
# PROP Intermediate_Dir "Win95_De"
OUTDIR=.\Win95_De
INTDIR=.\Win95_De

ALL : $(OUTDIR)/REFS32.exe $(OUTDIR)/REFS32.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE CPP /nologo /G4 /Zp2 /W2 /Zi /YX"globals.h" /Od /Gf /Gy /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "STRICT" /FR /c
# ADD CPP /nologo /Zp2 /W3 /Zi /YX"globals.h" /Od /Gf /Gy /D "_DEBUG" /D "OLE" /D "FOR95" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "CC_TOOLBAR" /D "CC_STATUS" /D "STRICT" /FR /c
CPP_PROJ=/nologo /Zp2 /W3 /Zi /YX"globals.h" /Od /Gf /Gy /D "_DEBUG" /D "OLE"\
 /D "FOR95" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "CC_TOOLBAR" /D "CC_STATUS"\
 /D "STRICT" /FR$(INTDIR)/ /Fp$(OUTDIR)/"REFS32.pch" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"REFS32.pdb" /c 
CPP_OBJS=.\Win95_De/
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG" /d "FOR95" /d "SPLASH" /d "CC_TOOLBAR"
RSC_PROJ=/l 0x809 /fo$(INTDIR)/"REFS.res" /d "_DEBUG" /d "FOR95" /d "SPLASH" /d\
 "CC_TOOLBAR" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"REFS32.bsc" 
BSC32_SBRS= \
	$(INTDIR)/GLOBALS.SBR \
	$(INTDIR)/MYCOLLS.SBR \
	$(INTDIR)/OBJECT.SBR \
	$(INTDIR)/OTREF.SBR \
	$(INTDIR)/OTREFWND.SBR \
	$(INTDIR)/OTSCOLL.SBR \
	$(INTDIR)/RCONFOPT.SBR \
	$(INTDIR)/RCUTPAST.SBR \
	$(INTDIR)/REFABOUT.SBR \
	$(INTDIR)/REFBIBS.SBR \
	$(INTDIR)/REFFONT.SBR \
	$(INTDIR)/REFCHILD.SBR \
	$(INTDIR)/REFFRAME.SBR \
	$(INTDIR)/REFIMP.SBR \
	$(INTDIR)/REFINOPT.SBR \
	$(INTDIR)/REFIO.SBR \
	$(INTDIR)/REFLOPTS.SBR \
	$(INTDIR)/REFNAG.SBR \
	$(INTDIR)/REFPAINT.SBR \
	$(INTDIR)/REFPRN.SBR \
	$(INTDIR)/REFS.SBR \
	$(INTDIR)/RSETLANG.SBR \
	$(INTDIR)/RSRCHOPT.SBR \
	$(INTDIR)/RSRTOPT.SBR \
	$(INTDIR)/JLISTDLG.SBR \
	$(INTDIR)/AUTHDLG.SBR \
	$(INTDIR)/EDITDLG.SBR

$(OUTDIR)/REFS32.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 version.lib ctl3d32.lib oldnames.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib uuid.lib /NOLOGO /STACK:0x10240 /SUBSYSTEM:windows /DEBUG /MACHINE:IX86
# SUBTRACT BASE LINK32 /PROFILE /INCREMENTAL:no
# ADD LINK32 version.lib oldnames.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib comctl32.lib advapi32.lib shell32.lib uuid.lib ole32.lib /NOLOGO /STACK:0x10240 /DEBUG /MACHINE:IX86 /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=version.lib oldnames.lib winmm.lib kernel32.lib user32.lib\
 gdi32.lib winspool.lib comdlg32.lib comctl32.lib advapi32.lib shell32.lib\
 uuid.lib ole32.lib /NOLOGO /STACK:0x10240 /INCREMENTAL:yes\
 /PDB:$(OUTDIR)/"REFS32.pdb" /DEBUG /MACHINE:IX86 /OUT:$(OUTDIR)/"REFS32.exe"\
 /SUBSYSTEM:windows,4.0  
DEF_FILE=
LINK32_OBJS= \
	.\WIN95_RE\RIMPEXP32.lib \
	$(INTDIR)/GLOBALS.OBJ \
	$(INTDIR)/MYCOLLS.OBJ \
	$(INTDIR)/OBJECT.OBJ \
	$(INTDIR)/OTREF.OBJ \
	$(INTDIR)/OTREFWND.OBJ \
	$(INTDIR)/OTSCOLL.OBJ \
	$(INTDIR)/RCONFOPT.OBJ \
	$(INTDIR)/RCUTPAST.OBJ \
	$(INTDIR)/REFABOUT.OBJ \
	$(INTDIR)/REFBIBS.OBJ \
	$(INTDIR)/REFFONT.OBJ \
	$(INTDIR)/REFCHILD.OBJ \
	$(INTDIR)/REFFRAME.OBJ \
	$(INTDIR)/REFIMP.OBJ \
	$(INTDIR)/REFINOPT.OBJ \
	$(INTDIR)/REFIO.OBJ \
	$(INTDIR)/REFLOPTS.OBJ \
	$(INTDIR)/REFNAG.OBJ \
	$(INTDIR)/REFPAINT.OBJ \
	$(INTDIR)/REFPRN.OBJ \
	$(INTDIR)/REFS.OBJ \
	$(INTDIR)/RSETLANG.OBJ \
	$(INTDIR)/RSRCHOPT.OBJ \
	$(INTDIR)/RSRTOPT.OBJ \
	$(INTDIR)/REFS.res \
	$(INTDIR)/JLISTDLG.OBJ \
	$(INTDIR)/AUTHDLG.OBJ \
	$(INTDIR)/EDITDLG.OBJ

$(OUTDIR)/REFS32.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Unicode_"
# PROP BASE Intermediate_Dir "Unicode_"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Unicode_"
# PROP Intermediate_Dir "Unicode_"
OUTDIR=.\Unicode_
INTDIR=.\Unicode_

ALL : $(OUTDIR)/REFS32.exe $(OUTDIR)/REFS32.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE CPP /nologo /Zp2 /W3 /Zi /YX"globals.h" /Od /Gf /Gy /D "_DEBUG" /D "OLE" /D "FOR95" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "CC_TOOLBAR" /D "CC_STATUS" /D "STRICT" /FR /c
# ADD CPP /nologo /Zp2 /W3 /Zi /YX"globals.h" /Od /Gf /Gy /D "_DEBUG" /D "OLE" /D "FOR95" /D "WIN32" /D "_WINDOWS" /D "UNICODE" /D "CC_TOOLBAR" /D "CC_STATUS" /D "STRICT" /FR /c
CPP_PROJ=/nologo /Zp2 /W3 /Zi /YX"globals.h" /Od /Gf /Gy /D "_DEBUG" /D "OLE"\
 /D "FOR95" /D "WIN32" /D "_WINDOWS" /D "UNICODE" /D "CC_TOOLBAR" /D "CC_STATUS"\
 /D "STRICT" /FR$(INTDIR)/ /Fp$(OUTDIR)/"REFS32.pch" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"REFS32.pdb" /c 
CPP_OBJS=.\Unicode_/
# ADD BASE RSC /l 0x809 /d "_DEBUG" /d "FOR95" /d "SPLASH" /d "CC_TOOLBAR"
# ADD RSC /l 0x809 /d "_DEBUG" /d "FOR95" /d "SPLASH" /d "CC_TOOLBAR"
RSC_PROJ=/l 0x809 /fo$(INTDIR)/"REFS.res" /d "_DEBUG" /d "FOR95" /d "SPLASH" /d\
 "CC_TOOLBAR" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"REFS32.bsc" 
BSC32_SBRS= \
	$(INTDIR)/GLOBALS.SBR \
	$(INTDIR)/MYCOLLS.SBR \
	$(INTDIR)/OBJECT.SBR \
	$(INTDIR)/OTREF.SBR \
	$(INTDIR)/OTREFWND.SBR \
	$(INTDIR)/OTSCOLL.SBR \
	$(INTDIR)/RCONFOPT.SBR \
	$(INTDIR)/RCUTPAST.SBR \
	$(INTDIR)/REFABOUT.SBR \
	$(INTDIR)/REFBIBS.SBR \
	$(INTDIR)/REFFONT.SBR \
	$(INTDIR)/REFCHILD.SBR \
	$(INTDIR)/REFFRAME.SBR \
	$(INTDIR)/REFIMP.SBR \
	$(INTDIR)/REFINOPT.SBR \
	$(INTDIR)/REFIO.SBR \
	$(INTDIR)/REFLOPTS.SBR \
	$(INTDIR)/REFNAG.SBR \
	$(INTDIR)/REFPAINT.SBR \
	$(INTDIR)/REFPRN.SBR \
	$(INTDIR)/REFS.SBR \
	$(INTDIR)/RSETLANG.SBR \
	$(INTDIR)/RSRCHOPT.SBR \
	$(INTDIR)/RSRTOPT.SBR \
	$(INTDIR)/JLISTDLG.SBR \
	$(INTDIR)/AUTHDLG.SBR \
	$(INTDIR)/EDITDLG.SBR

$(OUTDIR)/REFS32.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 version.lib oldnames.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib comctl32.lib advapi32.lib shell32.lib uuid.lib ole32.lib /NOLOGO /STACK:0x10240 /DEBUG /MACHINE:IX86 /SUBSYSTEM:windows,4.0
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 version.lib oldnames.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib comctl32.lib advapi32.lib shell32.lib uuid.lib ole32.lib /NOLOGO /STACK:0x10240 /DEBUG /MACHINE:IX86 /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=version.lib oldnames.lib winmm.lib kernel32.lib user32.lib\
 gdi32.lib winspool.lib comdlg32.lib comctl32.lib advapi32.lib shell32.lib\
 uuid.lib ole32.lib /NOLOGO /STACK:0x10240 /INCREMENTAL:yes\
 /PDB:$(OUTDIR)/"REFS32.pdb" /DEBUG /MACHINE:IX86 /OUT:$(OUTDIR)/"REFS32.exe"\
 /SUBSYSTEM:windows,4.0  
DEF_FILE=
LINK32_OBJS= \
	.\WIN95_RE\RIMPEXP32.lib \
	$(INTDIR)/GLOBALS.OBJ \
	$(INTDIR)/MYCOLLS.OBJ \
	$(INTDIR)/OBJECT.OBJ \
	$(INTDIR)/OTREF.OBJ \
	$(INTDIR)/OTREFWND.OBJ \
	$(INTDIR)/OTSCOLL.OBJ \
	$(INTDIR)/RCONFOPT.OBJ \
	$(INTDIR)/RCUTPAST.OBJ \
	$(INTDIR)/REFABOUT.OBJ \
	$(INTDIR)/REFBIBS.OBJ \
	$(INTDIR)/REFFONT.OBJ \
	$(INTDIR)/REFCHILD.OBJ \
	$(INTDIR)/REFFRAME.OBJ \
	$(INTDIR)/REFIMP.OBJ \
	$(INTDIR)/REFINOPT.OBJ \
	$(INTDIR)/REFIO.OBJ \
	$(INTDIR)/REFLOPTS.OBJ \
	$(INTDIR)/REFNAG.OBJ \
	$(INTDIR)/REFPAINT.OBJ \
	$(INTDIR)/REFPRN.OBJ \
	$(INTDIR)/REFS.OBJ \
	$(INTDIR)/RSETLANG.OBJ \
	$(INTDIR)/RSRCHOPT.OBJ \
	$(INTDIR)/RSRTOPT.OBJ \
	$(INTDIR)/REFS.res \
	$(INTDIR)/JLISTDLG.OBJ \
	$(INTDIR)/AUTHDLG.OBJ \
	$(INTDIR)/EDITDLG.OBJ

$(OUTDIR)/REFS32.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Group "Object/Library Files"

################################################################################
# Begin Source File

SOURCE=.\WIN95_RE\RIMPEXP32.lib
# End Source File
# End Group
################################################################################
# Begin Group "Source Files"

################################################################################
# Begin Source File

SOURCE=.\GLOBALS.CPP
DEP_GLOBA=\
	.\GLOBALS.H\
	.\REFS.H\
	.\OTREF.H\
	.\OTSCOLL.H\
	.\OTREFWND.H\
	.\RIMPEXP.H\
	.\REFFONT.H\
	.\OBJECT.H\
	.\MYCOLLS.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/GLOBALS.OBJ :  $(SOURCE)  $(DEP_GLOBA) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/GLOBALS.OBJ :  $(SOURCE)  $(DEP_GLOBA) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/GLOBALS.OBJ :  $(SOURCE)  $(DEP_GLOBA) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/GLOBALS.OBJ :  $(SOURCE)  $(DEP_GLOBA) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MYCOLLS.CPP
DEP_MYCOL=\
	.\GLOBALS.H\
	.\MYCOLLS.H\
	.\REFS.H\
	.\OTREF.H\
	.\OTSCOLL.H\
	.\OTREFWND.H\
	.\RIMPEXP.H\
	.\REFFONT.H\
	.\OBJECT.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/MYCOLLS.OBJ :  $(SOURCE)  $(DEP_MYCOL) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/MYCOLLS.OBJ :  $(SOURCE)  $(DEP_MYCOL) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/MYCOLLS.OBJ :  $(SOURCE)  $(DEP_MYCOL) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/MYCOLLS.OBJ :  $(SOURCE)  $(DEP_MYCOL) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OBJECT.CPP
DEP_OBJEC=\
	.\OBJECT.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/OBJECT.OBJ :  $(SOURCE)  $(DEP_OBJEC) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/OBJECT.OBJ :  $(SOURCE)  $(DEP_OBJEC) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/OBJECT.OBJ :  $(SOURCE)  $(DEP_OBJEC) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/OBJECT.OBJ :  $(SOURCE)  $(DEP_OBJEC) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OTREF.CPP
DEP_OTREF=\
	.\GLOBALS.H\
	.\REFFONT.H\
	.\REFPRN.H\
	.\RCUTPAST.H\
	.\REFS.H\
	.\OTREF.H\
	.\OTSCOLL.H\
	.\OTREFWND.H\
	.\RIMPEXP.H\
	.\OBJECT.H\
	.\MYCOLLS.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/OTREF.OBJ :  $(SOURCE)  $(DEP_OTREF) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/OTREF.OBJ :  $(SOURCE)  $(DEP_OTREF) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/OTREF.OBJ :  $(SOURCE)  $(DEP_OTREF) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/OTREF.OBJ :  $(SOURCE)  $(DEP_OTREF) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OTREFWND.CPP
DEP_OTREFW=\
	.\GLOBALS.H\
	.\REFFONT.H\
	.\REFIMP.H\
	.\REFS.H\
	.\OTREF.H\
	.\OTSCOLL.H\
	.\OTREFWND.H\
	.\RIMPEXP.H\
	.\OBJECT.H\
	.\MYCOLLS.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/OTREFWND.OBJ :  $(SOURCE)  $(DEP_OTREFW) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/OTREFWND.OBJ :  $(SOURCE)  $(DEP_OTREFW) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/OTREFWND.OBJ :  $(SOURCE)  $(DEP_OTREFW) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/OTREFWND.OBJ :  $(SOURCE)  $(DEP_OTREFW) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OTSCOLL.CPP
DEP_OTSCO=\
	.\GLOBALS.H\
	.\REFS.H\
	.\OTREF.H\
	.\OTSCOLL.H\
	.\OTREFWND.H\
	.\RIMPEXP.H\
	.\REFFONT.H\
	.\OBJECT.H\
	.\MYCOLLS.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/OTSCOLL.OBJ :  $(SOURCE)  $(DEP_OTSCO) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/OTSCOLL.OBJ :  $(SOURCE)  $(DEP_OTSCO) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/OTSCOLL.OBJ :  $(SOURCE)  $(DEP_OTSCO) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/OTSCOLL.OBJ :  $(SOURCE)  $(DEP_OTSCO) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RCONFOPT.CPP
DEP_RCONF=\
	.\GLOBALS.H\
	.\rconfopt.h\
	.\REFS.H\
	.\OTREF.H\
	.\OTSCOLL.H\
	.\OTREFWND.H\
	.\RIMPEXP.H\
	.\REFFONT.H\
	.\OBJECT.H\
	.\MYCOLLS.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/RCONFOPT.OBJ :  $(SOURCE)  $(DEP_RCONF) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/RCONFOPT.OBJ :  $(SOURCE)  $(DEP_RCONF) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/RCONFOPT.OBJ :  $(SOURCE)  $(DEP_RCONF) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/RCONFOPT.OBJ :  $(SOURCE)  $(DEP_RCONF) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RCUTPAST.CPP
DEP_RCUTP=\
	.\GLOBALS.H\
	.\RCUTPAST.H\
	.\REFS.H\
	.\OTREF.H\
	.\OTSCOLL.H\
	.\OTREFWND.H\
	.\RIMPEXP.H\
	.\REFFONT.H\
	.\OBJECT.H\
	.\MYCOLLS.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/RCUTPAST.OBJ :  $(SOURCE)  $(DEP_RCUTP) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/RCUTPAST.OBJ :  $(SOURCE)  $(DEP_RCUTP) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/RCUTPAST.OBJ :  $(SOURCE)  $(DEP_RCUTP) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/RCUTPAST.OBJ :  $(SOURCE)  $(DEP_RCUTP) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\REFABOUT.CPP
DEP_REFAB=\
	.\GLOBALS.H\
	.\refabout.h\
	.\REFS.H\
	.\OTREF.H\
	.\OTSCOLL.H\
	.\OTREFWND.H\
	.\RIMPEXP.H\
	.\REFFONT.H\
	.\OBJECT.H\
	.\MYCOLLS.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/REFABOUT.OBJ :  $(SOURCE)  $(DEP_REFAB) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/REFABOUT.OBJ :  $(SOURCE)  $(DEP_REFAB) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/REFABOUT.OBJ :  $(SOURCE)  $(DEP_REFAB) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/REFABOUT.OBJ :  $(SOURCE)  $(DEP_REFAB) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\REFBIBS.CPP
DEP_REFBI=\
	.\GLOBALS.H\
	.\refbibs.h\
	.\REFFONT.H\
	.\REFS.H\
	.\OTREF.H\
	.\OTSCOLL.H\
	.\OTREFWND.H\
	.\RIMPEXP.H\
	.\OBJECT.H\
	.\MYCOLLS.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/REFBIBS.OBJ :  $(SOURCE)  $(DEP_REFBI) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/REFBIBS.OBJ :  $(SOURCE)  $(DEP_REFBI) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/REFBIBS.OBJ :  $(SOURCE)  $(DEP_REFBI) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/REFBIBS.OBJ :  $(SOURCE)  $(DEP_REFBI) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\REFFONT.CPP
DEP_REFFO=\
	.\GLOBALS.H\
	.\REFFONT.H\
	.\REFS.H\
	.\OTREF.H\
	.\OTSCOLL.H\
	.\OTREFWND.H\
	.\RIMPEXP.H\
	.\OBJECT.H\
	.\MYCOLLS.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/REFFONT.OBJ :  $(SOURCE)  $(DEP_REFFO) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/REFFONT.OBJ :  $(SOURCE)  $(DEP_REFFO) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/REFFONT.OBJ :  $(SOURCE)  $(DEP_REFFO) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/REFFONT.OBJ :  $(SOURCE)  $(DEP_REFFO) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\REFCHILD.CPP
DEP_REFCH=\
	.\GLOBALS.H\
	.\REFCHILD.H\
	.\RCUTPAST.H\
	.\REFFONT.H\
	.\REFS.H\
	.\OTREF.H\
	.\OTSCOLL.H\
	.\OTREFWND.H\
	.\RIMPEXP.H\
	.\OBJECT.H\
	.\MYCOLLS.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/REFCHILD.OBJ :  $(SOURCE)  $(DEP_REFCH) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/REFCHILD.OBJ :  $(SOURCE)  $(DEP_REFCH) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/REFCHILD.OBJ :  $(SOURCE)  $(DEP_REFCH) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/REFCHILD.OBJ :  $(SOURCE)  $(DEP_REFCH) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\REFFRAME.CPP
DEP_REFFR=\
	.\GLOBALS.H\
	.\RCUTPAST.H\
	.\refabout.h\
	.\rconfopt.h\
	.\refbibs.h\
	.\refframe.h\
	.\REFIMP.H\
	.\refio.h\
	.\refinopt.h\
	.\reflopts.h\
	.\refnag.h\
	.\refpaint.h\
	.\REFPRN.H\
	.\rsetlang.h\
	.\rsrtopt.h\
	.\rsrchopt.h\
	.\rtoolbar.h\
	.\status.h\
	.\REFS.H\
	.\OTREF.H\
	.\OTSCOLL.H\
	.\OTREFWND.H\
	.\RIMPEXP.H\
	.\REFFONT.H\
	.\OBJECT.H\
	.\MYCOLLS.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/REFFRAME.OBJ :  $(SOURCE)  $(DEP_REFFR) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/REFFRAME.OBJ :  $(SOURCE)  $(DEP_REFFR) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/REFFRAME.OBJ :  $(SOURCE)  $(DEP_REFFR) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/REFFRAME.OBJ :  $(SOURCE)  $(DEP_REFFR) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\REFIMP.CPP
DEP_REFIM=\
	.\GLOBALS.H\
	.\IMPTFR.H\
	.\refio.h\
	.\REFIMP.H\
	.\REFS.H\
	.\OTREF.H\
	.\OTSCOLL.H\
	.\OTREFWND.H\
	.\RIMPEXP.H\
	.\REFFONT.H\
	.\OBJECT.H\
	.\MYCOLLS.H

!IF  "$(CFG)" == "Win32 FERIC"

# ADD BASE CPP /Ob1
# SUBTRACT BASE CPP /O<none>
# ADD CPP /Ob1
# SUBTRACT CPP /O<none>

$(INTDIR)/REFIMP.OBJ :  $(SOURCE)  $(DEP_REFIM) $(INTDIR)
   $(CPP) /nologo /Zp2 /W2 /YX"globals.h" /Ob1 /D "NDEBUG" /D "FERIC" /D\
 "WIN32" /D "_WINDOWS" /D "_MBCS" /D "CC_TOOLBAR" /D "CC_STATUS" /D "STRICT"\
 /FR$(INTDIR)/ /Fp$(OUTDIR)/"REFS32.pch" /Fo$(INTDIR)/ /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win95 Release"

# ADD BASE CPP /Ob1
# SUBTRACT BASE CPP /O<none>
# ADD CPP /Ob1
# SUBTRACT CPP /O<none>

$(INTDIR)/REFIMP.OBJ :  $(SOURCE)  $(DEP_REFIM) $(INTDIR)
   $(CPP) /nologo /Zp2 /W2 /YX"globals.h" /Ob1 /D "NDEBUG" /D "FOR95" /D\
 "WIN32" /D "_WINDOWS" /D "_MBCS" /D "CC_TOOLBAR" /D "CC_STATUS" /D "STRICT"\
 /FR$(INTDIR)/ /Fp$(OUTDIR)/"REFS32.pch" /Fo$(INTDIR)/ /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/REFIMP.OBJ :  $(SOURCE)  $(DEP_REFIM) $(INTDIR)
   $(CPP) /nologo /Zp2 /W3 /Zi /YX"globals.h" /Od /Gf /Gy /D "_DEBUG" /D "OLE"\
 /D "FOR95" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "CC_TOOLBAR" /D "CC_STATUS"\
 /D "STRICT" /FR$(INTDIR)/ /Fp$(OUTDIR)/"REFS32.pch" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"REFS32.pdb" /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/REFIMP.OBJ :  $(SOURCE)  $(DEP_REFIM) $(INTDIR)
   $(CPP) /nologo /Zp2 /W3 /Zi /YX"globals.h" /Od /Gf /Gy /D "_DEBUG" /D "OLE"\
 /D "FOR95" /D "WIN32" /D "_WINDOWS" /D "UNICODE" /D "CC_TOOLBAR" /D "CC_STATUS"\
 /D "STRICT" /FR$(INTDIR)/ /Fp$(OUTDIR)/"REFS32.pch" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"REFS32.pdb" /c  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\REFINOPT.CPP
DEP_REFIN=\
	.\GLOBALS.H\
	.\refinopt.h\
	.\REFS.H\
	.\OTREF.H\
	.\OTSCOLL.H\
	.\OTREFWND.H\
	.\RIMPEXP.H\
	.\REFFONT.H\
	.\OBJECT.H\
	.\MYCOLLS.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/REFINOPT.OBJ :  $(SOURCE)  $(DEP_REFIN) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/REFINOPT.OBJ :  $(SOURCE)  $(DEP_REFIN) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/REFINOPT.OBJ :  $(SOURCE)  $(DEP_REFIN) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/REFINOPT.OBJ :  $(SOURCE)  $(DEP_REFIN) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\REFIO.CPP
DEP_REFIO=\
	.\GLOBALS.H\
	.\RCUTPAST.H\
	.\refbibs.h\
	.\REFCHILD.H\
	.\REFFONT.H\
	.\refframe.h\
	.\refio.h\
	.\REFS.H\
	.\OTREF.H\
	.\OTSCOLL.H\
	.\OTREFWND.H\
	.\RIMPEXP.H\
	.\OBJECT.H\
	.\MYCOLLS.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/REFIO.OBJ :  $(SOURCE)  $(DEP_REFIO) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/REFIO.OBJ :  $(SOURCE)  $(DEP_REFIO) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/REFIO.OBJ :  $(SOURCE)  $(DEP_REFIO) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/REFIO.OBJ :  $(SOURCE)  $(DEP_REFIO) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\REFLOPTS.CPP
DEP_REFLO=\
	.\GLOBALS.H\
	.\reflopts.h\
	.\REFS.H\
	.\OTREF.H\
	.\OTSCOLL.H\
	.\OTREFWND.H\
	.\RIMPEXP.H\
	.\REFFONT.H\
	.\OBJECT.H\
	.\MYCOLLS.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/REFLOPTS.OBJ :  $(SOURCE)  $(DEP_REFLO) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/REFLOPTS.OBJ :  $(SOURCE)  $(DEP_REFLO) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/REFLOPTS.OBJ :  $(SOURCE)  $(DEP_REFLO) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/REFLOPTS.OBJ :  $(SOURCE)  $(DEP_REFLO) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\REFNAG.CPP
DEP_REFNA=\
	.\GLOBALS.H\
	.\refnag.h\
	.\REFS.H\
	.\OTREF.H\
	.\OTSCOLL.H\
	.\OTREFWND.H\
	.\RIMPEXP.H\
	.\REFFONT.H\
	.\OBJECT.H\
	.\MYCOLLS.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/REFNAG.OBJ :  $(SOURCE)  $(DEP_REFNA) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/REFNAG.OBJ :  $(SOURCE)  $(DEP_REFNA) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/REFNAG.OBJ :  $(SOURCE)  $(DEP_REFNA) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/REFNAG.OBJ :  $(SOURCE)  $(DEP_REFNA) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\REFPAINT.CPP
DEP_REFPA=\
	.\GLOBALS.H\
	.\status.h\
	.\REFS.H\
	.\OTREF.H\
	.\OTSCOLL.H\
	.\OTREFWND.H\
	.\RIMPEXP.H\
	.\REFFONT.H\
	.\OBJECT.H\
	.\MYCOLLS.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/REFPAINT.OBJ :  $(SOURCE)  $(DEP_REFPA) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/REFPAINT.OBJ :  $(SOURCE)  $(DEP_REFPA) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/REFPAINT.OBJ :  $(SOURCE)  $(DEP_REFPA) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/REFPAINT.OBJ :  $(SOURCE)  $(DEP_REFPA) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\REFPRN.CPP
DEP_REFPR=\
	.\GLOBALS.H\
	.\RCUTPAST.H\
	.\REFFONT.H\
	.\REFPRN.H\
	.\REFS.H\
	.\OTREF.H\
	.\OTSCOLL.H\
	.\OTREFWND.H\
	.\RIMPEXP.H\
	.\OBJECT.H\
	.\MYCOLLS.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/REFPRN.OBJ :  $(SOURCE)  $(DEP_REFPR) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/REFPRN.OBJ :  $(SOURCE)  $(DEP_REFPR) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/REFPRN.OBJ :  $(SOURCE)  $(DEP_REFPR) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/REFPRN.OBJ :  $(SOURCE)  $(DEP_REFPR) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\REFS.CPP
DEP_REFS_=\
	.\GLOBALS.H\
	.\refio.h\
	.\refnag.h\
	.\rsetlang.h\
	.\REFS.H\
	.\OTREF.H\
	.\OTSCOLL.H\
	.\OTREFWND.H\
	.\RIMPEXP.H\
	.\REFFONT.H\
	.\OBJECT.H\
	.\MYCOLLS.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/REFS.OBJ :  $(SOURCE)  $(DEP_REFS_) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/REFS.OBJ :  $(SOURCE)  $(DEP_REFS_) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/REFS.OBJ :  $(SOURCE)  $(DEP_REFS_) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/REFS.OBJ :  $(SOURCE)  $(DEP_REFS_) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RSETLANG.CPP
DEP_RSETL=\
	.\GLOBALS.H\
	.\rsetlang.h\
	.\REFS.H\
	.\OTREF.H\
	.\OTSCOLL.H\
	.\OTREFWND.H\
	.\RIMPEXP.H\
	.\REFFONT.H\
	.\OBJECT.H\
	.\MYCOLLS.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/RSETLANG.OBJ :  $(SOURCE)  $(DEP_RSETL) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/RSETLANG.OBJ :  $(SOURCE)  $(DEP_RSETL) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/RSETLANG.OBJ :  $(SOURCE)  $(DEP_RSETL) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/RSETLANG.OBJ :  $(SOURCE)  $(DEP_RSETL) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RSRCHOPT.CPP
DEP_RSRCH=\
	.\GLOBALS.H\
	.\rsrchopt.h\
	.\REFS.H\
	.\OTREF.H\
	.\OTSCOLL.H\
	.\OTREFWND.H\
	.\RIMPEXP.H\
	.\REFFONT.H\
	.\OBJECT.H\
	.\MYCOLLS.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/RSRCHOPT.OBJ :  $(SOURCE)  $(DEP_RSRCH) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/RSRCHOPT.OBJ :  $(SOURCE)  $(DEP_RSRCH) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/RSRCHOPT.OBJ :  $(SOURCE)  $(DEP_RSRCH) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/RSRCHOPT.OBJ :  $(SOURCE)  $(DEP_RSRCH) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RSRTOPT.CPP
DEP_RSRTO=\
	.\GLOBALS.H\
	.\rsrtopt.h\
	.\REFS.H\
	.\OTREF.H\
	.\OTSCOLL.H\
	.\OTREFWND.H\
	.\RIMPEXP.H\
	.\REFFONT.H\
	.\OBJECT.H\
	.\MYCOLLS.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/RSRTOPT.OBJ :  $(SOURCE)  $(DEP_RSRTO) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/RSRTOPT.OBJ :  $(SOURCE)  $(DEP_RSRTO) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/RSRTOPT.OBJ :  $(SOURCE)  $(DEP_RSRTO) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/RSRTOPT.OBJ :  $(SOURCE)  $(DEP_RSRTO) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\REFS.RC
DEP_REFS_R=\
	.\FERICS.BMP\
	.\GONG.BMP\
	.\splash95.bmp\
	.\splashnt.bmp\
	.\splash16.bmp\
	.\toolbar.bmp\
	.\BOOKMASK.BMP\
	.\BOOK.BMP\
	.\ARTMASK.BMP\
	.\ARTICLE.BMP\
	.\REPORT.BMP\
	.\REPMASK.BMP\
	.\REFS.ICO\
	.\REFDATA.ICO\
	.\reffile.ico\
	.\SINGLE.CUR\
	.\MULTI.CUR\
	.\REFS.H\
	.\FERIC.DLG\
	.\SPLASH.DLG

!IF  "$(CFG)" == "Win32 FERIC"

# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809

$(INTDIR)/REFS.res :  $(SOURCE)  $(DEP_REFS_R) $(INTDIR)
   $(RSC) /l 0x809 /fo$(INTDIR)/"REFS.res" /d "NDEBUG" /d "FERIC" /d\
 "CC_TOOLBAR"  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/REFS.res :  $(SOURCE)  $(DEP_REFS_R) $(INTDIR)
   $(RSC) /l 0x809 /fo$(INTDIR)/"REFS.res" /d "NDEBUG" /d "FOR95" /d "SPLASH"\
 /d "CC_TOOLBAR"  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/REFS.res :  $(SOURCE)  $(DEP_REFS_R) $(INTDIR)
   $(RSC) /l 0x809 /fo$(INTDIR)/"REFS.res" /d "_DEBUG" /d "FOR95" /d "SPLASH"\
 /d "CC_TOOLBAR"  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/REFS.res :  $(SOURCE)  $(DEP_REFS_R) $(INTDIR)
   $(RSC) /l 0x809 /fo$(INTDIR)/"REFS.res" /d "_DEBUG" /d "FOR95" /d "SPLASH"\
 /d "CC_TOOLBAR"  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\JLISTDLG.CPP
DEP_JLIST=\
	.\GLOBALS.H\
	.\RIMPEXP.H\
	.\JLISTDLG.H\
	.\REFS.H\
	.\OTREF.H\
	.\OTSCOLL.H\
	.\OTREFWND.H\
	.\OBJECT.H\
	.\MYCOLLS.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/JLISTDLG.OBJ :  $(SOURCE)  $(DEP_JLIST) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/JLISTDLG.OBJ :  $(SOURCE)  $(DEP_JLIST) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/JLISTDLG.OBJ :  $(SOURCE)  $(DEP_JLIST) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/JLISTDLG.OBJ :  $(SOURCE)  $(DEP_JLIST) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\AUTHDLG.CPP
DEP_AUTHD=\
	.\GLOBALS.H\
	.\AUTHDLG.H\
	.\REFS.H\
	.\OTREF.H\
	.\OTSCOLL.H\
	.\OTREFWND.H\
	.\OBJECT.H\
	.\MYCOLLS.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/AUTHDLG.OBJ :  $(SOURCE)  $(DEP_AUTHD) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/AUTHDLG.OBJ :  $(SOURCE)  $(DEP_AUTHD) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/AUTHDLG.OBJ :  $(SOURCE)  $(DEP_AUTHD) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/AUTHDLG.OBJ :  $(SOURCE)  $(DEP_AUTHD) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EDITDLG.CPP
DEP_EDITD=\
	.\GLOBALS.H\
	.\REFFONT.H\
	.\REFPRN.H\
	.\RIMPEXP.H\
	.\RCUTPAST.H\
	.\EDITDLG.H\
	.\JLISTDLG.H\
	.\REFS.H\
	.\OTREF.H\
	.\OTSCOLL.H\
	.\OTREFWND.H\
	.\OBJECT.H\
	.\MYCOLLS.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/EDITDLG.OBJ :  $(SOURCE)  $(DEP_EDITD) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/EDITDLG.OBJ :  $(SOURCE)  $(DEP_EDITD) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/EDITDLG.OBJ :  $(SOURCE)  $(DEP_EDITD) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/EDITDLG.OBJ :  $(SOURCE)  $(DEP_EDITD) $(INTDIR)

!ENDIF 

# End Source File
# End Group
# End Project
################################################################################
