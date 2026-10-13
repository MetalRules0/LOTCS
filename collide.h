#ifndef COLLISION_H
#define COLLISION_H
#include <stdint.h>
#include "power3d.h"
// remove duplicate includes

typedef struct {

	float x0;
	float y0;
	float z0;
	float x1;
	float y1;
	float z1;

} AABB;

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


void RegisterCollisionTile(AABB *newtile, CollisionTile *oldtile);

Vec3f getAABBClip(AABB *a, AABB *b);

#endif
