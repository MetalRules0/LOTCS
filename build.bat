@echo off
title LOTCS Build

:: Install: MSVC, MASM SDK
:: PLACE VCVARSALL HERE!!!
call "C:\Path\To\vcvarsall.bat" x86

cls
rmdir /s /q bin
md bin

pushd P3D
del /q *.log *.err *.obj *.dll *.exp *.lib *.a *.res >nul 2>&1
C:\masm32\bin\rc /r rsrc.rc
C:\masm32\bin\ml /nologo /c /coff /Cp /Zi power3d.asm
C:\masm32\bin\link /nologo /DEBUG /SUBSYSTEM:WINDOWS /DLL /DEF:power3d.def power3d.obj rsrc.res
del /q *.log *.err *.obj *.exp *.a *.res >nul 2>&1
popd

cl /nologo /Od /Zi /arch:IA32 main.c camera.c player.c collide.c P3D/power3d.lib /Fe:bin\LOTCS.EXE /link /DEBUG

del /q P3D/power3d.lib
move P3D/power3d.dll bin/Power3D.dll
move P3D/power3d.ilk bin/power3d.ilk
move P3D/power3d.pdb bin/power3d.pdb