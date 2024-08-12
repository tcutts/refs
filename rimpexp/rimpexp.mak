# Microsoft Visual C++ generated build script - Do not modify

PROJ = RIMPEXP
DEBUG = 0
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
FIRSTC = FIMPEXP.C   
FIRSTCPP =             
RC = rc
CFLAGS_D_WDLL = /nologo /Gs /G2 /W2 /Gf /Zi /ALw /YX /Od /D "_DEBUG" /I "d:\data\refs" /FR /GD /Fd"RIMPEXP.PDB"   /Fp"RIMPEXP.PCH"
CFLAGS_R_WDLL = /nologo /f- /Gs /G2 /W2 /Gf /ALw /YX /O2 /Ob1 /D "NDEBUG" /I "d:\data\refs" /FR /GD /Fp"RIMPEXP.PCH"
LFLAGS_D_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /CO /MAP:FULL
LFLAGS_R_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /MAP /MAP:FULL
LIBS_D_WDLL = oldnames libw ldllcew commdlg.lib mmsystem.lib shell.lib 
LIBS_R_WDLL = oldnames libw ldllcew mmsystem.lib 
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
DEFFILE = FIMPEXP.DEF
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
SBRS = FIMPEXP.SBR


FIMPEXP_DEP = d:\msvc\include\tchar.h


all:	$(PROJ).DLL $(PROJ).BSC

FIMPEXP.OBJ:	FIMPEXP.C $(FIMPEXP_DEP)
	$(CC) $(CFLAGS) $(CCREATEPCHFLAG) /c FIMPEXP.C

RIMPEXP.RES:	RIMPEXP.RC $(RIMPEXP_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r RIMPEXP.RC


$(PROJ).DLL::	RIMPEXP.RES

$(PROJ).DLL::	FIMPEXP.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
FIMPEXP.OBJ +
$(OBJS_EXT)
$(PROJ).DLL
$(MAPFILE)
d:\msvc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) RIMPEXP.RES $@
	@copy $(PROJ).CRF MSVC.BND
	implib /nowep $(PROJ).LIB $(PROJ).DLL

$(PROJ).DLL::	RIMPEXP.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) RIMPEXP.RES $@

run: $(PROJ).DLL
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
