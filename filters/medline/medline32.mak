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
!MESSAGE NMAKE /f "medline32.mak" CFG="Win32 Debug"
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

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Win95_Re"
# PROP Intermediate_Dir "Win95_Re"
OUTDIR=.\Win95_Re
INTDIR=.\Win95_Re

ALL : \data\refs\bin32\medline.flt .\Win95_Re\medline32.map\
 .\Win95_Re\medline32.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE CPP /nologo /MT /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /Zp2 /MT /W3 /YX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /FR /c
CPP_PROJ=/nologo /Zp2 /MT /W3 /YX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /FR$(INTDIR)/ /Fp$(OUTDIR)/"medline32.pch" /Fo$(INTDIR)/ /c 
CPP_OBJS=.\Win95_Re/
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
RSC_PROJ=/l 0x809 /fo$(INTDIR)/"medline.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"medline32.bsc" 
BSC32_SBRS= \
	.\Win95_Re\medline.sbr

.\Win95_Re\medline32.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /NOLOGO /SUBSYSTEM:windows /DLL /MACHINE:I386
# ADD LINK32 kernel32.lib user32.lib advapi32.lib shell32.lib /NOLOGO /SUBSYSTEM:windows /DLL /INCREMENTAL:yes /MAP /MACHINE:I386 /OUT:"\data\refs\bin32\medline.flt"
# SUBTRACT LINK32 /VERBOSE
LINK32_FLAGS=kernel32.lib user32.lib advapi32.lib shell32.lib /NOLOGO\
 /SUBSYSTEM:windows /DLL /INCREMENTAL:yes /PDB:$(OUTDIR)/"medline32.pdb"\
 /MAP:$(INTDIR)/"medline32.map" /MACHINE:I386\
 /OUT:"\data\refs\bin32\medline.flt" /IMPLIB:$(OUTDIR)/"medline32.lib" 
DEF_FILE=
LINK32_OBJS= \
	.\Win95_Re\medline.res \
	.\Win95_Re\medline.obj \
	\data\refs\bin32\rimpexp32.lib

\data\refs\bin32\medline.flt : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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
# PROP Output_Dir "Win95_De"
# PROP Intermediate_Dir "Win95_De"
OUTDIR=.\Win95_De
INTDIR=.\Win95_De

ALL : \data\refs\bin32\medline.flt .\Win95_De\medline32.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /Zp2 /MT /W3 /Zi /YX /Od /Gf /Gy /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /FR /c
CPP_PROJ=/nologo /Zp2 /MT /W3 /Zi /YX /Od /Gf /Gy /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /FR$(INTDIR)/ /Fp$(OUTDIR)/"medline32.pch" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"medline32.pdb" /c 
CPP_OBJS=.\Win95_De/
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
RSC_PROJ=/l 0x809 /fo$(INTDIR)/"medline.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"medline32.bsc" 
BSC32_SBRS= \
	.\Win95_De\medline.sbr

.\Win95_De\medline32.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /NOLOGO /SUBSYSTEM:windows /DLL /DEBUG /MACHINE:I386
# ADD LINK32 kernel32.lib user32.lib advapi32.lib shell32.lib /NOLOGO /SUBSYSTEM:windows /DLL /DEBUG /MACHINE:I386 /OUT:"\data\refs\bin32\medline.flt"
# SUBTRACT LINK32 /VERBOSE /INCREMENTAL:no
LINK32_FLAGS=kernel32.lib user32.lib advapi32.lib shell32.lib /NOLOGO\
 /SUBSYSTEM:windows /DLL /INCREMENTAL:yes /PDB:$(OUTDIR)/"medline32.pdb" /DEBUG\
 /MACHINE:I386 /OUT:"\data\refs\bin32\medline.flt"\
 /IMPLIB:$(OUTDIR)/"medline32.lib" 
DEF_FILE=
LINK32_OBJS= \
	.\Win95_De\medline.res \
	.\Win95_De\medline.obj \
	\data\refs\bin32\rimpexp32.lib

\data\refs\bin32\medline.flt : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

SOURCE=.\medline.rc

!IF  "$(CFG)" == "Win32 Release"

.\Win95_Re\medline.res :  $(SOURCE)  $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\Win95_De\medline.res :  $(SOURCE)  $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\medline.c
DEP_MEDLI=\
	..\..\..\src\sscanf\wsscanf.h\
	..\..\inc\imptfr.h\
	..\..\rimpexp\rimpexp.h

!IF  "$(CFG)" == "Win32 Release"

.\Win95_Re\medline.obj :  $(SOURCE)  $(DEP_MEDLI) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\Win95_De\medline.obj :  $(SOURCE)  $(DEP_MEDLI) $(INTDIR)

!ENDIF 

# End Source File
# End Group
################################################################################
# Begin Group "Object Files & Libraries"

################################################################################
# Begin Source File

SOURCE=\data\refs\bin32\rimpexp32.lib
# End Source File
# End Group
# End Project
################################################################################
