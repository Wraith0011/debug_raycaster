#include "raycast.h"

Ray rays[NUM_OF_RAYS];

void cast_all_rays()
{
	float ray_angle = player.rotation_angle - (FOV_ANGLE / 2);
	for (int ray_index = 0; ray_index < NUM_OF_RAYS; ray_index++)
	{
		cast_ray(ray_angle, ray_index);
		ray_angle += DIST_BETWEEN_RAYS;
	}
}

void cast_ray(float angle, int ray_index)
{
	float ray_angle = normalize_angle(angle);

	bool is_ray_facing_down = (ray_angle > 0 && ray_angle < PI);
	bool is_ray_facing_up = !is_ray_facing_down;

	bool is_ray_facing_right = (ray_angle < 0.5 * PI || ray_angle > 1.5 * PI);
	bool is_ray_facing_left = !is_ray_facing_right;

	bool found_horizontal_wall = false;
	bool found_vertical_wall = false;

	// HORIZONTAL GRID INTERSECTION
	float horizontal_intercept_y = player.tile_y * TILE_SIZE;
	horizontal_intercept_y += is_ray_facing_down ? TILE_SIZE : 0;
	horizontal_intercept_y += is_ray_facing_up ? -1 : 0;

	float horizontal_intercept_x = player.x + (horizontal_intercept_y - player.y) / tan(ray_angle);
	
	float horizontal_step_y = TILE_SIZE;
	horizontal_step_y *= (is_ray_facing_up ? -1 : 1);

	float horizontal_step_x = TILE_SIZE / tan(ray_angle);
	horizontal_step_x *= (is_ray_facing_left && horizontal_step_x > 0) ? -1 : 1;
	horizontal_step_x *= (is_ray_facing_right && horizontal_step_x < 0) ? -1 : 1;

	float current_horizontal_step_x = horizontal_intercept_x;
	float current_horizontal_step_y = horizontal_intercept_y;

	int   horizontal_wall_hit_id = 0;
	float horizontal_wall_hit_x = (float)SDL_MAX_UINT32;
	float horizontal_wall_hit_y = (float)SDL_MAX_UINT32;

	float horizontal_hit_distance = (float)SDL_MAX_UINT32;

	while (current_horizontal_step_x >= 0 && current_horizontal_step_x <= MAP_NUM_COLS * TILE_SIZE && current_horizontal_step_y >= 0 && current_horizontal_step_y <= MAP_NUM_ROWS * TILE_SIZE)
	{
		if (is_wall_at(current_horizontal_step_x, current_horizontal_step_y) == true)
		{
			horizontal_wall_hit_x = current_horizontal_step_x;
			horizontal_wall_hit_y = current_horizontal_step_y;
			horizontal_wall_hit_id = map[(int)floor(horizontal_wall_hit_y/TILE_SIZE)][(int)floor(horizontal_wall_hit_x/TILE_SIZE)];
			found_horizontal_wall = true;
			break;
		}
		else
		{
			current_horizontal_step_x += horizontal_step_x;
			current_horizontal_step_y += horizontal_step_y;
		}
	}

	// VERTICAL GRID_INTERSECTION
	float vertical_intercept_x = floor(player.tile_x * TILE_SIZE - 1.0f);
	vertical_intercept_x += is_ray_facing_right ? TILE_SIZE + 1.0f : 0;

	float vertical_intercept_y = player.y + (vertical_intercept_x - player.x) * tan(ray_angle);

	float vertical_step_x = TILE_SIZE;
	vertical_step_x *= is_ray_facing_left ? -1 : 1;
	vertical_step_x += is_ray_facing_left ? -1 : 0;

	float vertical_step_y = TILE_SIZE * tan(ray_angle);
	vertical_step_y *= (is_ray_facing_up && vertical_step_y > 0) ? -1 : 1;
	vertical_step_y *= (is_ray_facing_down && vertical_step_y < 0) ? -1 : 1;

	float vertical_wall_hit_x = (float)SDL_MAX_UINT32;
	float vertical_wall_hit_y = (float)SDL_MAX_UINT32;
	float vertical_wall_hit_id = 0;

	float current_vertical_step_x = vertical_intercept_x;
	float current_vertical_step_y = vertical_intercept_y;

	float vertical_hit_distance = (float)SDL_MAX_UINT32;

	while (current_vertical_step_x >= 0 && current_vertical_step_x <= MAP_NUM_COLS * TILE_SIZE && current_vertical_step_y >= 0 && current_vertical_step_y <= MAP_NUM_ROWS * TILE_SIZE)
	{
		if (is_wall_at(current_vertical_step_x, current_vertical_step_y) == true)
		{
			vertical_wall_hit_x = current_vertical_step_x;
			vertical_wall_hit_y = current_vertical_step_y;
			vertical_wall_hit_id = map[(int)floor(current_vertical_step_y / TILE_SIZE)][(int)floor(current_vertical_step_x / TILE_SIZE)];
			found_vertical_wall = true;
			break;
		}
		else
		{
			current_vertical_step_x += vertical_step_x;
			current_vertical_step_y += vertical_step_y;
		}
	}
	
	 //Find out which ray was shorter
	if (found_horizontal_wall == true)
	{
		horizontal_hit_distance = distance_between_points(player.x, player.y, horizontal_wall_hit_x, horizontal_wall_hit_y);
		horizontal_hit_distance *= cos(ray_angle - player.rotation_angle);
	}
	if (found_vertical_wall == true)
	{
		vertical_hit_distance = distance_between_points(player.x, player.y, vertical_wall_hit_x, vertical_wall_hit_y);
		vertical_hit_distance *= cos(ray_angle - player.rotation_angle);
	}

	if (horizontal_hit_distance > vertical_hit_distance)
	{
		// Store vertical ray information
		rays[ray_index].ray_angle = ray_angle;
		rays[ray_index].was_intersection_vertical = true;
		rays[ray_index].is_ray_facing_up = is_ray_facing_up;
		rays[ray_index].is_ray_facing_down = is_ray_facing_down;
		rays[ray_index].is_ray_facing_left = is_ray_facing_left;
		rays[ray_index].is_ray_facing_right = is_ray_facing_right;
		rays[ray_index].wallhit_x = vertical_wall_hit_x;
		rays[ray_index].wallhit_y = vertical_wall_hit_y;
		rays[ray_index].wallhit_id = vertical_wall_hit_id;
		rays[ray_index].distance = vertical_hit_distance;
	}
	else
	{
		// Store horizontal ray information
		rays[ray_index].ray_angle = ray_angle;
		rays[ray_index].was_intersection_vertical = false;
		rays[ray_index].is_ray_facing_up = is_ray_facing_up;
		rays[ray_index].is_ray_facing_down = is_ray_facing_down;
		rays[ray_index].is_ray_facing_left = is_ray_facing_left;
		rays[ray_index].is_ray_facing_right = is_ray_facing_right;
		rays[ray_index].wallhit_x = horizontal_wall_hit_x;
		rays[ray_index].wallhit_y = horizontal_wall_hit_y;
		rays[ray_index].wallhit_id = horizontal_wall_hit_id;
		rays[ray_index].distance = horizontal_hit_distance;
	}
}

void draw_rays_on_minimap(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 200, 200, 0, 255);
	for (int i = 0; i < NUM_OF_RAYS; i++)
	{
		SDL_RenderDrawLineF
		(
			renderer,
			MINIMAP_SCALE_FACTOR * player.x,
			MINIMAP_SCALE_FACTOR * player.y,
			MINIMAP_SCALE_FACTOR * rays[i].wallhit_x,
			MINIMAP_SCALE_FACTOR * rays[i].wallhit_y
		);
	}
}