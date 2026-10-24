_iskeydown proc C lkey :WORD

; returns 1 while the key is held, 0 otherwise
; LKEY_* constants start at 1, keytable starts at index 0
movzx edx, lkey
dec edx
cmp edx, 9
ja @nokey
movzx edx, BYTE ptr [keytable + edx]
push edx
call GetAsyncKeyState
movzx eax, ax
shr eax, 15
ret
@nokey:
xor eax, eax
ret

_iskeydown endp
