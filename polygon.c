#include "polygon.h"
#include <math.h>



bool is_top_left(Vec2f* start, Vec2f* end) {
  Vec2f edge = { end->x - start->x, end->y - start->y };
  bool is_top_edge = edge.y == 0 && edge.x > 0;
  bool is_left_edge = edge.y < 0;
  return is_left_edge || is_top_edge;
}

float edge_cross(Vec2f* a, Vec2f* b, Vec2f* p) {
  Vec2f ab = { b->x - a->x, b->y - a->y };
  Vec2f ap = { p->x - a->x, p->y - a->y };
  return ab.x * ap.y - ab.y * ap.x;
}


void draw_pixel(float x, float y, int c) {

  short nx = 0, ny = 0;

  if (y < 1.0f && y > -1.0f) {
		if (y < -x) {
			nx = (x * SCREEN_WIDTH);
			ny = (y * SCREEN_HEIGHT);
		}
  }

  _SetPixel(nx, ny, c);

}

void draw_right_triangle(short x, short y, __attribute__((unused))signed short slope, __attribute__((unused))short height) {
	draw_pixel(x, y, 0); /* Todo: actual proper triangle drawing */
}

