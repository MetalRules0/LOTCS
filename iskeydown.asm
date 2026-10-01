_iskeydown proc lkey :WORD

; yeah its a little primitive rn
movzx edx, lkey
mov ecx, offset keytable
add ecx, edx
movzx edx, WORD ptr [ecx]
xor dh, dh
push edx
call GetAsyncKeyState
and ax, 1
ret

_iskeydown endp