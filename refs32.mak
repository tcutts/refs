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
!MESSAGE NMAKE /f "refs32.mak" CFG="Win95 Debug"
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
# PROP Output_Dir "bin32"
# PROP Intermediate_Dir "Win32_FE"
OUTDIR=.\bin32
INTDIR=.\Win32_FE

ALL : $(OUTDIR)/refs32.exe .\Win32_FE\refs32.map $(OUTDIR)/refs32.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

$(INTDIR) : 
    if not exist $(INTDIR)/nul mkdir $(INTDIR)

# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE CPP /nologo /G4 /Zp2 /W2 /YX"globals.h" /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /c
# ADD CPP /nologo /Zp2 /W2 /YX"globals.h" /O2 /D "NDEBUG" /D "FERIC" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "CC_TOOLBAR" /D "CC_STATUS" /D "STRICT" /FR /c
CPP_PROJ=/nologo /Zp2 /W2 /YX"globals.h" /O2 /D "NDEBUG" /D "FERIC" /D "WIN32"\
 /D "_WINDOWS" /D "_MBCS" /D "CC_TOOLBAR" /D "CC_STATUS" /D "STRICT"\
 /FR$(INTDIR)/ /Fp$(OUTDIR)/"refs32.pch" /Fo$(INTDIR)/ /c 
CPP_OBJS=.\Win32_FE/
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG" /d "FERIC" /d "CC_TOOLBAR"
RSC_PROJ=/l 0x809 /fo$(INTDIR)/"refs.res" /d "NDEBUG" /d "FERIC" /d\
 "CC_TOOLBAR" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"refs32.bsc" 
BSC32_SBRS= \
	$(INTDIR)/globals.sbr \
	$(INTDIR)/mycolls.sbr \
	$(INTDIR)/object.sbr \
	$(INTDIR)/otref.sbr \
	$(INTDIR)/otrefwnd.sbr \
	$(INTDIR)/otscoll.sbr \
	$(INTDIR)/rconfopt.sbr \
	$(INTDIR)/rcutpast.sbr \
	$(INTDIR)/refabout.sbr \
	$(INTDIR)/refbibs.sbr \
	$(INTDIR)/reffont.sbr \
	$(INTDIR)/refchild.sbr \
	$(INTDIR)/refframe.sbr \
	$(INTDIR)/refimp.sbr \
	$(INTDIR)/refinopt.sbr \
	$(INTDIR)/refio.sbr \
	$(INTDIR)/reflopts.sbr \
	$(INTDIR)/refnag.sbr \
	$(INTDIR)/refpaint.sbr \
	$(INTDIR)/refprn.sbr \
	$(INTDIR)/refs.sbr \
	$(INTDIR)/rsetlang.sbr \
	$(INTDIR)/rsrchopt.sbr \
	$(INTDIR)/rsrtopt.sbr \
	$(INTDIR)/jlistdlg.sbr \
	$(INTDIR)/authdlg.sbr \
	$(INTDIR)/editdlg.sbr \
	$(INTDIR)/redit.sbr

$(OUTDIR)/refs32.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 version.lib ctl3d32s.lib oldnames.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib uuid.lib /NOLOGO /STACK:0x10240 /SUBSYSTEM:windows /MAP /MACHINE:IX86
# ADD LINK32 ctl3d32.lib version.lib oldnames.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib comctl32.lib advapi32.lib shell32.lib uuid.lib /NOLOGO /STACK:0x10240 /SUBSYSTEM:windows /INCREMENTAL:yes /MAP /MACHINE:IX86
LINK32_FLAGS=ctl3d32.lib version.lib oldnames.lib winmm.lib kernel32.lib\
 user32.lib gdi32.lib winspool.lib comdlg32.lib comctl32.lib advapi32.lib\
 shell32.lib uuid.lib /NOLOGO /STACK:0x10240 /SUBSYSTEM:windows /INCREMENTAL:yes\
 /PDB:$(OUTDIR)/"refs32.pdb" /MAP:$(INTDIR)/"refs32.map" /MACHINE:IX86\
 /OUT:$(OUTDIR)/"refs32.exe" 
DEF_FILE=
LINK32_OBJS= \
	\DATA\src\re\winrel\regexp32.lib \
	.\bin32\rimpexp32.lib \
	$(INTDIR)/globals.obj \
	$(INTDIR)/mycolls.obj \
	$(INTDIR)/object.obj \
	$(INTDIR)/otref.obj \
	$(INTDIR)/otrefwnd.obj \
	$(INTDIR)/otscoll.obj \
	$(INTDIR)/rconfopt.obj \
	$(INTDIR)/rcutpast.obj \
	$(INTDIR)/refabout.obj \
	$(INTDIR)/refbibs.obj \
	$(INTDIR)/reffont.obj \
	$(INTDIR)/refchild.obj \
	$(INTDIR)/refframe.obj \
	$(INTDIR)/refimp.obj \
	$(INTDIR)/refinopt.obj \
	$(INTDIR)/refio.obj \
	$(INTDIR)/reflopts.obj \
	$(INTDIR)/refnag.obj \
	$(INTDIR)/refpaint.obj \
	$(INTDIR)/refprn.obj \
	$(INTDIR)/refs.obj \
	$(INTDIR)/rsetlang.obj \
	$(INTDIR)/rsrchopt.obj \
	$(INTDIR)/rsrtopt.obj \
	$(INTDIR)/refs.res \
	$(INTDIR)/jlistdlg.obj \
	$(INTDIR)/authdlg.obj \
	$(INTDIR)/editdlg.obj \
	$(INTDIR)/redit.obj

$(OUTDIR)/refs32.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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
# PROP Output_Dir "bin32"
# PROP Intermediate_Dir "Win95_Re"
OUTDIR=.\bin32
INTDIR=.\Win95_Re

ALL : $(OUTDIR)/refs32.exe .\Win95_Re\refs32.map $(OUTDIR)/refs32.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

$(INTDIR) : 
    if not exist $(INTDIR)/nul mkdir $(INTDIR)

# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE CPP /nologo /G4 /Zp2 /W2 /YX"globals.h" /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "STRICT" /FR /c
# ADD CPP /nologo /G4 /Zp2 /W3 /YX"globals.h" /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "STRICT" /FR /c
# SUBTRACT CPP /X
CPP_PROJ=/nologo /G4 /Zp2 /W3 /YX"globals.h" /O2 /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_MBCS" /D "STRICT" /FR$(INTDIR)/ /Fp$(OUTDIR)/"refs32.pch"\
 /Fo$(INTDIR)/ /c 
CPP_OBJS=.\Win95_Re/
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG" /d "FOR95" /d "SPLASH" /d "WIN32"
RSC_PROJ=/l 0x809 /fo$(INTDIR)/"refs.res" /d "NDEBUG" /d "FOR95" /d "SPLASH" /d\
 "WIN32" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"refs32.bsc" 
BSC32_SBRS= \
	$(INTDIR)/globals.sbr \
	$(INTDIR)/mycolls.sbr \
	$(INTDIR)/object.sbr \
	$(INTDIR)/otref.sbr \
	$(INTDIR)/otrefwnd.sbr \
	$(INTDIR)/otscoll.sbr \
	$(INTDIR)/rconfopt.sbr \
	$(INTDIR)/rcutpast.sbr \
	$(INTDIR)/refabout.sbr \
	$(INTDIR)/refbibs.sbr \
	$(INTDIR)/reffont.sbr \
	$(INTDIR)/refchild.sbr \
	$(INTDIR)/refframe.sbr \
	$(INTDIR)/refimp.sbr \
	$(INTDIR)/refinopt.sbr \
	$(INTDIR)/refio.sbr \
	$(INTDIR)/reflopts.sbr \
	$(INTDIR)/refnag.sbr \
	$(INTDIR)/refpaint.sbr \
	$(INTDIR)/refprn.sbr \
	$(INTDIR)/refs.sbr \
	$(INTDIR)/rsetlang.sbr \
	$(INTDIR)/rsrchopt.sbr \
	$(INTDIR)/rsrtopt.sbr \
	$(INTDIR)/jlistdlg.sbr \
	$(INTDIR)/authdlg.sbr \
	$(INTDIR)/editdlg.sbr \
	$(INTDIR)/redit.sbr

$(OUTDIR)/refs32.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 version.lib ctl3d32.lib oldnames.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib uuid.lib /NOLOGO /STACK:0x10240 /SUBSYSTEM:windows /MAP /MACHINE:IX86
# ADD LINK32 version.lib oldnames.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib comctl32.lib advapi32.lib shell32.lib uuid.lib /NOLOGO /STACK:0x10240 /INCREMENTAL:yes /MAP /MACHINE:IX86 /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /VERBOSE /PDB:none
LINK32_FLAGS=version.lib oldnames.lib winmm.lib kernel32.lib user32.lib\
 gdi32.lib winspool.lib comdlg32.lib comctl32.lib advapi32.lib shell32.lib\
 uuid.lib /NOLOGO /STACK:0x10240 /INCREMENTAL:yes /PDB:$(OUTDIR)/"refs32.pdb"\
 /MAP:$(INTDIR)/"refs32.map" /MACHINE:IX86 /OUT:$(OUTDIR)/"refs32.exe"\
 /SUBSYSTEM:windows,4.0  
DEF_FILE=
LINK32_OBJS= \
	\DATA\src\re\winrel\regexp32.lib \
	.\bin32\rimpexp32.lib \
	$(INTDIR)/globals.obj \
	$(INTDIR)/mycolls.obj \
	$(INTDIR)/object.obj \
	$(INTDIR)/otref.obj \
	$(INTDIR)/otrefwnd.obj \
	$(INTDIR)/otscoll.obj \
	$(INTDIR)/rconfopt.obj \
	$(INTDIR)/rcutpast.obj \
	$(INTDIR)/refabout.obj \
	$(INTDIR)/refbibs.obj \
	$(INTDIR)/reffont.obj \
	$(INTDIR)/refchild.obj \
	$(INTDIR)/refframe.obj \
	$(INTDIR)/refimp.obj \
	$(INTDIR)/refinopt.obj \
	$(INTDIR)/refio.obj \
	$(INTDIR)/reflopts.obj \
	$(INTDIR)/refnag.obj \
	$(INTDIR)/refpaint.obj \
	$(INTDIR)/refprn.obj \
	$(INTDIR)/refs.obj \
	$(INTDIR)/rsetlang.obj \
	$(INTDIR)/rsrchopt.obj \
	$(INTDIR)/rsrtopt.obj \
	$(INTDIR)/refs.res \
	$(INTDIR)/jlistdlg.obj \
	$(INTDIR)/authdlg.obj \
	$(INTDIR)/editdlg.obj \
	$(INTDIR)/redit.obj

$(OUTDIR)/refs32.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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
# PROP Output_Dir "bin32"
# PROP Intermediate_Dir "Win95_De"
OUTDIR=.\bin32
INTDIR=.\Win95_De

ALL : $(OUTDIR)/refs32.exe $(OUTDIR)/refs32.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

$(INTDIR) : 
    if not exist $(INTDIR)/nul mkdir $(INTDIR)

# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE CPP /nologo /G4 /Zp2 /W2 /Zi /YX"globals.h" /Od /Gf /Gy /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "STRICT" /FR /c
# ADD CPP /nologo /G4 /Zp2 /W3 /Zi /YX"globals.h" /Od /Gf /Gy /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "STRICT" /FR /c
CPP_PROJ=/nologo /G4 /Zp2 /W3 /Zi /YX"globals.h" /Od /Gf /Gy /D "_DEBUG" /D\
 "WIN32" /D "_WINDOWS" /D "_MBCS" /D "STRICT" /FR$(INTDIR)/\
 /Fp$(OUTDIR)/"refs32.pch" /Fo$(INTDIR)/ /Fd$(OUTDIR)/"refs32.pdb" /c 
CPP_OBJS=.\Win95_De/
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG" /d "WIN32" /d "FOR95" /d "SPLASH"
RSC_PROJ=/l 0x809 /fo$(INTDIR)/"refs.res" /d "_DEBUG" /d "WIN32" /d "FOR95" /d\
 "SPLASH" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"refs32.bsc" 
BSC32_SBRS= \
	$(INTDIR)/globals.sbr \
	$(INTDIR)/mycolls.sbr \
	$(INTDIR)/object.sbr \
	$(INTDIR)/otref.sbr \
	$(INTDIR)/otrefwnd.sbr \
	$(INTDIR)/otscoll.sbr \
	$(INTDIR)/rconfopt.sbr \
	$(INTDIR)/rcutpast.sbr \
	$(INTDIR)/refabout.sbr \
	$(INTDIR)/refbibs.sbr \
	$(INTDIR)/reffont.sbr \
	$(INTDIR)/refchild.sbr \
	$(INTDIR)/refframe.sbr \
	$(INTDIR)/refimp.sbr \
	$(INTDIR)/refinopt.sbr \
	$(INTDIR)/refio.sbr \
	$(INTDIR)/reflopts.sbr \
	$(INTDIR)/refnag.sbr \
	$(INTDIR)/refpaint.sbr \
	$(INTDIR)/refprn.sbr \
	$(INTDIR)/refs.sbr \
	$(INTDIR)/rsetlang.sbr \
	$(INTDIR)/rsrchopt.sbr \
	$(INTDIR)/rsrtopt.sbr \
	$(INTDIR)/jlistdlg.sbr \
	$(INTDIR)/authdlg.sbr \
	$(INTDIR)/editdlg.sbr \
	$(INTDIR)/redit.sbr

$(OUTDIR)/refs32.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 version.lib ctl3d32.lib oldnames.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib uuid.lib /NOLOGO /STACK:0x10240 /SUBSYSTEM:windows /DEBUG /MACHINE:IX86
# SUBTRACT BASE LINK32 /PROFILE /INCREMENTAL:no
# ADD LINK32 version.lib oldnames.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib comctl32.lib advapi32.lib shell32.lib uuid.lib ole32.lib /NOLOGO /STACK:0x10240 /DEBUG /MACHINE:IX86 /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /VERBOSE /PDB:none
LINK32_FLAGS=version.lib oldnames.lib winmm.lib kernel32.lib user32.lib\
 gdi32.lib winspool.lib comdlg32.lib comctl32.lib advapi32.lib shell32.lib\
 uuid.lib ole32.lib /NOLOGO /STACK:0x10240 /INCREMENTAL:yes\
 /PDB:$(OUTDIR)/"refs32.pdb" /DEBUG /MACHINE:IX86 /OUT:$(OUTDIR)/"refs32.exe"\
 /SUBSYSTEM:windows,4.0  
DEF_FILE=
LINK32_OBJS= \
	\DATA\src\re\winrel\regexp32.lib \
	.\bin32\rimpexp32.lib \
	$(INTDIR)/globals.obj \
	$(INTDIR)/mycolls.obj \
	$(INTDIR)/object.obj \
	$(INTDIR)/otref.obj \
	$(INTDIR)/otrefwnd.obj \
	$(INTDIR)/otscoll.obj \
	$(INTDIR)/rconfopt.obj \
	$(INTDIR)/rcutpast.obj \
	$(INTDIR)/refabout.obj \
	$(INTDIR)/refbibs.obj \
	$(INTDIR)/reffont.obj \
	$(INTDIR)/refchild.obj \
	$(INTDIR)/refframe.obj \
	$(INTDIR)/refimp.obj \
	$(INTDIR)/refinopt.obj \
	$(INTDIR)/refio.obj \
	$(INTDIR)/reflopts.obj \
	$(INTDIR)/refnag.obj \
	$(INTDIR)/refpaint.obj \
	$(INTDIR)/refprn.obj \
	$(INTDIR)/refs.obj \
	$(INTDIR)/rsetlang.obj \
	$(INTDIR)/rsrchopt.obj \
	$(INTDIR)/rsrtopt.obj \
	$(INTDIR)/refs.res \
	$(INTDIR)/jlistdlg.obj \
	$(INTDIR)/authdlg.obj \
	$(INTDIR)/editdlg.obj \
	$(INTDIR)/redit.obj

$(OUTDIR)/refs32.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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
# PROP Output_Dir "bin32"
# PROP Intermediate_Dir "Unicode_"
OUTDIR=.\bin32
INTDIR=.\Unicode_

ALL : $(OUTDIR)/refs32.exe $(OUTDIR)/refs32.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

$(INTDIR) : 
    if not exist $(INTDIR)/nul mkdir $(INTDIR)

# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE CPP /nologo /Zp2 /W3 /Zi /YX"globals.h" /Od /Gf /Gy /D "_DEBUG" /D "OLE" /D "FOR95" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "CC_TOOLBAR" /D "CC_STATUS" /D "STRICT" /FR /c
# ADD CPP /nologo /Zp2 /W3 /Zi /YX"globals.h" /Od /Gf /Gy /D "_DEBUG" /D "OLE" /D "FOR95" /D "WIN32" /D "_WINDOWS" /D "UNICODE" /D "CC_TOOLBAR" /D "CC_STATUS" /D "STRICT" /FR /c
CPP_PROJ=/nologo /Zp2 /W3 /Zi /YX"globals.h" /Od /Gf /Gy /D "_DEBUG" /D "OLE"\
 /D "FOR95" /D "WIN32" /D "_WINDOWS" /D "UNICODE" /D "CC_TOOLBAR" /D "CC_STATUS"\
 /D "STRICT" /FR$(INTDIR)/ /Fp$(OUTDIR)/"refs32.pch" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"refs32.pdb" /c 
CPP_OBJS=.\Unicode_/
# ADD BASE RSC /l 0x809 /d "_DEBUG" /d "FOR95" /d "SPLASH" /d "CC_TOOLBAR"
# ADD RSC /l 0x809 /d "_DEBUG" /d "FOR95" /d "SPLASH" /d "CC_TOOLBAR"
RSC_PROJ=/l 0x809 /fo$(INTDIR)/"refs.res" /d "_DEBUG" /d "FOR95" /d "SPLASH" /d\
 "CC_TOOLBAR" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"refs32.bsc" 
BSC32_SBRS= \
	$(INTDIR)/globals.sbr \
	$(INTDIR)/mycolls.sbr \
	$(INTDIR)/object.sbr \
	$(INTDIR)/otref.sbr \
	$(INTDIR)/otrefwnd.sbr \
	$(INTDIR)/otscoll.sbr \
	$(INTDIR)/rconfopt.sbr \
	$(INTDIR)/rcutpast.sbr \
	$(INTDIR)/refabout.sbr \
	$(INTDIR)/refbibs.sbr \
	$(INTDIR)/reffont.sbr \
	$(INTDIR)/refchild.sbr \
	$(INTDIR)/refframe.sbr \
	$(INTDIR)/refimp.sbr \
	$(INTDIR)/refinopt.sbr \
	$(INTDIR)/refio.sbr \
	$(INTDIR)/reflopts.sbr \
	$(INTDIR)/refnag.sbr \
	$(INTDIR)/refpaint.sbr \
	$(INTDIR)/refprn.sbr \
	$(INTDIR)/refs.sbr \
	$(INTDIR)/rsetlang.sbr \
	$(INTDIR)/rsrchopt.sbr \
	$(INTDIR)/rsrtopt.sbr \
	$(INTDIR)/jlistdlg.sbr \
	$(INTDIR)/authdlg.sbr \
	$(INTDIR)/editdlg.sbr \
	$(INTDIR)/redit.sbr

$(OUTDIR)/refs32.bsc : $(OUTDIR)  $(BSC32_SBRS)
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
 /PDB:$(OUTDIR)/"refs32.pdb" /DEBUG /MACHINE:IX86 /OUT:$(OUTDIR)/"refs32.exe"\
 /SUBSYSTEM:windows,4.0  
DEF_FILE=
LINK32_OBJS= \
	\DATA\src\re\winrel\regexp32.lib \
	.\bin32\rimpexp32.lib \
	$(INTDIR)/globals.obj \
	$(INTDIR)/mycolls.obj \
	$(INTDIR)/object.obj \
	$(INTDIR)/otref.obj \
	$(INTDIR)/otrefwnd.obj \
	$(INTDIR)/otscoll.obj \
	$(INTDIR)/rconfopt.obj \
	$(INTDIR)/rcutpast.obj \
	$(INTDIR)/refabout.obj \
	$(INTDIR)/refbibs.obj \
	$(INTDIR)/reffont.obj \
	$(INTDIR)/refchild.obj \
	$(INTDIR)/refframe.obj \
	$(INTDIR)/refimp.obj \
	$(INTDIR)/refinopt.obj \
	$(INTDIR)/refio.obj \
	$(INTDIR)/reflopts.obj \
	$(INTDIR)/refnag.obj \
	$(INTDIR)/refpaint.obj \
	$(INTDIR)/refprn.obj \
	$(INTDIR)/refs.obj \
	$(INTDIR)/rsetlang.obj \
	$(INTDIR)/rsrchopt.obj \
	$(INTDIR)/rsrtopt.obj \
	$(INTDIR)/refs.res \
	$(INTDIR)/jlistdlg.obj \
	$(INTDIR)/authdlg.obj \
	$(INTDIR)/editdlg.obj \
	$(INTDIR)/redit.obj

$(OUTDIR)/refs32.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

SOURCE=\DATA\src\re\winrel\regexp32.lib
# End Source File
################################################################################
# Begin Source File

SOURCE=.\bin32\rimpexp32.lib
# End Source File
# End Group
################################################################################
# Begin Group "Source Files"

################################################################################
# Begin Source File

SOURCE=.\globals.cpp
DEP_GLOBA=\
	.\inc\globals.h\
	.\inc\refimp.h\
	.\inc\config.h\
	.\inc\refs.h\
	.\inc\otref.h\
	.\inc\otscoll.h\
	.\inc\otrefwnd.h\
	.\inc\imptfr.h\
	.\inc\object.h\
	.\inc\mycolls.h\
	F:\MSTOOLS\include\RICHEDIT.H\
	F:\MSTOOLS\include\PSHPACK4.H\
	F:\MSTOOLS\include\POPPACK.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/globals.obj :  $(SOURCE)  $(DEP_GLOBA) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/globals.obj :  $(SOURCE)  $(DEP_GLOBA) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/globals.obj :  $(SOURCE)  $(DEP_GLOBA) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/globals.obj :  $(SOURCE)  $(DEP_GLOBA) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\mycolls.cpp
DEP_MYCOL=\
	.\inc\globals.h\
	.\inc\mycolls.h\
	.\inc\config.h\
	.\inc\refs.h\
	.\inc\otref.h\
	.\inc\otscoll.h\
	.\inc\otrefwnd.h\
	.\inc\object.h\
	F:\MSTOOLS\include\RICHEDIT.H\
	F:\MSTOOLS\include\PSHPACK4.H\
	F:\MSTOOLS\include\POPPACK.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/mycolls.obj :  $(SOURCE)  $(DEP_MYCOL) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/mycolls.obj :  $(SOURCE)  $(DEP_MYCOL) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/mycolls.obj :  $(SOURCE)  $(DEP_MYCOL) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/mycolls.obj :  $(SOURCE)  $(DEP_MYCOL) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\object.cpp
DEP_OBJEC=\
	.\inc\object.h

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/object.obj :  $(SOURCE)  $(DEP_OBJEC) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/object.obj :  $(SOURCE)  $(DEP_OBJEC) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/object.obj :  $(SOURCE)  $(DEP_OBJEC) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/object.obj :  $(SOURCE)  $(DEP_OBJEC) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\otref.cpp
DEP_OTREF=\
	.\inc\globals.h\
	.\inc\refpaint.h\
	.\rimpexp\rimpexp.h\
	.\inc\editdlg.h\
	.\inc\authdlg.h\
	.\inc\config.h\
	.\inc\refs.h\
	.\inc\otref.h\
	.\inc\otscoll.h\
	.\inc\otrefwnd.h\
	.\inc\object.h\
	.\inc\mycolls.h\
	F:\MSTOOLS\include\RICHEDIT.H\
	F:\MSTOOLS\include\PSHPACK4.H\
	F:\MSTOOLS\include\POPPACK.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/otref.obj :  $(SOURCE)  $(DEP_OTREF) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/otref.obj :  $(SOURCE)  $(DEP_OTREF) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/otref.obj :  $(SOURCE)  $(DEP_OTREF) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/otref.obj :  $(SOURCE)  $(DEP_OTREF) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\otrefwnd.cpp
DEP_OTREFW=\
	.\inc\globals.h\
	.\inc\reffont.h\
	.\inc\refimp.h\
	.\inc\refpaint.h\
	.\inc\rtoolbar.h\
	.\inc\refframe.h\
	.\inc\redit.h\
	.\inc\config.h\
	.\inc\refs.h\
	.\inc\otref.h\
	.\inc\otscoll.h\
	.\inc\otrefwnd.h\
	.\inc\imptfr.h\
	.\inc\object.h\
	.\inc\mycolls.h\
	F:\MSTOOLS\include\RICHEDIT.H\
	F:\MSTOOLS\include\PSHPACK4.H\
	F:\MSTOOLS\include\POPPACK.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/otrefwnd.obj :  $(SOURCE)  $(DEP_OTREFW) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/otrefwnd.obj :  $(SOURCE)  $(DEP_OTREFW) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/otrefwnd.obj :  $(SOURCE)  $(DEP_OTREFW) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/otrefwnd.obj :  $(SOURCE)  $(DEP_OTREFW) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\otscoll.cpp
DEP_OTSCO=\
	.\inc\globals.h\
	..\src\re\regexp.h\
	.\inc\config.h\
	.\inc\refs.h\
	.\inc\otref.h\
	.\inc\otscoll.h\
	.\inc\otrefwnd.h\
	.\inc\object.h\
	.\inc\mycolls.h\
	F:\MSTOOLS\include\RICHEDIT.H\
	F:\MSTOOLS\include\PSHPACK4.H\
	F:\MSTOOLS\include\POPPACK.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/otscoll.obj :  $(SOURCE)  $(DEP_OTSCO) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/otscoll.obj :  $(SOURCE)  $(DEP_OTSCO) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/otscoll.obj :  $(SOURCE)  $(DEP_OTSCO) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/otscoll.obj :  $(SOURCE)  $(DEP_OTSCO) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\rconfopt.cpp
DEP_RCONF=\
	.\inc\globals.h\
	.\inc\rconfopt.h\
	.\inc\config.h\
	.\inc\refs.h\
	.\inc\otref.h\
	.\inc\otscoll.h\
	.\inc\otrefwnd.h\
	.\inc\object.h\
	.\inc\mycolls.h\
	F:\MSTOOLS\include\RICHEDIT.H\
	F:\MSTOOLS\include\PSHPACK4.H\
	F:\MSTOOLS\include\POPPACK.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/rconfopt.obj :  $(SOURCE)  $(DEP_RCONF) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/rconfopt.obj :  $(SOURCE)  $(DEP_RCONF) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/rconfopt.obj :  $(SOURCE)  $(DEP_RCONF) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/rconfopt.obj :  $(SOURCE)  $(DEP_RCONF) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\rcutpast.cpp
DEP_RCUTP=\
	.\inc\globals.h\
	.\inc\rcutpast.h\
	.\inc\refpaint.h\
	.\rimpexp\rimpexp.h\
	.\inc\config.h\
	.\inc\refs.h\
	.\inc\otref.h\
	.\inc\otscoll.h\
	.\inc\otrefwnd.h\
	.\inc\object.h\
	.\inc\mycolls.h\
	F:\MSTOOLS\include\RICHEDIT.H\
	F:\MSTOOLS\include\PSHPACK4.H\
	F:\MSTOOLS\include\POPPACK.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/rcutpast.obj :  $(SOURCE)  $(DEP_RCUTP) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/rcutpast.obj :  $(SOURCE)  $(DEP_RCUTP) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/rcutpast.obj :  $(SOURCE)  $(DEP_RCUTP) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/rcutpast.obj :  $(SOURCE)  $(DEP_RCUTP) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\refabout.cpp
DEP_REFAB=\
	.\inc\globals.h\
	.\inc\refabout.h\
	.\inc\config.h\
	.\inc\refs.h\
	.\inc\otref.h\
	.\inc\otscoll.h\
	.\inc\otrefwnd.h\
	.\inc\object.h\
	.\inc\mycolls.h\
	F:\MSTOOLS\include\RICHEDIT.H\
	F:\MSTOOLS\include\PSHPACK4.H\
	F:\MSTOOLS\include\POPPACK.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/refabout.obj :  $(SOURCE)  $(DEP_REFAB) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/refabout.obj :  $(SOURCE)  $(DEP_REFAB) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/refabout.obj :  $(SOURCE)  $(DEP_REFAB) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/refabout.obj :  $(SOURCE)  $(DEP_REFAB) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\refbibs.cpp
DEP_REFBI=\
	.\inc\globals.h\
	.\inc\refbibs.h\
	.\inc\reffont.h\
	.\rimpexp\rimpexp.h\
	.\inc\config.h\
	.\inc\refs.h\
	.\inc\otref.h\
	.\inc\otscoll.h\
	.\inc\otrefwnd.h\
	.\inc\object.h\
	.\inc\mycolls.h\
	F:\MSTOOLS\include\RICHEDIT.H\
	F:\MSTOOLS\include\PSHPACK4.H\
	F:\MSTOOLS\include\POPPACK.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/refbibs.obj :  $(SOURCE)  $(DEP_REFBI) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/refbibs.obj :  $(SOURCE)  $(DEP_REFBI) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/refbibs.obj :  $(SOURCE)  $(DEP_REFBI) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/refbibs.obj :  $(SOURCE)  $(DEP_REFBI) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\reffont.cpp
DEP_REFFO=\
	.\inc\globals.h\
	.\inc\reffont.h\
	.\rimpexp\rimpexp.h\
	.\inc\config.h\
	.\inc\refs.h\
	.\inc\otref.h\
	.\inc\otscoll.h\
	.\inc\otrefwnd.h\
	.\inc\object.h\
	.\inc\mycolls.h\
	F:\MSTOOLS\include\RICHEDIT.H\
	F:\MSTOOLS\include\PSHPACK4.H\
	F:\MSTOOLS\include\POPPACK.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/reffont.obj :  $(SOURCE)  $(DEP_REFFO) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/reffont.obj :  $(SOURCE)  $(DEP_REFFO) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/reffont.obj :  $(SOURCE)  $(DEP_REFFO) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/reffont.obj :  $(SOURCE)  $(DEP_REFFO) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\refchild.cpp
DEP_REFCH=\
	.\inc\globals.h\
	.\inc\refchild.h\
	.\inc\rcutpast.h\
	.\inc\reffont.h\
	.\inc\rtoolbar.h\
	.\inc\refframe.h\
	.\inc\refpaint.h\
	.\inc\editdlg.h\
	.\inc\authdlg.h\
	.\inc\redit.h\
	.\inc\config.h\
	.\inc\refs.h\
	.\inc\otref.h\
	.\inc\otscoll.h\
	.\inc\otrefwnd.h\
	.\inc\object.h\
	.\inc\mycolls.h\
	F:\MSTOOLS\include\RICHEDIT.H\
	F:\MSTOOLS\include\PSHPACK4.H\
	F:\MSTOOLS\include\POPPACK.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/refchild.obj :  $(SOURCE)  $(DEP_REFCH) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/refchild.obj :  $(SOURCE)  $(DEP_REFCH) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/refchild.obj :  $(SOURCE)  $(DEP_REFCH) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/refchild.obj :  $(SOURCE)  $(DEP_REFCH) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\refframe.cpp
DEP_REFFR=\
	.\inc\globals.h\
	.\inc\rcutpast.h\
	.\inc\refabout.h\
	.\inc\rconfopt.h\
	.\inc\refbibs.h\
	.\inc\refframe.h\
	.\inc\refimp.h\
	.\inc\refio.h\
	.\inc\refinopt.h\
	.\inc\reflopts.h\
	.\inc\refnag.h\
	.\inc\refpaint.h\
	.\inc\refprn.h\
	.\inc\rsetlang.h\
	.\inc\rsrtopt.h\
	.\inc\rsrchopt.h\
	.\inc\reffont.h\
	.\inc\editdlg.h\
	.\inc\authdlg.h\
	.\inc\redit.h\
	.\inc\status.h\
	.\inc\rtoolbar.h\
	.\inc\config.h\
	.\inc\refs.h\
	.\inc\otref.h\
	.\inc\otscoll.h\
	.\inc\otrefwnd.h\
	.\inc\imptfr.h\
	.\inc\object.h\
	.\inc\mycolls.h\
	F:\MSTOOLS\include\RICHEDIT.H\
	F:\MSTOOLS\include\PSHPACK4.H\
	F:\MSTOOLS\include\POPPACK.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/refframe.obj :  $(SOURCE)  $(DEP_REFFR) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/refframe.obj :  $(SOURCE)  $(DEP_REFFR) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/refframe.obj :  $(SOURCE)  $(DEP_REFFR) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/refframe.obj :  $(SOURCE)  $(DEP_REFFR) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\refimp.cpp
DEP_REFIM=\
	.\inc\globals.h\
	.\inc\refio.h\
	.\inc\refimp.h\
	.\rimpexp\rimpexp.h\
	.\inc\redit.h\
	.\inc\config.h\
	.\inc\refs.h\
	.\inc\otref.h\
	.\inc\otscoll.h\
	.\inc\otrefwnd.h\
	.\inc\imptfr.h\
	.\inc\object.h\
	.\inc\mycolls.h\
	F:\MSTOOLS\include\RICHEDIT.H\
	F:\MSTOOLS\include\PSHPACK4.H\
	F:\MSTOOLS\include\POPPACK.H

!IF  "$(CFG)" == "Win32 FERIC"

# ADD BASE CPP /Ob1
# SUBTRACT BASE CPP /O<none>
# ADD CPP /Ob1
# SUBTRACT CPP /O<none>

$(INTDIR)/refimp.obj :  $(SOURCE)  $(DEP_REFIM) $(INTDIR)
   $(CPP) /nologo /Zp2 /W2 /YX"globals.h" /Ob1 /D "NDEBUG" /D "FERIC" /D\
 "WIN32" /D "_WINDOWS" /D "_MBCS" /D "CC_TOOLBAR" /D "CC_STATUS" /D "STRICT"\
 /FR$(INTDIR)/ /Fp$(OUTDIR)/"refs32.pch" /Fo$(INTDIR)/ /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win95 Release"

# ADD BASE CPP /Ob1
# SUBTRACT BASE CPP /O<none>
# ADD CPP /Ob1
# SUBTRACT CPP /O<none>

$(INTDIR)/refimp.obj :  $(SOURCE)  $(DEP_REFIM) $(INTDIR)
   $(CPP) /nologo /G4 /Zp2 /W3 /YX"globals.h" /Ob1 /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_MBCS" /D "STRICT" /FR$(INTDIR)/ /Fp$(OUTDIR)/"refs32.pch"\
 /Fo$(INTDIR)/ /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/refimp.obj :  $(SOURCE)  $(DEP_REFIM) $(INTDIR)
   $(CPP) /nologo /G4 /Zp2 /W3 /Zi /YX"globals.h" /Od /Gf /Gy /D "_DEBUG" /D\
 "WIN32" /D "_WINDOWS" /D "_MBCS" /D "STRICT" /FR$(INTDIR)/\
 /Fp$(OUTDIR)/"refs32.pch" /Fo$(INTDIR)/ /Fd$(OUTDIR)/"refs32.pdb" /c  $(SOURCE)\
 

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/refimp.obj :  $(SOURCE)  $(DEP_REFIM) $(INTDIR)
   $(CPP) /nologo /Zp2 /W3 /Zi /YX"globals.h" /Od /Gf /Gy /D "_DEBUG" /D "OLE"\
 /D "FOR95" /D "WIN32" /D "_WINDOWS" /D "UNICODE" /D "CC_TOOLBAR" /D "CC_STATUS"\
 /D "STRICT" /FR$(INTDIR)/ /Fp$(OUTDIR)/"refs32.pch" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"refs32.pdb" /c  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\refinopt.cpp
DEP_REFIN=\
	.\inc\globals.h\
	.\inc\refinopt.h\
	.\inc\config.h\
	.\inc\refs.h\
	.\inc\otref.h\
	.\inc\otscoll.h\
	.\inc\otrefwnd.h\
	.\inc\object.h\
	.\inc\mycolls.h\
	F:\MSTOOLS\include\RICHEDIT.H\
	F:\MSTOOLS\include\PSHPACK4.H\
	F:\MSTOOLS\include\POPPACK.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/refinopt.obj :  $(SOURCE)  $(DEP_REFIN) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/refinopt.obj :  $(SOURCE)  $(DEP_REFIN) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/refinopt.obj :  $(SOURCE)  $(DEP_REFIN) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/refinopt.obj :  $(SOURCE)  $(DEP_REFIN) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\refio.cpp
DEP_REFIO=\
	.\inc\globals.h\
	.\inc\rcutpast.h\
	.\inc\refbibs.h\
	.\inc\refchild.h\
	.\inc\reffont.h\
	.\inc\refframe.h\
	.\inc\refio.h\
	.\rimpexp\rimpexp.h\
	.\inc\editdlg.h\
	.\inc\config.h\
	.\inc\refs.h\
	.\inc\otref.h\
	.\inc\otscoll.h\
	.\inc\otrefwnd.h\
	.\inc\object.h\
	.\inc\mycolls.h\
	F:\MSTOOLS\include\RICHEDIT.H\
	F:\MSTOOLS\include\PSHPACK4.H\
	F:\MSTOOLS\include\POPPACK.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/refio.obj :  $(SOURCE)  $(DEP_REFIO) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/refio.obj :  $(SOURCE)  $(DEP_REFIO) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/refio.obj :  $(SOURCE)  $(DEP_REFIO) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/refio.obj :  $(SOURCE)  $(DEP_REFIO) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\reflopts.cpp
DEP_REFLO=\
	.\inc\globals.h\
	.\inc\reflopts.h\
	.\inc\config.h\
	.\inc\refs.h\
	.\inc\otref.h\
	.\inc\otscoll.h\
	.\inc\otrefwnd.h\
	.\inc\object.h\
	.\inc\mycolls.h\
	F:\MSTOOLS\include\RICHEDIT.H\
	F:\MSTOOLS\include\PSHPACK4.H\
	F:\MSTOOLS\include\POPPACK.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/reflopts.obj :  $(SOURCE)  $(DEP_REFLO) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/reflopts.obj :  $(SOURCE)  $(DEP_REFLO) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/reflopts.obj :  $(SOURCE)  $(DEP_REFLO) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/reflopts.obj :  $(SOURCE)  $(DEP_REFLO) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\refnag.cpp
DEP_REFNA=\
	.\inc\globals.h\
	.\inc\refnag.h\
	.\rimpexp\rimpexp.h\
	.\inc\rsetlang.h\
	.\inc\config.h\
	.\inc\refs.h\
	.\inc\otref.h\
	.\inc\otscoll.h\
	.\inc\otrefwnd.h\
	.\inc\object.h\
	.\inc\mycolls.h\
	F:\MSTOOLS\include\RICHEDIT.H\
	F:\MSTOOLS\include\PSHPACK4.H\
	F:\MSTOOLS\include\POPPACK.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/refnag.obj :  $(SOURCE)  $(DEP_REFNA) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/refnag.obj :  $(SOURCE)  $(DEP_REFNA) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/refnag.obj :  $(SOURCE)  $(DEP_REFNA) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/refnag.obj :  $(SOURCE)  $(DEP_REFNA) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\refpaint.cpp
DEP_REFPA=\
	.\inc\globals.h\
	.\inc\status.h\
	.\inc\config.h\
	.\inc\refs.h\
	.\inc\otref.h\
	.\inc\otscoll.h\
	.\inc\otrefwnd.h\
	.\inc\object.h\
	.\inc\mycolls.h\
	F:\MSTOOLS\include\RICHEDIT.H\
	F:\MSTOOLS\include\PSHPACK4.H\
	F:\MSTOOLS\include\POPPACK.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/refpaint.obj :  $(SOURCE)  $(DEP_REFPA) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/refpaint.obj :  $(SOURCE)  $(DEP_REFPA) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/refpaint.obj :  $(SOURCE)  $(DEP_REFPA) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/refpaint.obj :  $(SOURCE)  $(DEP_REFPA) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\refprn.cpp
DEP_REFPR=\
	.\inc\globals.h\
	.\inc\rcutpast.h\
	.\inc\reffont.h\
	.\inc\refprn.h\
	.\inc\redit.h\
	.\inc\config.h\
	.\inc\refs.h\
	.\inc\otref.h\
	.\inc\otscoll.h\
	.\inc\otrefwnd.h\
	.\inc\object.h\
	.\inc\mycolls.h\
	F:\MSTOOLS\include\RICHEDIT.H\
	F:\MSTOOLS\include\PSHPACK4.H\
	F:\MSTOOLS\include\POPPACK.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/refprn.obj :  $(SOURCE)  $(DEP_REFPR) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/refprn.obj :  $(SOURCE)  $(DEP_REFPR) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/refprn.obj :  $(SOURCE)  $(DEP_REFPR) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/refprn.obj :  $(SOURCE)  $(DEP_REFPR) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\refs.cpp
DEP_REFS_=\
	.\inc\globals.h\
	.\inc\refabout.h\
	.\rimpexp\rimpexp.h\
	.\inc\refio.h\
	.\inc\editdlg.h\
	.\inc\refnag.h\
	.\inc\rsetlang.h\
	.\inc\config.h\
	.\inc\refs.h\
	.\inc\otref.h\
	.\inc\otscoll.h\
	.\inc\otrefwnd.h\
	.\inc\object.h\
	.\inc\mycolls.h\
	F:\MSTOOLS\include\RICHEDIT.H\
	F:\MSTOOLS\include\PSHPACK4.H\
	F:\MSTOOLS\include\POPPACK.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/refs.obj :  $(SOURCE)  $(DEP_REFS_) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/refs.obj :  $(SOURCE)  $(DEP_REFS_) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/refs.obj :  $(SOURCE)  $(DEP_REFS_) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/refs.obj :  $(SOURCE)  $(DEP_REFS_) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\rsetlang.cpp
DEP_RSETL=\
	.\inc\globals.h\
	.\inc\rsetlang.h\
	.\rimpexp\rimpexp.h\
	.\inc\editdlg.h\
	.\inc\config.h\
	.\inc\refs.h\
	.\inc\otref.h\
	.\inc\otscoll.h\
	.\inc\otrefwnd.h\
	.\inc\object.h\
	.\inc\mycolls.h\
	F:\MSTOOLS\include\RICHEDIT.H\
	F:\MSTOOLS\include\PSHPACK4.H\
	F:\MSTOOLS\include\POPPACK.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/rsetlang.obj :  $(SOURCE)  $(DEP_RSETL) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/rsetlang.obj :  $(SOURCE)  $(DEP_RSETL) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/rsetlang.obj :  $(SOURCE)  $(DEP_RSETL) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/rsetlang.obj :  $(SOURCE)  $(DEP_RSETL) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\rsrchopt.cpp
DEP_RSRCH=\
	.\inc\globals.h\
	.\inc\rsrchopt.h\
	.\inc\config.h\
	.\inc\refs.h\
	.\inc\otref.h\
	.\inc\otscoll.h\
	.\inc\otrefwnd.h\
	.\inc\object.h\
	.\inc\mycolls.h\
	F:\MSTOOLS\include\RICHEDIT.H\
	F:\MSTOOLS\include\PSHPACK4.H\
	F:\MSTOOLS\include\POPPACK.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/rsrchopt.obj :  $(SOURCE)  $(DEP_RSRCH) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/rsrchopt.obj :  $(SOURCE)  $(DEP_RSRCH) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/rsrchopt.obj :  $(SOURCE)  $(DEP_RSRCH) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/rsrchopt.obj :  $(SOURCE)  $(DEP_RSRCH) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\rsrtopt.cpp
DEP_RSRTO=\
	.\inc\globals.h\
	.\inc\rsrtopt.h\
	.\inc\config.h\
	.\inc\refs.h\
	.\inc\otref.h\
	.\inc\otscoll.h\
	.\inc\otrefwnd.h\
	.\inc\object.h\
	.\inc\mycolls.h\
	F:\MSTOOLS\include\RICHEDIT.H\
	F:\MSTOOLS\include\PSHPACK4.H\
	F:\MSTOOLS\include\POPPACK.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/rsrtopt.obj :  $(SOURCE)  $(DEP_RSRTO) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/rsrtopt.obj :  $(SOURCE)  $(DEP_RSRTO) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/rsrtopt.obj :  $(SOURCE)  $(DEP_RSRTO) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/rsrtopt.obj :  $(SOURCE)  $(DEP_RSRTO) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\refs.rc
DEP_REFS_R=\
	.\FERICS.BMP\
	.\GONG.BMP\
	.\splash32.bmp\
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
	.\inc\config.h\
	.\inc\refs.h\
	.\splash.dlg

!IF  "$(CFG)" == "Win32 FERIC"

# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809

$(INTDIR)/refs.res :  $(SOURCE)  $(DEP_REFS_R) $(INTDIR)
   $(RSC) /l 0x809 /fo$(INTDIR)/"refs.res" /d "NDEBUG" /d "FERIC" /d\
 "CC_TOOLBAR"  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/refs.res :  $(SOURCE)  $(DEP_REFS_R) $(INTDIR)
   $(RSC) /l 0x809 /fo$(INTDIR)/"refs.res" /d "NDEBUG" /d "FOR95" /d "SPLASH"\
 /d "WIN32"  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/refs.res :  $(SOURCE)  $(DEP_REFS_R) $(INTDIR)
   $(RSC) /l 0x809 /fo$(INTDIR)/"refs.res" /d "_DEBUG" /d "WIN32" /d "FOR95" /d\
 "SPLASH"  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/refs.res :  $(SOURCE)  $(DEP_REFS_R) $(INTDIR)
   $(RSC) /l 0x809 /fo$(INTDIR)/"refs.res" /d "_DEBUG" /d "FOR95" /d "SPLASH"\
 /d "CC_TOOLBAR"  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\jlistdlg.cpp
DEP_JLIST=\
	.\inc\globals.h\
	.\rimpexp\rimpexp.h\
	.\inc\jlistdlg.h\
	.\inc\config.h\
	.\inc\refs.h\
	.\inc\otref.h\
	.\inc\otscoll.h\
	.\inc\otrefwnd.h\
	.\inc\object.h\
	.\inc\mycolls.h\
	F:\MSTOOLS\include\RICHEDIT.H\
	F:\MSTOOLS\include\PSHPACK4.H\
	F:\MSTOOLS\include\POPPACK.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/jlistdlg.obj :  $(SOURCE)  $(DEP_JLIST) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/jlistdlg.obj :  $(SOURCE)  $(DEP_JLIST) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/jlistdlg.obj :  $(SOURCE)  $(DEP_JLIST) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/jlistdlg.obj :  $(SOURCE)  $(DEP_JLIST) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\authdlg.cpp
DEP_AUTHD=\
	.\inc\globals.h\
	.\inc\authdlg.h\
	.\inc\config.h\
	.\inc\refs.h\
	.\inc\otref.h\
	.\inc\otscoll.h\
	.\inc\otrefwnd.h\
	.\inc\object.h\
	.\inc\mycolls.h\
	F:\MSTOOLS\include\RICHEDIT.H\
	F:\MSTOOLS\include\PSHPACK4.H\
	F:\MSTOOLS\include\POPPACK.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/authdlg.obj :  $(SOURCE)  $(DEP_AUTHD) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/authdlg.obj :  $(SOURCE)  $(DEP_AUTHD) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/authdlg.obj :  $(SOURCE)  $(DEP_AUTHD) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/authdlg.obj :  $(SOURCE)  $(DEP_AUTHD) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\editdlg.cpp
DEP_EDITD=\
	.\inc\globals.h\
	.\inc\reffont.h\
	.\inc\refprn.h\
	.\rimpexp\rimpexp.h\
	.\inc\rcutpast.h\
	.\inc\editdlg.h\
	.\inc\jlistdlg.h\
	.\inc\config.h\
	.\inc\refs.h\
	.\inc\otref.h\
	.\inc\otscoll.h\
	.\inc\otrefwnd.h\
	.\inc\object.h\
	.\inc\mycolls.h\
	F:\MSTOOLS\include\RICHEDIT.H\
	F:\MSTOOLS\include\PSHPACK4.H\
	F:\MSTOOLS\include\POPPACK.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/editdlg.obj :  $(SOURCE)  $(DEP_EDITD) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/editdlg.obj :  $(SOURCE)  $(DEP_EDITD) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/editdlg.obj :  $(SOURCE)  $(DEP_EDITD) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/editdlg.obj :  $(SOURCE)  $(DEP_EDITD) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\redit.cpp
DEP_REDIT=\
	.\inc\globals.h\
	.\inc\redit.h\
	.\inc\config.h\
	.\inc\refs.h\
	.\inc\otref.h\
	.\inc\otscoll.h\
	.\inc\otrefwnd.h\
	.\inc\object.h\
	.\inc\mycolls.h\
	F:\MSTOOLS\include\RICHEDIT.H\
	F:\MSTOOLS\include\PSHPACK4.H\
	F:\MSTOOLS\include\POPPACK.H

!IF  "$(CFG)" == "Win32 FERIC"

$(INTDIR)/redit.obj :  $(SOURCE)  $(DEP_REDIT) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Release"

$(INTDIR)/redit.obj :  $(SOURCE)  $(DEP_REDIT) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win95 Debug"

$(INTDIR)/redit.obj :  $(SOURCE)  $(DEP_REDIT) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/redit.obj :  $(SOURCE)  $(DEP_REDIT) $(INTDIR)

!ENDIF 

# End Source File
# End Group
# End Project
################################################################################
