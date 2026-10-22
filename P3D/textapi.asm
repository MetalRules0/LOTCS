; text api for rendering text using the character set
;
;

_Print_char proc txtinfo :WORD

ASSUME esi: ptr CHARSET_HEADER

push esi
mov esi, ChrSet
mov ax, txtinfo ; ah = color info, al = actual character
mov cl, TILE_BYTE_LEN


pop esi
ret

_Print_char endp
