# Microsoft Visual C++ generated build script - Do not modify

PROJ = REGEXP
DEBUG = 1
PROGTYPE = 1
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = D:\DATA\REFS\RIMPEXP\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC =             
FIRSTCPP =             
RC = rc
CFLAGS_D_WDLL = /nologo /W3 /FR /G2 /Zi /D_DEBUG /Od /GD /ALw /Fd"REGEXP.PDB"
CFLAGS_R_WDLL = /nologo /W3 /FR /O1 /DNDEBUG /GD /ALw
LFLAGS_D_WDLL = /NOLOGO /ONERROR:NOEXE /NOD /PACKC:61440 /CO /NOE /ALIGN:16 /MAP:FULL
LFLAGS_R_WDLL = /NOLOGO /ONERROR:NOEXE /NOD /PACKC:61440 /NOE /ALIGN:16 /MAP:FULL
LIBS_D_WDLL = oldnames libw commdlg shell olecli olesvr ldllcew
LIBS_R_WDLL = oldnames libw commdlg shell olecli olesvr ldllcew
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
DEFFILE = REGEXP.DEF
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WDLL)
LFLAGS = $(LFLAGS_D_WDLL)
LIBS = $(LIBS_D_WDLL)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_WDLL)
LFLAGS = $(LFLAGS_R_WDLL)
LIBS = $(LIBS_R_WDLL)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = REGERROR.SBR \
		REGEXP.SBR \
		REGSUB.SBR


REGERROR_DEP = 

REGEXP_DEP = d:\data\src\re\regexp.h \
	d:\data\src\re\regmagic.h


REGSUB_DEP = d:\data\src\re\regexp.h \
	d:\data\src\re\regmagic.h


all:	$(PROJ).DLL $(PROJ).BSC

REGERROR.OBJ:	..\..\SRC\RE\REGERROR.C $(REGERROR_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c ..\..\SRC\RE\REGERROR.C

REGEXP.OBJ:	..\..\SRC\RE\REGEXP.C $(REGEXP_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c ..\..\SRC\RE\REGEXP.C

REGSUB.OBJ:	..\..\SRC\RE\REGSUB.C $(REGSUB_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c ..\..\SRC\RE\REGSUB.C

REGEXP.RES:	..\..\SRC\RE\REGEXP.RC $(REGEXP_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r -FoD:\DATA\REFS\RIMPEXP\REGEXP.RES ..\..\SRC\RE\REGEXP.RC


$(PROJ).DLL::	REGEXP.RES

$(PROJ).DLL::	REGERROR.OBJ REGEXP.OBJ REGSUB.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
REGERROR.OBJ +
REGEXP.OBJ +
REGSUB.OBJ +
$(OBJS_EXT)
$(PROJ).DLL
$(MAPFILE)
d:\msvc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) REGEXP.RES $@
	@copy $(PROJ).CRF MSVC.BND
	implib /nowep $(PROJ).LIB $(PROJ).DLL

$(PROJ).DLL::	REGEXP.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) REGEXP.RES $@

run: $(PROJ).DLL
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
