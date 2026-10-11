#ifndef CAMERA_H
#define CAMERA_H

#include <math.h>
#include <stdint.h>
#include "power3d.h"

typedef struct {

	Vec3f pos;
	Vec3f rot;
	float vfov;
	uint16_t flags;
	float Pitch;
	float Yaw;
	CameraInitData Config;
	Mat4f CameraControlMatrix;

}Camera;

int make_camera(Camera *cam_out, CameraInitData *camDataPtr, Player *playerDataPtr);

int update_camera (Camera *camptr, Player *pdata);

#endif
