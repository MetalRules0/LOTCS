_SetPixel proc xpos :WORD, ypos :WORD, color :DWORD

push esi
mov esi, GdaPtr
mov eax, DWORD ptr [esi + 16]
pop esi
push ebx
movzx ebx, ypos
imul ebx, 1920
movzx edx, xpos
add ebx, edx
add ebx, eax
mov edx, color
mov DWORD ptr [ebx], edx
pop ebx
ret

_SetPixel endp

nop
nop
nop
nop