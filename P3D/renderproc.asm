RenderProc proc


push esi
mov esi, GdaPtr
mov eax, [esi + 16]
mov edx, fbfinal
; memcopy to the final buffer

push BYTE_CNT
push edx
push eax

call MemCopy

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

pop esi

ret

RenderProc endp