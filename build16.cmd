call d:\msvc\bin\msvcvars

rem ...build main program...

choice /tN,5 Build 16-bit Standard help file

if errorlevel 2 goto nohelp

pushd help
d:\msvc\bin\hc31 refs.hpj
popd

:nohelp

choice /tY,5 Build 16-bit RIMPEXP and REFEN

if errorlevel 2 goto main

pushd rimpexp
nmake /nologo /a /f rimpexp.mak DEBUG=0
cd ..\languages\en
nmake /nologo /a /f refen.mak DEBUG=0
popd

:main

choice /tY,5 Build 16-bit standard executable

if errorlevel 2 goto feric

nmake /nologo /a /f refs.mak DEBUG=0

:feric

choice /tN,5 Build 16-bit FERIC help file

if errorlevel 2 goto nohelp2

pushd help
d:\msvc\bin\hc31 feric.hpj
popd

:nohelp2

choice /tY,5 Build FERIC 16-bit executable

if errorlevel 2 goto filters

nmake /nologo /f /a feric.mak DEBUG=0

:filters

choice /tY,5 Build 16-bit import filters

if errorlevel 2 goto langs

rem ...build filters...
pushd filters\bids
nmake /nologo /f bids.mak DEBUG=0
cd ..\refer
nmake /nologo /f refer.mak DEBUG=0
cd..\medline
nmake /nologo /f medline.mak DEBUG=0
popd

:langs

if x%2==x goto nolangs

rem ...build language libraries...

choice /tY,5 Build language libraries

if errorlevel 2 goto nolangs

pushd languages\de
nmake /nologo /f refdeu.mak DEBUG=0
cd ..\po
nmake /nologo /f refpo.mak DEBUG=0
cd ..\jpn
nmake /nologo /f refjpn.mak DEBUG=0
cd ..\su
nmake /nologo /f refsu.mak DEBUG=0
popd

:nolangs

rem ...edit 16-bit text files...
edit install\dist16\readme.txt
edit install\dist16\install.ini

copy install\dist16\readme.txt          install\FERIC
copy install\dist32\data\readme.wri     install\dist16

rem ...copy 16 bit bits...

choice /tY,5 Build FERIC distribution

if errorlevel 2 goto nonly

echo Feric files...
d:\msvc\bin\rc -31 -t -x -id:\msvc\include -dFERIC refs.rc feric.exe

copy FERIC.EXE          install\feric\REFS.EXE
copy RIMPEXP.DLL        install\FERIC
copy Help\FERIC.HLP     install\FERIC\REFS.HLP
copy REFER.DLL          install\FERIC\REFER.FLT
copy REFEN.DLL          install\FERIC

pkzip -ex install\feric%1.zip install\feric\*.*

:nonly

echo 16-bit standard version files...
copy REFS.EXE           install\dist16
copy Help\REFS.HLP      install\dist16
copy MEDLINE.DLL        install\dist16\MEDLINE.FLT
copy BIDS.DLL           install\dist16\BIDS.FLT
copy REFER.DLL          install\dist16\REFER.FLT
copy RIMPEXP.DLL        install\dist16
copy REFEN.DLL          install\dist16

del  install\dist16\refdeu.dll
if x%wlangs%==x goto nolangs2
copy REFDEU.DLL         install\dist16
copy REFPO.DLL          install\dist16
copy REFSU.DLL          install\dist16
copy REFES.DLL          install\dist16
copy REFJPN.DLL          install\dist16
:nolangs2

rem ...start making 16-bit distributions...

pkzip -ex install\78%1.zip install\dist16\*.*

echo RTH files...
copy refs.exe                   install\rth
copy help\refs.hlp              install\rth
copy install\feric\*.dll        install\rth
copy install\feric\refs.ini     install\rth
copy install\feric\refer.flt    install\rth
copy install\feric\install.exe  install\rth

d:\msvc\bin\rc -31 -t -x -id:\msvc\include -dSPLASH -dGONG refs.rc install\rth\refs.exe

