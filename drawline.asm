_DrawLine proc x0 :WORD, y0 :WORD, x1 :WORD, y1 :WORD, col :DWORD, buf :DWORD ;WORKING

push eax
push ebx
push ecx
push edx
push esi
push edi

mov ecx, col
mov edi, buf


mov ax, x1
sub  ax, x0
_abs ax
mov dx, ax
rol edx, 16

mov ax, x0
cmp ax, x1
jge @lbl1
mov ax, 1
jmp @lbl2
@lbl1:
mov ax, -1


mov  ax, x1
sub  ax, x0
_abs ax
@lbl2:
rol eax, 16

mov dx, y1
sub dx, y0
_abs dx
neg dx

mov ax, y0
cmp ax, y1
jge @lbl3
mov ax, 1
jmp @lbl4
@lbl3:
mov ax, -1
@lbl4:
rol eax, 16

mov bx, dx
rol edx, 16
add bx, dx
rol edx, 16
;EdgeFunc proc



;EdgeFunc endp
@draw_loop:

push eax
push ebx
movzx eax, x0
cmp eax, SCREEN_WIDTH
ja @F
movzx ebx, y0
cmp ebx, SCREEN_HEIGHT
ja @F
imul ebx, 1920
shl eax, 2
add ebx, eax
mov DWORD ptr [ebx + edi], ecx
@@:
pop ebx
pop eax


rol esi, 16
mov si, x0
cmp si, x1
je @draw_done
mov si, y0
cmp si, y1
je @draw_done
rol esi, 16

mov si, bx
shl esi, 1
cmp si, dx
jge @lbl5
jmp @lbl6
@lbl5:
add bx, dx
add x0, ax
@lbl6:
rol edx, 16
rol eax, 16
cmp si, dx
jle @lbl7
jmp @draw_loop
@lbl7:
add bx, dx
add y0, ax
jmp @draw_loop



@draw_done:

pop edi
pop esi
pop edx
pop ecx
pop ebx
pop eax
ret

_DrawLine endp