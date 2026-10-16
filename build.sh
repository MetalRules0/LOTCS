#!/usr/bin/env bash
# Install: WINE, GCC, MinGW-GCC
# Install to default WINE prefix: MASM SDK
# And obviously, make sure this file is executable...

clear
rm -r bin 2>/dev/null
mkdir bin

pushd P3D
echo | WINEDEBUG=-all wine makedll.bat
i686-w64-mingw32-dlltool -d power3d.def -l power3d.a

popd
echo Building LOTCS...
# ... Do not generate unneccessary sections
Compiler=(-ffunction-sections -fdata-sections -fno-unwind-tables -fno-asynchronous-unwind-tables -fno-ident -fomit-frame-pointer)
# ... Link to Windows 95, remove unused sections in linker
Linker=(-Wl,--subsystem,windows:4.0 -Wl,--gc-sections)

i686-w64-mingw32-gcc -std=c99 -march=i586 -Os "${Compiler[@]}" -Wall -Wextra -Wpedantic main.c camera.c player.c collide.c P3D/power3d.a "${Linker[@]}" -o bin/LOTCS.EXE

# Manage build artifacts 
rm P3D/power3d.a P3D/power3d.lib
mv P3D/power3d.dll bin/Power3D.dll

# Strip even more useless information from the binaries
i686-w64-mingw32-strip -s bin/LOTCS.EXE
i686-w64-mingw32-strip -s bin/Power3D.dll