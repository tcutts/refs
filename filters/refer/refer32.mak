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
!MESSAGE NMAKE /f "refer32.mak" CFG="Win32 Debug"
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
# PROP Output_Dir "WinRel"
# PROP Intermediate_Dir "WinRel"
OUTDIR=.\WinRel
INTDIR=.\WinRel

ALL : \data\refs\bin32\refer.flt $(OUTDIR)/refer32.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32  
# ADD BASE CPP /nologo /MT /W2 /GX /YX /O2 /Ob2 /I "d:\msvc\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_MBCS" /FR /c
# ADD CPP /nologo /G4 /Zp2 /MT /W2 /GX /YX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "_MBCS" /FR /c
CPP_PROJ=/nologo /G4 /Zp2 /MT /W2 /GX /YX /O2 /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"refer32.pch"\
 /Fo$(INTDIR)/ /c 
CPP_OBJS=.\WinRel/
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
RSC_PROJ=/l 0x809 /fo$(INTDIR)/"refer.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"refer32.bsc" 
BSC32_SBRS= \
	$(INTDIR)/refer.sbr

$(OUTDIR)/refer32.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 oldnames.lib ldllcew.lib winmm.lib /NOLOGO /SUBSYSTEM:windows /DLL /MAP:"FULL" /MACHINE:IX86
# ADD LINK32 oldnames.lib winmm.lib kernel32.lib user32.lib comdlg32.lib advapi32.lib shell32.lib /NOLOGO /SUBSYSTEM:windows /DLL /INCREMENTAL:yes /MACHINE:IX86 /OUT:"\data\refs\bin32\refer.flt"
# SUBTRACT LINK32 /MAP
LINK32_FLAGS=oldnames.lib winmm.lib kernel32.lib user32.lib comdlg32.lib\
 advapi32.lib shell32.lib /NOLOGO /SUBSYSTEM:windows /DLL /INCREMENTAL:yes\
 /PDB:$(OUTDIR)/"refer32.pdb" /MACHINE:IX86 /OUT:"\data\refs\bin32\refer.flt"\
 /IMPLIB:$(OUTDIR)/"refer32.lib" 
DEF_FILE=
LINK32_OBJS= \
	\DATA\REFS\bin32\rimpexp32.lib \
	$(INTDIR)/refer.res \
	$(INTDIR)/refer.obj

\data\refs\bin32\refer.flt : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
OUTDIR=.\WinDebug
INTDIR=.\WinDebug

ALL : \data\refs\bin32\refer.flt $(OUTDIR)/refer32.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE CPP /nologo /MT /W2 /GX /Zi /YX /O2 /Ob2 /I "d:\msvc\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_MBCS" /FR /c
# ADD CPP /nologo /G4 /Zp2 /MT /W2 /GX /Zi /YX /Od /Gf /Gy /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "_MBCS" /FR /c
CPP_PROJ=/nologo /G4 /Zp2 /MT /W2 /GX /Zi /YX /Od /Gf /Gy /D "_DEBUG" /D\
 "WIN32" /D "_WINDOWS" /D "STRICT" /D "_MBCS" /FR$(INTDIR)/\
 /Fp$(OUTDIR)/"refer32.pch" /Fo$(INTDIR)/ /Fd$(OUTDIR)/"refer32.pdb" /c 
CPP_OBJS=.\WinDebug/
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
RSC_PROJ=/l 0x809 /fo$(INTDIR)/"refer.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"refer32.bsc" 
BSC32_SBRS= \
	$(INTDIR)/refer.sbr

$(OUTDIR)/refer32.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 oldnames.lib ldllcew.lib winmm.lib /NOLOGO /SUBSYSTEM:windows /DLL /MAP:"FULL" /DEBUG /MACHINE:IX86
# ADD LINK32 oldnames.lib winmm.lib kernel32.lib user32.lib comdlg32.lib advapi32.lib shell32.lib /NOLOGO /SUBSYSTEM:windows /DLL /MAP:"FULL" /DEBUG /MACHINE:IX86 /OUT:"\data\refs\bin32\refer.flt"
LINK32_FLAGS=oldnames.lib winmm.lib kernel32.lib user32.lib comdlg32.lib\
 advapi32.lib shell32.lib /NOLOGO /SUBSYSTEM:windows /DLL /INCREMENTAL:yes\
 /PDB:$(OUTDIR)/"refer32.pdb" /MAP:"FULL" /DEBUG /MACHINE:IX86\
 /OUT:"\data\refs\bin32\refer.flt" /IMPLIB:$(OUTDIR)/"refer32.lib" 
DEF_FILE=
LINK32_OBJS= \
	\DATA\REFS\bin32\rimpexp32.lib \
	$(INTDIR)/refer.res \
	$(INTDIR)/refer.obj

\data\refs\bin32\refer.flt : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Unicode0"
# PROP BASE Intermediate_Dir "Unicode0"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Unicode"
# PROP Intermediate_Dir "Unicode"
OUTDIR=.\Unicode
INTDIR=.\Unicode

ALL : \data\refs\bin32\refer.flt $(OUTDIR)/refer32.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /D "_UNICODE" /win32
MTL_PROJ=/nologo /D "_DEBUG" /D "_UNICODE" /win32 
# ADD BASE CPP /nologo /G4 /Zp2 /MT /W2 /Zi /YX /Od /Gf /Gy /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "STRICT" /FR /c
# ADD CPP /nologo /G4 /Zp2 /MT /W2 /Zi /YX /Od /Gf /Gy /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "UNICODE" /D "STRICT" /FR /c
CPP_PROJ=/nologo /G4 /Zp2 /MT /W2 /Zi /YX /Od /Gf /Gy /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "UNICODE" /D "STRICT" /FR$(INTDIR)/ /Fp$(OUTDIR)/"refer32.pch"\
 /Fo$(INTDIR)/ /Fd$(OUTDIR)/"refer32.pdb" /c 
CPP_OBJS=.\Unicode/
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
RSC_PROJ=/l 0x809 /fo$(INTDIR)/"refer.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"refer32.bsc" 
BSC32_SBRS= \
	$(INTDIR)/refer.sbr

$(OUTDIR)/refer32.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 user32.lib oldnames.lib winmm.lib advapi32.lib /NOLOGO /SUBSYSTEM:windows /DLL /MAP:"FULL" /DEBUG /MACHINE:IX86 /OUT:"Win95_De\REFER.FLT"
# ADD LINK32 user32.lib oldnames.lib winmm.lib advapi32.lib /NOLOGO /SUBSYSTEM:windows /DLL /DEBUG /MACHINE:IX86 /OUT:"\data\refs\bin32\refer.flt"
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=user32.lib oldnames.lib winmm.lib advapi32.lib /NOLOGO\
 /SUBSYSTEM:windows /DLL /INCREMENTAL:yes /PDB:$(OUTDIR)/"refer32.pdb" /DEBUG\
 /MACHINE:IX86 /OUT:"\data\refs\bin32\refer.flt" /IMPLIB:$(OUTDIR)/"refer32.lib"\
 
DEF_FILE=
LINK32_OBJS= \
	\DATA\REFS\bin32\rimpexp32.lib \
	$(INTDIR)/refer.res \
	$(INTDIR)/refer.obj

\data\refs\bin32\refer.flt : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

SOURCE=\DATA\REFS\bin32\rimpexp32.lib
# End Source File
# End Group
################################################################################
# Begin Group "Source Files"

################################################################################
# Begin Source File

SOURCE=.\refer.rc

!IF  "$(CFG)" == "Win32 Release"

$(INTDIR)/refer.res :  $(SOURCE)  $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/refer.res :  $(SOURCE)  $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/refer.res :  $(SOURCE)  $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\refer.c
DEP_REFER=\
	..\..\inc\imptfr.h\
	..\..\rimpexp\rimpexp.h

!IF  "$(CFG)" == "Win32 Release"

$(INTDIR)/refer.obj :  $(SOURCE)  $(DEP_REFER) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/refer.obj :  $(SOURCE)  $(DEP_REFER) $(INTDIR)

!ELSEIF  "$(CFG)" == "Unicode Debug"

$(INTDIR)/refer.obj :  $(SOURCE)  $(DEP_REFER) $(INTDIR)

!ENDIF 

# End Source File
# End Group
# End Project
################################################################################
