# Microsoft Visual C++ Generated NMAKE File, Format Version 2.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Win32 Release" && "$(CFG)" != "Win32 Debug" && "$(CFG)" !=\
 "Unicode Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "rimpexp32.mak" CFG="Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

################################################################################
# Begin Project
# PROP Target_Last_Scanned "Win32 Debug"
MTL=MkTypLib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "\data\refs\bin32"
# PROP Intermediate_Dir "Win95_Re"
OUTDIR=\data\refs\bin32
INTDIR=.\Win95_Re

ALL : $(OUTDIR)/rimpexp.dll $(OUTDIR)/rimpexp32.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

$(INTDIR) : 
    if not exist $(INTDIR)/nul mkdir $(INTDIR)

# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE CPP /nologo /MT /W2 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_MBCS" /FR /c
# ADD CPP /nologo /G4 /Zp2 /MT /W3 /YX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "STRICT" /FR /c
CPP_PROJ=/nologo /G4 /Zp2 /MT /W3 /YX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_MBCS" /D "STRICT" /FR$(INTDIR)/ /Fp$(OUTDIR)/"rimpexp32.pch" /Fo$(INTDIR)/\
 /c 
CPP_OBJS=.\Win95_Re/
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
RSC_PROJ=/l 0x809 /fo$(INTDIR)/"rimpexp.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"rimpexp32.bsc" 
BSC32_SBRS= \
	$(INTDIR)/fimpexp.sbr

$(OUTDIR)/rimpexp32.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 oldnames.lib ldllcew.lib winmm.lib /NOLOGO /SUBSYSTEM:windows /DLL /MAP:"FULL" /MACHINE:IX86
# ADD LINK32 oldnames.lib winmm.lib kernel32.lib user32.lib uuid.lib advapi32.lib /NOLOGO /SUBSYSTEM:windows /DLL /INCREMENTAL:yes /MACHINE:IX86 /OUT:"\data\refs\bin32\rimpexp.dll"
# SUBTRACT LINK32 /MAP
LINK32_FLAGS=oldnames.lib winmm.lib kernel32.lib user32.lib uuid.lib\
 advapi32.lib /NOLOGO /SUBSYSTEM:windows /DLL /INCREMENTAL:yes\
 /PDB:$(OUTDIR)/"rimpexp32.pdb" /MACHINE:IX86 /DEF:".\fimpexp.def"\
 /OUT:"\data\refs\bin32\rimpexp.dll" /IMPLIB:$(OUTDIR)/"rimpexp32.lib" 
DEF_FILE=.\fimpexp.def
LINK32_OBJS= \
	$(INTDIR)/fimpexp.obj \
	$(INTDIR)/rimpexp.res

$(OUTDIR)/rimpexp.dll : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "\data\refs\bin32"
# PROP Intermediate_Dir "Win95_De"
OUTDIR=\data\refs\bin32
INTDIR=.\Win95_De

ALL : $(OUTDIR)/rimpexp.dll $(OUTDIR)/rimpexp32.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

$(INTDIR) : 
    if not exist $(INTDIR)/nul mkdir $(INTDIR)

# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE CPP /nologo /MT /W2 /GX /Zi /YX /O2 /Ob2 /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_MBCS" /FR /c
# ADD CPP /nologo /G4 /Zp2 /MT /W3 /GX /Zi /YX /Od /Gf /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "STRICT" /FR /c
CPP_PROJ=/nologo /G4 /Zp2 /MT /W3 /GX /Zi /YX /Od /Gf /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_MBCS" /D "STRICT" /FR$(INTDIR)/ /Fp$(OUTDIR)/"rimpexp32.pch"\
 /Fo$(INTDIR)/ /Fd$(OUTDIR)/"rimpexp32.pdb" /c 
CPP_OBJS=.\Win95_De/
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
RSC_PROJ=/l 0x809 /fo$(INTDIR)/"rimpexp.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"rimpexp32.bsc" 
BSC32_SBRS= \
	$(INTDIR)/fimpexp.sbr

$(OUTDIR)/rimpexp32.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 oldnames.lib ldllcew.lib winmm.lib /NOLOGO /SUBSYSTEM:windows /DLL /MAP:"FULL" /DEBUG /MACHINE:IX86
# ADD LINK32 oldnames.lib winmm.lib kernel32.lib user32.lib uuid.lib advapi32.lib /NOLOGO /SUBSYSTEM:windows /DLL /MAP:"FULL" /DEBUG /MACHINE:IX86 /OUT:"\data\refs\bin32\rimpexp.dll"
# SUBTRACT LINK32 /INCREMENTAL:no
LINK32_FLAGS=oldnames.lib winmm.lib kernel32.lib user32.lib uuid.lib\
 advapi32.lib /NOLOGO /SUBSYSTEM:windows /DLL /INCREMENTAL:yes\
 /PDB:$(OUTDIR)/"rimpexp32.pdb" /MAP:"FULL" /DEBUG /MACHINE:IX86\
 /DEF:".\fimpexp.def" /OUT:"\data\refs\bin32\rimpexp.dll"\
 /IMPLIB:$(OUTDIR)/"rimpexp32.lib" 
DEF_FILE=.\fimpexp.def
LINK32_OBJS= \
	$(INTDIR)/fimpexp.obj \
	$(INTDIR)/rimpexp.res

$(OUTDIR)/rimpexp.dll : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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
# PROP Output_Dir "\data\refs\bin32"
# PROP Intermediate_Dir "Unicode_"
OUTDIR=\data\refs\bin32
INTDIR=.\Unicode_

ALL : .\Unicode_\rimpexp.dll $(OUTDIR)/rimpexp32.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

$(INTDIR) : 
    if not exist $(INTDIR)/nul mkdir $(INTDIR)

# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE CPP /nologo /G4 /Zp2 /MT /W3 /GX /Zi /YX /Od /Gf /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "STRICT" /FR /c
# ADD CPP /nologo /G4 /Zp2 /MT /W3 /GX /Zi /YX /Od /Gf /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "UNICODE" /D "STRICT" /FR /c
CPP_PROJ=/nologo /G4 /Zp2 /MT /W3 /GX /Zi /YX /Od /Gf /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "UNICODE" /D "STRICT" /FR$(INTDIR)/ /Fp$(OUTDIR)/"rimpexp32.pch"\
 /Fo$(INTDIR)/ /Fd$(OUTDIR)/"rimpexp32.pdb" /c 
CPP_OBJS=.\Unicode_/
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
RSC_PROJ=/l 0x809 /fo$(INTDIR)/"rimpexp.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"rimpexp32.bsc" 
BSC32_SBRS= \
	$(INTDIR)/fimpexp.sbr

$(OUTDIR)/rimpexp32.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 oldnames.lib winmm.lib kernel32.lib user32.lib uuid.lib advapi32.lib /NOLOGO /SUBSYSTEM:windows /DLL /MAP:"FULL" /DEBUG /MACHINE:IX86 /OUT:"Win95_De\rimpexp.dll"
# SUBTRACT BASE LINK32 /INCREMENTAL:no
# ADD LINK32 oldnames.lib winmm.lib kernel32.lib user32.lib uuid.lib advapi32.lib /NOLOGO /SUBSYSTEM:windows /DLL /MAP:"FULL" /DEBUG /MACHINE:IX86 /OUT:"Unicode_\rimpexp.dll"
# SUBTRACT LINK32 /INCREMENTAL:no
LINK32_FLAGS=oldnames.lib winmm.lib kernel32.lib user32.lib uuid.lib\
 advapi32.lib /NOLOGO /SUBSYSTEM:windows /DLL /INCREMENTAL:yes\
 /PDB:$(OUTDIR)/"rimpexp32.pdb" /MAP:"FULL" /DEBUG /MACHINE:IX86\
 /DEF:".\fimpexp.def" /OUT:"Unicode_\rimpexp.dll"\
 /IMPLIB:$(OUTDIR)/"rimpexp32.lib" 
DEF_FILE=.\fimpexp.def
LINK32_OBJS= \
	$(INTDIR)/fimpexp.obj \
	$(INTDIR)/rimpexp.res

.\Unicode_\rimpexp.dll : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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
# Begin Group "Source Files"

################################################################################
# Begin Source File

SOURCE=.\fimpexp.c

!IF  "$(CFG)" == "Win32 Release"

$(INTDIR)/fimpexp.obj :  $(SOURCE)  $(INTDIR)

!ELSEIF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/fimpexp.obj :  $(SOURCE)  $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/fimpexp.obj :  $(SOURCE)  $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\rimpexp.rc

!IF  "$(CFG)" == "Win32 Release"

$(INTDIR)/rimpexp.res :  $(SOURCE)  $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/rimpexp.res :  $(SOURCE)  $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/rimpexp.res :  $(SOURCE)  $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\fimpexp.def
# End Source File
# End Group
# End Project
################################################################################
