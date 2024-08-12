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
!MESSAGE NMAKE /f "bids32.mak" CFG="Win32 Debug"
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
# PROP Target_Last_Scanned "Win32 Release"
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

ALL : \data\refs\bin32\bids.flt $(OUTDIR)/bids32.map $(OUTDIR)/bids32.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE CPP /nologo /MT /W2 /GX /YX /O2 /Ob2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_MBCS" /FR /c
# ADD CPP /nologo /G4 /Zp2 /MT /W3 /YX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "STRICT" /FR /c
CPP_PROJ=/nologo /G4 /Zp2 /MT /W3 /YX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_MBCS" /D "STRICT" /FR$(INTDIR)/ /Fp$(OUTDIR)/"bids32.pch" /Fo$(INTDIR)/ /c\
 
CPP_OBJS=.\Win95_Re/
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
RSC_PROJ=/l 0x809 /fo$(INTDIR)/"bids.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"bids32.bsc" 
BSC32_SBRS= \
	$(INTDIR)/bids.sbr

$(OUTDIR)/bids32.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 oldnames.lib ldllcew.lib winmm.lib /NOLOGO /SUBSYSTEM:windows /DLL /MAP:"FULL" /MACHINE:IX86
# ADD LINK32 oldnames.lib winmm.lib user32.lib advapi32.lib /NOLOGO /SUBSYSTEM:windows /DLL /INCREMENTAL:yes /MAP /MACHINE:IX86 /OUT:"\data\refs\bin32\bids.flt"
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=oldnames.lib winmm.lib user32.lib advapi32.lib /NOLOGO\
 /SUBSYSTEM:windows /DLL /INCREMENTAL:yes /PDB:$(OUTDIR)/"bids32.pdb"\
 /MAP:$(INTDIR)/"bids32.map" /MACHINE:IX86 /OUT:"\data\refs\bin32\bids.flt"\
 /IMPLIB:$(OUTDIR)/"bids32.lib" 
DEF_FILE=
LINK32_OBJS= \
	\data\refs\bin32\rimpexp32.lib \
	$(INTDIR)/bids.obj \
	$(INTDIR)/bids.res

\data\refs\bin32\bids.flt : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

ALL : \data\refs\bin32\bids.flt $(OUTDIR)/bids32.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE CPP /nologo /MT /W2 /GX /Zi /YX /O2 /Ob2 /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_MBCS" /FR /c
# ADD CPP /nologo /G4 /Zp2 /MT /W3 /Zi /YX /Od /Gf /Gy /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "STRICT" /FR /c
CPP_PROJ=/nologo /G4 /Zp2 /MT /W3 /Zi /YX /Od /Gf /Gy /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_MBCS" /D "STRICT" /FR$(INTDIR)/ /Fp$(OUTDIR)/"bids32.pch"\
 /Fo$(INTDIR)/ /Fd$(OUTDIR)/"bids32.pdb" /c 
CPP_OBJS=.\Win95_De/
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
RSC_PROJ=/l 0x809 /fo$(INTDIR)/"bids.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"bids32.bsc" 
BSC32_SBRS= \
	$(INTDIR)/bids.sbr

$(OUTDIR)/bids32.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 oldnames.lib ldllcew.lib winmm.lib /NOLOGO /SUBSYSTEM:windows /DLL /MAP:"FULL" /DEBUG /MACHINE:IX86
# ADD LINK32 oldnames.lib winmm.lib user32.lib advapi32.lib /NOLOGO /SUBSYSTEM:windows /DLL /DEBUG /MACHINE:IX86 /OUT:"\data\refs\bin32\bids.flt"
# SUBTRACT LINK32 /INCREMENTAL:no /MAP
LINK32_FLAGS=oldnames.lib winmm.lib user32.lib advapi32.lib /NOLOGO\
 /SUBSYSTEM:windows /DLL /INCREMENTAL:yes /PDB:$(OUTDIR)/"bids32.pdb" /DEBUG\
 /MACHINE:IX86 /OUT:"\data\refs\bin32\bids.flt" /IMPLIB:$(OUTDIR)/"bids32.lib" 
DEF_FILE=
LINK32_OBJS= \
	\data\refs\bin32\rimpexp32.lib \
	$(INTDIR)/bids.obj \
	$(INTDIR)/bids.res

\data\refs\bin32\bids.flt : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

SOURCE=\data\refs\bin32\rimpexp32.lib
# End Source File
# End Group
################################################################################
# Begin Group "Source Files"

################################################################################
# Begin Source File

SOURCE=.\bids.c
DEP_BIDS_=\
	..\..\inc\imptfr.h\
	..\..\rimpexp\rimpexp.h

$(INTDIR)/bids.obj :  $(SOURCE)  $(DEP_BIDS_) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\bids.rc

$(INTDIR)/bids.res :  $(SOURCE)  $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

# End Source File
# End Group
# End Project
################################################################################
