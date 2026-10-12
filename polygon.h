#ifndef POLYGON_H
#define POLYGON_H

#include <stdint.h>
#include <stdbool.h>
#include "power3d.h"

// polygon.h library

bool is_top_left(Vec2f* start, Vec2f* end);
float edge_cross(Vec2f* a, Vec2f* b, Vec2f* p);
void draw_pixel(float x, float y, int c);

#endif // end of library
