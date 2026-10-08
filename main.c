#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <memoryapi.h>
#include "power3d.h"
#include "player.c" //done
#include "Camera.c" //done
#include "polygon.c" // working on it

Player playerdata;
Camera viewport; 
LevelHeader gym;
char videomode;

    /*

; 256, 26, -256
; 256, 26, 256
; -256, 26, 256 done

; -256, 26, 256
; -256, 26, -256
; 256, 26, -256 done


; 256, 26, -256
; 256, 64, -256
; -256, 26, -256 done

; 256, 64, -256
; 256, 64, 256
; 256, 26, 256 done


; 256. 26. 256
; 256, 64, 256,
; 256, 64, -256 done

; 256, 26, 256
; 256, 26, -256
; 256, 64, -256 done


; -256, 26, -256
; 256, 26, -256 
; 256, 64, -256 done

; -256, 26, -256
; -256, 64, -256
; -256, 64, 256 done


; -256, 26, 256
; -256, 64, 256
; -256, 64, 256 done

; -256, 64, -256
; 256, 64, -256
; 256, 26, -256

*/

// done
void Render_scene(LevelHeader *map) {

    


}

int Draw_backround(int color) {

    // set up the loop for the scan lines
    for (int j = 0; j < SCREEN_HEIGHT; j++) {
    // draw a scan line
        for (int i = 0; i < SCREEN_WIDTH; i++) {
            // set the pixel on the screen of the desired color
            _SetPixel(i, j, color);

        }

    }
        return 0;
}

void AddRenderPlane(LevelHeader *finalmap, RenderTile *ntile, int index) {

    int spot = index * (int)sizeof(RenderTile);
    unsigned char *base = (unsigned char *)finalmap->map_OffsetAddr;
    RenderTile *addptr = (RenderTile *)(base + finalmap->RenderOffset + spot);
    memcpy(addptr, ntile, sizeof(RenderTile));
    return;
    

}

LevelHeader NewLevel(int xdim, int ydim, int zdim) {

	
	LevelHeader newmap;
    newmap.depth = ydim;
    newmap.width = xdim;
    newmap.height = zdim;
    newmap.CollisionOffset = xdim * ydim * 32;
    newmap.CollisionOffset += 128;
    newmap.RenderOffset = newmap.CollisionOffset + 64 + 0x000FFFFF; // 64 is for padding
    newmap.CollisionSize = 0;
    newmap.RenderSize = 11;
    newmap.totalmapsize = newmap.RenderOffset + newmap.RenderSize * (int)sizeof(RenderTile);
    newmap.map_OffsetAddr = VirtualAlloc(NULL, newmap.totalmapsize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    return newmap;


}

void gameloop() {

    if (_iskeydown(LKEY_UP) == 1) {

        MovePlayer_Relative(&playerdata, 1.0f, 0.0f, 0.3f);


    } else if (_iskeydown(LKEY_RIGHT) == 1) {

        TurnPlayer(&playerdata, 0.0f, 1.0f, 90.0f, -90.0f);

    } else if (_iskeydown(LKEY_LEFT) == 1) { 

        TurnPlayer(&playerdata, 0.0f, -1.0f, 90.0f, -90.0f);

    }

    
     
    MovePlayer_xyz(&playerdata, &gym);
    update_camera(&viewport, &playerdata); 

    
    return;

}

static int ProjectPoint(const Vec3f *world, const Camera *cam, Vec2s *screen) {
    float dx = world->x - cam->pos.x;
    float dy = world->y - cam->pos.y;
    float dz = world->z - cam->pos.z;
    float cp = cosf(cam->rot.x);
    float sp = sinf(cam->rot.x);
    float cy = cosf(cam->rot.y);
    float sy = sinf(cam->rot.y);

    float camx = cy * dx - sy * dz;
    float camz = sy * dx + cy * dz;
    float camy = cp * dy - sp * camz;
    camz = sp * dy + cp * camz;

    if (camz <= 0.01f) return 0;

    float vfov = cam->vfov;
    if (vfov <= 1.0f || vfov >= 179.0f) vfov = 80.0f;

    float fovrad = vfov * 0.5f * 0.01745329251994329577f;
    float focal = ((float)SCREEN_HEIGHT * 0.5f) / tanf(fovrad);

    int sx = (int)((float)SCREEN_WIDTH * 0.5f + camx * focal / camz);
    int sy_screen = (int)((float)SCREEN_HEIGHT * 0.5f - camy * focal / camz);

    if (sx < -32768) sx = -32768;
    if (sx > 32767) sx = 32767;
    if (sy_screen < -32768) sy_screen = -32768;
    if (sy_screen > 32767) sy_screen = 32767;

    screen->x = (short)sx;
    screen->y = (short)sy_screen;
    return 1;
}

void videoloop() {
    Draw_backround(SKYCOLOR);

    unsigned char *base = (unsigned char *)gym.map_OffsetAddr;
    RenderTile *planes = (RenderTile *)(base + gym.RenderOffset);

    for (int i = 0; i < gym.RenderSize; i++) {
        RenderTile *tile = &planes[i];
        Vec3f vertices[3] = { tile->a, tile->b, tile->c };
        Vec2s projected[3];
        int visible = 1;

        for (int v = 0; v < 3; v++) {
            if (!ProjectPoint(&vertices[v], &viewport, &projected[v])) {
                visible = 0;
                break;
            }
        }

        if (!visible) continue;

        WirePolygon poly;
        poly.color = tile->color;
        poly.a = projected[0];
        poly.b = projected[1];
        poly.c = projected[2];

        _DrawWirePolygon((uint32_t)&poly);
    }
}

int main() {
 
    CameraInitData viewdata;
    viewdata.flags = CAMERA_UPDATE_CALCULATE;
    viewdata.UpdateMode = 1;
    viewdata.vfov = 80;
    
    playerdata.x = 0;
    playerdata.y = 32;
    playerdata.z = 0;
    
    RenderTile tile_to_add;
    gym = NewLevel(256, 64, 256);



    tile_to_add.a.x = 256.0f;
    tile_to_add.a.y = 26.0f;
    tile_to_add.a.z = -256.0f;

    tile_to_add.b.x = 256.0f;
    tile_to_add.b.y = 26.0f;
    tile_to_add.b.z = 256.0f;

    tile_to_add.c.x = -256.0f;
    tile_to_add.c.y = 26.0f;
    tile_to_add.c.z = 256.0f;

    tile_to_add.color = GRASSCOLOR;
    tile_to_add.flags = 1;

    AddRenderPlane(&gym, &tile_to_add, 1);

    tile_to_add.a.x = -256.0f;
    tile_to_add.a.y = 26.0f;
    tile_to_add.a.z = 256.0f;

    tile_to_add.b.x = -256.0f;
    tile_to_add.b.y = 26.0f;
    tile_to_add.b.z = -256.0f;

    tile_to_add.c.x = 256.0f;
    tile_to_add.c.y = 26.0f;
    tile_to_add.c.z = -256.0f;

    tile_to_add.color = GRASSCOLOR;
    tile_to_add.flags = 1;

    AddRenderPlane(&gym, &tile_to_add, 2);

    tile_to_add.a.x = 256.0f;
    tile_to_add.a.y = 26.0f;
    tile_to_add.a.z = -256.0f;

    tile_to_add.b.x = 256.0f;
    tile_to_add.b.y = 64.0f;
    tile_to_add.b.z = -256.0f;

    tile_to_add.c.x = -256.0f;
    tile_to_add.c.y = 26.0f;
    tile_to_add.c.z = -256.0f;

    tile_to_add.color = WALLCOLOR;
    tile_to_add.flags = 1;

    AddRenderPlane(&gym, &tile_to_add, 3);

    tile_to_add.a.x = 256.0f;
    tile_to_add.a.y = 64.0f;
    tile_to_add.a.z = -256.0f;

    tile_to_add.b.x = 256.0f;
    tile_to_add.b.y = 64.0f;
    tile_to_add.b.z = 256.0f;

    tile_to_add.c.x = 256.0f;
    tile_to_add.c.y = 26.0f;
    tile_to_add.c.z = 256.0f;

    tile_to_add.color = WALLCOLOR;
    tile_to_add.flags = 1;

    AddRenderPlane(&gym, &tile_to_add, 4);

    tile_to_add.a.x = 256.0f;
    tile_to_add.a.y = 26.0f;
    tile_to_add.a.z = 256.0f;

    tile_to_add.b.x = 256.0f;
    tile_to_add.b.y = 64.0f;
    tile_to_add.b.z = 256.0f;

    tile_to_add.c.x = 256.0f;
    tile_to_add.c.y = 64.0f;
    tile_to_add.c.z = -256.0f;

    tile_to_add.color = WALLCOLOR;
    tile_to_add.flags = 1;

    AddRenderPlane(&gym, &tile_to_add, 5);

    tile_to_add.a.x = 256.0f;
    tile_to_add.a.y = 26.0f;
    tile_to_add.a.z = 256.0f;

    tile_to_add.b.x = 256.0f;
    tile_to_add.b.y = 26.0f;
    tile_to_add.b.z = -256.0f;

    tile_to_add.c.x = 256.0f;
    tile_to_add.c.y = 64.0f;
    tile_to_add.c.z = -256.0f;

    tile_to_add.color = WALLCOLOR;
    tile_to_add.flags = 1;

    AddRenderPlane(&gym, &tile_to_add, 6);

    tile_to_add.a.x = -256.0f;
    tile_to_add.a.y = 26.0f;
    tile_to_add.a.z = -256.0f;

    tile_to_add.b.x = 256.0f;
    tile_to_add.b.y = 26.0f;
    tile_to_add.b.z = -256.0f;

    tile_to_add.c.x = 256.0f;
    tile_to_add.c.y = 64.0f;
    tile_to_add.c.z = -256.0f;

    tile_to_add.color = WALLCOLOR;
    tile_to_add.flags = 1;

    AddRenderPlane(&gym, &tile_to_add, 7);

    tile_to_add.a.x = -256.0f;
    tile_to_add.a.y = 26.0f;
    tile_to_add.a.z = -256.0f;

    tile_to_add.b.x = -256.0f;
    tile_to_add.b.y = 64.0f;
    tile_to_add.b.z = -256.0f;

    tile_to_add.c.x = -256.0f;
    tile_to_add.c.y = 64.0f;
    tile_to_add.c.z = 256.0f;

    tile_to_add.color = WALLCOLOR;
    tile_to_add.flags = 1;

    AddRenderPlane(&gym, &tile_to_add, 8);

    tile_to_add.a.x = -256.0f;
    tile_to_add.a.y = 26.0f;
    tile_to_add.a.z = 256.0f;

    tile_to_add.b.x = -256.0f;
    tile_to_add.b.y = 64.0f;
    tile_to_add.b.z = 256.0f;

    tile_to_add.c.x = -256.0f;
    tile_to_add.c.y = 64.0f;
    tile_to_add.c.z = 256.0f;

    tile_to_add.color = WALLCOLOR;
    tile_to_add.flags = 1;

    AddRenderPlane(&gym, &tile_to_add, 9);

    tile_to_add.a.x = -256.0f;
    tile_to_add.a.y = 64.0f;
    tile_to_add.a.z = -256.0f;

    tile_to_add.b.x = 256.0f;
    tile_to_add.b.y = 64.0f;
    tile_to_add.b.z = -256.0f;

    tile_to_add.c.x = 256.0f;
    tile_to_add.c.y = 26.0f;
    tile_to_add.c.z = -256.0f;

    tile_to_add.color = WALLCOLOR;
    tile_to_add.flags = 1;

    AddRenderPlane(&gym, &tile_to_add, 10);


    //load the main level
    make_camera(&viewport, &viewdata, &playerdata);
    _Timer_new(20);
    SetCoreProc(&gameloop, 1); // function 1 gets called 20 times a second
    SetCoreProc(&videoloop, 2); // funtion 2 has no limit to how often it can get called
    // function 3 is only called when the debug menu option is selected
    StartGame();
    return 1;
}
