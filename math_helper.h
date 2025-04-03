#ifndef MATH_HELPER_H
#define MATH_HELPER_H
#include "global.h"

typedef struct Vec2
{
	float x;
	float y;
}Vec2;
typedef struct iVec2
{
	int x;
	int y;
}iVec2;

float distance_between_points(float p1x, float p1y, float p2x, float p2y);
float normalize_angle(float angle);

#endif