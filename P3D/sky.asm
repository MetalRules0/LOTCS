_DrawSky Proc C flags :DWORD, Color :DWORD
; flags is currently ignored for now
; C (cdecl) so it matches the declaration in power3d.h: caller cleans the stack

push edi
mov edx, GdaPtr
mov edi, DWORD ptr [edx + VIDL1]
test edi, edi            ; video layer not allocated yet -> nothing to draw
jz @done
mov eax, Color
mov ecx, PIXEL_CNT       ; 480 * 360 pixels
cld
rep stosd
@done:
pop edi
ret

_DrawSky endp
