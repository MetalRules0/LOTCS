#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <memoryapi.h>
#include "power3d.h"
#include "matrix4x4.h" 
// We don't have this file, whatever it may be. #include "COLISION.C" //done
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

    int spot = index * sizeof(RenderTile);
    int *addptr = finalmap->map_OffsetAddr + finalmap->RenderOffset + spot;
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
    newmap.totalmapsize = newmap.RenderOffset + newmap.CollisionOffset;
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

void videoloop() {
    
    // set up proper pointers
    return; // NOT WORKING BUT STILL NEEDS TESTING
    
    int i;
    int j;


    RenderTile *plane;
    WirePolygon k;
    WirePolygon h;
    
    plane = gym.map_OffsetAddr + gym.RenderOffset;
    const char *k = plane;
    
    Draw_backround(SKYCOLOR);

    // make a loop that first obtains the specs for the amount of render tiles
    for (int i = 0; i > gym.RenderSize; i++) {

        // use wireframes
        if (videomode == 1) {

            Normalise_Tile(&);


        } else {

            

        }

    // obtain a render tile


    // while in that loop, normalise, filter and convert them for rendering in a loop each time its called


    // apply extra transformations

    
    // convert them to screen corrdinates and render the polygon
    }
    return;

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


