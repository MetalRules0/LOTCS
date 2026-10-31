RenderProc proc

push eax
push esi
push ecx
push edx
mov esi, GdaPtr
mov eax, [esi + VIDL1]
mov edx, fbfinal
; memcopy to the final buffer

push BYTE_CNT
push edx
push eax

call MemCopy

mov esi, GdaPtr
mov eax, [esi + 8]
mov edx, [esi]
push SRCCOPY
push 0
push 0
push edx
push SCREEN_HEIGHT
push SCREEN_WIDTH
push 0
push 0
push eax
call BitBlt

call GetTickCount
mov FPS_Tick, eax ; tick count since last frame

pop edx
pop ecx
pop esi
pop eax
ret

RenderProc endp
