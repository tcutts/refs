pushd d:\data\refs
d:\msvc\bin\rc -31 renglish.rc refen.dll
nmake -Frefen32.mak CFG="Win32 Release"
popd