# Microsoft Visual C++ generated build script - Do not modify

PROJ = MEDLINE
DEBUG = 1
PROGTYPE = 1
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = D:\DATA\REFS\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC = MEDLINE.C   
FIRSTCPP =             
RC = rc
CFLAGS_D_WDLL = /nologo /G2 /W2 /Gf /Zi /ALw /YX /O2 /Ob2 /D "_DEBUG" /FR /GD /Fd"MEDLINE.PDB" /Fp"MEDLINE.PCH"
CFLAGS_R_WDLL = /nologo /f- /Gs /G2 /W2 /Gf /ALw /YX /O2 /Ob1 /D "NDEBUG" /GD /Fp"MEDLINE.PCH"
LFLAGS_D_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /CO /MAP:FULL
LFLAGS_R_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /MAP /MAP:FULL
LIBS_D_WDLL = libw ldllcew oldnames commdlg.lib mmsystem.lib olecli.lib olesvr.lib shell.lib 
LIBS_R_WDLL = libw ldllcew oldnames mmsystem.lib 
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
DEFFILE = MEDLINE.DEF
OBJS_EXT = 
LIBS_EXT = RIMPEXP.LIB 
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
SBRS = MEDLINE.SBR \
		WSSCANF.SBR


RIMPEXP_DEP = 

MEDLINE_DEP = d:\data\refs\imptfr.h \
	d:\data\refs\rimpexp.h


WSSCANF_DEP = d:\data\src\sscanf\wstdarg.h


WSSCANF_DEP = d:\data\src\sscanf\wsscanf.h


all:	$(PROJ).DLL $(PROJ).BSC

MEDLINE.OBJ:	MEDLINE.C $(MEDLINE_DEP)
	$(CC) $(CFLAGS) $(CCREATEPCHFLAG) /c MEDLINE.C

MEDLINE.RES:	MEDLINE.RC $(MEDLINE_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r MEDLINE.RC

WSSCANF.OBJ:	..\SRC\SSCANF\WSSCANF.C $(WSSCANF_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c ..\SRC\SSCANF\WSSCANF.C


$(PROJ).DLL::	MEDLINE.RES

$(PROJ).DLL::	MEDLINE.OBJ WSSCANF.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
MEDLINE.OBJ +
WSSCANF.OBJ +
$(OBJS_EXT)
$(PROJ).DLL
$(MAPFILE)
d:\msvc\lib\+
RIMPEXP.LIB+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) MEDLINE.RES $@
	@copy $(PROJ).CRF MSVC.BND
	implib /nowep $(PROJ).LIB $(PROJ).DLL

$(PROJ).DLL::	MEDLINE.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) MEDLINE.RES $@

run: $(PROJ).DLL
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
