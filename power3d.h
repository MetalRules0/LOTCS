#include <stdint.h>
#ifndef POWERX3D_H
#define POWERX3D_H

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 360

#define SKYCOLOR 0xFF8899DD
#define GRASSCOLOR 0xFF66EE88
#define WALLCOLOR 0xFFAA4466

#define MAP_ID_MAX_LEN 7
#define CAMERA_UPDATE_CALCULATE 4

#define LKEY_UP 1
#define LKEY_DOWN 2
#define LKEY_RIGHT 3
#define LKEY_LEFT 4
#define LKEY_A 5
#define LKEY_B 6
#define LKEY_R 7
#define LKEY_L 8
#define LKEY_PAUSE 9
#define LKEY_MISC 10

typedef struct {

	short x;
	short y;

} Vec2s;

typedef struct {

	float x;
	float y;

} Vec2f;

typedef struct {

	float x;
	float y;
	float z;

} Vec3f, vec3_t;

typedef struct {

	float x;
	float y;
	float z;
	float w;

} Vec4f, vec4_t;

typedef struct {

	float x0;
	float y0;
	float z0;
	float w0;
	float x1;
	float y1;
	float z1;
	float w1;
	float x2;
	float y2;
	float z2;
	float w2;
	float x3;
	float y3;
	float z3;
	float w3;

} Mat4f, mat4_t;

typedef struct {

	uint8_t flags;
	uint8_t other;
	uint16_t zrot;
	uint32_t ReactProc;
	float xpos;
	float ypos;
	float zpos;
	float xsize;
	float zsize;
	float xrot;
	

} CollisionTile;

typedef struct {

	uint32_t color;
	Vec2s a;
	Vec2s b;
	Vec2s c;

} WirePolygon;

typedef struct {

	uint32_t flags; // 0x00
	Vec3f a; // 0x04
	Vec3f b; // 0x10
	Vec3f c; // 0x1C
	uint32_t color; //0x28
	float scale; // 0x2C
	Vec4f misc; // 0x30

} RenderTile; // total size = 0x40 bytes



typedef struct {

	uint16_t flags;
	uint8_t UpdateMode;
	char unk_03;
	short viewWidth;
	short viewHeight;
	short viewStartX;
	short viewStartY;
	float nearClip;
	float farClip;
	float vfov;

} CameraInitData;

typedef struct {

	Vec3f pos;
	Vec3f rot;
	float vfov;
	uint16_t flags;
	float Pitch;
	float Yaw;
	CameraInitData Config;
	Mat4f CameraControlMatrix;

}Camera;

typedef struct {

	float x0;
	float y0;
	float z0;
	float x1;
	float y1;
	float z1;

} AABB;

typedef struct {

	float PrevX;
	float PrevY;
	float PrevZ;
	float x;
	float y;
	float z;
	float Xmot;
	float Ymot;
	float Zmot;
	float xrot;
	float yrot;
	AABB bb;
	int misc;

} Player;

typedef struct {

	uint32_t modelTreeRoot;
	uint32_t hitAssetCollisionoffset;
    uint32_t hitAssetZoneOffset;
	void *totalmapsize;
	uint32_t main;
	uint32_t entryList;
	int entrycount;
	char unk_1C[12];
    char** modelNameList;
    char** colliderNameList;
    char** zoneNameList;
	char unk_34[4];
	uint32_t background;
	float width;
	float height;
	float depth;



} MapSettings;

typedef struct {

	int flags;
	int CollisionOffset;
	int RenderOffset;
	int CollisionSize;
	int RenderSize;
	int *backround;
	int sky_color;
	int totalmapsize;
	float width;
	float height;
	float depth;
	int* map_OffsetAddr;


} LevelHeader;

/*
extern void  StartGame();
extern int  SetCoreProc(uint32_t funcptr, char type);
extern void  _Timer_new(int TPS);
extern void  _UpdateTimer();
extern void  _IncrementTimer();
extern int  _CheckIfReady();
extern void  _DrawLine(short x0, short y0, short x1, short y1, uint32_t color, uint32_t vbuffer);
extern void  _DrawWirePolygon(int polygonptr);
extern void  _SetPixel(short x, short y, uint32_t color, uint32_t scrbuf);
*/


__declspec(dllimport) void __stdcall StartGame();
__declspec(dllimport) int __stdcall SetCoreProc(uint32_t funcptr, char type);
__declspec(dllimport) void __stdcall _Timer_new(int TPS);
__declspec(dllimport) void __stdcall _UpdateTimer();
__declspec(dllimport) void __stdcall _IncrementTimer();
__declspec(dllimport) int __stdcall _CheckIfReady();
__declspec(dllimport) void __stdcall _DrawLine(short x0, short y0, short x1, short y1, uint32_t color, uint32_t vbuffer);
//POWERX3D void __stdcall _DrawWirePolygon(int polygonptr);
__declspec(dllimport) void __stdcall _SetPixel(short x, short y, uint32_t color, uint32_t scrbuf);


// Add vec2_t definition
typedef Vec2f vec2_t;

typedef struct {
    float u;
    float v;
} tex2_t;

typedef struct {
    vec4_t points[3];
    tex2_t texcoords[3];
} triangle_t;

#define NUM_PLANES 6

typedef Mat4f mat4f;

#endif
