@echo off
pushd d:\data\refs
echo Filter source...
pushd filters\refer
for %%f in (refer.c refer.def refer.h refer.rc refer.mak refer32.mak) do copy %%f ..\..\rdk\filters\refer
popd

echo Filter includes...
for %%f in (rimpexp\rimpexp.h inc\imptfr.h) do copy %%f rdk\filters\c

echo Lib16...
copy rimpexp.lib rdk\filters\c\lib16\rimpexp.lib

echo Lib32...
copy win95_re\rimpexp32.lib rdk\filters\c\lib32\rimpexp.lib

REM  Now the language stuff

echo Language includes...
copy inc\refs.h rdk\language
copy inc\config.h rdk\language

echo Language source...
copy languages\refen.c rdk\language
copy languages\en\*.rc rdk\language

pkzip -Prex install\rdk79.zip rdk\*.*
popd