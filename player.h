#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>
#include <stdlib.h>
#include "power3d.h"
#include "collide.h"

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

void TurnPlayer(Player *ps, float xamount, float yamount, float maxpitch, float minpitch);

void MovePlayer_Relative(Player *ps, float x, float z, float speed);

#endif
