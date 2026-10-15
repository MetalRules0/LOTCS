@echo off
title Power3D build script
echo Power3D build process START!
echo Cleaning files...
del /q build.log power3d.obj power3d.dll power3d.exp power3d.lib power3d.a rsrc.res >nul 2>&1
pause
echo.
echo.

echo Assembling source...
C:\masm32\bin\rc /r rsrc.rc
C:\masm32\bin\ml /c /coff /Cp /Zi power3d.asm
echo.
echo.

if NOT exist power3d.def (
    echo Build failed.
    goto leave
)

echo Linking binaries...
C:\masm32\bin\link /DEBUG /SUBSYSTEM:WINDOWS /DLL /DEF:power3d.def power3d.obj rsrc.res
echo.
echo.


if NOT exist power3d.dll (
    echo Build failed.
    goto leave
)

echo P3D build success!

:leave
echo Cleaning intermediary files...
del /q build.log power3d.obj power3d.exp rsrc.res
echo Press any key to exit...
pause>nul
