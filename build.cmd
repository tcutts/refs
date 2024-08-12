@echo off

if x%1==x goto badexit

set wlangs=y

choice Do you want languages to be included

if errorlevel 2 set wlangs=

if x%wlangs% == x goto rep1

Echo Language libraries ARE being included.
goto rep2
:rep1
Echo No language libraries being included.
:rep2

del install\*.ZIP

start /max /wait write install\dist32\data\readme.wri

cmd /c build16.cmd %1 %wlangs%

call dist32.cmd %1 %wlangs%

call rdk.cmd

rem ... map files ...
mkdir maps\%1
copy *.map maps\%1
copy Win95_Re\*.map maps\%1

call inst32.cmd %1 %wlangs%

call build32.cmd %1 %wlangs%

choice /tN,10 Do you want the distributions sent to chiark

if errorlevel 2 goto exit

rem ... send the distributions to chiark ...
echo Sending to chiark...
rcp -b install\*.ZIP chiark.chu.cam.ac.uk.timc:
echo Putting into chiark ftp area...
rsh chiark.chu.cam.ac.uk -l timc update_refs %1
goto exit

:badexit
echo What patch level is this?
echo "Usage:  build <patchlevel> [anything]"
echo .
echo If there is a second parameter, language support will
echo be included.  The contents of the parameter are unimportant.
:exit
echo Finished.
