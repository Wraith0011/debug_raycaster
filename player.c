#include "player.h"

Player player;

void init_player()
{
	player.collider_width = 5;
	player.collider_height = 5;
	player.rotation_angle = PI/2;
	player.turn_dir = 0;
	player.turn_speed = 60 * (PI / 180);
	player.walk_dir = 0;
	player.walk_speed = 50.0f;
	player.x = (MAP_NUM_COLS / 2) * TILE_SIZE;
	player.y = (MAP_NUM_ROWS / 2) * TILE_SIZE;
}

void update_player(double delta_time)
{
	player.walk_dir = 0;
	player.turn_dir = 0;
	
	if (input.keys[SDLK_w])
	{
		player.walk_dir = 1;
	}
	if (input.keys[SDLK_s])
	{
		player.walk_dir = -1;
	}
	if (input.keys[SDLK_a])
	{
		player.turn_dir = -1;
	}
	if (input.keys[SDLK_d])
	{
		player.turn_dir = 1;
	}

	float move_step = player.walk_dir * player.walk_speed * delta_time;
	player.rotation_angle += player.turn_dir * player.turn_speed * delta_time;

	float new_x = player.x + cos(player.rotation_angle) * move_step;
	float new_y = player.y + sin(player.rotation_angle) * move_step;

	if (is_wall_at(new_x, new_y) == false)
	{
		player.x = new_x;
		player.y = new_y;
	}
	player.tile_x = floor(player.x / TILE_SIZE);
	player.tile_y = floor(player.y / TILE_SIZE);
}

void draw_player_on_minimap(SDL_Renderer* renderer)
{
	SDL_Rect destrect =
	{
		MINIMAP_SCALE_FACTOR * player.x,
		MINIMAP_SCALE_FACTOR * player.y,
		MINIMAP_SCALE_FACTOR * player.collider_width,
		MINIMAP_SCALE_FACTOR * player.collider_height
	};
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &destrect);
}