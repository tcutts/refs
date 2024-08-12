# Microsoft Visual C++ generated build script - Do not modify

PROJ = FERIC
DEBUG = 0
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG /dFERIC /dCC_TOOLBAR 
R_RCDEFINES = /dNDEBUG /dFERIC /dMODAL_EDIT /dCC_TOOLBAR
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
CFLAGS_D_WEXE = /nologo /G2 /W2 /Gf /Zi /AL /YX"globals.h" /Od /D "_DEBUG" /D "FERIC" /D "FERIC" /D "STRICT" /D "CC_TOOLBAR" /FR /GA /Fd"REFS.PDB"        /Fp"REFS.PCH"
CFLAGS_R_WEXE = /nologo /f- /Gs /G2 /W0 /Gf /AL /Gt65500 /YX"globals.h" /O2 /Ob1 /D "NDEBUG" /D "FERIC" /D "STRICT" /D "CC_TOOLBAR" /GA /Fp"REFS.PCH"
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /CO  
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /PACKD:65500 /ALIGN:16 /ONERROR:NOEXE  
LIBS_D_WEXE = llibcew oldnames libw commdlg.lib mmsystem.lib shell.lib ver.lib 
LIBS_R_WEXE = llibcew oldnames libw commdlg.lib mmsystem.lib shell.lib ver.lib 
RCFLAGS = /nologo 
RESFLAGS = /nologo 
RUNFLAGS = 
DEFFILE = FERIC.DEF
OBJS_EXT = 
LIBS_EXT = ..\..\MSVC\LIB\CTL3D.LIB RIMPEXP.LIB 
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
		EDITDLG.SBR \
		AUTHDLG.SBR \
		JLISTDLG.SBR


CTL3D_DEP = 

RIMPEXP_DEP = 

GLOBALS_DEP = d:\data\refs\globals.h \
	d:\msvc\include\ctl3d.h \
	d:\msvc\include\commctrl.h \
	d:\data\refs\refs.h \
	d:\data\refs\otref.h \
	d:\data\refs\object.h \
	d:\data\refs\otscoll.h \
	d:\data\refs\mycolls.h \
	d:\data\refs\otrefwnd.h \
	d:\data\refs\refimp.h \
	d:\data\refs\imptfr.h


MYCOLLS_DEP = d:\data\refs\globals.h \
	d:\msvc\include\ctl3d.h \
	d:\msvc\include\commctrl.h \
	d:\data\refs\refs.h \
	d:\data\refs\otref.h \
	d:\data\refs\object.h \
	d:\data\refs\otscoll.h \
	d:\data\refs\mycolls.h \
	d:\data\refs\otrefwnd.h


OBJECT_DEP = d:\data\refs\object.h


OTREF_DEP = d:\data\refs\globals.h \
	d:\msvc\include\ctl3d.h \
	d:\msvc\include\commctrl.h \
	d:\data\refs\refs.h \
	d:\data\refs\otref.h \
	d:\data\refs\object.h \
	d:\data\refs\otscoll.h \
	d:\data\refs\mycolls.h \
	d:\data\refs\otrefwnd.h \
	d:\data\refs\refpaint.h \
	d:\data\refs\rimpexp.h \
	d:\data\refs\editdlg.h


OTREFWND_DEP = d:\data\refs\globals.h \
	d:\msvc\include\ctl3d.h \
	d:\msvc\include\commctrl.h \
	d:\data\refs\refs.h \
	d:\data\refs\otref.h \
	d:\data\refs\object.h \
	d:\data\refs\otscoll.h \
	d:\data\refs\mycolls.h \
	d:\data\refs\otrefwnd.h \
	d:\data\refs\reffont.h \
	d:\data\refs\refimp.h \
	d:\data\refs\imptfr.h \
	d:\data\refs\refpaint.h \
	d:\data\refs\rtoolbar.h \
	d:\data\refs\refframe.h


OTSCOLL_DEP = d:\data\refs\globals.h \
	d:\msvc\include\ctl3d.h \
	d:\msvc\include\commctrl.h \
	d:\data\refs\refs.h \
	d:\data\refs\otref.h \
	d:\data\refs\object.h \
	d:\data\refs\otscoll.h \
	d:\data\refs\mycolls.h \
	d:\data\refs\otrefwnd.h


RCONFOPT_DEP = d:\data\refs\globals.h \
	d:\msvc\include\ctl3d.h \
	d:\msvc\include\commctrl.h \
	d:\data\refs\refs.h \
	d:\data\refs\otref.h \
	d:\data\refs\object.h \
	d:\data\refs\otscoll.h \
	d:\data\refs\mycolls.h \
	d:\data\refs\otrefwnd.h \
	d:\data\refs\rconfopt.h


RCUTPAST_DEP = d:\data\refs\globals.h \
	d:\msvc\include\ctl3d.h \
	d:\msvc\include\commctrl.h \
	d:\data\refs\refs.h \
	d:\data\refs\otref.h \
	d:\data\refs\object.h \
	d:\data\refs\otscoll.h \
	d:\data\refs\mycolls.h \
	d:\data\refs\otrefwnd.h \
	d:\data\refs\rcutpast.h \
	d:\data\refs\refpaint.h \
	d:\data\refs\rimpexp.h


REFABOUT_DEP = d:\data\refs\globals.h \
	d:\msvc\include\ctl3d.h \
	d:\msvc\include\commctrl.h \
	d:\data\refs\refs.h \
	d:\data\refs\otref.h \
	d:\data\refs\object.h \
	d:\data\refs\otscoll.h \
	d:\data\refs\mycolls.h \
	d:\data\refs\otrefwnd.h \
	d:\data\refs\refabout.h


REFBIBS_DEP = d:\data\refs\globals.h \
	d:\msvc\include\ctl3d.h \
	d:\msvc\include\commctrl.h \
	d:\data\refs\refs.h \
	d:\data\refs\otref.h \
	d:\data\refs\object.h \
	d:\data\refs\otscoll.h \
	d:\data\refs\mycolls.h \
	d:\data\refs\otrefwnd.h \
	d:\data\refs\refbibs.h \
	d:\data\refs\reffont.h \
	d:\data\refs\rimpexp.h


REFFONT_DEP = d:\data\refs\globals.h \
	d:\msvc\include\ctl3d.h \
	d:\msvc\include\commctrl.h \
	d:\data\refs\refs.h \
	d:\data\refs\otref.h \
	d:\data\refs\object.h \
	d:\data\refs\otscoll.h \
	d:\data\refs\mycolls.h \
	d:\data\refs\otrefwnd.h \
	d:\data\refs\reffont.h \
	d:\data\refs\rimpexp.h


REFCHILD_DEP = d:\data\refs\globals.h \
	d:\msvc\include\ctl3d.h \
	d:\msvc\include\commctrl.h \
	d:\data\refs\refs.h \
	d:\data\refs\otref.h \
	d:\data\refs\object.h \
	d:\data\refs\otscoll.h \
	d:\data\refs\mycolls.h \
	d:\data\refs\otrefwnd.h \
	d:\data\refs\refchild.h \
	d:\data\refs\rcutpast.h \
	d:\data\refs\reffont.h \
	d:\data\refs\rtoolbar.h \
	d:\data\refs\refframe.h \
	d:\data\refs\refpaint.h \
	d:\data\refs\editdlg.h


REFFRAME_DEP = d:\data\refs\globals.h \
	d:\msvc\include\ctl3d.h \
	d:\msvc\include\commctrl.h \
	d:\data\refs\refs.h \
	d:\data\refs\otref.h \
	d:\data\refs\object.h \
	d:\data\refs\otscoll.h \
	d:\data\refs\mycolls.h \
	d:\data\refs\otrefwnd.h \
	d:\data\refs\rcutpast.h \
	d:\data\refs\refabout.h \
	d:\data\refs\rconfopt.h \
	d:\data\refs\refbibs.h \
	d:\data\refs\refframe.h \
	d:\data\refs\refimp.h \
	d:\data\refs\imptfr.h \
	d:\data\refs\refio.h \
	d:\data\refs\refinopt.h \
	d:\data\refs\reflopts.h \
	d:\data\refs\refnag.h \
	d:\data\refs\refpaint.h \
	d:\data\refs\refprn.h \
	d:\data\refs\rsetlang.h \
	d:\data\refs\rsrtopt.h \
	d:\data\refs\rsrchopt.h \
	d:\data\refs\reffont.h \
	d:\data\refs\editdlg.h \
	d:\data\refs\status.h \
	d:\data\refs\rtoolbar.h


REFIMP_DEP = d:\data\refs\globals.h \
	d:\msvc\include\ctl3d.h \
	d:\msvc\include\commctrl.h \
	d:\data\refs\refs.h \
	d:\data\refs\otref.h \
	d:\data\refs\object.h \
	d:\data\refs\otscoll.h \
	d:\data\refs\mycolls.h \
	d:\data\refs\otrefwnd.h \
	d:\data\refs\refio.h \
	d:\data\refs\refimp.h \
	d:\data\refs\imptfr.h \
	d:\data\refs\rimpexp.h


REFINOPT_DEP = d:\data\refs\globals.h \
	d:\msvc\include\ctl3d.h \
	d:\msvc\include\commctrl.h \
	d:\data\refs\refs.h \
	d:\data\refs\otref.h \
	d:\data\refs\object.h \
	d:\data\refs\otscoll.h \
	d:\data\refs\mycolls.h \
	d:\data\refs\otrefwnd.h \
	d:\data\refs\refinopt.h


REFIO_DEP = d:\data\refs\globals.h \
	d:\msvc\include\ctl3d.h \
	d:\msvc\include\commctrl.h \
	d:\data\refs\refs.h \
	d:\data\refs\otref.h \
	d:\data\refs\object.h \
	d:\data\refs\otscoll.h \
	d:\data\refs\mycolls.h \
	d:\data\refs\otrefwnd.h \
	d:\data\refs\rcutpast.h \
	d:\data\refs\refbibs.h \
	d:\data\refs\refchild.h \
	d:\data\refs\reffont.h \
	d:\data\refs\refframe.h \
	d:\data\refs\refio.h \
	d:\data\refs\rimpexp.h


REFLOPTS_DEP = d:\data\refs\globals.h \
	d:\msvc\include\ctl3d.h \
	d:\msvc\include\commctrl.h \
	d:\data\refs\refs.h \
	d:\data\refs\otref.h \
	d:\data\refs\object.h \
	d:\data\refs\otscoll.h \
	d:\data\refs\mycolls.h \
	d:\data\refs\otrefwnd.h \
	d:\data\refs\reflopts.h


REFNAG_DEP = d:\data\refs\globals.h \
	d:\msvc\include\ctl3d.h \
	d:\msvc\include\commctrl.h \
	d:\data\refs\refs.h \
	d:\data\refs\otref.h \
	d:\data\refs\object.h \
	d:\data\refs\otscoll.h \
	d:\data\refs\mycolls.h \
	d:\data\refs\otrefwnd.h \
	d:\data\refs\refnag.h \
	d:\data\refs\rimpexp.h


REFPAINT_DEP = d:\data\refs\globals.h \
	d:\msvc\include\ctl3d.h \
	d:\msvc\include\commctrl.h \
	d:\data\refs\refs.h \
	d:\data\refs\otref.h \
	d:\data\refs\object.h \
	d:\data\refs\otscoll.h \
	d:\data\refs\mycolls.h \
	d:\data\refs\otrefwnd.h \
	d:\data\refs\status.h


REFPRN_DEP = d:\data\refs\globals.h \
	d:\msvc\include\ctl3d.h \
	d:\msvc\include\commctrl.h \
	d:\data\refs\refs.h \
	d:\data\refs\otref.h \
	d:\data\refs\object.h \
	d:\data\refs\otscoll.h \
	d:\data\refs\mycolls.h \
	d:\data\refs\otrefwnd.h \
	d:\data\refs\rcutpast.h \
	d:\data\refs\reffont.h \
	d:\data\refs\refprn.h


REFS_DEP = d:\data\refs\globals.h \
	d:\msvc\include\ctl3d.h \
	d:\msvc\include\commctrl.h \
	d:\data\refs\refs.h \
	d:\data\refs\otref.h \
	d:\data\refs\object.h \
	d:\data\refs\otscoll.h \
	d:\data\refs\mycolls.h \
	d:\data\refs\otrefwnd.h \
	d:\data\refs\refabout.h \
	d:\data\refs\rimpexp.h \
	d:\data\refs\refio.h \
	d:\data\refs\refnag.h \
	d:\data\refs\rsetlang.h


RSETLANG_DEP = d:\data\refs\globals.h \
	d:\msvc\include\ctl3d.h \
	d:\msvc\include\commctrl.h \
	d:\data\refs\refs.h \
	d:\data\refs\otref.h \
	d:\data\refs\object.h \
	d:\data\refs\otscoll.h \
	d:\data\refs\mycolls.h \
	d:\data\refs\otrefwnd.h \
	d:\data\refs\rsetlang.h \
	d:\data\refs\rimpexp.h


RSRCHOPT_DEP = d:\data\refs\globals.h \
	d:\msvc\include\ctl3d.h \
	d:\msvc\include\commctrl.h \
	d:\data\refs\refs.h \
	d:\data\refs\otref.h \
	d:\data\refs\object.h \
	d:\data\refs\otscoll.h \
	d:\data\refs\mycolls.h \
	d:\data\refs\otrefwnd.h \
	d:\data\refs\rsrchopt.h


RSRTOPT_DEP = d:\data\refs\globals.h \
	d:\msvc\include\ctl3d.h \
	d:\msvc\include\commctrl.h \
	d:\data\refs\refs.h \
	d:\data\refs\otref.h \
	d:\data\refs\object.h \
	d:\data\refs\otscoll.h \
	d:\data\refs\mycolls.h \
	d:\data\refs\otrefwnd.h \
	d:\data\refs\rsrtopt.h


REFS_RCDEP = d:\data\refs\refs.h \
	d:\data\refs\ferics.bmp \
	d:\data\refs\feric.dlg \
	d:\data\refs\splash.dlg \
	d:\data\refs\gong.bmp \
	d:\data\refs\splash95.bmp \
	d:\data\refs\splashnt.bmp \
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


EDITDLG_DEP = d:\data\refs\globals.h \
	d:\msvc\include\ctl3d.h \
	d:\msvc\include\commctrl.h \
	d:\data\refs\refs.h \
	d:\data\refs\otref.h \
	d:\data\refs\object.h \
	d:\data\refs\otscoll.h \
	d:\data\refs\mycolls.h \
	d:\data\refs\otrefwnd.h \
	d:\data\refs\reffont.h \
	d:\data\refs\refprn.h \
	d:\data\refs\rimpexp.h \
	d:\data\refs\rcutpast.h \
	d:\data\refs\editdlg.h


AUTHDLG_DEP = 

JLISTDLG_DEP = 

all:	$(PROJ).EXE

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

EDITDLG.OBJ:	EDITDLG.CPP $(EDITDLG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EDITDLG.CPP

AUTHDLG.OBJ:	AUTHDLG.CPP $(AUTHDLG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c AUTHDLG.CPP

JLISTDLG.OBJ:	JLISTDLG.CPP $(JLISTDLG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c JLISTDLG.CPP


$(PROJ).EXE::	REFS.RES

$(PROJ).EXE::	GLOBALS.OBJ MYCOLLS.OBJ OBJECT.OBJ OTREF.OBJ OTREFWND.OBJ OTSCOLL.OBJ \
	RCONFOPT.OBJ RCUTPAST.OBJ REFABOUT.OBJ REFBIBS.OBJ REFFONT.OBJ REFCHILD.OBJ REFFRAME.OBJ \
	REFIMP.OBJ REFINOPT.OBJ REFIO.OBJ REFLOPTS.OBJ REFNAG.OBJ REFPAINT.OBJ REFPRN.OBJ \
	REFS.OBJ RSETLANG.OBJ RSRCHOPT.OBJ RSRTOPT.OBJ EDITDLG.OBJ AUTHDLG.OBJ JLISTDLG.OBJ $(OBJS_EXT) $(DEFFILE)
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
EDITDLG.OBJ +
AUTHDLG.OBJ +
JLISTDLG.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
D:\MSVC\LIB\+
D:\MSVC\MFC\LIB\+
..\..\MSVC\LIB\CTL3D.LIB+
RIMPEXP.LIB+
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
