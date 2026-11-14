_Draw_Vec_Triangle    proc C DEPTHPOLY :DWORD

ASSUME ebp: ptr DEPTHPOLY

LOCAL x0, y0, z0, x1, y1, z1, mx, my, mix, miy e0, e1, e2 :DWORD

mov ebp, DEPTHPOLY ; get the struct at the proper location
push ebx
push esi
push edi

; put the screen resultion on the fpu stack first

fild fscreen_width
fild fscreen_height

; move the 4 varibles onto the fpu stack but w must be the highest value
fld DWORD ptr [ebp].w0
fld DWORD ptr [ebp].z0 ;
fld DWORD ptr [ebp].y0
fld DWORD ptr [ebp].x0

; divide each one by w, convert them to screen cordinates and put them in the local stack
fdiv st(3) ; x
fdiv st(5)
fstp DWORD ptr x0
fdiv st(2) ; y
fdiv st(3) 
fstp DWORD ptr y0
fdiv st(1) ; z
fstp DWORD ptr z0


; repeat the process for the other 2 points 

fld DWORD ptr [ebp].z1
fld DWORD ptr [ebp].y1 
fld DWORD ptr [ebp].x1

fdiv st(3) ; x
fdiv st(5)
fstp DWORD ptr x1
fdiv st(2) ; y
fdiv st(3) 
fstp DWORD ptr y1
fdiv st(1) ; z
fstp DWORD ptr z1

; last time

fld DWORD ptr [ebp].z2
fld DWORD ptr [ebp].y2 
fld DWORD ptr [ebp].x2

fdiv st(3) ; x
fdiv st(5)
fstp DWORD ptr x2
fdiv st(2) ; y
fdiv st(3) 
fstp DWORD ptr y2
fdiv st(1) ; z
fstp DWORD ptr z2



ffree st(0); clean up stack
ffree st(1)
fdecstp
fdecstp

mov esi, [ebp].color
mov edx, GdaPtr
mov ebp, [edx + 16]

mov eax, x0
mov ebx, x1
mov ecx, y0
mov edx, y1

min eax, ebx, x2
mov mix, eax
min ecx, edx, y2
mov miy, ecx
;
mov eax, x0
mov ecx, y0

max eax, ebx, x2
mov mx, eax
max ecx, edx, y2
mov my, ecx

mov ecx, esi


mov edx, miy

@lbl1:

mov eax, mix

@lbl2:

; get the 3 edges

mov esi, eax
mov edi, edx

edge esi, edi, x0, y0, x1, y1, ebx, e0

mov esi, eax
mov edi, edx

edge esi, edi, x1, y1, x2, y2, ebx, e1

mov esi, eax
mov edi, edx
edge esi, edi, x0, y0, x2, y2, ebx, e2

; if e0 >= 0 and e1 >= 0 and e2 >= 0 or e0 < 0 and e1 < 0 and e2 < 0 then draw a pixel
; if all 3 have the same sign then draw a pixel

cmp e0, 0
js @F
cmp e1, 0
js @lbl3
cmp e2, 0
js @lbl3

jmp lbl4 
@@:
cmp e1, 0
jns @lbl3
cmp e2, 0
jns @lbl3

@lbl4:

imul edi, edx, 480
add edi, eax
shl edi, 2
mov DWORD ptr [ebp + edi], ecx ; plot a pixel

@lbl3:

cmp eax, mx
jb @lbl2

cmp edx, my
jb @lbl1



pop edi
pop esi
pop ebx
ret 




_Draw_Vec_Triangle_flat endp

