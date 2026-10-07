
.386
.model flat, stdcall
option casemap :none   ; case sensitive

; #########################################################################

include \masm32\include\windows.inc
include \masm32\include\kernel32.inc
include \masm32\include\user32.inc
include \masm32\include\gdi32.inc
include \masm32\fpulib\fpu.inc
include \masm32\m32lib\masm32.inc
include common.inc

includelib \masm32\lib\kernel32.lib
includelib \masm32\lib\user32.lib
includelib \masm32\lib\gdi32.lib
includelib \masm32\fpulib\fpu.lib
includelib \masm32\m32lib\masm32.lib


; #########################################################################




.data

szDisplayName db "Game",0
ALIGN 4
CommandLine   dd 0
hWnd          dd 0
hInstance     dd 0
hBmp          dd 0
fntptr        dd 0
GameProc      dd 0
VideoProc     dd 0
DebugProc     dd 0
StartupProc   dd 0


ALIGN 4
TickCount dd 0
LastTime dd 0
TimePassed dd 0
Max_MS_Update dd 0
MSPerTick  dd 50
MaxTickUpdate dd 100
TickPerSecond dd 20
ReadyProc dd 0
TimerStatus db 0
ALIGN 4


player_level DD 0
DEFAULT_X DD 0
DEFAULT_Y DD 0
DEFAULT_Z DD 0


GdaPtr        dd 0

szClassName   db "Game_Class",0
ALIGN 4

scrdef        dd 00000042h

gameHeap      dd 0    
gameTickProc  dd 0
gameStatus    db 0
GameActive    db 0
ALIGN 4
infotext      db "PowerX3D engine version PC.20260626", 0
discordlnk    db "Our Public Dicord server(and for MCPlayground minecraft silver age anarchy server): https://discord.gg/tKYgqtpdcc", 0

ALIGN 4
keytable db 57h, 53h, 44h, 41h, 20h, 10h, 51h, 45h, 3Ah, 40h
ALIGN 4

fbfinal  dd 0
savebuf  dd 0
m0 dd 0
m1 dd 0
m2 dd 0
m3 dd 0
LC0 dd 1056964608
LC1 dd 1069547520

.code


LibMain proc hInstDLL:DWORD, reason:DWORD, unused:DWORD

            szText LmTitle,"tstdll's LibMain Function"

        .if reason == DLL_PROCESS_ATTACH
            szText ATTACHPROCESS,"PROCESS_ATTACH"
            invoke MessageBox,NULL,ADDR ATTACHPROCESS,addr LmTitle,MB_OK

            return TRUE
            ; -----------------------------
            ; If error at startup, return 0
            ; System will abort loading DLL
            ; -----------------------------

        .elseif reason == DLL_PROCESS_DETACH
            szText DETACHPROCESS,"PROCESS_DETACH"
            invoke MessageBox,NULL,addr DETACHPROCESS,addr LmTitle,MB_OK

        .elseif reason == DLL_THREAD_ATTACH
            szText ATTACHTHREAD,"THREAD_ATTACH"
            invoke MessageBox,NULL,addr ATTACHTHREAD,addr LmTitle,MB_OK

        .elseif reason == DLL_THREAD_DETACH
            szText DETACHTHREAD,"THREAD_DETACH"
            invoke MessageBox,NULL,addr DETACHTHREAD,addr LmTitle,MB_OK
            
        .endif

        ret

LibMain Endp


StartGame proc


call GetCommandLine
mov CommandLine, eax

call GetProcessHeap
mov gameHeap, eax
push 1024
push 8
push eax
call HeapAlloc
mov GdaPtr, eax
mov esi, eax
mov ebx, eax
add ebx, 32


push SW_SHOWDEFAULT
push CommandLine
push NULL
push hInstance
call WinMain

push eax
call ExitProcess

StartGame endp

; #########################################################################

WinMain proc hInst     :DWORD,
hPrevInst :DWORD,
CmdLine   :DWORD,
CmdShow   :DWORD


LOCAL wc   :WNDCLASSEX
LOCAL Wtx  :DWORD
LOCAL Wty  :DWORD

mov esi, GdaPtr
mov edx, esi
add edx, 256

;==================================================
; Fill WNDCLASSEX structure with required variables
;==================================================

mov wc.cbSize,          sizeof WNDCLASSEX
mov wc.lpfnWndProc,    offset WndProc      
mov wc.cbClsExtra,    NULL
mov wc.cbWndExtra,     NULL
mov eax, CS_OWNDC
mov edx, CS_HREDRAW
or eax, edx
mov wc.style,            eax
mov eax,                 hInst
mov wc.hInstance,    eax           
mov wc.hbrBackground,  COLOR_BTNFACE+1    
mov wc.lpszMenuName,   NULL
mov wc.lpszClassName,  offset szClassName  

push 500
push hInst
call LoadIcon
mov wc.hIcon, eax

push IDC_ARROW
push NULL
call LoadCursor
mov wc.hCursor, eax
mov wc.hIconSm, 0


lea eax, wc
push eax
call RegisterClassEx

;================================
; Centre window at following size
;================================

push SM_CXSCREEN
call GetSystemMetrics

mov ebx, SCREEN_WIDTH
mov ecx, eax
call TopXY
mov Wtx, eax

push SM_CYSCREEN
call GetSystemMetrics


mov ebx, SCREEN_HEIGHT
mov ecx, eax
call TopXY
mov Wty, eax
mov ecx, SCREEN_WIDTH
mov edx, SCREEN_HEIGHT

push NULL
push hInst
push NULL
push NULL
push edx
push ecx
push Wty
push Wtx
push 13107200
push offset szDisplayName
push offset szClassName
push WS_EX_OVERLAPPEDWINDOW
call CreateWindowEx
mov hWnd, eax
mov DWORD ptr [esi + 12], eax



push 600
push hInst
call LoadMenu

push eax
push hWnd
call SetMenu

push SW_SHOWNORMAL
push hWnd
call ShowWindow

push hWnd
call UpdateWindow


call LoadDisplay


mov al, gameStatus
or al, 00000010b
mov gameStatus, al


;===================================


; Loop until PostQuitMessage is sent
;===================================
mov esi, GdaPtr
mov ebx, esi
add ebx, 320
call RenderProc
call _UpdateTimer

@lbl1:

mov al, GameActive
test al, al
jnz EndLoop

GameLoop:
call _IncrementTimer

push PM_REMOVE
push 0
push 0
push NULL
push ebx
call PeekMessage

test eax, eax
jz @lbl2

mov eax, DWORD ptr [ebx + 4]
cmp eax, WM_QUIT
je EndLoop

push ebx
call TranslateMessage
push ebx
call DispatchMessage

jmp @lbl3
@lbl2:

push ebx
call RenderProc
pop ebx
mov eax, TimePassed
mov edx, MSPerTick
cmp eax, edx
jb @lbl3

pushfd
pushad
mov eax, GameProc
call eax
popad
popfd

xor eax, eax
mov TimePassed, eax
@lbl3:

pushad
pushfd
mov eax, VideoProc
call eax
popfd
popad  

mov al, GameActive
test al, al
jz GameLoop

EndLoop:

xor ah, al
mov al, 1
ret

WinMain endp










; #########################################################################


WndProc proc hWin :DWORD, uMsg :DWORD, wParam :DWORD, lParam :DWORD

.if uMsg == WM_COMMAND
;======== menu commands ========
.if wParam == 1000
invoke SendMessage,hWin,WM_SYSCOMMAND,SC_CLOSE,NULL
.elseif wParam == 1900
push MB_OK
push offset szDisplayName   ; in .data section
push offset infotext          ; in .data section
push hWin
call MessageBox
.elseif wParam == 1950
push MB_OK
push offset szDisplayName
push offset discordlnk
push hWin
call MessageBox
.elseif wParam == 1800
call _CheckIfReady
jnc @lbl1
szText TheText1,"Timer Charged :)"
szText TheText2,"Ok this sucks. the timer was not charged :("
invoke MessageBox,hWin,ADDR TheText1,offset szDisplayName,MB_YESNO
jmp @lbl2
@lbl1:
invoke MessageBox,hWin,ADDR TheText2,offset szDisplayName,MB_YESNO
.elseif wParam == 1850
mov eax, DebugProc
call eax
@lbl2:
.endif
;====== end menu commands ======

.elseif uMsg == WM_CLOSE
szText TheText,"Please Confirm Exit"
invoke MessageBox,hWin,ADDR TheText,offset szDisplayName,MB_YESNO
.if eax == IDNO
ret
.endif
.elseif uMsg == WM_DESTROY
invoke PostQuitMessage,NULL
mov eax, 0
ret
;.elseif uMsg == WM_PAINT
;dd    push ebx
;       push esi
;       mov esi, GdaPtr
;      mov ebx, [esi + 80]
;     pop esi
;    invoke BeginPaint,hWin, esi
;   mov edx, eax
;  call RenderProc
; invoke EndPaint,hWin,ADDR Ps

;    pop ebx


.endif

push lParam
push wParam
push uMsg
push hWin
call DefWindowProc

ret



ret
WndProc endp


LoadDisplay proc  ; WORKING DO NOT TOUCH


     push ebx
     push esi

     mov esi, GdaPtr
     mov ebx, esi
     add ebx, 32
  



mov ecx, 000FFFFFh ; 1 MB
mov edx, MEM_COMMIT
mov eax, MEM_RESERVE
or edx, eax
push PAGE_READWRITE
push edx
push ecx
push NULL
call VirtualAlloc
test eax, eax
jz allocfail
mov edi, eax
mov DWORD ptr [esi + 16], eax

push NULL
call CreateCompatibleDC
cmp eax, NULL
je noDIBfound
mov DWORD ptr [esi], eax

;
mov eax, 40
mov DWORD ptr [ebx], eax 
mov eax, SCREEN_WIDTH
mov DWORD ptr [ebx + 04h], eax
mov eax, SCREEN_HEIGHT
neg eax
mov DWORD ptr [ebx + 08h], eax
mov ax, 1
mov WORD ptr [ebx + 0Ch], ax
mov ax, 32
mov WORD ptr [ebx + 0Eh], ax
mov eax, 0
mov DWORD ptr [ebx + 10h], eax


mov eax, [esi]
push 0
push NULL
push offset fbfinal
push DIB_RGB_COLORS
push ebx
push eax
call CreateDIBSection
mov DWORD ptr [esi + 4], eax

push eax
mov ecx, [esi]
push ecx
call SelectObject

push hWnd
call GetDC
mov DWORD ptr [esi + 8], eax
mov edx, [esi]
mov ecx, scrdef
push ecx
push 0
push 0
push edx
push SCREEN_HEIGHT
push SCREEN_WIDTH
push 0
push 0
push eax
call BitBlt
mov ecx, [esi + 8]

mov eax, [esi + 16]

pop ebx
pop esi

ret

allocfail:
xor ebx, ebx
xor ax, ax
mov ds, ax
mov DWORD ptr [ebx], eax
ret
ret
ret
nop



gobackld:


mov al, gameStatus
or al, 8
mov gameStatus, al
  
  pop ebx
  pop esi

mov ecx, fbfinal
mov edx, [esi + 4]
ret

noDIBfound:

   pop ebx
   pop esi

ret

LoadDisplay endp         

SetCoreProc Proc funcptr :DWORD, functype :BYTE
mov al, functype
test al, al
jz @invalid
cmp al, 1
je @setgame
cmp al, 2
je @setrender
cmp al, 3
je @setdebug
cmp al, 4
je @setStartProc

@invalid:
mov eax, 0FFFFFFFFh
ret

@setgame:
mov eax, funcptr
mov GameProc, eax
xor eax, eax
ret

@setrender:

mov eax, funcptr
mov VideoProc, eax
xor eax, eax
ret

@setdebug:
mov eax, funcptr
mov DebugProc, eax
xor eax, eax
ret

@setStartProc:
mov eax, funcptr
mov StartupProc, eax
xor eax, eax
ret

SetCoreProc endp



DrawSky proc skcolor :DWORD

push ebx
push edi
push esi
mov esi, GdaPtr
mov edi, [esi + 16]
mov eax, skcolor
pop esi
mov ecx, PIXEL_CNT
xor ebx, ebx
@lbl1:
mov DWORD ptr [ebx + edi], eax
add ebx, 4
loop @lbl1
pop edi
pop ebx
ret

DrawSky endp

; ########################################################################


TopXY proc 


shr ecx, 1      ; divide screen dimension by 2
shr ebx, 1      ; divide window dimension by 2
mov eax, ebx    ; copy window dimension into eax
sub ecx, eax    ; sub half win dimension from half screen dimension

mov eax, ecx

ret

TopXY endp

GetDisplay proc

push esi
mov esi, GdaPtr
mov eax, [esi + 16]
pop esi
ret

GetDisplay endp

nop
nop
nop
nop




_GetSize_Zero proc _szptr :DWORD, _size :DWORD

push ebx
push edx
push esi

mov esi, _szptr
xor ecx, ecx
push eax
@lbl1:
mov edx, _size
@lbl2:
mov eax, DWORD ptr [esi] ; lodsd but for ebx
add esi, 4
test eax, eax ; chek if zero
jnz @lbl3; declaree success for 32 byte block
dec edx
jz @lbl4 ; failure if counter runs out, run away with ecx
jmp @lbl2

@lbl3:
add esi, 4
dec edx
jnz @lbl3
add ecx, 1
jmp @lbl1

@lbl4:


pop eax

pop esi
pop edx
pop ebx
ret

_GetSize_Zero endp

include setpixel.asm; 
include timer.asm;
include renderproc.asm;
include drawline.asm;
include PushPolygon.asm;
include draw_wire_polygon.asm
include iskeydown.asm




call FpuAdd
call FpuSub
call FpuMul
call FpuDiv
call FpuComp

 NOP
 NOP
 NOP
 NOP
 NOP
 NOP
 NOP
 NOP
 


; ########################################################################

end LibMain



