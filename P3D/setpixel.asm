_SetPixel proc xpos :WORD, ypos :WORD, color :DWORD

push esi
push ebx
push edx
mov esi, GdaPtr
mov eax, [esi + 16]
movzx ebx, ypos
imul ebx, 1920
movzx edx, xpos
shl edx, 2
add ebx, edx
add ebx, eax
mov edx, color
mov DWORD ptr [ebx], edx
pop edx
pop ebx
pop esi
ret

_SetPixel endp
