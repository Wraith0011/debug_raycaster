#ifndef GLOBAL_H
#define GLOBAL_H

// Include external libraries

#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

// Global defines

#define PI	3.141f
#define TAU 6.283f
#define QUARTER_TAU (TAU * 0.25f)
#define HALF_TAU (TAU * 0.5f)
#define THREEQUARTER_TAU (TAU * 0.75f)

#define WINDOW_WIDTH  360//360
#define WINDOW_HEIGHT 200//200

#define TARGET_FPS 60
#define TARGET_FRAME_TIME (1000.0f / TARGET_FPS) // 1 ms

#define TILE_SIZE 32
#define MAP_NUM_COLS 10
#define MAP_NUM_ROWS 10

#define MINIMAP_SCALE_FACTOR 0.5

#define FOV_ANGLE 60.0 * (PI / 180.0)
#define NUM_OF_RAYS (WINDOW_WIDTH)
#define DIST_BETWEEN_RAYS ((FOV_ANGLE) / NUM_OF_RAYS)
#define DIST_TO_PROJ_PLANE (WINDOW_WIDTH / 2) / (FOV_ANGLE / 2)

#define NUM_OF_SDL_KEYS 512

#define WALL_TEXTURE_SIZE (TILE_SIZE)
#define EMPTY 0


#endif