; =====================================================================
; Text API - draws text straight into the main video layer (VIDL1)
;
; Font: 8x8 bitmap, ASCII 0..127 (see font8x8.inc). Anything above 127
; is drawn as '?'. Background is transparent (only set bits are drawn).
; Everything is clipped per pixel, so x/y may be negative or off screen.
; All coordinates are signed DWORDs, color is 0AARRGGBB like the rest
; of the engine. All functions are C (cdecl) and preserve ebx/esi/edi.
;
;   _Print_char   (x, y, char, color)    draws one character
;   _Print_string (x, y, strptr, color)  draws a zero terminated string,
;                                        returns number of characters drawn
;                                        0Ah = new line, 0Dh is ignored
;   _Print_int    (x, y, value, color)   draws a signed decimal number
; =====================================================================


_Print_char proc C xpos :DWORD, ypos :DWORD, cval :DWORD, color :DWORD
LOCAL rowidx :DWORD
LOCAL vbase :DWORD

push ebx
push esi
push edi

mov edx, GdaPtr
mov edx, DWORD ptr [edx + VIDL1]
test edx, edx                   ; video layer not allocated yet
jz @done
mov vbase, edx

mov eax, cval
cmp eax, 127
jbe @F
mov eax, '?'
@@:
shl eax, 3                      ; 8 bytes per glyph
lea esi, [ChrSet + eax]
mov ebx, color
mov rowidx, 0

@row:
mov eax, ypos
add eax, rowidx
cmp eax, SCREEN_HEIGHT          ; unsigned: also rejects negative y
jae @nextrow
imul edi, eax, SCREEN_WIDTH * 4 ; start of this scan line
add edi, vbase                  ; + video layer base
movzx eax, BYTE ptr [esi]       ; bit 0 = leftmost pixel
test eax, eax
jz @nextrow
xor ecx, ecx

@col:
bt eax, ecx
jnc @skip
mov edx, xpos
add edx, ecx
cmp edx, SCREEN_WIDTH           ; unsigned: also rejects negative x
jae @skip
mov DWORD ptr [edi + edx * 4], ebx
@skip:
inc ecx
cmp ecx, 8
jb @col

@nextrow:
inc esi
inc rowidx
cmp rowidx, 8
jb @row

@done:
pop edi
pop esi
pop ebx
ret

_Print_char endp


_Print_string proc C xpos :DWORD, ypos :DWORD, strptr :DWORD, color :DWORD
LOCAL curx :DWORD
LOCAL cury :DWORD
LOCAL count :DWORD

push ebx
push esi

mov eax, xpos
mov curx, eax
mov eax, ypos
mov cury, eax
mov count, 0

mov esi, strptr
test esi, esi
jz @done

@next:
movzx ebx, BYTE ptr [esi]
inc esi
test ebx, ebx
jz @done
cmp ebx, 0Ah
je @newline
cmp ebx, 0Dh
je @next
invoke _Print_char, curx, cury, ebx, color
add curx, TEXT_CELL_W
inc count
jmp @next

@newline:
mov eax, xpos
mov curx, eax
add cury, TEXT_CELL_H
cmp cury, SCREEN_HEIGHT         ; signed: nothing more can be visible
jge @done
jmp @next

@done:
mov eax, count
pop esi
pop ebx
ret

_Print_string endp


_Print_int proc C xpos :DWORD, ypos :DWORD, value :DWORD, color :DWORD
LOCAL numbuf[16] :BYTE

push ebx
push esi
push edi

lea edi, numbuf
add edi, 15                     ; digits are written backwards from the end
mov BYTE ptr [edi], 0

mov eax, value
mov esi, eax                    ; remember the sign
test eax, eax
jns @F
neg eax                         ; -2147483648 stays 80000000h, fine as unsigned
@@:
mov ebx, 10
@digit:
xor edx, edx
div ebx
add dl, '0'
dec edi
mov BYTE ptr [edi], dl
test eax, eax
jnz @digit

test esi, esi
jns @print
dec edi
mov BYTE ptr [edi], '-'

@print:
invoke _Print_string, xpos, ypos, edi, color

pop edi
pop esi
pop ebx
ret

_Print_int endp
