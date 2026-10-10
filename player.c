#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "power3d.h"
#include "collide.c"

void MovePlayer_xyz(Player *ps, LevelHeader *map) {

	float nx;
	float ny;
	float nz;
	AABB tilebox;
	Vec3f newpos;
	AABB newplayerbb;
	 
	CollisionTile *geoptr;
	 
	newpos.x = ps->x + ps->Xmot;
	newpos.y = ps->y + ps->Ymot;
	newpos.z = ps->z + ps->Zmot;	
	 
	geoptr = (CollisionTile *)((unsigned char *) map->map_OffsetAddr + map->CollisionOffset);
	 
	 // getPlayerAABB(&newplayerbb, nx, ny, nz);
	for (int i = 0; i < map->CollisionSize; i++) {
     // AABB data gets overwritten every time a new tile is called so it doesn't really matter that much
		RegisterCollisionTile(&tilebox, &geoptr[i]);
		// correct the player's movement to comply with AABB
		Vec3f mc = getAABBClip(&ps->bb, &tilebox);
		// check for player direction in order to correct movement properly
	if (ps->Xmot < 0.0f) {
            newpos.x += mc.x;
		} else {
            newpos.x -= mc.x;
		}
        if (ps->Ymot < 0.0f) {
            newpos.y += mc.y;
		} else {
            newpos.y -= mc.y;
		}
        if (ps->Zmot < 0.0f) {
            newpos.z += mc.z;
		} else {
            newpos.z -= mc.z;
		}
    }

    ps->x = newpos.x;
    ps->y = newpos.y;
    ps->z = newpos.z;

    ps->Xmot = 0.0f;
    ps->Ymot = 0.0f;
    ps->Zmot = 0.0f;
}
//done
void TurnPlayer(Player *ps, float xamount, float yamount, float maxpitch, float minpitch) {
	
	 ps->yrot += xamount * 0.15f;
	 ps->xrot += yamount * 0.15f;
	 
	 if (ps->xrot > maxpitch) {
	 	ps->xrot = maxpitch;  
	 }	  
     if (ps->xrot < minpitch) {	
     	ps->xrot = minpitch;
	 } 
	 return;
}

void MovePlayer_Relative(Player *ps, float x, float z, float speed) {
    float d2 = x * x + z * z;
    if (d2 < 0.01f)
        return; 
	{
        float k = speed / sqrtf(d2);
        x *= k;
        z *= k;
    }
    {
        double s = sin(ps->yrot * M_PI / 180.0);
        double c = cos(ps->yrot * M_PI / 180.0);

        ps->Xmot += (float)(x * c - z * s);
        ps->Zmot += (float)(z * c + x * s);
    }
}
