
_Timer_new proc C TPS :DWORD

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

_Timer_Reset Proc

xor eax, eax
mov TickCount, eax

_Timer_Reset endp

_SetTickSpeed proc NTPS :DWORD

mov eax, NTPS
mov MSPerTick, eax
ret

_SetTickSpeed endp

_GetFrameRate proc C

push edi
push ebx
push edx

mov edi, MaxFPS ; edx stores the max framerate
test edx, edx
jz @error_ 
; if no error proceed as normal

call GetTickCount

mov ebx, FPS_Tick 
sub eax, ebx ; prepare for the divison by getting the time passed since the last frame in ms
xchg eax, ebx ; division is not reversible
xor edx, edx ; sacrifice edx to the gods for accurate division
mov ebx, 1000 ; convert ms to seconds
div ebx ; remander gets purged automatically when edx is restored

; eax = (GetTickCount() - ebx)/1000

pop edx
pop ebx
pop edi
ret

@error_:
mov eax, 0FFFFFFFFh ; return -1 if invalid

pop edx
pop ebx
pop edi
ret

_GetFrameRate endp

_SetFrameRate Proc C frate:DWORD

push eax
mov eax, frate
mov MaxFPS, eax
pop eax
ret

_SetFrameRate endp

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
