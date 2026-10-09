#include <math.h>
#include <stdint.h>
#include "power3d.h"

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
//    .     .   ,       ,

//         ,     .  ,      .

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

/* AABB -> max/min X/Y/Z do NOT exist. What is this code referencing?
float AABB_clipXCollide(const AABB* a, const AABB* b, float x) {
    if (b->maxY <= a->minY || b->minY >= a->maxY) return x;
    if (b->maxZ <= a->minZ || b->minZ >= a->maxZ) return x;

    if (x > 0.0 && b->maxX <= a->minX) {
        float d = a->minX - b->maxX;
        return (d < x) ? d : x;
    }
    if (x < 0.0 && b->minX >= a->maxX) {
        float d = a->maxX - b->minX;
        return (d > x) ? d : x;
    }
    return x;
}

float AABB_clipYCollide(const AABB* a, const AABB* b, float y) {
    if (b->maxX <= a->minX || b->minX >= a->maxX) return y;
    if (b->maxZ <= a->minZ || b->minZ >= a->maxZ) return y;

    if (y > 0.0 && b->maxY <= a->minY) {
        float d = a->minY - b->maxY;
        return (d < y) ? d : y;
    }
    if (y < 0.0 && b->minY >= a->maxY) {
        float d = a->maxY - b->minY;
        return (d > y) ? d : y;
    }
    return y;
}

float AABB_clipZCollide(const AABB* a, const AABB* b, float z) {
    if (b->maxX <= a->minX || b->minX >= a->maxX) return z;
    if (b->maxY <= a->minY || b->minY >= a->maxY) return z;

    if (z > 0.0 && b->maxZ <= a->minZ) {
        float d = a->minZ - b->maxZ;
        return (d < z) ? d : z;
    }
    if (z < 0.0 && b->minZ >= a->maxZ) {
        float d = a->maxZ - b->minZ;
        return (d > z) ? d : z;
    }
    return z;
}
*/

