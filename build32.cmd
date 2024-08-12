pushd d:\data\refs

rem ...build main program...

choice /tN,10 Build 32-bit help file?

if errorlevel 2 goto nohelp

pushd help
f:\help\hcw
popd

:nohelp

choice /tY,10 Build 32-bit version

if errorlevel 2 goto filters

pushd ..\src\re
nmake /nologo -f regexp32.mak CFG="Win32 Release"
popd 

pushd rimpexp
nmake /nologo /f rimpexp32.mak CFG="Win32 Release"
popd

pushd filters\refer
nmake /nologo /f refer32.mak CFG="Win32 Release"
popd

nmake /nologo /f refs32.mak CFG="Win95 Release"

pushd languages\en
nmake /nologo /f refen32.mak CFG="Win32 Release"
popd

rem ...build import filters...

:filters

choice /tY,10 Build 32-bit filters

if errorlevel 2 goto langs

pushd filters
pushd bids
nmake /nologo /f bids32.mak CFG="Win32 Release"
popd
pushd medline
nmake /nologo /f medline32.mak CFG="Win32 Release"
popd
pushd procite
nmake /nologo /f procite32.mak CFG="Win32 Release"
popd
popd

rem ...build language libraries...

:langs

if x%2==x goto nolangs1

choice /tY,10 Build 32-bit language libraries

if errorlevel 2 goto nolangs1

pushd languages
pushd de
nmake /nologo /f refdeu32.mak CFG="Win32 Release"
popd
pushd po
nmake /nologo /f refpo32.mak CFG="Win32 Release"
popd
pushd jpn
nmake /nologo /f refjpn32.mak CFG="Win32 Release"
popd
REM pushd sp
REM nmake /nologo /f refes32.mak CFG="Win32 Release"
REM popd
pushd su
nmake /nologo /f refsu32.mak CFG="Win32 Release"
popd
popd

:nolangs1

popd
