SCREEN_WIDTH equ 480
SCREEN_HEIGHT equ 360
PIXEL_CNT equ 172800
BYTE_CNT equ 691200
GRASSCOLOR equ 0FF66EE88h
SKYCOLOR equ 0FF8899DDh
MAP_ID_MAX_LEN EQU 8
MIN_X_ROT EQU 0C2B40000h 
MAX_Y_ROT EQU 042b40000h
GD_DIB EQU 4
GD_HDC EQU 8
GD_GLCONTEXT EQU 24
;=============
; Local macros
;=============


; COMMON DATA STRUCTURES (WIP)



Mat4_t STRUCT

x0 DWORD ?
y0 DWORD ?
z0 DWORD ?
w0 DWORD ?
x1 DWORD ?
y1 DWORD ?
z1 DWORD ?
w1 DWORD ?
x2 DWORD ?
y2 DWORD ?
z2 DWORD ?
w2 DWORD ?
x3 DWORD ?
y3 DWORD ?
z3 DWORD ?
w3 DWORD ?

Mat4_t ENDS

Vec2f STRUCT

x DWORD ?
y DWORD ?

Vec2f ENDS

Vec3f STRUCT

x DWORD ?
y DWORD ?
z DWORD ?

Vec3f ENDS

Vec4f STRUCT

x DWORD ?
y DWORD ?
z DWORD ?
w DWORD ?

Vec4f ENDS



NewLevel PROTO :DWORD, :DWORD, :DWORD


MapSettings STRUCT

modelTreeRoot DWORD ?
hitAssetCollisionOffset DWORD ?
hitAssetZoneOffset DWORD ?
unk_0C DWORD ?
main DWORD ?
entryList DWORD ?
unk_1C QWORD ?
modelNameList DWORD ?
colliderNameList DWORD ?
zoneNameList DWORD ?
background DWORD ?
unk_34 DWORD ?
msgID DWORD ?
height DWORD ?
mapwidth DWORD ?
depth DWORD ?
EventProc DWORD ?
MapSize DWORD ?


MapSettings ENDS

AABB STRUCT

x0 DWORD ?
y0 DWORD ?
z0 DWORD ?
x1 DWORD ?
y1 DWORD ?
z1 DWORD ?

AABB ENDS

COLLISIONTILE STRUCT

status BYTE ?
other BYTE ?
zrot WORD ?
ReactProc DWORD ?
xpos DWORD ?
ypos DWORD ?
zpos DWORD ?
xsize DWORD ?
zsize DWORD ?
xrot DWORD ?


COLLISIONTILE ENDS

CHUNKHEADER STRUCT 

bsize DWORD ? ; size of bytes for feild, MUST BE A MULTIPLE OF 32
chunktype BYTE ? ; bitmask for data
arraylist BYTE ?
chunksize WORD ?
next_x_pos DWORD ?
next_z_pos DWORD ?
next_x_neg DWORD ?
next_z_neg DWORD ?
split_ya DWORD ?
split_ypos WORD ?
split_yb WORD ?



CHUNKHEADER ENDS

CHUNKROWHEADER STRUCT 

chunksize DWORD ? ; must be the size of each chunk
again WORD ? ; for adding extra chunks in case more data is needed for that area
chunknum WORD ? ; number of chunks in row
nextrow DWORD ? ; pointer to the next


CHUNKROWHEADER ENDS 

PLAYER STRUCT

xo DWORD ?
yo DWORD ?
zo DWORD ?
x DWORD ?
y DWORD ?
z DWORD ?
xd DWORD ?
yd DWORD ?
zd DWORD ?
yrot DWORD ?
xrot DWORD ?
bb AABB <>
misc DWORD ?

PLAYER ENDS

RENDERTILE STRUCT 

flags DWORD ? ; misc data, dont worry about it for now
x0 DWORD ?
y0 DWORD ?
z0 DWORD ?
x1 DWORD ?
y1 DWORD ?
z1 DWORD ?
x2 DWORD ?
y2 DWORD ?
z2 DWORD ?
color DWORD ? ; can also be a pointer to texture
scale DWORD ? ; dont worry about this
m0 DWORD ?
m1 DWORD ? ; Dont worry about these
m2 DWORD ?
m3 DWORD ?

RENDERTILE ENDS 

CameraInitData STRUCT

flags WORD ?
UpdateMode BYTE ?
unk_03 BYTE ?
viewWidth WORD ?
viewHeight WORD ?
viewStartX WORD ?
viewStartY WORD ?
nearClip DWORD ?
farClip DWORD ?
vfov DWORD ?

CameraInitData ENDS

Camera STRUCT 


Pos Vec3f <>
Rot Vec3f <>
vfov DWORD ?
flags WORD ?
Pitch DWORD ?
Yaw DWORD ?
Config CameraInitData <>
CameraControlMatrix Mat4_t <>

Camera ENDS

CameraRig STRUCT

boomYaw DWORD ?
boomLength DWORD ?
boomPitch DWORD ?
viewPitch DWORD ?
targetXPos DWORD ?
targetYPos DWORD ?
targetZPos DWORD ?

CameraRig ENDS

WIREPOLY STRUCT

color DWORD ?
x0 WORD ?
y0 WORD ?
x1 WORD ?
y1 WORD ?
x2 WORD ?
y2 WORD ?

WIREPOLY ENDS

SRDATA STRUCT ; HEADER

flags DWORD ?
wireframe_sp WORD ?
renderplane_sp WORD ?
active_camera DWORD ?


SRDATA ENDS



szText MACRO Name, Text:VARARG
LOCAL lbl
jmp lbl
Name db Text,0
lbl:
ENDM

_abs MACRO _reg
LOCAL ispos_
cmp _reg, 0
jge ispos_
neg _reg             
ispos_:
ENDM



return MACRO arg
mov eax, arg
ret
ENDM

ztest MACRO
test eax, eax

ENDM


;=================
; Local prototypes
;=================
StartGame PROTO
WinMain PROTO :DWORD,:DWORD,:DWORD,:DWORD
WndProc PROTO :DWORD,:DWORD,:DWORD,:DWORD
SetCoreProc PROTO :DWORD, :BYTE
_Timer_new PROTO :DWORD
_UpdateTimer PROTO
_IncrementTimer PROTO
_CheckIfReady PROTO
_DrawLine PROTO :WORD, :WORD, :WORD, :WORD, :DWORD, :DWORD
_DrawWirePolygon PROTO :DWORD
_PushPolygon_wf PROTO :DWORD, :DWORD, :DWORD, :DWORD, :DWORD
_SetPixel PROTO :WORD, :WORD, :DWORD


PUBLIC StartGame
PUBLIC SetCoreProc
PUBLIC _Timer_new
PUBLIC _UpdateTimer
PUBLIC _CheckIfReady
PUBLIC _DrawLine
PUBLIC _SetPixel
PUBLIC _DrawWirePolygon
PUBLIC _iskeydown