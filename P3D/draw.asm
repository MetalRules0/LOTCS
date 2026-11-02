_Draw_Square proc C x0 :WORD, y0 :WORD, x1 :WORD, y1 :WORD, color :DWORD
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

OPTION PROLOGUE:NONE
OPTION EPILOGUE:NONE

_Draw_Triangle_flat proc C WIREFRAME_POLY :DWORD

ASSUME ebp: PTR WIREPOLY

pushad

mov ebp, [esp + 8]
sub esp, 64

mov eax, [ebp].px
mov ebx, [ebp].py
mov edi, [ebp].pz
mov edx, eax
mov ecx, ebx

sub ax, di
sub bx, dx
sub di, cx

rol edx, 16
rol ecx, 16
rol edi, 16
rol ebx, 16
rol eax, 16

sub ax, di
sub bx, dx
sub di, cx

mov DWORD ptr [esp], eax
mov DWORD ptr [esp + 4], ebx
mov DWORD ptr [esp + 8], edi

xor eax, eax
mov DWORD ptr [esp + 12], eax

mov ecx, [ebp].px
mov edx, [esp]

; edgefunc
rol edx, 16
sub ax, cx
mul dx
rol eax, 16
rol ecx, 16
rol edx, 16
sub ax, cx
mul dx
mov dx, ax
rol eax, 16
sub ax, dx
rol ecx, 16

mov WORD ptr [esp + 16], ax

xor eax, eax
mov ecx, [ebp].py
mov edx, [esp + 4]

; edgefunc
rol edx, 16
sub ax, cx
mul dx
rol eax, 16
rol ecx, 16
rol edx, 16
sub ax, cx
mul dx
mov dx, ax
rol eax, 16
sub ax, dx
rol ecx, 16

mov WORD ptr [esp + 18], ax
mov di, ax

xor eax, eax
mov ecx, [ebp].pz
mov edx, [esp + 8]

; edgefunc
rol edx, 16
sub ax, cx
mul dx
rol eax, 16
rol ecx, 16
rol edx, 16
sub ax, cx
mul dx
mov dx, ax
rol eax, 16
sub ax, dx
rol ecx, 16

mov WORD ptr [esp + 20], ax
mov si, ax

add ax, si
add ax, di

mov WORD ptr [esp + 22], ax

mov eax, [esp + 16]
mov [esp + 24], eax
mov WORD ptr [esp + 28], si


;add logic here


mov edi, GdaPtr
mov edi, [edi + VIDL1]
mov esi, [ebp.color]


xor ecx, ecx

@lbl2:
test dx, dx
jb @nodraw
rol edx,  16
test dx, dx
jb @nodraw
test bx, bx
jb @nodraw
imul eax, ebp, 480
add eax, ecx
shl eax, 2
mov [edi + eax], esi

; UNFINISHED(WIP)


@nodraw:

add esp, 64
popad
ret


edgefunc:
rol edx, 16
sub ax, cx
mul dx
rol eax, 16
rol ecx, 16
rol edx, 16
sub ax, cx
mul dx
mov dx, ax
rol eax, 16
sub ax, dx
rol ecx, 16
ret




_Draw_Triangle_flat endp

OPTION PROLOGUE:PrologueDef
OPTION EPILOGUE:EpilogueDef
