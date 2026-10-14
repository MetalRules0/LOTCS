_DrawSky Proc flags :DWORD, Color :DWORD
; flags is currently ignored for now

push ebx
mov ecx, GdaPtr
mov ebx, [ecx + VIDL1]
xor eax, eax
xor ecx, ecx
mov edx, Color
@lbl1:
xor eax, eax
@lbl2:
mov [ebx], edx
add ebx, 4
inc eax
cmp eax, SCREEN_WIDTH
jc @lbl2
inc ecx
cmp ecx, SCREEN_HEIGHT
jc @lbl1
pop ebx
ret

_DrawSky endp
