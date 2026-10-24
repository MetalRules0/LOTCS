_SetPixel proc xpos :WORD, ypos :WORD, color :DWORD

push esi
push ebx
push edx
push eax

mov esi, GdaPtr
mov eax, [esi + 16]
movzx ebx, ypos
imul ebx, 1920 ; times a single row of 480 pixels
movzx edx, xpos
shl edx, 2 ; times 4
add ebx, edx
cmp ebx, BYTE_CNT
ja @outofscreen
add ebx, eax ; eax still has the origonal offset of the video layer
mov edx, color
mov DWORD PTR [ebx], edx
@outofscreen:

pop eax
pop edx
pop ebx
pop esi
ret

_SetPixel endp
