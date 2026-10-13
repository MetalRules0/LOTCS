_Draw_Square proc x0 :WORD, y0 :WORD, x1 :WORD, y1 :WORD, color :DWORD
push esi
push ebx
push edi
mov ecx, GdaPtr
mov esi, [ecx + 16]
movzx ecx, x0
mov edx, color
movzx eax, y0
imul eax, eax, 480
add ax, x0
shl eax, 2
@lbl1:
push cx ; draw a line
@lbl2:
mov ebx, eax
add ebx, ecx
mov [esi + ebx], edx
inc ecx
cmp cx, x1
jng @lbl2
pop cx
add eax, 1920
movzx edx, y0
inc edx
cmp dx, y1
mov edx, color
jc @lbl1

pop edi
pop ebx
pop esi
nop
ret



_Draw_Square endp
