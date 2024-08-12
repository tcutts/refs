# Microsoft Visual C++ generated build script - Do not modify

PROJ = REFS
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG /dSPLASH /dCC_TOOLBAR 
R_RCDEFINES = /dNDEBUG /dSPLASH /dCC_TOOLBAR 
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
FIRSTC =             
FIRSTCPP = GLOBALS.CPP 
RC = rc
CFLAGS_D_WEXE = /nologo /G2 /W3 /Zi /AL /Gt65500 /YX"globals.h" /Od /D "_DEBUG" /D "STRICT" /D "CC_TOOLBAR" /I "d:\data\ctl3d" /I "d:\wfwdev\include" /FR /GA /Fd"REFS.PDB"                 /Fp"REFS.PCH"
CFLAGS_R_WEXE = /nologo /f- /Gs /G2 /W2 /AL /Gt65500 /YX"globals.h" /O2 /Ob1 /D "NDEBUG" /D "STRICT" /D "CC_TOOLBAR" /I "d:\data\ctl3d" /I "d:\wfwdev\include" /Fr /GA /Fp"REFS.PCH"
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /PACKD:65500 /ALIGN:16 /ONERROR:NOEXE /CO /MAP /LINE  
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /PACKD:65500 /ALIGN:16 /ONERROR:NOEXE /MAP /LINE  
LIBS_D_WEXE = llibcew oldnames libw commdlg.lib mmsystem.lib shell.lib ver.lib 
LIBS_R_WEXE = llibcew oldnames libw commdlg.lib mmsystem.lib shell.lib ver.lib 
RCFLAGS = /nologo 
RESFLAGS = /nologo 
RUNFLAGS = 
DEFFILE = MODULE.DEF
OBJS_EXT = 
LIBS_EXT = RIMPEXP.LIB ..\CTL3D\OBJ16\DLL\CTL3D.LIB 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WEXE)
LFLAGS = $(LFLAGS_D_WEXE)
LIBS = $(LIBS_D_WEXE)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_WEXE)
LFLAGS = $(LFLAGS_R_WEXE)
LIBS = $(LIBS_R_WEXE)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = GLOBALS.SBR \
		MYCOLLS.SBR \
		OBJECT.SBR \
		OTREF.SBR \
		OTREFWND.SBR \
		OTSCOLL.SBR \
		RCONFOPT.SBR \
		RCUTPAST.SBR \
		REFABOUT.SBR \
		REFBIBS.SBR \
		REFFONT.SBR \
		REFCHILD.SBR \
		REFFRAME.SBR \
		REFIMP.SBR \
		REFINOPT.SBR \
		REFIO.SBR \
		REFLOPTS.SBR \
		REFNAG.SBR \
		REFPAINT.SBR \
		REFPRN.SBR \
		REFS.SBR \
		RSETLANG.SBR \
		RSRCHOPT.SBR \
		RSRTOPT.SBR \
		AUTHDLG.SBR \
		EDITDLG.SBR \
		JLISTDLG.SBR


RIMPEXP_DEP = 

CTL3D_DEP = 

GLOBALS_DEP = d:\data\refs\inc/globals.h \
	d:\msvc\include\tchar.h \
	d:\data\refs\inc/\config.h \
	d:\data\refs\inc/\refs.h \
	d:\data\refs\inc/\otref.h \
	d:\data\refs\inc/\object.h \
	d:\data\refs\inc/\otscoll.h \
	d:\data\refs\inc/\mycolls.h \
	d:\data\refs\inc/\otrefwnd.h \
	d:\data\refs\inc/refimp.h \
	d:\data\refs\inc/\imptfr.h


MYCOLLS_DEP = d:\data\refs\inc/globals.h \
	d:\msvc\include\tchar.h \
	d:\data\refs\inc/\config.h \
	d:\data\refs\inc/\refs.h \
	d:\data\refs\inc/\otref.h \
	d:\data\refs\inc/\object.h \
	d:\data\refs\inc/\otscoll.h \
	d:\data\refs\inc/\mycolls.h \
	d:\data\refs\inc/\otrefwnd.h \
	d:\data\refs\inc/mycolls.h


OBJECT_DEP = d:\data\refs\inc/object.h


OTREF_DEP = d:\data\refs\inc/globals.h \
	d:\msvc\include\tchar.h \
	d:\data\refs\inc/\config.h \
	d:\data\refs\inc/\refs.h \
	d:\data\refs\inc/\otref.h \
	d:\data\refs\inc/\object.h \
	d:\data\refs\inc/\otscoll.h \
	d:\data\refs\inc/\mycolls.h \
	d:\data\refs\inc/\otrefwnd.h \
	d:\data\refs\inc/refpaint.h \
	d:\data\refs\rimpexp/rimpexp.h \
	d:\data\refs\inc/editdlg.h \
	d:\data\refs\inc/authdlg.h


OTREFWND_DEP = d:\data\refs\inc/globals.h \
	d:\msvc\include\tchar.h \
	d:\data\refs\inc/\config.h \
	d:\data\refs\inc/\refs.h \
	d:\data\refs\inc/\otref.h \
	d:\data\refs\inc/\object.h \
	d:\data\refs\inc/\otscoll.h \
	d:\data\refs\inc/\mycolls.h \
	d:\data\refs\inc/\otrefwnd.h \
	d:\data\refs\inc/reffont.h \
	d:\data\refs\inc/refimp.h \
	d:\data\refs\inc/\imptfr.h \
	d:\data\refs\inc/refpaint.h \
	d:\data\refs\inc/rtoolbar.h \
	d:\data\refs\inc/refframe.h \
	d:\data\refs\inc/redit.h


OTSCOLL_DEP = d:\data\refs\inc/globals.h \
	d:\msvc\include\tchar.h \
	d:\data\refs\inc/\config.h \
	d:\data\refs\inc/\refs.h \
	d:\data\refs\inc/\otref.h \
	d:\data\refs\inc/\object.h \
	d:\data\refs\inc/\otscoll.h \
	d:\data\refs\inc/\mycolls.h \
	d:\data\refs\inc/\otrefwnd.h \
	d:\data\src/re/regexp.h


RCONFOPT_DEP = d:\data\refs\inc/globals.h \
	d:\msvc\include\tchar.h \
	d:\data\refs\inc/\config.h \
	d:\data\refs\inc/\refs.h \
	d:\data\refs\inc/\otref.h \
	d:\data\refs\inc/\object.h \
	d:\data\refs\inc/\otscoll.h \
	d:\data\refs\inc/\mycolls.h \
	d:\data\refs\inc/\otrefwnd.h \
	d:\data\refs\inc/rconfopt.h


RCUTPAST_DEP = d:\data\refs\inc/globals.h \
	d:\msvc\include\tchar.h \
	d:\data\refs\inc/\config.h \
	d:\data\refs\inc/\refs.h \
	d:\data\refs\inc/\otref.h \
	d:\data\refs\inc/\object.h \
	d:\data\refs\inc/\otscoll.h \
	d:\data\refs\inc/\mycolls.h \
	d:\data\refs\inc/\otrefwnd.h \
	d:\data\refs\inc/rcutpast.h \
	d:\data\refs\inc/refpaint.h \
	d:\data\refs\rimpexp/rimpexp.h


REFABOUT_DEP = d:\data\refs\inc/globals.h \
	d:\msvc\include\tchar.h \
	d:\data\refs\inc/\config.h \
	d:\data\refs\inc/\refs.h \
	d:\data\refs\inc/\otref.h \
	d:\data\refs\inc/\object.h \
	d:\data\refs\inc/\otscoll.h \
	d:\data\refs\inc/\mycolls.h \
	d:\data\refs\inc/\otrefwnd.h \
	d:\data\refs\inc/refabout.h


REFBIBS_DEP = d:\data\refs\inc/globals.h \
	d:\msvc\include\tchar.h \
	d:\data\refs\inc/\config.h \
	d:\data\refs\inc/\refs.h \
	d:\data\refs\inc/\otref.h \
	d:\data\refs\inc/\object.h \
	d:\data\refs\inc/\otscoll.h \
	d:\data\refs\inc/\mycolls.h \
	d:\data\refs\inc/\otrefwnd.h \
	d:\data\refs\inc/refbibs.h \
	d:\data\refs\inc/reffont.h \
	d:\data\refs\rimpexp/rimpexp.h \
	d:\data\refs\inc/redit.h


REFFONT_DEP = d:\data\refs\inc/globals.h \
	d:\msvc\include\tchar.h \
	d:\data\refs\inc/\config.h \
	d:\data\refs\inc/\refs.h \
	d:\data\refs\inc/\otref.h \
	d:\data\refs\inc/\object.h \
	d:\data\refs\inc/\otscoll.h \
	d:\data\refs\inc/\mycolls.h \
	d:\data\refs\inc/\otrefwnd.h \
	d:\data\refs\inc/reffont.h \
	d:\data\refs\rimpexp/rimpexp.h


REFCHILD_DEP = d:\data\refs\inc/globals.h \
	d:\msvc\include\tchar.h \
	d:\data\refs\inc/\config.h \
	d:\data\refs\inc/\refs.h \
	d:\data\refs\inc/\otref.h \
	d:\data\refs\inc/\object.h \
	d:\data\refs\inc/\otscoll.h \
	d:\data\refs\inc/\mycolls.h \
	d:\data\refs\inc/\otrefwnd.h \
	d:\data\refs\inc/refchild.h \
	d:\data\refs\inc/rcutpast.h \
	d:\data\refs\inc/reffont.h \
	d:\data\refs\inc/rtoolbar.h \
	d:\data\refs\inc/refframe.h \
	d:\data\refs\inc/refpaint.h \
	d:\data\refs\inc/editdlg.h \
	d:\data\refs\inc/authdlg.h \
	d:\data\refs\inc/redit.h


REFFRAME_DEP = d:\data\refs\inc/globals.h \
	d:\msvc\include\tchar.h \
	d:\data\refs\inc/\config.h \
	d:\data\refs\inc/\refs.h \
	d:\data\refs\inc/\otref.h \
	d:\data\refs\inc/\object.h \
	d:\data\refs\inc/\otscoll.h \
	d:\data\refs\inc/\mycolls.h \
	d:\data\refs\inc/\otrefwnd.h \
	d:\data\refs\inc/rcutpast.h \
	d:\data\refs\inc/refabout.h \
	d:\data\refs\inc/rconfopt.h \
	d:\data\refs\inc/refbibs.h \
	d:\data\refs\inc/refframe.h \
	d:\data\refs\inc/refimp.h \
	d:\data\refs\inc/\imptfr.h \
	d:\data\refs\inc/refio.h \
	d:\data\refs\inc/refinopt.h \
	d:\data\refs\inc/reflopts.h \
	d:\data\refs\inc/refnag.h \
	d:\data\refs\inc/refpaint.h \
	d:\data\refs\inc/refprn.h \
	d:\data\refs\inc/rsetlang.h \
	d:\data\refs\inc/rsrtopt.h \
	d:\data\refs\inc/rsrchopt.h \
	d:\data\refs\inc/reffont.h \
	d:\data\refs\inc/editdlg.h \
	d:\data\refs\inc/authdlg.h \
	d:\data\refs\inc/redit.h \
	d:\data\refs\inc/status.h \
	d:\data\refs\inc/rtoolbar.h


REFIMP_DEP = d:\data\refs\inc/globals.h \
	d:\msvc\include\tchar.h \
	d:\data\refs\inc/\config.h \
	d:\data\refs\inc/\refs.h \
	d:\data\refs\inc/\otref.h \
	d:\data\refs\inc/\object.h \
	d:\data\refs\inc/\otscoll.h \
	d:\data\refs\inc/\mycolls.h \
	d:\data\refs\inc/\otrefwnd.h \
	d:\data\refs\inc/refio.h \
	d:\data\refs\inc/refimp.h \
	d:\data\refs\inc/\imptfr.h \
	d:\data\refs\rimpexp/rimpexp.h \
	d:\data\refs\inc/redit.h


REFINOPT_DEP = d:\data\refs\inc/globals.h \
	d:\msvc\include\tchar.h \
	d:\data\refs\inc/\config.h \
	d:\data\refs\inc/\refs.h \
	d:\data\refs\inc/\otref.h \
	d:\data\refs\inc/\object.h \
	d:\data\refs\inc/\otscoll.h \
	d:\data\refs\inc/\mycolls.h \
	d:\data\refs\inc/\otrefwnd.h \
	d:\data\refs\inc/refinopt.h


REFIO_DEP = d:\data\refs\inc/globals.h \
	d:\msvc\include\tchar.h \
	d:\data\refs\inc/\config.h \
	d:\data\refs\inc/\refs.h \
	d:\data\refs\inc/\otref.h \
	d:\data\refs\inc/\object.h \
	d:\data\refs\inc/\otscoll.h \
	d:\data\refs\inc/\mycolls.h \
	d:\data\refs\inc/\otrefwnd.h \
	d:\data\refs\inc/rcutpast.h \
	d:\data\refs\inc/refbibs.h \
	d:\data\refs\inc/refchild.h \
	d:\data\refs\inc/reffont.h \
	d:\data\refs\inc/refframe.h \
	d:\data\refs\inc/refio.h \
	d:\data\refs\rimpexp/rimpexp.h \
	d:\data\refs\inc/editdlg.h


REFLOPTS_DEP = d:\data\refs\inc/globals.h \
	d:\msvc\include\tchar.h \
	d:\data\refs\inc/\config.h \
	d:\data\refs\inc/\refs.h \
	d:\data\refs\inc/\otref.h \
	d:\data\refs\inc/\object.h \
	d:\data\refs\inc/\otscoll.h \
	d:\data\refs\inc/\mycolls.h \
	d:\data\refs\inc/\otrefwnd.h \
	d:\data\refs\inc/reflopts.h


REFNAG_DEP = d:\data\refs\inc/globals.h \
	d:\msvc\include\tchar.h \
	d:\data\refs\inc/\config.h \
	d:\data\refs\inc/\refs.h \
	d:\data\refs\inc/\otref.h \
	d:\data\refs\inc/\object.h \
	d:\data\refs\inc/\otscoll.h \
	d:\data\refs\inc/\mycolls.h \
	d:\data\refs\inc/\otrefwnd.h \
	d:\data\refs\inc/refnag.h \
	d:\data\refs\rimpexp/rimpexp.h \
	d:\data\refs\inc/rsetlang.h


REFPAINT_DEP = d:\data\refs\inc/globals.h \
	d:\msvc\include\tchar.h \
	d:\data\refs\inc/\config.h \
	d:\data\refs\inc/\refs.h \
	d:\data\refs\inc/\otref.h \
	d:\data\refs\inc/\object.h \
	d:\data\refs\inc/\otscoll.h \
	d:\data\refs\inc/\mycolls.h \
	d:\data\refs\inc/\otrefwnd.h \
	d:\data\refs\inc/status.h


REFPRN_DEP = d:\data\refs\inc/globals.h \
	d:\msvc\include\tchar.h \
	d:\data\refs\inc/\config.h \
	d:\data\refs\inc/\refs.h \
	d:\data\refs\inc/\otref.h \
	d:\data\refs\inc/\object.h \
	d:\data\refs\inc/\otscoll.h \
	d:\data\refs\inc/\mycolls.h \
	d:\data\refs\inc/\otrefwnd.h \
	d:\data\refs\inc/rcutpast.h \
	d:\data\refs\inc/reffont.h \
	d:\data\refs\inc/refprn.h \
	d:\data\refs\inc/redit.h


REFS_DEP = d:\data\refs\inc/globals.h \
	d:\msvc\include\tchar.h \
	d:\data\refs\inc/\config.h \
	d:\data\refs\inc/\refs.h \
	d:\data\refs\inc/\otref.h \
	d:\data\refs\inc/\object.h \
	d:\data\refs\inc/\otscoll.h \
	d:\data\refs\inc/\mycolls.h \
	d:\data\refs\inc/\otrefwnd.h \
	d:\data\refs\inc/refabout.h \
	d:\data\refs\rimpexp/rimpexp.h \
	d:\data\refs\inc/refio.h \
	d:\data\refs\inc/editdlg.h \
	d:\data\refs\inc/refnag.h \
	d:\data\refs\inc/rsetlang.h


RSETLANG_DEP = d:\data\refs\inc/globals.h \
	d:\msvc\include\tchar.h \
	d:\data\refs\inc/\config.h \
	d:\data\refs\inc/\refs.h \
	d:\data\refs\inc/\otref.h \
	d:\data\refs\inc/\object.h \
	d:\data\refs\inc/\otscoll.h \
	d:\data\refs\inc/\mycolls.h \
	d:\data\refs\inc/\otrefwnd.h \
	d:\data\refs\inc/rsetlang.h \
	d:\data\refs\rimpexp/rimpexp.h \
	d:\data\refs\inc/editdlg.h


RSRCHOPT_DEP = d:\data\refs\inc/globals.h \
	d:\msvc\include\tchar.h \
	d:\data\refs\inc/\config.h \
	d:\data\refs\inc/\refs.h \
	d:\data\refs\inc/\otref.h \
	d:\data\refs\inc/\object.h \
	d:\data\refs\inc/\otscoll.h \
	d:\data\refs\inc/\mycolls.h \
	d:\data\refs\inc/\otrefwnd.h \
	d:\data\refs\inc/rsrchopt.h


RSRTOPT_DEP = d:\data\refs\inc/globals.h \
	d:\msvc\include\tchar.h \
	d:\data\refs\inc/\config.h \
	d:\data\refs\inc/\refs.h \
	d:\data\refs\inc/\otref.h \
	d:\data\refs\inc/\object.h \
	d:\data\refs\inc/\otscoll.h \
	d:\data\refs\inc/\mycolls.h \
	d:\data\refs\inc/\otrefwnd.h \
	d:\data\refs\inc/rsrtopt.h


REFS_RCDEP = d:\data\refs\inc/config.h \
	d:\data\refs\inc/refs.h \
	d:\data\refs\ferics.bmp \
	d:\data\refs\splash.dlg \
	d:\data\refs\gong.bmp \
	d:\data\refs\splash32.bmp \
	d:\data\refs\splash16.bmp \
	d:\data\refs\toolbar.bmp \
	d:\data\refs\bookmask.bmp \
	d:\data\refs\book.bmp \
	d:\data\refs\artmask.bmp \
	d:\data\refs\article.bmp \
	d:\data\refs\report.bmp \
	d:\data\refs\repmask.bmp \
	d:\data\refs\single.cur \
	d:\data\refs\multi.cur


AUTHDLG_DEP = d:\data\refs\inc/globals.h \
	d:\msvc\include\tchar.h \
	d:\data\refs\inc/\config.h \
	d:\data\refs\inc/\refs.h \
	d:\data\refs\inc/\otref.h \
	d:\data\refs\inc/\object.h \
	d:\data\refs\inc/\otscoll.h \
	d:\data\refs\inc/\mycolls.h \
	d:\data\refs\inc/\otrefwnd.h \
	d:\data\refs\inc/authdlg.h


EDITDLG_DEP = d:\data\refs\inc/globals.h \
	d:\msvc\include\tchar.h \
	d:\data\refs\inc/\config.h \
	d:\data\refs\inc/\refs.h \
	d:\data\refs\inc/\otref.h \
	d:\data\refs\inc/\object.h \
	d:\data\refs\inc/\otscoll.h \
	d:\data\refs\inc/\mycolls.h \
	d:\data\refs\inc/\otrefwnd.h \
	d:\data\refs\inc/reffont.h \
	d:\data\refs\inc/refprn.h \
	d:\data\refs\rimpexp/rimpexp.h \
	d:\data\refs\inc/rcutpast.h \
	d:\data\refs\inc/editdlg.h \
	d:\data\refs\inc/jlistdlg.h


JLISTDLG_DEP = d:\data\refs\inc/globals.h \
	d:\msvc\include\tchar.h \
	d:\data\refs\inc/\config.h \
	d:\data\refs\inc/\refs.h \
	d:\data\refs\inc/\otref.h \
	d:\data\refs\inc/\object.h \
	d:\data\refs\inc/\otscoll.h \
	d:\data\refs\inc/\mycolls.h \
	d:\data\refs\inc/\otrefwnd.h \
	d:\data\refs\rimpexp/rimpexp.h \
	d:\data\refs\inc/jlistdlg.h


all:	$(PROJ).EXE $(PROJ).BSC

GLOBALS.OBJ:	GLOBALS.CPP $(GLOBALS_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c GLOBALS.CPP

MYCOLLS.OBJ:	MYCOLLS.CPP $(MYCOLLS_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MYCOLLS.CPP

OBJECT.OBJ:	OBJECT.CPP $(OBJECT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c OBJECT.CPP

OTREF.OBJ:	OTREF.CPP $(OTREF_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c OTREF.CPP

OTREFWND.OBJ:	OTREFWND.CPP $(OTREFWND_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c OTREFWND.CPP

OTSCOLL.OBJ:	OTSCOLL.CPP $(OTSCOLL_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c OTSCOLL.CPP

RCONFOPT.OBJ:	RCONFOPT.CPP $(RCONFOPT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c RCONFOPT.CPP

RCUTPAST.OBJ:	RCUTPAST.CPP $(RCUTPAST_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c RCUTPAST.CPP

REFABOUT.OBJ:	REFABOUT.CPP $(REFABOUT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c REFABOUT.CPP

REFBIBS.OBJ:	REFBIBS.CPP $(REFBIBS_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c REFBIBS.CPP

REFFONT.OBJ:	REFFONT.CPP $(REFFONT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c REFFONT.CPP

REFCHILD.OBJ:	REFCHILD.CPP $(REFCHILD_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c REFCHILD.CPP

REFFRAME.OBJ:	REFFRAME.CPP $(REFFRAME_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c REFFRAME.CPP

REFIMP.OBJ:	REFIMP.CPP $(REFIMP_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c REFIMP.CPP

REFINOPT.OBJ:	REFINOPT.CPP $(REFINOPT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c REFINOPT.CPP

REFIO.OBJ:	REFIO.CPP $(REFIO_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c REFIO.CPP

REFLOPTS.OBJ:	REFLOPTS.CPP $(REFLOPTS_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c REFLOPTS.CPP

REFNAG.OBJ:	REFNAG.CPP $(REFNAG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c REFNAG.CPP

REFPAINT.OBJ:	REFPAINT.CPP $(REFPAINT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c REFPAINT.CPP

REFPRN.OBJ:	REFPRN.CPP $(REFPRN_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c REFPRN.CPP

REFS.OBJ:	REFS.CPP $(REFS_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c REFS.CPP

RSETLANG.OBJ:	RSETLANG.CPP $(RSETLANG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c RSETLANG.CPP

RSRCHOPT.OBJ:	RSRCHOPT.CPP $(RSRCHOPT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c RSRCHOPT.CPP

RSRTOPT.OBJ:	RSRTOPT.CPP $(RSRTOPT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c RSRTOPT.CPP

REFS.RES:	REFS.RC $(REFS_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r REFS.RC

AUTHDLG.OBJ:	AUTHDLG.CPP $(AUTHDLG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c AUTHDLG.CPP

EDITDLG.OBJ:	EDITDLG.CPP $(EDITDLG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EDITDLG.CPP

JLISTDLG.OBJ:	JLISTDLG.CPP $(JLISTDLG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c JLISTDLG.CPP


$(PROJ).EXE::	REFS.RES

$(PROJ).EXE::	GLOBALS.OBJ MYCOLLS.OBJ OBJECT.OBJ OTREF.OBJ OTREFWND.OBJ OTSCOLL.OBJ \
	RCONFOPT.OBJ RCUTPAST.OBJ REFABOUT.OBJ REFBIBS.OBJ REFFONT.OBJ REFCHILD.OBJ REFFRAME.OBJ \
	REFIMP.OBJ REFINOPT.OBJ REFIO.OBJ REFLOPTS.OBJ REFNAG.OBJ REFPAINT.OBJ REFPRN.OBJ \
	REFS.OBJ RSETLANG.OBJ RSRCHOPT.OBJ RSRTOPT.OBJ AUTHDLG.OBJ EDITDLG.OBJ JLISTDLG.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
GLOBALS.OBJ +
MYCOLLS.OBJ +
OBJECT.OBJ +
OTREF.OBJ +
OTREFWND.OBJ +
OTSCOLL.OBJ +
RCONFOPT.OBJ +
RCUTPAST.OBJ +
REFABOUT.OBJ +
REFBIBS.OBJ +
REFFONT.OBJ +
REFCHILD.OBJ +
REFFRAME.OBJ +
REFIMP.OBJ +
REFINOPT.OBJ +
REFIO.OBJ +
REFLOPTS.OBJ +
REFNAG.OBJ +
REFPAINT.OBJ +
REFPRN.OBJ +
REFS.OBJ +
RSETLANG.OBJ +
RSRCHOPT.OBJ +
RSRTOPT.OBJ +
AUTHDLG.OBJ +
EDITDLG.OBJ +
JLISTDLG.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
d:\msvc\lib\+
RIMPEXP.LIB+
..\CTL3D\OBJ16\DLL\CTL3D.LIB+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) REFS.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	REFS.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) REFS.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
