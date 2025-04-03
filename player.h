#ifndef PLAYER_H
#define PLAYER_H
#include "global.h"
#include "math_helper.h"
#include "input.h"
#include "map.h"

typedef struct Player
{
	float x;
	float y;
	float tile_x;
	float tile_y;
	float collider_width;
	float collider_height;
	float rotation_angle;
	float walk_speed;
	float turn_speed;
	int walk_dir;	// -1 walking backwards, 1 walking forwards
	int turn_dir;	// -1 turning left,      1 turning right
}Player;
extern Player player;

void init_player();
void update_player(double delta_time);
void draw_player_on_minimap(SDL_Renderer* renderer);

#endif