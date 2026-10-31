


_DrawWirePolygon proc C Wireframe_Triangle :DWORD
LOCAL y0:WORD, x0:WORD, y1:WORD, x1:WORD ; make sure this isnt reversed ; MetalRules

push eax
push ebx
push ecx
push edx


ASSUME ebx: ptr WIREPOLY

mov ebx, Wireframe_Triangle
mov edi, GdaPtr
mov edi, [edi + VIDL1]

mov ecx, [ebx].color ;maybe i should try packing the bits ; MetalRules

mov eax, [ebx].py
mov edx, [ebx].px
call DrawLine
mov eax, [ebx].py
mov edx, [ebx].pz
call DrawLine
mov eax, [ebx].px
mov edx, [ebx].pz
call DrawLine

pop edx
pop ecx
pop ebx
pop eax


ret

DrawLine:
; eax is the xy0 and edx is the xy1

push eax
push ebx
push ecx
push edx
push esi

mov DWORD ptr [x0], eax
mov DWORD ptr [x1], edx 

mov  ax, dx
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
pop esi
pop edx
pop ecx
pop ebx
pop eax
ret



_DrawWirePolygon endp