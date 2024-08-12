@echo off

rem ... copy the RDK files...

del /s                          install\dist32\data\RDK
xcopy /s rdk\*.*                install\dist32\data\RDK

rem ...compress 32 bit data files...
pushd d:\data\refs
cd install\dist32
del data\data.z

f:\mstools\installshield\program\icomp -i data\*.* data\data.z
copy data\data.z disk1
del data\data.z
popd

rem ... compile setup rulefile ...
pushd d:\data\refs\install\dist32\setup

notepad setup.rul

if x%2==x goto nolangs3
f:\mstools\installshield\program\compile -DLANGS setup.rul
goto nolangs4

:nolangs3
f:\mstools\installshield\program\compile setup.rul

:nolangs4
copy setup.ins ..\disk1

rem ... compile packing list ...
f:\mstools\installshield\program\packlist setup.lst
copy setup.pkg ..\disk1

popd
