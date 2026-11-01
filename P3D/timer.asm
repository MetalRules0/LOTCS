
_Timer_new proc C TPS :DWORD

push ecx
push edx
mov eax, offset dummy_ret_1
mov ReadyProc, eax
mov eax, TPS
mov TickPerSecond, eax
mov ecx, eax
mov eax, 1000 ; ms per second
div ecx
mov MSPerTick, eax ; calculates the MS per tick form the ticks per second
call timeGetTime
mov TickCount, eax
mov LastTime, eax
pop edx
pop ecx
ret

_Timer_new endp

UpdateTimer proc
push eax
push edx
call timeGetTime
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

UpdateTimer endp

IncrementTimer proc

push eax
push edx
call timeGetTime
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

IncrementTimer endp

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

mov edx, MaxFrameTime
test edx, edx
jz @error_ ; if MaxFrameTime is 0, error

call timeGetTime
mov ebx, Frame_Tick
sub eax, ebx ; EAX = Current time - Last frame's time

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
mov MaxFrameTime, eax
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
