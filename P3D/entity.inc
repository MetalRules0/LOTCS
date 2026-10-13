; entity handler library module
; when ever you interract with an entity its eventproc will be called and 2 data values will be passed: 
; 1. a 32 bit integer with the command that is sent plus some info if needed later on in development
; 2. a pointer to the local entity struct for that specific entity

; when ever you interact with an entity in any way the entity the entity's type has its eventproc called and that specific entity of that type
; in the world has its struct located and sent off as part of the data. plus in the way you interracted with that entity gets passed off as the data value


ENTITY STRUCT
xpos DWORD ?
ypos DWORD ?
zpos DWORD ?
xmot DWORD ?
ymot DWORD ?
zmot DWORD ?
pitch DWORD ?
yaw DWORD ?
roll DWORD ?
hp WORD ?
tp WWORD ?
other DWORD ?
type WORD ?
attack WORD ?
defense WORD ?
time WORD ?
hpmax wORD ?
tpmax WORD ?
m0 DWORD ?
m1 DWORD ?
m2 DWORD ?
m3 DWORD ?
mw0 WORD ?
mw1 WORD ?
mw2 WORD ?
mw3 WORD ?
speed DWORD ?
sprite DWORD ?
animate WORD ?
frame WORD ?
eventptr DWORD ?
ENTITY ENDS


