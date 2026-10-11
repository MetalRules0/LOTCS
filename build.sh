#!/usr/bin/env bash
#Install: WINE, GCC, MinGW-GCC
#Install to default WINE prefix: MASM SDK
#And obviously, make sure this file is executable...

clear
rm bin/*
rmdir bin
mkdir bin

cd P3D
echo | WINEDEBUG=-all wine makedll.bat
i686-w64-mingw32-dlltool -d power3d.def -l power3d.a

cd ..
i686-w64-mingw32-gcc -std=c99 -march=i586 -Os -Wall -Wextra -Wpedantic main.c P3D/power3d.a -Wl,--subsystem,windows:4.10 -o ./bin/LOTCS.EXE
rm ./P3D/power3d.a P3D/power3d.lib
cp ./P3D/power3d.dll ./bin/power3d.dll