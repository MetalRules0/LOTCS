

_PushPolygon_wf proc a :DWORD, b :DWORD, cw :DWORD, color :DWORD, index :DWORD
; ebx is index
push edx
push edi
ASSUME ebx: ptr SRDATA
ASSUME edi: ptr WIREPOLY
mov ebx, index

push ebx
movzx edx, WORD ptr [ebx].wireframe_sp
shl edx, 4
add ebx, edx
add ebx, 64
mov edi, ebx
pop ebx

mov eax, a
mov WORD ptr [edi].x0, ax
shr eax, 16
mov WORD ptr [edi].y0, ax

mov eax, b
mov WORD ptr [edi].x1, ax
shr eax, 16
mov WORD ptr [edi].y1, ax

mov eax, cw
mov WORD ptr [edi].x2, ax
shr eax, 16
mov WORD ptr [edi].y2, ax

mov eax, color
mov [edi].color, eax
mov dx, WORD ptr [ebx].wireframe_sp
inc dx
mov word ptr [ebx].wireframe_sp, dx


@exit:
pop edi
pop edx
ret
_PushPolygon_wf endp