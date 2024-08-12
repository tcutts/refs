@echo off

if x%1==x goto badexit

REM If %2 contains anything, we want languages in the distributions.

if x%2==x goto rep1
Echo Language libraries ARE being included.
goto rep2
:rep1
Echo No language libraries being included.
:rep2

del install\7832*.ZIP

call rdk.cmd

call build32.cmd %1 %2

rem ... map files ...
copy WinRel\*.map maps\%1
copy Win95_Re\*.map maps\%1

start /max /wait c:\windows\write install\dist32\data\readme.wri

call dist32.cmd %1 %2

rem ... send the distributions to chiark ...
echo
echo Sending to chiark...
echo rcp -b install\7832*.ZIP chiark.chu.cam.ac.uk.timc:
echo
echo Putting into chiark ftp area...
echo rsh chiark.chu.cam.ac.uk -l timc update_refs %1
echo
echo Finished.
echo
goto exit

:badexit
echo What patch level is this?
echo Usage:  build <patchlevel> [anything]
echo
echo If there is a second parameter, language support will
echo be included.  The contents of the parameter are unimportant.
:exit