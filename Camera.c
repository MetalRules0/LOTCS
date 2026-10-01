#include <math.h>
#include <stdint.h>
#include "power3d.h"

int make_camera(Camera *cam_out, CameraInitData *camDataPtr, Player *playerDataPtr) {
    int i;
    int j;
    
    int vx;
    int vy;
    
    float cp;
    float sp;
    float cy;
    float sy;
    float cr;
    float sr;
    
    cam_out->Config.flags = camDataPtr->flags;
    cam_out->Config.farClip = camDataPtr->farClip;
    cam_out->Config.nearClip = camDataPtr->nearClip;
    cam_out->Config.vfov = camDataPtr->vfov;
    cam_out->Config.viewHeight = camDataPtr->viewHeight;
    cam_out->Config.viewStartX = camDataPtr->viewStartX;
    cam_out->Config.viewStartY = camDataPtr->viewStartY;
    cam_out->Config.viewWidth = camDataPtr->viewWidth;

    cam_out->vfov = camDataPtr->vfov;
    cam_out->Rot.x = playerDataPtr->xrot;
    cam_out->Rot.y = playerDataPtr->yrot;
    cam_out->Pos.x = playerDataPtr->x;
    cam_out->Pos.y = playerDataPtr->y;
    cam_out->Pos.z = playerDataPtr->z;
    
    cp = cosf(cam_out->Rot.x);
    sp = sinf(cam_out->Rot.x);
    cy = cosf(cam_out->Rot.y);
    sy = sinf(cam_out->Rot.y);
    cr = cosf(cam_out->Rot.z);
    sr = sinf(cam_out->Rot.z);

    cam_out->CameraControlMatrix.x0 = cy * cr + sy * sp * sr;
    cam_out->CameraControlMatrix.y0 = sr * cp;
    cam_out->CameraControlMatrix.z0 = -sy * cr + cy * sp * sr;
    cam_out->CameraControlMatrix.w0 = 0.0f;

    cam_out->CameraControlMatrix.x1 = -cy * sr + sy * sp * cr;
    cam_out->CameraControlMatrix.y1 = cr * cp;
    cam_out->CameraControlMatrix.z1 = sr * sy + cy * sp * sr;
    cam_out->CameraControlMatrix.w1 = 0.0f;

    cam_out->CameraControlMatrix.x2 = sy * cp;
    cam_out->CameraControlMatrix.y2 = -sp;
    cam_out->CameraControlMatrix.z2 = cy * cp;
    cam_out->CameraControlMatrix.w2 = 0.0f;

    cam_out->CameraControlMatrix.x3 = cam_out->Pos.x;
    cam_out->CameraControlMatrix.y3 = cam_out->Pos.y;
    cam_out->CameraControlMatrix.z3 = cam_out->Pos.z;
    cam_out->CameraControlMatrix.w3 = 1.0f;

    return 1;

}

int update_camera (Camera *camptr, Player *pdata) {

    float cp;
    float sp;
    float cy;
    float sy;
    float cr;
    float sr;

    camptr->Pos.x = pdata->x;
    camptr->Pos.y = pdata->y;
    camptr->Pos.z = pdata->z;
    
    camptr->Rot.x = pdata->xrot;
    camptr->Rot.x = pdata->yrot;

    if (camptr->flags & CAMERA_UPDATE_CALCULATE == CAMERA_UPDATE_CALCULATE) {

        camptr->Rot.x = asinf(pdata->yd);
        camptr->Rot.y = atan2f(pdata->xd, pdata->zd);


    } 
    
    cp = cosf(cam_out->Rot.x);
    sp = sinf(cam_out->Rot.x);
    cy = cosf(cam_out->Rot.y);
    sy = sinf(cam_out->Rot.y);
    cr = cosf(cam_out->Rot.z);
    sr = sinf(cam_out->Rot.z);

    camptr->CameraControlMatrix.x0 = cy * cr + sy * sp * sr;
    camptr->CameraControlMatrix.y0 = sr * cp;
    camptr->CameraControlMatrix.z0 = -sy * cr + cy * sp * sr;
    camptr->CameraControlMatrix.w0 = 0.0f;

    camptr->CameraControlMatrix.x1 = -cy * sr + sy * sp * cr;
    camptr->CameraControlMatrix.y1 = cr * cp;
    camptr->CameraControlMatrix.z1 = sr * sy + cy * sp * sr;
    camptr->CameraControlMatrix.w1 = 0.0f;

    camptr->CameraControlMatrix.x2 = sy * cp;
    camptr->CameraControlMatrix.y2 = -sp;
    camptr->CameraControlMatrix.z2 = cy * cp;
    camptr->CameraControlMatrix.w2 = 0.0f;

    camptr->CameraControlMatrix.x3 = camptr->Pos.x;
    camptr->CameraControlMatrix.y3 = camptr->Pos.y;
    camptr->CameraControlMatrix.z3 = camptr->Pos.z;
    camptr->CameraControlMatrix.w3 = 1.0f;



    return 1;

}