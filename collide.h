#ifndef COLLISION_H
#define COLLISION_H

#include "power3d.h"

typedef struct {

	float x0;
	float y0;
	float z0;
	float x1;
	float y1;
	float z1;

} AABB;


void RegisterCollisionTile(AABB *newtile, CollisionTile *oldtile);
Vec3f getAABBClip(AABB *a, AABB *b);

#endif
