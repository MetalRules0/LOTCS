
_Timer_new proc TPS :DWORD

mov eax, offset dummy_ret_1
mov ReadyProc, eax
mov eax, TPS
mov TickPerSecond, eax
call GetTickCount
mov TickCount, eax
mov LastTime, eax
ret

_Timer_new endp

_UpdateTimer proc
push eax
push edx
call GetTickCount
mov TickCount, eax
mov edx, eax
mov eax, LastTime
sub edx, eax
mov TimePassed, edx
mov eax, TickCount
mov LastTime, eax
pop edx
pop eax
ret

_UpdateTimer endp

_IncrementTimer proc

push eax
push edx
call GetTickCount
mov TickCount, eax
mov edx, eax
mov eax, LastTime
sub edx, eax
add TimePassed, edx
mov eax, TickCount
mov LastTime, eax
pop edx
pop eax
ret

_IncrementTimer endp

_CheckIfReady proc

push eax
push edx

mov eax, TimePassed
mov edx, MSPerTick
cmp eax, edx
ja @lbl1

pop edx
pop eax
clc
ret
@lbl1:

pop edx
pop eax
stc
ret
_CheckIfReady endp

_Timer_Reset Proc

xor eax, eax
mov TickCount, eax

_Timer_Reset endp

_SetTickSpeed proc NTPS :DWORD

mov eax, NTPS
mov MSPerTick, eax
ret

_SetTickSpeed endp

dummy_ret_1:
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
ret