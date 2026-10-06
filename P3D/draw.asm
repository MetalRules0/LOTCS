_Draw_Square proc x0 :WORD, y0 :WORD, x1 :WORD, y1 :WORD, color :DWORD
push esi
push ebx
push edi
mov ecx, GdaPtr
mov esi, [esi + VIDL1]
movzx ecx, x0
mov edx, color
movzx eax, y0
imul eax, eax, 480
add ax, x0
shl eax, 2
@lbl1:
push cx
@lbl2:
mov ebx, eax
add ebx, ecx
mov [esi + ebx], edx
inc ecx
cmp cx, x1
jng @lbl2
pop cx


pop edi
pop ebx
pop esi
nop
ret



_Draw_Square endp
