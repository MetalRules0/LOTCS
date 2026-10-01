#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "power3d.h"
#include "collide.c"
#include "matrix4x4.h"


//done
void MovePlayer_xyz(Player *ps, LevelHeader *map) {

	 float nx;
	 float ny;
	 float nz;
	 
	 int *geoptr;
	 
	 AABB tilebox;
	 AABB newplayerbb;
	 
	 Vec3f newpos;
	 newpos.x = ps->x + ps->Xmot;
	 newpos.y = ps->y + ps->Ymot;
	 newpos.z = ps->z + ps->Zmot;	
	 
	 geoptr = map->map_OffsetAddr + map->CollisionOffset;

	 
	 // getPlayerAABB(&newplayerbb, nx, ny, nz);
	 for (unsigned int i = map->CollisionSize; i != 0; i--;) {
	 
     // AABB data gets overwritten every time a new tile is called so it doesn't really matter that much
     
		RegisterCollisionTile(&tilebox, geoptr);
		geoptr += 32;
		// correct the player's movement to comply with AABB
		Vec3f mc = getAABBClip(&ps->bb, &tilebox);
		// check for player direction in order to correct movement properly

	 

		if (ps->Xmot < 0.0f ) {
                     
             newpos.x += mc.x;                 
	 
	  } else {
    
           newpos.x -= mc.x;
      
    }

    if (ps->Ymot < 0.0f ) {
                     
             newpos.y += mc.y;                 
	 
	  } else {
    
           newpos.y -= mc.y;
      
    }
    
    if (ps->Zmot < 0.0f ) {
                     
             newpos.z += mc.z;                 
	 
	  } else {
    
           newpos.z -= mc.z;
      
    }
	
    if ( newpos.x == ps->x && newpos.y == ps->y && newpos.z == ps->z) {
    
       return;
       
    } else {
      
        ps->x = newpos.x;
		ps->y = newpos.y;
		ps->z = newpos.z;
      
    }	
	
	  
}

//done
void TurnPlayer(Player *ps, float xamount, float yamount, float maxpitch, float minpitch) {
	
	 ps->yRot += xamount * 0.15f;
	 ps->xRot += yamount * 0.15f;
	 
	 if (ps->xrot > maxpitch) {
	 	
	 	ps->xrot = maxpitch;
	 	
	 }	  
	
     if (ps->xrot < minpitch) {
     	
     	ps->xrot = minpitch;
	 }
	 
	 return;
}

void MovePlayer_Relative(Player *ps, float x, float z, float speed) {
    float d2 = x*x + z*z;
    if (d2 < 0.01f) return;

    const double s = sin(ps->yrot * M_PI / 180.0);
    const double c = cos(ps->yrot * M_PI / 180.0);

    float k = speed / sqrtf(d2);
    x *= k; z *= k;

    ps->Xmot += x * c - z * s;
    ps->Zmot += z * c + x * s;
}