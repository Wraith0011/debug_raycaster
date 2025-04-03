#include "map.h"

int map[MAP_NUM_ROWS][MAP_NUM_COLS] =
{
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

bool is_wall_at(int x, int y)
{
	// Find the map index given the world position
	int map_x = floor((float)x / TILE_SIZE);
	int map_y = floor((float)y / TILE_SIZE);

	if (map_x >= MAP_NUM_COLS || map_y >= MAP_NUM_ROWS || map_x < 0 || map_y < 0)
	{
		return false;
	}
	if (map[map_y][map_x] != EMPTY)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void draw_minimap(SDL_Renderer* renderer)
{
	// Loop through all the tiles in the map
	for (int y = 0; y < MAP_NUM_ROWS; y++)
	{
		for (int x = 0; x < MAP_NUM_COLS; x++)
		{
			// Get the tile position
			int tile_x = x * TILE_SIZE;
			int tile_y = y * TILE_SIZE;

			// Create the destination rectangle
			SDL_Rect tile_rect =
			{
				tile_x * MINIMAP_SCALE_FACTOR, 
				tile_y * MINIMAP_SCALE_FACTOR, 
				TILE_SIZE * MINIMAP_SCALE_FACTOR, 
				TILE_SIZE * MINIMAP_SCALE_FACTOR
			};

			// Draw minimap tiles based on their content
			if (map[y][x] == EMPTY)
			{
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderFillRect(renderer, &tile_rect);
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
				SDL_RenderFillRect(renderer, &tile_rect);
			}
		}
	}
}