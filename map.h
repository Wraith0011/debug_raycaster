#ifndef MAP_H
#define MAP_H
#include "global.h"

extern int map[MAP_NUM_ROWS][MAP_NUM_COLS];

bool is_wall_at(int x, int y);
void draw_minimap(SDL_Renderer* renderer);

#endif