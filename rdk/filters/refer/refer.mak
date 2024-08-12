# Microsoft Visual C++ generated build script - Do not modify

PROJ = REFER
DEBUG = 0
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
FIRSTC = REFER.C     
FIRSTCPP =             
RC = rc
CFLAGS_D_WDLL = /nologo /Gs /G2 /W3 /Gf /Zi /ALw /YX /Od /D "_DEBUG" /D "STRICT" /Fc /FR /GD /Fd"REFER.PDB"   /Fp"REFER.PCH"
CFLAGS_R_WDLL = /nologo /f- /Gs /G2 /W3 /Gf /ALw /YX /O2 /Ob1 /D "NDEBUG" /D "STRICT" /FR /GD /Fp"REFER.PCH"
LFLAGS_D_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /CO /MAP /LINE /MAP:FULL
LFLAGS_R_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /MAP /MAP:FULL
LIBS_D_WDLL = oldnames libw ldllcew mmsystem.lib 
LIBS_R_WDLL = oldnames libw ldllcew mmsystem.lib 
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
DEFFILE = REFER.DEF
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
SBRS = REFER.SBR


REFER_DEP = d:\data\refs\imptfr.h \
	d:\data\refs\rimpexp.h


RIMPEXP_DEP = 

all:	$(PROJ).DLL $(PROJ).BSC

REFER.OBJ:	REFER.C $(REFER_DEP)
	$(CC) $(CFLAGS) $(CCREATEPCHFLAG) /c REFER.C

REFER.RES:	REFER.RC $(REFER_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r REFER.RC


$(PROJ).DLL::	REFER.RES

$(PROJ).DLL::	REFER.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
REFER.OBJ +
$(OBJS_EXT)
$(PROJ).DLL
$(MAPFILE)
D:\MSVC\LIB\+
D:\MSVC\MFC\LIB\+
RIMPEXP.LIB+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) REFER.RES $@
	@copy $(PROJ).CRF MSVC.BND
	implib /nowep $(PROJ).LIB $(PROJ).DLL

$(PROJ).DLL::	REFER.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) REFER.RES $@

run: $(PROJ).DLL
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
