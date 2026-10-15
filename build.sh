#!/usr/bin/env bash
#Install: WINE, GCC, MinGW-GCC
#Install to default WINE prefix: MASM SDK
#And obviously, make sure this file is executable...

clear
rm -r bin 2>/dev/null
mkdir bin

pushd P3D
echo | WINEDEBUG=-all wine makedll.bat
i686-w64-mingw32-dlltool -d power3d.def -l power3d.a

popd
echo Building LOTCS...
i686-w64-mingw32-gcc -g -std=c99 -march=i586 -Os -Wall -Wextra -Wpedantic main.c camera.c player.c collide.c P3D/power3d.a -Wl,--subsystem,windows:4.10 -o ./bin/LOTCS.EXE
rm ./P3D/power3d.a P3D/power3d.lib
mv ./P3D/power3d.dll ./bin/Power3D.dll
mv ./P3D/power3d.ilk ./bin/power3d.ilk
mv ./P3D/power3d.pdb ./bin/power3d.pdb
