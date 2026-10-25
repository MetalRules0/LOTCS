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

mov ecx, [esi + TXTL1]
mov edx, PIXEL_CNT
mov esi, fbfinal

@lbl1:
mov eax, [ecx]
test eax, eax
jz @lbl2:
mov [esi], eax
add esi, 4
@lbl2:
add ecx, 4
dec edx
test edx, edx
jnz @lbl1

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

pop edx
pop ecx
pop esi
pop eax
ret

RenderProc endp
