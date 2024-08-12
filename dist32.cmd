pushd d:\data\refs
rem ...edit 32-bit text files...
edit install\dist32\disk1\readme.txt

rem ...copy 32 bit bits...
echo 32-bit version files...
copy bin32\REFS32.EXE			install\dist32\data\95
copy Help\REFS32.HLP            	install\dist32\data\HELP
copy Help\REFS32.CNT            	install\dist32\data\HELP
copy bin32\REFEN.DLL         		install\dist32\data\COMMON
copy bin32\REFER.FLT         		install\dist32\data\COMMON
copy bin32\RIMPEXP.DLL       		install\dist32\data\COMMON
copy ..\src\re\winrel\regexp32.dll	install\dist32\data\COMMON
copy bin32\*.FLT             		install\dist32\data\FILTERS
del                             	install\dist32\data\FILTERS\refer.flt

del install\dist32\data\LANG\*

if x%2==x goto nolangs2
copy bin32\REFDEU.DLL        install\dist32\data\LANG
copy bin32\REFPO.DLL         install\dist32\data\LANG
copy bin32\REFJPN.DLL         install\dist32\data\LANG
copy bin32\REFSU32.DLL         install\dist32\data\LANG

:nolangs2

rem ... copy the RDK files...

del /s /q                       install\dist32\data\RDK
xcopy /s rdk\*.*                install\dist32\data\RDK

rem ...compress 32 bit data files...
pushd install\dist32
del data\data.z
f:\installshield\program\icomp -i data\*.* data\data.z
copy data\data.z disk1
del data\data.z
pushd setup
notepad setup.rul

if x%2==x goto nolangs3
f:\installshield\program\compile -DLANGS setup.rul
goto nolangs4

:nolangs3
f:\installshield\program\compile setup.rul

:nolangs4
copy setup.ins ..\disk1

rem ... compile packing list ...
f:\installshield\program\packlist setup.lst
copy setup.pkg ..\disk1

popd
popd

rem ... package it all up ...
pkzip install\7832-%1.ZIP -prex install\dist32\disk1\*.*
popd
