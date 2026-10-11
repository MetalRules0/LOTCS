#ifndef PLAYER_H
#define PLAYER_H

#include "power3d.h"

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

void MovePlayer_xyz(Player *ps, LevelHeader *map);

#endif
