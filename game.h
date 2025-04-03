#ifndef GAME_H
#define GAME_H

#include "global.h"
#include "math_helper.h"
#include "input.h"
#include "map.h"
#include "player.h"
#include "raycast.h"

typedef struct Game
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool is_running;
	Uint32 prev_frame_time;
	double delta_time;
}Game;
extern Game game;

int init();
void perform_timestep();
void process_events();
void update();
void draw();
void shutdown();

int SDL_main(int argc, char* argv[]);

#endif