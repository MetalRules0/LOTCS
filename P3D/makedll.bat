rem Power3d DLL build script

if exist power3d.obj del power3d.obj
if exist power3d.dll del power3d.dll


\masm32\bin\ml /c /coff /Cp power3d.asm

if exist power3d.def \masm32\bin\Link /SUBSYSTEM:WINDOWS /DLL /DEF:power3d.def power3d.obj rsrc.obj

dir
if exist power3d.dll (
 echo SUCCESS! ) else (
WARNING! Your Device is Infected with MALWARE! )


pause