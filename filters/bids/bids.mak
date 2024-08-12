# Microsoft Visual C++ generated build script - Do not modify

PROJ = BIDS
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
FIRSTC = BIDS.C      
FIRSTCPP =             
RC = rc
CFLAGS_D_WDLL = /nologo /Gs /G2 /W2 /Gf /Zi /ALw /YX /O2 /Ob2 /D "_DEBUG" /FR /GD /Fd"BIDS.PDB" /Fp"BIDS.PCH"
CFLAGS_R_WDLL = /nologo /f- /Gs /G2 /W2 /Gf /ALw /YX /O2 /Ob1 /D "NDEBUG" /GD /Fp"BIDS.PCH"
LFLAGS_D_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /CO /MAP:FULL
LFLAGS_R_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /MAP /MAP:FULL
LIBS_D_WDLL = oldnames libw ldllcew commdlg.lib mmsystem.lib olecli.lib olesvr.lib shell.lib 
LIBS_R_WDLL = oldnames libw ldllcew mmsystem.lib 
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
DEFFILE = BIDS.DEF
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
SBRS = BIDS.SBR


RIMPEXP_DEP = 

BIDS_DEP = d:\data\refs\imptfr.h \
	d:\data\refs\rimpexp.h


all:	$(PROJ).DLL

BIDS.OBJ:	BIDS.C $(BIDS_DEP)
	$(CC) $(CFLAGS) $(CCREATEPCHFLAG) /c BIDS.C

BIDS.RES:	BIDS.RC $(BIDS_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r BIDS.RC


$(PROJ).DLL::	BIDS.RES

$(PROJ).DLL::	BIDS.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
BIDS.OBJ +
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
	$(RC) $(RESFLAGS) BIDS.RES $@
	@copy $(PROJ).CRF MSVC.BND
	implib /nowep $(PROJ).LIB $(PROJ).DLL

$(PROJ).DLL::	BIDS.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) BIDS.RES $@

run: $(PROJ).DLL
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
