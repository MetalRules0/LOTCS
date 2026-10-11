#ifndef COLLISION_H
#define COLLISION_H
#include <math.h>
#include <stdint.h>

typedef struct {

	float x0;
	float y0;
	float z0;
	float x1;
	float y1;
	float z1;

} AABB;

void RegisterCollisionTile(AABB *newtile, CollisionTile *oldtile) {
	
	float i;
	float j;
	float k;
	float x;
	float y;
		
	// floor collision	
 	if ((oldtile->flags & 0x0007) == 1)  {
 		
 		newtile->y0 = oldtile->ypos;
		newtile->y1 = oldtile->ypos;
		newtile->x0 = oldtile->xpos - (oldtile->xsize / 2);
		newtile->x1 = oldtile->xpos + (oldtile->xsize / 2);
		newtile->z0 = oldtile->zpos - (oldtile->zsize / 2);
		newtile->z1 = oldtile->zpos + (oldtile->zsize / 2);		
 		return; 
 		
	} else if ((oldtile->flags & 0x0007) == 2) {
		
		newtile->x0 = oldtile->xpos;
		newtile->x1 = oldtile->xpos;
		newtile->y0 = oldtile->ypos - (oldtile->xsize / 2);
		newtile->y1 = oldtile->ypos + (oldtile->xsize / 2);
		newtile->z0 = oldtile->zpos - (oldtile->zsize / 2);
		newtile->z1 = oldtile->zpos + (oldtile->zsize / 2);
		return;
		
		
	} else if ((oldtile->flags & 0x0007) == 3) {
		
		newtile->z0 = oldtile->zpos;
		newtile->z1 = oldtile->zpos;
		newtile->y0 = oldtile->ypos - (oldtile->xsize / 2);
		newtile->y1 = oldtile->ypos + (oldtile->xsize / 2);
		newtile->x0 = oldtile->xpos - (oldtile->zsize / 2);
		newtile->x1 = oldtile->xpos + (oldtile->zsize / 2);
		return;
		
	} else {
		
		return;
		
	}
	
	return;
	
}
  
Vec3f getAABBClip(AABB *a, AABB *b) {

      Vec3f v;

      if ( a->x0 <= b->x1 && a->x1 >= b->x0 ) {
            v.x = a->x1 - b->x0;
      } else {
            v.x = 0;       
      }
      
      if (a->y0 <= b->y1 && a->y1 >= b->y0) {
            v.y = a->y1 - b->y0;
      } else {
            v.y = 0;     
      }
      
      if ( a->z0 <= b->z1 && a->z1 >= b->z0 ) {
            v.z = a->z1 - b->z0;
      } else {
            v.z = 0;       
      }
      
      return v;
      
}

#endif
