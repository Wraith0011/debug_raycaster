#ifndef RAYCAST_H
#define RAYCAST_H
#include "global.h"
#include "player.h"
#include "map.h"
#include "math_helper.h"

typedef struct Ray
{
	float ray_angle;				// angle of the ray cast
	float wallhit_x;				// x coordinate of the wall hit by the ray
	float wallhit_y;				// y coordinate of the wall hit by the ray
	float distance;					// distance from where the ray was projected to where it hit
	bool was_intersection_vertical; // did the ray intersect the grid vertically?
	bool is_ray_facing_up;			// is the ray going in the -y direction
	bool is_ray_facing_down;		// is the ray going in the +y direction
	bool is_ray_facing_left;		// is the ray going in the -x diraction
	bool is_ray_facing_right;		// is the ray going in the +x direction
	int wallhit_id;					// integer ID of the wall that was hit by the ray
}Ray;
extern Ray rays[NUM_OF_RAYS];

void cast_all_rays();
void cast_ray(float angle, int ray_index);
void draw_rays_on_minimap(SDL_Renderer* renderer);

#endif