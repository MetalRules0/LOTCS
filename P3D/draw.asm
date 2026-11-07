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

COMMENT %
esp = dy0
esp + 2 = dx0
esp + 4 = dy1
esp + 6 = dx1
esp + 8 = dy2
esp + 10 = dx2
esp + 12 = start_x
esp + 14 = start_y
esp + 16 = e0
esp + 18 = e1
esp + 20 = e2
esp + 22 = area

%


;func edge(x, y, xi, yi, dXi, dYi)
;    return (x - xi)*dYi - (y-yi)*dXi
;
;func draw_triangle(x0, y0, x1, y1, x2, y2, v0, v1, v2):
;    dX0 = x0 - x2
;    dX1 = x1 - x0
;    dX2 = x2 - x1
;    dY0 = y0 - y2
;    dY1 = y1 - y0
;    dY2 = y2 - y1
;    start_x = 0
;    start_y = 0
;    e0 = edge(start_x, start_y, x0, y0, dX0, dY0)
;    e1 = edge(start_x, start_y, x1, y1, dX1, dY1)
;    e2 = edge(start_x, start_y, x2, y2, dX2, dY2)
;    area = e0 + e1 + e2
;    dYV = (dY0*v0 + dY1*v1 + dY2*v2) / area
;    dXV = (dX0*v0 + dX1*v1 + dX2*v2) / area
;
;    v = (e0*v0 + e1*v1 + e2*v2) / area
;
;    starting_e0 = e0
;    starting_e1 = e1
;    starting_e2 = e2
;    starting_v = v
;
;    for y = 0 to screen_height:
;        for x = 0 to screen_width:
;            if(e0 >= 0 && e1 >= 0 && e2 >= 0)
;                draw_pixel(x, y, v)
;            e0 = e0 + dY0
;            e1 = e1 + dY1
;            e2 = e2 + dY2
;            v = v + dYV
;
;        e0 = starting_e0 - dX0
;        e1 = starting_e1 - dX1
;        e2 = starting_e2 - dX2
;        v = starting_v - dXV
;
;        starting_e0 = e0
;        starting_e1 = e1
;        starting_e2 = e2
;        starting_v = v


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

mov DWORD ptr [esp], eax ; i think it could be backwords, as in y comes first, so the lower 2 bytes are y and the next 2 are x
mov DWORD ptr [esp + 4], ebx
mov DWORD ptr [esp + 8], edi

xor eax, eax
mov DWORD ptr [esp + 12], eax

mov ecx, [ebp].px
mov edx, [esp]

; edgefunc
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
mov eax, [ebp].px
mov ebx, [ebp].py

rol eax, 16
rol ebx, 16
cmp ax, bx
jae @F ; if bx is less than ax set ax to bx to get the min
mov ax, bx

@@:

cmp ax, WORD ptr [ebp + 2].pz
jae @F
mov ax, WORD ptr [ebp + 2].pz

@@:

; ax is now the minimum
movzx edx, ax
imul edx, edx, 480

mov eax, [ebp].px
rol ebx, 16

cmp ax, bx
jae @F ; if bx is less than ax set ax to bx to get the min
mov ax, bx

@@:

cmp ax, WORD ptr [ebp].pz
jae @F
mov ax, WORD ptr [ebp].pz

@@:

and eax, 0000FFFFh
add edx, eax
shl edx, 2

add edi, edx

; get the max values now


; get the max x

mov eax, [ebp].px
mov ebx, [ebp].py

cmp ax, bx
jb @F ; if bx is less than ax set ax to bx to get the min
mov ax, bx

@@:

cmp ax, WORD ptr [ebp].pz
jb @F
mov ax, WORD ptr [ebp].pz

@@:

movzx DWORD ptr [esp + 32], ax

; get the max y 
rol eax, 16
rol ebx, 16

cmp ax, bx
jb @F ; if bx is less than ax set ax to bx to get the min
mov ax, bx

@@:

cmp ax, WORD ptr [ebp + 2].pz
jb @F
mov ax, WORD ptr [ebp + 2].pz

@@:

movzx DWORD ptr [esp + 36], ax

@lbl1: ; first loop

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

add dx, WORD ptr [esp] ; dy0
rol edx, 16
add dx, WORD ptr [esp + 4] ; dy1
add bx, WORD ptr [esp + 8] ; dy2

inc ecx
cmp ecx, [esp + 32] ; x bounding box
jb @lbl2

inc ebp
cmp ebp, [esp + 36] ; y bounding box
jb @lbl1

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
