# Microsoft Visual C++ Generated NMAKE File, Format Version 2.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Win32 Release" && "$(CFG)" != "Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "refpo32.mak" CFG="Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Win95_Re"
# PROP Intermediate_Dir "Win95_Re"
OUTDIR=.\Win95_Re
INTDIR=.\Win95_Re

ALL : $(OUTDIR)/refpo.dll $(OUTDIR)/refpo32.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE CPP /nologo /MT /W3 /GX /YX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_MBCS" /FR /c
# ADD CPP /nologo /MT /W3 /GX /YX /O1 /Ob2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /FR /c
CPP_PROJ=/nologo /MT /W3 /GX /YX /O1 /Ob2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"refpo32.pch" /Fo$(INTDIR)/ /c 
CPP_OBJS=.\Win95_Re/
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
RSC_PROJ=/l 0x809 /fo$(INTDIR)/"REFPO.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"refpo32.bsc" 
BSC32_SBRS= \
	$(INTDIR)/REFEN.SBR

$(OUTDIR)/refpo32.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 oldnames.lib ldllcew.lib /NOLOGO /SUBSYSTEM:windows /DLL /MAP:"FULL" /MACHINE:IX86
# ADD LINK32 oldnames.lib kernel32.lib user32.lib /NOLOGO /SUBSYSTEM:windows /DLL /INCREMENTAL:yes /MACHINE:IX86 /OUT:"Win95_Re\refpo.dll"
# SUBTRACT LINK32 /MAP
LINK32_FLAGS=oldnames.lib kernel32.lib user32.lib /NOLOGO /SUBSYSTEM:windows\
 /DLL /INCREMENTAL:yes /PDB:$(OUTDIR)/"refpo32.pdb" /MACHINE:IX86\
 /OUT:"Win95_Re\refpo.dll" /IMPLIB:$(OUTDIR)/"refpo32.lib" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/REFEN.OBJ \
	$(INTDIR)/REFPO.res

$(OUTDIR)/refpo.dll : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Win32 Debug"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Win95_De"
# PROP Intermediate_Dir "Win95_De"
OUTDIR=.\Win95_De
INTDIR=.\Win95_De

ALL : $(OUTDIR)/refpo.dll $(OUTDIR)/refpo32.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_MBCS" /FR /c
# ADD CPP /nologo /MT /W3 /GX /Zi /YX /Od /Ob2 /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /FR /c
CPP_PROJ=/nologo /MT /W3 /GX /Zi /YX /Od /Ob2 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"refpo32.pch" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"refpo32.pdb" /c 
CPP_OBJS=.\Win95_De/
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
RSC_PROJ=/l 0x809 /fo$(INTDIR)/"REFPO.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"refpo32.bsc" 
BSC32_SBRS= \
	$(INTDIR)/REFEN.SBR

$(OUTDIR)/refpo32.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 oldnames.lib ldllcew.lib /NOLOGO /SUBSYSTEM:windows /DLL /MAP:"FULL" /DEBUG /MACHINE:IX86
# ADD LINK32 oldnames.lib kernel32.lib user32.lib winspool.lib advapi32.lib shell32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /DLL /MAP:"FULL" /DEBUG /MACHINE:IX86 /OUT:"Win95_De\refpo.dll"
LINK32_FLAGS=oldnames.lib kernel32.lib user32.lib winspool.lib advapi32.lib\
 shell32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /DLL /INCREMENTAL:yes\
 /PDB:$(OUTDIR)/"refpo32.pdb" /MAP:"FULL" /DEBUG /MACHINE:IX86\
 /OUT:"Win95_De\refpo.dll" /IMPLIB:$(OUTDIR)/"refpo32.lib" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/REFEN.OBJ \
	$(INTDIR)/REFPO.res

$(OUTDIR)/refpo.dll : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

SOURCE=.\REFEN.C

$(INTDIR)/REFEN.OBJ :  $(SOURCE)  $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\REFPO.RC
DEP_REFPO=\
	\MSVC\INCLUDE\WINDOWS.H\
	\MSVC\INCLUDE\VER.H\
	.\REFS.H

$(INTDIR)/REFPO.res :  $(SOURCE)  $(DEP_REFPO) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

# End Source File
# End Group
################################################################################
# Begin Group "Libraries"

# End Group
# End Project
################################################################################
