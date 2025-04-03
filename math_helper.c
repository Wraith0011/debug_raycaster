#include "math_helper.h"

float distance_between_points(float p1x, float p1y, float p2x, float p2y)
{
	return sqrt( (p2x - p1x)*(p2x - p1x) + (p2y - p1y)*(p2y - p1y) );
}

float normalize_angle(float angle)
{
	angle = remainder(angle, TAU);
	if (angle < 0)
	{
		angle = angle + TAU;
	}
	return angle;
}