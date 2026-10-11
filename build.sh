#!/usr/bin/env bash
#Install: WINE, GCC, MinGW-GCC
#Install to WINE (Assuming default prefix): MASM SDK
#And obviously, make sure this file is executable...

clear
cd P3D
echo | WINEDEBUG=-all wine makedll.bat
i686-w64-mingw32-dlltool -d power3d.def -l power3d.a

cd ..
i686-w64-mingw32-gcc -std=c99 -Os -Wall -Wextra -Wpedantic main.c P3D/power3d.a -Wl,--subsystem,windows:4.10 -o LOTCS.EXE